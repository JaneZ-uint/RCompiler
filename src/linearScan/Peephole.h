#pragma once

#include "ASM.h"
#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace JaneZ {

class Peephole {
public:
    bool optimize(std::vector<std::shared_ptr<ASMBlock>> &blocks, bool removeFallthroughJumps = false) {
        bool changed = false;
        if (removeFallthroughJumps) {
            changed |= cleanupRedundantStackAccesses(blocks);
        }
        auto useCounts = countUses(blocks);
        for (size_t i = 0; i < blocks.size(); i++) {
            if (!blocks[i]) continue;
            std::vector<ASMInstr> out;
            out.reserve(blocks[i]->instrs.size());
            auto &instrs = blocks[i]->instrs;
            for (size_t j = 0; j < instrs.size();) {
                ASMInstr folded;
                int consumed = 0;
                if (!removeFallthroughJumps) {
                    consumed = tryFoldCompareBranch(instrs, j, useCounts, folded);
                    if (consumed == 0) {
                        consumed = tryFoldAddressAccess(instrs, j, useCounts, folded, true);
                    }
                    if (consumed == 0) {
                        consumed = tryFoldMoveIntoNext(instrs, j, useCounts, folded, true);
                    }
                } else {
                    consumed = tryFoldAddressAccess(instrs, j, useCounts, folded, false);
                    if (consumed == 0) {
                        consumed = tryFoldMoveIntoNext(instrs, j, useCounts, folded, false);
                    }
                }
                if (consumed > 0) {
                    if (!isSelfMove(folded) && !isNoopAddi(folded)) {
                        out.push_back(folded);
                    }
                    j += consumed;
                    changed = true;
                    continue;
                }

                const auto &instr = instrs[j];
                if (isSelfMove(instr) || isNoopAddi(instr) ||
                    (removeFallthroughJumps && isJumpToNextBlock(instr, blocks, i))) {
                    changed = true;
                    j++;
                    continue;
                }
                out.push_back(instr);
                j++;
            }
            blocks[i]->instrs = std::move(out);
        }
        return changed;
    }

private:
    struct StackSlotValue {
        int base = -1;
        long long offset = 0;
        int size = 0;
        int reg = -1;
    };

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

    bool isTempReg(const Operand &op) const {
        return op.type == OperandType::REG && op.value >= 32;
    }

    bool isAllocatablePhysicalReg(int reg) const {
        if (reg == 5 || reg == 6 || reg == 7 ||
            reg == 28 || reg == 29 || reg == 30 || reg == 31 ||
            (reg >= 10 && reg <= 17)) {
            return true;
        }
        return reg == 9 || (reg >= 18 && reg <= 26);
    }

    bool isAddressTempReg(const Operand &op, bool allowPhysical) const {
        if (op.type != OperandType::REG) return false;
        if (op.value >= 32) return true;
        return allowPhysical && isAllocatablePhysicalReg((int)op.value);
    }

    bool fitsSigned12(long long value) const {
        return value >= -2048 && value <= 2047;
    }

    bool sameReg(const Operand &a, const Operand &b) const {
        return a.type == OperandType::REG &&
               b.type == OperandType::REG &&
               a.value == b.value;
    }

    int regUseCount(const std::unordered_map<int, int> &useCounts, int reg) const {
        auto it = useCounts.find(reg);
        return it == useCounts.end() ? 0 : it->second;
    }

    int tryFoldCompareBranch(const std::vector<ASMInstr> &instrs,
                             size_t index,
                             const std::unordered_map<int, int> &useCounts,
                             ASMInstr &folded) const {
        if (index + 1 >= instrs.size()) return 0;

        const auto &cmp = instrs[index];
        const auto &br = instrs[index + 1];
        if ((cmp.op == ASMOp::SEQZ || cmp.op == ASMOp::SNEZ) &&
            isTempReg(cmp.rd) &&
            br.op == ASMOp::BNEZ &&
            sameReg(cmp.rd, br.rs1) &&
            regUseCount(useCounts, cmp.rd.value) == 1) {
            folded.op = (cmp.op == ASMOp::SEQZ) ? ASMOp::BEQ : ASMOp::BNE;
            folded.rs1 = cmp.rs1;
            folded.rs2 = Operand(OperandType::REG, 0);
            folded.label = br.label;
            return 2;
        }

        if ((cmp.op == ASMOp::SLT || cmp.op == ASMOp::SLTU) &&
            isTempReg(cmp.rd) &&
            br.op == ASMOp::BNEZ &&
            sameReg(cmp.rd, br.rs1) &&
            regUseCount(useCounts, cmp.rd.value) == 1) {
            folded.op = (cmp.op == ASMOp::SLTU) ? ASMOp::BLTU : ASMOp::BLT;
            folded.rs1 = cmp.rs1;
            folded.rs2 = cmp.rs2;
            folded.label = br.label;
            return 2;
        }

        if (isTempReg(cmp.rd) &&
            br.op == ASMOp::BNEZ &&
            sameReg(cmp.rd, br.rs1) &&
            regUseCount(useCounts, cmp.rd.value) == 1 &&
            cmp.imm.type == OperandType::IMM) {
            if (cmp.op == ASMOp::SLTI && cmp.imm.value == 0) {
                folded.op = ASMOp::BLT;
                folded.rs1 = cmp.rs1;
                folded.rs2 = Operand(OperandType::REG, 0);
                folded.label = br.label;
                return 2;
            }
            if (cmp.op == ASMOp::SLTIU && cmp.imm.value == 1) {
                folded.op = ASMOp::BEQ;
                folded.rs1 = cmp.rs1;
                folded.rs2 = Operand(OperandType::REG, 0);
                folded.label = br.label;
                return 2;
            }
        }

        if (index + 2 >= instrs.size()) return 0;
        const auto &boolOp = instrs[index + 1];
        const auto &boolBr = instrs[index + 2];
        if (boolBr.op != ASMOp::BNEZ || !isTempReg(cmp.rd) ||
            !sameReg(cmp.rd, boolBr.rs1) ||
            regUseCount(useCounts, cmp.rd.value) != 2) {
            return 0;
        }

        if ((cmp.op == ASMOp::SLT || cmp.op == ASMOp::SLTU) &&
            boolOp.op == ASMOp::XORI &&
            sameReg(boolOp.rd, cmp.rd) &&
            sameReg(boolOp.rs1, cmp.rd) &&
            boolOp.imm.type == OperandType::IMM &&
            boolOp.imm.value == 1) {
            folded.op = (cmp.op == ASMOp::SLTU) ? ASMOp::BGEU : ASMOp::BGE;
            folded.rs1 = cmp.rs1;
            folded.rs2 = cmp.rs2;
            folded.label = boolBr.label;
            return 3;
        }

        if ((cmp.op == ASMOp::SLTI || cmp.op == ASMOp::SLTIU) &&
            boolOp.op == ASMOp::XORI &&
            sameReg(boolOp.rd, cmp.rd) &&
            sameReg(boolOp.rs1, cmp.rd) &&
            boolOp.imm.type == OperandType::IMM &&
            boolOp.imm.value == 1 &&
            cmp.imm.type == OperandType::IMM) {
            if (cmp.op == ASMOp::SLTI && cmp.imm.value == 0) {
                folded.op = ASMOp::BGE;
                folded.rs1 = cmp.rs1;
                folded.rs2 = Operand(OperandType::REG, 0);
                folded.label = boolBr.label;
                return 3;
            }
            if (cmp.op == ASMOp::SLTIU && cmp.imm.value == 1) {
                folded.op = ASMOp::BNE;
                folded.rs1 = cmp.rs1;
                folded.rs2 = Operand(OperandType::REG, 0);
                folded.label = boolBr.label;
                return 3;
            }
        }

        if (cmp.op == ASMOp::SUB &&
            (boolOp.op == ASMOp::SEQZ || boolOp.op == ASMOp::SNEZ) &&
            sameReg(boolOp.rd, cmp.rd) &&
            sameReg(boolOp.rs1, cmp.rd)) {
            folded.op = (boolOp.op == ASMOp::SEQZ) ? ASMOp::BEQ : ASMOp::BNE;
            folded.rs1 = cmp.rs1;
            folded.rs2 = cmp.rs2;
            folded.label = boolBr.label;
            return 3;
        }

        return 0;
    }

    bool isLoad(const ASMInstr &instr) const {
        switch (instr.op) {
            case ASMOp::LW: case ASMOp::LWU: case ASMOp::LD:
            case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
                return true;
            default:
                return false;
        }
    }

    bool isStore(const ASMInstr &instr) const {
        switch (instr.op) {
            case ASMOp::SW: case ASMOp::SD: case ASMOp::SB: case ASMOp::SH:
                return true;
            default:
                return false;
        }
    }

    bool isMemoryAccess(const ASMInstr &instr) const {
        return isLoad(instr) || isStore(instr);
    }

    bool isTrackedStackLoad(const ASMInstr &instr, int &base, long long &offset, int &size) const {
        if (instr.op != ASMOp::LD ||
            instr.rd.type != OperandType::REG ||
            instr.rd.value == 0 ||
            instr.rs1.type != OperandType::REG ||
            instr.imm.type != OperandType::IMM ||
            instr.rs1.value != 8) {
            return false;
        }
        base = (int)instr.rs1.value;
        offset = instr.imm.value;
        size = RISCV_XLEN_BYTES;
        return true;
    }

    bool isTrackedStackStore(const ASMInstr &instr, int &base, long long &offset, int &size) const {
        if (instr.op != ASMOp::SD ||
            instr.rs2.type != OperandType::REG ||
            instr.rs1.type != OperandType::REG ||
            instr.imm.type != OperandType::IMM ||
            instr.rs1.value != 8) {
            return false;
        }
        base = (int)instr.rs1.value;
        offset = instr.imm.value;
        size = RISCV_XLEN_BYTES;
        return true;
    }

    bool sameSlot(const StackSlotValue &slot, int base, long long offset, int size) const {
        return slot.base == base && slot.offset == offset && slot.size == size;
    }

    bool slotsOverlap(const StackSlotValue &slot, int base, long long offset, int size) const {
        if (slot.base != base) return false;
        long long slotEnd = slot.offset + slot.size;
        long long memEnd = offset + size;
        return slot.offset < memEnd && offset < slotEnd;
    }

    void eraseKnownReg(std::vector<StackSlotValue> &known, int reg) const {
        known.erase(std::remove_if(known.begin(), known.end(),
            [&](const StackSlotValue &slot) { return slot.reg == reg || slot.base == reg; }),
            known.end());
    }

    void eraseOverlappingSlots(std::vector<StackSlotValue> &known,
                               int base,
                               long long offset,
                               int size) const {
        known.erase(std::remove_if(known.begin(), known.end(),
            [&](const StackSlotValue &slot) { return slotsOverlap(slot, base, offset, size); }),
            known.end());
    }

    int findKnownSlot(const std::vector<StackSlotValue> &known,
                      int base,
                      long long offset,
                      int size) const {
        for (size_t i = 0; i < known.size(); i++) {
            if (sameSlot(known[i], base, offset, size)) return (int)i;
        }
        return -1;
    }

    void rememberSlot(std::vector<StackSlotValue> &known,
                      int base,
                      long long offset,
                      int size,
                      int reg) const {
        int idx = findKnownSlot(known, base, offset, size);
        if (idx >= 0) {
            known[idx].reg = reg;
            return;
        }
        known.push_back(StackSlotValue{base, offset, size, reg});
    }

    bool cleanupRedundantStackAccesses(std::vector<std::shared_ptr<ASMBlock>> &blocks) const {
        bool changed = false;
        for (auto &block : blocks) {
            if (!block) continue;
            std::vector<StackSlotValue> known;
            std::vector<ASMInstr> out;
            out.reserve(block->instrs.size());

            for (const auto &instr : block->instrs) {
                int base = -1;
                int size = 0;
                long long offset = 0;

                if (isTrackedStackLoad(instr, base, offset, size)) {
                    int dst = (int)instr.rd.value;
                    int idx = findKnownSlot(known, base, offset, size);
                    int src = idx >= 0 ? known[idx].reg : -1;
                    eraseKnownReg(known, dst);
                    if (idx >= 0) {
                        if (src != dst) {
                            ASMInstr mv;
                            mv.op = ASMOp::MV;
                            mv.rd = instr.rd;
                            mv.rs1 = Operand(OperandType::REG, src);
                            out.push_back(mv);
                        }
                        rememberSlot(known, base, offset, size, dst);
                        changed = true;
                    } else {
                        out.push_back(instr);
                        rememberSlot(known, base, offset, size, dst);
                    }
                    continue;
                }

                if (isTrackedStackStore(instr, base, offset, size)) {
                    int src = (int)instr.rs2.value;
                    int idx = findKnownSlot(known, base, offset, size);
                    if (idx >= 0 && known[idx].reg == src) {
                        changed = true;
                    } else {
                        eraseOverlappingSlots(known, base, offset, size);
                        out.push_back(instr);
                    }
                    rememberSlot(known, base, offset, size, src);
                    continue;
                }

                if (instr.op == ASMOp::CALL || !instr.funcName.empty()) {
                    known.clear();
                    out.push_back(instr);
                    continue;
                }

                if (isStore(instr)) {
                    known.clear();
                    out.push_back(instr);
                    continue;
                }

                bool clearAll = false;
                for (const auto &slot : known) {
                    if (instrDefsReg(instr, slot.base)) {
                        clearAll = true;
                        break;
                    }
                }
                if (clearAll || isTerminator(instr)) {
                    known.clear();
                } else {
                    known.erase(std::remove_if(known.begin(), known.end(),
                        [&](const StackSlotValue &slot) {
                            return instrDefsReg(instr, slot.reg);
                        }),
                        known.end());
                }
                out.push_back(instr);
            }

            if (out.size() != block->instrs.size()) changed = true;
            block->instrs = std::move(out);
        }
        return changed;
    }

    int tryFoldAddressAccess(const std::vector<ASMInstr> &instrs,
                             size_t index,
                             const std::unordered_map<int, int> &useCounts,
                             ASMInstr &folded,
                             bool requireSingleUse) const {
        if (index + 1 >= instrs.size()) return 0;

        const auto &addr = instrs[index];
        const auto &mem = instrs[index + 1];
        if (!isMemoryAccess(mem) || !isAddressTempReg(addr.rd, !requireSingleUse) ||
            !sameReg(addr.rd, mem.rs1) ||
            mem.imm.type != OperandType::IMM ||
            !addr.funcName.empty()) {
            return 0;
        }
        if (requireSingleUse) {
            if (regUseCount(useCounts, addr.rd.value) != 1) return 0;
        } else {
            if (isStore(mem) && sameReg(mem.rs2, addr.rd)) return 0;
            if (!(isLoad(mem) && sameReg(mem.rd, addr.rd)) &&
                !isRegDeadAfter(instrs, index + 2, addr.rd.value)) {
                return 0;
            }
        }

        Operand base;
        long long offset = mem.imm.value;
        if (addr.op == ASMOp::ADDI &&
            addr.rs1.type == OperandType::REG &&
            addr.imm.type == OperandType::IMM) {
            offset += addr.imm.value;
            base = addr.rs1;
        } else if (addr.op == ASMOp::MV &&
                   addr.rs1.type == OperandType::REG) {
            base = addr.rs1;
        } else {
            return 0;
        }

        if (!fitsSigned12(offset)) return 0;

        folded = mem;
        folded.rs1 = base;
        folded.imm = Operand(OperandType::IMM, offset);
        return 2;
    }

    bool instrUsesReg(const ASMInstr &instr, int reg) const {
        std::unordered_map<int, int> uses;
        countInstrUses(instr, uses);
        return uses.find(reg) != uses.end();
    }

    bool instrDefsReg(const ASMInstr &instr, int reg) const {
        switch (instr.op) {
            case ASMOp::ADD: case ASMOp::SUB: case ASMOp::MUL: case ASMOp::DIV:
            case ASMOp::DIVU: case ASMOp::REM: case ASMOp::REMU:
            case ASMOp::ADDW: case ASMOp::SUBW: case ASMOp::MULW: case ASMOp::DIVW:
            case ASMOp::DIVUW: case ASMOp::REMW: case ASMOp::REMUW:
            case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA:
            case ASMOp::SLLW: case ASMOp::SRLW: case ASMOp::SRAW:
            case ASMOp::SLT: case ASMOp::SLTU:
            case ASMOp::ADDI: case ASMOp::ANDI: case ASMOp::ORI: case ASMOp::XORI:
            case ASMOp::SLLI: case ASMOp::SRLI: case ASMOp::SRAI:
            case ASMOp::SLTI: case ASMOp::SLTIU:
            case ASMOp::LW: case ASMOp::LWU: case ASMOp::LD:
            case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
            case ASMOp::LI: case ASMOp::LUI:
            case ASMOp::MV: case ASMOp::SEQZ: case ASMOp::SNEZ:
                return instr.rd.type == OperandType::REG && instr.rd.value == reg;
            case ASMOp::CALL:
                return reg == 1 ||
                       reg == 5 || reg == 6 || reg == 7 ||
                       reg == 28 || reg == 29 || reg == 30 || reg == 31 ||
                       (reg >= 10 && reg <= 17);
            default:
                return false;
        }
    }

    bool isTerminator(const ASMInstr &instr) const {
        switch (instr.op) {
            case ASMOp::J: case ASMOp::JR: case ASMOp::JAL:
            case ASMOp::BEQ: case ASMOp::BNE: case ASMOp::BLT: case ASMOp::BGE:
            case ASMOp::BLTU: case ASMOp::BGEU: case ASMOp::BNEZ:
                return true;
            default:
                return false;
        }
    }

    bool rewriteRegOperand(Operand &op, int fromReg, const Operand &toReg) const {
        if (op.type == OperandType::REG && op.value == fromReg) {
            op = toReg;
            return true;
        }
        return false;
    }

    bool rewriteExplicitUses(ASMInstr &instr, int fromReg, const Operand &toReg) const {
        bool changed = false;
        switch (instr.op) {
            case ASMOp::ADD: case ASMOp::SUB: case ASMOp::MUL: case ASMOp::DIV:
            case ASMOp::DIVU: case ASMOp::REM: case ASMOp::REMU:
            case ASMOp::ADDW: case ASMOp::SUBW: case ASMOp::MULW: case ASMOp::DIVW:
            case ASMOp::DIVUW: case ASMOp::REMW: case ASMOp::REMUW:
            case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA:
            case ASMOp::SLLW: case ASMOp::SRLW: case ASMOp::SRAW:
            case ASMOp::SLT: case ASMOp::SLTU:
                changed |= rewriteRegOperand(instr.rs1, fromReg, toReg);
                changed |= rewriteRegOperand(instr.rs2, fromReg, toReg);
                break;
            case ASMOp::ADDI: case ASMOp::ANDI: case ASMOp::ORI: case ASMOp::XORI:
            case ASMOp::SLLI: case ASMOp::SRLI: case ASMOp::SRAI:
            case ASMOp::SLTI: case ASMOp::SLTIU:
            case ASMOp::LW: case ASMOp::LWU: case ASMOp::LD:
            case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
            case ASMOp::MV: case ASMOp::SEQZ: case ASMOp::SNEZ:
            case ASMOp::BNEZ: case ASMOp::JR:
                changed |= rewriteRegOperand(instr.rs1, fromReg, toReg);
                break;
            case ASMOp::SW: case ASMOp::SD: case ASMOp::SB: case ASMOp::SH:
            case ASMOp::BEQ: case ASMOp::BNE: case ASMOp::BLT: case ASMOp::BGE:
            case ASMOp::BLTU: case ASMOp::BGEU:
                changed |= rewriteRegOperand(instr.rs1, fromReg, toReg);
                changed |= rewriteRegOperand(instr.rs2, fromReg, toReg);
                break;
            default:
                break;
        }
        return changed;
    }

    int tryFoldMoveIntoNext(const std::vector<ASMInstr> &instrs,
                            size_t index,
                            const std::unordered_map<int, int> &useCounts,
                            ASMInstr &folded,
                            bool requireSingleUse) const {
        if (index + 1 >= instrs.size()) return 0;

        const auto &copy = instrs[index];
        const auto &next = instrs[index + 1];
        if (copy.op != ASMOp::MV ||
            copy.rd.type != OperandType::REG ||
            copy.rs1.type != OperandType::REG ||
            sameReg(copy.rd, copy.rs1) ||
            !copy.funcName.empty() ||
            !next.funcName.empty() ||
            next.op == ASMOp::CALL ||
            !isAddressTempReg(copy.rd, !requireSingleUse) ||
            !instrUsesReg(next, copy.rd.value)) {
            return 0;
        }

        if (requireSingleUse) {
            if (regUseCount(useCounts, copy.rd.value) != 1) return 0;
        } else if (!instrDefsReg(next, copy.rd.value) &&
                   !isRegDeadAfter(instrs, index + 2, copy.rd.value)) {
            return 0;
        }

        folded = next;
        if (!rewriteExplicitUses(folded, copy.rd.value, copy.rs1)) return 0;
        return 2;
    }

    bool isRegDeadAfter(const std::vector<ASMInstr> &instrs, size_t start, int reg) const {
        for (size_t i = start; i < instrs.size(); i++) {
            const auto &instr = instrs[i];
            if (instrUsesReg(instr, reg)) return false;
            if (instrDefsReg(instr, reg)) return true;
            if (isTerminator(instr)) return false;
        }
        return false;
    }

    void addUse(const Operand &op, std::unordered_map<int, int> &useCounts) const {
        if (op.type == OperandType::REG) {
            useCounts[op.value]++;
        }
    }

    void countInstrUses(const ASMInstr &instr, std::unordered_map<int, int> &useCounts) const {
        switch (instr.op) {
            case ASMOp::ADD: case ASMOp::SUB: case ASMOp::MUL: case ASMOp::DIV:
            case ASMOp::DIVU: case ASMOp::REM: case ASMOp::REMU:
            case ASMOp::ADDW: case ASMOp::SUBW: case ASMOp::MULW: case ASMOp::DIVW:
            case ASMOp::DIVUW: case ASMOp::REMW: case ASMOp::REMUW:
            case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA:
            case ASMOp::SLLW: case ASMOp::SRLW: case ASMOp::SRAW:
            case ASMOp::SLT: case ASMOp::SLTU:
                addUse(instr.rs1, useCounts);
                addUse(instr.rs2, useCounts);
                break;
            case ASMOp::ADDI: case ASMOp::ANDI: case ASMOp::ORI: case ASMOp::XORI:
            case ASMOp::SLLI: case ASMOp::SRLI: case ASMOp::SRAI:
            case ASMOp::SLTI: case ASMOp::SLTIU:
            case ASMOp::LW: case ASMOp::LWU: case ASMOp::LD:
            case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
            case ASMOp::MV: case ASMOp::SEQZ: case ASMOp::SNEZ:
            case ASMOp::BNEZ: case ASMOp::JR:
                addUse(instr.rs1, useCounts);
                break;
            case ASMOp::SW: case ASMOp::SD: case ASMOp::SB: case ASMOp::SH:
            case ASMOp::BEQ: case ASMOp::BNE: case ASMOp::BLT: case ASMOp::BGE:
            case ASMOp::BLTU: case ASMOp::BGEU:
                addUse(instr.rs1, useCounts);
                addUse(instr.rs2, useCounts);
                break;
            case ASMOp::CALL:
                for (int r = 10; r <= 17; r++) {
                    useCounts[r]++;
                }
                break;
            default:
                break;
        }
    }

    std::unordered_map<int, int> countUses(const std::vector<std::shared_ptr<ASMBlock>> &blocks) const {
        std::unordered_map<int, int> useCounts;
        for (const auto &block : blocks) {
            if (!block) continue;
            for (const auto &instr : block->instrs) {
                countInstrUses(instr, useCounts);
            }
        }
        return useCounts;
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
