#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include "../ir/IRAlloca.h"
#include "../ir/IRRoot.h"
#include "../ir/IRFunction.h"
#include "../ir/IRImpl.h"
#include "../ir/IRBlock.h"
#include "../ir/IRVar.h"
#include "../ir/IRValue.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRBinaryop.h"
#include "../ir/IRGetptr.h"
#include "../ir/IRLoad.h"
#include "../ir/IRReturn.h"
#include "../ir/IRCall.h"
#include "../ir/IRParam.h"
#include "../ir/IRStore.h"
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
        collectCallCounts();
        buildCallGraph();
        collectRecursiveFunctions();
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
    std::map<IRFunction*, int> callCounts;
    std::map<IRFunction*, std::set<IRFunction*>> callGraph;
    std::set<IRFunction*> recursiveFunctions;
    std::map<IRFunction*, int> costCache;
    static constexpr int kMaxInlineInstr = 24;
    static constexpr int kSingleUseInlineInstr = 48;
    static constexpr int kMaxInlineCost = 36;
    static constexpr int kSingleUseInlineCost = 92;
    static constexpr int kTinyInlineCost = 14;
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

    void collectCallCounts() {
        callCounts.clear();
        for (auto &func : functions) {
            countCallsInFunction(func);
        }
    }

    void countCallsInFunction(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        countCallsInBlock(func->body);
        for (auto &blk : func->body->blockList) countCallsInBlock(blk);
    }

    void countCallsInBlock(const std::shared_ptr<IRBlock> &block) {
        if (!block) return;
        for (auto &instr : block->instrList) {
            auto call = std::dynamic_pointer_cast<IRCall>(instr);
            if (call && call->function) callCounts[call->function.get()]++;
        }
    }

    void buildCallGraph() {
        callGraph.clear();
        for (auto &func : functions) {
            if (!func || !func->body) continue;
            auto *raw = func.get();
            callGraph[raw] = {};
            collectCallsInBlock(func->body, callGraph[raw]);
            for (auto &blk : func->body->blockList) collectCallsInBlock(blk, callGraph[raw]);
        }
    }

    void collectCallsInBlock(const std::shared_ptr<IRBlock> &block,
                             std::set<IRFunction*> &out) {
        if (!block) return;
        for (auto &instr : block->instrList) {
            auto call = std::dynamic_pointer_cast<IRCall>(instr);
            if (call && call->function) out.insert(call->function.get());
        }
    }

    void collectRecursiveFunctions() {
        recursiveFunctions.clear();
        for (auto &func : functions) {
            if (!func) continue;
            std::set<IRFunction*> visiting;
            if (canReach(func.get(), func.get(), visiting)) {
                recursiveFunctions.insert(func.get());
            }
        }
    }

    bool canReach(IRFunction *start, IRFunction *target, std::set<IRFunction*> &visiting) {
        if (!start || !callGraph.count(start)) return false;
        for (auto *next : callGraph[start]) {
            if (!next) continue;
            if (next == target) return true;
            if (!visiting.insert(next).second) continue;
            if (canReach(next, target, visiting)) return true;
        }
        return false;
    }

    bool canInline(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return false;
        if (func->name == "main") return false;
        if (!func->body->blockList.empty()) return false;
        if (recursiveFunctions.count(func.get())) return false;
        if (!std::dynamic_pointer_cast<IRIntType>(func->retType) &&
            !std::dynamic_pointer_cast<IRVoidType>(func->retType)) {
            return false;
        }

        auto &instrs = func->body->instrList;
        size_t paramCount = func->paramList ? func->paramList->paramList.size() : 0;
        int callCount = callCounts.count(func.get()) ? callCounts[func.get()] : 0;
        int instrLimit = (callCount == 1 && paramCount <= 8) ? kSingleUseInlineInstr : kMaxInlineInstr;
        if (instrs.empty() || instrs.size() > static_cast<size_t>(instrLimit)) return false;

        int cost = inlineCost(func);
        if (cost < 0) return false;
        int costLimit = (callCount == 1 && paramCount <= 10) ? kSingleUseInlineCost : kMaxInlineCost;
        if (isTinyInline(func, cost)) costLimit = std::max(costLimit, kTinyInlineCost);
        if (cost > costLimit) return false;

        int returnCnt = 0;
        for (size_t i = 0; i < instrs.size(); i++) {
            if (isAllowedInlineInstr(func, instrs[i])) {
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

    bool isAllowedInlineInstr(const std::shared_ptr<IRFunction> &func,
                              const std::shared_ptr<IRNode> &instr) const {
        if (!instr) return false;
        if (std::dynamic_pointer_cast<IRAlloca>(instr) ||
            std::dynamic_pointer_cast<IRLoad>(instr) ||
            std::dynamic_pointer_cast<IRStore>(instr) ||
            std::dynamic_pointer_cast<IRGetptr>(instr)) return false;
        if (std::dynamic_pointer_cast<IRReturn>(instr)) return false;
        if (auto call = std::dynamic_pointer_cast<IRCall>(instr)) {
            return call->function.get() != func.get();
        }
        return std::dynamic_pointer_cast<IRBinaryop>(instr) ||
               std::dynamic_pointer_cast<IRSext>(instr) ||
               std::dynamic_pointer_cast<IRZext>(instr) ||
               std::dynamic_pointer_cast<IRTrunc>(instr) ||
               std::dynamic_pointer_cast<IRPrint>(instr) ||
               std::dynamic_pointer_cast<IRExit>(instr) ||
               std::dynamic_pointer_cast<IRGetint>(instr);
    }

    int inlineCost(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return -1;
        auto cached = costCache.find(func.get());
        if (cached != costCache.end()) return cached->second;

        int cost = paramCost(func);
        int returnCnt = 0;
        auto &instrs = func->body->instrList;
        for (size_t i = 0; i < instrs.size(); i++) {
            auto instr = instrs[i];
            if (std::dynamic_pointer_cast<IRReturn>(instr)) {
                returnCnt++;
                if (i + 1 != instrs.size()) return costCache[func.get()] = -1;
                continue;
            }
            int icost = instrCost(func, instr);
            if (icost < 0) return costCache[func.get()] = -1;
            cost += icost;
        }
        if (returnCnt != 1) return costCache[func.get()] = -1;
        return costCache[func.get()] = cost;
    }

    int instrCost(const std::shared_ptr<IRFunction> &func,
                  const std::shared_ptr<IRNode> &instr) const {
        if (!instr) return -1;
        if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
            return alloca->allocatedType && isScalarMemoryType(alloca->allocatedType) ? 2 : -1;
        }
        if (std::dynamic_pointer_cast<IRLoad>(instr)) return 3;
        if (std::dynamic_pointer_cast<IRStore>(instr)) return 3;
        if (std::dynamic_pointer_cast<IRGetptr>(instr)) return 2;
        if (std::dynamic_pointer_cast<IRBinaryop>(instr)) return 2;
        if (std::dynamic_pointer_cast<IRSext>(instr) ||
            std::dynamic_pointer_cast<IRZext>(instr) ||
            std::dynamic_pointer_cast<IRTrunc>(instr)) return 1;
        if (std::dynamic_pointer_cast<IRPrint>(instr) ||
            std::dynamic_pointer_cast<IRExit>(instr) ||
            std::dynamic_pointer_cast<IRGetint>(instr)) return 8;
        if (auto call = std::dynamic_pointer_cast<IRCall>(instr)) {
            if (call->function.get() == func.get()) return -1;
            int argc = call->pList ? static_cast<int>(call->pList->paramList.size()) : 0;
            return 10 + argc;
        }
        return -1;
    }

    int paramCost(const std::shared_ptr<IRFunction> &func) const {
        if (!func || !func->paramList) return 0;
        int cost = 0;
        int count = static_cast<int>(func->paramList->paramList.size());
        if (count > 8) cost += (count - 8) * 8;
        for (auto &param : func->paramList->paramList) {
            auto var = std::dynamic_pointer_cast<IRVar>(param);
            if (!var || !var->type) continue;
            if (isAggregateLike(var->type)) cost += 16;
            else if (auto ptr = std::dynamic_pointer_cast<IRPtrType>(var->type)) {
                cost += isAggregateLike(ptr->baseType) ? 8 : 2;
            }
        }
        return cost;
    }

    bool isTinyInline(const std::shared_ptr<IRFunction> &func, int cost) const {
        if (!func || cost > kTinyInlineCost) return false;
        for (auto &instr : func->body->instrList) {
            if (std::dynamic_pointer_cast<IRCall>(instr) ||
                std::dynamic_pointer_cast<IRPrint>(instr) ||
                std::dynamic_pointer_cast<IRExit>(instr) ||
                std::dynamic_pointer_cast<IRGetint>(instr)) {
                return false;
            }
        }
        return true;
    }

    bool isScalarMemoryType(const std::shared_ptr<IRType> &type) const {
        return std::dynamic_pointer_cast<IRIntType>(type) ||
               std::dynamic_pointer_cast<IRPtrType>(type);
    }

    bool isAggregateLike(const std::shared_ptr<IRType> &type) const {
        return std::dynamic_pointer_cast<IRStructType>(type) ||
               std::dynamic_pointer_cast<IRArrayType>(type);
    }

    void inlineInFunction(const std::shared_ptr<IRFunction> &caller) {
        if (!caller || !caller->body) return;
        int growthBudget = callerGrowthBudget(caller);
        for (int round = 0; round < kMaxInlineRounds; round++) {
            bool changed = false;
            changed |= inlineInBlock(caller->body, growthBudget);
            for (auto &blk : caller->body->blockList) changed |= inlineInBlock(blk, growthBudget);
            if (!changed || growthBudget <= 0) break;
        }
    }

    int callerGrowthBudget(const std::shared_ptr<IRFunction> &caller) const {
        if (!caller || !caller->body) return 0;
        int instrCount = static_cast<int>(caller->body->instrList.size());
        for (auto &blk : caller->body->blockList) {
            if (blk) instrCount += static_cast<int>(blk->instrList.size());
        }
        return std::max(48, std::min(180, 64 + instrCount / 2));
    }

    bool inlineInBlock(const std::shared_ptr<IRBlock> &block, int &growthBudget) {
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

            int growth = inlineGrowth(call->function);
            if (growth > growthBudget && !forceInline(call->function)) {
                newInstrs.push_back(instr);
                continue;
            }

            auto inlined = inlineCall(call);
            if (inlined.empty()) {
                newInstrs.push_back(instr);
                continue;
            }
            for (auto &cloned : inlined) newInstrs.push_back(cloned);
            growthBudget -= std::max(0, growth);
            changed = true;
        }
        block->instrList = std::move(newInstrs);
        return changed;
    }

    int inlineGrowth(const std::shared_ptr<IRFunction> &func) {
        int cost = inlineCost(func);
        if (cost < 0) return 1000000;
        return std::max(0, cost - 1);
    }

    bool forceInline(const std::shared_ptr<IRFunction> &func) {
        if (!func) return false;
        int calls = callCounts.count(func.get()) ? callCounts[func.get()] : 0;
        int cost = inlineCost(func);
        return calls == 1 && cost >= 0 && cost <= kSingleUseInlineCost;
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
            if (auto op = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                auto cloned = cloneAlloca(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRGetptr>(instr)) {
                auto cloned = cloneGetptr(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRLoad>(instr)) {
                auto cloned = cloneLoad(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRStore>(instr)) {
                auto cloned = cloneStore(op, valueMap);
                if (!cloned) return {};
                result.push_back(cloned);
            } else if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
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
            // The synthesized ADD is effectively a mov from returnValue into
            // retVar.  Lower it as a 64-bit add so the upper bits of usize/
            // isize values survive; addw would truncate. For i32, the lower
            // 32 bits are identical and subsequent uses re-sign-extend, so
            // tagging w64 unconditionally is safe.
            assign->w64tag = true;
            assign->utag = true;
            result.push_back(assign);
        }
        return result;
    }

    std::shared_ptr<IRAlloca> cloneAlloca(const std::shared_ptr<IRAlloca> &op,
                                          std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->var || !op->allocatedType || !isScalarMemoryType(op->allocatedType)) {
            return nullptr;
        }
        auto clonedVar = cloneVar(op->var);
        auto cloned = std::make_shared<IRAlloca>(op->allocatedType, clonedVar);
        cloned->w64tag = op->w64tag;
        valueMap[op->var.get()] = clonedVar;
        return cloned;
    }

    std::shared_ptr<IRGetptr> cloneGetptr(const std::shared_ptr<IRGetptr> &op,
                                          std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->base || !op->res) return nullptr;
        auto base = std::dynamic_pointer_cast<IRVar>(mapValue(op->base, valueMap));
        if (!base) return nullptr;
        std::shared_ptr<IRVar> index = nullptr;
        if (op->index) {
            index = std::dynamic_pointer_cast<IRVar>(mapValue(op->index, valueMap));
            if (!index) return nullptr;
        }
        auto clonedResult = cloneVar(op->res);
        auto cloned = std::make_shared<IRGetptr>(op->type, base, clonedResult, op->offset, index);
        valueMap[op->res.get()] = clonedResult;
        return cloned;
    }

    std::shared_ptr<IRLoad> cloneLoad(const std::shared_ptr<IRLoad> &op,
                                      std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->tmp || !op->addressVar) return nullptr;
        auto address = std::dynamic_pointer_cast<IRVar>(mapValue(op->addressVar, valueMap));
        if (!address) return nullptr;
        auto clonedResult = cloneVar(op->tmp);
        auto cloned = std::make_shared<IRLoad>(clonedResult, address, op->type);
        cloned->w64tag = op->w64tag;
        cloned->utag = op->utag;
        valueMap[op->tmp.get()] = clonedResult;
        return cloned;
    }

    std::shared_ptr<IRStore> cloneStore(const std::shared_ptr<IRStore> &op,
                                        std::map<IRVar*, ValuePtr> &valueMap) {
        if (!op || !op->address) return nullptr;
        auto address = std::dynamic_pointer_cast<IRVar>(mapValue(op->address, valueMap));
        if (!address) return nullptr;
        auto cloned = std::make_shared<IRStore>();
        cloned->valueType = op->valueType;
        cloned->address = address;
        cloned->w64tag = op->w64tag;
        if (op->storeLiteral) {
            cloned->storeLiteral = op->storeLiteral;
        } else if (op->storeValue) {
            auto mapped = mapValue(op->storeValue, valueMap);
            if (auto lit = std::dynamic_pointer_cast<IRLiteral>(mapped)) {
                cloned->storeLiteral = lit;
            } else if (auto var = std::dynamic_pointer_cast<IRVar>(mapped)) {
                cloned->storeValue = var;
            } else {
                return nullptr;
            }
        }
        return cloned;
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
        cloned->isW64Stack = var->isW64Stack;
        cloned->isPtrStorage = var->isPtrStorage;
        cloned->isPtrBindingSlot = var->isPtrBindingSlot;
        return cloned;
    }

};

}
