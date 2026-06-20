#pragma once

#include <algorithm>
#include <cstdint>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <utility>
#include <vector>
#include "../ir/IRBinaryop.h"
#include "../ir/IRAlloca.h"
#include "../ir/IRBlock.h"
#include "../ir/IRBr.h"
#include "../ir/IRCall.h"
#include "../ir/IRExit.h"
#include "../ir/IRFunction.h"
#include "../ir/IRGetint.h"
#include "../ir/IRGetptr.h"
#include "../ir/IRImpl.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRLoad.h"
#include "../ir/IRPHI.h"
#include "../ir/IRPhi.h"
#include "../ir/IRPrint.h"
#include "../ir/IRReturn.h"
#include "../ir/IRRoot.h"
#include "../ir/IRStore.h"
#include "../ir/IRType.h"
#include "../ir/IRSext.h"
#include "../ir/IRTrunc.h"
#include "../ir/IRValue.h"
#include "../ir/IRVar.h"
#include "../ir/IRZext.h"
#include "IRUtil.h"

namespace JaneZ {

class SCCP {
public:
    void optimize(const std::shared_ptr<IRRoot> &root) {
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
    enum class LatticeKind {
        Unknown,
        Constant,
        Overdefined,
    };

    struct LatticeValue {
        LatticeKind kind = LatticeKind::Unknown;
        std::shared_ptr<IRLiteral> literal;
    };

    using ValuePtr = std::shared_ptr<IRValue>;
    using LitPtr = std::shared_ptr<IRLiteral>;
    using Edge = std::pair<IRBlock*, IRBlock*>;

    std::vector<std::shared_ptr<IRBlock>> blocks;
    std::map<IRBlock*, std::vector<IRBlock*>> succs;
    std::set<IRBlock*> executableBlocks;
    std::set<Edge> executableEdges;
    std::map<IRVar*, LatticeValue> values;

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        initializeCFG(func);
        initializeUnknownInputs(func);
        solve();
        rewriteConstants(func);
    }

    void initializeCFG(const std::shared_ptr<IRFunction> &func) {
        blocks.clear();
        succs.clear();
        executableBlocks.clear();
        executableEdges.clear();
        values.clear();

        blocks.push_back(func->body);
        for (auto &blk : func->body->blockList) {
            if (blk) blocks.push_back(blk);
        }
        for (size_t i = 0; i < blocks.size(); i++) {
            succs[blocks[i].get()] = {};
        }

        for (size_t i = 0; i < blocks.size(); i++) {
            auto blk = blocks[i];
            if (!blk) continue;
            std::vector<IRBlock*> out;
            if (!blk->instrList.empty()) {
                auto last = blk->instrList.back();
                if (auto br = std::dynamic_pointer_cast<IRBr>(last)) {
                    addUnique(out, br->trueLabel.get());
                    if (br->falseLabel && br->falseLabel != br->trueLabel) {
                        addUnique(out, br->falseLabel.get());
                    }
                } else if (!std::dynamic_pointer_cast<IRReturn>(last) &&
                           !std::dynamic_pointer_cast<IRExit>(last)) {
                    if (i + 1 < blocks.size()) addUnique(out, blocks[i + 1].get());
                }
            } else if (i + 1 < blocks.size()) {
                addUnique(out, blocks[i + 1].get());
            }
            succs[blk.get()] = out;
        }
    }

    void initializeUnknownInputs(const std::shared_ptr<IRFunction> &func) {
        if (func->paramList) {
            for (auto &param : func->paramList->paramList) {
                if (auto var = std::dynamic_pointer_cast<IRVar>(param)) {
                    values[var.get()] = overdefined();
                }
            }
        }
    }

    void addUnique(std::vector<IRBlock*> &vec, IRBlock *blk) {
        if (!blk) return;
        if (std::find(vec.begin(), vec.end(), blk) == vec.end()) vec.push_back(blk);
    }

    void solve() {
        if (blocks.empty() || !blocks[0]) return;
        executableBlocks.insert(blocks[0].get());

        bool changed = true;
        while (changed) {
            changed = false;
            for (auto &blk : blocks) {
                if (!blk || !executableBlocks.count(blk.get())) continue;
                changed |= visitBlock(blk);
            }
        }
    }

    bool visitBlock(const std::shared_ptr<IRBlock> &blk) {
        bool changed = false;
        for (auto &instr : blk->instrList) {
            if (auto phi = std::dynamic_pointer_cast<IRPHI>(instr)) {
                changed |= visitPHI(phi, blk.get());
            } else if (auto phi = std::dynamic_pointer_cast<IRPhi>(instr)) {
                changed |= setResult(phi->result, overdefined());
            } else if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
                changed |= setResult(op->result, evalBinary(op));
            } else if (auto cast = std::dynamic_pointer_cast<IRSext>(instr)) {
                changed |= setResult(cast->result, evalCast(cast->value, cast->originalType, cast->targetType, true));
            } else if (auto cast = std::dynamic_pointer_cast<IRZext>(instr)) {
                changed |= setResult(cast->result, evalCast(cast->value, cast->originalType, cast->targetType, false));
            } else if (auto cast = std::dynamic_pointer_cast<IRTrunc>(instr)) {
                changed |= setResult(cast->result, evalCast(cast->value, cast->originalType, cast->targetType, false));
            } else if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                changed |= setResult(alloca->var, overdefined());
            } else if (auto load = std::dynamic_pointer_cast<IRLoad>(instr)) {
                changed |= setResult(load->tmp, overdefined());
            } else if (auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr)) {
                changed |= setResult(getptr->res, overdefined());
            } else if (auto call = std::dynamic_pointer_cast<IRCall>(instr)) {
                changed |= setResult(call->retVar, overdefined());
            } else if (auto getint = std::dynamic_pointer_cast<IRGetint>(instr)) {
                changed |= setResult(getint->result, overdefined());
            } else if (auto br = std::dynamic_pointer_cast<IRBr>(instr)) {
                changed |= visitBranch(br, blk.get());
            }
        }
        if (!endsWithTerminator(blk)) {
            for (auto *succ : succs[blk.get()]) changed |= markEdge(blk.get(), succ);
        }
        return changed;
    }

    bool endsWithTerminator(const std::shared_ptr<IRBlock> &blk) const {
        if (!blk || blk->instrList.empty()) return false;
        auto last = blk->instrList.back();
        return std::dynamic_pointer_cast<IRBr>(last) ||
               std::dynamic_pointer_cast<IRReturn>(last) ||
               std::dynamic_pointer_cast<IRExit>(last);
    }

    bool visitPHI(const std::shared_ptr<IRPHI> &phi, IRBlock *block) {
        if (!phi || !phi->result) return false;
        LatticeValue merged;
        bool hasExecutableInput = false;

        auto consider = [&](const ValuePtr &value, IRBlock *pred) {
            if (!pred || !executableEdges.count({pred, block})) return;
            hasExecutableInput = true;
            merged = merge(merged, valueState(value));
        };

        if (!phi->entries.empty()) {
            for (auto &entry : phi->entries) consider(entry.first, entry.second.get());
        } else {
            consider(phi->firstState, phi->firstBlock.get());
            consider(phi->secondState, phi->secondBlock.get());
        }

        if (!hasExecutableInput && executableBlocks.count(block)) return false;
        return setResult(phi->result, merged);
    }

    bool visitBranch(const std::shared_ptr<IRBr> &br, IRBlock *from) {
        if (!br || !from) return false;
        bool changed = false;
        if (!br->condition || !br->falseLabel) {
            changed |= markEdge(from, br->trueLabel.get());
            return changed;
        }

        auto cond = valueState(br->condition);
        if (cond.kind == LatticeKind::Constant && cond.literal) {
            changed |= markEdge(from, literalIsTrue(cond.literal) ? br->trueLabel.get() : br->falseLabel.get());
        } else {
            changed |= markEdge(from, br->trueLabel.get());
            changed |= markEdge(from, br->falseLabel.get());
        }
        return changed;
    }

    bool markEdge(IRBlock *from, IRBlock *to) {
        if (!from || !to) return false;
        bool changed = false;
        if (executableEdges.insert({from, to}).second) changed = true;
        if (executableBlocks.insert(to).second) changed = true;
        return changed;
    }

    LatticeValue unknown() const {
        return {};
    }

    LatticeValue overdefined() const {
        LatticeValue value;
        value.kind = LatticeKind::Overdefined;
        return value;
    }

    LatticeValue constant(const LitPtr &literal) const {
        if (!literal) return overdefined();
        LatticeValue value;
        value.kind = LatticeKind::Constant;
        value.literal = literal;
        return value;
    }

    LatticeValue valueState(const ValuePtr &value) const {
        if (!value) return overdefined();
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(value)) return constant(lit);
        if (auto var = std::dynamic_pointer_cast<IRVar>(value)) {
            auto it = values.find(var.get());
            if (it != values.end()) return it->second;
            return unknown();
        }
        return overdefined();
    }

    LatticeValue merge(const LatticeValue &lhs, const LatticeValue &rhs) const {
        if (lhs.kind == LatticeKind::Unknown) return rhs;
        if (rhs.kind == LatticeKind::Unknown) return lhs;
        if (lhs.kind == LatticeKind::Overdefined || rhs.kind == LatticeKind::Overdefined) {
            return overdefined();
        }
        if (sameLiteral(lhs.literal, rhs.literal)) return lhs;
        return overdefined();
    }

    bool setResult(const std::shared_ptr<IRVar> &var, const LatticeValue &next) {
        if (!var) return false;
        auto old = valueState(var);
        auto joined = merge(old, next);
        if (sameState(old, joined)) return false;
        values[var.get()] = joined;
        return true;
    }

    bool sameState(const LatticeValue &a, const LatticeValue &b) const {
        if (a.kind != b.kind) return false;
        if (a.kind != LatticeKind::Constant) return true;
        return sameLiteral(a.literal, b.literal);
    }

    LatticeValue evalBinary(const std::shared_ptr<IRBinaryop> &op) {
        if (!op || !op->result) return overdefined();
        auto lhs = valueState(op->leftValue);
        auto rhs = valueState(op->rightValue);
        if (lhs.kind == LatticeKind::Overdefined || rhs.kind == LatticeKind::Overdefined) {
            return overdefined();
        }
        if (lhs.kind == LatticeKind::Unknown || rhs.kind == LatticeKind::Unknown) {
            return unknown();
        }
        auto folded = foldBinary(op->op, lhs.literal, rhs.literal, op->utag, op->w64tag);
        return folded ? constant(*folded) : overdefined();
    }

    LatticeValue evalCast(const std::shared_ptr<IRVar> &value,
                          const std::shared_ptr<IRType> &originalType,
                          const std::shared_ptr<IRType> &targetType,
                          bool signExtend) {
        auto state = valueState(value);
        if (state.kind != LatticeKind::Constant) return state;
        return constant(normalizeCastLiteral(state.literal, originalType, targetType, signExtend));
    }

    std::optional<LitPtr> foldBinary(IROp op, const LitPtr &lhs, const LitPtr &rhs, bool unsignedTag, bool wide64) {
        if (!lhs || !rhs) return std::nullopt;
        long long l = literalValue(lhs);
        long long r = literalValue(rhs);

        if (wide64) return foldBinary64(op, l, r, unsignedTag);

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
                }
                if (ri32 == 0) return std::nullopt;
                return makeI32(li32 / ri32);
            case MOD:
                if (unsignedTag) {
                    if (ru32 == 0) return std::nullopt;
                    return makeI32(lu32 % ru32);
                }
                if (ri32 == 0) return std::nullopt;
                return makeI32(li32 % ri32);
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
                }
                if (ri64 == 0) return std::nullopt;
                if (li64 == std::numeric_limits<int64_t>::min() && ri64 == -1) return std::nullopt;
                return makeI64(static_cast<uint64_t>(li64 / ri64));
            case MOD:
                if (unsignedTag) {
                    if (ru64 == 0) return std::nullopt;
                    return makeI64(lu64 % ru64);
                }
                if (ri64 == 0) return std::nullopt;
                if (li64 == std::numeric_limits<int64_t>::min() && ri64 == -1) return std::nullopt;
                return makeI64(static_cast<uint64_t>(li64 % ri64));
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

    LitPtr normalizeCastLiteral(const LitPtr &lit,
                                const std::shared_ptr<IRType> &originalType,
                                const std::shared_ptr<IRType> &targetType,
                                bool signExtend) {
        if (!lit) return lit;
        auto intType = std::dynamic_pointer_cast<IRIntType>(targetType);
        if (!intType) return lit;

        long long value = literalValue(lit);
        if (intType->bitWidth == 64) {
            if (auto originalInt = std::dynamic_pointer_cast<IRIntType>(originalType)) {
                if (originalInt->bitWidth == 32) {
                    value = signExtend ? toI32(value) : static_cast<long long>(toU32(value));
                }
            }
            return makeI64(static_cast<uint64_t>(value));
        }

        if (intType->bitWidth == 32) {
            long long low = static_cast<long long>(static_cast<unsigned long long>(value) & 0xffffffffULL);
            if (!intType->isUnsigned && (low & 0x80000000LL)) low -= 0x100000000LL;
            if (lit->literalType == BOOL_LITERAL) return makeBool(low != 0);
            return makeInt(low);
        }

        if (intType->bitWidth == 1 || intType->size == 1) {
            return makeBool(value != 0);
        }
        return lit;
    }

    void rewriteConstants(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        std::map<IRVar*, ValuePtr> replaceMap;
        for (auto &entry : values) {
            if (entry.second.kind == LatticeKind::Constant && entry.second.literal) {
                replaceMap[entry.first] = entry.second.literal;
            }
        }
        if (replaceMap.empty()) return;

        for (auto &blk : blocks) {
            if (!blk || !executableBlocks.count(blk.get())) continue;
            for (auto &instr : blk->instrList) {
                rewriteInstruction(instr, replaceMap);
            }
        }
    }

    void rewriteInstruction(const std::shared_ptr<IRNode> &instr,
                            const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!instr) return;
        if (auto br = std::dynamic_pointer_cast<IRBr>(instr)) {
            rewriteBranch(br, replaceMap);
            return;
        }
        if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
            rewriteStore(store, replaceMap);
            return;
        }
        if (auto ret = std::dynamic_pointer_cast<IRReturn>(instr)) {
            rewriteReturn(ret, replaceMap);
            return;
        }
        IRUtil::replaceUses(instr, replaceMap);
    }

    void rewriteBranch(const std::shared_ptr<IRBr> &br,
                       const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!br || !br->condition || !br->trueLabel || !br->falseLabel) return;
        auto it = replaceMap.find(br->condition.get());
        if (it == replaceMap.end()) return;
        auto lit = std::dynamic_pointer_cast<IRLiteral>(it->second);
        if (!lit) return;
        br->trueLabel = literalIsTrue(lit) ? br->trueLabel : br->falseLabel;
        br->condition = nullptr;
        br->falseLabel = nullptr;
    }

    void rewriteStore(const std::shared_ptr<IRStore> &store,
                      const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!store) return;
        IRUtil::replaceVar(store->address, replaceMap);
        if (!store->storeValue) return;
        auto it = replaceMap.find(store->storeValue.get());
        if (it == replaceMap.end()) return;
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(it->second)) {
            store->storeLiteral = lit;
            store->storeValue = nullptr;
        } else if (auto var = std::dynamic_pointer_cast<IRVar>(it->second)) {
            store->storeValue = var;
        }
    }

    void rewriteReturn(const std::shared_ptr<IRReturn> &ret,
                       const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!ret || !ret->returnValue) return;
        auto it = replaceMap.find(ret->returnValue.get());
        if (it == replaceMap.end()) return;
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(it->second)) {
            ret->returnLiteral = lit;
            ret->returnValue = nullptr;
        } else if (auto var = std::dynamic_pointer_cast<IRVar>(it->second)) {
            ret->returnValue = var;
        }
    }

    bool literalIsTrue(const LitPtr &lit) const {
        return lit && (lit->literalType == BOOL_LITERAL ? (lit->boolValue || lit->intValue != 0) : lit->intValue != 0);
    }

    long long literalValue(const LitPtr &lit) const {
        if (!lit) return 0;
        if (lit->literalType == BOOL_LITERAL) return lit->boolValue || lit->intValue;
        return lit->intValue;
    }

    bool sameLiteral(const LitPtr &a, const LitPtr &b) const {
        if (!a || !b) return false;
        return a->literalType == b->literalType && literalValue(a) == literalValue(b);
    }

    LitPtr makeInt(long long value) const {
        return std::make_shared<IRLiteral>(INT_LITERAL, value, value != 0);
    }

    LitPtr makeBool(bool value) const {
        return std::make_shared<IRLiteral>(BOOL_LITERAL, value ? 1 : 0, value);
    }

    LitPtr makeI32(long long value) const {
        return makeInt(toI32(value));
    }

    LitPtr makeI64(uint64_t value) const {
        return makeInt(static_cast<long long>(value));
    }

    long long toI32(long long value) const {
        value &= 0xffffffffLL;
        if (value >= 0x80000000LL) value -= 0x100000000LL;
        return value;
    }

    unsigned long long toU32(long long value) const {
        return static_cast<unsigned long long>(value) & 0xffffffffULL;
    }
};

} // namespace JaneZ
