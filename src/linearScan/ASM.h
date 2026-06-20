# pragma once

# include <string>
# include <vector>

namespace JaneZ {
static constexpr int RISCV_XLEN_BYTES = 8;

enum class OperandType{
    REG,
    IMM,
    LABEL,
    EXIT_LABEL,
};

struct Operand{
    OperandType type;
    long long int value;

    Operand() : type(OperandType::IMM), value(0) {}
    Operand(OperandType type, long long value) : type(type), value(value) {}
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
    ADDW,
    SUBW,
    MULW,
    DIVW,
    DIVUW,
    REMW,
    REMUW,
    SLLW,
    SRLW,
    SRAW,
    DIV,
    DIVU,
    REM,
    REMU,
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
    LWU,
    LD,
    SB,
    SH,
    SW,
    SD,
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
    JR,
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

class ASMBlock{
public:
    std::string label;
    std::vector<ASMInstr> instrs;

    ASMBlock() : label("") {}
    ASMBlock(const std::string& label) : label(label) {}
};
}
