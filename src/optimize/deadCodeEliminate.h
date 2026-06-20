#pragma once

#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include "../ir/IRFunction.h"
#include "../ir/IRImpl.h"
#include "../ir/IRRoot.h"
#include "IRUtil.h"

namespace JaneZ {

class DeadCodeEliminate {
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

        bool changed = true;
        while (changed) {
            changed = false;
            std::set<IRVar*> live;
            std::map<IRVar*, std::shared_ptr<IRNode>> defInstr;
            std::vector<std::shared_ptr<IRNode>> allInstrs;

            IRUtil::forEachInstruction(func, [&](const std::shared_ptr<IRNode> &instr) {
                allInstrs.push_back(instr);
                for (auto &def : IRUtil::defs(instr)) defInstr[def.get()] = instr;
            });

            std::vector<std::shared_ptr<IRVar>> worklist;
            auto markLive = [&](const std::shared_ptr<IRVar> &var) {
                if (!var) return;
                if (live.insert(var.get()).second) worklist.push_back(var);
            };

            for (auto &instr : allInstrs) {
                if (!IRUtil::hasSideEffect(instr)) continue;
                for (auto &use : IRUtil::uses(instr)) markLive(use);
            }

            while (!worklist.empty()) {
                auto var = worklist.back();
                worklist.pop_back();
                auto it = defInstr.find(var.get());
                if (it == defInstr.end()) continue;
                for (auto &use : IRUtil::uses(it->second)) markLive(use);
            }

            auto removeDead = [&](std::vector<std::shared_ptr<IRNode>> &instrList) {
                auto oldSize = instrList.size();
                instrList.erase(
                    std::remove_if(instrList.begin(), instrList.end(),
                        [&](const std::shared_ptr<IRNode> &instr) {
                            if (!IRUtil::isPureRemovable(instr)) return false;
                            for (auto &def : IRUtil::defs(instr)) {
                                if (def && live.count(def.get())) return false;
                            }
                            return true;
                        }),
                    instrList.end());
                if (instrList.size() != oldSize) changed = true;
            };

            removeDead(func->body->instrList);
            for (auto &blk : func->body->blockList) {
                if (blk) removeDead(blk->instrList);
            }
        }
    }
};

} // namespace JaneZ
