#pragma once

#include "ASM.h"
#include <memory>
#include <string>
#include <vector>

namespace JaneZ {

class Peephole {
public:
    bool optimize(std::vector<std::shared_ptr<ASMBlock>> &blocks, bool removeFallthroughJumps = false) {
        bool changed = false;
        for (size_t i = 0; i < blocks.size(); i++) {
            if (!blocks[i]) continue;
            std::vector<ASMInstr> out;
            out.reserve(blocks[i]->instrs.size());
            for (const auto &instr : blocks[i]->instrs) {
                if (isSelfMove(instr) || isNoopAddi(instr) ||
                    (removeFallthroughJumps && isJumpToNextBlock(instr, blocks, i))) {
                    changed = true;
                    continue;
                }
                out.push_back(instr);
            }
            blocks[i]->instrs = std::move(out);
        }
        return changed;
    }

private:
    bool isSelfMove(const ASMInstr &instr) const {
        return instr.op == ASMOp::MV &&
               instr.rd.type == OperandType::REG &&
               instr.rs1.type == OperandType::REG &&
               instr.rd.value == instr.rs1.value;
    }

    bool isNoopAddi(const ASMInstr &instr) const {
        return instr.op == ASMOp::ADDI &&
               instr.funcName.empty() &&
               instr.rd.type == OperandType::REG &&
               instr.rs1.type == OperandType::REG &&
               instr.rd.value == instr.rs1.value &&
               instr.imm.type == OperandType::IMM &&
               instr.imm.value == 0;
    }

    std::string formatLabel(const Operand &label) const {
        if (label.type == OperandType::EXIT_LABEL) {
            return ".Lexit" + std::to_string(label.value);
        }
        return ".L" + std::to_string(label.value);
    }

    bool isJumpToNextBlock(const ASMInstr &instr,
                           const std::vector<std::shared_ptr<ASMBlock>> &blocks,
                           size_t blockIndex) const {
        if (instr.op != ASMOp::J) return false;
        if (blockIndex + 1 >= blocks.size() || !blocks[blockIndex + 1]) return false;
        if (blocks[blockIndex + 1]->label.empty()) return false;
        return formatLabel(instr.label) == blocks[blockIndex + 1]->label;
    }
};

} // namespace JaneZ
