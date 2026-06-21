#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>
#include <optional>
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
    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        optimizeBlock(func->body);
        for (auto &blk : func->body->blockList) optimizeBlock(blk);
    }

    void optimizeBlock(const std::shared_ptr<IRBlock> &block) {
        if (!block) return;
        for (auto &instr : block->instrList) {
            auto op = std::dynamic_pointer_cast<IRBinaryop>(instr);
            if (!op) continue;
            reduceBinary(op);
        }
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
