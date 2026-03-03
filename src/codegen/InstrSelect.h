# pragma once
# include "ASM.h"
# include "../ir/IRNode.h"
# include "../ir/IRBinaryop.h"
# include "../ir/IRLiteral.h"
#include <memory>
#include <vector>

namespace JaneZ {
class InstrSelect {
public:
    std::shared_ptr<IRNode> irInstr;
    std::vector<ASMInstr> instrs;

    int nextReg = 10;

    int newReg(){
        return nextReg++;
    }

    void selectBinaryOp(std::shared_ptr<IRBinaryop> binaryOp){
        bool isImm = false;
        if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->leftValue.get())){
            isImm = true;
            swap(binaryOp->leftValue, binaryOp->rightValue);
        }else if(auto *imm = dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())){
            isImm = true;
        }
        //imm >= 2048 TODO!!!
        if(binaryOp->op == ADD){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // addi rd, rs1, imm
                instr.op = ASMOp::ADDI;
                Operand imm(OperandType::IMM, dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // add rd, rs1, rs2
                instr.op = ASMOp::ADD;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == SUB){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // addi rd, rs1, -imm
                instr.op = ASMOp::ADDI;
                Operand imm(OperandType::IMM, -dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // sub rd, rs1, rs2
                instr.op = ASMOp::SUB;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == MUL){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // mul rd, rs1, imm todo
            }else{
                // mul rd, rs1, rs2
                instr.op = ASMOp::MUL;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == DIV){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // div rd, rs1, imm todo
            }else{
                // div rd, rs1, rs2
                instr.op = ASMOp::DIV;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == MOD){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // rem rd, rs1, imm todo
            }else{
                // rem rd, rs1, rs2
                instr.op = ASMOp::REM;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == XOROP){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // xori rd, rs1, imm
                instr.op = ASMOp::XORI;
                Operand imm(OperandType::IMM, dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // xor rd, rs1, rs2
                instr.op = ASMOp::XOR;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == OROP){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // ori rd, rs1, imm
                instr.op = ASMOp::ORI;
                Operand imm(OperandType::IMM, dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // or rd, rs1, rs2
                instr.op = ASMOp::OR;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == ANDOP){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // andi rd, rs1, imm
                instr.op = ASMOp::ANDI;
                Operand imm(OperandType::IMM, dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // and rd, rs1, rs2
                instr.op = ASMOp::AND;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == LEFTSHIFTOP){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // slli rd, rs1, imm
                instr.op = ASMOp::SLLI;
                Operand imm(OperandType::IMM, dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // sll rd, rs1, rs2
                instr.op = ASMOp::SLL;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == RIGHTSHIFTOP){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // srli rd, rs1, imm
                instr.op = ASMOp::SRLI;
                Operand imm(OperandType::IMM, dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // srl rd, rs1, rs2
                instr.op = ASMOp::SRL;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
        }else if(binaryOp->op == LT){
            ASMInstr instr;
            Operand rd(OperandType::REG, newReg());
            Operand rs1(OperandType::REG, newReg());
            instr.operands.push_back(rd);
            instr.operands.push_back(rs1);
            if(isImm){
                // slti rd, rs1, imm
                instr.op = ASMOp::SLTI;
                Operand imm(OperandType::IMM, dynamic_cast<IRLiteral *>(binaryOp->rightValue.get())->intValue);
                instr.operands.push_back(imm);
            }else{
                // slt rd, rs1, rs2
                instr.op = ASMOp::SLT;
                Operand rs2(OperandType::REG, newReg());
                instr.operands.push_back(rs2);
            }
            instrs.push_back(instr);
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
};
}