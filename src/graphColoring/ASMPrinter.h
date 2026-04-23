# pragma once

#include "ASM.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace JaneZ {
class ASMPrinter {
public:
    std::vector<std::shared_ptr<ASMBlock>> blocks;

    ASMPrinter(const std::vector<std::shared_ptr<ASMBlock>>& blocks) 
        : blocks(blocks) {}

    void print(){
        // Print header or global directives if needed
        std::cout << "    .text\n";
        
        for (const auto& block : blocks) {
            // Print block label if it exists and is not empty
            if (!block->label.empty()) {
                if (block->label[0] == '.') {
                    // Local label (e.g., .Lexit)
                    std::cout << block->label << ":\n";
                } else {
                    // Function entry label (global)
                    std::cout << "    .globl " << block->label << "\n";
                    std::cout << "    .type " << block->label << ", @function\n";
                    std::cout << block->label << ":\n";
                }
            }

            for (const auto& instr : block->instrs) {
                printInstr(instr);
            }
        }
    }

private:
    std::string getRegName(int regId) {
        // Map virtual registers to physical registers for naive allocation
        // 0-31 are physical registers in RISC-V
        // >31 are virtual registers
        
        if (regId < 32) {
            const char* regNames[] = {
                "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
                "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
                "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
                "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
            };
            return regNames[regId];
        } else {
            // For virtual registers in naive allocation
            return "v" + std::to_string(regId);
        }
    }

    void printInstr(const ASMInstr& instr) {
        std::cout << "    "; // Indent instructions
        switch (instr.op) {
            case ASMOp::ADD:  std::cout << "add"; break;
            case ASMOp::SUB:  std::cout << "sub"; break;
            case ASMOp::MUL:  std::cout << "mul"; break;
            case ASMOp::DIV:  std::cout << "div"; break;
            case ASMOp::DIVU: std::cout << "divu"; break;
            case ASMOp::REM:  std::cout << "rem"; break;
            case ASMOp::REMU: std::cout << "remu"; break;
            
            case ASMOp::AND:  std::cout << "and"; break;
            case ASMOp::OR:   std::cout << "or"; break;
            case ASMOp::XOR:  std::cout << "xor"; break;
            case ASMOp::SLL:  std::cout << "sll"; break;
            case ASMOp::SRL:  std::cout << "srl"; break;
            case ASMOp::SRA:  std::cout << "sra"; break;
            
            case ASMOp::SLT:  std::cout << "slt"; break;
            case ASMOp::SLTU: std::cout << "sltu"; break;
            case ASMOp::SLE:  std::cout << "sle"; break; 
            case ASMOp::SGE:  std::cout << "sge"; break; 
            case ASMOp::SEQZ: std::cout << "seqz"; break;
            case ASMOp::SNEZ: std::cout << "snez"; break;

            case ASMOp::ADDI: std::cout << "addi"; break;
            case ASMOp::ANDI: std::cout << "andi"; break;
            case ASMOp::ORI:  std::cout << "ori"; break;
            case ASMOp::XORI: std::cout << "xori"; break;
            case ASMOp::SLLI: std::cout << "slli"; break;
            case ASMOp::SRLI: std::cout << "srli"; break;
            case ASMOp::SRAI: std::cout << "srai"; break;
            case ASMOp::SLTI: std::cout << "slti"; break;
            case ASMOp::SLTIU: std::cout << "sltiu"; break;

            case ASMOp::LB:   std::cout << "lb"; break;
            case ASMOp::LH:   std::cout << "lh"; break;
            case ASMOp::LW:   std::cout << "lw"; break;
            case ASMOp::LBU:  std::cout << "lbu"; break;
            case ASMOp::LHU:  std::cout << "lhu"; break;
            
            case ASMOp::SB:   std::cout << "sb"; break;
            case ASMOp::SH:   std::cout << "sh"; break;
            case ASMOp::SW:   std::cout << "sw"; break;

            case ASMOp::BEQ:  std::cout << "beq"; break;
            case ASMOp::BNE:  std::cout << "bne"; break;
            case ASMOp::BLT:  std::cout << "blt"; break;
            case ASMOp::BGE:  std::cout << "bge"; break;
            case ASMOp::BLTU: std::cout << "bltu"; break;
            case ASMOp::BGEU: std::cout << "bgeu"; break;
            case ASMOp::BNEZ: std::cout << "bnez"; break;

            case ASMOp::J:    std::cout << "j"; break;
            case ASMOp::JR:   std::cout << "jr"; break;
            case ASMOp::JAL:  std::cout << "jal"; break;
            case ASMOp::JALR: std::cout << "jalr"; break;
            case ASMOp::CALL: std::cout << "call"; break;
            
            case ASMOp::LI:   std::cout << "li"; break;
            case ASMOp::MV:   std::cout << "mv"; break;
            case ASMOp::LUI:  std::cout << "lui"; break;
            
            default: std::cout << "UNKNOWN"; break;
        }

        std::cout << " ";

        if (instr.op == ASMOp::CALL) {
            std::cout << instr.funcName;
        } 
        else if (instr.op == ASMOp::J || instr.op == ASMOp::JAL) {
            if (instr.label.type == OperandType::LABEL) {
                std::cout << ".L" << instr.label.value;
            } else {
                std::cout << ".L" << instr.label.value; 
            }
        }
        else if (instr.op == ASMOp::JR) {
            std::cout << getRegName(instr.rs1.value);
        }
        else if (instr.op == ASMOp::LI || instr.op == ASMOp::LUI) {
             std::cout << getRegName(instr.rd.value) << ", " << instr.imm.value;
        }
        else if (instr.op == ASMOp::MV) {
             std::cout << getRegName(instr.rd.value) << ", " << getRegName(instr.rs1.value);
        }
        else if (instr.op == ASMOp::SEQZ || instr.op == ASMOp::SNEZ) {
             std::cout << getRegName(instr.rd.value) << ", " << getRegName(instr.rs1.value);
        }
        else if (instr.op == ASMOp::SW || instr.op == ASMOp::SB || instr.op == ASMOp::SH) {
            // S-type: sw rs2, imm(rs1)
            // rs2 is source value, rs1 is base address
            std::cout << getRegName(instr.rs2.value) << ", " 
                      << instr.imm.value << "(" << getRegName(instr.rs1.value) << ")";
        }
        else if (instr.op == ASMOp::LW || instr.op == ASMOp::LB || instr.op == ASMOp::LH || 
                 instr.op == ASMOp::LBU || instr.op == ASMOp::LHU) {
            // I-type (load): lw rd, imm(rs1)
            std::cout << getRegName(instr.rd.value) << ", " 
                      << instr.imm.value << "(" << getRegName(instr.rs1.value) << ")";
        }
        else if (instr.op == ASMOp::BEQ || instr.op == ASMOp::BNE || instr.op == ASMOp::BLT || 
                 instr.op == ASMOp::BGE || instr.op == ASMOp::BLTU || instr.op == ASMOp::BGEU) {
            std::cout << getRegName(instr.rs1.value) << ", " 
                      << getRegName(instr.rs2.value) << ", " 
                      << ".L" << instr.label.value;
        }
        else if (instr.op == ASMOp::BNEZ) {
            std::cout << getRegName(instr.rs1.value) << ", " 
                      << ".L" << instr.label.value;
        }
        else if (instr.op == ASMOp::ADDI || instr.op == ASMOp::SLTI || instr.op == ASMOp::SLTIU ||
                 instr.op == ASMOp::ANDI || instr.op == ASMOp::ORI || instr.op == ASMOp::XORI ||
                 instr.op == ASMOp::SLLI || instr.op == ASMOp::SRLI || instr.op == ASMOp::SRAI) {
            std::cout << getRegName(instr.rd.value) << ", " 
                      << getRegName(instr.rs1.value) << ", " 
                      << instr.imm.value;
        }
        else {
            // R-type (default): op rd, rs1, rs2
            std::cout << getRegName(instr.rd.value) << ", " 
                      << getRegName(instr.rs1.value) << ", " 
                      << getRegName(instr.rs2.value);
        }
        
        std::cout << "\n";
    }
};
}