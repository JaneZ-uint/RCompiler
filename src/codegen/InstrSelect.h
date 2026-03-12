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
# include "../ir/IRParam.h"
# include "CodegenFunction.h"
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

    std::string currentFuncExitLabel;

    std::vector<std::shared_ptr<ASMBlock>> asmBlocks;
    std::shared_ptr<ASMBlock> currentBlock;

    int currentStackSize = 0;

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
        std::shared_ptr<CodegenFunction> codegenFunc = std::make_shared<CodegenFunction>(irInstr);
        asmBlocks.clear();
        currentFuncExitLabel = ".L" + irInstr->name + "_exit";
        //entry block
        std::shared_ptr<ASMBlock> entryBlock = std::make_shared<ASMBlock>(irInstr->name);
        asmBlocks.push_back(entryBlock);
        //wait for stack allocation
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
        //caculate stack size
        currentStackSize = (nextReg - 32) * 4;
        //entry block!
        ASMInstr addiInstr;
        addiInstr.op = ASMOp::ADDI;
        addiInstr.rd.type = OperandType::REG;
        addiInstr.rd.value = 2; // sp
        addiInstr.rs1.type = OperandType::REG;
        addiInstr.rs1.value = 2; // sp
        addiInstr.imm.type = OperandType::IMM;
        addiInstr.imm.value = -currentStackSize;
        entryBlock->instrs.push_back(addiInstr);
        ASMInstr swRaInstr;
        swRaInstr.op = ASMOp::SW;
        swRaInstr.rs1.type = OperandType::REG;
        swRaInstr.rs1.value = 1; // ra
        swRaInstr.imm.type = OperandType::IMM;
        swRaInstr.imm.value = currentStackSize - 4;
        swRaInstr.rs2.type = OperandType::REG;
        swRaInstr.rs2.value = 2; // sp
        entryBlock->instrs.push_back(swRaInstr);
        ASMInstr s0Instr;
        s0Instr.op = ASMOp::SW;
        s0Instr.rs1.type = OperandType::REG;
        s0Instr.rs1.value = 8; // s0
        s0Instr.imm.type = OperandType::IMM;
        s0Instr.imm.value = currentStackSize - 8;
        s0Instr.rs2.type = OperandType::REG;
        s0Instr.rs2.value = 2; // sp
        entryBlock->instrs.push_back(s0Instr);
        //exitBlock!
        std::shared_ptr<ASMBlock> exitBlock = std::make_shared<ASMBlock>(currentFuncExitLabel);
        ASMInstr lwRaInstr;
        lwRaInstr.op = ASMOp::LW;
        lwRaInstr.rs1.type = OperandType::REG;
        lwRaInstr.rs1.value = 2; // sp
        lwRaInstr.imm.type = OperandType::IMM;
        lwRaInstr.imm.value = currentStackSize - 4;
        lwRaInstr.rs2.type = OperandType::REG;
        lwRaInstr.rs2.value = 1; // ra
        exitBlock->instrs.push_back(lwRaInstr);
        ASMInstr lwS0Instr;
        lwS0Instr.op = ASMOp::LW;
        lwS0Instr.rs1.type = OperandType::REG;
        lwS0Instr.rs1.value = 2; // sp
        lwS0Instr.imm.type = OperandType::IMM;
        lwS0Instr.imm.value = currentStackSize - 8;
        lwS0Instr.rs2.type = OperandType::REG;
        lwS0Instr.rs2.value = 8; // s0
        exitBlock->instrs.push_back(lwS0Instr);
        ASMInstr addiSpInstr;
        addiSpInstr.op = ASMOp::ADDI;
        addiSpInstr.rd.type = OperandType::REG;
        addiSpInstr.rd.value = 2; // sp
        addiSpInstr.rs1.type = OperandType::REG;
        addiSpInstr.rs1.value = 2; // sp
        addiSpInstr.imm.type = OperandType::IMM;
        addiSpInstr.imm.value = currentStackSize;
        exitBlock->instrs.push_back(addiSpInstr);
        ASMInstr jrInstr;
        jrInstr.op = ASMOp::JR;
        jrInstr.rs1.type = OperandType::REG;
        jrInstr.rs1.value = 1; // ra
        exitBlock->instrs.push_back(jrInstr);
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
        }
    }

    void selectBinaryOp(std::shared_ptr<IRBinaryop> binaryOp){
        if(binaryOp->op == ADD || binaryOp->op == XOROP || binaryOp->op == OROP || binaryOp->op == ANDOP){
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                if(imm->intValue >= -2048 && imm->intValue <= 2047){
                    ASMInstr instr;
                    if(binaryOp->op == ADD){
                        instr.op = ASMOp::ADDI;
                    }else if(binaryOp->op == XOROP){
                        instr.op = ASMOp::XORI;
                    }else if(binaryOp->op == OROP){
                        instr.op = ASMOp::ORI;
                    }else if(binaryOp->op == ANDOP){
                        instr.op = ASMOp::ANDI;
                    }
                    instr.rd.type = OperandType::REG;
                    instr.rd.value = getReg(binaryOp->result);
                    instr.rs1.type = OperandType::REG;
                    instr.rs1.value = getReg(binaryOp->leftValue);
                    instr.imm.type = OperandType::IMM;
                    instr.imm.value = imm->intValue;
                    instrs.push_back(instr);
                }else{
                    // li tmp, imm
                    // add tmp, left, tmp
                    ASMInstr liInstr;
                    liInstr.op = ASMOp::LI;
                    liInstr.rd.type = OperandType::REG;
                    int tmpReg = newReg();
                    liInstr.rd.value = tmpReg;
                    liInstr.imm.type = OperandType::IMM;
                    liInstr.imm.value = imm->intValue;
                    instrs.push_back(liInstr);
                    ASMInstr instr;
                    instr.rd.type = OperandType::REG;
                    instr.rd.value = getReg(binaryOp->result);
                    instr.rs1.type = OperandType::REG;
                    instr.rs1.value = getReg(binaryOp->leftValue);
                    instr.rs2.type = OperandType::REG;
                    instr.rs2.value = tmpReg;
                    if(binaryOp->op == ADD){
                        instr.op = ASMOp::ADD;
                    }else if(binaryOp->op == XOROP){
                        instr.op = ASMOp::XOR;
                    }else if(binaryOp->op == OROP){
                        instr.op = ASMOp::OR;
                    }else if(binaryOp->op == ANDOP){
                        instr.op = ASMOp::AND;
                    }
                    instrs.push_back(instr);
                }
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                if(imm->intValue >= -2048 && imm->intValue <= 2047){
                    ASMInstr instr;
                    if(binaryOp->op == ADD){
                        instr.op = ASMOp::ADDI;
                    }else if(binaryOp->op == XOROP){
                        instr.op = ASMOp::XORI;
                    }else if(binaryOp->op == OROP){
                        instr.op = ASMOp::ORI;
                    }else if(binaryOp->op == ANDOP){
                        instr.op = ASMOp::ANDI;
                    }
                    instr.rd.type = OperandType::REG;
                    instr.rd.value = getReg(binaryOp->result);
                    instr.rs1.type = OperandType::REG;
                    instr.rs1.value = getReg(binaryOp->rightValue);
                    instr.imm.type = OperandType::IMM;
                    instr.imm.value = imm->intValue;
                    instrs.push_back(instr);
                }else{
                    // li tmp, imm
                    // add tmp, right, tmp
                    ASMInstr liInstr;
                    liInstr.op = ASMOp::LI;
                    liInstr.rd.type = OperandType::REG;
                    int tmpReg = newReg();
                    liInstr.rd.value = tmpReg;
                    liInstr.imm.type = OperandType::IMM;
                    liInstr.imm.value = imm->intValue;
                    instrs.push_back(liInstr);
                    ASMInstr instr;
                    instr.rd.type = OperandType::REG;
                    instr.rd.value = getReg(binaryOp->result);
                    instr.rs1.type = OperandType::REG;
                    instr.rs1.value = getReg(binaryOp->rightValue);
                    instr.rs2.type = OperandType::REG;
                    instr.rs2.value = tmpReg;
                    if(binaryOp->op == ADD){
                        instr.op = ASMOp::ADD;
                    }else if(binaryOp->op == XOROP){
                        instr.op = ASMOp::XOR;
                    }else if(binaryOp->op == OROP){
                        instr.op = ASMOp::OR;
                    }else if(binaryOp->op == ANDOP){
                        instr.op = ASMOp::AND;
                    }
                    instrs.push_back(instr);
                }
            }else{
                ASMInstr instr;
                if(binaryOp->op == ADD){
                    instr.op = ASMOp::ADD;
                }else if(binaryOp->op == XOROP){
                    instr.op = ASMOp::XOR;
                }else if(binaryOp->op == OROP){
                    instr.op = ASMOp::OR;
                }else if(binaryOp->op == ANDOP){
                    instr.op = ASMOp::AND;
                }
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == SUB){
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                if(imm->intValue >= -2047 && imm->intValue <= 2048){
                    ASMInstr instr;
                    instr.op = ASMOp::ADDI;
                    instr.rd.type = OperandType::REG;
                    instr.rd.value = getReg(binaryOp->result);
                    instr.rs1.type = OperandType::REG;
                    instr.rs1.value = getReg(binaryOp->leftValue);
                    instr.imm.type = OperandType::IMM;
                    instr.imm.value = -imm->intValue;
                    instrs.push_back(instr);    
                }else{
                    // li tmp, imm
                    // sub tmp, left, tmp
                    ASMInstr liInstr;
                    liInstr.op = ASMOp::LI;
                    liInstr.rd.type = OperandType::REG; 
                    int tmpReg = newReg();
                    liInstr.rd.value = tmpReg;
                    liInstr.imm.type = OperandType::IMM;
                    liInstr.imm.value = imm->intValue;
                    instrs.push_back(liInstr);
                    ASMInstr instr;
                    instr.op = ASMOp::SUB;
                    instr.rd.type = OperandType::REG;
                    instr.rd.value = getReg(binaryOp->result);
                    instr.rs1.type = OperandType::REG;
                    instr.rs1.value = getReg(binaryOp->leftValue);
                    instr.rs2.type = OperandType::REG;
                    instr.rs2.value = tmpReg;
                    instrs.push_back(instr);
                }
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SUB;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = tmpReg;
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }else{
                ASMInstr instr;
                instr.op = ASMOp::SUB;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == MUL || binaryOp->op == DIV || binaryOp->op == MOD){
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                // li tmp, imm
                // mul tmp, left, tmp
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                if(binaryOp->op == MUL){
                    instr.op = ASMOp::MUL;
                }else if(binaryOp->op == DIV){
                    instr.op = ASMOp::DIV;
                }else if(binaryOp->op == MOD){
                    instr.op = ASMOp::REM;
                }
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = tmpReg;
                instrs.push_back(instr);
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                // li tmp, imm
                // mul tmp, right, tmp
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                if(binaryOp->op == MUL){
                    instr.op = ASMOp::MUL;
                }else if(binaryOp->op == DIV){
                    instr.op = ASMOp::DIV;
                }else if(binaryOp->op == MOD){
                    instr.op = ASMOp::REM;
                }
                instr.rd.type = OperandType::REG;   
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = tmpReg;
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }else{
                ASMInstr instr;
                if(binaryOp->op == MUL){
                    instr.op = ASMOp::MUL;
                }else if(binaryOp->op == DIV){
                    instr.op = ASMOp::DIV;
                }else if(binaryOp->op == MOD){
                    instr.op = ASMOp::REM;
                }
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == LEFTSHIFTOP || binaryOp->op == RIGHTSHIFTOP){
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                ASMInstr instr;
                if(binaryOp->op == LEFTSHIFTOP){
                    instr.op = ASMOp::SLLI;
                }else if(binaryOp->op == RIGHTSHIFTOP){
                    instr.op = ASMOp::SRLI;
                }
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.imm.type = OperandType::IMM;
                instr.imm.value = imm->intValue;
                instrs.push_back(instr);
            }else{
                ASMInstr instr;
                if(binaryOp->op == LEFTSHIFTOP){
                    instr.op = ASMOp::SLL;
                }else if(binaryOp->op == RIGHTSHIFTOP){
                    instr.op = ASMOp::SRL;
                }
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;  
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == LT ){
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                // slti rd, rs1, imm
                ASMInstr instr;
                instr.op = ASMOp::SLTI;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.imm.type = OperandType::IMM;
                instr.imm.value = imm->intValue;
                instrs.push_back(instr);
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                // li + slti
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SLTI;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = tmpReg;
                instr.rs2.type = OperandType::REG;  
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);    
            }else{
                // slt rd, rs1, rs2
                ASMInstr instr;
                instr.op = ASMOp::SLT;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == LEQ){
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                // li + sle
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SLE;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = tmpReg;
                instrs.push_back(instr);
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                // li + sle
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SLE;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = tmpReg;
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }else{
                // sle rd, rs1, rs2
                ASMInstr instr;
                instr.op = ASMOp::SLE;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == GT){
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                // li + slt
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SLT;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = tmpReg;
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->leftValue);
                instrs.push_back(instr);
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                // slt rd, right, left
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SLT;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->rightValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = tmpReg;
                instrs.push_back(instr);
            }else{
                // slt rd, right, left
                ASMInstr instr;
                instr.op = ASMOp::SLT;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->rightValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->leftValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == GEQ){
            // sge
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                // li + sge
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SGE;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = tmpReg;
                instrs.push_back(instr);
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                // li + sge
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr instr;
                instr.op = ASMOp::SGE;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = tmpReg;
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }else{
                // sge rd, left, right
                ASMInstr instr;
                instr.op = ASMOp::SGE;
                instr.rd.type = OperandType::REG;
                instr.rd.value = getReg(binaryOp->result);
                instr.rs1.type = OperandType::REG;
                instr.rs1.value = getReg(binaryOp->leftValue);
                instr.rs2.type = OperandType::REG;
                instr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(instr);
            }
        }else if(binaryOp->op == EQ){
            // sub + seqz
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                // li tmp, imm
                // sub tmp, left, tmp
                // seqz rd, tmp
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG;
                subInstr.rd.value = newReg();
                subInstr.rs1.type = OperandType::REG;
                subInstr.rs1.value = getReg(binaryOp->leftValue);
                subInstr.rs2.type = OperandType::REG;
                subInstr.rs2.value = tmpReg;
                instrs.push_back(subInstr);
                ASMInstr seqzInstr;
                seqzInstr.op = ASMOp::SEQZ;
                seqzInstr.rd.type = OperandType::REG;
                seqzInstr.rd.value = getReg(binaryOp->result);
                seqzInstr.rs1 = subInstr.rd;
                instrs.push_back(seqzInstr);
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                // li tmp, imm
                // sub tmp, right, tmp
                // seqz rd, tmp
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG;
                subInstr.rd.value = newReg();
                subInstr.rs1.type = OperandType::REG;
                subInstr.rs1.value = getReg(binaryOp->rightValue);
                subInstr.rs2.type = OperandType::REG;
                subInstr.rs2.value = tmpReg;
                instrs.push_back(subInstr);
                ASMInstr seqzInstr;
                seqzInstr.op = ASMOp::SEQZ;
                seqzInstr.rd.type = OperandType::REG;
                seqzInstr.rd.value = getReg(binaryOp->result);
                seqzInstr.rs1 = subInstr.rd;
                instrs.push_back(seqzInstr);
            }else{
                // sub tmp, left, right
                // seqz rd, tmp
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG;
                subInstr.rd.value = newReg();
                subInstr.rs1.type = OperandType::REG;
                subInstr.rs1.value = getReg(binaryOp->leftValue);
                subInstr.rs2.type = OperandType::REG;
                subInstr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(subInstr);
                ASMInstr seqzInstr;
                seqzInstr.op = ASMOp::SEQZ;
                seqzInstr.rd.type = OperandType::REG;
                seqzInstr.rd.value = getReg(binaryOp->result);
                seqzInstr.rs1 = subInstr.rd;
                instrs.push_back(seqzInstr);
            }
        }else if(binaryOp->op == NEQ){
            // sub + snez
            if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
                // li tmp, imm
                // sub tmp, left, tmp
                // snez rd, tmp
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;  
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG;
                subInstr.rd.value = newReg();
                subInstr.rs1.type = OperandType::REG;
                subInstr.rs1.value = getReg(binaryOp->leftValue);
                subInstr.rs2.type = OperandType::REG;
                subInstr.rs2.value = tmpReg;
                instrs.push_back(subInstr);
                ASMInstr snezInstr;
                snezInstr.op = ASMOp::SNEZ;
                snezInstr.rd.type = OperandType::REG;
                snezInstr.rd.value = getReg(binaryOp->result);
                snezInstr.rs1 = subInstr.rd;
                instrs.push_back(snezInstr);
            }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
                // li tmp, imm
                // sub tmp, right, tmp
                // snez rd, tmp
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                int tmpReg = newReg();
                liInstr.rd.value = tmpReg;
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG;
                subInstr.rd.value = newReg();
                subInstr.rs1.type = OperandType::REG;
                subInstr.rs1.value = getReg(binaryOp->rightValue);
                subInstr.rs2.type = OperandType::REG;
                subInstr.rs2.value = tmpReg;
                instrs.push_back(subInstr);
                ASMInstr snezInstr;
                snezInstr.op = ASMOp::SNEZ;
                snezInstr.rd.type = OperandType::REG;
                snezInstr.rd.value = getReg(binaryOp->result);
                snezInstr.rs1 = subInstr.rd;
                instrs.push_back(snezInstr);
            }else{
                // sub tmp, left, right
                // snez rd, tmp
                ASMInstr subInstr;
                subInstr.op = ASMOp::SUB;
                subInstr.rd.type = OperandType::REG;    
                subInstr.rd.value = newReg();
                subInstr.rs1.type = OperandType::REG;
                subInstr.rs1.value = getReg(binaryOp->leftValue);
                subInstr.rs2.type = OperandType::REG;
                subInstr.rs2.value = getReg(binaryOp->rightValue);
                instrs.push_back(subInstr);
                ASMInstr snezInstr;
                snezInstr.op = ASMOp::SNEZ;
                snezInstr.rd.type = OperandType::REG;
                snezInstr.rd.value = getReg(binaryOp->result);
                snezInstr.rs1 = subInstr.rd;
                instrs.push_back(snezInstr);    
            }
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
        for(int i = 0;i < callOp->pList->paramList.size();i ++){
            Operand arg;
            arg.type = OperandType::REG;
            if(auto *imm = dynamic_cast<IRLiteral *>(callOp->pList->paramList[i].get())){
                ASMInstr liInstr;
                liInstr.op = ASMOp::LI;
                liInstr.rd.type = OperandType::REG;
                liInstr.rd.value = newReg();
                liInstr.imm.type = OperandType::IMM;
                liInstr.imm.value = imm->intValue;
                instrs.push_back(liInstr);
                arg.value = liInstr.rd.value;
            }else{
                arg.value = getReg(callOp->pList->paramList[i]);
            }
            ASMInstr mvInstr;
            mvInstr.op = ASMOp::MV;
            mvInstr.rd.type = OperandType::REG;
            mvInstr.rd.value = 10 + i;
            mvInstr.rs1 = arg;
            instrs.push_back(mvInstr);
        }
        ASMInstr callInstr;
        callInstr.op = ASMOp::CALL;
        callInstr.funcName = callOp->function->name;
        instrs.push_back(callInstr);
        ASMInstr mvInstr;
        mvInstr.op = ASMOp::MV;
        mvInstr.rd.type = OperandType::REG;
        mvInstr.rd.value = getReg(callOp->retVar);
        mvInstr.rs1.type = OperandType::REG;
        mvInstr.rs1.value = 10; // a0
        instrs.push_back(mvInstr);
    }

    
};
}