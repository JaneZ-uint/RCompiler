#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <vector>
#include "../ir/IRRoot.h"
#include "../ir/IRFunction.h"
#include "../ir/IRVar.h"
#include "../ir/IRBlock.h"
#include "../ir/IRAlloca.h"
#include "../ir/IRStore.h"
#include "../ir/IRLoad.h"
#include "../ir/IRGetptr.h"
#include "../ir/IRBinaryop.h"
#include "../ir/IRBr.h"
#include "../ir/IRReturn.h"
#include "../ir/IRCall.h"
#include "../ir/IRParam.h"
#include "../ir/IRPrint.h"
#include "../ir/IRGetint.h"
#include "../ir/IRSext.h"
#include "../ir/IRZext.h"
#include "../ir/IRTrunc.h"
#include "../ir/IRPhi.h"
#include "../ir/IRPHI.h"
#include "../ir/IRMem.h"
#include "../ir/IRExit.h"
#include "../ir/IRLiteral.h"

namespace JaneZ {

class DominantTree {
public:
    void optimize(std::shared_ptr<IRRoot> root) {
        for (auto &func : root->children) {
            if (auto *p = dynamic_cast<IRFunction*>(&*func)) {
                for (auto &childFunc : p->funcList) {
                    if (auto cf = std::dynamic_pointer_cast<IRFunction>(childFunc))
                        optimizeFunc(cf);
                }
                optimizeFunc(std::dynamic_pointer_cast<IRFunction>(func));
            }
        }
    }

private:
    using BlockPtr = std::shared_ptr<IRBlock>;
    using VarPtr = std::shared_ptr<IRVar>;
    using ValuePtr = std::shared_ptr<IRValue>;

    std::vector<BlockPtr> allBlocks;
    std::map<IRBlock*, std::vector<IRBlock*>> succs;
    std::map<IRBlock*, std::vector<IRBlock*>> preds;
    std::map<IRBlock*, IRBlock*> idom;
    std::map<IRBlock*, std::vector<IRBlock*>> domChildren;
    std::map<IRBlock*, std::set<IRBlock*>> domFrontier;
    std::vector<IRBlock*> rpo;
    std::map<IRBlock*, int> rpoIndex;
    std::map<IRBlock*, BlockPtr> rawToShared;

    void optimizeFunc(std::shared_ptr<IRFunction> func) {
        if (!func || !func->body) return;

        buildCFG(func);
        if (allBlocks.empty()) return;

        computeRPO(func->body.get());
        if (rpo.empty()) return;

        buildDomTree(func->body.get());
        computeDomFrontier();
        promoteAllocas(func);
    }

    void buildCFG(std::shared_ptr<IRFunction> func) {
        allBlocks.clear();
        succs.clear();
        preds.clear();
        rawToShared.clear();

        allBlocks.push_back(func->body);
        rawToShared[func->body.get()] = func->body;
        for (auto &blk : func->body->blockList) {
            allBlocks.push_back(blk);
            rawToShared[blk.get()] = blk;
        }

        for (auto &blk : allBlocks) {
            succs[blk.get()] = {};
            preds[blk.get()] = {};
        }

        for (size_t idx = 0; idx < allBlocks.size(); idx++) {
            auto &blk = allBlocks[idx];
            if (blk->instrList.empty()) {
                if (idx + 1 < allBlocks.size()) {
                    auto &nextBlk = allBlocks[idx + 1];
                    auto *next = nextBlk.get();
                    succs[blk.get()].push_back(next);
                    preds[next].push_back(blk.get());
                    auto br = std::make_shared<IRBr>();
                    br->trueLabel = nextBlk;
                    blk->instrList.push_back(br);
                }
                continue;
            }
            auto &last = blk->instrList.back();
            if (auto *br = dynamic_cast<IRBr*>(&*last)) {
                if (br->trueLabel) {
                    succs[blk.get()].push_back(br->trueLabel.get());
                    preds[br->trueLabel.get()].push_back(blk.get());
                }
                if (br->falseLabel && br->falseLabel != br->trueLabel) {
                    succs[blk.get()].push_back(br->falseLabel.get());
                    preds[br->falseLabel.get()].push_back(blk.get());
                }
            } else if (!dynamic_cast<IRReturn*>(&*last) && !dynamic_cast<IRExit*>(&*last)) {
                if (idx + 1 < allBlocks.size()) {
                    auto &nextBlk = allBlocks[idx + 1];
                    auto *next = nextBlk.get();
                    succs[blk.get()].push_back(next);
                    preds[next].push_back(blk.get());
                    auto br = std::make_shared<IRBr>();
                    br->trueLabel = nextBlk;
                    blk->instrList.push_back(br);
                }
            }
        }
    }

    void computeRPO(IRBlock *entry) {
        rpo.clear();
        rpoIndex.clear();

        std::set<IRBlock*> visited;
        std::vector<IRBlock*> postorder;

        std::function<void(IRBlock*)> dfs = [&](IRBlock *blk) {
            visited.insert(blk);
            for (auto *s : succs[blk]) {
                if (!visited.count(s)) dfs(s);
            }
            postorder.push_back(blk);
        };
        dfs(entry);

        rpo.assign(postorder.rbegin(), postorder.rend());
        for (int i = 0; i < (int)rpo.size(); i++) {
            rpoIndex[rpo[i]] = i;
        }
    }

    IRBlock* intersect(IRBlock *b1, IRBlock *b2) {
        auto *f1 = b1, *f2 = b2;
        while (f1 != f2) {
            while (rpoIndex[f1] > rpoIndex[f2]) f1 = idom[f1];
            while (rpoIndex[f2] > rpoIndex[f1]) f2 = idom[f2];
        }
        return f1;
    }

    void buildDomTree(IRBlock *entry) {
        idom.clear();
        domChildren.clear();
        idom[entry] = entry;

        bool changed = true;
        while (changed) {
            changed = false;
            for (auto *blk : rpo) {
                if (blk == entry) continue;
                IRBlock *newIdom = nullptr;
                for (auto *p : preds[blk]) {
                    if (!idom.count(p)) continue;
                    if (!newIdom) { 
                        newIdom = p; 
                    }
                    else { 
                        newIdom = intersect(p, newIdom); 
                    }
                }
                if (newIdom && idom[blk] != newIdom) {
                    idom[blk] = newIdom;
                    changed = true;
                }
            }
        }

        for (auto *blk : rpo) {
            if (blk == entry) continue;
            if (idom.count(blk)) domChildren[idom[blk]].push_back(blk);
        }
    }

    void computeDomFrontier() {
        domFrontier.clear();
        for (auto *blk : rpo) {
            if (preds[blk].size() < 2) continue;
            for (auto *p : preds[blk]) {
                auto *runner = p;
                while (runner && runner != idom[blk]) {
                    domFrontier[runner].insert(blk);
                    runner = idom[runner];
                }
            }
        }
    }

    void forEachInstr(std::shared_ptr<IRFunction> func,
                      const std::function<void(const std::shared_ptr<IRNode>&)> &fn) {
        for (auto &instr : func->body->instrList) {
            fn(instr);
        }
        for (auto &blk : func->body->blockList){
            for (auto &instr : blk->instrList) {
                fn(instr);
            }
        }
    }

    struct AllocaInfo {
        VarPtr allocaVar;
        std::shared_ptr<IRType> allocaType;
        std::set<IRBlock*> defBlocks;
        std::set<IRBlock*> useBlocks;
    };

    void promoteAllocas(std::shared_ptr<IRFunction> func) {
        std::set<IRVar*> allocaVars;
        std::map<IRVar*, AllocaInfo> infoMap;

        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr) {
            if (auto *p = dynamic_cast<IRAlloca*>(&*instr)) {
                allocaVars.insert(p->var.get());
                AllocaInfo info;
                info.allocaVar = p->var;
                info.allocaType = p->allocatedType;
                infoMap[p->var.get()] = info;
            }
        });
        if (allocaVars.empty()) return;

        std::set<IRVar*> escaped;
        auto markEscape = [&](const VarPtr &var) {
            if (var && allocaVars.count(var.get())) escaped.insert(var.get());
        };
        auto markEscapeVal = [&](const ValuePtr &val) {
            if (auto var = std::dynamic_pointer_cast<IRVar>(val)) markEscape(var);
        };

        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr) {
            if (dynamic_cast<IRAlloca*>(&*instr)) return;
            if (auto *p = dynamic_cast<IRStore*>(&*instr)) {
                if (!(p->address && allocaVars.count(p->address.get()))) markEscape(p->address);
                markEscape(p->storeValue);
            } else if (dynamic_cast<IRLoad*>(&*instr)) {
            } else if (auto *p = dynamic_cast<IRGetptr*>(&*instr)) {
                markEscape(p->base); markEscape(p->res); markEscape(p->index);
            } else if (auto *p = dynamic_cast<IRBinaryop*>(&*instr)) {
                markEscapeVal(p->leftValue); markEscapeVal(p->rightValue); markEscape(p->result);
            } else if (auto *p = dynamic_cast<IRBr*>(&*instr)) {
                markEscape(p->condition);
            } else if (auto *p = dynamic_cast<IRReturn*>(&*instr)) {
                markEscape(p->returnValue);
            } else if (auto *p = dynamic_cast<IRCall*>(&*instr)) {
                markEscape(p->retVar);
                if (p->pList)
                    for (auto &param : p->pList->paramList)
                        if (auto var = std::dynamic_pointer_cast<IRVar>(param)) markEscape(var);
            } else if (auto *p = dynamic_cast<IRPrint*>(&*instr)) {
                markEscapeVal(p->printVar);
            } else if (auto *p = dynamic_cast<IRGetint*>(&*instr)) {
                markEscape(p->result);
            } else if (auto *p = dynamic_cast<IRSext*>(&*instr)) {
                markEscape(p->value); markEscape(p->result);
            } else if (auto *p = dynamic_cast<IRZext*>(&*instr)) {
                markEscape(p->value); markEscape(p->result);
            } else if (auto *p = dynamic_cast<IRTrunc*>(&*instr)) {
                markEscape(p->value); markEscape(p->result);
            } else if (auto *p = dynamic_cast<IRPhi*>(&*instr)) {
                markEscape(p->result); markEscape(p->secondState);
            } else if (auto *p = dynamic_cast<IRPHI*>(&*instr)) {
                markEscape(p->result); markEscapeVal(p->firstState); markEscapeVal(p->secondState);
                for (auto &e : p->entries) markEscapeVal(e.first);
            } else if (auto *p = dynamic_cast<IRMemset*>(&*instr)) {
                markEscape(p->dest);
            } else if (auto *p = dynamic_cast<IRMemcpy*>(&*instr)) {
                markEscape(p->dest); markEscape(p->value);
            } else if (auto *p = dynamic_cast<IRExit*>(&*instr)) {
                markEscapeVal(p->exitCode);
            }
        });

        std::set<IRVar*> promotable;
        for (auto *av : allocaVars) {
            if (escaped.count(av)) continue;
            auto &info = infoMap[av];
            if (dynamic_cast<IRArrayType*>(&*info.allocaType)) continue;
            if (dynamic_cast<IRStructType*>(&*info.allocaType)) continue;
            if (dynamic_cast<IRPtrType*>(&*info.allocaType)) continue;
            promotable.insert(av);
        }
        if (promotable.empty()) return;

        convertLiteralStores(func, promotable, infoMap);
        collectDefUse(func, promotable, infoMap);

        std::map<IRVar*, std::set<IRBlock*>> phiBlocks;
        for (auto *av : promotable) {
            std::queue<IRBlock*> worklist;
            std::set<IRBlock*> inWL, hasPhi;
            for (auto *db : infoMap[av].defBlocks) {
                worklist.push(db);
                inWL.insert(db);
            }
            while (!worklist.empty()) {
                auto *b = worklist.front(); 
                worklist.pop();
                for (auto *df : domFrontier[b]) {
                    if (hasPhi.insert(df).second) {
                        phiBlocks[av].insert(df);
                        if (inWL.insert(df).second) worklist.push(df);
                    }
                }
            }
        }

        std::map<std::pair<IRVar*, IRBlock*>, std::shared_ptr<IRPHI>> phiNodes;
        std::map<std::pair<IRVar*, IRBlock*>, VarPtr> phiVars;

        for (auto *av : promotable) {
            for (auto *blk : phiBlocks[av]) {
                auto phi = std::make_shared<IRPHI>();
                auto rv = std::make_shared<IRVar>();
                rv->type = infoMap[av].allocaType;
                phi->result = rv;
                phiNodes[{av, blk}] = phi;
                phiVars[{av, blk}] = rv;
                blk->instrList.insert(blk->instrList.begin(), phi);
            }
        }

        std::map<IRVar*, std::vector<ValuePtr>> stacks;
        for (auto *av : promotable) {
            auto undef = std::make_shared<IRVar>();
            undef->type = infoMap[av].allocaType;
            auto init = std::make_shared<IRBinaryop>(ADD, undef);
            init->leftValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
            init->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
            func->body->instrList.insert(func->body->instrList.begin(), init);
            stacks[av].push_back(undef);
        }

        std::map<IRVar*, ValuePtr> replaceMap;
        std::set<IRNode*> toRemove;

        std::function<void(IRBlock*)> rename = [&](IRBlock *blk) {
            std::map<IRVar*, int> pushCnt;

            for (auto *av : promotable) {
                auto key = std::make_pair(av, blk);
                if (phiVars.count(key)) {
                    stacks[av].push_back(phiVars[key]);
                    pushCnt[av]++;
                }
            }

            for (auto &instr : blk->instrList) {
                if (dynamic_cast<IRPHI*>(&*instr)) {
                    bool isOurs = false;
                    for (auto *av : promotable) {
                        if (phiNodes.count({av, blk}) && phiNodes[{av, blk}].get() == &*instr) {
                            isOurs = true; break;
                        }
                    }
                    if (isOurs) continue;
                }

                if (auto *store = dynamic_cast<IRStore*>(&*instr)) {
                    if (store->address && promotable.count(store->address.get())) {
                        auto *av = store->address.get();
                        if (store->storeValue) {
                            stacks[av].push_back(store->storeValue);
                            pushCnt[av]++;
                        }
                        toRemove.insert(store);
                    }
                } else if (auto *load = dynamic_cast<IRLoad*>(&*instr)) {
                    if (load->addressVar && promotable.count(load->addressVar.get())) {
                        auto *av = load->addressVar.get();
                        if (!stacks[av].empty()) {
                            replaceMap[load->tmp.get()] = stacks[av].back();
                        }
                        toRemove.insert(load);
                    }
                }
            }

            for (auto *s : succs[blk]) {
                for (auto *av : promotable) {
                    auto key = std::make_pair(av, s);
                    if (phiNodes.count(key)) {
                        ValuePtr val;
                        if (!stacks[av].empty()) val = stacks[av].back();
                        phiNodes[key]->entries.push_back({val, rawToShared[blk]});
                    }
                }
            }

            for (auto *child : domChildren[blk]) rename(child);

            for (auto &[av, cnt] : pushCnt) {
                for (int i = 0; i < cnt; i++) stacks[av].pop_back();
            }
        };

        rename(func->body.get());

        for (auto *av : promotable) {
            for (auto *blk : phiBlocks[av]) {
                auto &phi = phiNodes[{av, blk}];
                if (phi->entries.empty()) {
                    toRemove.insert(phi.get());
                    continue;
                }
                bool allSame = true;
                auto &first = phi->entries[0].first;
                for (size_t i = 1; i < phi->entries.size(); i++) {
                    if (phi->entries[i].first != first) { allSame = false; break; }
                }
                if (allSame && first) {
                    replaceMap[phi->result.get()] = first;
                    toRemove.insert(phi.get());
                }
            }
        }

        for (auto &[key, val] : replaceMap) {
            auto cur = val;
            int limit = 100;
            while (limit-- > 0) {
                auto curVar = std::dynamic_pointer_cast<IRVar>(cur);
                if (!curVar || !replaceMap.count(curVar.get())) break;
                cur = replaceMap[curVar.get()];
            }
            val = cur;
        }

        auto repVar = [&](VarPtr &var) {
            if (!var || !replaceMap.count(var.get())) return;
            if (auto v = std::dynamic_pointer_cast<IRVar>(replaceMap[var.get()])) var = v;
        };
        auto repVal = [&](ValuePtr &val) {
            if (auto var = std::dynamic_pointer_cast<IRVar>(val)) {
                if (replaceMap.count(var.get())) val = replaceMap[var.get()];
            }
        };

        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr) {
            if (auto *p = dynamic_cast<IRStore*>(&*instr)) {
                repVar(p->storeValue); repVar(p->address);
            } else if (auto *p = dynamic_cast<IRLoad*>(&*instr)) {
                repVar(p->addressVar); repVar(p->tmp);
            } else if (auto *p = dynamic_cast<IRGetptr*>(&*instr)) {
                repVar(p->base); repVar(p->res); repVar(p->index);
            } else if (auto *p = dynamic_cast<IRBinaryop*>(&*instr)) {
                repVal(p->leftValue); repVal(p->rightValue); repVar(p->result);
            } else if (auto *p = dynamic_cast<IRBr*>(&*instr)) {
                repVar(p->condition);
            } else if (auto *p = dynamic_cast<IRReturn*>(&*instr)) {
                repVar(p->returnValue);
            } else if (auto *p = dynamic_cast<IRCall*>(&*instr)) {
                repVar(p->retVar);
                if (p->pList)
                    for (auto &param : p->pList->paramList)
                        if (auto var = std::dynamic_pointer_cast<IRVar>(param))
                            if (replaceMap.count(var.get())) param = replaceMap[var.get()];
            } else if (auto *p = dynamic_cast<IRPrint*>(&*instr)) {
                repVal(p->printVar);
            } else if (auto *p = dynamic_cast<IRGetint*>(&*instr)) {
                repVar(p->result);
            } else if (auto *p = dynamic_cast<IRSext*>(&*instr)) {
                repVar(p->value); repVar(p->result);
            } else if (auto *p = dynamic_cast<IRZext*>(&*instr)) {
                repVar(p->value); repVar(p->result);
            } else if (auto *p = dynamic_cast<IRTrunc*>(&*instr)) {
                repVar(p->value); repVar(p->result);
            } else if (auto *p = dynamic_cast<IRPhi*>(&*instr)) {
                repVar(p->result); repVar(p->secondState);
            } else if (auto *p = dynamic_cast<IRPHI*>(&*instr)) {
                repVar(p->result); repVal(p->firstState); repVal(p->secondState);
                for (auto &e : p->entries) repVal(e.first);
            } else if (auto *p = dynamic_cast<IRMemset*>(&*instr)) {
                repVar(p->dest);
            } else if (auto *p = dynamic_cast<IRMemcpy*>(&*instr)) {
                repVar(p->dest); repVar(p->value);
            } else if (auto *p = dynamic_cast<IRExit*>(&*instr)) {
                repVal(p->exitCode);
            }
        });

        std::set<IRVar*> removedAllocas(promotable.begin(), promotable.end());
        auto removeDead = [&](std::vector<std::shared_ptr<IRNode>> &instrList) {
            instrList.erase(
                std::remove_if(instrList.begin(), instrList.end(),
                    [&](const std::shared_ptr<IRNode> &instr) {
                        if (toRemove.count(instr.get())) return true;
                        if (auto *p = dynamic_cast<IRAlloca*>(&*instr))
                            return removedAllocas.count(p->var.get()) > 0;
                        return false;
                    }),
                instrList.end());
        };
        removeDead(func->body->instrList);
        for (auto &blk : func->body->blockList) removeDead(blk->instrList);
    }

    void convertLiteralStores(std::shared_ptr<IRFunction> func,
                              const std::set<IRVar*> &promotable,
                              std::map<IRVar*, AllocaInfo> &infoMap) {
        auto convert = [&](std::vector<std::shared_ptr<IRNode>> &instrList) {
            std::vector<std::shared_ptr<IRNode>> newList;
            for (auto &instr : instrList) {
                auto *store = dynamic_cast<IRStore*>(&*instr);
                if (store && store->address && promotable.count(store->address.get())
                    && !store->storeValue && store->storeLiteral) {
                    auto fresh = std::make_shared<IRVar>();
                    fresh->type = infoMap[store->address.get()].allocaType;
                    auto add = std::make_shared<IRBinaryop>(ADD, fresh);
                    add->leftValue = store->storeLiteral;
                    add->rightValue = std::make_shared<IRLiteral>(INT_LITERAL, 0);
                    newList.push_back(add);
                    store->storeValue = fresh;
                }
                newList.push_back(instr);
            }
            instrList = std::move(newList);
        };
        convert(func->body->instrList);
        for (auto &blk : func->body->blockList) convert(blk->instrList);
    }

    void collectDefUse(std::shared_ptr<IRFunction> func,
                       const std::set<IRVar*> &promotable,
                       std::map<IRVar*, AllocaInfo> &infoMap) {
        auto scan = [&](IRBlock *blk) {
            for (auto &instr : blk->instrList) {
                if (auto *p = dynamic_cast<IRStore*>(&*instr)) {
                    if (p->address && promotable.count(p->address.get())){
                        infoMap[p->address.get()].defBlocks.insert(blk);
                    }
                } else if (auto *p = dynamic_cast<IRLoad*>(&*instr)) {
                    if (p->addressVar && promotable.count(p->addressVar.get())){
                        infoMap[p->addressVar.get()].useBlocks.insert(blk);
                    }
                }
            }
        };
        scan(func->body.get());
        for (auto &blk : func->body->blockList) scan(blk.get());
    }
};

}
