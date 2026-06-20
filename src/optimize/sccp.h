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
    using FactMap = std::map<IRVar*, LatticeValue>;

    struct BranchFacts {
        FactMap trueFacts;
        FactMap falseFacts;
    };

    std::vector<std::shared_ptr<IRBlock>> blocks;
    std::map<IRBlock*, std::vector<IRBlock*>> succs;
    std::set<IRBlock*> executableBlocks;
    std::set<Edge> executableEdges;
    std::map<Edge, FactMap> edgeFacts;
    std::map<IRVar*, BranchFacts> branchFacts;
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
        edgeFacts.clear();
        branchFacts.clear();
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
                changed |= visitLegacyPhi(phi, blk.get());
            } else if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
                changed |= setResult(op->result, evalBinary(op, blk.get()));
            } else if (auto cast = std::dynamic_pointer_cast<IRSext>(instr)) {
                changed |= setResult(cast->result, evalCast(cast->value, cast->originalType, cast->targetType, true, blk.get()));
            } else if (auto cast = std::dynamic_pointer_cast<IRZext>(instr)) {
                changed |= setResult(cast->result, evalCast(cast->value, cast->originalType, cast->targetType, false, blk.get()));
            } else if (auto cast = std::dynamic_pointer_cast<IRTrunc>(instr)) {
                changed |= setResult(cast->result, evalCast(cast->value, cast->originalType, cast->targetType, false, blk.get()));
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
            merged = merge(merged, valueStateOnEdge(value, pred, block));
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

    bool visitLegacyPhi(const std::shared_ptr<IRPhi> &phi, IRBlock *block) {
        if (!phi || !phi->result) return false;
        LatticeValue merged;
        bool hasExecutableInput = false;

        auto consider = [&](LatticeValue state) {
            // Legacy IRPhi is only used for short-circuit bool lowering. Treat
            // not-yet-known executable inputs conservatively to avoid folding
            // through pending phi copies.
            if (state.kind == LatticeKind::Unknown) state = overdefined();
            merged = hasExecutableInput ? merge(merged, state) : state;
            hasExecutableInput = true;
        };

        if (phi->firstBlock && executableEdges.count({phi->firstBlock.get(), block})) {
            consider(constant(std::make_shared<IRLiteral>(BOOL_LITERAL,
                                                          phi->firstState ? 1 : 0,
                                                          phi->firstState)));
        }
        if (phi->secondBlock && executableEdges.count({phi->secondBlock.get(), block})) {
            consider(valueStateOnEdge(phi->secondState, phi->secondBlock.get(), block));
        }

        if (!hasExecutableInput) return false;
        return setResult(phi->result, merged);
    }

    bool visitBranch(const std::shared_ptr<IRBr> &br, IRBlock *from) {
        if (!br || !from) return false;
        bool changed = false;
        if (!br->condition || !br->falseLabel) {
            changed |= markEdge(from, br->trueLabel.get());
            return changed;
        }

        auto trueFacts = factsForBranch(br->condition, true);
        auto falseFacts = factsForBranch(br->condition, false);
        auto cond = valueStateInBlock(br->condition, from);
        if (cond.kind == LatticeKind::Constant && cond.literal) {
            auto *target = literalIsTrue(cond.literal) ? br->trueLabel.get() : br->falseLabel.get();
            changed |= markEdge(from, target, literalIsTrue(cond.literal) ? trueFacts : falseFacts);
        } else {
            changed |= markEdge(from, br->trueLabel.get(), trueFacts);
            changed |= markEdge(from, br->falseLabel.get(), falseFacts);
        }
        return changed;
    }

    bool markEdge(IRBlock *from, IRBlock *to, const std::shared_ptr<IRVar> &factVar = nullptr, const LitPtr &fact = nullptr) {
        FactMap facts;
        if (factVar && fact) addLiteralFact(facts, factVar.get(), fact);
        return markEdge(from, to, facts);
    }

    bool markEdge(IRBlock *from, IRBlock *to, const FactMap &newFacts) {
        if (!from || !to) return false;
        bool changed = false;
        Edge edge{from, to};
        if (executableEdges.insert(edge).second) changed = true;
        if (!newFacts.empty()) {
            auto &facts = edgeFacts[edge];
            for (auto &entry : newFacts) {
                auto it = facts.find(entry.first);
                if (it == facts.end()) {
                    facts[entry.first] = entry.second;
                    changed = true;
                } else {
                    auto merged = merge(it->second, entry.second);
                    if (!sameState(it->second, merged)) {
                        it->second = merged;
                        changed = true;
                    }
                }
            }
        }
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

    LatticeValue valueStateInBlock(const ValuePtr &value, IRBlock *block) const {
        if (!value) return overdefined();
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(value)) return constant(lit);
        auto var = std::dynamic_pointer_cast<IRVar>(value);
        if (!var) return overdefined();

        if (auto fact = singlePredFact(var.get(), block)) return *fact;
        return valueState(value);
    }

    LatticeValue valueStateOnEdge(const ValuePtr &value, IRBlock *from, IRBlock *to) const {
        if (!value) return overdefined();
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(value)) return constant(lit);
        auto var = std::dynamic_pointer_cast<IRVar>(value);
        if (!var) return overdefined();

        auto edgeIt = edgeFacts.find({from, to});
        if (edgeIt != edgeFacts.end()) {
            auto factIt = edgeIt->second.find(var.get());
            if (factIt != edgeIt->second.end()) return factIt->second;
        }
        return valueState(value);
    }

    std::optional<LatticeValue> singlePredFact(IRVar *var, IRBlock *block) const {
        if (!var || !block) return std::nullopt;
        auto *onlyPred = singleExecutablePred(block);
        if (!onlyPred) return std::nullopt;

        auto edgeIt = edgeFacts.find({onlyPred, block});
        if (edgeIt == edgeFacts.end()) return std::nullopt;
        auto factIt = edgeIt->second.find(var);
        if (factIt == edgeIt->second.end()) return std::nullopt;
        return factIt->second;
    }

    IRBlock *singleExecutablePred(IRBlock *block) const {
        if (!block) return nullptr;
        IRBlock *onlyPred = nullptr;
        int count = 0;
        for (auto &edge : executableEdges) {
            if (edge.second != block) continue;
            onlyPred = edge.first;
            count++;
            if (count > 1) return nullptr;
        }
        return count == 1 ? onlyPred : nullptr;
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

    LatticeValue evalBinary(const std::shared_ptr<IRBinaryop> &op, IRBlock *block) {
        if (!op || !op->result) return overdefined();
        auto lhs = valueStateInBlock(op->leftValue, block);
        auto rhs = valueStateInBlock(op->rightValue, block);
        recordComparisonFacts(op);
        if (auto simplified = simplifyPartialBinary(op, lhs, rhs)) {
            return constant(*simplified);
        }
        if (lhs.kind == LatticeKind::Overdefined || rhs.kind == LatticeKind::Overdefined) {
            return overdefined();
        }
        if (lhs.kind == LatticeKind::Unknown || rhs.kind == LatticeKind::Unknown) {
            return unknown();
        }
        auto folded = foldBinary(op->op, lhs.literal, rhs.literal, op->utag, op->w64tag);
        return folded ? constant(*folded) : overdefined();
    }

    void recordComparisonFacts(const std::shared_ptr<IRBinaryop> &op) {
        if (!op || !op->result || (op->op != EQ && op->op != NEQ)) return;

        BranchFacts facts;
        recordComparisonFact(op->op, op->leftValue, op->rightValue, facts);
        recordComparisonFact(op->op, op->rightValue, op->leftValue, facts);
        if (!facts.trueFacts.empty() || !facts.falseFacts.empty()) {
            branchFacts[op->result.get()] = facts;
        }
    }

    void recordComparisonFact(IROp op,
                              const ValuePtr &maybeVar,
                              const ValuePtr &maybeLiteral,
                              BranchFacts &facts) {
        auto var = std::dynamic_pointer_cast<IRVar>(maybeVar);
        auto lit = std::dynamic_pointer_cast<IRLiteral>(maybeLiteral);
        if (!isIntegerVar(var) || !isIntegerLiteral(lit)) return;

        auto normalized = normalizeFactLiteral(var, lit);
        if (op == EQ) {
            addLiteralFact(facts.trueFacts, var.get(), normalized);
            if (auto opposite = boolOppositeFact(var, normalized)) {
                addLiteralFact(facts.falseFacts, var.get(), *opposite);
            }
        } else if (op == NEQ) {
            addLiteralFact(facts.falseFacts, var.get(), normalized);
            if (auto opposite = boolOppositeFact(var, normalized)) {
                addLiteralFact(facts.trueFacts, var.get(), *opposite);
            }
        }
    }

    FactMap factsForBranch(const std::shared_ptr<IRVar> &condition, bool trueEdge) {
        FactMap facts;
        if (condition) addLiteralFact(facts, condition.get(), makeBool(trueEdge));
        auto it = condition ? branchFacts.find(condition.get()) : branchFacts.end();
        if (it != branchFacts.end()) {
            mergeFactMap(facts, trueEdge ? it->second.trueFacts : it->second.falseFacts);
        }
        return facts;
    }

    std::optional<LitPtr> simplifyPartialBinary(const std::shared_ptr<IRBinaryop> &op,
                                                const LatticeValue &lhs,
                                                const LatticeValue &rhs) {
        if (!op) return std::nullopt;
        auto lhsLit = lhs.kind == LatticeKind::Constant ? lhs.literal : nullptr;
        auto rhsLit = rhs.kind == LatticeKind::Constant ? rhs.literal : nullptr;
        auto zero = makeSizedInt(0, op->w64tag);
        auto one = makeSizedInt(1, op->w64tag);

        switch (op->op) {
            case MUL:
                if (isZero(lhsLit) || isZero(rhsLit)) return zero;
                break;
            case MOD:
                if (isOne(rhsLit)) return zero;
                break;
            case ANDOP:
            case LOGICALAND:
                if (isZero(lhsLit) || isZero(rhsLit)) return zero;
                break;
            case OROP:
                if (isAllOnes(lhsLit, op->w64tag) || isAllOnes(rhsLit, op->w64tag)) {
                    return makeSizedInt(-1, op->w64tag);
                }
                break;
            case LOGICALOR:
                if ((lhsLit && literalValue(lhsLit) != 0) ||
                    (rhsLit && literalValue(rhsLit) != 0)) {
                    return one;
                }
                break;
            default:
                break;
        }
        return std::nullopt;
    }

    LatticeValue evalCast(const std::shared_ptr<IRVar> &value,
                          const std::shared_ptr<IRType> &originalType,
                          const std::shared_ptr<IRType> &targetType,
                          bool signExtend,
                          IRBlock *block) {
        auto state = valueStateInBlock(value, block);
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
        for (auto &blk : blocks) {
            if (!blk || !executableBlocks.count(blk.get())) continue;
            auto scopedMap = replacementMapForBlock(blk.get(), replaceMap);
            if (scopedMap.empty() && replaceMap.empty()) continue;
            for (auto &instr : blk->instrList) {
                rewriteInstruction(instr, blk.get(), isPhiInstruction(instr) ? replaceMap : scopedMap);
            }
        }
    }

    std::map<IRVar*, ValuePtr> replacementMapForBlock(IRBlock *block,
                                                       const std::map<IRVar*, ValuePtr> &baseMap) {
        auto scopedMap = baseMap;
        auto *onlyPred = singleExecutablePred(block);
        if (!onlyPred) return scopedMap;

        auto edgeIt = edgeFacts.find({onlyPred, block});
        if (edgeIt == edgeFacts.end()) return scopedMap;
        for (auto &entry : edgeIt->second) {
            if (entry.second.kind == LatticeKind::Constant && entry.second.literal) {
                scopedMap[entry.first] = entry.second.literal;
            }
        }
        return scopedMap;
    }

    bool isPhiInstruction(const std::shared_ptr<IRNode> &instr) const {
        return std::dynamic_pointer_cast<IRPHI>(instr) ||
               std::dynamic_pointer_cast<IRPhi>(instr);
    }

    void rewriteInstruction(const std::shared_ptr<IRNode> &instr,
                            IRBlock *block,
                            const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!instr) return;
        if (auto br = std::dynamic_pointer_cast<IRBr>(instr)) {
            rewriteBranch(br, block, replaceMap);
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
                       IRBlock *block,
                       const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!br || !br->condition || !br->trueLabel || !br->falseLabel) return;
        auto state = valueStateInBlock(br->condition, block);
        auto lit = state.kind == LatticeKind::Constant ? state.literal : nullptr;
        if (!lit) {
            auto it = replaceMap.find(br->condition.get());
            if (it == replaceMap.end()) return;
            lit = std::dynamic_pointer_cast<IRLiteral>(it->second);
            if (!lit) return;
        }
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

    bool isZero(const LitPtr &lit) const {
        return lit && literalValue(lit) == 0;
    }

    bool isOne(const LitPtr &lit) const {
        return lit && literalValue(lit) == 1;
    }

    bool isAllOnes(const LitPtr &lit, bool wide64) const {
        if (!lit) return false;
        if (wide64) return static_cast<uint64_t>(literalValue(lit)) == UINT64_MAX;
        return toU32(literalValue(lit)) == 0xffffffffULL;
    }

    bool isIntegerLiteral(const LitPtr &lit) const {
        return lit && lit->literalType != NULL_LITERAL;
    }

    bool isIntegerVar(const std::shared_ptr<IRVar> &var) const {
        return var && std::dynamic_pointer_cast<IRIntType>(var->type);
    }

    bool isBoolVar(const std::shared_ptr<IRVar> &var) const {
        auto type = var ? std::dynamic_pointer_cast<IRIntType>(var->type) : nullptr;
        return type && (type->bitWidth == 1 || type->bitWidth == 8);
    }

    void addLiteralFact(FactMap &facts, IRVar *var, const LitPtr &lit) {
        addFact(facts, var, constant(lit));
    }

    void addFact(FactMap &facts, IRVar *var, const LatticeValue &fact) {
        if (!var) return;
        auto it = facts.find(var);
        if (it == facts.end()) {
            facts[var] = fact;
            return;
        }
        it->second = merge(it->second, fact);
    }

    void mergeFactMap(FactMap &dest, const FactMap &src) {
        for (auto &entry : src) addFact(dest, entry.first, entry.second);
    }

    LitPtr normalizeFactLiteral(const std::shared_ptr<IRVar> &var, const LitPtr &lit) {
        auto type = var ? std::dynamic_pointer_cast<IRIntType>(var->type) : nullptr;
        if (!type || !lit) return lit;
        if (type->bitWidth == 64) return makeI64(static_cast<uint64_t>(literalValue(lit)));
        if (type->bitWidth == 1 || type->bitWidth == 8 || lit->literalType == BOOL_LITERAL) {
            return makeBool(literalValue(lit) != 0);
        }
        return makeI32(literalValue(lit));
    }

    std::optional<LitPtr> boolOppositeFact(const std::shared_ptr<IRVar> &var, const LitPtr &lit) {
        if (!isBoolVar(var) || !lit) return std::nullopt;
        return makeBool(literalValue(lit) == 0);
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

    LitPtr makeSizedInt(long long value, bool wide64) const {
        if (wide64) return makeI64(static_cast<uint64_t>(value));
        return makeI32(value);
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
