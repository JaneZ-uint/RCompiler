#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <cstdint>
#include <optional>
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
#include "../ir/IRBr.h"
#include "../ir/IRReturn.h"
#include "../ir/IRCall.h"
#include "../ir/IRParam.h"
#include "../ir/IRPrint.h"
#include "../ir/IRExit.h"
#include "../ir/IRStore.h"
#include "../ir/IRLoad.h"
#include "../ir/IRGetptr.h"
#include "../ir/IRGetint.h"
#include "../ir/IRPhi.h"
#include "../ir/IRPHI.h"
#include "../ir/IRSext.h"
#include "../ir/IRZext.h"
#include "../ir/IRTrunc.h"
#include "../ir/IRMem.h"

namespace JaneZ {

class ConstantFold {
public:
    void optimize(std::shared_ptr<IRRoot> root) {
        if (!root) return;
        for (auto &child : root->children) {
            if (auto func = std::dynamic_pointer_cast<IRFunction>(child)) {
                for (auto &nested : func->funcList) optimizeFunc(nested);
                optimizeFunc(func);
            } else if (auto impl = std::dynamic_pointer_cast<IRImpl>(child)) {
                for (auto &func : impl->functions) optimizeFunc(func);
            }
        }
    }

private:
    using ValuePtr = std::shared_ptr<IRValue>;
    using VarPtr = std::shared_ptr<IRVar>;
    using LitPtr = std::shared_ptr<IRLiteral>;

    void optimizeFunc(std::shared_ptr<IRFunction> func) {
        if (!func || !func->body) return;

        bool changed = false;
        std::set<IRNode*> toRemove;

        processBlock(func->body, toRemove, changed);
        for (auto &blk : func->body->blockList) {
            processBlock(blk, toRemove, changed);
        }

        removeInstructions(func, toRemove, changed);
    }

    void processBlock(std::shared_ptr<IRBlock> blk,
                      std::set<IRNode*> &toRemove,
                      bool &changed) {
        if (!blk) return;
        std::map<IRVar*, LitPtr> constMap;
        for (auto &instr : blk->instrList) {
            if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
                replaceValue(op->leftValue, constMap, changed);
                replaceValue(op->rightValue, constMap, changed);
                auto lhs = getLiteral(op->leftValue, constMap);
                auto rhs = getLiteral(op->rightValue, constMap);
                auto folded = foldBinary(op->op, lhs, rhs, op->utag, op->w64tag);
                if (folded && op->result) {
                    constMap[op->result.get()] = *folded;
                    changed = true;
                } else if (op->result) {
                    constMap.erase(op->result.get());
                }
            } else if (auto phi = std::dynamic_pointer_cast<IRPHI>(instr)) {
                auto folded = foldPhi(phi);
                if (folded && phi->result) {
                    constMap[phi->result.get()] = *folded;
                    changed = true;
                } else if (phi->result) {
                    constMap.erase(phi->result.get());
                }
            } else if (auto phi = std::dynamic_pointer_cast<IRPhi>(instr)) {
                if (phi->result) constMap.erase(phi->result.get());
            } else if (auto cast = std::dynamic_pointer_cast<IRSext>(instr)) {
                foldCast(cast->value, cast->result, constMap, changed);
            } else if (auto cast = std::dynamic_pointer_cast<IRZext>(instr)) {
                foldCast(cast->value, cast->result, constMap, changed);
            } else if (auto cast = std::dynamic_pointer_cast<IRTrunc>(instr)) {
                foldCast(cast->value, cast->result, constMap, changed);
            } else if (auto ret = std::dynamic_pointer_cast<IRReturn>(instr)) {
                rewriteReturn(ret, constMap, changed);
            } else if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
                rewriteStore(store, constMap, changed);
            } else if (auto print = std::dynamic_pointer_cast<IRPrint>(instr)) {
                replaceValue(print->printVar, constMap, changed);
            } else if (auto exit = std::dynamic_pointer_cast<IRExit>(instr)) {
                replaceValue(exit->exitCode, constMap, changed);
            } else if (auto br = std::dynamic_pointer_cast<IRBr>(instr)) {
                simplifyBranch(br, constMap, changed);
            } else if (auto call = std::dynamic_pointer_cast<IRCall>(instr)) {
                rewriteCall(call, constMap, changed);
                clearDefinedVar(instr, constMap);
            } else {
                clearDefinedVar(instr, constMap);
            }
        }
    }

    LitPtr getLiteral(const ValuePtr &value, const std::map<IRVar*, LitPtr> &constMap) {
        if (!value) return nullptr;
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(value)) return lit;
        if (auto var = std::dynamic_pointer_cast<IRVar>(value)) {
            auto it = constMap.find(var.get());
            if (it != constMap.end()) return it->second;
        }
        return nullptr;
    }

    long long literalValue(const LitPtr &lit) {
        if (!lit) return 0;
        if (lit->literalType == BOOL_LITERAL) return lit->boolValue || lit->intValue;
        return lit->intValue;
    }

    LitPtr makeInt(long long value) {
        return std::make_shared<IRLiteral>(INT_LITERAL, value, value != 0);
    }

    long long toI32(long long value) {
        value &= 0xffffffffLL;
        if (value >= 0x80000000LL) value -= 0x100000000LL;
        return value;
    }

    unsigned long long toU32(long long value) {
        return static_cast<unsigned long long>(value) & 0xffffffffULL;
    }

    LitPtr makeI32(long long value) {
        return makeInt(toI32(value));
    }

    LitPtr makeI64(uint64_t value) {
        return makeInt(static_cast<long long>(value));
    }

    LitPtr makeBool(bool value) {
        return std::make_shared<IRLiteral>(BOOL_LITERAL, value ? 1 : 0, value);
    }

    bool sameLiteral(const LitPtr &a, const LitPtr &b) {
        if (!a || !b) return false;
        return a->literalType == b->literalType && literalValue(a) == literalValue(b);
    }

    std::optional<LitPtr> foldBinary(IROp op, const LitPtr &lhs, const LitPtr &rhs, bool unsignedTag, bool wide64 = false) {
        if (!lhs || !rhs) return std::nullopt;
        long long l = literalValue(lhs);
        long long r = literalValue(rhs);

        if (wide64) {
            return foldBinary64(op, l, r, unsignedTag);
        }

        long long li32 = toI32(l);
        long long ri32 = toI32(r);
        unsigned long long lu32 = toU32(l);
        unsigned long long ru32 = toU32(r);

        switch (op) {
            case ADD: return makeI32(unsignedTag ? lu32 + ru32 : li32 + ri32);
            case SUB: return makeI32(unsignedTag ? lu32 - ru32 : li32 - ri32);
            case MUL: return makeI32(unsignedTag ? lu32 * ru32 : li32 * ri32);
            case DIV:
                if (unsignedTag) {
                    if (ru32 == 0) return std::nullopt;
                    return makeI32(lu32 / ru32);
                } else {
                    if (ri32 == 0) return std::nullopt;
                    return makeI32(li32 / ri32);
                }
            case MOD:
                if (unsignedTag) {
                    if (ru32 == 0) return std::nullopt;
                    return makeI32(lu32 % ru32);
                } else {
                    if (ri32 == 0) return std::nullopt;
                    return makeI32(li32 % ri32);
                }
            case EQ: return makeBool(unsignedTag ? lu32 == ru32 : li32 == ri32);
            case NEQ: return makeBool(unsignedTag ? lu32 != ru32 : li32 != ri32);
            case LT: return makeBool(unsignedTag ? lu32 < ru32 : li32 < ri32);
            case GT: return makeBool(unsignedTag ? lu32 > ru32 : li32 > ri32);
            case LEQ: return makeBool(unsignedTag ? lu32 <= ru32 : li32 <= ri32);
            case GEQ: return makeBool(unsignedTag ? lu32 >= ru32 : li32 >= ri32);
            case LOGICALAND: return makeBool((li32 != 0) && (ri32 != 0));
            case LOGICALOR: return makeBool((li32 != 0) || (ri32 != 0));
            case XOROP: return makeI32(li32 ^ ri32);
            case OROP: return makeI32(li32 | ri32);
            case ANDOP: return makeI32(li32 & ri32);
            case LEFTSHIFTOP:
                if (ri32 < 0 || ri32 >= 32) return std::nullopt;
                return makeI32(lu32 << ri32);
            case RIGHTSHIFTOP:
                if (ri32 < 0 || ri32 >= 32) return std::nullopt;
                return makeI32(unsignedTag ? lu32 >> ri32 : li32 >> ri32);
            default:
                return std::nullopt;
        }
    }

    std::optional<LitPtr> foldBinary64(IROp op, long long l, long long r, bool unsignedTag) {
        uint64_t lu64 = static_cast<uint64_t>(l);
        uint64_t ru64 = static_cast<uint64_t>(r);
        int64_t li64 = static_cast<int64_t>(lu64);
        int64_t ri64 = static_cast<int64_t>(ru64);

        switch (op) {
            case ADD: return makeI64(lu64 + ru64);
            case SUB: return makeI64(lu64 - ru64);
            case MUL: return makeI64(lu64 * ru64);
            case DIV:
                if (unsignedTag) {
                    if (ru64 == 0) return std::nullopt;
                    return makeI64(lu64 / ru64);
                } else {
                    if (ri64 == 0) return std::nullopt;
                    if (li64 == INT64_MIN && ri64 == -1) return std::nullopt;
                    return makeI64(static_cast<uint64_t>(li64 / ri64));
                }
            case MOD:
                if (unsignedTag) {
                    if (ru64 == 0) return std::nullopt;
                    return makeI64(lu64 % ru64);
                } else {
                    if (ri64 == 0) return std::nullopt;
                    if (li64 == INT64_MIN && ri64 == -1) return std::nullopt;
                    return makeI64(static_cast<uint64_t>(li64 % ri64));
                }
            case EQ: return makeBool(unsignedTag ? lu64 == ru64 : li64 == ri64);
            case NEQ: return makeBool(unsignedTag ? lu64 != ru64 : li64 != ri64);
            case LT: return makeBool(unsignedTag ? lu64 < ru64 : li64 < ri64);
            case GT: return makeBool(unsignedTag ? lu64 > ru64 : li64 > ri64);
            case LEQ: return makeBool(unsignedTag ? lu64 <= ru64 : li64 <= ri64);
            case GEQ: return makeBool(unsignedTag ? lu64 >= ru64 : li64 >= ri64);
            case LOGICALAND: return makeBool((lu64 != 0) && (ru64 != 0));
            case LOGICALOR: return makeBool((lu64 != 0) || (ru64 != 0));
            case XOROP: return makeI64(lu64 ^ ru64);
            case OROP: return makeI64(lu64 | ru64);
            case ANDOP: return makeI64(lu64 & ru64);
            case LEFTSHIFTOP:
                if (ri64 < 0 || ri64 >= 64) return std::nullopt;
                return makeI64(lu64 << static_cast<unsigned>(ri64));
            case RIGHTSHIFTOP:
                if (ri64 < 0 || ri64 >= 64) return std::nullopt;
                if (unsignedTag) return makeI64(lu64 >> static_cast<unsigned>(ri64));
                return makeI64(static_cast<uint64_t>(li64 >> static_cast<unsigned>(ri64)));
            default:
                return std::nullopt;
        }
    }

    std::optional<LitPtr> foldPhi(const std::shared_ptr<IRPHI> &phi) {
        LitPtr first = nullptr;
        bool hasValue = false;

        auto consider = [&](const ValuePtr &value) -> bool {
            auto lit = std::dynamic_pointer_cast<IRLiteral>(value);
            if (!lit) return false;
            if (!hasValue) {
                first = lit;
                hasValue = true;
                return true;
            }
            return sameLiteral(first, lit);
        };

        if (!phi->entries.empty()) {
            for (auto &entry : phi->entries) {
                if (!consider(entry.first)) return std::nullopt;
            }
        } else {
            if (phi->firstState && !consider(phi->firstState)) return std::nullopt;
            if (phi->secondState && !consider(phi->secondState)) return std::nullopt;
        }

        if (!hasValue) return std::nullopt;
        return first;
    }

    void foldCast(const VarPtr &value, const VarPtr &result,
                  std::map<IRVar*, LitPtr> &constMap,
                  bool &changed) {
        if (!result) return;
        auto lit = getLiteral(value, constMap);
        if (!lit) {
            constMap.erase(result.get());
            return;
        }
        constMap[result.get()] = lit;
        changed = true;
    }

    void clearDefinedVar(const std::shared_ptr<IRNode> &instr,
                         std::map<IRVar*, LitPtr> &constMap) {
        auto eraseVar = [&](const VarPtr &var) {
            if (var) constMap.erase(var.get());
        };

        if (auto p = std::dynamic_pointer_cast<IRLoad>(instr)) eraseVar(p->tmp);
        else if (auto p = std::dynamic_pointer_cast<IRGetptr>(instr)) eraseVar(p->res);
        else if (auto p = std::dynamic_pointer_cast<IRCall>(instr)) eraseVar(p->retVar);
        else if (auto p = std::dynamic_pointer_cast<IRGetint>(instr)) eraseVar(p->result);
    }

    void replaceValue(ValuePtr &val, const std::map<IRVar*, LitPtr> &constMap, bool &changed) {
        if (auto var = std::dynamic_pointer_cast<IRVar>(val)) {
            auto it = constMap.find(var.get());
            if (it != constMap.end()) {
                val = it->second;
                changed = true;
            }
        }
    }

    void rewriteStore(const std::shared_ptr<IRStore> &store,
                      const std::map<IRVar*, LitPtr> &constMap,
                      bool &changed) {
        if (!store || !store->storeValue) return;
        auto it = constMap.find(store->storeValue.get());
        if (it == constMap.end()) return;
        store->storeLiteral = it->second;
        store->storeValue = nullptr;
        changed = true;
    }

    void rewriteReturn(const std::shared_ptr<IRReturn> &ret,
                       const std::map<IRVar*, LitPtr> &constMap,
                       bool &changed) {
        if (!ret || !ret->returnValue) return;
        auto it = constMap.find(ret->returnValue.get());
        if (it == constMap.end()) return;
        ret->returnLiteral = it->second;
        ret->returnValue = nullptr;
        changed = true;
    }

    void rewriteCall(const std::shared_ptr<IRCall> &call,
                     const std::map<IRVar*, LitPtr> &constMap,
                     bool &changed) {
        if (!call || !call->pList) return;
        for (auto &param : call->pList->paramList) {
            auto val = std::dynamic_pointer_cast<IRValue>(param);
            if (!val) continue;
            replaceValue(val, constMap, changed);
            param = std::dynamic_pointer_cast<IRNode>(val);
        }
    }

    void simplifyBranch(const std::shared_ptr<IRBr> &br,
                        const std::map<IRVar*, LitPtr> &constMap,
                        bool &changed) {
        if (!br || !br->condition || !br->trueLabel || !br->falseLabel) return;
        auto it = constMap.find(br->condition.get());
        if (it == constMap.end()) return;

        auto chosen = literalValue(it->second) != 0 ? br->trueLabel : br->falseLabel;
        br->condition = nullptr;
        br->trueLabel = chosen;
        br->falseLabel = nullptr;
        changed = true;
    }

    void removeInstructions(std::shared_ptr<IRFunction> func,
                            const std::set<IRNode*> &toRemove,
                            bool &changed) {
        if (toRemove.empty()) return;
        auto removeFrom = [&](std::vector<std::shared_ptr<IRNode>> &instrList) {
            auto oldSize = instrList.size();
            instrList.erase(
                std::remove_if(instrList.begin(), instrList.end(),
                    [&](const std::shared_ptr<IRNode> &instr) {
                        return toRemove.count(instr.get()) > 0;
                    }),
                instrList.end());
            if (instrList.size() != oldSize) changed = true;
        };

        removeFrom(func->body->instrList);
        for (auto &blk : func->body->blockList) removeFrom(blk->instrList);
    }

};

}
