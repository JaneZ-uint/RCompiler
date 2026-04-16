# pragma once

# include "ASM.h"
# include <algorithm>
# include <memory>
# include <unordered_map>
# include <utility>
# include <vector>

namespace JaneZ {
class LinearScan {
public:
    struct Interval {
        int vreg = -1;
        int start = 0;
        int end = 0;
    };

    struct Assign {
        bool spilled = false;
        int preg = -1;
        int slot = -1;
    };

    void run(std::vector<std::shared_ptr<ASMBlock>> &blocks) {
        int n = static_cast<int>(blocks.size());
        int i = 0;
        while (i < n) {
            if (!isFunctionEntry(blocks[i])) {
                ++i;
                continue;
            }
            int j = i + 1;
            while (j < n && !isFunctionEntry(blocks[j])) {
                ++j;
            }
            processFunction(blocks, i, j);
            i = j;
        }
    }

private:
    const std::vector<int> allocRegs = {5, 6, 7, 31};   // t0,t1,t2,t6
    const std::vector<int> scratchRegs = {28, 29, 30};  // t3,t4,t5

    static bool isFunctionEntry(const std::shared_ptr<ASMBlock> &b) {
        return b && !b->label.empty() && b->label[0] != '.';
    }

    static int align16(int v) {
        return (v % 16 == 0) ? v : ((v / 16) + 1) * 16;
    }

    static bool isVReg(const Operand &op) {
        return op.type == OperandType::REG && op.value >= 32;
    }

    static bool inRange(int idx, const Interval &itv) {
        return itv.start <= idx && idx <= itv.end;
    }

    static void addInstrDefUse(const ASMInstr &ins, std::vector<int> &defs, std::vector<int> &uses) {
        auto addDef = [&](const Operand &op) {
            if (isVReg(op)) defs.push_back(static_cast<int>(op.value));
        };
        auto addUse = [&](const Operand &op) {
            if (isVReg(op)) uses.push_back(static_cast<int>(op.value));
        };

        switch (ins.op) {
            case ASMOp::ADD: case ASMOp::SUB: case ASMOp::MUL: case ASMOp::DIV: case ASMOp::DIVU:
            case ASMOp::REM: case ASMOp::REMU: case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA: case ASMOp::SLT: case ASMOp::SLTU:
            case ASMOp::SLE: case ASMOp::SGE:
                addDef(ins.rd); addUse(ins.rs1); addUse(ins.rs2); break;
            case ASMOp::ADDI: case ASMOp::SLTI: case ASMOp::SLTIU: case ASMOp::ANDI: case ASMOp::ORI:
            case ASMOp::XORI: case ASMOp::SLLI: case ASMOp::SRLI: case ASMOp::SRAI:
                addDef(ins.rd); addUse(ins.rs1); break;
            case ASMOp::LB: case ASMOp::LH: case ASMOp::LW: case ASMOp::LBU: case ASMOp::LHU:
                addDef(ins.rd); addUse(ins.rs1); break;
            case ASMOp::SB: case ASMOp::SH: case ASMOp::SW:
                addUse(ins.rs1); addUse(ins.rs2); break;
            case ASMOp::MV: case ASMOp::SEQZ: case ASMOp::SNEZ:
                addDef(ins.rd); addUse(ins.rs1); break;
            case ASMOp::LI: case ASMOp::LUI:
                addDef(ins.rd); break;
            case ASMOp::BEQ: case ASMOp::BNE: case ASMOp::BLT: case ASMOp::BGE: case ASMOp::BLTU: case ASMOp::BGEU:
                addUse(ins.rs1); addUse(ins.rs2); break;
            case ASMOp::BNEZ: case ASMOp::JR:
                addUse(ins.rs1); break;
            default:
                break;
        }
    }

    static void collectIntervals(
        const std::vector<std::shared_ptr<ASMBlock>> &blocks,
        int l, int r,
        std::unordered_map<int, Interval> &intervals,
        std::vector<int> &callSites
    ) {
        int idx = 0;
        for (int bi = l; bi < r; ++bi) {
            for (const auto &ins : blocks[bi]->instrs) {
                if (ins.op == ASMOp::CALL) {
                    callSites.push_back(idx);
                }
                std::vector<int> defs, uses;
                addInstrDefUse(ins, defs, uses);
                for (int v : uses) {
                    auto &it = intervals[v];
                    if (it.vreg == -1) {
                        it.vreg = v;
                        it.start = idx;
                        it.end = idx;
                    } else {
                        it.start = std::min(it.start, idx);
                        it.end = std::max(it.end, idx);
                    }
                }
                for (int v : defs) {
                    auto &it = intervals[v];
                    if (it.vreg == -1) {
                        it.vreg = v;
                        it.start = idx;
                        it.end = idx;
                    } else {
                        it.start = std::min(it.start, idx);
                        it.end = std::max(it.end, idx);
                    }
                }
                ++idx;
            }
        }
    }

    void linearScanAllocate(
        const std::unordered_map<int, Interval> &intervalMap,
        std::unordered_map<int, Assign> &assignMap
    ) {
        std::vector<Interval> intervals;
        intervals.reserve(intervalMap.size());
        for (const auto &kv : intervalMap) intervals.push_back(kv.second);
        std::sort(intervals.begin(), intervals.end(), [](const Interval &a, const Interval &b) {
            if (a.start != b.start) return a.start < b.start;
            return a.vreg < b.vreg;
        });

        std::vector<Interval> active;
        auto sortActive = [&]() {
            std::sort(active.begin(), active.end(), [](const Interval &a, const Interval &b) {
                return a.end < b.end;
            });
        };

        for (const auto &cur : intervals) {
            active.erase(std::remove_if(active.begin(), active.end(), [&](const Interval &x) {
                return x.end < cur.start;
            }), active.end());
            sortActive();

            if (static_cast<int>(active.size()) == static_cast<int>(allocRegs.size())) {
                int spillIdx = static_cast<int>(active.size()) - 1;
                if (active[spillIdx].end > cur.end) {
                    int victim = active[spillIdx].vreg;
                    assignMap[cur.vreg] = {false, assignMap[victim].preg, -1};
                    assignMap[victim] = {true, -1, -1};
                    active[spillIdx] = cur;
                    sortActive();
                } else {
                    assignMap[cur.vreg] = {true, -1, -1};
                }
            } else {
                std::vector<bool> used(32, false);
                for (const auto &x : active) {
                    auto it = assignMap.find(x.vreg);
                    if (it != assignMap.end() && !it->second.spilled && it->second.preg >= 0) {
                        used[it->second.preg] = true;
                    }
                }
                int chosen = -1;
                for (int preg : allocRegs) {
                    if (!used[preg]) {
                        chosen = preg;
                        break;
                    }
                }
                if (chosen < 0) {
                    assignMap[cur.vreg] = {true, -1, -1};
                } else {
                    assignMap[cur.vreg] = {false, chosen, -1};
                    active.push_back(cur);
                    sortActive();
                }
            }
        }
    }

    static int parseStackSize(const std::shared_ptr<ASMBlock> &entry) {
        for (const auto &ins : entry->instrs) {
            if (ins.op == ASMOp::ADDI &&
                ins.rd.type == OperandType::REG && ins.rd.value == 2 &&
                ins.rs1.type == OperandType::REG && ins.rs1.value == 2 &&
                ins.imm.type == OperandType::IMM && ins.imm.value < 0) {
                return static_cast<int>(-ins.imm.value);
            }
        }
        return 0;
    }

    static void patchFrameLayout(std::vector<std::shared_ptr<ASMBlock>> &blocks, int l, int r, int oldSize, int newSize) {
        if (oldSize == newSize || oldSize <= 0) return;
        int oldRa = oldSize - 4, oldS0 = oldSize - 8;
        int newRa = newSize - 4, newS0 = newSize - 8;

        for (int bi = l; bi < r; ++bi) {
            for (auto &ins : blocks[bi]->instrs) {
                if (ins.op == ASMOp::ADDI &&
                    ins.rd.type == OperandType::REG && ins.rd.value == 2 &&
                    ins.rs1.type == OperandType::REG && ins.rs1.value == 2 &&
                    ins.imm.type == OperandType::IMM) {
                    if (ins.imm.value == -oldSize) ins.imm.value = -newSize;
                    if (ins.imm.value == oldSize) ins.imm.value = newSize;
                }
                if (ins.op == ASMOp::ADDI &&
                    ins.rd.type == OperandType::REG && ins.rd.value == 8 &&
                    ins.rs1.type == OperandType::REG && ins.rs1.value == 2 &&
                    ins.imm.type == OperandType::IMM && ins.imm.value == oldSize) {
                    ins.imm.value = newSize;
                }
                if ((ins.op == ASMOp::SW || ins.op == ASMOp::LW) &&
                    ins.rs1.type == OperandType::REG && ins.rs1.value == 2 &&
                    ins.imm.type == OperandType::IMM) {
                    bool isRa = (ins.op == ASMOp::SW && ins.rs2.type == OperandType::REG && ins.rs2.value == 1) ||
                                (ins.op == ASMOp::LW && ins.rd.type == OperandType::REG && ins.rd.value == 1);
                    bool isS0 = (ins.op == ASMOp::SW && ins.rs2.type == OperandType::REG && ins.rs2.value == 8) ||
                                (ins.op == ASMOp::LW && ins.rd.type == OperandType::REG && ins.rd.value == 8);
                    if (isRa && ins.imm.value == oldRa) ins.imm.value = newRa;
                    if (isS0 && ins.imm.value == oldS0) ins.imm.value = newS0;
                }
            }
        }
    }

    static std::vector<ASMInstr> makeLoadFromSpill(int scratch, int offset) {
        ASMInstr lw;
        lw.op = ASMOp::LW;
        lw.rd = Operand(OperandType::REG, scratch);
        lw.rs1 = Operand(OperandType::REG, 2);
        lw.imm = Operand(OperandType::IMM, offset);
        return {lw};
    }

    static std::vector<ASMInstr> makeStoreToSpill(int scratch, int offset) {
        ASMInstr sw;
        sw.op = ASMOp::SW;
        sw.rs2 = Operand(OperandType::REG, scratch);
        sw.rs1 = Operand(OperandType::REG, 2);
        sw.imm = Operand(OperandType::IMM, offset);
        return {sw};
    }

    static void rewriteUseOperand(
        Operand &op,
        std::vector<ASMInstr> &pre,
        const std::unordered_map<int, Assign> &assignMap,
        int scratch,
        int baseStack
    ) {
        if (!isVReg(op)) return;
        int vreg = static_cast<int>(op.value);
        auto it = assignMap.find(vreg);
        if (it == assignMap.end()) return;
        if (!it->second.spilled) {
            op.value = it->second.preg;
        } else {
            int off = baseStack + it->second.slot * 4;
            auto loads = makeLoadFromSpill(scratch, off);
            pre.insert(pre.end(), loads.begin(), loads.end());
            op.value = scratch;
        }
    }

    static void rewriteDefOperand(
        Operand &op,
        std::vector<ASMInstr> &post,
        const std::unordered_map<int, Assign> &assignMap,
        int scratch,
        int baseStack
    ) {
        if (!isVReg(op)) return;
        int vreg = static_cast<int>(op.value);
        auto it = assignMap.find(vreg);
        if (it == assignMap.end()) return;
        if (!it->second.spilled) {
            op.value = it->second.preg;
        } else {
            op.value = scratch;
            int off = baseStack + it->second.slot * 4;
            auto stores = makeStoreToSpill(scratch, off);
            post.insert(post.end(), stores.begin(), stores.end());
        }
    }

    void rewriteFunction(
        std::vector<std::shared_ptr<ASMBlock>> &blocks,
        int l, int r,
        const std::unordered_map<int, Interval> &intervalMap,
        std::unordered_map<int, Assign> &assignMap,
        int baseStack
    ) {
        int idx = 0;
        for (int bi = l; bi < r; ++bi) {
            std::vector<ASMInstr> rewritten;
            rewritten.reserve(blocks[bi]->instrs.size() * 2);

            for (auto ins : blocks[bi]->instrs) {
                std::vector<ASMInstr> pre, post;

                auto saveAcrossCall = [&]() {
                    if (ins.op != ASMOp::CALL) return;
                    for (const auto &kv : intervalMap) {
                        int vreg = kv.first;
                        const auto &itv = kv.second;
                        auto ait = assignMap.find(vreg);
                        if (ait == assignMap.end() || ait->second.spilled) continue;
                        if (!inRange(idx, itv) || itv.end <= idx) continue;
                        if (ait->second.slot < 0) continue;
                        int off = baseStack + ait->second.slot * 4;
                        auto s = makeStoreToSpill(ait->second.preg, off);
                        auto lds = makeLoadFromSpill(ait->second.preg, off);
                        pre.insert(pre.end(), s.begin(), s.end());
                        post.insert(post.end(), lds.begin(), lds.end());
                    }
                };

                switch (ins.op) {
                    case ASMOp::ADD: case ASMOp::SUB: case ASMOp::MUL: case ASMOp::DIV: case ASMOp::DIVU:
                    case ASMOp::REM: case ASMOp::REMU: case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
                    case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA: case ASMOp::SLT: case ASMOp::SLTU:
                    case ASMOp::SLE: case ASMOp::SGE:
                        rewriteUseOperand(ins.rs1, pre, assignMap, scratchRegs[0], baseStack);
                        rewriteUseOperand(ins.rs2, pre, assignMap, scratchRegs[1], baseStack);
                        rewriteDefOperand(ins.rd, post, assignMap, scratchRegs[2], baseStack);
                        break;
                    case ASMOp::ADDI: case ASMOp::SLTI: case ASMOp::SLTIU: case ASMOp::ANDI: case ASMOp::ORI:
                    case ASMOp::XORI: case ASMOp::SLLI: case ASMOp::SRLI: case ASMOp::SRAI:
                    case ASMOp::LB: case ASMOp::LH: case ASMOp::LW: case ASMOp::LBU: case ASMOp::LHU:
                        rewriteUseOperand(ins.rs1, pre, assignMap, scratchRegs[0], baseStack);
                        rewriteDefOperand(ins.rd, post, assignMap, scratchRegs[2], baseStack);
                        break;
                    case ASMOp::SB: case ASMOp::SH: case ASMOp::SW:
                        rewriteUseOperand(ins.rs1, pre, assignMap, scratchRegs[0], baseStack);
                        rewriteUseOperand(ins.rs2, pre, assignMap, scratchRegs[1], baseStack);
                        break;
                    case ASMOp::MV: case ASMOp::SEQZ: case ASMOp::SNEZ:
                        rewriteUseOperand(ins.rs1, pre, assignMap, scratchRegs[0], baseStack);
                        rewriteDefOperand(ins.rd, post, assignMap, scratchRegs[2], baseStack);
                        break;
                    case ASMOp::LI: case ASMOp::LUI:
                        rewriteDefOperand(ins.rd, post, assignMap, scratchRegs[2], baseStack);
                        break;
                    case ASMOp::BEQ: case ASMOp::BNE: case ASMOp::BLT: case ASMOp::BGE: case ASMOp::BLTU: case ASMOp::BGEU:
                        rewriteUseOperand(ins.rs1, pre, assignMap, scratchRegs[0], baseStack);
                        rewriteUseOperand(ins.rs2, pre, assignMap, scratchRegs[1], baseStack);
                        break;
                    case ASMOp::BNEZ: case ASMOp::JR:
                        rewriteUseOperand(ins.rs1, pre, assignMap, scratchRegs[0], baseStack);
                        break;
                    default:
                        break;
                }

                saveAcrossCall();
                rewritten.insert(rewritten.end(), pre.begin(), pre.end());
                rewritten.push_back(ins);
                rewritten.insert(rewritten.end(), post.begin(), post.end());
                ++idx;
            }
            blocks[bi]->instrs.swap(rewritten);
        }
    }

    void processFunction(std::vector<std::shared_ptr<ASMBlock>> &blocks, int l, int r) {
        if (l >= r) return;
        int oldStack = parseStackSize(blocks[l]);

        std::unordered_map<int, Interval> intervalMap;
        std::vector<int> callSites;
        collectIntervals(blocks, l, r, intervalMap, callSites);
        if (intervalMap.empty()) return;

        std::unordered_map<int, Assign> assignMap;
        linearScanAllocate(intervalMap, assignMap);

        int slots = 0;
        auto ensureSlot = [&](int vreg) {
            auto &a = assignMap[vreg];
            if (a.slot < 0) a.slot = slots++;
        };

        for (auto &kv : assignMap) {
            if (kv.second.spilled) ensureSlot(kv.first);
        }

        for (int callIdx : callSites) {
            for (const auto &kv : intervalMap) {
                int vreg = kv.first;
                const auto &itv = kv.second;
                if (!inRange(callIdx, itv) || itv.end <= callIdx) continue;
                auto ait = assignMap.find(vreg);
                if (ait == assignMap.end() || ait->second.spilled) continue;
                ensureSlot(vreg);
            }
        }

        int newStack = align16(oldStack + slots * 4);
        patchFrameLayout(blocks, l, r, oldStack, newStack);
        rewriteFunction(blocks, l, r, intervalMap, assignMap, oldStack);
    }
};
}
