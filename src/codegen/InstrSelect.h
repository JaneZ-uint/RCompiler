# pragma once
# include "ASM.h"
# include "../ir/IRNode.h"
# include "../ir/IRBinaryop.h"
# include "../ir/IRLiteral.h"
# include "../ir/IRStore.h"
# include "../ir/IRLoad.h"
# include "../ir/IRBr.h"
# include "../ir/IRReturn.h"
# include "../ir/IRBlock.h"
# include "../ir/IRFunction.h"
# include "../ir/IRCall.h"
# include "../ir/IRBr.h"
#include <memory>
#include <vector>
#include <unordered_map>

namespace JaneZ {
class InstrSelect {
public:
    std::vector<ASMInstr> instrs;
    std::unordered_map<std::shared_ptr<IRNode>,int> regMap; // ir reg -> asm reg
    int exitblock = 1;
    int currenctExitBlock = 1;

    int nextReg = 32;

    int getReg(std::shared_ptr<IRNode> irVal){
        if(regMap.find(irVal) != regMap.end()){
            return regMap[irVal];
        }else{
            int reg = nextReg++;
            regMap[irVal] = reg;
            return reg;
        }
    }

    int newReg(){
        return nextReg++;
    }

    void selectFunc(std::shared_ptr<IRFunction> irInstr){
        regMap[irInstr] = exitblock++;
        for(auto &func: irInstr->funcList){
            selectFunc(func);
        }
        currenctExitBlock = regMap[irInstr];
        if(irInstr->body){
            for(auto &instr: irInstr->body->instrList){
                selectInstr(instr);
            }
            for(auto &block: irInstr->body->blockList){
                for(auto &instr: block->instrList){
                    selectInstr(instr);
                }
            }
        }
        //exitBlock!
    }

    void selectInstr(std::shared_ptr<IRNode> irInstr){
        if(auto *binaryOp = dynamic_cast<IRBinaryop *>(irInstr.get())){
            selectBinaryOp(std::make_shared<IRBinaryop>(*binaryOp));
        }else if(auto *storeOp = dynamic_cast<IRStore *>(irInstr.get())){
            selectStore(std::make_shared<IRStore>(*storeOp));
        }else if(auto *loadOp = dynamic_cast<IRLoad *>(irInstr.get())){
            selectLoad(std::make_shared<IRLoad>(*loadOp));
        }else if(auto *brOp = dynamic_cast<IRBr *>(irInstr.get())){
            selectBr(std::make_shared<IRBr>(*brOp));
        }else if(auto *retOp = dynamic_cast<IRReturn *>(irInstr.get())){
            selectReturn(std::make_shared<IRReturn>(*retOp));
        }else if(auto *callOp = dynamic_cast<IRCall *>(irInstr.get())){
            selectCall(std::make_shared<IRCall>(*callOp));
        }
    }

    void selectBinaryOp(std::shared_ptr<IRBinaryop> binaryOp){
        bool isImm = false;
        if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
            isImm = true;
        }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
            isImm = true;
        }
        //imm >= 2048 
        // TODO!!!
        if(binaryOp->op == ADD || binaryOp->op == XOROP || binaryOp->op == OROP || binaryOp->op == ANDOP){
            //
        }else if(binaryOp->op == SUB){
            //
        }else if(binaryOp->op == MUL){
            //
        }else if(binaryOp->op == DIV || binaryOp->op == MOD){
            //
        }else if(binaryOp->op == LEFTSHIFTOP || binaryOp->op == RIGHTSHIFTOP){
            //
        }else if(binaryOp->op == LT){
            //
        }else if(binaryOp->op == LEQ){
            //
        }else if(binaryOp->op == GT){
            //
        }else if(binaryOp->op == GEQ){
            //
        }else if(binaryOp->op == EQ){
            //
        }else if(binaryOp->op == NEQ){
            //
        }
    }
   
    void selectStore(std::shared_ptr<IRStore> storeOp){
        ASMInstr instr;
        instr.op = ASMOp::SW;
        if(storeOp->storeLiteral){
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG;
            liInstr.rd.value = newReg();
            liInstr.imm.type = OperandType::IMM;
            liInstr.imm.value = storeOp->storeLiteral->intValue;
            instr.rs1 = liInstr.rd;
            instr.imm.type = OperandType::IMM;
            instr.imm.value = 0;
            instr.rs2.type = OperandType::REG;
            instr.rs2.value = getReg(storeOp->address);
            instrs.push_back(liInstr);
            instrs.push_back(instr);
        }else{
            instr.rs1.type = OperandType::REG;
            instr.rs1.value = getReg(storeOp->storeValue);
            instr.imm.type = OperandType::IMM;
            instr.imm.value = 0;
            instr.rs2.type = OperandType::REG;
            instr.rs2.value = getReg(storeOp->address);
            instrs.push_back(instr);
        }
    }

    void selectLoad(std::shared_ptr<IRLoad> loadOp){
        ASMInstr instr;
        instr.op = ASMOp::LW;
        instr.rd.type = OperandType::REG;
        instr.rd.value = getReg(loadOp->tmp);
        instr.rs1.type = OperandType::REG;
        instr.rs1.value = getReg(loadOp->addressVar);
        instr.imm.type = OperandType::IMM;
        instr.imm.value = 0;
        instrs.push_back(instr);
    }

    void selectBr(std::shared_ptr<IRBr> brOp){
        ASMInstr brInstr;
        brInstr.op = ASMOp::BNEZ;
        brInstr.rs1.type = OperandType::REG;
        brInstr.rs1.value = getReg(brOp->condition);
        brInstr.label.type = OperandType::LABEL;
        brInstr.label.value = getReg(brOp->trueLabel);
        instrs.push_back(brInstr);
        if(brOp->falseLabel){
            ASMInstr jInstr;
            jInstr.op = ASMOp::J;
            jInstr.label.value = getReg(brOp->falseLabel);
            instrs.push_back(jInstr);
        }
    }

    void selectReturn(std::shared_ptr<IRReturn> retOp){
        if(retOp->returnLiteral){
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG;
            liInstr.rd.value = newReg();
            liInstr.imm.type = OperandType::IMM;
            liInstr.imm.value = retOp->returnLiteral->intValue;
            ASMInstr mvInstr;
            mvInstr.op = ASMOp::MV;
            mvInstr.rd.type = OperandType::REG;
            mvInstr.rd.value = 10; // a0
            mvInstr.rs1 = liInstr.rd;
            instrs.push_back(liInstr);
            instrs.push_back(mvInstr);
        }else if(retOp->returnValue){
            ASMInstr mvInstr;
            mvInstr.op = ASMOp::MV;
            mvInstr.rd.type = OperandType::REG;
            mvInstr.rd.value = 10; // a0
            mvInstr.rs1.type = OperandType::REG;
            mvInstr.rs1.value = getReg(retOp->returnValue);
            instrs.push_back(mvInstr);
        }
        ASMInstr retInstr;
        retInstr.op = ASMOp::J;
        retInstr.label.value = currenctExitBlock;
        retInstr.label.type = OperandType::LABEL;
        instrs.push_back(retInstr);
    }

    void selectCall(std::shared_ptr<IRCall> callOp){
        // TODO
    }

    
};
}