# pragma once

#include "ASM.h"
#include <algorithm>
#include <cassert>
#include <climits>
#include <cstring>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace JaneZ {

// ============================================================
//  Linear Scan Register Allocator
// ============================================================

// Physical register classification
static const int CALLER_SAVED[] = {5,6,7, 28,29, 10,11,12,13,14,15,16,17}; // t0-t2, t3-t4, a0-a7
static const int CALLEE_SAVED[] = {9, 18,19,20,21,22,23,24,25,26}; // s1, s2-s10
// scratch regs for spill load/store (never allocated)
static const int SCRATCH1 = 30; // t5
static const int SCRATCH2 = 31; // t6

static bool isCallerSaved(int r) {
    for (int x : CALLER_SAVED) if (x == r) return true;
    return false;
}
static bool isCalleeSaved(int r) {
    for (int x : CALLEE_SAVED) if (x == r) return true;
    return false;
}

// All allocatable registers (callee-saved first for better cross-call behavior)
static std::vector<int> getAllocRegs() {
    std::vector<int> regs;
    for (int r : CALLEE_SAVED) regs.push_back(r);
    for (int r : CALLER_SAVED) regs.push_back(r);
    return regs;
}

// ---- CFG Block ----
struct CFGBlock {
    int id;
    ASMBlock* asmBlock;
    int startIdx = 0; // first instr index
    int endIdx = 0;   // one-past-last instr index
    std::vector<int> succs;
    std::vector<int> preds;
    std::set<int> def;
    std::set<int> use;
    std::set<int> liveIn;
    std::set<int> liveOut;
};

// ---- Live Interval ----
struct LiveInterval {
    int vreg;
    int start;
    int end;
    int physReg = -1;   // allocated phys reg, -1 = spilled
    int spillSlot = -1; // stack offset for spill, -1 = not spilled
};

// ---- Function Boundary ----
struct FuncInfo {
    std::string name;
    int firstBlock; // index in cfgBlocks
    int lastBlock;  // inclusive
    int allocaSize; // from InstrSelect
    int numVRegs;
};

class LinearScan {
public:
    // Input: all ASM blocks from InstrSelect
    // Output: modified in-place with physical registers + spill code + prologue/epilogue

    void process(std::vector<std::shared_ptr<ASMBlock>>& blocks) {
        // Identify function boundaries: a function starts at a block whose label
        // does NOT start with '.' (global symbol).
        std::vector<std::pair<int,int>> funcRanges; // [start, end) block indices
        for (int i = 0; i < (int)blocks.size(); i++) {
            if (!blocks[i]->label.empty() && blocks[i]->label[0] != '.') {
                if (!funcRanges.empty()) funcRanges.back().second = i;
                funcRanges.push_back({i, (int)blocks.size()});
            }
        }
        if (!funcRanges.empty()) funcRanges.back().second = (int)blocks.size();

        for (auto& [fStart, fEnd] : funcRanges) {
            processFunction(blocks, fStart, fEnd);
        }
    }

private:
    // ============================================================
    //  Per-function processing
    // ============================================================
    void processFunction(std::vector<std::shared_ptr<ASMBlock>>& blocks, int fStart, int fEnd) {
        // 1. Build CFG
        std::vector<CFGBlock> cfg;
        std::unordered_map<std::string, int> labelToIdx;
        for (int i = fStart; i < fEnd; i++) {
            CFGBlock b;
            b.id = i - fStart;
            b.asmBlock = blocks[i].get();
            cfg.push_back(b);
            labelToIdx[blocks[i]->label] = b.id;
        }

        // Number instructions globally within this function
        int instrIdx = 0;
        for (auto& b : cfg) {
            b.startIdx = instrIdx;
            instrIdx += (int)b.asmBlock->instrs.size();
            b.endIdx = instrIdx;
        }
        int totalInstrs = instrIdx;

        // Build edges from terminators
        for (int bi = 0; bi < (int)cfg.size(); bi++) {
            auto& instrs = cfg[bi].asmBlock->instrs;
            if (instrs.empty()) continue;
            buildEdges(cfg, labelToIdx, bi, instrs);
        }

        // Fill preds from succs
        for (int i = 0; i < (int)cfg.size(); i++) {
            for (int s : cfg[i].succs) {
                cfg[s].preds.push_back(i);
            }
        }

        // 2. Compute DEF/USE per block
        for (auto& b : cfg) {
            computeDefUse(b);
        }

        // 3. Liveness analysis (iterative backward dataflow)
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = (int)cfg.size() - 1; i >= 0; i--) {
                auto& b = cfg[i];
                std::set<int> newLiveOut;
                for (int s : b.succs) {
                    for (int r : cfg[s].liveIn) newLiveOut.insert(r);
                }
                // liveIn = use ∪ (liveOut - def)
                std::set<int> newLiveIn = b.use;
                for (int r : newLiveOut) {
                    if (b.def.find(r) == b.def.end()) newLiveIn.insert(r);
                }
                if (newLiveIn != b.liveIn || newLiveOut != b.liveOut) {
                    b.liveIn = newLiveIn;
                    b.liveOut = newLiveOut;
                    changed = true;
                }
            }
        }



        // 4. Compute live intervals
        std::unordered_map<int, LiveInterval> intervals; // vreg → interval
        for (auto& b : cfg) {
            // All regs in liveIn are live from block start
            for (int r : b.liveIn) {
                extendInterval(intervals, r, b.startIdx, b.startIdx);
            }
            // All regs in liveOut are live until block end
            for (int r : b.liveOut) {
                extendInterval(intervals, r, b.endIdx - 1, b.endIdx - 1);
            }
            // If a reg is in both liveIn and liveOut, it's live for the whole block
            for (int r : b.liveIn) {
                if (b.liveOut.count(r)) {
                    extendInterval(intervals, r, b.startIdx, b.endIdx - 1);
                }
            }
            // Walk instructions for precise def/use points
            int idx = b.startIdx;
            for (auto& instr : b.asmBlock->instrs) {
                auto uses = getUses(instr);
                auto defs = getDefs(instr);
                for (int r : uses) {
                    if (r >= 32 || isAllocatable(r))
                        extendInterval(intervals, r, idx, idx);
                }
                for (int r : defs) {
                    if (r >= 32 || isAllocatable(r))
                        extendInterval(intervals, r, idx, idx);
                }
                idx++;
            }
        }

        // Separate vreg intervals from fixed physical reg intervals
        std::vector<LiveInterval> vregIntervals;
        for (auto& [reg, iv] : intervals) {
            if (reg >= 32) {
                vregIntervals.push_back(iv);
            }
        }

        // Sort by start point
        std::sort(vregIntervals.begin(), vregIntervals.end(),
                  [](const LiveInterval& a, const LiveInterval& b) { return a.start < b.start; });

        std::string funcName = blocks[fStart]->label;

        // 5. Linear scan allocation
        auto allocRegs = getAllocRegs();
        int numRegs = (int)allocRegs.size();
        std::set<int> freeRegs(allocRegs.begin(), allocRegs.end());
        // active list sorted by end point
        std::vector<LiveInterval*> active;
        // Track which physical regs are occupied by fixed constraints at each point
        // We need to handle physical register constraints: if a vreg interval overlaps
        // with a fixed use of the same phys reg, we can't assign that phys reg.

        // Build a set of "blocked" ranges for each physical register
        // from fixed physical register uses in instructions
        std::unordered_map<int, std::vector<std::pair<int,int>>> physRegBlocked;
        for (auto& b : cfg) {
            int idx = b.startIdx;
            for (auto& instr : b.asmBlock->instrs) {
                auto defs = getDefs(instr);
                auto uses = getUses(instr);
                // Fixed phys regs (0-31) that appear in instructions
                for (int r : defs) {
                    if (r < 32 && isAllocatable(r)) {
                        physRegBlocked[r].push_back({idx, idx});
                    }
                }
                for (int r : uses) {
                    if (r < 32 && isAllocatable(r)) {
                        physRegBlocked[r].push_back({idx, idx});
                    }
                }
                // CALL clobbers all caller-saved regs
                if (instr.op == ASMOp::CALL) {
                    for (int cr : CALLER_SAVED) {
                        physRegBlocked[cr].push_back({idx, idx});
                    }
                    // ra is also clobbered
                    physRegBlocked[1].push_back({idx, idx});
                }
                idx++;
            }
        }

        // Helper: check if physReg is blocked at any point in [start, end]
        auto isBlocked = [&](int physReg, int start, int end) -> bool {
            auto it = physRegBlocked.find(physReg);
            if (it == physRegBlocked.end()) return false;
            for (auto& [bs, be] : it->second) {
                if (bs <= end && be >= start) return true;
            }
            return false;
        };

        int nextSpillSlot = 0;
        std::set<int> usedCalleeSaved;

        // Allocate
        for (auto& iv : vregIntervals) {
            // Expire old intervals
            active.erase(
                std::remove_if(active.begin(), active.end(),
                    [&](LiveInterval* j) {
                        if (j->end < iv.start) {
                            freeRegs.insert(j->physReg);
                            return true;
                        }
                        return false;
                    }),
                active.end()
            );

            // Try to find a free register not blocked during iv's range
            int chosen = -1;
            // Prefer callee-saved if interval crosses a call
            bool crossesCall = false;
            for (auto& [bs, be] : physRegBlocked.count(1) ? physRegBlocked[1] : std::vector<std::pair<int,int>>()) {
                // ra blocked = call point
                if (bs >= iv.start && bs <= iv.end) { crossesCall = true; break; }
            }

            if (crossesCall) {
                // Try callee-saved first
                for (int r : CALLEE_SAVED) {
                    if (freeRegs.count(r) && !isBlocked(r, iv.start, iv.end)) {
                        chosen = r; break;
                    }
                }
            }
            if (chosen == -1) {
                for (int r : allocRegs) {
                    if (freeRegs.count(r) && !isBlocked(r, iv.start, iv.end)) {
                        chosen = r; break;
                    }
                }
            }

            if (chosen != -1) {
                iv.physReg = chosen;
                freeRegs.erase(chosen);
                if (isCalleeSaved(chosen)) usedCalleeSaved.insert(chosen);
                active.push_back(&iv);
                std::sort(active.begin(), active.end(),
                    [](LiveInterval* a, LiveInterval* b) { return a->end < b->end; });
            } else {
                // Spill: try to spill the interval with the longest remaining range
                // If active has something ending later, spill that instead
                LiveInterval* spill = nullptr;
                if (!active.empty()) {
                    spill = active.back();
                }
                if (spill && spill->end > iv.end) {
                    // Spill the longer one, give its reg to current
                    iv.physReg = spill->physReg;
                    spill->physReg = -1;
                    spill->spillSlot = nextSpillSlot++;
                    active.pop_back();
                    active.push_back(&iv);
                    std::sort(active.begin(), active.end(),
                        [](LiveInterval* a, LiveInterval* b) { return a->end < b->end; });
                } else {
                    // Spill current interval
                    iv.spillSlot = nextSpillSlot++;
                }
            }
        }

        // Build vreg → allocation map
        std::unordered_map<int, int> vregToPhys; // vreg → physReg
        std::unordered_map<int, int> vregToSpill; // vreg → spillSlot
        for (auto& iv : vregIntervals) {
            if (iv.physReg != -1) {
                vregToPhys[iv.vreg] = iv.physReg;
            } else {
                vregToSpill[iv.vreg] = iv.spillSlot;
            }
        }

        // 6. Compute frame layout
        int spillAreaSize = nextSpillSlot * 4;
        int allocaSize = 0;
        for (auto& instr : cfg[0].asmBlock->instrs) {
            if (instr.funcName == "__PROLOGUE__") {
                break;
            }
        }
        allocaSize = computeAllocaSize(cfg);

        int calleeSaveCount = (int)usedCalleeSaved.size();
        int frameSize = allocaSize + spillAreaSize + calleeSaveCount * 4 + 8;
        if (frameSize % 16 != 0) frameSize = ((frameSize / 16) + 1) * 16;

        int raOffset = frameSize - 4;
        int s0Offset = frameSize - 8;
        int calleeSaveBase = allocaSize + spillAreaSize;

        // Sort callee-saved regs for deterministic ordering
        std::vector<int> calleeSavedList(usedCalleeSaved.begin(), usedCalleeSaved.end());
        std::sort(calleeSavedList.begin(), calleeSavedList.end());

        // 7. Rewrite instructions: replace vregs with physregs, insert spill loads/stores
        for (auto& b : cfg) {
            std::vector<ASMInstr> newInstrs;
            for (auto& instr : b.asmBlock->instrs) {
                // Skip prologue/epilogue markers (will be replaced)
                if (instr.funcName == "__PROLOGUE__" || instr.funcName == "__EPILOGUE__") {
                    // Keep as marker for later replacement
                    newInstrs.push_back(instr);
                    continue;
                }

                // Patch __ALLOCA__ instructions: rewrite vreg and adjust offset
                if (instr.funcName == "__ALLOCA__") {
                    ASMInstr patched = instr;
                    patched.funcName = "";
                    // Rewrite vregs in this instruction
                    auto replaceVreg = [&](Operand& op) {
                        if (op.type != OperandType::REG || op.value < 32) return;
                        int vreg = op.value;
                        if (vregToPhys.count(vreg)) op.value = vregToPhys[vreg];
                    };
                    // Check if rd is spilled
                    bool rdSpilled = false;
                    int rdVreg = -1;
                    if (patched.rd.type == OperandType::REG && patched.rd.value >= 32) {
                        rdVreg = patched.rd.value;
                        if (vregToSpill.count(rdVreg)) {
                            rdSpilled = true;
                            patched.rd.value = SCRATCH1;
                        } else {
                            replaceVreg(patched.rd);
                        }
                    }
                    replaceVreg(patched.rs1);
                    replaceVreg(patched.rs2);
                    newInstrs.push_back(patched);
                    if (rdSpilled) {
                        int slot = vregToSpill[rdVreg];
                        int off = allocaSize + slot * 4;
                        emitStore(newInstrs, SCRATCH1, 2, off);
                    }
                    continue;
                }

                // Collect which vregs need spill loads (uses) and spill stores (defs)
                auto uses = getUses(instr);
                auto defs = getDefs(instr);

                // Insert spill loads for used vregs that are spilled
                std::unordered_map<int, int> spillLoadMap; // vreg → scratch reg used
                int scratchIdx = 0;
                int scratchRegs[2] = {SCRATCH1, SCRATCH2};

                for (int r : uses) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        int slot = vregToSpill[r];
                        int off = allocaSize + slot * 4; // sp-relative
                        int scratch = scratchRegs[scratchIdx++ % 2];
                        spillLoadMap[r] = scratch;
                        emitLoad(newInstrs, scratch, 2, off); // lw scratch, off(sp)
                    }
                }

                // Also map spilled defs to scratch regs for rewriting
                std::unordered_map<int, int> spillDefMap; // vreg → scratch reg for def
                for (int r : defs) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        int scratch;
                        if (spillLoadMap.count(r)) {
                            scratch = spillLoadMap[r]; // reuse same scratch
                        } else {
                            scratch = scratchRegs[scratchIdx++ % 2];
                        }
                        spillDefMap[r] = scratch;
                        spillLoadMap[r] = scratch; // so rewriteOperand can find it
                    }
                }

                // Rewrite the instruction
                ASMInstr rewritten = instr;
                rewriteOperand(rewritten, vregToPhys, spillLoadMap);
                newInstrs.push_back(rewritten);

                // Insert spill stores for defined vregs that are spilled
                for (int r : defs) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        int slot = vregToSpill[r];
                        int off = allocaSize + slot * 4;
                        int physUsed = spillDefMap[r];
                        emitStore(newInstrs, physUsed, 2, off); // sw scratch, off(sp)
                    }
                }
            }
            b.asmBlock->instrs = newInstrs;
        }

        // 8. Replace prologue/epilogue markers
        // Prologue is in the first block
        {
            auto& instrs = cfg[0].asmBlock->instrs;
            for (int i = 0; i < (int)instrs.size(); i++) {
                if (instrs[i].funcName == "__PROLOGUE__") {
                    std::vector<ASMInstr> prologue;
                    emitPrologue(prologue, frameSize, raOffset, s0Offset,
                                 calleeSavedList, calleeSaveBase);
                    instrs.erase(instrs.begin() + i);
                    instrs.insert(instrs.begin() + i, prologue.begin(), prologue.end());
                    break;
                }
            }
        }

        // Epilogue: find the exit block (last block of function, or block with __EPILOGUE__)
        for (auto& b : cfg) {
            auto& instrs = b.asmBlock->instrs;
            for (int i = 0; i < (int)instrs.size(); i++) {
                if (instrs[i].funcName == "__EPILOGUE__") {
                    std::vector<ASMInstr> epilogue;
                    emitEpilogue(epilogue, frameSize, raOffset, s0Offset,
                                 calleeSavedList, calleeSaveBase);
                    instrs.erase(instrs.begin() + i);
                    instrs.insert(instrs.begin() + i, epilogue.begin(), epilogue.end());
                    break;
                }
            }
        }
    }

    // ============================================================
    //  CFG edge building
    // ============================================================
    void buildEdges(std::vector<CFGBlock>& cfg, std::unordered_map<std::string, int>& labelToIdx,
                    int bi, std::vector<ASMInstr>& instrs) {
        // Scan from the end for branch/jump instructions
        for (int i = (int)instrs.size() - 1; i >= 0; i--) {
            auto& instr = instrs[i];
            if (instr.op == ASMOp::J || instr.op == ASMOp::JAL) {
                std::string target = ".L" + std::to_string(instr.label.value);
                if (labelToIdx.count(target)) {
                    cfg[bi].succs.push_back(labelToIdx[target]);
                }
                // Don't break — there might be a conditional branch before this J
                continue;
            }
            if (instr.op == ASMOp::BNEZ || instr.op == ASMOp::BEQ || instr.op == ASMOp::BNE ||
                instr.op == ASMOp::BLT || instr.op == ASMOp::BGE || instr.op == ASMOp::BLTU ||
                instr.op == ASMOp::BGEU) {
                std::string target = ".L" + std::to_string(instr.label.value);
                if (labelToIdx.count(target)) {
                    cfg[bi].succs.push_back(labelToIdx[target]);
                }
                break; // Conditional branch is always before J, so we're done
            }
            if (instr.op == ASMOp::JR) {
                // Function return — no successors
                break;
            }
            if (instr.op == ASMOp::CALL) {
                // call is not a terminator, fall through
                // But if this is the last instr, fall through to next block
                if (bi + 1 < (int)cfg.size()) {
                    // Only add fall-through if there's no jump after
                    bool hasJumpAfter = false;
                    for (int j = i + 1; j < (int)instrs.size(); j++) {
                        if (instrs[j].op == ASMOp::J || instrs[j].op == ASMOp::JR ||
                            instrs[j].op == ASMOp::BNEZ) {
                            hasJumpAfter = true; break;
                        }
                    }
                    if (!hasJumpAfter) {
                        cfg[bi].succs.push_back(bi + 1);
                    }
                }
                break;
            }
            // Other instructions: not terminators
        }
        // If no terminator found (empty block or only non-control instrs), fall through
        if (cfg[bi].succs.empty() && bi + 1 < (int)cfg.size()) {
            // Check if block has any terminator
            bool hasTerm = false;
            for (auto& instr : instrs) {
                if (instr.op == ASMOp::J || instr.op == ASMOp::JR || instr.op == ASMOp::BNEZ ||
                    instr.op == ASMOp::BEQ || instr.op == ASMOp::BNE) {
                    hasTerm = true; break;
                }
            }
            if (!hasTerm) {
                cfg[bi].succs.push_back(bi + 1);
            }
        }
    }

    // ============================================================
    //  DEF/USE computation
    // ============================================================
    bool isAllocatable(int r) {
        if (r >= 32) return true;
        for (int x : CALLER_SAVED) if (x == r) return true;
        for (int x : CALLEE_SAVED) if (x == r) return true;
        return false;
    }

    std::vector<int> getDefs(const ASMInstr& instr) {
        std::vector<int> defs;
        switch (instr.op) {
            // R-type: def rd
            case ASMOp::ADD: case ASMOp::SUB: case ASMOp::MUL: case ASMOp::DIV:
            case ASMOp::DIVU: case ASMOp::REM: case ASMOp::REMU:
            case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA:
            case ASMOp::SLT: case ASMOp::SLTU:
                if (instr.rd.type == OperandType::REG && instr.rd.value != 0)
                    defs.push_back(instr.rd.value);
                break;
            // I-type: def rd
            case ASMOp::ADDI: case ASMOp::ANDI: case ASMOp::ORI: case ASMOp::XORI:
            case ASMOp::SLLI: case ASMOp::SRLI: case ASMOp::SRAI:
            case ASMOp::SLTI: case ASMOp::SLTIU:
                if (instr.rd.type == OperandType::REG && instr.rd.value != 0)
                    defs.push_back(instr.rd.value);
                break;
            // Load: def rd
            case ASMOp::LW: case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
                if (instr.rd.type == OperandType::REG && instr.rd.value != 0)
                    defs.push_back(instr.rd.value);
                break;
            // Store: no def
            case ASMOp::SW: case ASMOp::SB: case ASMOp::SH:
                break;
            // LI/LUI: def rd
            case ASMOp::LI: case ASMOp::LUI:
                if (instr.rd.type == OperandType::REG && instr.rd.value != 0)
                    defs.push_back(instr.rd.value);
                break;
            // MV: def rd
            case ASMOp::MV:
                if (instr.rd.type == OperandType::REG && instr.rd.value != 0)
                    defs.push_back(instr.rd.value);
                break;
            // SEQZ/SNEZ: def rd
            case ASMOp::SEQZ: case ASMOp::SNEZ:
                if (instr.rd.type == OperandType::REG && instr.rd.value != 0)
                    defs.push_back(instr.rd.value);
                break;
            // Branch: no def
            case ASMOp::BEQ: case ASMOp::BNE: case ASMOp::BLT: case ASMOp::BGE:
            case ASMOp::BLTU: case ASMOp::BGEU: case ASMOp::BNEZ:
                break;
            // Jump: no def
            case ASMOp::J: case ASMOp::JR:
                break;
            // CALL: clobbers all caller-saved + ra
            case ASMOp::CALL:
                for (int r : CALLER_SAVED) defs.push_back(r);
                defs.push_back(1); // ra
                break;
            default: break;
        }
        return defs;
    }

    std::vector<int> getUses(const ASMInstr& instr) {
        std::vector<int> uses;
        switch (instr.op) {
            case ASMOp::ADD: case ASMOp::SUB: case ASMOp::MUL: case ASMOp::DIV:
            case ASMOp::DIVU: case ASMOp::REM: case ASMOp::REMU:
            case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA:
            case ASMOp::SLT: case ASMOp::SLTU:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                if (instr.rs2.type == OperandType::REG && instr.rs2.value != 0)
                    uses.push_back(instr.rs2.value);
                break;
            case ASMOp::ADDI: case ASMOp::ANDI: case ASMOp::ORI: case ASMOp::XORI:
            case ASMOp::SLLI: case ASMOp::SRLI: case ASMOp::SRAI:
            case ASMOp::SLTI: case ASMOp::SLTIU:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                break;
            case ASMOp::LW: case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                break;
            case ASMOp::SW: case ASMOp::SB: case ASMOp::SH:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                if (instr.rs2.type == OperandType::REG && instr.rs2.value != 0)
                    uses.push_back(instr.rs2.value);
                break;
            case ASMOp::LI: case ASMOp::LUI:
                break; // no reg uses
            case ASMOp::MV:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                break;
            case ASMOp::SEQZ: case ASMOp::SNEZ:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                break;
            case ASMOp::BEQ: case ASMOp::BNE: case ASMOp::BLT: case ASMOp::BGE:
            case ASMOp::BLTU: case ASMOp::BGEU:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                if (instr.rs2.type == OperandType::REG && instr.rs2.value != 0)
                    uses.push_back(instr.rs2.value);
                break;
            case ASMOp::BNEZ:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                break;
            case ASMOp::J:
                break;
            case ASMOp::JR:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                break;
            case ASMOp::CALL:
                // Arguments are already moved to a0-a7 before call
                // The call itself implicitly uses a0-a7 (but they're already physical)
                break;
            default: break;
        }
        return uses;
    }

    void computeDefUse(CFGBlock& b) {
        // Process instructions in order: use before def within block
        for (auto& instr : b.asmBlock->instrs) {
            auto uses = getUses(instr);
            auto defs = getDefs(instr);
            for (int r : uses) {
                if ((r >= 32 || isAllocatable(r)) && b.def.find(r) == b.def.end()) {
                    b.use.insert(r);
                }
            }
            for (int r : defs) {
                if (r >= 32 || isAllocatable(r)) {
                    b.def.insert(r);
                }
            }
        }
    }

    // ============================================================
    //  Live interval helpers
    // ============================================================
    void extendInterval(std::unordered_map<int, LiveInterval>& intervals, int reg, int start, int end) {
        auto it = intervals.find(reg);
        if (it == intervals.end()) {
            LiveInterval iv;
            iv.vreg = reg;
            iv.start = start;
            iv.end = end;
            intervals[reg] = iv;
        } else {
            it->second.start = std::min(it->second.start, start);
            it->second.end = std::max(it->second.end, end);
        }
    }

    int computeAllocaSize(std::vector<CFGBlock>& cfg) {
        // Read totalAllocaSize encoded in __PROLOGUE__ marker's imm field
        for (auto& b : cfg) {
            for (auto& instr : b.asmBlock->instrs) {
                if (instr.funcName == "__PROLOGUE__") {
                    int sz = instr.imm.value;
                    return (sz + 3) / 4 * 4; // align to 4
                }
            }
        }
        return 0;
    }

    // ============================================================
    //  Instruction rewriting
    // ============================================================
    void rewriteOperand(ASMInstr& instr,
                        const std::unordered_map<int, int>& vregToPhys,
                        const std::unordered_map<int, int>& spillLoadMap) {
        auto rewrite = [&](Operand& op) {
            if (op.type != OperandType::REG || op.value < 32) return;
            int vreg = op.value;
            if (vregToPhys.count(vreg)) {
                op.value = vregToPhys.at(vreg);
            } else if (spillLoadMap.count(vreg)) {
                op.value = spillLoadMap.at(vreg);
            }
        };
        rewrite(instr.rd);
        rewrite(instr.rs1);
        rewrite(instr.rs2);
    }

    // ============================================================
    //  Spill load/store emission
    // ============================================================
    void emitLoad(std::vector<ASMInstr>& out, int dstReg, int baseReg, int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr lw;
            lw.op = ASMOp::LW;
            lw.rd = Operand(OperandType::REG, dstReg);
            lw.rs1 = Operand(OperandType::REG, baseReg);
            lw.imm = Operand(OperandType::IMM, offset);
            out.push_back(lw);
        } else {
            // Use dstReg itself as address temp to avoid clobbering the other scratch
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, dstReg);
            li.imm = Operand(OperandType::IMM, offset);
            out.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, dstReg);
            add.rs1 = Operand(OperandType::REG, dstReg);
            add.rs2 = Operand(OperandType::REG, baseReg);
            out.push_back(add);
            ASMInstr lw;
            lw.op = ASMOp::LW;
            lw.rd = Operand(OperandType::REG, dstReg);
            lw.rs1 = Operand(OperandType::REG, dstReg);
            lw.imm = Operand(OperandType::IMM, 0);
            out.push_back(lw);
        }
    }

    void emitStore(std::vector<ASMInstr>& out, int srcReg, int baseReg, int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr sw;
            sw.op = ASMOp::SW;
            sw.rs2 = Operand(OperandType::REG, srcReg);
            sw.rs1 = Operand(OperandType::REG, baseReg);
            sw.imm = Operand(OperandType::IMM, offset);
            out.push_back(sw);
        } else {
            // Use the OTHER scratch register for address computation
            int addrReg = (srcReg == SCRATCH1) ? SCRATCH2 : SCRATCH1;
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, addrReg);
            li.imm = Operand(OperandType::IMM, offset);
            out.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, addrReg);
            add.rs1 = Operand(OperandType::REG, addrReg);
            add.rs2 = Operand(OperandType::REG, baseReg);
            out.push_back(add);
            ASMInstr sw;
            sw.op = ASMOp::SW;
            sw.rs2 = Operand(OperandType::REG, srcReg);
            sw.rs1 = Operand(OperandType::REG, addrReg);
            sw.imm = Operand(OperandType::IMM, 0);
            out.push_back(sw);
        }
    }

    // ============================================================
    //  Prologue / Epilogue
    // ============================================================
    void emitPrologue(std::vector<ASMInstr>& out, int frameSize, int raOffset, int s0Offset,
                      const std::vector<int>& calleeSaved, int calleeSaveBase) {
        // addi sp, sp, -frameSize
        emitAddi(out, 2, 2, -frameSize);
        // sw ra, raOffset(sp)
        emitStoreFixed(out, 1, 2, raOffset);
        // sw s0, s0Offset(sp)
        emitStoreFixed(out, 8, 2, s0Offset);
        // Save callee-saved regs
        for (int i = 0; i < (int)calleeSaved.size(); i++) {
            emitStoreFixed(out, calleeSaved[i], 2, calleeSaveBase + i * 4);
        }
        // addi s0, sp, frameSize
        emitAddi(out, 8, 2, frameSize);
    }

    void emitEpilogue(std::vector<ASMInstr>& out, int frameSize, int raOffset, int s0Offset,
                      const std::vector<int>& calleeSaved, int calleeSaveBase) {
        // Restore callee-saved regs
        for (int i = 0; i < (int)calleeSaved.size(); i++) {
            emitLoadFixed(out, calleeSaved[i], 2, calleeSaveBase + i * 4);
        }
        // lw s0, s0Offset(sp)
        emitLoadFixed(out, 8, 2, s0Offset);
        // lw ra, raOffset(sp)
        emitLoadFixed(out, 1, 2, raOffset);
        // addi sp, sp, frameSize
        emitAddi(out, 2, 2, frameSize);
    }

    void emitAddi(std::vector<ASMInstr>& out, int rd, int rs1, int imm) {
        if (imm >= -2048 && imm <= 2047) {
            ASMInstr i;
            i.op = ASMOp::ADDI;
            i.rd = Operand(OperandType::REG, rd);
            i.rs1 = Operand(OperandType::REG, rs1);
            i.imm = Operand(OperandType::IMM, imm);
            out.push_back(i);
        } else {
            // Use t5 as temp (it's a scratch reg)
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, SCRATCH1);
            li.imm = Operand(OperandType::IMM, imm);
            out.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, rd);
            add.rs1 = Operand(OperandType::REG, rs1);
            add.rs2 = Operand(OperandType::REG, SCRATCH1);
            out.push_back(add);
        }
    }

    void emitStoreFixed(std::vector<ASMInstr>& out, int srcReg, int baseReg, int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr sw;
            sw.op = ASMOp::SW;
            sw.rs2 = Operand(OperandType::REG, srcReg);
            sw.rs1 = Operand(OperandType::REG, baseReg);
            sw.imm = Operand(OperandType::IMM, offset);
            out.push_back(sw);
        } else {
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, SCRATCH1);
            li.imm = Operand(OperandType::IMM, offset);
            out.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, SCRATCH1);
            add.rs1 = Operand(OperandType::REG, SCRATCH1);
            add.rs2 = Operand(OperandType::REG, baseReg);
            out.push_back(add);
            ASMInstr sw;
            sw.op = ASMOp::SW;
            sw.rs2 = Operand(OperandType::REG, srcReg);
            sw.rs1 = Operand(OperandType::REG, SCRATCH1);
            sw.imm = Operand(OperandType::IMM, 0);
            out.push_back(sw);
        }
    }

    void emitLoadFixed(std::vector<ASMInstr>& out, int dstReg, int baseReg, int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr lw;
            lw.op = ASMOp::LW;
            lw.rd = Operand(OperandType::REG, dstReg);
            lw.rs1 = Operand(OperandType::REG, baseReg);
            lw.imm = Operand(OperandType::IMM, offset);
            out.push_back(lw);
        } else {
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, SCRATCH1);
            li.imm = Operand(OperandType::IMM, offset);
            out.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, SCRATCH1);
            add.rs1 = Operand(OperandType::REG, SCRATCH1);
            add.rs2 = Operand(OperandType::REG, baseReg);
            out.push_back(add);
            ASMInstr lw;
            lw.op = ASMOp::LW;
            lw.rd = Operand(OperandType::REG, dstReg);
            lw.rs1 = Operand(OperandType::REG, SCRATCH1);
            lw.imm = Operand(OperandType::IMM, 0);
            out.push_back(lw);
        }
    }
};

} // namespace JaneZ
