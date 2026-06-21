#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>
#include "../ir/IRBinaryop.h"
#include "../ir/IRBlock.h"
#include "../ir/IRFunction.h"
#include "../ir/IRImpl.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRRoot.h"
#include "../ir/IRValue.h"

namespace JaneZ {

class StrengthReduction {
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
    struct NearPowerPlan {
        int shift = 0;
        bool add = true;
    };

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        optimizeBlock(func->body);
        for (auto &blk : func->body->blockList) optimizeBlock(blk);
    }

    void optimizeBlock(const std::shared_ptr<IRBlock> &block) {
        if (!block) return;
        std::vector<std::shared_ptr<IRNode>> rewritten;
        rewritten.reserve(block->instrList.size());
        for (auto &instr : block->instrList) {
            auto op = std::dynamic_pointer_cast<IRBinaryop>(instr);
            if (!op) {
                rewritten.push_back(instr);
                continue;
            }
            if (reduceMulNearPowerOfTwo(op, rewritten)) {
                rewritten.push_back(instr);
                continue;
            }
            reduceBinary(op);
            rewritten.push_back(instr);
        }
        block->instrList.swap(rewritten);
    }

    void reduceBinary(const std::shared_ptr<IRBinaryop> &op) {
        if (!op || !op->leftValue || !op->rightValue) return;
        if (reduceMulPowerOfTwo(op)) return;
        if (reduceUnsignedDivModPowerOfTwo(op)) return;
    }

    bool reduceMulPowerOfTwo(const std::shared_ptr<IRBinaryop> &op) {
        if (op->op != MUL) return false;

        auto rhsLit = std::dynamic_pointer_cast<IRLiteral>(op->rightValue);
        if (auto shift = powerOfTwoShift(rhsLit, op->w64tag)) {
            op->op = LEFTSHIFTOP;
            op->rightValue = makeShiftLiteral(*shift);
            return true;
        }

        auto lhsLit = std::dynamic_pointer_cast<IRLiteral>(op->leftValue);
        if (auto shift = powerOfTwoShift(lhsLit, op->w64tag)) {
            op->op = LEFTSHIFTOP;
            op->leftValue = op->rightValue;
            op->rightValue = makeShiftLiteral(*shift);
            return true;
        }

        return false;
    }

    bool reduceMulNearPowerOfTwo(const std::shared_ptr<IRBinaryop> &op,
                                 std::vector<std::shared_ptr<IRNode>> &rewritten) {
        if (op->op != MUL || !op->w64tag || !op->result) return false;

        std::shared_ptr<IRLiteral> factor;
        std::shared_ptr<IRValue> value;
        if ((factor = std::dynamic_pointer_cast<IRLiteral>(op->rightValue))) {
            value = op->leftValue;
        } else if ((factor = std::dynamic_pointer_cast<IRLiteral>(op->leftValue))) {
            value = op->rightValue;
        } else {
            return false;
        }

        auto plan = nearPowerOfTwoPlan(factor);
        if (!plan || !value) return false;

        auto shifted = std::make_shared<IRVar>();
        shifted->type = op->result->type;

        auto shiftOp = std::make_shared<IRBinaryop>(LEFTSHIFTOP, shifted);
        shiftOp->leftValue = value;
        shiftOp->rightValue = makeShiftLiteral(plan->shift);
        shiftOp->utag = op->utag;
        shiftOp->i8tag = op->i8tag;
        shiftOp->w64tag = op->w64tag;
        rewritten.push_back(shiftOp);

        op->op = plan->add ? ADD : SUB;
        op->leftValue = shifted;
        op->rightValue = value;
        return true;
    }

    bool reduceUnsignedDivModPowerOfTwo(const std::shared_ptr<IRBinaryop> &op) {
        if (!op->utag || (op->op != DIV && op->op != MOD)) return false;

        auto rhsLit = std::dynamic_pointer_cast<IRLiteral>(op->rightValue);
        auto shift = powerOfTwoShift(rhsLit, op->w64tag);
        if (!shift) return false;

        if (op->op == DIV) {
            op->op = RIGHTSHIFTOP;
            op->rightValue = makeShiftLiteral(*shift);
            return true;
        }

        op->op = ANDOP;
        op->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, literalMask(*shift), true);
        return true;
    }

    std::shared_ptr<IRLiteral> makeShiftLiteral(int shift) const {
        return std::make_shared<IRLiteral>(INT_LITERAL, shift, shift != 0);
    }

    long long literalMask(int shift) const {
        if (shift <= 0) return 0;
        if (shift >= 64) return static_cast<long long>(UINT64_MAX);
        return static_cast<long long>((1ULL << shift) - 1ULL);
    }

    std::optional<NearPowerPlan> nearPowerOfTwoPlan(const std::shared_ptr<IRLiteral> &lit) const {
        if (!lit || lit->literalType != INT_LITERAL || lit->intValue <= 2) {
            return std::nullopt;
        }
        uint64_t value = static_cast<uint64_t>(lit->intValue);

        if (auto shift = powerOfTwoShift(value - 1, 64)) {
            return NearPowerPlan{*shift, true};
        }
        if (value != UINT64_MAX) {
            if (auto shift = powerOfTwoShift(value + 1, 64)) {
                return NearPowerPlan{*shift, false};
            }
        }
        return std::nullopt;
    }

    std::optional<int> powerOfTwoShift(const std::shared_ptr<IRLiteral> &lit, bool wide64) const {
        if (!lit || lit->literalType != INT_LITERAL) return std::nullopt;
        int bits = wide64 ? 64 : 32;
        uint64_t value = wide64 ? static_cast<uint64_t>(lit->intValue)
                                : (static_cast<uint64_t>(lit->intValue) & 0xffffffffULL);
        return powerOfTwoShift(value, bits);
    }

    std::optional<int> powerOfTwoShift(uint64_t value, int bits) const {
        if (value == 0 || (value & (value - 1)) != 0) return std::nullopt;
        int shift = 0;
        while ((value >>= 1) != 0) shift++;
        if (shift <= 0 || shift >= bits) return std::nullopt;
        return shift;
    }
};

} // namespace JaneZ
