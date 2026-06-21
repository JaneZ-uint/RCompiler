#pragma once

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "../ir/IRAlloca.h"
#include "../ir/IRBlock.h"
#include "../ir/IRBr.h"
#include "../ir/IRCall.h"
#include "../ir/IRExit.h"
#include "../ir/IRFunction.h"
#include "../ir/IRGetint.h"
#include "../ir/IRGetptr.h"
#include "../ir/IRGlobal.h"
#include "../ir/IRImpl.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRMem.h"
#include "../ir/IRReturn.h"
#include "../ir/IRRoot.h"
#include "../ir/IRStore.h"
#include "../ir/IRLoad.h"
#include "IRUtil.h"

namespace JaneZ {

class MemoryForward {
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
    using ValuePtr = std::shared_ptr<IRValue>;

    struct AddressInfo {
        std::string exact;
        std::string root;
        std::string path;
        bool knownRoot = false;
        bool precisePath = false;
    };

    struct AccessInfo {
        AddressInfo address;
        std::string type;
        int size = 0;
        bool valid = false;
    };

    struct StoreState {
        ValuePtr value;
        std::shared_ptr<IRStore> instr;
        IRBlock *block = nullptr;
        AccessInfo access;
    };

    struct ForwardState {
        std::map<std::string, StoreState> stores;
        std::map<IRVar*, ValuePtr> replaceMap;
        std::map<IRVar*, AddressInfo> addressFacts;
    };

    std::vector<std::shared_ptr<IRBlock>> blocks;
    std::map<IRBlock*, std::vector<IRBlock*>> succs;
    std::map<IRBlock*, std::vector<IRBlock*>> preds;
    std::map<IRBlock*, IRBlock*> idom;
    std::map<IRBlock*, std::vector<IRBlock*>> domChildren;
    std::vector<IRBlock*> rpo;
    std::map<IRBlock*, int> rpoIndex;
    std::set<IRVar*> objectRoots;

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        buildCFG(func);
        computeRPO(func->body.get());
        if (rpo.empty()) return;
        buildDomTree(func->body.get());
        collectObjectRoots();

        ForwardState state;
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
        objectRoots.clear();

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

    void collectObjectRoots() {
        for (auto &blk : blocks) {
            if (!blk) continue;
            for (auto &instr : blk->instrList) {
                if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                    if (alloca->var) objectRoots.insert(alloca->var.get());
                }
            }
        }
    }

    void optimizeDomTree(IRBlock *blk, ForwardState state) {
        if (!blk) return;
        if (!canKeepIncomingMemory(blk)) state.stores.clear();
        std::set<IRNode*> toRemove;

        for (auto &instr : blk->instrList) {
            if (isPhiInstruction(instr)) {
                killDefs(instr, state);
                continue;
            }

            rewriteUses(instr, state.replaceMap);

            if (auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr)) {
                processGetptr(getptr, state);
                continue;
            }

            if (auto load = std::dynamic_pointer_cast<IRLoad>(instr)) {
                processLoad(load, state);
                continue;
            }

            if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
                processStore(store, blk, state, toRemove);
                continue;
            }

            if (isMemoryBarrier(instr)) {
                state.stores.clear();
            }
            killDefs(instr, state);
        }

        if (!toRemove.empty()) {
            blk->instrList.erase(std::remove_if(blk->instrList.begin(), blk->instrList.end(),
                [&](const std::shared_ptr<IRNode> &instr) {
                    return toRemove.count(instr.get()) > 0;
                }),
                blk->instrList.end());
        }

        for (auto *child : domChildren[blk]) optimizeDomTree(child, state);
    }

    bool canKeepIncomingMemory(IRBlock *blk) const {
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

    void processLoad(const std::shared_ptr<IRLoad> &load,
                     ForwardState &state) {
        if (!load || !load->tmp) {
            state.stores.clear();
            return;
        }
        auto access = loadAccess(load, state);
        auto it = findForwardStore(access, state);
        if (it != state.stores.end() && it->second.value) {
            state.replaceMap[load->tmp.get()] = it->second.value;
            state.addressFacts.erase(load->tmp.get());
            return;
        }

        state.replaceMap.erase(load->tmp.get());
        state.addressFacts.erase(load->tmp.get());
        if (!access.valid) {
            state.stores.clear();
            return;
        }
        forgetAliasedStores(access.address, state);
    }

    void processStore(const std::shared_ptr<IRStore> &store,
                      IRBlock *blk,
                      ForwardState &state,
                      std::set<IRNode*> &toRemove) {
        if (!store) {
            state.stores.clear();
            return;
        }
        auto access = storeAccess(store, state);
        auto value = storeValue(store);

        auto prev = findForwardStore(access, state);
        if (prev != state.stores.end() && prev->second.instr &&
            prev->second.block == blk && compatibleAccess(access, prev->second.access)) {
            toRemove.insert(prev->second.instr.get());
        }

        if (!access.valid) {
            state.stores.clear();
            return;
        }
        forgetAliasedStores(access.address, state);
        auto key = accessKey(access);
        if (!key.empty() && value) {
            state.stores[key] = StoreState{value, store, blk, access};
        }
    }

    void processGetptr(const std::shared_ptr<IRGetptr> &getptr,
                       ForwardState &state) {
        if (!getptr || !getptr->res) return;
        state.replaceMap.erase(getptr->res.get());

        auto base = addressInfo(getptr->base, state);
        AddressInfo info;
        info.exact = valueKey(getptr->res);
        if (base.knownRoot) {
            info.knownRoot = true;
            info.root = base.root;
            info.path = base.path;
            info.precisePath = base.precisePath;
            if (getptr->index) {
                appendPath(info.path, "i" + valueKey(getptr->index));
                info.precisePath = false;
            } else if (getptr->offset != -1) {
                appendPath(info.path, "o" + std::to_string(getptr->offset));
            }
        }

        if (info.knownRoot) state.addressFacts[getptr->res.get()] = info;
        else state.addressFacts.erase(getptr->res.get());
    }

    void killDefs(const std::shared_ptr<IRNode> &instr, ForwardState &state) {
        for (auto &def : IRUtil::defs(instr)) {
            if (!def) continue;
            state.replaceMap.erase(def.get());
            state.addressFacts.erase(def.get());
            auto defKey = valueKey(def);
            for (auto it = state.stores.begin(); it != state.stores.end();) {
                if (storeMentionsVar(it->second, def.get(), defKey)) {
                    it = state.stores.erase(it);
                } else {
                    ++it;
                }
            }
        }
    }

    ValuePtr storeValue(const std::shared_ptr<IRStore> &store) {
        if (!store) return nullptr;
        if (store->storeLiteral) return store->storeLiteral;
        return store->storeValue;
    }

    AccessInfo loadAccess(const std::shared_ptr<IRLoad> &load,
                          const ForwardState &state) const {
        AccessInfo access;
        if (!load || !load->addressVar || !load->type) return access;
        access.address = addressInfo(load->addressVar, state);
        access.type = accessTypeKey(load->type, load->w64tag);
        access.size = accessSize(load->type, load->w64tag);
        access.valid = !locationKey(access.address).empty() && !access.type.empty() &&
                       access.size > 0;
        return access;
    }

    AccessInfo storeAccess(const std::shared_ptr<IRStore> &store,
                           const ForwardState &state) const {
        AccessInfo access;
        if (!store || !store->address || !store->valueType) return access;
        access.address = addressInfo(store->address, state);
        access.type = accessTypeKey(store->valueType, store->w64tag);
        access.size = accessSize(store->valueType, store->w64tag);
        access.valid = !locationKey(access.address).empty() && !access.type.empty() &&
                       access.size > 0;
        return access;
    }

    AddressInfo addressInfo(const std::shared_ptr<IRVar> &var,
                            const ForwardState &state) const {
        AddressInfo info;
        if (!var) return info;
        info.exact = valueKey(var);
        auto it = state.addressFacts.find(var.get());
        if (it != state.addressFacts.end()) {
            info = it->second;
            info.exact = valueKey(var);
            return info;
        }
        if (objectRoots.count(var.get())) {
            info.knownRoot = true;
            info.root = valueKey(var);
            info.precisePath = true;
        }
        return info;
    }

    std::map<std::string, StoreState>::iterator
    findForwardStore(const AccessInfo &access, ForwardState &state) {
        if (!access.valid) return state.stores.end();
        for (auto it = state.stores.begin(); it != state.stores.end(); ++it) {
            if (sameLocation(access.address, it->second.access.address) &&
                compatibleAccess(access, it->second.access)) {
                return it;
            }
        }
        return state.stores.end();
    }

    void forgetAliasedStores(const AddressInfo &address, ForwardState &state) {
        for (auto it = state.stores.begin(); it != state.stores.end();) {
            if (mayAlias(address, it->second.access.address)) {
                it = state.stores.erase(it);
            } else {
                ++it;
            }
        }
    }

    bool compatibleAccess(const AccessInfo &lhs, const AccessInfo &rhs) const {
        return lhs.valid && rhs.valid &&
               lhs.size == rhs.size &&
               lhs.type == rhs.type;
    }

    bool sameLocation(const AddressInfo &lhs, const AddressInfo &rhs) const {
        if (!lhs.exact.empty() && lhs.exact == rhs.exact) return true;
        return lhs.knownRoot && rhs.knownRoot &&
               lhs.root == rhs.root &&
               lhs.path == rhs.path;
    }

    bool mayAlias(const AddressInfo &lhs, const AddressInfo &rhs) const {
        if (sameLocation(lhs, rhs)) return true;
        if (!lhs.knownRoot || !rhs.knownRoot) return true;
        if (lhs.root != rhs.root) return false;
        if (lhs.precisePath && rhs.precisePath &&
            disjointPrecisePaths(lhs.path, rhs.path)) {
            return false;
        }
        return true;
    }

    bool disjointPrecisePaths(const std::string &lhs, const std::string &rhs) const {
        if (lhs.empty() || rhs.empty() || lhs == rhs) return false;
        return !pathPrefix(lhs, rhs) && !pathPrefix(rhs, lhs);
    }

    bool pathPrefix(const std::string &prefix, const std::string &path) const {
        if (prefix.size() > path.size()) return false;
        if (path.compare(0, prefix.size(), prefix) != 0) return false;
        return prefix.size() == path.size() || path[prefix.size()] == '/';
    }

    void appendPath(std::string &path, const std::string &component) {
        if (component.empty()) return;
        if (!path.empty()) path += "/";
        path += component;
    }

    std::string accessKey(const AccessInfo &access) const {
        auto loc = locationKey(access.address);
        if (loc.empty() || access.type.empty()) return "";
        return loc + "|" + access.type + "|" + std::to_string(access.size);
    }

    std::string locationKey(const AddressInfo &address) const {
        if (address.knownRoot) {
            return "r" + address.root + ":" + address.path;
        }
        if (!address.exact.empty()) return "e" + address.exact;
        return "";
    }

    std::string valueKey(const std::shared_ptr<IRValue> &value) const {
        if (auto var = std::dynamic_pointer_cast<IRVar>(value)) return valueKey(var);
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(value)) {
            return "l" + std::to_string(static_cast<int>(lit->literalType)) + ":" +
                   std::to_string(lit->intValue) + ":" + (lit->boolValue ? "1" : "0");
        }
        return "";
    }

    std::string valueKey(const std::shared_ptr<IRVar> &var) const {
        if (!var) return "";
        return "v" + std::to_string(reinterpret_cast<uintptr_t>(var.get()));
    }

    std::string accessTypeKey(const std::shared_ptr<IRType> &type, bool w64tag) const {
        if (!type) return "";
        if (auto intType = std::dynamic_pointer_cast<IRIntType>(type)) {
            int bits = w64tag ? 64 : intType->bitWidth;
            return "i" + std::to_string(bits) + ":" +
                   (intType->isUnsigned ? "u" : "s");
        }
        if (auto ptrType = std::dynamic_pointer_cast<IRPtrType>(type)) {
            return "p(" + typeShapeKey(ptrType->baseType) + ")";
        }
        return typeShapeKey(type);
    }

    std::string typeShapeKey(const std::shared_ptr<IRType> &type) const {
        if (!type) return "";
        if (auto intType = std::dynamic_pointer_cast<IRIntType>(type)) {
            return "i" + std::to_string(intType->bitWidth) + ":" +
                   (intType->isUnsigned ? "u" : "s");
        }
        if (std::dynamic_pointer_cast<IRVoidType>(type)) return "void";
        if (auto ptrType = std::dynamic_pointer_cast<IRPtrType>(type)) {
            return "p(" + typeShapeKey(ptrType->baseType) + ")";
        }
        if (auto arrType = std::dynamic_pointer_cast<IRArrayType>(type)) {
            return "a" + std::to_string(arrType->length) + "[" +
                   typeShapeKey(arrType->elementType) + "]";
        }
        if (auto structType = std::dynamic_pointer_cast<IRStructType>(type)) {
            if (!structType->true_name.empty()) return "s" + structType->true_name;
            if (!structType->name.empty()) return "s" + structType->name;
            std::string key = "s{";
            for (auto &member : structType->memberTypes) {
                key += typeShapeKey(member.second) + ";";
            }
            key += "}";
            return key;
        }
        return "t" + std::to_string(static_cast<int>(type->type)) + ":" +
               std::to_string(type->size);
    }

    int accessSize(const std::shared_ptr<IRType> &type, bool w64tag) const {
        if (!type) return 0;
        if (w64tag) return 8;
        if (auto intType = std::dynamic_pointer_cast<IRIntType>(type)) {
            return intType->bitWidth == 64 ? 8 : 4;
        }
        return type->size;
    }

    bool storeMentionsVar(const StoreState &store, IRVar *var, const std::string &key) const {
        if (!var) return false;
        if (auto valueVar = std::dynamic_pointer_cast<IRVar>(store.value)) {
            if (valueVar.get() == var) return true;
        }
        return store.access.address.exact == key ||
               (store.access.address.knownRoot && store.access.address.root == key);
    }

    bool isMemoryBarrier(const std::shared_ptr<IRNode> &instr) {
        return std::dynamic_pointer_cast<IRCall>(instr) ||
               std::dynamic_pointer_cast<IRGetint>(instr) ||
               std::dynamic_pointer_cast<IRMemcpy>(instr) ||
               std::dynamic_pointer_cast<IRMemset>(instr);
    }

    void rewriteUses(const std::shared_ptr<IRNode> &instr,
                     const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!instr || replaceMap.empty()) return;
        IRUtil::replaceUses(instr, replaceMap);
        if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
            rewriteStoreValue(store, replaceMap);
        } else if (auto ret = std::dynamic_pointer_cast<IRReturn>(instr)) {
            rewriteReturnValue(ret, replaceMap);
        } else if (auto br = std::dynamic_pointer_cast<IRBr>(instr)) {
            rewriteBranchCondition(br, replaceMap);
        }
    }

    void rewriteStoreValue(const std::shared_ptr<IRStore> &store,
                           const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!store || !store->storeValue) return;
        auto it = replaceMap.find(store->storeValue.get());
        if (it == replaceMap.end()) return;
        if (auto lit = std::dynamic_pointer_cast<IRLiteral>(it->second)) {
            store->storeLiteral = lit;
            store->storeValue = nullptr;
        } else if (auto var = std::dynamic_pointer_cast<IRVar>(it->second)) {
            store->storeValue = var;
        }
    }

    void rewriteReturnValue(const std::shared_ptr<IRReturn> &ret,
                            const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!ret || !ret->returnValue) return;
        auto lit = replacementLiteral(ret->returnValue, replaceMap);
        if (!lit) return;
        ret->returnLiteral = lit;
        ret->returnValue = nullptr;
    }

    void rewriteBranchCondition(const std::shared_ptr<IRBr> &br,
                                const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!br || !br->condition || !br->trueLabel || !br->falseLabel) return;
        auto lit = replacementLiteral(br->condition, replaceMap);
        if (!lit) return;
        br->trueLabel = literalIsTrue(lit) ? br->trueLabel : br->falseLabel;
        br->condition = nullptr;
        br->falseLabel = nullptr;
    }

    std::shared_ptr<IRLiteral> replacementLiteral(const std::shared_ptr<IRVar> &var,
                                                  const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!var) return nullptr;
        auto it = replaceMap.find(var.get());
        if (it == replaceMap.end()) return nullptr;
        return std::dynamic_pointer_cast<IRLiteral>(it->second);
    }

    bool literalIsTrue(const std::shared_ptr<IRLiteral> &lit) {
        if (!lit) return false;
        if (lit->literalType == BOOL_LITERAL) return lit->boolValue || lit->intValue != 0;
        return lit->intValue != 0;
    }
};

} // namespace JaneZ
