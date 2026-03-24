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
# include "../ir/IRType.h"
# include "../ir/IRParam.h"
# include "../ir/IRGetptr.h"
# include "../ir/IRAlloca.h"
# include "../ir/IRRoot.h"
# include "../ir/IRPhi.h"
# include "../ir/IRPHI.h"
# include "CodegenFunction.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace JaneZ {
class InstrSelect {
public:
    std::vector<ASMInstr> instrs;
    std::unordered_map<std::shared_ptr<IRNode>,int> regMap; // ir reg -> asm reg
    std::unordered_map<std::shared_ptr<IRBlock>, std::shared_ptr<ASMBlock>> blockMap;
    std::shared_ptr<IRBlock> currentIRBlock;

    int exitblock = 1;
    int currenctExitBlock = 1;

    int nextReg = 32;

    std::string currentFuncExitLabel;

    std::vector<std::shared_ptr<ASMBlock>> asmBlocks;
    std::shared_ptr<ASMBlock> currentBlock;

    int currentStackSize = 0;

    int stackOffset = 0;

    std::unordered_map<std::shared_ptr<IRNode>, int> stackMap; //alloca
    std::unordered_map<std::shared_ptr<IRNode>, int> varStackOffset; //spilling

    int getStackSlot(std::shared_ptr<IRNode> var) {
        if (varStackOffset.find(var) != varStackOffset.end()) {
            return varStackOffset[var];
        }
        int offset = stackOffset;
        stackOffset += 4;
        varStackOffset[var] = offset;
        return offset;
    }

    // Load value from stack (or immediate) into a physical register
    void loadToReg(std::shared_ptr<IRNode> val, int physReg) {
        if (auto *lit = dynamic_cast<IRLiteral *>(val.get())) {
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG;
            liInstr.rd.value = physReg;
            liInstr.imm.type = OperandType::IMM;
            liInstr.imm.value = lit->intValue;
            currentBlock->instrs.push_back(liInstr);
        } else {
            int offset = getStackSlot(val);
            ASMInstr lwInstr;
            lwInstr.op = ASMOp::LW;
            lwInstr.rd.type = OperandType::REG;
            lwInstr.rd.value = physReg;
            lwInstr.rs1.type = OperandType::REG;
            lwInstr.rs1.value = 2; // sp
            lwInstr.imm.type = OperandType::IMM;
            lwInstr.imm.value = offset;
            currentBlock->instrs.push_back(lwInstr);
        }
    }

    // Store value from physical register to stack slot for variable
    void storeFromReg(int physReg, std::shared_ptr<IRNode> val) {
        int offset = getStackSlot(val);
        ASMInstr swInstr;
        swInstr.op = ASMOp::SW;
        swInstr.rs2.type = OperandType::REG;
        swInstr.rs2.value = physReg;
        swInstr.rs1.type = OperandType::REG;
        swInstr.rs1.value = 2; // sp
        swInstr.imm.type = OperandType::IMM;
        swInstr.imm.value = offset;
        currentBlock->instrs.push_back(swInstr);
    }

    void handlePhiCopies(std::shared_ptr<IRBlock> targetBlock) {
        if (!targetBlock) {
            return;
        }
        for (auto &instr : targetBlock->instrList) {
            if (auto *phi = dynamic_cast<IRPhi *>(instr.get())) { //IRPhi 是有true false指示的
                bool useImm = false;
                int immVal = 0;
                std::shared_ptr<IRNode> sourceNode = nullptr;
                
                if (phi->firstBlock == currentIRBlock) {
                    useImm = true;
                    immVal = phi->firstState ? 1 : 0;
                } else if (phi->secondBlock == currentIRBlock) {
                    sourceNode = phi->secondState;
                } else {
                    continue;
                }
                if (useImm) {
                    ASMInstr liInstr;
                    liInstr.op = ASMOp::LI;
                    liInstr.rd.type = OperandType::REG; 
                    liInstr.rd.value = 6; // t1
                    liInstr.imm.type = OperandType::IMM; 
                    liInstr.imm.value = immVal;
                    currentBlock->instrs.push_back(liInstr);
                } else if (sourceNode) {
                    loadToReg(sourceNode, 6); // t1
                }
                storeFromReg(6, phi->result);

            } else if (auto *phi = dynamic_cast<IRPHI *>(instr.get())) {  //IRPHI 是没有true false指示的，直接两个都是变量
                std::shared_ptr<IRNode> sourceNode = nullptr;
                if (phi->firstBlock == currentIRBlock) {
                    sourceNode = phi->firstState;
                } else if (phi->secondBlock == currentIRBlock) {
                    sourceNode = phi->secondState;
                } else {
                    continue;
                }
                if (sourceNode) {
                    loadToReg(sourceNode, 6); // t1
                    storeFromReg(6, phi->result);
                }
            } else {
                break;
            }
        }
    }

    // Deprecated: Reg allocation logic (kept for compatibility if needed, but unused in new scheme)
    int getRegInternal(std::shared_ptr<IRNode> irVal){
        if(regMap.find(irVal) != regMap.end()){
            return regMap[irVal];
        }else{
            int reg = nextReg++;
            regMap[irVal] = reg;
            return reg;
        }
    }

    int loadOperand(std::shared_ptr<IRNode> val){
        if(auto *lit = dynamic_cast<IRLiteral *>(val.get())){
             int reg = getRegInternal(val);
             ASMInstr liInstr;
             liInstr.op = ASMOp::LI;
             liInstr.rd.type = OperandType::REG;
             liInstr.rd.value = reg;
             liInstr.imm.type = OperandType::IMM;
             liInstr.imm.value = lit->intValue;
             currentBlock->instrs.push_back(liInstr);
             return reg;
        }
        return getRegInternal(val);
    }

    int newReg(){
        return nextReg++;
    }

    void select(std::shared_ptr<IRRoot> irRoot){
        regMap.clear();
        stackMap.clear();
        asmBlocks.clear();
        for(auto &func: irRoot->children){
            if(auto *irFunc = dynamic_cast<IRFunction *>(func.get())){
                selectFunc(std::make_shared<IRFunction>(*irFunc));
            }
        }
    }

    void selectFunc(std::shared_ptr<IRFunction> irInstr){
        blockMap.clear();
        stackOffset = 0;
        varStackOffset.clear();

        for(auto &func: irInstr->funcList){
            selectFunc(func);
        }

        int myExitBlockID = exitblock++;
        currenctExitBlock = myExitBlockID;
        currentFuncExitLabel = ".L" + std::to_string(currenctExitBlock);

        std::shared_ptr<ASMBlock> entryBlock = std::make_shared<ASMBlock>(irInstr->name);
        asmBlocks.push_back(entryBlock);
        
        if(irInstr->body){
            blockMap[irInstr->body] = entryBlock;
            for(auto &block: irInstr->body->blockList){
                int id = getRegInternal(block);
                std::shared_ptr<ASMBlock> ab = std::make_shared<ASMBlock>(".L" + std::to_string(id));
                blockMap[block] = ab;
                asmBlocks.push_back(ab);
            }
            currentBlock = entryBlock;
            currentIRBlock = irInstr->body;
            for(auto &instr: irInstr->body->instrList){
                selectInstr(instr);
            }
            for(auto &block: irInstr->body->blockList){
                currentBlock = blockMap[block];
                currentIRBlock = block;
                for(auto &instr: block->instrList){
                    selectInstr(instr);
                }
            }
        }
        
        currentStackSize = stackOffset + 8;
        if (currentStackSize % 16 != 0) {
            currentStackSize = ((currentStackSize / 16) + 1) * 16;
        }

        std::vector<ASMInstr> prologue;
        
        ASMInstr addiInstr;
        addiInstr.op = ASMOp::ADDI;
        addiInstr.rd = Operand(OperandType::REG, 2);
        addiInstr.rs1 = Operand(OperandType::REG, 2);
        addiInstr.imm = Operand(OperandType::IMM, -currentStackSize);
        prologue.push_back(addiInstr);

        ASMInstr swRa;
        swRa.op = ASMOp::SW;
        swRa.rs2 = Operand(OperandType::REG, 1);
        swRa.rs1 = Operand(OperandType::REG, 2);
        swRa.imm = Operand(OperandType::IMM, currentStackSize - 4);
        prologue.push_back(swRa);

        ASMInstr swS0;
        swS0.op = ASMOp::SW;
        swS0.rs2 = Operand(OperandType::REG, 8);
        swS0.rs1 = Operand(OperandType::REG, 2);
        swS0.imm = Operand(OperandType::IMM, currentStackSize - 8);
        prologue.push_back(swS0);

        ASMInstr addiS0;
        addiS0.op = ASMOp::ADDI;
        addiS0.rd = Operand(OperandType::REG, 8);
        addiS0.rs1 = Operand(OperandType::REG, 2);
        addiS0.imm = Operand(OperandType::IMM, currentStackSize);
        prologue.push_back(addiS0);

        entryBlock->instrs.insert(entryBlock->instrs.begin(), prologue.begin(), prologue.end());

        // Epilogue
        std::shared_ptr<ASMBlock> exitBlock = std::make_shared<ASMBlock>(currentFuncExitLabel);
        
        ASMInstr lwRa;
        lwRa.op = ASMOp::LW;
        lwRa.rd = Operand(OperandType::REG, 1);
        lwRa.rs1 = Operand(OperandType::REG, 2);
        lwRa.imm = Operand(OperandType::IMM, currentStackSize - 4);
        exitBlock->instrs.push_back(lwRa);

        ASMInstr lwS0;
        lwS0.op = ASMOp::LW;
        lwS0.rd = Operand(OperandType::REG, 8);
        lwS0.rs1 = Operand(OperandType::REG, 2);
        lwS0.imm = Operand(OperandType::IMM, currentStackSize - 8);
        exitBlock->instrs.push_back(lwS0);

        ASMInstr addiSp;
        addiSp.op = ASMOp::ADDI;
        addiSp.rd = Operand(OperandType::REG, 2);
        addiSp.rs1 = Operand(OperandType::REG, 2);
        addiSp.imm = Operand(OperandType::IMM, currentStackSize);
        exitBlock->instrs.push_back(addiSp);

        ASMInstr retInstr;
        retInstr.op = ASMOp::JR;
        retInstr.rs1 = Operand(OperandType::REG, 1); // ra
        exitBlock->instrs.push_back(retInstr);

        asmBlocks.push_back(exitBlock);
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
        }else if(auto *getptrOp = dynamic_cast<IRGetptr *>(irInstr.get())){
            selectGetptr(std::make_shared<IRGetptr>(*getptrOp));
        }else if(auto *allocaOp = dynamic_cast<IRAlloca *>(irInstr.get())){
            selectAlloca(std::make_shared<IRAlloca>(*allocaOp));
        }else{
            //other instructions
        }
    }

    void selectAlloca(std::shared_ptr<IRAlloca> allocaOp){
        int offest = 0;
        if(allocaOp->allocatedType->size % 4 != 0){
            offest = ((allocaOp->allocatedType->size / 4) + 1) * 4;
        }else{
            offest = allocaOp->allocatedType->size;
        }
        int dataOffset = stackOffset;
        stackOffset += offest;
        ASMInstr addrInstr;
        addrInstr.op = ASMOp::ADDI;
        addrInstr.rd.type = OperandType::REG;
        addrInstr.rd.value = 5; // t0
        addrInstr.rs1.type = OperandType::REG;
        addrInstr.rs1.value = 2; // sp
        addrInstr.imm.type = OperandType::IMM;
        addrInstr.imm.value = dataOffset;
        currentBlock->instrs.push_back(addrInstr);

        //wait and see whether necessary
        storeFromReg(5, allocaOp->var);
    }

    void selectBinaryOp(std::shared_ptr<IRBinaryop> binaryOp){
        loadToReg(binaryOp->leftValue, 5); // t0
        loadToReg(binaryOp->rightValue, 6); // t1

        ASMInstr instr;
        instr.rd.type = OperandType::REG; 
        instr.rd.value = 7; // t2
        instr.rs1.type = OperandType::REG; 
        instr.rs1.value = 5; // t0
        instr.rs2.type = OperandType::REG; 
        instr.rs2.value = 6; // t1
        bool handled = true;
        switch (binaryOp->op) {
            case ADD: 
                instr.op = ASMOp::ADD; 
                break;
            case SUB: 
                instr.op = ASMOp::SUB; 
                break;
            case MUL: 
                instr.op = ASMOp::MUL; 
                break;
            case DIV: 
                instr.op = ASMOp::DIV; 
                break;
            case MOD: 
                instr.op = ASMOp::REM; 
                break;
            case XOROP: 
                instr.op = ASMOp::XOR; 
                break;
            case OROP: 
                instr.op = ASMOp::OR; 
                break;
            case ANDOP: 
                instr.op = ASMOp::AND; 
                break;
            case LEFTSHIFTOP: 
                instr.op = ASMOp::SLL; 
                break;
            case RIGHTSHIFTOP: 
                instr.op = ASMOp::SRL; 
                break;
            case LT: 
                instr.op = ASMOp::SLT; 
                break;
            case GT: 
                instr.op = ASMOp::SLT;
                instr.rs1.value = 6; // t1
                instr.rs2.value = 5; // t0
                break;
            case LEQ: 
                instr.op = ASMOp::SLE; 
                break;
            case GEQ: 
                instr.op = ASMOp::SGE; 
                break;
            case EQ:{
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG; 
                subInstr.rd.value = 7;
                subInstr.rs1.type = OperandType::REG; 
                subInstr.rs1.value = 5;
                subInstr.rs2.type = OperandType::REG; 
                subInstr.rs2.value = 6;
                currentBlock->instrs.push_back(subInstr);
                instr.op = ASMOp::SEQZ;
                instr.rs1.value = 7;
                instr.rs2.type = OperandType::IMM;
                break;
            }
            case NEQ:{
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG; subInstr.rd.value = 7;
                subInstr.rs1.type = OperandType::REG; subInstr.rs1.value = 5;
                subInstr.rs2.type = OperandType::REG; subInstr.rs2.value = 6;
                currentBlock->instrs.push_back(subInstr);

                instr.op = ASMOp::SNEZ;
                instr.rs1.value = 7;
                instr.rs2.type = OperandType::IMM;
                break;
            }
            default:
                handled = false;
                break;
        }
        if (handled) {
            currentBlock->instrs.push_back(instr);
            storeFromReg(7, binaryOp->result);
        }
    }

    void selectStore(std::shared_ptr<IRStore> storeOp){
        loadToReg(storeOp->address, 5); // t0 address
        if(storeOp->storeLiteral){
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG; liInstr.rd.value = 6; // t1
            liInstr.imm.type = OperandType::IMM; liInstr.imm.value = storeOp->storeLiteral->intValue;
            currentBlock->instrs.push_back(liInstr);
        } else {
            loadToReg(storeOp->storeValue, 6); // t1 value
        }
        ASMInstr swInstr;
        swInstr.op = ASMOp::SW;
        swInstr.rs2.type = OperandType::REG; swInstr.rs2.value = 6; // t1 value
        swInstr.rs1.type = OperandType::REG; swInstr.rs1.value = 5; // t0 base
        swInstr.imm.type = OperandType::IMM; swInstr.imm.value = 0;
        currentBlock->instrs.push_back(swInstr);
    }

    void selectLoad(std::shared_ptr<IRLoad> loadOp){
        loadToReg(loadOp->addressVar, 5); // t0 address
        ASMInstr lwInstr;
        lwInstr.op = ASMOp::LW;
        lwInstr.rd.type = OperandType::REG; 
        lwInstr.rd.value = 6; // t1 dest
        lwInstr.rs1.type = OperandType::REG; 
        lwInstr.rs1.value = 5; // t0 base
        lwInstr.imm.type = OperandType::IMM; 
        lwInstr.imm.value = 0;
        currentBlock->instrs.push_back(lwInstr);
        storeFromReg(6, loadOp->tmp);
    }

    void selectBr(std::shared_ptr<IRBr> brOp){
        if (brOp->condition) {
            handlePhiCopies(brOp->trueLabel);
            loadToReg(brOp->condition, 5); // t0
            ASMInstr brInstr;
            brInstr.op = ASMOp::BNEZ;
            brInstr.rs1.type = OperandType::REG;
            brInstr.rs1.value = 5; // t0
            brInstr.label.type = OperandType::LABEL;
            brInstr.label.value = getRegInternal(brOp->trueLabel);
            currentBlock->instrs.push_back(brInstr);
            if(brOp->falseLabel){
                handlePhiCopies(brOp->falseLabel);
                ASMInstr jInstr;
                jInstr.op = ASMOp::J;
                jInstr.label.type = OperandType::LABEL;
                jInstr.label.value = getRegInternal(brOp->falseLabel);
                currentBlock->instrs.push_back(jInstr);
            }
        } else {
            handlePhiCopies(brOp->trueLabel);
            ASMInstr jInstr;
            jInstr.op = ASMOp::J;
            jInstr.label.type = OperandType::LABEL;
            jInstr.label.value = getRegInternal(brOp->trueLabel);
            currentBlock->instrs.push_back(jInstr);
        }
    }

    void selectReturn(std::shared_ptr<IRReturn> retOp){
        if(retOp->returnLiteral){
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG;
            liInstr.rd.value = 10; // a0
            liInstr.imm.type = OperandType::IMM;
            liInstr.imm.value = retOp->returnLiteral->intValue;
            currentBlock->instrs.push_back(liInstr);
        } else if(retOp->returnValue){
            loadToReg(retOp->returnValue, 10);
        }
        ASMInstr jInstr;
        jInstr.op = ASMOp::J;
        jInstr.label.type = OperandType::LABEL;
        jInstr.label.value = currenctExitBlock;
        currentBlock->instrs.push_back(jInstr);
    }

    void selectCall(std::shared_ptr<IRCall> callOp){
        int paramCount = callOp->pList->paramList.size();
        if (paramCount > 8) {
            paramCount = 8; 
        }
        for(int i = 0; i < paramCount; i ++){
            loadToReg(callOp->pList->paramList[i], 10 + i);
        }
        ASMInstr callInstr;
        callInstr.op = ASMOp::CALL;
        callInstr.funcName = callOp->function->name;
        currentBlock->instrs.push_back(callInstr);
        if (callOp->retVar) { 
            storeFromReg(10, callOp->retVar);
        }
    }

    int caculateStructOffset(std::shared_ptr<IRStructType> structType, int fieldIndex){
        int offset = 0;
        for(int i = 0;i < fieldIndex;i ++){
            offset += structType->memberTypes[i].second->size;
        }
        return offset;
    }

    void selectGetptr(std::shared_ptr<IRGetptr> getptrOp){
        loadToReg(getptrOp->base, 5); // t0 base
        if(auto array = std::dynamic_pointer_cast<IRArrayType>(getptrOp->base->type)){
            int elemSize = array->elementType->size;
            int index = getptrOp->offset;
            if(getptrOp->index){
                loadToReg(getptrOp->index, 6); // t1 index
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG; 
                liInstr.rd.value = 7; // t2 size
                liInstr.imm.type = OperandType::IMM; 
                liInstr.imm.value = elemSize;
                currentBlock->instrs.push_back(liInstr);
                ASMInstr mulInstr;
                mulInstr.op = ASMOp::MUL;
                mulInstr.rd.type = OperandType::REG; 
                mulInstr.rd.value = 6; // t1 = index * size
                mulInstr.rs1.type = OperandType::REG; 
                mulInstr.rs1.value = 6;
                mulInstr.rs2.type = OperandType::REG; 
                mulInstr.rs2.value = 7;
                currentBlock->instrs.push_back(mulInstr);
                ASMInstr addInstr;
                addInstr.op = ASMOp::ADD;
                addInstr.rd.type = OperandType::REG; 
                addInstr.rd.value = 5; // t0 = base + offset
                addInstr.rs1.type = OperandType::REG; 
                addInstr.rs1.value = 5;
                addInstr.rs2.type = OperandType::REG; 
                addInstr.rs2.value = 6;
                currentBlock->instrs.push_back(addInstr);
            }else{
                ASMInstr addInstr;
                addInstr.op = ASMOp::ADDI;
                addInstr.rd.type = OperandType::REG; 
                addInstr.rd.value = 5; // t0
                addInstr.rs1.type = OperandType::REG; 
                addInstr.rs1.value = 5;
                addInstr.imm.type = OperandType::IMM; 
                addInstr.imm.value = index * elemSize;
                currentBlock->instrs.push_back(addInstr);
            }
        }else if(auto structType = std::dynamic_pointer_cast<IRStructType>(getptrOp->base->type)){
            int offset = caculateStructOffset(structType, getptrOp->offset);
            ASMInstr addInstr;
            addInstr.op = ASMOp::ADDI;
            addInstr.rd.type = OperandType::REG; 
            addInstr.rd.value = 5; // t0
            addInstr.rs1.type = OperandType::REG; 
            addInstr.rs1.value = 5;
            addInstr.imm.type = OperandType::IMM; 
            addInstr.imm.value = offset;
            currentBlock->instrs.push_back(addInstr);
        }
        storeFromReg(5, getptrOp->res);
    }
};
}