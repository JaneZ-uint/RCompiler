# pragma once

#include <string>
namespace JaneZ {
enum class OperandType{
    REG,
    IMM,
    LABEL,
};

struct Operand{
    OperandType type;
    int value;

    Operand() : type(OperandType::IMM), value(0) {}
    Operand(OperandType type, int value) : type(type), value(value) {}
};

enum class ASMOp{
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    SLL,
    SRL,
    SRA,
    SLT,
    SLTU,
    MUL,
    DIV,
    REM,
    ADDI,
    ANDI,
    ORI,
    XORI,
    SLLI,
    SRLI,
    SRAI,
    SLTI,
    SLTIU,
    LB,
    LBU,
    LH,
    LHU,
    LW,
    SB,
    SH,
    SW,
    BEQ,
    BGE,
    BGEU,
    BLT,
    BLTU,
    BNE,
    JAL,
    JALR,
    AUIPC,
    LUI,
    
    LI,
    J,
    BNEZ,
    MV,
    CALL,
    SLE,
    SGE,
    SEQZ,
    SNEZ,
};

struct ASMInstr{
    ASMOp op;
    Operand rd;
    Operand rs1;
    Operand rs2;
    Operand imm;
    Operand label;
    std::string funcName;

    ASMInstr() : op(ASMOp::ADD) {}
};
}