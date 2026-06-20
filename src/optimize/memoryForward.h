#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include "../ir/IRFunction.h"
#include "../ir/IRImpl.h"
#include "../ir/IRLiteral.h"
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

    struct StoreState {
        ValuePtr value;
        std::shared_ptr<IRStore> instr;
    };

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        optimizeBlock(func->body);
        for (auto &blk : func->body->blockList) optimizeBlock(blk);
    }

    void optimizeBlock(const std::shared_ptr<IRBlock> &blk) {
        if (!blk) return;
        std::map<std::string, StoreState> lastStore;
        std::map<IRVar*, ValuePtr> replaceMap;
        std::set<IRNode*> toRemove;

        for (auto &instr : blk->instrList) {
            rewriteUses(instr, replaceMap);

            if (auto load = std::dynamic_pointer_cast<IRLoad>(instr)) {
                processLoad(load, lastStore, replaceMap);
                continue;
            }

            if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
                processStore(store, lastStore, toRemove);
                continue;
            }

            if (isMemoryBarrier(instr)) {
                lastStore.clear();
            }
        }

        if (!toRemove.empty()) {
            blk->instrList.erase(std::remove_if(blk->instrList.begin(), blk->instrList.end(),
                [&](const std::shared_ptr<IRNode> &instr) {
                    return toRemove.count(instr.get()) > 0;
                }),
                blk->instrList.end());
        }
    }

    void processLoad(const std::shared_ptr<IRLoad> &load,
                     std::map<std::string, StoreState> &lastStore,
                     std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!load || !load->tmp) {
            lastStore.clear();
            return;
        }
        auto key = addressKey(load->addressVar);
        auto it = key.empty() ? lastStore.end() : lastStore.find(key);
        if (it != lastStore.end() && it->second.value) {
            replaceMap[load->tmp.get()] = it->second.value;
        } else {
            replaceMap.erase(load->tmp.get());
        }
        lastStore.clear();
    }

    void processStore(const std::shared_ptr<IRStore> &store,
                      std::map<std::string, StoreState> &lastStore,
                      std::set<IRNode*> &toRemove) {
        if (!store) {
            lastStore.clear();
            return;
        }
        auto key = addressKey(store->address);
        auto value = storeValue(store);

        auto prev = key.empty() ? lastStore.end() : lastStore.find(key);
        if (prev != lastStore.end() && prev->second.instr) {
            toRemove.insert(prev->second.instr.get());
        }

        lastStore.clear();
        if (!key.empty() && value) {
            lastStore[key] = StoreState{value, store};
        }
    }

    ValuePtr storeValue(const std::shared_ptr<IRStore> &store) {
        if (!store) return nullptr;
        if (store->storeLiteral) return store->storeLiteral;
        return store->storeValue;
    }

    std::string addressKey(const std::shared_ptr<IRVar> &address) {
        if (!address) return "";
        return "v" + std::to_string(reinterpret_cast<uintptr_t>(address.get()));
    }

    bool isMemoryBarrier(const std::shared_ptr<IRNode> &instr) {
        return std::dynamic_pointer_cast<IRCall>(instr) ||
               std::dynamic_pointer_cast<IRGetint>(instr) ||
               std::dynamic_pointer_cast<IRMemcpy>(instr) ||
               std::dynamic_pointer_cast<IRMemset>(instr) ||
               std::dynamic_pointer_cast<IRBr>(instr) ||
               std::dynamic_pointer_cast<IRReturn>(instr) ||
               std::dynamic_pointer_cast<IRExit>(instr);
    }

    void rewriteUses(const std::shared_ptr<IRNode> &instr,
                     const std::map<IRVar*, ValuePtr> &replaceMap) {
        if (!instr || replaceMap.empty()) return;
        IRUtil::replaceUses(instr, replaceMap);
        if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
            rewriteStoreValue(store, replaceMap);
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
};

} // namespace JaneZ
