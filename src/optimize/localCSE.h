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
    struct BinaryKey {
        IROp op;
        std::string lhs;
        std::string rhs;
        bool utag;
        bool i8tag;
        bool w64tag;

        bool operator<(const BinaryKey &other) const {
            if (op != other.op) return op < other.op;
            if (lhs != other.lhs) return lhs < other.lhs;
            if (rhs != other.rhs) return rhs < other.rhs;
            if (utag != other.utag) return utag < other.utag;
            if (i8tag != other.i8tag) return i8tag < other.i8tag;
            return w64tag < other.w64tag;
        }
    };

    struct GetptrKey {
        std::string type;
        std::string base;
        long long offset;
        std::string index;
        bool hasIndex;

        bool operator<(const GetptrKey &other) const {
            if (type != other.type) return type < other.type;
            if (base != other.base) return base < other.base;
            if (offset != other.offset) return offset < other.offset;
            if (index != other.index) return index < other.index;
            return hasIndex < other.hasIndex;
        }
    };

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        optimizeBlock(func->body);
        for (auto &blk : func->body->blockList) optimizeBlock(blk);
    }

    void optimizeBlock(const std::shared_ptr<IRBlock> &blk) {
        if (!blk) return;
        std::map<BinaryKey, std::shared_ptr<IRVar>> binaryTable;
        std::map<GetptrKey, std::shared_ptr<IRVar>> getptrTable;
        std::map<IRVar*, std::shared_ptr<IRValue>> replaceMap;

        for (auto &instr : blk->instrList) {
            IRUtil::replaceUses(instr, replaceMap);

            auto op = std::dynamic_pointer_cast<IRBinaryop>(instr);
            if (op && op->result) {
                processBinary(op, binaryTable, replaceMap);
                continue;
            }

            auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr);
            if (getptr && getptr->res) {
                processGetptr(getptr, getptrTable, replaceMap);
                continue;
            }

            if (IRUtil::hasSideEffect(instr)) {
                binaryTable.clear();
                getptrTable.clear();
            }
            killDefs(instr, binaryTable, getptrTable, replaceMap);
        }
    }

    void processBinary(const std::shared_ptr<IRBinaryop> &op,
                       std::map<BinaryKey, std::shared_ptr<IRVar>> &binaryTable,
                       std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
        auto key = makeBinaryKey(op);
        if (!key) {
            replaceMap.erase(op->result.get());
            return;
        }

        auto it = binaryTable.find(*key);
        if (it != binaryTable.end()) {
            replaceMap[op->result.get()] = it->second;
        } else {
            binaryTable[*key] = op->result;
            replaceMap.erase(op->result.get());
        }
    }

    void processGetptr(const std::shared_ptr<IRGetptr> &getptr,
                       std::map<GetptrKey, std::shared_ptr<IRVar>> &getptrTable,
                       std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
        auto key = makeGetptrKey(getptr);
        if (!key) {
            replaceMap.erase(getptr->res.get());
            return;
        }

        auto it = getptrTable.find(*key);
        if (it != getptrTable.end()) {
            replaceMap[getptr->res.get()] = it->second;
        } else {
            getptrTable[*key] = getptr->res;
            replaceMap.erase(getptr->res.get());
        }
    }

    void killDefs(const std::shared_ptr<IRNode> &instr,
                  std::map<BinaryKey, std::shared_ptr<IRVar>> &binaryTable,
                  std::map<GetptrKey, std::shared_ptr<IRVar>> &getptrTable,
                  std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
        for (auto &def : IRUtil::defs(instr)) {
            if (!def) continue;
            replaceMap.erase(def.get());
            for (auto it = binaryTable.begin(); it != binaryTable.end();) {
                if (it->second.get() == def.get()) it = binaryTable.erase(it);
                else ++it;
            }
            for (auto it = getptrTable.begin(); it != getptrTable.end();) {
                if (it->second.get() == def.get()) it = getptrTable.erase(it);
                else ++it;
            }
        }
    }

    bool isCommutative(IROp op) const {
        return op == ADD || op == MUL || op == ANDOP || op == OROP ||
               op == XOROP || op == EQ || op == NEQ;
    }

    std::optional<BinaryKey> makeBinaryKey(const std::shared_ptr<IRBinaryop> &op) const {
        if (!op || !op->leftValue || !op->rightValue) return std::nullopt;
        BinaryKey key{op->op, valueKey(op->leftValue), valueKey(op->rightValue),
                      op->utag, op->i8tag, op->w64tag};
        if (key.lhs.empty() || key.rhs.empty()) return std::nullopt;
        if (isCommutative(key.op) && key.rhs < key.lhs) std::swap(key.lhs, key.rhs);
        return key;
    }

    std::optional<GetptrKey> makeGetptrKey(const std::shared_ptr<IRGetptr> &getptr) const {
        if (!getptr || !getptr->base) return std::nullopt;
        GetptrKey key{getptrTypeKey(getptr), valueKey(getptr->base), getptr->offset,
                      getptr->index ? valueKey(getptr->index) : "", getptr->index != nullptr};
        if (key.type.empty() || key.base.empty()) return std::nullopt;
        if (key.hasIndex && key.index.empty()) return std::nullopt;
        return key;
    }

    std::string getptrTypeKey(const std::shared_ptr<IRGetptr> &getptr) const {
        if (!getptr) return "";
        auto pointedType = getptr->base ? getptr->base->type : nullptr;
        if (auto ptr = std::dynamic_pointer_cast<IRPtrType>(pointedType)) {
            pointedType = ptr->baseType;
        }
        return typeKey(pointedType) + ":" + typeKey(getptr->type);
    }

    std::string typeKey(const std::shared_ptr<IRType> &type) const {
        if (!type) return "";
        return "t" + std::to_string(reinterpret_cast<uintptr_t>(type.get())) + ":" +
               std::to_string(static_cast<int>(type->type)) + ":" +
               std::to_string(type->size);
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
