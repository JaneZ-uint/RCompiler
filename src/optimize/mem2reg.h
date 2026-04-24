#pragma once
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <set>
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

namespace JaneZ {
class Mem2Reg {
public:
    void optimize(std::shared_ptr<IRRoot> root){
        for(auto &func: root->children){
            if(auto *p = dynamic_cast<IRFunction *>(& *func)){
                for(auto &childFunc: p->funcList){
                    scan(childFunc);
                }
            }
            scan(func);
        }
    }

    void scan(std::shared_ptr<IRNode> node){
        if(dynamic_cast<IRFunction *>(& *node)){
            funcScan(std::dynamic_pointer_cast<IRFunction>(node));
        }
    }

    void funcScan(std::shared_ptr<IRFunction> func){
        if(!func->body) return;
        removeUnusedAllocas(func);
        singleStorePropagate(func);
    }

private:
    void forEachInstr(std::shared_ptr<IRFunction> func,
                      const std::function<void(const std::shared_ptr<IRNode>&)> &fn){
        for(auto &instr: func->body->instrList) {
            fn(instr);
        }
        for(auto &blk: func->body->blockList){
            for(auto &instr: blk->instrList) {
                fn(instr);
            }
        }
    }

    void forEachInstrMut(std::shared_ptr<IRFunction> func,
                         const std::function<void(std::shared_ptr<IRNode>&)> &fn){
        for(auto &instr: func->body->instrList) {
            fn(instr);
        }
        for(auto &blk: func->body->blockList){
            for(auto &instr: blk->instrList) {
                fn(instr);
            }
        }
    }

    void checkAllocaRef(IRVar *raw, std::set<IRVar*> &allocaVars,
                        const std::shared_ptr<IRVar> &var, bool isStoreAddr, bool isLoadAddr,
                        std::map<IRVar*, int> &storeCnt,
                        std::map<IRVar*, std::vector<std::shared_ptr<IRLoad>>> &loadMap,
                        std::map<IRVar*, bool> &escaped,
                        std::shared_ptr<IRStore> storeInstr = nullptr,
                        std::shared_ptr<IRLoad> loadInstr = nullptr){
        if(!var || !allocaVars.count(var.get())) return;
        auto key = var.get();
        if(isStoreAddr){
            storeCnt[key]++;
        } else if(isLoadAddr && loadInstr){
            loadMap[key].push_back(loadInstr);
        } else {
            escaped[key] = true;
        }
    }

    void removeUnusedAllocas(std::shared_ptr<IRFunction> func){
        std::vector<std::shared_ptr<IRVar>> varList;
        std::set<IRVar*> allocaVars;

        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr){
            if(auto *p = dynamic_cast<IRAlloca*>(&*instr)){
                p->var->isUsed = false;
                varList.push_back(p->var);
                allocaVars.insert(p->var.get());
            }
        });
        if(varList.empty()) return;

        auto markUsed = [&](const std::shared_ptr<IRVar> &var){
            if(var && allocaVars.count(var.get())) var->isUsed = true;
        };
        auto markUsedValue = [&](const std::shared_ptr<IRValue> &val){
            if(auto var = std::dynamic_pointer_cast<IRVar>(val)) markUsed(var);
        };

        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr){
            if(dynamic_cast<IRAlloca*>(&*instr)) return;
            if(auto *p = dynamic_cast<IRStore*>(&*instr)){
                markUsed(p->storeValue); markUsed(p->address);
            } else if(auto *p = dynamic_cast<IRLoad*>(&*instr)){
                markUsed(p->addressVar);
            } else if(auto *p = dynamic_cast<IRGetptr*>(&*instr)){
                markUsed(p->base); markUsed(p->index);
            } else if(auto *p = dynamic_cast<IRBinaryop*>(&*instr)){
                markUsedValue(p->leftValue); markUsedValue(p->rightValue);
            } else if(auto *p = dynamic_cast<IRBr*>(&*instr)){
                markUsed(p->condition);
            } else if(auto *p = dynamic_cast<IRReturn*>(&*instr)){
                markUsed(p->returnValue);
            } else if(auto *p = dynamic_cast<IRCall*>(&*instr)){
                markUsed(p->retVar);
                if(p->pList)
                    for(auto &param: p->pList->paramList)
                        if(auto var = std::dynamic_pointer_cast<IRVar>(param)) markUsed(var);
            } else if(auto *p = dynamic_cast<IRPrint*>(&*instr)){
                markUsedValue(p->printVar);
            } else if(auto *p = dynamic_cast<IRGetint*>(&*instr)){
                markUsed(p->result);
            } else if(auto *p = dynamic_cast<IRSext*>(&*instr)){
                markUsed(p->value);
            } else if(auto *p = dynamic_cast<IRZext*>(&*instr)){
                markUsed(p->value);
            } else if(auto *p = dynamic_cast<IRTrunc*>(&*instr)){
                markUsed(p->value);
            } else if(auto *p = dynamic_cast<IRPhi*>(&*instr)){
                markUsed(p->result); markUsed(p->secondState);
            } else if(auto *p = dynamic_cast<IRPHI*>(&*instr)){
                markUsed(p->result); markUsedValue(p->firstState); markUsedValue(p->secondState);
            } else if(auto *p = dynamic_cast<IRMemset*>(&*instr)){
                markUsed(p->dest);
            } else if(auto *p = dynamic_cast<IRMemcpy*>(&*instr)){
                markUsed(p->dest); markUsed(p->value);
            } else if(auto *p = dynamic_cast<IRExit*>(&*instr)){
                markUsedValue(p->exitCode);
            }
        });

        auto removeUnused = [](std::vector<std::shared_ptr<IRNode>> &instrList){
            instrList.erase(
                std::remove_if(instrList.begin(), instrList.end(),
                    [](const std::shared_ptr<IRNode> &instr){
                        if(auto *p = dynamic_cast<IRAlloca*>(&*instr))
                            return !p->var->isUsed;
                        return false;
                    }),
                instrList.end());
        };
        removeUnused(func->body->instrList);
        for(auto &blk: func->body->blockList) removeUnused(blk->instrList);
    }

    void singleStorePropagate(std::shared_ptr<IRFunction> func){
        std::set<IRVar*> allocaVars;
        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr){
            if(auto *p = dynamic_cast<IRAlloca*>(&*instr))
                allocaVars.insert(p->var.get());
        });
        if(allocaVars.empty()) return;

        std::map<IRVar*, int> storeCnt;
        std::map<IRVar*, std::shared_ptr<IRStore>> singleStore;
        std::map<IRVar*, std::vector<std::shared_ptr<IRLoad>>> loadMap;
        std::map<IRVar*, bool> escaped;

        auto markEscape = [&](const std::shared_ptr<IRVar> &var){
            if(var && allocaVars.count(var.get())) escaped[var.get()] = true;
        };
        auto markEscapeValue = [&](const std::shared_ptr<IRValue> &val){
            if(auto var = std::dynamic_pointer_cast<IRVar>(val)) markEscape(var);
        };

        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr){
            if(dynamic_cast<IRAlloca*>(&*instr)) return;

            if(auto *p = dynamic_cast<IRStore*>(&*instr)){
                if(p->address && allocaVars.count(p->address.get())){
                    storeCnt[p->address.get()]++;
                    singleStore[p->address.get()] = std::dynamic_pointer_cast<IRStore>(instr);
                }
                markEscape(p->storeValue);
            } else if(auto *p = dynamic_cast<IRLoad*>(&*instr)){
                if(p->addressVar && allocaVars.count(p->addressVar.get())){
                    loadMap[p->addressVar.get()].push_back(std::dynamic_pointer_cast<IRLoad>(instr));
                }
            } else if(auto *p = dynamic_cast<IRGetptr*>(&*instr)){
                markEscape(p->base); 
                markEscape(p->res); 
                markEscape(p->index);
            } else if(auto *p = dynamic_cast<IRBinaryop*>(&*instr)){
                markEscapeValue(p->leftValue); 
                markEscapeValue(p->rightValue); 
                markEscape(p->result);
            } else if(auto *p = dynamic_cast<IRBr*>(&*instr)){
                markEscape(p->condition);
            } else if(auto *p = dynamic_cast<IRReturn*>(&*instr)){
                markEscape(p->returnValue);
            } else if(auto *p = dynamic_cast<IRCall*>(&*instr)){
                markEscape(p->retVar);
                if(p->pList){
                    for(auto &param: p->pList->paramList){
                        if(auto var = std::dynamic_pointer_cast<IRVar>(param)) {
                            markEscape(var);
                        }
                    }
                }
            } else if(auto *p = dynamic_cast<IRPrint*>(&*instr)){
                markEscapeValue(p->printVar);
            } else if(auto *p = dynamic_cast<IRGetint*>(&*instr)){
                markEscape(p->result);
            } else if(auto *p = dynamic_cast<IRSext*>(&*instr)){
                markEscape(p->value); 
                markEscape(p->result);
            } else if(auto *p = dynamic_cast<IRZext*>(&*instr)){
                markEscape(p->value); 
                markEscape(p->result);
            } else if(auto *p = dynamic_cast<IRTrunc*>(&*instr)){
                markEscape(p->value); 
                markEscape(p->result);
            } else if(auto *p = dynamic_cast<IRPhi*>(&*instr)){
                markEscape(p->result); 
                markEscape(p->secondState);
            } else if(auto *p = dynamic_cast<IRPHI*>(&*instr)){
                markEscape(p->result); 
                markEscapeValue(p->firstState); 
                markEscapeValue(p->secondState);
            } else if(auto *p = dynamic_cast<IRMemset*>(&*instr)){
                markEscape(p->dest);
            } else if(auto *p = dynamic_cast<IRMemcpy*>(&*instr)){
                markEscape(p->dest); 
                markEscape(p->value);
            } else if(auto *p = dynamic_cast<IRExit*>(&*instr)){
                markEscapeValue(p->exitCode);
            }
        });

        std::map<IRVar*, std::shared_ptr<IRVar>> replaceMap;
        std::set<IRNode*> toRemove;
        std::set<IRVar*> removedAllocas;

        for(auto *av : allocaVars){
            if(escaped[av]) continue;
            if(storeCnt[av] != 1) continue;
            auto &store = singleStore[av];
            if(!store || !store->storeValue) continue;

            for(auto &load : loadMap[av]){
                replaceMap[load->tmp.get()] = store->storeValue;
                toRemove.insert(load.get());
            }
            toRemove.insert(store.get());
            removedAllocas.insert(av);
        }

        if(replaceMap.empty()) return;

        // if A->B and B->C, make A->C
        for(auto &[key, val] : replaceMap){
            auto cur = val.get();
            while(replaceMap.count(cur)){
                cur = replaceMap[cur].get();
            }
            if(cur != val.get()){
                for(auto &[k2, v2] : replaceMap){
                    if(v2.get() == val.get()){
                        v2 = replaceMap[val.get()];
                    }
                }
            }
        }
        for(auto &[key, val] : replaceMap){
            auto cur = val;
            while(replaceMap.count(cur.get())){
                cur = replaceMap[cur.get()];
            }
            val = cur;
        }

        auto repVar = [&](std::shared_ptr<IRVar> &var){
            if(var && replaceMap.count(var.get())) {
                var = replaceMap[var.get()];
            }
        };
        auto repValue = [&](std::shared_ptr<IRValue> &val){
            if(auto var = std::dynamic_pointer_cast<IRVar>(val)){
                if(replaceMap.count(var.get())) {
                    val = replaceMap[var.get()];
                }
            }
        };

        forEachInstr(func, [&](const std::shared_ptr<IRNode> &instr){
            if(auto *p = dynamic_cast<IRStore*>(&*instr)){
                repVar(p->storeValue); 
                repVar(p->address);
            } else if(auto *p = dynamic_cast<IRLoad*>(&*instr)){
                repVar(p->addressVar); 
                repVar(p->tmp);
            } else if(auto *p = dynamic_cast<IRGetptr*>(&*instr)){
                repVar(p->base); 
                repVar(p->res); 
                repVar(p->index);
            } else if(auto *p = dynamic_cast<IRBinaryop*>(&*instr)){
                repValue(p->leftValue); 
                repValue(p->rightValue); 
                repVar(p->result);
            } else if(auto *p = dynamic_cast<IRBr*>(&*instr)){
                repVar(p->condition);
            } else if(auto *p = dynamic_cast<IRReturn*>(&*instr)){
                repVar(p->returnValue);
            } else if(auto *p = dynamic_cast<IRCall*>(&*instr)){
                repVar(p->retVar);
                if(p->pList){
                    for(auto &param: p->pList->paramList){
                        if(auto var = std::dynamic_pointer_cast<IRVar>(param)){
                            if(replaceMap.count(var.get())) {
                                param = replaceMap[var.get()];
                            }
                        }
                    }
                }
            } else if(auto *p = dynamic_cast<IRPrint*>(&*instr)){
                repValue(p->printVar);
            } else if(auto *p = dynamic_cast<IRGetint*>(&*instr)){
                repVar(p->result);
            } else if(auto *p = dynamic_cast<IRSext*>(&*instr)){
                repVar(p->value); 
                repVar(p->result);
            } else if(auto *p = dynamic_cast<IRZext*>(&*instr)){
                repVar(p->value); 
                repVar(p->result);
            } else if(auto *p = dynamic_cast<IRTrunc*>(&*instr)){
                repVar(p->value); 
                repVar(p->result);
            } else if(auto *p = dynamic_cast<IRPhi*>(&*instr)){
                repVar(p->result); 
                repVar(p->secondState);
            } else if(auto *p = dynamic_cast<IRPHI*>(&*instr)){
                repVar(p->result); 
                repValue(p->firstState); 
                repValue(p->secondState);
            } else if(auto *p = dynamic_cast<IRMemset*>(&*instr)){
                repVar(p->dest);
            } else if(auto *p = dynamic_cast<IRMemcpy*>(&*instr)){
                repVar(p->dest); 
                repVar(p->value);
            } else if(auto *p = dynamic_cast<IRExit*>(&*instr)){
                repValue(p->exitCode);
            }
        });

        auto removeDead = [&](std::vector<std::shared_ptr<IRNode>> &instrList){
            instrList.erase(
                std::remove_if(instrList.begin(), instrList.end(),
                    [&](const std::shared_ptr<IRNode> &instr){
                        if(toRemove.count(instr.get())) {
                            return true;
                        }
                        if(auto *p = dynamic_cast<IRAlloca*>(&*instr)){
                            return removedAllocas.count(p->var.get()) > 0;
                        }
                        return false;
                    }),
                instrList.end());
        };
        removeDead(func->body->instrList);
        for(auto &blk: func->body->blockList) {
            removeDead(blk->instrList);
        }
    }
};
}
