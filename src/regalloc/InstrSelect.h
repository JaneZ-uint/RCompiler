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
# include "../ir/IRImpl.h"
# include "../ir/IRPrint.h"
# include "../ir/IRExit.h"
# include "../ir/IRGetint.h"
# include "../ir/IRMem.h"
# include "../ir/IRTrunc.h"
# include "../ir/IRZext.h"
# include "../ir/IRSext.h"
# include "CodegenFunction.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace JaneZ {
class InstrSelect {
public:
    std::vector<ASMInstr> instrs;
    std::unordered_map<std::shared_ptr<IRBlock>, std::shared_ptr<ASMBlock>> blockMap;
    std::shared_ptr<IRBlock> currentIRBlock;

    int exitblock = 1;
    int currenctExitBlock = 1;

    std::string currentFuncExitLabel;

    std::vector<std::shared_ptr<ASMBlock>> asmBlocks;
    std::shared_ptr<ASMBlock> currentBlock;

    int currentStackSize = 0;
    int stackOffset = 0;
    std::unordered_map<std::shared_ptr<IRNode>, int> varStackOffset; // fallback stack slots
    std::unordered_map<std::shared_ptr<IRNode>, int> valueRegMap;
    int nextVirtualReg = 32;

    int newVirtualReg() {
        return nextVirtualReg++;
    }

    int getValueReg(const std::shared_ptr<IRNode> &val) {
        auto it = valueRegMap.find(val);
        if (it != valueRegMap.end()) {
            return it->second;
        }
        int vreg = newVirtualReg();
        valueRegMap[val] = vreg;
        return vreg;
    }

    int getStackSlot(std::shared_ptr<IRNode> var) {
        if (varStackOffset.find(var) != varStackOffset.end()) {
            return varStackOffset[var];
        }
        int offset = stackOffset;
        stackOffset += 4;
        varStackOffset[var] = offset;
        return offset;
    }

    // Load value to a working register.
    // IR values are primarily materialized in virtual registers and copied here.
    void loadToReg(std::shared_ptr<IRNode> val, int physReg,bool tag = false,int newOffest = 0) {
        if (auto *lit = dynamic_cast<IRLiteral *>(val.get())) {
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG;
            liInstr.rd.value = physReg;
            liInstr.imm.type = OperandType::IMM;
            liInstr.imm.value = lit->intValue;
            currentBlock->instrs.push_back(liInstr);
            return;
        }

        auto regIt = valueRegMap.find(val);
        if (regIt != valueRegMap.end()) {
            ASMInstr mvInstr;
            mvInstr.op = ASMOp::MV;
            mvInstr.rd.type = OperandType::REG;
            mvInstr.rd.value = physReg;
            mvInstr.rs1.type = OperandType::REG;
            mvInstr.rs1.value = regIt->second;
            currentBlock->instrs.push_back(mvInstr);
            return;
        }

        // Fallback for values that are still stack-resident.
        int offset = getStackSlot(val);
        if(tag){
            offset += newOffest;
        }
        if (offset >= -2048 and offset <= 2047) {
            ASMInstr lwInstr;
            lwInstr.op = ASMOp::LW;
            lwInstr.rd.type = OperandType::REG;
            lwInstr.rd.value = physReg;
            lwInstr.rs1.type = OperandType::REG;
            lwInstr.rs1.value = 2; // sp
            lwInstr.imm.type = OperandType::IMM;
            lwInstr.imm.value = offset;
            currentBlock->instrs.push_back(lwInstr);
        } else {
            int tempReg = 28; // t3
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG;
            liInstr.rd.value = tempReg;
            liInstr.imm.type = OperandType::IMM;
            liInstr.imm.value = offset;
            currentBlock->instrs.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd.type = OperandType::REG;
            addInstr.rd.value = tempReg;
            addInstr.rs1.type = OperandType::REG;
            addInstr.rs1.value = tempReg;
            addInstr.rs2.type = OperandType::REG;
            addInstr.rs2.value = 2; // sp
            currentBlock->instrs.push_back(addInstr);

            ASMInstr lwInstr;
            lwInstr.op = ASMOp::LW;
            lwInstr.rd.type = OperandType::REG;
            lwInstr.rd.value = physReg;
            lwInstr.rs1.type = OperandType::REG;
            lwInstr.rs1.value = tempReg;
            lwInstr.imm.type = OperandType::IMM;
            lwInstr.imm.value = 0;
            currentBlock->instrs.push_back(lwInstr);
        }
    }

    // Store value from a working register into a virtual register owner.
    void storeFromReg(int physReg, std::shared_ptr<IRNode> val) {
        int vreg = getValueReg(val);
        if (vreg == physReg) {
            return;
        }
        ASMInstr mvInstr;
        mvInstr.op = ASMOp::MV;
        mvInstr.rd.type = OperandType::REG;
        mvInstr.rd.value = vreg;
        mvInstr.rs1.type = OperandType::REG;
        mvInstr.rs1.value = physReg;
        currentBlock->instrs.push_back(mvInstr);
    }

    // Keep explicit fallback for places that must write memory slots.
    void storeFromRegToStack(int physReg, std::shared_ptr<IRNode> val) {
        int offset = getStackSlot(val);
        if (offset >= -2048 and offset <= 2047) {
            ASMInstr swInstr;
            swInstr.op = ASMOp::SW;
            swInstr.rs2.type = OperandType::REG;
            swInstr.rs2.value = physReg;
            swInstr.rs1.type = OperandType::REG;
            swInstr.rs1.value = 2; // sp
            swInstr.imm.type = OperandType::IMM;
            swInstr.imm.value = offset;
            currentBlock->instrs.push_back(swInstr);
        } else {
            int tempReg = 28; // t3
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG;
            liInstr.rd.value = tempReg;
            liInstr.imm.type = OperandType::IMM;
            liInstr.imm.value = offset;
            currentBlock->instrs.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd.type = OperandType::REG;
            addInstr.rd.value = tempReg;
            addInstr.rs1.type = OperandType::REG;
            addInstr.rs1.value = tempReg;
            addInstr.rs2.type = OperandType::REG;
            addInstr.rs2.value = 2; // sp
            currentBlock->instrs.push_back(addInstr);

            ASMInstr swInstr;
            swInstr.op = ASMOp::SW;
            swInstr.rs2.type = OperandType::REG;
            swInstr.rs2.value = physReg;
            swInstr.rs1.type = OperandType::REG;
            swInstr.rs1.value = tempReg;
            swInstr.imm.type = OperandType::IMM;
            swInstr.imm.value = 0;
            currentBlock->instrs.push_back(swInstr);
        }
    }

    void handlePhiCopies(std::shared_ptr<IRBlock> targetBlock) {
        if (!targetBlock) {
            return;
        }
        for (auto &instr : targetBlock->instrList) {
            if (auto *phi = dynamic_cast<IRPhi *>(instr.get())) {
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

            } else if (auto *phi = dynamic_cast<IRPHI *>(instr.get())) {
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
            }
        }
    }

    void select(std::shared_ptr<IRRoot> irRoot){
        asmBlocks.clear();
        for(auto &func: irRoot->children){
            if(auto *irFunc = dynamic_cast<IRFunction *>(func.get())){
                selectFunc(std::make_shared<IRFunction>(*irFunc));
            } else if (auto *irImpl = dynamic_cast<IRImpl *>(func.get())) {
                for (auto &implFunc : irImpl->functions) {
                    selectFunc(std::make_shared<IRFunction>(*implFunc));
                }
            }
        }
    }

    void selectFunc(std::shared_ptr<IRFunction> irInstr){
        blockMap.clear();
        stackOffset = 0;
        varStackOffset.clear();
        valueRegMap.clear();
        nextVirtualReg = 32;

        for(auto &func: irInstr->funcList){
            selectFunc(func);
        }

        int myExitBlockID = exitblock++;
        currenctExitBlock = myExitBlockID;
        currentFuncExitLabel = ".L" + std::to_string(currenctExitBlock);

        std::string funcName = irInstr->name;
        if (irInstr->parentStructType) {
            funcName = irInstr->parentStructType->name + "_" + funcName;
        }

        std::shared_ptr<ASMBlock> entryBlock = std::make_shared<ASMBlock>(funcName);
        asmBlocks.push_back(entryBlock);
        
        if(irInstr->body){
            blockMap[irInstr->body] = entryBlock;
            for(auto &block: irInstr->body->blockList){
                int id = (int)block->label;
                std::shared_ptr<ASMBlock> ab = std::make_shared<ASMBlock>(".L" + std::to_string(id));
                blockMap[block] = ab;
                asmBlocks.push_back(ab);
            }
            currentBlock = entryBlock;
            currentIRBlock = irInstr->body;

            // Spill arguments
            int argCount = irInstr->paramList->paramList.size();
            for(int i = 0; i < argCount; i++){
                if(i < 8){
                    storeFromReg(10 + i, irInstr->paramList->paramList[i]);
                }else{
                    int stackParamOffset = (i - 8) * 4;
                    ASMInstr lwInstr;
                    lwInstr.op = ASMOp::LW;
                    lwInstr.rd.type = OperandType::REG;
                    lwInstr.rd.value = 5;
                    lwInstr.rs1.type = OperandType::REG;
                    lwInstr.rs1.value = 8; 
                    lwInstr.imm.type = OperandType::IMM;
                    lwInstr.imm.value = stackParamOffset;
                    currentBlock->instrs.push_back(lwInstr);
                    storeFromReg(5, irInstr->paramList->paramList[i]);
                }
            }

            for(auto &instr: irInstr->body->instrList){
                if(auto allocaOp = std::dynamic_pointer_cast<IRAlloca>(instr)){
                    selectAlloca(allocaOp);
                }
            }

            for(auto &block: irInstr->body->blockList){
                for(auto &instr: block->instrList){
                    if(auto allocaOp = std::dynamic_pointer_cast<IRAlloca>(instr)){
                        selectAlloca(allocaOp);
                    }
                }
             }

            for(auto &instr: irInstr->body->instrList){
                if(auto allocaOp = std::dynamic_pointer_cast<IRAlloca>(instr)){
                    continue;
                }
                selectInstr(instr);
            }
            for(auto &block: irInstr->body->blockList){
                currentBlock = blockMap[block];
                currentIRBlock = block;
                for(auto &instr: block->instrList){
                    if(auto allocaOp = std::dynamic_pointer_cast<IRAlloca>(instr)){
                        continue;
                    }
                    selectInstr(instr);
                }
            }
        }
        
        currentStackSize = stackOffset + 8;
        if (currentStackSize % 16 != 0) {
            currentStackSize = ((currentStackSize / 16) + 1) * 16;
        }

        std::vector<ASMInstr> prologue;
        
        if (currentStackSize >= -2048 and currentStackSize <= 2047) {
            ASMInstr addiInstr;
            addiInstr.op = ASMOp::ADDI;
            addiInstr.rd = Operand(OperandType::REG, 2);
            addiInstr.rs1 = Operand(OperandType::REG, 2);
            addiInstr.imm = Operand(OperandType::IMM, -currentStackSize);
            prologue.push_back(addiInstr);
        } else {
            int tempReg = 5; // t0
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, -currentStackSize);
            prologue.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, 2);
            addInstr.rs1 = Operand(OperandType::REG, 2);
            addInstr.rs2 = Operand(OperandType::REG, tempReg);
            prologue.push_back(addInstr);
        }

        // sw ra, offset(sp)
        int raOffset = currentStackSize - 4;
        if (raOffset >= -2048 and raOffset <= 2047) {
            ASMInstr swRa;
            swRa.op = ASMOp::SW;
            swRa.rs2 = Operand(OperandType::REG, 1);
            swRa.rs1 = Operand(OperandType::REG, 2);
            swRa.imm = Operand(OperandType::IMM, raOffset);
            prologue.push_back(swRa);
        } else {
            int tempReg = 5; // t0
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, raOffset);
            prologue.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, tempReg);
            addInstr.rs1 = Operand(OperandType::REG, tempReg);
            addInstr.rs2 = Operand(OperandType::REG, 2);
            prologue.push_back(addInstr);

            ASMInstr swRa;
            swRa.op = ASMOp::SW;
            swRa.rs2 = Operand(OperandType::REG, 1);
            swRa.rs1 = Operand(OperandType::REG, tempReg);
            swRa.imm = Operand(OperandType::IMM, 0);
            prologue.push_back(swRa);
        }

        // sw s0, offset(sp)
        int s0Offset = currentStackSize - 8;
        if (s0Offset >= -2048 and s0Offset <= 2047) {
            ASMInstr swS0;
            swS0.op = ASMOp::SW;
            swS0.rs2 = Operand(OperandType::REG, 8);
            swS0.rs1 = Operand(OperandType::REG, 2);
            swS0.imm = Operand(OperandType::IMM, s0Offset);
            prologue.push_back(swS0);
        } else {
            int tempReg = 5; // t0
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, s0Offset);
            prologue.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, tempReg);
            addInstr.rs1 = Operand(OperandType::REG, tempReg);
            addInstr.rs2 = Operand(OperandType::REG, 2);
            prologue.push_back(addInstr);

            ASMInstr swS0;
            swS0.op = ASMOp::SW;
            swS0.rs2 = Operand(OperandType::REG, 8);
            swS0.rs1 = Operand(OperandType::REG, tempReg);
            swS0.imm = Operand(OperandType::IMM, 0);
            prologue.push_back(swS0);
        }

        // addi s0, sp, size
        if (currentStackSize >= -2048 and currentStackSize <= 2047) {
            ASMInstr addiS0;
            addiS0.op = ASMOp::ADDI;
            addiS0.rd = Operand(OperandType::REG, 8);
            addiS0.rs1 = Operand(OperandType::REG, 2);
            addiS0.imm = Operand(OperandType::IMM, currentStackSize);
            prologue.push_back(addiS0);
        } else {
            int tempReg = 5; // t0
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, currentStackSize);
            prologue.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, 8);
            addInstr.rs1 = Operand(OperandType::REG, 2);
            addInstr.rs2 = Operand(OperandType::REG, tempReg);
            prologue.push_back(addInstr);
        }

        entryBlock->instrs.insert(entryBlock->instrs.begin(), prologue.begin(), prologue.end());

        // Epilogue
        std::shared_ptr<ASMBlock> exitBlock = std::make_shared<ASMBlock>(currentFuncExitLabel);
        currentBlock = exitBlock;
        asmBlocks.push_back(exitBlock);

        if(auto retType = std::dynamic_pointer_cast<IRStructType>(irInstr->retType)){
            //lw to a0
            auto lastParam = irInstr->paramList->paramList.back();
            loadToReg(lastParam, 5); // t0
            ASMInstr mvA0;
            mvA0.op = ASMOp::MV;
            mvA0.rd = Operand(OperandType::REG, 10); // a0
            mvA0.rs1 = Operand(OperandType::REG, 5); // t0
            currentBlock->instrs.push_back(mvA0);
        }else if(auto retType = std::dynamic_pointer_cast<IRArrayType>(irInstr->retType)){
            //lw to a0
            auto lastParam = irInstr->paramList->paramList.back();
            loadToReg(lastParam, 5); // t0
            ASMInstr mvA0;
            mvA0.op = ASMOp::MV;
            mvA0.rd = Operand(OperandType::REG, 10); // a0
            mvA0.rs1 = Operand(OperandType::REG, 5); // t0
            currentBlock->instrs.push_back(mvA0);
        }

        // lw ra, offset(sp)
        if (raOffset >= -2048 and raOffset <= 2047) {
            ASMInstr lwRa;
            lwRa.op = ASMOp::LW;
            lwRa.rd = Operand(OperandType::REG, 1);
            lwRa.rs1 = Operand(OperandType::REG, 2);
            lwRa.imm = Operand(OperandType::IMM, raOffset);
            currentBlock->instrs.push_back(lwRa);
        } else {
            int tempReg = 5; // t0
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, raOffset);
            currentBlock->instrs.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, tempReg);
            addInstr.rs1 = Operand(OperandType::REG, tempReg);
            addInstr.rs2 = Operand(OperandType::REG, 2);
            currentBlock->instrs.push_back(addInstr);

            ASMInstr lwRa;
            lwRa.op = ASMOp::LW;
            lwRa.rd = Operand(OperandType::REG, 1);
            lwRa.rs1 = Operand(OperandType::REG, tempReg);
            lwRa.imm = Operand(OperandType::IMM, 0);
            currentBlock->instrs.push_back(lwRa);
        }

        // lw s0, offset(sp)
        if (s0Offset >= -2048 and s0Offset <= 2047) {
            ASMInstr lwS0;
            lwS0.op = ASMOp::LW;
            lwS0.rd = Operand(OperandType::REG, 8);
            lwS0.rs1 = Operand(OperandType::REG, 2);
            lwS0.imm = Operand(OperandType::IMM, s0Offset);
            currentBlock->instrs.push_back(lwS0);
        } else {
            int tempReg = 5; // t0
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, s0Offset);
            currentBlock->instrs.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, tempReg);
            addInstr.rs1 = Operand(OperandType::REG, tempReg);
            addInstr.rs2 = Operand(OperandType::REG, 2);
            currentBlock->instrs.push_back(addInstr);

            ASMInstr lwS0;
            lwS0.op = ASMOp::LW;
            lwS0.rd = Operand(OperandType::REG, 8);
            lwS0.rs1 = Operand(OperandType::REG, tempReg);
            lwS0.imm = Operand(OperandType::IMM, 0);
            currentBlock->instrs.push_back(lwS0);
        }

        // addi sp, sp, size
        if (currentStackSize >= -2048 and currentStackSize <= 2047) {
            ASMInstr addiSp;
            addiSp.op = ASMOp::ADDI;
            addiSp.rd = Operand(OperandType::REG, 2);
            addiSp.rs1 = Operand(OperandType::REG, 2);
            addiSp.imm = Operand(OperandType::IMM, currentStackSize);
            currentBlock->instrs.push_back(addiSp);
        } else {
            int tempReg = 5; // t0
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, currentStackSize);
            currentBlock->instrs.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, 2);
            addInstr.rs1 = Operand(OperandType::REG, 2);
            addInstr.rs2 = Operand(OperandType::REG, tempReg);
            currentBlock->instrs.push_back(addInstr);
        }

        //jr ra
        ASMInstr jrRa;
        jrRa.op = ASMOp::JR;
        jrRa.rs1 = Operand(OperandType::REG, 1);
        currentBlock->instrs.push_back(jrRa);
    }

    void selectInstr(std::shared_ptr<IRNode> instr){
        if(auto binaryOp = std::dynamic_pointer_cast<IRBinaryop>(instr)){
            selectBinaryOp(binaryOp);
        } else if(auto allocaOp = std::dynamic_pointer_cast<IRAlloca>(instr)){
            selectAlloca(allocaOp);
        } else if(auto loadOp = std::dynamic_pointer_cast<IRLoad>(instr)){
            selectLoad(loadOp);
        } else if(auto storeOp = std::dynamic_pointer_cast<IRStore>(instr)){
            selectStore(storeOp);
        } else if(auto getptrOp = std::dynamic_pointer_cast<IRGetptr>(instr)){
            selectGetptr(getptrOp);
        } else if(auto brOp = std::dynamic_pointer_cast<IRBr>(instr)){
            selectBr(brOp);
        } else if(auto retOp = std::dynamic_pointer_cast<IRReturn>(instr)){
            selectReturn(retOp);
        } else if(auto callOp = std::dynamic_pointer_cast<IRCall>(instr)){
            selectCall(callOp);
        } else if(auto printOp = std::dynamic_pointer_cast<IRPrint>(instr)){
            selectPrint(printOp);
        } else if(auto exitOp = std::dynamic_pointer_cast<IRExit>(instr)){
            selectExit(exitOp);
        } else if(auto getintOp = std::dynamic_pointer_cast<IRGetint>(instr)){
            selectGetint(getintOp);
        } else if(auto memOp = std::dynamic_pointer_cast<IRMemcpy>(instr)){
            selectMemcpy(memOp);
        } else if(auto memSet = std::dynamic_pointer_cast<IRMemset>(instr)){
            selectMemset(memSet);
        }else if(auto truncOp = std::dynamic_pointer_cast<IRTrunc>(instr)){
            selectTrunc(truncOp);
        }else if(auto zextOp = std::dynamic_pointer_cast<IRZext>(instr)){
            selectZext(zextOp);
        }else if(auto sextOp = std::dynamic_pointer_cast<IRSext>(instr)){
            selectSext(sextOp);
        }
    }

    void selectBinaryOp(std::shared_ptr<IRBinaryop> binaryOp) {
        loadToReg(binaryOp->leftValue, 5); // t0
        loadToReg(binaryOp->rightValue, 6); // t1

        ASMInstr instr;
        instr.rd = Operand(OperandType::REG, 5); // t0
        instr.rs1 = Operand(OperandType::REG, 5);
        instr.rs2 = Operand(OperandType::REG, 6);

        switch (binaryOp->op) {
            case IROp::ADD: instr.op = ASMOp::ADD; break;
            case IROp::SUB: instr.op = ASMOp::SUB; break;
            case IROp::MUL: instr.op = ASMOp::MUL; break;
            case IROp::DIV: {
                instr.op = ASMOp::DIV;
                if(binaryOp->utag){
                    instr.op = ASMOp::DIVU;
                }
                break;
            }
            case IROp::MOD: {
                instr.op = ASMOp::REM; 
                if(binaryOp->utag){
                    instr.op = ASMOp::REMU;
                }
                break;
            }
            case IROp::LT:  instr.op = ASMOp::SLT; break;
            case IROp::GT:
                // a > b  <=>  b < a
                instr.op = ASMOp::SLT;
                instr.rs1 = Operand(OperandType::REG, 6); // rhs
                instr.rs2 = Operand(OperandType::REG, 5); // lhs
                break;
            case IROp::LEQ: {
                                ASMInstr sltInstr;
                                sltInstr.op = ASMOp::SLT;
                                sltInstr.rd = Operand(OperandType::REG, 5);
                                sltInstr.rs1 = Operand(OperandType::REG, 6); // rhs
                                sltInstr.rs2 = Operand(OperandType::REG, 5); // lhs
                                currentBlock->instrs.push_back(sltInstr);
                                
                                ASMInstr xorInstr;
                                xorInstr.op = ASMOp::XORI;
                                xorInstr.rd = Operand(OperandType::REG, 5);
                                xorInstr.rs1 = Operand(OperandType::REG, 5);
                                xorInstr.imm = Operand(OperandType::IMM, 1);
                                currentBlock->instrs.push_back(xorInstr);
                                storeFromReg(5, binaryOp->result);
                                return;
                            }
            case IROp::GEQ: {
                                ASMInstr sltInstr;
                                sltInstr.op = ASMOp::SLT;
                                sltInstr.rd = Operand(OperandType::REG, 5);
                                sltInstr.rs1 = Operand(OperandType::REG, 5); // lhs
                                sltInstr.rs2 = Operand(OperandType::REG, 6); // rhs
                                currentBlock->instrs.push_back(sltInstr);
                                
                                ASMInstr xorInstr;
                                xorInstr.op = ASMOp::XORI;
                                xorInstr.rd = Operand(OperandType::REG, 5);
                                xorInstr.rs1 = Operand(OperandType::REG, 5);
                                xorInstr.imm = Operand(OperandType::IMM, 1);
                                currentBlock->instrs.push_back(xorInstr);
                                storeFromReg(5, binaryOp->result);
                                return;
                            }
            case IROp::EQ:  {
                                ASMInstr subInstr;
                                subInstr.op = ASMOp::SUB;
                                subInstr.rd = Operand(OperandType::REG, 5);
                                subInstr.rs1 = Operand(OperandType::REG, 5);
                                subInstr.rs2 = Operand(OperandType::REG, 6);
                                currentBlock->instrs.push_back(subInstr);

                                ASMInstr seqzInstr;
                                seqzInstr.op = ASMOp::SEQZ;
                                seqzInstr.rd = Operand(OperandType::REG, 5);
                                seqzInstr.rs1 = Operand(OperandType::REG, 5);
                                currentBlock->instrs.push_back(seqzInstr);
                                storeFromReg(5, binaryOp->result);
                                return;
                            }
            case IROp::NEQ: // sub t0, t0, t1; snez t0, t0
                            {
                                ASMInstr subInstr;
                                subInstr.op = ASMOp::SUB;
                                subInstr.rd = Operand(OperandType::REG, 5);
                                subInstr.rs1 = Operand(OperandType::REG, 5);
                                subInstr.rs2 = Operand(OperandType::REG, 6);
                                currentBlock->instrs.push_back(subInstr);

                                ASMInstr snezInstr;
                                snezInstr.op = ASMOp::SNEZ;
                                snezInstr.rd = Operand(OperandType::REG, 5);
                                snezInstr.rs1 = Operand(OperandType::REG, 5);
                                currentBlock->instrs.push_back(snezInstr);
                                storeFromReg(5, binaryOp->result);
                                return;
                            }
            case IROp::ANDOP: instr.op = ASMOp::AND; break;
            case IROp::OROP:  instr.op = ASMOp::OR; break;
            case IROp::XOROP: instr.op = ASMOp::XOR; break;
            case IROp::LEFTSHIFTOP: instr.op = ASMOp::SLL; break;
            case IROp::RIGHTSHIFTOP: instr.op = ASMOp::SRA; break; // Arithmetic shift right for signed int
            default: break;
        }
        currentBlock->instrs.push_back(instr);
        storeFromReg(5, binaryOp->result);
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
        
        if (dataOffset >= -2048 and dataOffset <= 2047) {
            ASMInstr addrInstr;
            addrInstr.op = ASMOp::ADDI;
            addrInstr.rd = Operand(OperandType::REG, 5); // t0
            addrInstr.rs1 = Operand(OperandType::REG, 2); // sp
            addrInstr.imm = Operand(OperandType::IMM, dataOffset);
            currentBlock->instrs.push_back(addrInstr);
        } else {
            int tempReg = 6; // t1
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd = Operand(OperandType::REG, tempReg);
            liInstr.imm = Operand(OperandType::IMM, dataOffset);
            currentBlock->instrs.push_back(liInstr);

            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd = Operand(OperandType::REG, 5); // t0
            addInstr.rs1 = Operand(OperandType::REG, 2); // sp
            addInstr.rs2 = Operand(OperandType::REG, tempReg);
            currentBlock->instrs.push_back(addInstr);
        }
        storeFromReg(5, allocaOp->var);
    }

    void selectLoad(std::shared_ptr<IRLoad> loadOp){
        loadToReg(loadOp->addressVar, 5); // t0 = address
        //lw t0, 0(t0)
        if(loadOp->type->type == BaseType::PTR){
            storeFromReg(5, loadOp->tmp);
            return;
        }
        ASMInstr lwInstr;
        lwInstr.op = ASMOp::LW;
        lwInstr.rd = Operand(OperandType::REG, 5);
        lwInstr.rs1 = Operand(OperandType::REG, 5);
        lwInstr.imm = Operand(OperandType::IMM, 0);
        currentBlock->instrs.push_back(lwInstr);
        
        storeFromReg(5, loadOp->tmp);
    }

    void selectStore(std::shared_ptr<IRStore> storeOp){
        if(storeOp->valueType->type == BaseType::PTR){
            loadToReg(storeOp->storeValue, 5); // t0 = value
            storeFromReg(5, storeOp->address);
            return;
        }
        if(storeOp->storeLiteral){
            loadToReg(storeOp->storeLiteral, 5); // t0 = value
        } else {
            loadToReg(storeOp->storeValue, 5); // t0 = value
        }
        loadToReg(storeOp->address, 6);   // t1 = address
        ASMInstr swInstr;
        swInstr.op = ASMOp::SW;
        swInstr.rs2 = Operand(OperandType::REG, 5); // value
        swInstr.rs1 = Operand(OperandType::REG, 6); // address
        swInstr.imm = Operand(OperandType::IMM, 0);
        currentBlock->instrs.push_back(swInstr);
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

        std::shared_ptr<IRType> pointedType = nullptr;
        if(auto ptrType = std::dynamic_pointer_cast<IRPtrType>(getptrOp->base->type)){
            pointedType = ptrType->baseType;
        } else {
            pointedType = getptrOp->base->type;
        }

        if(getptrOp->index){
            int elemSize = 0;
            if(auto array = std::dynamic_pointer_cast<IRArrayType>(pointedType)){
                elemSize = array->elementType->size;
            } else {
                elemSize = pointedType->size;
            }
            
            loadToReg(getptrOp->index, 6); // t1 = index
            
            ASMInstr liInstr;
            liInstr.op = ASMOp::LI;
            liInstr.rd.type = OperandType::REG; 
            liInstr.rd.value = 7; 
            liInstr.imm.type = OperandType::IMM; 
            liInstr.imm.value = elemSize;
            currentBlock->instrs.push_back(liInstr);
            
            ASMInstr mulInstr;
            mulInstr.op = ASMOp::MUL;
            mulInstr.rd.type = OperandType::REG; 
            mulInstr.rd.value = 6; 
            mulInstr.rs1.type = OperandType::REG; 
            mulInstr.rs1.value = 6;
            mulInstr.rs2.type = OperandType::REG; 
            mulInstr.rs2.value = 7;
            currentBlock->instrs.push_back(mulInstr);
            
            ASMInstr addInstr;
            addInstr.op = ASMOp::ADD;
            addInstr.rd.type = OperandType::REG; 
            addInstr.rd.value = 5; 
            addInstr.rs1.type = OperandType::REG; 
            addInstr.rs1.value = 5;
            addInstr.rs2.type = OperandType::REG; 
            addInstr.rs2.value = 6;
            currentBlock->instrs.push_back(addInstr);
        }else if(getptrOp->offset != -1){
            int offset = 0;
            if(auto structType = std::dynamic_pointer_cast<IRStructType>(pointedType)){
                offset = caculateStructOffset(structType, getptrOp->offset);
            } else if(auto array = std::dynamic_pointer_cast<IRArrayType>(pointedType)){
                offset = getptrOp->offset * array->elementType->size;
            } else {
                offset = getptrOp->offset * pointedType->size;
            }
            
            if(offset >= -2048 and offset <= 2047){
                ASMInstr addInstr;
                addInstr.op = ASMOp::ADDI;
                addInstr.rd.type = OperandType::REG; 
                addInstr.rd.value = 5; 
                addInstr.rs1.type = OperandType::REG; 
                addInstr.rs1.value = 5;
                addInstr.imm.type = OperandType::IMM; 
                addInstr.imm.value = offset;
                currentBlock->instrs.push_back(addInstr);
            }else{
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG; 
                liInstr.rd.value = 6; // t1
                liInstr.imm.type = OperandType::IMM; 
                liInstr.imm.value = offset;
                currentBlock->instrs.push_back(liInstr);
                ASMInstr addInstr;
                addInstr.op = ASMOp::ADD;
                addInstr.rd.type = OperandType::REG; 
                addInstr.rd.value = 5; 
                addInstr.rs1.type = OperandType::REG; 
                addInstr.rs1.value = 5;
                addInstr.rs2.type = OperandType::REG; 
                addInstr.rs2.value = 6;
                currentBlock->instrs.push_back(addInstr);
            }
        }
        storeFromReg(5, getptrOp->res);
    }

    void selectBr(std::shared_ptr<IRBr> brOp){
        handlePhiCopies(brOp->trueLabel);
        
        if(brOp->condition){
            handlePhiCopies(brOp->falseLabel);
            
            loadToReg(brOp->condition, 5); // t0
            // bnez t0, label
            ASMInstr bnezInstr;
            bnezInstr.op = ASMOp::BNEZ;
            bnezInstr.rs1 = Operand(OperandType::REG, 5);
            bnezInstr.label = Operand(OperandType::LABEL, (int)brOp->trueLabel->label);
            currentBlock->instrs.push_back(bnezInstr);
            
            // j label
            ASMInstr jInstr;
            jInstr.op = ASMOp::J;
            jInstr.label = Operand(OperandType::LABEL, (int)brOp->falseLabel->label);
            currentBlock->instrs.push_back(jInstr);
        } else {
            ASMInstr jInstr;
            jInstr.op = ASMOp::J;
            jInstr.label = Operand(OperandType::LABEL, (int)brOp->trueLabel->label);
            currentBlock->instrs.push_back(jInstr);
        }
    }

    void selectReturn(std::shared_ptr<IRReturn> retOp){
        if(retOp->returnLiteral){
            loadToReg(retOp->returnLiteral, 10); // a0
        }else{
            loadToReg(retOp->returnValue, 10); // a0
        }
        ASMInstr jInstr;
        jInstr.op = ASMOp::J;
        jInstr.label = Operand(OperandType::LABEL, currenctExitBlock);
        currentBlock->instrs.push_back(jInstr);
    }

    void selectCall(std::shared_ptr<IRCall> callOp){
        int totalParamCount = callOp->pList->paramList.size();

        int regParamCount = totalParamCount > 8 ? 8 : totalParamCount;
        for(int i = 0; i < regParamCount; i++){
            loadToReg(callOp->pList->paramList[i], 10 + i);
        }
        
        if (totalParamCount > 8) {
            int stackBytesNeeded = (totalParamCount - 8) * 4;
            ASMInstr addiSp;
            addiSp.op = ASMOp::ADDI;
            addiSp.rd = Operand(OperandType::REG, 2);
            addiSp.rs1 = Operand(OperandType::REG, 2);
            addiSp.imm = Operand(OperandType::IMM, -stackBytesNeeded);
            currentBlock->instrs.push_back(addiSp);

            for(int i = 8; i < totalParamCount; i++){
                loadToReg(callOp->pList->paramList[i], 5,true, stackBytesNeeded);
                ASMInstr swInstr;
                swInstr.op = ASMOp::SW;
                swInstr.rs2 = Operand(OperandType::REG, 5); 
                swInstr.rs1 = Operand(OperandType::REG, 2); 
                swInstr.imm = Operand(OperandType::IMM, (i - 8) * 4);
                currentBlock->instrs.push_back(swInstr);
            }
        }
        
        ASMInstr callInstr;
        callInstr.op = ASMOp::CALL;
        std::string targetName = callOp->function->name;
        if (callOp->function->parentStructType) {
            targetName = callOp->function->parentStructType->name + "_" + targetName;
        }
        callInstr.funcName = targetName;
        currentBlock->instrs.push_back(callInstr);

        // Clean up stack space for parameters
        if (totalParamCount > 8) {
            int stackBytesToClean = (totalParamCount - 8) * 4;
            ASMInstr addiSp;
            addiSp.op = ASMOp::ADDI;
            addiSp.rd = Operand(OperandType::REG, 2);
            addiSp.rs1 = Operand(OperandType::REG, 2);
            addiSp.imm = Operand(OperandType::IMM, stackBytesToClean);
            currentBlock->instrs.push_back(addiSp);
        }
        
        if (callOp->retVar) {
            storeFromReg(10, callOp->retVar);
        }
    }

    void selectPrint(std::shared_ptr<IRPrint> printOp){
        if (printOp->printVar) {
             loadToReg(printOp->printVar, 10); // a0
             
            ASMInstr callInstr;
            callInstr.op = ASMOp::CALL;
            if (printOp->inttag) {
                callInstr.funcName = "printInt";
            } else {
                callInstr.funcName = "printlnInt";
            }
            currentBlock->instrs.push_back(callInstr);
        }
    }

    void selectExit(std::shared_ptr<IRExit> exitOp){
        if (exitOp->exitCode) {
            loadToReg(exitOp->exitCode, 10); // a0
        } else {
             ASMInstr liInstr;
             liInstr.op = ASMOp::LI;
             liInstr.rd.type = OperandType::REG;
             liInstr.rd.value = 10; // a0
             liInstr.imm.type = OperandType::IMM;
             liInstr.imm.value = 0; // exit code 0
             currentBlock->instrs.push_back(liInstr);
        }

        ASMInstr callInstr;
        callInstr.op = ASMOp::CALL;
        callInstr.funcName = "__builtin_exit";
        currentBlock->instrs.push_back(callInstr);
    }

    void selectGetint(std::shared_ptr<IRGetint> getintOp){
        ASMInstr callInstr;
        callInstr.op = ASMOp::CALL;
        callInstr.funcName = "getInt";
        currentBlock->instrs.push_back(callInstr);
        storeFromReg(10, getintOp->result);
    }

    void selectMemcpy(std::shared_ptr<IRMemcpy> memcpyOp){
        loadToReg(memcpyOp->dest, 10);
        loadToReg(memcpyOp->value, 11); 
        loadToReg(std::make_shared<IRLiteral>(INT_LITERAL,memcpyOp->size), 12);

        ASMInstr callInstr;
        callInstr.op = ASMOp::CALL;
        callInstr.funcName = "memcpy";
        currentBlock->instrs.push_back(callInstr);
    }

    void selectMemset(std::shared_ptr<IRMemset> memsetOp){
        loadToReg(memsetOp->dest, 10);
        loadToReg(std::make_shared<IRLiteral>(INT_LITERAL,memsetOp->value), 11); 
        loadToReg(std::make_shared<IRLiteral>(INT_LITERAL,memsetOp->size), 12);

        ASMInstr callInstr;
        callInstr.op = ASMOp::CALL;
        callInstr.funcName = "memset";
        currentBlock->instrs.push_back(callInstr);
    }

    void selectTrunc(std::shared_ptr<IRTrunc> truncOp){
        loadToReg(truncOp->value, 5); 
        storeFromReg(5, truncOp->result);
    }

    void selectZext(std::shared_ptr<IRZext> zextOp){
        loadToReg(zextOp->value, 5); 
        storeFromReg(5, zextOp->result);
    }

    void selectSext(std::shared_ptr<IRSext> sextOp){
        loadToReg(sextOp->value, 5); 
        storeFromReg(5, sextOp->result);
    }
};
}
