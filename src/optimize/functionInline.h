#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include "../ir/IRRoot.h"
#include "../ir/IRFunction.h"
#include "../ir/IRImpl.h"
#include "../ir/IRBlock.h"
#include "../ir/IRVar.h"
#include "../ir/IRValue.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRBinaryop.h"
#include "../ir/IRReturn.h"
#include "../ir/IRCall.h"
#include "../ir/IRParam.h"
#include "../ir/IRType.h"
#include "../ir/IRSext.h"
#include "../ir/IRZext.h"
#include "../ir/IRTrunc.h"
#include "../ir/IRPrint.h"
#include "../ir/IRExit.h"
#include "../ir/IRGetint.h"

namespace JaneZ {

class FunctionInline {
public:
    void optimize(std::shared_ptr<IRRoot> root) {
        if (!root) return;
        collectFunctions(root);
        collectInlineable();

        for (auto &child : root->children) {
            if (auto func = std::dynamic_pointer_cast<IRFunction>(child)) {
                for (auto &nested : func->funcList) inlineInFunction(nested);
                inlineInFunction(func);
            } else if (auto impl = std::dynamic_pointer_cast<IRImpl>(child)) {
                for (auto &func : impl->functions) inlineInFunction(func);
            }
        }
    }

private:
    using ValuePtr = std::shared_ptr<IRValue>;
    using VarPtr = std::shared_ptr<IRVar>;

    std::vector<std::shared_ptr<IRFunction>> functions;
    std::set<IRFunction*> inlineable;
    static constexpr int kMaxInlineInstr = 24;
    static constexpr int kMaxInlineRounds = 3;

    void collectFunctions(std::shared_ptr<IRRoot> root) {
        functions.clear();
        for (auto &child : root->children) {
            if (auto func = std::dynamic_pointer_cast<IRFunction>(child)) {
                collectFunction(func);
            } else if (auto impl = std::dynamic_pointer_cast<IRImpl>(child)) {
                for (auto &func : impl->functions) collectFunction(func);
            }
        }
    }

    void collectFunction(const std::shared_ptr<IRFunction> &func) {
        if (!func) return;
        functions.push_back(func);
        for (auto &nested : func->funcList) collectFunction(nested);
    }

    void collectInlineable() {
        inlineable.clear();
        for (auto &func : functions) {
            if (canInline(func)) inlineable.insert(func.get());
        }
    }

    bool canInline(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return false;
        if (func->name == "main") return false;
        if (!func->body->blockList.empty()) return false;
        if (!std::dynamic_pointer_cast<IRIntType>(func->retType) &&
            !std::dynamic_pointer_cast<IRVoidType>(func->retType)) {
            return false;
        }

        auto &instrs = func->body->instrList;
        if (instrs.empty() || instrs.size() > kMaxInlineInstr) return false;

        int returnCnt = 0;
        for (size_t i = 0; i < instrs.size(); i++) {
            if (std::dynamic_pointer_cast<IRBinaryop>(instrs[i])) continue;
            if (std::dynamic_pointer_cast<IRSext>(instrs[i])) continue;
            if (std::dynamic_pointer_cast<IRZext>(instrs[i])) continue;
            if (std::dynamic_pointer_cast<IRTrunc>(instrs[i])) continue;
            if (std::dynamic_pointer_cast<IRPrint>(instrs[i])) continue;
            if (std::dynamic_pointer_cast<IRExit>(instrs[i])) continue;
            if (std::dynamic_pointer_cast<IRGetint>(instrs[i])) continue;
            if (auto call = std::dynamic_pointer_cast<IRCall>(instrs[i])) {
                if (call->function.get() == func.get()) return false;
                continue;
            }
            if (std::dynamic_pointer_cast<IRReturn>(instrs[i])) {
                returnCnt++;
                if (i + 1 != instrs.size()) return false;
                continue;
            }
            return false;
        }
        return returnCnt == 1;
    }

    void inlineInFunction(const std::shared_ptr<IRFunction> &caller) {
        if (!caller || !caller->body) return;
        for (int round = 0; round < kMaxInlineRounds; round++) {
            bool changed = false;
            changed |= inlineInBlock(caller->body);
            for (auto &blk : caller->body->blockList) changed |= inlineInBlock(blk);
            if (!changed) break;
        }
    }

    bool inlineInBlock(const std::shared_ptr<IRBlock> &block) {
        if (!block) return false;

        bool changed = false;
        std::vector<std::shared_ptr<IRNode>> newInstrs;
        for (auto &instr : block->instrList) {
            auto call = std::dynamic_pointer_cast<IRCall>(instr);
            if (!call || !call->function ||
                !inlineable.count(call->function.get()) ||
                call->function.get() == nullptr) {
                newInstrs.push_back(instr);
                continue;
            }

            auto inlined = inlineCall(call);
            if (inlined.empty()) {
                newInstrs.push_back(instr);
                continue;
            }
            for (auto &cloned : inlined) newInstrs.push_back(cloned);
            changed = true;
        }
        block->instrList = std::move(newInstrs);
        return changed;
    }

    std::vector<std::shared_ptr<IRNode>> inlineCall(const std::shared_ptr<IRCall> &call) {
        std::vector<std::shared_ptr<IRNode>> result;
        auto callee = call->function;
        if (!callee || !callee->body || !call->pList) return result;
        if (callee->paramList && callee->paramList->paramList.size() > call->pList->paramList.size())
            return result;

        std::map<IRVar*, ValuePtr> valueMap;
        if (callee->paramList) {
            for (size_t i = 0; i < callee->paramList->paramList.size(); i++) {
                auto paramVar = std::dynamic_pointer_cast<IRVar>(callee->paramList->paramList[i]);
                auto argValue = std::dynamic_pointer_cast<IRValue>(call->pList->paramList[i]);
                if (!paramVar || !argValue) return {};
                valueMap[paramVar.get()] = argValue;
            }
        }

        ValuePtr returnValue = nullptr;
        for (auto &instr : callee->body->instrList) {
            if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
                auto cloned = cloneBinary(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRSext>(instr)) {
                auto cloned = cloneSext(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRZext>(instr)) {
                auto cloned = cloneZext(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRTrunc>(instr)) {
                auto cloned = cloneTrunc(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRPrint>(instr)) {
                auto cloned = clonePrint(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRExit>(instr)) {
                auto cloned = cloneExit(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRGetint>(instr)) {
                auto cloned = cloneGetint(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRCall>(instr)) {
                auto cloned = cloneCall(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto ret = std::dynamic_pointer_cast<IRReturn>(instr)) {
                returnValue = mapReturnValue(ret, valueMap);
                if (!returnValue && call->retVar) return {};
            }
        }

        if (call->retVar) {
            if (!returnValue) return {};
            auto assign = std::make_shared<IRBinaryop>(ADD, call->retVar);
            assign->leftValue = returnValue;
            assign->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
            result.push_back(assign);
        }
        return result;
    }

    std::shared_ptr<IRBinaryop> cloneBinary(const std::shared_ptr<IRBinaryop> &op,
                                            std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->result) return nullptr;
        auto clonedResult = cloneVar(op->result);
        auto cloned = std::make_shared<IRBinaryop>(op->op, clonedResult);
        cloned->leftValue = mapValue(op->leftValue, valueMap);
        cloned->rightValue = mapValue(op->rightValue, valueMap);
        cloned->utag = op->utag;
        cloned->i8tag = op->i8tag;
        cloned->w64tag = op->w64tag;
        if (!cloned->leftValue || !cloned->rightValue) return nullptr;
        valueMap[op->result.get()] = clonedResult;
        return cloned;
    }

    std::shared_ptr<IRSext> cloneSext(const std::shared_ptr<IRSext> &op,
                                      std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->value || !op->result) return nullptr;
        auto mapped = std::dynamic_pointer_cast<IRVar>(mapValue(op->value, valueMap));
        if (!mapped) return nullptr;
        auto clonedResult = cloneVar(op->result);
        auto cloned = std::make_shared<IRSext>(op->originalType, mapped, op->targetType, clonedResult);
        valueMap[op->result.get()] = clonedResult;
        return cloned;
    }

    std::shared_ptr<IRZext> cloneZext(const std::shared_ptr<IRZext> &op,
                                      std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->value || !op->result) return nullptr;
        auto mapped = std::dynamic_pointer_cast<IRVar>(mapValue(op->value, valueMap));
        if (!mapped) return nullptr;
        auto clonedResult = cloneVar(op->result);
        auto cloned = std::make_shared<IRZext>(op->originalType, mapped, op->targetType, clonedResult);
        valueMap[op->result.get()] = clonedResult;
        return cloned;
    }

    std::shared_ptr<IRTrunc> cloneTrunc(const std::shared_ptr<IRTrunc> &op,
                                        std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->value || !op->result) return nullptr;
        auto mapped = std::dynamic_pointer_cast<IRVar>(mapValue(op->value, valueMap));
        if (!mapped) return nullptr;
        auto clonedResult = cloneVar(op->result);
        auto cloned = std::make_shared<IRTrunc>(op->originalType, mapped, op->targetType, clonedResult);
        valueMap[op->result.get()] = clonedResult;
        return cloned;
    }

    std::shared_ptr<IRPrint> clonePrint(const std::shared_ptr<IRPrint> &op,
                                        std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op) return nullptr;
        auto cloned = std::make_shared<IRPrint>();
        cloned->printVar = mapValue(op->printVar, valueMap);
        cloned->inttag = op->inttag;
        return cloned;
    }

    std::shared_ptr<IRExit> cloneExit(const std::shared_ptr<IRExit> &op,
                                      std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op) return nullptr;
        return std::make_shared<IRExit>(mapValue(op->exitCode, valueMap));
    }

    std::shared_ptr<IRGetint> cloneGetint(const std::shared_ptr<IRGetint> &op,
                                          std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->result) return nullptr;
        auto clonedResult = cloneVar(op->result);
        valueMap[op->result.get()] = clonedResult;
        return std::make_shared<IRGetint>(clonedResult);
    }

    std::shared_ptr<IRCall> cloneCall(const std::shared_ptr<IRCall> &op,
                                      std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->pList) return nullptr;
        auto cloned = std::make_shared<IRCall>();
        cloned->function = op->function;
        cloned->pList = std::make_shared<IRParam>();
        for (auto &param : op->pList->paramList) {
            auto value = std::dynamic_pointer_cast<IRValue>(param);
            if (!value) return nullptr;
            auto mapped = mapValue(value, valueMap);
            if (!mapped) return nullptr;
            cloned->pList->paramList.push_back(std::dynamic_pointer_cast<IRNode>(mapped));
        }
        if (op->retVar) {
            cloned->retVar = cloneVar(op->retVar);
            valueMap[op->retVar.get()] = cloned->retVar;
        }
        return cloned;
    }

    ValuePtr mapReturnValue(const std::shared_ptr<IRReturn> &ret,
                            std::map<IRVar*, ValuePtr> &valueMap) {
        if (!ret) return nullptr;
        if (ret->returnLiteral) return ret->returnLiteral;
        if (ret->returnValue) return mapValue(ret->returnValue, valueMap);
        return nullptr;
    }

    ValuePtr mapValue(const ValuePtr &value, std::map<IRVar*, ValuePtr> &valueMap) {
        if (!value) return nullptr;
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(value)) return lit;
        if (auto var = std::dynamic_pointer_cast<IRVar>(value)) {
            auto it = valueMap.find(var.get());
            if (it != valueMap.end()) return it->second;
            return var;
        }
        return value;
    }

    VarPtr cloneVar(const VarPtr &var) {
        auto cloned = std::make_shared<IRVar>();
        if (!var) return cloned;
        cloned->type = var->type;
        cloned->varName = var->varName;
        cloned->reName = var->reName;
        cloned->isSelf = var->isSelf;
        cloned->baseVar = var->baseVar;
        cloned->isUsed = var->isUsed;
        return cloned;
    }
};

}
