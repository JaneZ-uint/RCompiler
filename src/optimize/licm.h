#pragma once

#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <set>
#include <vector>
#include "../ir/IRBinaryop.h"
#include "../ir/IRBlock.h"
#include "../ir/IRBr.h"
#include "../ir/IRCall.h"
#include "../ir/IRExit.h"
#include "../ir/IRFunction.h"
#include "../ir/IRGetptr.h"
#include "../ir/IRGetint.h"
#include "../ir/IRImpl.h"
#include "../ir/IRLiteral.h"
#include "../ir/IRMem.h"
#include "../ir/IRReturn.h"
#include "../ir/IRRoot.h"
#include "../ir/IRSext.h"
#include "../ir/IRTrunc.h"
#include "../ir/IRValue.h"
#include "../ir/IRVar.h"
#include "../ir/IRZext.h"
#include "IRUtil.h"

namespace JaneZ {

class LICM {
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
    struct LoopInfo {
        IRBlock *header = nullptr;
        IRBlock *preheader = nullptr;
        std::set<IRBlock*> blocks;
    };

    std::vector<std::shared_ptr<IRBlock>> blocks;
    std::map<IRBlock*, std::vector<IRBlock*>> succs;
    std::map<IRBlock*, std::vector<IRBlock*>> preds;
    std::map<IRBlock*, IRBlock*> idom;
    std::vector<IRBlock*> rpo;
    std::map<IRBlock*, int> rpoIndex;

    void optimizeFunc(const std::shared_ptr<IRFunction> &func) {
        if (!func || !func->body) return;
        buildCFG(func);
        computeRPO(func->body.get());
        if (rpo.empty()) return;
        buildDomTree(func->body.get());

        auto loops = findLoops();
        std::sort(loops.begin(), loops.end(), [](const LoopInfo &lhs, const LoopInfo &rhs) {
            return lhs.blocks.size() < rhs.blocks.size();
        });

        for (auto &loop : loops) {
            if (!loop.preheader) continue;
            if (hasCallLikeBarrier(loop)) continue;
            hoistLoop(loop);
        }
    }

    void buildCFG(const std::shared_ptr<IRFunction> &func) {
        blocks.clear();
        succs.clear();
        preds.clear();
        idom.clear();
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
        for (int i = 0; i < static_cast<int>(rpo.size()); i++) rpoIndex[rpo[i]] = i;
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
    }

    bool dominates(IRBlock *dom, IRBlock *blk) const {
        if (!dom || !blk || !idom.count(blk)) return false;
        auto *cur = blk;
        while (cur && cur != idom.at(cur)) {
            if (cur == dom) return true;
            auto it = idom.find(cur);
            if (it == idom.end()) return false;
            cur = it->second;
        }
        return cur == dom;
    }

    std::vector<LoopInfo> findLoops() {
        std::map<IRBlock*, std::set<IRBlock*>> loopsByHeader;

        for (auto *tail : rpo) {
            for (auto *header : succs[tail]) {
                if (!dominates(header, tail)) continue;
                auto loopBlocks = collectNaturalLoop(header, tail);
                auto &merged = loopsByHeader[header];
                merged.insert(loopBlocks.begin(), loopBlocks.end());
            }
        }

        std::vector<LoopInfo> loops;
        for (auto &entry : loopsByHeader) {
            LoopInfo loop;
            loop.header = entry.first;
            loop.blocks = std::move(entry.second);
            loop.preheader = uniquePreheader(loop);
            loops.push_back(std::move(loop));
        }
        return loops;
    }

    std::set<IRBlock*> collectNaturalLoop(IRBlock *header, IRBlock *tail) {
        std::set<IRBlock*> loopBlocks;
        std::vector<IRBlock*> worklist;
        loopBlocks.insert(header);
        worklist.push_back(tail);

        while (!worklist.empty()) {
            auto *blk = worklist.back();
            worklist.pop_back();
            if (!blk || !loopBlocks.insert(blk).second) continue;
            for (auto *pred : preds[blk]) {
                if (!loopBlocks.count(pred)) worklist.push_back(pred);
            }
        }

        return loopBlocks;
    }

    IRBlock *uniquePreheader(const LoopInfo &loop) const {
        if (!loop.header) return nullptr;
        IRBlock *preheader = nullptr;
        for (auto *pred : preds.at(loop.header)) {
            if (loop.blocks.count(pred)) continue;
            if (preheader && preheader != pred) return nullptr;
            preheader = pred;
        }
        if (!preheader) return nullptr;
        auto succIt = succs.find(preheader);
        if (succIt == succs.end() || succIt->second.size() != 1 ||
            succIt->second.front() != loop.header) {
            return nullptr;
        }
        return preheader;
    }

    bool hasCallLikeBarrier(const LoopInfo &loop) const {
        for (auto *blk : loop.blocks) {
            if (!blk) continue;
            for (auto &instr : blk->instrList) {
                if (std::dynamic_pointer_cast<IRCall>(instr) ||
                    std::dynamic_pointer_cast<IRGetint>(instr) ||
                    std::dynamic_pointer_cast<IRMemcpy>(instr) ||
                    std::dynamic_pointer_cast<IRMemset>(instr)) {
                    return true;
                }
            }
        }
        return false;
    }

    void hoistLoop(const LoopInfo &loop) {
        auto defBlock = buildDefBlockMap();
        std::set<IRVar*> hoistedDefs;
        std::vector<std::pair<IRBlock*, std::shared_ptr<IRNode>>> hoisted;
        std::set<IRNode*> selected;

        bool changed = true;
        while (changed) {
            changed = false;
            for (auto *blk : rpo) {
                if (!loop.blocks.count(blk)) continue;
                for (auto &instr : blk->instrList) {
                    if (!instr || selected.count(instr.get())) continue;
                    auto result = hoistResult(instr);
                    if (!result || hoistedDefs.count(result.get())) continue;
                    if (!isHoistable(instr, loop, defBlock, hoistedDefs)) continue;
                    selected.insert(instr.get());
                    hoistedDefs.insert(result.get());
                    hoisted.push_back({blk, instr});
                    changed = true;
                }
            }
        }

        if (hoisted.empty()) return;
        removeHoisted(hoisted, selected);
        insertIntoPreheader(loop.preheader, hoisted);
    }

    std::map<IRVar*, IRBlock*> buildDefBlockMap() const {
        std::map<IRVar*, IRBlock*> defBlock;
        for (auto &blk : blocks) {
            if (!blk) continue;
            for (auto &instr : blk->instrList) {
                for (auto &def : IRUtil::defs(instr)) {
                    if (def) defBlock[def.get()] = blk.get();
                }
            }
        }
        return defBlock;
    }

    std::shared_ptr<IRVar> hoistResult(const std::shared_ptr<IRNode> &instr) const {
        if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
            return profitableBinary(op) ? op->result : nullptr;
        }
        if (auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr)) return getptr->res;
        return nullptr;
    }

    bool isHoistable(const std::shared_ptr<IRNode> &instr,
                     const LoopInfo &loop,
                     const std::map<IRVar*, IRBlock*> &defBlock,
                     const std::set<IRVar*> &hoistedDefs) const {
        if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) {
            if (!safeBinary(op)) return false;
            return valueInvariant(op->leftValue, loop, defBlock, hoistedDefs) &&
                   valueInvariant(op->rightValue, loop, defBlock, hoistedDefs);
        }
        if (auto getptr = std::dynamic_pointer_cast<IRGetptr>(instr)) {
            return varInvariant(getptr->base, loop, defBlock, hoistedDefs) &&
                   varInvariant(getptr->index, loop, defBlock, hoistedDefs);
        }
        return false;
    }

    bool safeBinary(const std::shared_ptr<IRBinaryop> &op) const {
        if (!op) return false;
        if (op->op != DIV && op->op != MOD) return true;
        auto rhs = std::dynamic_pointer_cast<IRLiteral>(op->rightValue);
        return rhs && literalValue(rhs) != 0;
    }

    bool profitableBinary(const std::shared_ptr<IRBinaryop> &op) const {
        if (!op) return false;
        switch (op->op) {
            case MUL:
            case DIV:
            case MOD:
            case LEFTSHIFTOP:
            case RIGHTSHIFTOP:
                return true;
            default:
                return false;
        }
    }

    bool valueInvariant(const std::shared_ptr<IRValue> &value,
                        const LoopInfo &loop,
                        const std::map<IRVar*, IRBlock*> &defBlock,
                        const std::set<IRVar*> &hoistedDefs) const {
        if (!value) return true;
        if (std::dynamic_pointer_cast<IRLiteral>(value)) return true;
        return varInvariant(std::dynamic_pointer_cast<IRVar>(value), loop, defBlock, hoistedDefs);
    }

    bool varInvariant(const std::shared_ptr<IRVar> &var,
                      const LoopInfo &loop,
                      const std::map<IRVar*, IRBlock*> &defBlock,
                      const std::set<IRVar*> &hoistedDefs) const {
        if (!var) return true;
        if (hoistedDefs.count(var.get())) return true;
        auto it = defBlock.find(var.get());
        if (it == defBlock.end()) return true;
        return !loop.blocks.count(it->second);
    }

    void removeHoisted(const std::vector<std::pair<IRBlock*, std::shared_ptr<IRNode>>> &hoisted,
                       const std::set<IRNode*> &selected) {
        std::set<IRBlock*> touched;
        for (auto &entry : hoisted) touched.insert(entry.first);
        for (auto *blk : touched) {
            if (!blk) continue;
            blk->instrList.erase(std::remove_if(blk->instrList.begin(), blk->instrList.end(),
                [&](const std::shared_ptr<IRNode> &instr) {
                    return instr && selected.count(instr.get());
                }),
                blk->instrList.end());
        }
    }

    void insertIntoPreheader(IRBlock *preheader,
                             const std::vector<std::pair<IRBlock*, std::shared_ptr<IRNode>>> &hoisted) {
        if (!preheader) return;
        auto insertPos = preheader->instrList.end();
        if (!preheader->instrList.empty() && isTerminator(preheader->instrList.back())) {
            insertPos = preheader->instrList.end() - 1;
        }
        for (auto &entry : hoisted) {
            insertPos = preheader->instrList.insert(insertPos, entry.second);
            ++insertPos;
        }
    }

    bool isTerminator(const std::shared_ptr<IRNode> &instr) const {
        return std::dynamic_pointer_cast<IRBr>(instr) ||
               std::dynamic_pointer_cast<IRReturn>(instr) ||
               std::dynamic_pointer_cast<IRExit>(instr);
    }

    long long literalValue(const std::shared_ptr<IRLiteral> &lit) const {
        if (!lit) return 0;
        if (lit->literalType == BOOL_LITERAL) return lit->boolValue || lit->intValue;
        return lit->intValue;
    }
};

} // namespace JaneZ
