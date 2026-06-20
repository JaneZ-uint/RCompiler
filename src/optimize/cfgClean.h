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
#include "IRUtil.h"

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
        simplifyPhiNodes(func);
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

    void simplifyPhiNodes(const std::shared_ptr<IRFunction> &func) {
        std::map<IRVar*, std::shared_ptr<IRValue>> replaceMap;
        collectSimplifiedPhi(func->body, replaceMap);
        for (auto &blk : func->body->blockList) collectSimplifiedPhi(blk, replaceMap);
        if (replaceMap.empty()) return;

        applyReplacements(func->body, replaceMap);
        for (auto &blk : func->body->blockList) applyReplacements(blk, replaceMap);
    }

    void collectSimplifiedPhi(const std::shared_ptr<IRBlock> &blk,
                              std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
        if (!blk) return;
        for (auto &instr : blk->instrList) {
            if (auto phi = std::dynamic_pointer_cast<IRPHI>(instr)) {
                if (!phi->result) continue;
                auto replacement = singlePhiValue(phi);
                if (replacement) replaceMap[phi->result.get()] = replacement;
            } else if (auto phi = std::dynamic_pointer_cast<IRPhi>(instr)) {
                if (!phi->result) continue;
                auto replacement = singleLegacyPhiValue(phi);
                if (replacement) replaceMap[phi->result.get()] = replacement;
            }
        }
    }

    std::shared_ptr<IRValue> singlePhiValue(const std::shared_ptr<IRPHI> &phi) {
        std::shared_ptr<IRValue> first = nullptr;
        int valueCount = 0;

        auto consider = [&](const std::shared_ptr<IRValue> &value) -> bool {
            if (!value) return true;
            valueCount++;
            if (!first) {
                first = value;
                return true;
            }
            return sameValue(first, value);
        };

        if (!phi->entries.empty()) {
            for (auto &entry : phi->entries) {
                if (!consider(entry.first)) return nullptr;
            }
        } else {
            if (!consider(phi->firstState)) return nullptr;
            if (!consider(phi->secondState)) return nullptr;
        }

        if (valueCount == 0) return nullptr;
        return first;
    }

    std::shared_ptr<IRValue> singleLegacyPhiValue(const std::shared_ptr<IRPhi> &phi) {
        if (!phi) return nullptr;
        std::shared_ptr<IRValue> first = nullptr;
        int valueCount = 0;

        auto consider = [&](const std::shared_ptr<IRValue> &value) -> bool {
            if (!value) return true;
            valueCount++;
            if (!first) {
                first = value;
                return true;
            }
            return sameValue(first, value);
        };

        if (phi->firstBlock) {
            auto firstValue = std::make_shared<IRLiteral>(BOOL_LITERAL, phi->firstState ? 1 : 0, phi->firstState);
            if (!consider(firstValue)) return nullptr;
        }
        if (phi->secondBlock) {
            if (!consider(phi->secondState)) return nullptr;
        }

        if (valueCount == 0) return nullptr;
        return first;
    }

    bool sameValue(const std::shared_ptr<IRValue> &lhs,
                   const std::shared_ptr<IRValue> &rhs) {
        if (lhs == rhs) return true;
        auto lv = std::dynamic_pointer_cast<IRVar>(lhs);
        auto rv = std::dynamic_pointer_cast<IRVar>(rhs);
        if (lv || rv) return lv && rv && lv.get() == rv.get();
        auto ll = std::dynamic_pointer_cast<IRLiteral>(lhs);
        auto rl = std::dynamic_pointer_cast<IRLiteral>(rhs);
        return ll && rl && ll->literalType == rl->literalType &&
               ll->intValue == rl->intValue && ll->boolValue == rl->boolValue;
    }

    void applyReplacements(const std::shared_ptr<IRBlock> &blk,
                           const std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
        if (!blk) return;
        for (auto &instr : blk->instrList) {
            applyLiteralReplacement(instr, replaceMap);
            IRUtil::replaceUses(instr, replaceMap);
        }
    }

    void applyLiteralReplacement(const std::shared_ptr<IRNode> &instr,
                                 const std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
        if (!instr || replaceMap.empty()) return;
        if (auto ret = std::dynamic_pointer_cast<IRReturn>(instr)) {
            if (!ret->returnValue) return;
            auto lit = replacementLiteral(ret->returnValue, replaceMap);
            if (!lit) return;
            ret->returnLiteral = lit;
            ret->returnValue = nullptr;
        } else if (auto store = std::dynamic_pointer_cast<IRStore>(instr)) {
            if (!store->storeValue) return;
            auto lit = replacementLiteral(store->storeValue, replaceMap);
            if (!lit) return;
            store->storeLiteral = lit;
            store->storeValue = nullptr;
        } else if (auto br = std::dynamic_pointer_cast<IRBr>(instr)) {
            if (!br->condition || !br->trueLabel || !br->falseLabel) return;
            auto lit = replacementLiteral(br->condition, replaceMap);
            if (!lit) return;
            br->trueLabel = literalIsTrue(lit) ? br->trueLabel : br->falseLabel;
            br->condition = nullptr;
            br->falseLabel = nullptr;
        }
    }

    std::shared_ptr<IRLiteral> replacementLiteral(const std::shared_ptr<IRVar> &var,
                                                  const std::map<IRVar*, std::shared_ptr<IRValue>> &replaceMap) {
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
