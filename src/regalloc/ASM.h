# pragma once

# include <string>
# include <vector>

namespace JaneZ {
enum class OperandType{
    REG,
    IMM,
    LABEL,
};

struct Operand{
    OperandType type;
    long long int value;

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