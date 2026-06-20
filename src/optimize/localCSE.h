#pragma once

#include <algorithm>
#include <cstdint>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include "../ir/IRFunction.h"
#include "../ir/IRImpl.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRRoot.h"
#include "IRUtil.h"

namespace JaneZ {

class LocalCSE {
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
    struct ExprKey {
        IROp op;
        std::string lhs;
        std::string rhs;
        bool utag;
        bool i8tag;
        bool w64tag;

        bool operator<(const ExprKey &other) const {
            if (op != other.op) return op < other.op;
            if (lhs != other.lhs) return lhs < other.lhs;
            if (rhs != other.rhs) return rhs < other.rhs;
            if (utag != other.utag) return utag < other.utag;
            if (i8tag != other.i8tag) return i8tag < other.i8tag;
            return w64tag < other.w64tag;
        }
    };

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        optimizeBlock(func->body);
        for (auto &blk : func->body->blockList) optimizeBlock(blk);
    }

    void optimizeBlock(const std::shared_ptr<IRBlock> &blk) {
        if (!blk) return;
        std::map<ExprKey, std::shared_ptr<IRVar>> exprTable;
        std::map<IRVar*, std::shared_ptr<IRValue>> replaceMap;

        for (auto &instr : blk->instrList) {
            IRUtil::replaceUses(instr, replaceMap);

            auto op = std::dynamic_pointer_cast<IRBinaryop>(instr);
            if (!op || !op->result) {
                if (IRUtil::hasSideEffect(instr)) exprTable.clear();
                killDefs(instr, exprTable, replaceMap);
                continue;
            }

            auto key = makeKey(op);
            if (!key) {
                killDefs(instr, exprTable, replaceMap);
                continue;
            }

            auto it = exprTable.find(*key);
            if (it != exprTable.end()) {
                replaceMap[op->result.get()] = it->second;
            } else {
                exprTable[*key] = op->result;
                replaceMap.erase(op->result.get());
            }
        }
    }

    void killDefs(const std::shared_ptr<IRNode> &instr,
                  std::map<ExprKey, std::shared_ptr<IRVar>> &exprTable,
                  std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
        for (auto &def : IRUtil::defs(instr)) {
            if (!def) continue;
            replaceMap.erase(def.get());
            for (auto it = exprTable.begin(); it != exprTable.end();) {
                if (it->second.get() == def.get()) it = exprTable.erase(it);
                else ++it;
            }
        }
    }

    bool isCommutative(IROp op) const {
        return op == ADD || op == MUL || op == ANDOP || op == OROP ||
               op == XOROP || op == EQ || op == NEQ;
    }

    std::optional<ExprKey> makeKey(const std::shared_ptr<IRBinaryop> &op) const {
        if (!op || !op->leftValue || !op->rightValue) return std::nullopt;
        ExprKey key{op->op, valueKey(op->leftValue), valueKey(op->rightValue),
                    op->utag, op->i8tag, op->w64tag};
        if (key.lhs.empty() || key.rhs.empty()) return std::nullopt;
        if (isCommutative(key.op) && key.rhs < key.lhs) std::swap(key.lhs, key.rhs);
        return key;
    }

    std::string valueKey(const std::shared_ptr<IRValue> &value) const {
        if (auto var = std::dynamic_pointer_cast<IRVar>(value)) {
            return "v" + std::to_string(reinterpret_cast<uintptr_t>(var.get()));
        }
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(value)) {
            return "l" + std::to_string(static_cast<int>(lit->literalType)) + ":" +
                   std::to_string(lit->intValue) + ":" + (lit->boolValue ? "1" : "0");
        }
        return "";
    }
};

} // namespace JaneZ
