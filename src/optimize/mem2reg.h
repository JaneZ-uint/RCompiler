#pragma once
#include <algorithm>
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
    std::shared_ptr<IRRoot> root;

    std::vector<std::shared_ptr<IRVar>> varList;

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
        if(auto *func = dynamic_cast<IRFunction *>(& *node)){
            funcScan(std::dynamic_pointer_cast<IRFunction>(node));
        }
    }

    void funcScan(std::shared_ptr<IRFunction> func){
        if(!func->body){
            return;
        }
        varList.clear();

        for(auto &instr: func->body->instrList){
            if(auto *p = dynamic_cast<IRAlloca *>(& *instr)){
                p->var->isUsed = false;
                varList.push_back(p->var);
            }
        }
        for(auto &blk: func->body->blockList){
            for(auto &instr: blk->instrList){
                if(auto *p = dynamic_cast<IRAlloca *>(& *instr)){
                    p->var->isUsed = false;
                    varList.push_back(p->var);
                }
            }
        }

        if(varList.empty()) return;

        std::set<IRVar*> allocaVars;
        for(auto &v: varList){
            allocaVars.insert(v.get());
        }

        auto markUsed = [&](const std::shared_ptr<IRVar> &var){
            if(var && allocaVars.count(var.get())){
                var->isUsed = true;
            }
        };

        auto markUsedValue = [&](const std::shared_ptr<IRValue> &val){
            if(auto var = std::dynamic_pointer_cast<IRVar>(val)){
                markUsed(var);
            }
        };

        auto scanInstr = [&](const std::shared_ptr<IRNode> &instr){
            if(dynamic_cast<IRAlloca*>(&*instr)) return;

            if(auto *p = dynamic_cast<IRStore*>(&*instr)){
                markUsed(p->storeValue);
                markUsed(p->address);
            } else if(auto *p = dynamic_cast<IRLoad*>(&*instr)){
                markUsed(p->addressVar);
            } else if(auto *p = dynamic_cast<IRGetptr*>(&*instr)){
                markUsed(p->base);
                markUsed(p->index);
            } else if(auto *p = dynamic_cast<IRBinaryop*>(&*instr)){
                markUsedValue(p->leftValue);
                markUsedValue(p->rightValue);
            } else if(auto *p = dynamic_cast<IRBr*>(&*instr)){
                markUsed(p->condition);
            } else if(auto *p = dynamic_cast<IRReturn*>(&*instr)){
                markUsed(p->returnValue);
            } else if(auto *p = dynamic_cast<IRCall*>(&*instr)){
                markUsed(p->retVar);
                if(p->pList){
                    for(auto &param: p->pList->paramList){
                        if(auto var = std::dynamic_pointer_cast<IRVar>(param)){
                            markUsed(var);
                        }
                    }
                }
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
                markUsed(p->result);
                markUsed(p->secondState);
            } else if(auto *p = dynamic_cast<IRPHI*>(&*instr)){
                markUsed(p->result);
                markUsedValue(p->firstState);
                markUsedValue(p->secondState);
            } else if(auto *p = dynamic_cast<IRMemset*>(&*instr)){
                markUsed(p->dest);
            } else if(auto *p = dynamic_cast<IRMemcpy*>(&*instr)){
                markUsed(p->dest);
                markUsed(p->value);
            } else if(auto *p = dynamic_cast<IRExit*>(&*instr)){
                markUsedValue(p->exitCode);
            }
        };

        for(auto &instr: func->body->instrList){
            scanInstr(instr);
        }
        for(auto &blk: func->body->blockList){
            for(auto &instr: blk->instrList){
                scanInstr(instr);
            }
        }

        auto removeUnused = [](std::vector<std::shared_ptr<IRNode>> &instrList){
            instrList.erase(
                std::remove_if(instrList.begin(), instrList.end(),
                    [](const std::shared_ptr<IRNode> &instr){
                        if(auto *p = dynamic_cast<IRAlloca*>(&*instr)){
                            return !p->var->isUsed;
                        }
                        return false;
                    }),
                instrList.end()
            );
        };

        removeUnused(func->body->instrList);
        for(auto &blk: func->body->blockList){            
            removeUnused(blk->instrList);
        }
    }
};
}
