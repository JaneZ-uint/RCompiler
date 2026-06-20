#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include "../ir/IRBlock.h"
#include "../ir/IRBr.h"
#include "../ir/IRExit.h"
#include "../ir/IRFunction.h"
#include "../ir/IRImpl.h"
#include "../ir/IRPHI.h"
#include "../ir/IRPhi.h"
#include "../ir/IRReturn.h"
#include "../ir/IRRoot.h"

namespace JaneZ {

class CFGClean {
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
        auto reachable = collectReachable(func);
        removeUnreachableBlocks(func, reachable);
        cleanupPhiInputs(func, reachable);
    }

    std::vector<std::shared_ptr<IRBlock>> orderedBlocks(const std::shared_ptr<IRFunction> &func) {
        std::vector<std::shared_ptr<IRBlock>> blocks;
        if (!func || !func->body) return blocks;
        blocks.push_back(func->body);
        for (auto &blk : func->body->blockList) {
            if (blk) blocks.push_back(blk);
        }
        return blocks;
    }

    std::map<IRBlock*, std::vector<IRBlock*>> buildSuccs(const std::shared_ptr<IRFunction> &func) {
        std::map<IRBlock*, std::vector<IRBlock*>> succs;
        auto blocks = orderedBlocks(func);
        for (auto &blk : blocks) succs[blk.get()] = {};

        for (size_t i = 0; i < blocks.size(); i++) {
            auto &blk = blocks[i];
            if (!blk) continue;
            if (blk->instrList.empty()) {
                if (i + 1 < blocks.size()) succs[blk.get()].push_back(blocks[i + 1].get());
                continue;
            }

            auto last = blk->instrList.back();
            if (auto br = std::dynamic_pointer_cast<IRBr>(last)) {
                addSucc(succs[blk.get()], br->trueLabel.get());
                if (br->falseLabel != br->trueLabel) addSucc(succs[blk.get()], br->falseLabel.get());
            } else if (!std::dynamic_pointer_cast<IRReturn>(last) &&
                       !std::dynamic_pointer_cast<IRExit>(last)) {
                if (i + 1 < blocks.size()) succs[blk.get()].push_back(blocks[i + 1].get());
            }
        }

        return succs;
    }

    void addSucc(std::vector<IRBlock*> &succs, IRBlock *blk) {
        if (!blk) return;
        if (std::find(succs.begin(), succs.end(), blk) == succs.end()) succs.push_back(blk);
    }

    std::set<IRBlock*> collectReachable(const std::shared_ptr<IRFunction> &func) {
        std::set<IRBlock*> reachable;
        auto succs = buildSuccs(func);
        std::vector<IRBlock*> stack;
        stack.push_back(func->body.get());

        while (!stack.empty()) {
            auto *blk = stack.back();
            stack.pop_back();
            if (!blk || !reachable.insert(blk).second) continue;
            for (auto *succ : succs[blk]) {
                if (succ && !reachable.count(succ)) stack.push_back(succ);
            }
        }

        return reachable;
    }

    void removeUnreachableBlocks(const std::shared_ptr<IRFunction> &func,
                                 const std::set<IRBlock*> &reachable) {
        auto &blocks = func->body->blockList;
        blocks.erase(std::remove_if(blocks.begin(), blocks.end(),
                     [&](const std::shared_ptr<IRBlock> &blk) {
                         return !blk || !reachable.count(blk.get());
                     }),
                     blocks.end());
    }

    void cleanupPhiInputs(const std::shared_ptr<IRFunction> &func,
                          const std::set<IRBlock*> &reachable) {
        auto cleanupBlock = [&](const std::shared_ptr<IRBlock> &blk) {
            if (!blk) return;
            for (auto &instr : blk->instrList) {
                if (auto phi = std::dynamic_pointer_cast<IRPHI>(instr)) {
                    cleanupIRPHI(phi, reachable);
                } else if (auto phi = std::dynamic_pointer_cast<IRPhi>(instr)) {
                    cleanupLegacyPhi(phi, reachable);
                }
            }
        };

        cleanupBlock(func->body);
        for (auto &blk : func->body->blockList) cleanupBlock(blk);
    }

    void cleanupIRPHI(const std::shared_ptr<IRPHI> &phi,
                      const std::set<IRBlock*> &reachable) {
        if (!phi) return;
        if (phi->firstBlock && !reachable.count(phi->firstBlock.get())) {
            phi->firstBlock = nullptr;
            phi->firstState = nullptr;
        }
        if (phi->secondBlock && !reachable.count(phi->secondBlock.get())) {
            phi->secondBlock = nullptr;
            phi->secondState = nullptr;
        }
        phi->entries.erase(std::remove_if(phi->entries.begin(), phi->entries.end(),
                           [&](const auto &entry) {
                               return !entry.second || !reachable.count(entry.second.get());
                           }),
                           phi->entries.end());
    }

    void cleanupLegacyPhi(const std::shared_ptr<IRPhi> &phi,
                          const std::set<IRBlock*> &reachable) {
        if (!phi) return;
        if (phi->firstBlock && !reachable.count(phi->firstBlock.get())) {
            phi->firstBlock = nullptr;
        }
        if (phi->secondBlock && !reachable.count(phi->secondBlock.get())) {
            phi->secondBlock = nullptr;
            phi->secondState = nullptr;
        }
    }
};

} // namespace JaneZ
