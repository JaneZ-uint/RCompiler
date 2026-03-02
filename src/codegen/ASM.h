# pragma once

#include <vector>
namespace JaneZ {
enum class OperandType{
    REG,
    IMM,
    MEM
};

struct Operand{
    OperandType type;
    int value;
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
    LUI
};

struct ASMInstr{
    ASMOp op;
    std::vector<Operand> operands;
};
}