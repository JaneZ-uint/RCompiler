#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
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

    struct CastKey {
        int kind;
        std::string value;
        std::string originalType;
        std::string targetType;

        bool operator<(const CastKey &other) const {
            if (kind != other.kind) return kind < other.kind;
            if (value != other.value) return value < other.value;
            if (originalType != other.originalType) return originalType < other.originalType;
            return targetType < other.targetType;
        }
    };

    struct LoadKey {
        std::string address;
        std::string type;
        bool w64tag;
        bool utag;

        bool operator<(const LoadKey &other) const {
            if (address != other.address) return address < other.address;
            if (type != other.type) return type < other.type;
            if (w64tag != other.w64tag) return w64tag < other.w64tag;
            return utag < other.utag;
        }
    };

    struct CSEState {
        std::map<BinaryKey, std::shared_ptr<IRVar>> binaryTable;
        std::map<GetptrKey, std::shared_ptr<IRVar>> getptrTable;
        std::map<CastKey, std::shared_ptr<IRVar>> castTable;
        std::map<LoadKey, std::shared_ptr<IRVar>> loadTable;
        std::map<IRVar*, std::shared_ptr<IRValue>> replaceMap;
    };

    std::vector<std::shared_ptr<IRBlock>> blocks;
    std::map<IRBlock*, std::vector<IRBlock*>> succs;
    std::map<IRBlock*, std::vector<IRBlock*>> preds;
    std::map<IRBlock*, IRBlock*> idom;
    std::map<IRBlock*, std::vector<IRBlock*>> domChildren;
    std::vector<IRBlock*> rpo;
    std::map<IRBlock*, int> rpoIndex;

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        buildCFG(func);
        computeRPO(func->body.get());
        if (rpo.empty()) return;
        buildDomTree(func->body.get());
        CSEState state;
        optimizeDomTree(func->body.get(), state);
    }

    void buildCFG(const std::shared_ptr<IRFunction> &func) {
        blocks.clear();
        succs.clear();
        preds.clear();
        idom.clear();
        domChildren.clear();
        rpo.clear();
        rpoIndex.clear();

        blocks.push_back(func->body);
        for (auto &blk : func->body->blockList) {
            if (blk) blocks.push_back(blk);
        }
        for (auto &blk : blocks) {
            succs[blk.get()] = {};
            preds[blk.get()] = {};
        }

        for (size_t i = 0; i < blocks.size(); i++) {
            auto &blk = blocks[i];
            if (!blk) continue;

            if (!blk->instrList.empty()) {
                if (auto br = std::dynamic_pointer_cast<IRBr>(blk->instrList.back())) {
                    addEdge(blk.get(), br->trueLabel.get());
                    if (br->falseLabel && br->falseLabel != br->trueLabel) {
                        addEdge(blk.get(), br->falseLabel.get());
                    }
                    continue;
                }
                if (std::dynamic_pointer_cast<IRReturn>(blk->instrList.back()) ||
                    std::dynamic_pointer_cast<IRExit>(blk->instrList.back())) {
                    continue;
                }
            }

            if (i + 1 < blocks.size()) addEdge(blk.get(), blocks[i + 1].get());
        }
    }

    void addEdge(IRBlock *from, IRBlock *to) {
        if (!from || !to) return;
        auto &out = succs[from];
        if (std::find(out.begin(), out.end(), to) == out.end()) out.push_back(to);
        auto &in = preds[to];
        if (std::find(in.begin(), in.end(), from) == in.end()) in.push_back(from);
    }

    void computeRPO(IRBlock *entry) {
        if (!entry) return;
        std::set<IRBlock*> visited;
        std::vector<IRBlock*> postorder;

        std::function<void(IRBlock*)> dfs = [&](IRBlock *blk) {
            if (!blk || !visited.insert(blk).second) return;
            for (auto *succ : succs[blk]) dfs(succ);
            postorder.push_back(blk);
        };
        dfs(entry);

        rpo.assign(postorder.rbegin(), postorder.rend());
        for (int i = 0; i < static_cast<int>(rpo.size()); i++) {
            rpoIndex[rpo[i]] = i;
        }
    }

    IRBlock *intersect(IRBlock *lhs, IRBlock *rhs) {
        while (lhs != rhs) {
            while (rpoIndex[lhs] > rpoIndex[rhs]) lhs = idom[lhs];
            while (rpoIndex[rhs] > rpoIndex[lhs]) rhs = idom[rhs];
        }
        return lhs;
    }

    void buildDomTree(IRBlock *entry) {
        if (!entry) return;
        idom.clear();
        domChildren.clear();
        idom[entry] = entry;

        bool changed = true;
        while (changed) {
            changed = false;
            for (auto *blk : rpo) {
                if (blk == entry) continue;
                IRBlock *newIdom = nullptr;
                for (auto *pred : preds[blk]) {
                    if (!idom.count(pred)) continue;
                    newIdom = newIdom ? intersect(pred, newIdom) : pred;
                }
                if (newIdom && idom[blk] != newIdom) {
                    idom[blk] = newIdom;
                    changed = true;
                }
            }
        }

        for (auto *blk : rpo) {
            if (blk == entry) continue;
            auto it = idom.find(blk);
            if (it != idom.end()) domChildren[it->second].push_back(blk);
        }
    }

    void optimizeDomTree(IRBlock *blk, CSEState state) {
        if (!blk) return;
        if (!canKeepIncomingLoads(blk)) state.loadTable.clear();

        for (auto &instr : blk->instrList) {
            if (isPhiInstruction(instr)) {
                killDefs(instr, state);
                continue;
            }

            IRUtil::replaceUses(instr, state.replaceMap);

            auto op = std::dynamic_pointer_cast<IRBinaryop>(instr);
            if (op && op->result) {
                processBinary(op, state);
                continue;
            }

            auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr);
            if (getptr && getptr->res) {
                processGetptr(getptr, state);
                continue;
            }

            auto sext = std::dynamic_pointer_cast<IRSext>(instr);
            if (sext && sext->result) {
                processCast(0, sext->value, sext->originalType, sext->targetType,
                            sext->result, state);
                continue;
            }

            auto zext = std::dynamic_pointer_cast<IRZext>(instr);
            if (zext && zext->result) {
                processCast(1, zext->value, zext->originalType, zext->targetType,
                            zext->result, state);
                continue;
            }

            auto trunc = std::dynamic_pointer_cast<IRTrunc>(instr);
            if (trunc && trunc->result) {
                processCast(2, trunc->value, trunc->originalType, trunc->targetType,
                            trunc->result, state);
                continue;
            }

            auto load = std::dynamic_pointer_cast<IRLoad>(instr);
            if (load && load->tmp) {
                processLoad(load, state);
                continue;
            }

            if (std::dynamic_pointer_cast<IRStore>(instr)) {
                state.loadTable.clear();
                killDefs(instr, state);
                continue;
            }

            if (isMemoryBarrier(instr)) state.loadTable.clear();
            killDefs(instr, state);
        }

        for (auto *child : domChildren[blk]) optimizeDomTree(child, state);
    }

    bool canKeepIncomingLoads(IRBlock *blk) const {
        if (!blk || preds.find(blk) == preds.end()) return false;
        auto it = idom.find(blk);
        if (it != idom.end() && it->second == blk) return true;
        auto predIt = preds.find(blk);
        if (predIt == preds.end() || predIt->second.size() != 1) return false;
        return it != idom.end() && it->second == predIt->second.front();
    }

    bool isPhiInstruction(const std::shared_ptr<IRNode> &instr) const {
        return std::dynamic_pointer_cast<IRPHI>(instr) ||
               std::dynamic_pointer_cast<IRPhi>(instr);
    }

    void processBinary(const std::shared_ptr<IRBinaryop> &op,
                       CSEState &state) {
        auto key = makeBinaryKey(op);
        if (!key) {
            state.replaceMap.erase(op->result.get());
            return;
        }

        auto it = state.binaryTable.find(*key);
        if (it != state.binaryTable.end()) {
            state.replaceMap[op->result.get()] = it->second;
        } else {
            state.binaryTable[*key] = op->result;
            state.replaceMap.erase(op->result.get());
        }
    }

    void processGetptr(const std::shared_ptr<IRGetptr> &getptr,
                       CSEState &state) {
        auto key = makeGetptrKey(getptr);
        if (!key) {
            state.replaceMap.erase(getptr->res.get());
            return;
        }

        auto it = state.getptrTable.find(*key);
        if (it != state.getptrTable.end()) {
            state.replaceMap[getptr->res.get()] = it->second;
        } else {
            state.getptrTable[*key] = getptr->res;
            state.replaceMap.erase(getptr->res.get());
        }
    }

    void processCast(int kind,
                     const std::shared_ptr<IRVar> &value,
                     const std::shared_ptr<IRType> &originalType,
                     const std::shared_ptr<IRType> &targetType,
                     const std::shared_ptr<IRVar> &result,
                     CSEState &state) {
        auto key = makeCastKey(kind, value, originalType, targetType);
        if (!key) {
            state.replaceMap.erase(result.get());
            return;
        }

        auto it = state.castTable.find(*key);
        if (it != state.castTable.end()) {
            state.replaceMap[result.get()] = it->second;
        } else {
            state.castTable[*key] = result;
            state.replaceMap.erase(result.get());
        }
    }

    void processLoad(const std::shared_ptr<IRLoad> &load,
                     CSEState &state) {
        auto key = makeLoadKey(load);
        if (!key) {
            state.replaceMap.erase(load->tmp.get());
            return;
        }

        auto it = state.loadTable.find(*key);
        if (it != state.loadTable.end()) {
            state.replaceMap[load->tmp.get()] = it->second;
        } else {
            state.loadTable[*key] = load->tmp;
            state.replaceMap.erase(load->tmp.get());
        }
    }

    void killDefs(const std::shared_ptr<IRNode> &instr, CSEState &state) {
        for (auto &def : IRUtil::defs(instr)) {
            if (!def) continue;
            state.replaceMap.erase(def.get());
            for (auto it = state.binaryTable.begin(); it != state.binaryTable.end();) {
                if (it->second.get() == def.get()) it = state.binaryTable.erase(it);
                else ++it;
            }
            for (auto it = state.getptrTable.begin(); it != state.getptrTable.end();) {
                if (it->second.get() == def.get()) it = state.getptrTable.erase(it);
                else ++it;
            }
            for (auto it = state.castTable.begin(); it != state.castTable.end();) {
                if (it->second.get() == def.get()) it = state.castTable.erase(it);
                else ++it;
            }
            for (auto it = state.loadTable.begin(); it != state.loadTable.end();) {
                if (it->second.get() == def.get()) it = state.loadTable.erase(it);
                else ++it;
            }
        }
    }

    bool isMemoryBarrier(const std::shared_ptr<IRNode> &instr) const {
        return std::dynamic_pointer_cast<IRCall>(instr) ||
               std::dynamic_pointer_cast<IRGetint>(instr) ||
               std::dynamic_pointer_cast<IRMemcpy>(instr) ||
               std::dynamic_pointer_cast<IRMemset>(instr);
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

    std::optional<CastKey> makeCastKey(int kind,
                                       const std::shared_ptr<IRVar> &value,
                                       const std::shared_ptr<IRType> &originalType,
                                       const std::shared_ptr<IRType> &targetType) const {
        CastKey key{kind, valueKey(value), typeKey(originalType), typeKey(targetType)};
        if (key.value.empty() || key.originalType.empty() || key.targetType.empty()) {
            return std::nullopt;
        }
        return key;
    }

    std::optional<LoadKey> makeLoadKey(const std::shared_ptr<IRLoad> &load) const {
        if (!load || !load->addressVar || !load->type) return std::nullopt;
        LoadKey key{valueKey(load->addressVar), typeKey(load->type), load->w64tag, load->utag};
        if (key.address.empty() || key.type.empty()) return std::nullopt;
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
