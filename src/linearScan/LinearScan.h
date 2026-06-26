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
static const int CALLER_SAVED[] = {5,6,7, 28,29, 10,11,12,13,14,15,16,17}; // t0-t2, t3-t4, a0-a7
static const int CALLEE_SAVED[] = {9, 18,19,20,21,22,23,24,25,26}; // s1, s2-s10
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

static std::vector<int> getAllocRegs() {
    std::vector<int> regs;
    for (int r : CALLER_SAVED) regs.push_back(r);
    for (int r : CALLEE_SAVED) regs.push_back(r);
    return regs;
}

struct CFGBlock {
    int id;
    ASMBlock* asmBlock;
    int startIdx = 0;
    int endIdx = 0;
    std::vector<int> succs;
    std::vector<int> preds;
    std::set<int> def;
    std::set<int> use;
    std::set<int> liveIn;
    std::set<int> liveOut;
};

struct LiveInterval {
    int vreg;
    int start;
    int end;
    int physReg = -1;  
    int spillSlot = -1;
    long long useWeight = 1;
    std::vector<std::pair<int,int>> ranges;
};

struct RematValue {
    ASMOp op = ASMOp::LI;
    long long imm = 0;
};

struct FuncInfo {
    std::string name;
    int firstBlock;
    int lastBlock;
    int allocaSize;
    int numVRegs;
};

class LinearScan {
public:
    void process(std::vector<std::shared_ptr<ASMBlock>>& blocks) {
        std::vector<std::pair<int,int>> funcRanges;
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

    void deadCodeElimination(std::vector<std::shared_ptr<ASMBlock>>& blocks) {
        std::vector<std::pair<int,int>> funcRanges;
        for (int i = 0; i < (int)blocks.size(); i++) {
            if (!blocks[i]->label.empty() && blocks[i]->label[0] != '.') {
                if (!funcRanges.empty()) funcRanges.back().second = i;
                funcRanges.push_back({i, (int)blocks.size()});
            }
        }
        if (!funcRanges.empty()) funcRanges.back().second = (int)blocks.size();

        for (auto& [fStart, fEnd] : funcRanges) {
            dceFunction(blocks, fStart, fEnd);
        }
    }

private:
    bool hasSideEffect(const ASMInstr& instr) {
        if (!instr.funcName.empty()) return true;
        switch (instr.op) {
            case ASMOp::SW: case ASMOp::SD: case ASMOp::SB: case ASMOp::SH:
            case ASMOp::CALL:
            case ASMOp::J: case ASMOp::JR: case ASMOp::JAL:
            case ASMOp::BNEZ: case ASMOp::BEQ: case ASMOp::BNE:
            case ASMOp::BLT: case ASMOp::BGE: case ASMOp::BLTU: case ASMOp::BGEU:
                return true;
            default:
                return false;
        }
    }

    void dceFunction(std::vector<std::shared_ptr<ASMBlock>>& blocks, int fStart, int fEnd) {
        bool changed = true;
        while (changed) {
            changed = false;

            std::vector<CFGBlock> cfg;
            std::unordered_map<std::string, int> labelToIdx;
            for (int i = fStart; i < fEnd; i++) {
                CFGBlock b;
                b.id = i - fStart;
                b.asmBlock = blocks[i].get();
                cfg.push_back(b);
                labelToIdx[blocks[i]->label] = b.id;
            }

            for (auto& b : cfg) {
                auto& instrs = b.asmBlock->instrs;
                for (int i = 0; i < (int)instrs.size(); i++) {
                    if (instrs[i].op == ASMOp::J || instrs[i].op == ASMOp::JR) {
                        if (i + 1 < (int)instrs.size()) {
                            instrs.erase(instrs.begin() + i + 1, instrs.end());
                            changed = true;
                        }
                        break;
                    }
                }
            }

            for (int bi = 0; bi < (int)cfg.size(); bi++) {
                auto& instrs = cfg[bi].asmBlock->instrs;
                if (instrs.empty()) continue;
                buildEdges(cfg, labelToIdx, bi, instrs);
            }
            for (int i = 0; i < (int)cfg.size(); i++) {
                for (int s : cfg[i].succs)
                    cfg[s].preds.push_back(i);
            }
            for (auto& b : cfg) computeDefUse(b);

            bool liveChanged = true;
            while (liveChanged) {
                liveChanged = false;
                for (int i = (int)cfg.size() - 1; i >= 0; i--) {
                    auto& b = cfg[i];
                    std::set<int> newLiveOut;
                    for (int s : b.succs)
                        for (int r : cfg[s].liveIn) newLiveOut.insert(r);
                    std::set<int> newLiveIn = b.use;
                    for (int r : newLiveOut)
                        if (b.def.find(r) == b.def.end()) newLiveIn.insert(r);
                    if (newLiveIn != b.liveIn || newLiveOut != b.liveOut) {
                        b.liveIn = newLiveIn;
                        b.liveOut = newLiveOut;
                        liveChanged = true;
                    }
                }
            }

            for (auto& b : cfg) {
                std::set<int> live = b.liveOut;
                std::vector<bool> dead(b.asmBlock->instrs.size(), false);

                for (int i = (int)b.asmBlock->instrs.size() - 1; i >= 0; i--) {
                    auto& instr = b.asmBlock->instrs[i];
                    if (hasSideEffect(instr)) {
                        for (int r : getDefs(instr)) live.erase(r);
                        for (int r : getUses(instr)) live.insert(r);
                        continue;
                    }
                    auto defs = getDefs(instr);
                    bool allDead = !defs.empty();
                    for (int r : defs) {
                        if (r > 0 && r < 32 && !isAllocatable(r)) { allDead = false; break; }
                        if (live.count(r)) { allDead = false; break; }
                    }
                    if (allDead) {
                        dead[i] = true;
                        changed = true;
                    } else {
                        for (int r : defs) live.erase(r);
                        for (int r : getUses(instr)) live.insert(r);
                    }
                }

                if (changed) {
                    std::vector<ASMInstr> newInstrs;
                    for (int i = 0; i < (int)b.asmBlock->instrs.size(); i++) {
                        if (!dead[i]) newInstrs.push_back(b.asmBlock->instrs[i]);
                    }
                    b.asmBlock->instrs = std::move(newInstrs);
                }
            }
        }
    }

    void processFunction(std::vector<std::shared_ptr<ASMBlock>>& blocks, int fStart, int fEnd) {
        std::vector<CFGBlock> cfg;
        std::unordered_map<std::string, int> labelToIdx;
        for (int i = fStart; i < fEnd; i++) {
            CFGBlock b;
            b.id = i - fStart;
            b.asmBlock = blocks[i].get();
            cfg.push_back(b);
            labelToIdx[blocks[i]->label] = b.id;
        }

        int instrIdx = 0;
        for (auto& b : cfg) {
            b.startIdx = instrIdx;
            instrIdx += (int)b.asmBlock->instrs.size();
            b.endIdx = instrIdx;
        }
        int totalInstrs = instrIdx;

        for (int bi = 0; bi < (int)cfg.size(); bi++) {
            auto& instrs = cfg[bi].asmBlock->instrs;
            if (instrs.empty()) continue;
            buildEdges(cfg, labelToIdx, bi, instrs);
        }

        for (int i = 0; i < (int)cfg.size(); i++) {
            for (int s : cfg[i].succs) {
                cfg[s].preds.push_back(i);
            }
        }

        for (auto& b : cfg) {
            computeDefUse(b);
        }

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

        std::vector<long long> blockWeight(cfg.size(), 1);
        for (const auto& b : cfg) {
            for (int succ : b.succs) {
                if (succ <= b.id) {
                    for (int i = succ; i <= b.id && i < (int)blockWeight.size(); i++) {
                        blockWeight[i] = std::min<long long>(blockWeight[i] * 8, 4096);
                    }
                }
            }
        }

        std::unordered_map<int, RematValue> rematValues;
        std::unordered_set<int> rematInvalid;
        for (auto& b : cfg) {
            for (auto& instr : b.asmBlock->instrs) {
                auto defs = uniqueRegs(getDefs(instr));
                bool isLiCandidate = instr.op == ASMOp::LI &&
                                     instr.rd.type == OperandType::REG &&
                                     instr.rd.value >= 32 &&
                                     instr.imm.type == OperandType::IMM &&
                                     defs.size() == 1 &&
                                     defs[0] == instr.rd.value &&
                                     instr.funcName.empty();
                for (int r : defs) {
                    if (r < 32) continue;
                    if (isLiCandidate && r == instr.rd.value) {
                        if (rematValues.count(r) || rematInvalid.count(r)) {
                            rematValues.erase(r);
                            rematInvalid.insert(r);
                        } else {
                            rematValues[r] = RematValue{ASMOp::LI, instr.imm.value};
                        }
                    } else {
                        rematValues.erase(r);
                        rematInvalid.insert(r);
                    }
                }
            }
        }

        std::unordered_map<int, LiveInterval> intervals; // vreg → interval
        std::unordered_map<int, long long> useWeight;
        std::unordered_map<int, std::vector<int>> copyHints;
        for (auto& b : cfg) {
            int idx = b.startIdx;
            for (auto& instr : b.asmBlock->instrs) {
                auto uses = uniqueRegs(getUses(instr));
                auto defs = uniqueRegs(getDefs(instr));
                for (int r : uses) {
                    if (r >= 32) {
                        useWeight[r] += blockWeight[b.id];
                    }
                }
                for (int r : defs) {
                    if (r >= 32 && useWeight.find(r) == useWeight.end()) useWeight[r] = 1;
                }
                if (instr.op == ASMOp::MV &&
                    instr.rd.type == OperandType::REG &&
                    instr.rs1.type == OperandType::REG &&
                    instr.rd.value >= 32 &&
                    instr.rs1.value >= 32 &&
                    instr.rd.value != instr.rs1.value) {
                    copyHints[instr.rd.value].push_back(instr.rs1.value);
                    copyHints[instr.rs1.value].push_back(instr.rd.value);
                }
                idx++;
            }
        }

        for (auto& b : cfg) {
            std::set<int> live = b.liveOut;
            for (int i = (int)b.asmBlock->instrs.size() - 1; i >= 0; i--) {
                int idx = b.startIdx + i;
                auto uses = uniqueRegs(getUses(b.asmBlock->instrs[i]));
                auto defs = uniqueRegs(getDefs(b.asmBlock->instrs[i]));
                std::set<int> liveBefore = live;
                for (int r : defs) {
                    if (r >= 32 || isAllocatable(r)) {
                        liveBefore.erase(r);
                    }
                }
                for (int r : uses) {
                    if (r >= 32 || isAllocatable(r)) {
                        liveBefore.insert(r);
                    }
                }
                for (int r : liveBefore) {
                    if (r >= 32 || isAllocatable(r)) {
                        extendInterval(intervals, r, idx, idx);
                    }
                }
                for (int r : defs) {
                    if (r >= 32 || isAllocatable(r)) {
                        extendInterval(intervals, r, idx, idx);
                    }
                }
                live = std::move(liveBefore);
            }
        }

        std::vector<LiveInterval> vregIntervals;
        for (auto& [reg, iv] : intervals) {
            if (reg >= 32) {
                iv.useWeight = std::max<long long>(1, useWeight[reg]);
                normalizeRanges(iv);
                vregIntervals.push_back(iv);
            }
        }

        std::sort(vregIntervals.begin(), vregIntervals.end(),
                  [](const LiveInterval& a, const LiveInterval& b) { return a.start < b.start; });

        std::string funcName = blocks[fStart]->label;

        auto allocRegs = getAllocRegs();

        std::unordered_map<int, std::vector<std::pair<int,int>>> physRegBlocked;
        for (auto& b : cfg) {
            int idx = b.startIdx;
            for (auto& instr : b.asmBlock->instrs) {
                auto defs = getDefs(instr);
                auto uses = getUses(instr);
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
                if (instr.op == ASMOp::CALL) {
                    for (int cr : CALLER_SAVED) {
                        physRegBlocked[cr].push_back({idx, idx});
                    }
                    // ra
                    physRegBlocked[1].push_back({idx, idx});
                }
                idx++;
            }
        }

        auto regBlockedForInterval = [&](int physReg, const LiveInterval& iv) -> bool {
            auto it = physRegBlocked.find(physReg);
            if (it == physRegBlocked.end()) return false;
            for (auto& [rs, re] : iv.ranges) {
                for (auto& [bs, be] : it->second) {
                    if (bs <= re && be >= rs) return true;
                }
            }
            return false;
        };

        auto intervalsOverlap = [&](const LiveInterval& a, const LiveInterval& b) -> bool {
            size_t i = 0, j = 0;
            while (i < a.ranges.size() && j < b.ranges.size()) {
                auto [as, ae] = a.ranges[i];
                auto [bs, be] = b.ranges[j];
                if (as <= be && bs <= ae) return true;
                if (ae < be) {
                    i++;
                } else {
                    j++;
                }
            }
            return false;
        };

        int nextSpillSlot = 0;
        std::set<int> usedCalleeSaved;
        std::unordered_map<int, int> assignedPhys;
        std::unordered_map<int, std::vector<LiveInterval*>> assignedByReg;

        auto intervalLength = [](const LiveInterval& iv) -> long long {
            long long length = 0;
            for (auto& [s, e] : iv.ranges) {
                length += std::max(1, e - s + 1);
            }
            if (length <= 0) length = std::max(1, iv.end - iv.start + 1);
            return length;
        };

        auto spillPriority = [&](const LiveInterval& iv) -> long long {
            long long priority = (std::max<long long>(1, iv.useWeight) * 1024) / intervalLength(iv);
            if (rematValues.count(iv.vreg)) {
                priority = std::max<long long>(1, priority / 8);
            }
            return priority;
        };

        auto shouldPreferRemat = [&](const LiveInterval& iv) -> bool {
            if (!rematValues.count(iv.vreg)) return false;
            long long length = intervalLength(iv);
            if (length < 32) return false;
            long long density = (std::max<long long>(1, iv.useWeight) * 1024) / length;
            return density <= 256;
        };

        auto spillInterval = [&](LiveInterval& iv) {
            iv.physReg = -1;
            iv.spillSlot = nextSpillSlot++;
            assignedPhys.erase(iv.vreg);
        };

        auto canAssignReg = [&](int reg, const LiveInterval& iv) -> bool {
            if (regBlockedForInterval(reg, iv)) return false;
            auto it = assignedByReg.find(reg);
            if (it == assignedByReg.end()) return true;
            for (auto* other : it->second) {
                if (other->physReg == reg && intervalsOverlap(*other, iv)) return false;
            }
            return true;
        };

        auto assignReg = [&](LiveInterval& iv, int reg) {
            iv.physReg = reg;
            if (isCalleeSaved(reg)) usedCalleeSaved.insert(reg);
            assignedPhys[iv.vreg] = reg;
            assignedByReg[reg].push_back(&iv);
        };

        auto unassignReg = [&](LiveInterval* iv) {
            int reg = iv->physReg;
            if (reg == -1) return;
            auto& list = assignedByReg[reg];
            list.erase(std::remove(list.begin(), list.end(), iv), list.end());
            assignedPhys.erase(iv->vreg);
            iv->physReg = -1;
        };

        auto pruneAssignedBefore = [&](int start) {
            for (auto& [reg, list] : assignedByReg) {
                list.erase(std::remove_if(list.begin(), list.end(),
                    [&](LiveInterval* other) {
                        return other->physReg != reg || other->end < start;
                    }),
                    list.end());
            }
        };

        for (auto& iv : vregIntervals) {
            pruneAssignedBefore(iv.start);
            int chosen = -1;
            bool crossesCall = regBlockedForInterval(1, iv);

            if (shouldPreferRemat(iv)) {
                spillInterval(iv);
                continue;
            }

            auto tryCopyHint = [&]() {
                auto it = copyHints.find(iv.vreg);
                if (it == copyHints.end()) return;
                for (int related : it->second) {
                    auto physIt = assignedPhys.find(related);
                    if (physIt == assignedPhys.end()) continue;
                    int reg = physIt->second;
                    if (canAssignReg(reg, iv)) {
                        chosen = reg;
                        return;
                    }
                }
            };

            tryCopyHint();
            if (crossesCall) {
                if (chosen == -1 || !isCalleeSaved(chosen)) {
                    chosen = -1;
                    for (int r : CALLEE_SAVED) {
                        if (canAssignReg(r, iv)) {
                            chosen = r; break;
                        }
                    }
                }
            }
            if (chosen == -1) {
                for (int r : allocRegs) {
                    if (canAssignReg(r, iv)) {
                        chosen = r; break;
                    }
                }
            }

            if (chosen != -1) {
                assignReg(iv, chosen);
            } else {
                LiveInterval* spill = nullptr;
                int spillReg = -1;
                for (int r : allocRegs) {
                    if (regBlockedForInterval(r, iv)) continue;
                    std::vector<LiveInterval*> blockers;
                    for (auto* candidate : assignedByReg[r]) {
                        if (candidate->physReg == r && intervalsOverlap(*candidate, iv)) {
                            blockers.push_back(candidate);
                        }
                    }
                    if (blockers.size() != 1) continue;
                    auto* candidate = blockers[0];
                    if (!spill ||
                        spillPriority(*candidate) < spillPriority(*spill) ||
                        (spillPriority(*candidate) == spillPriority(*spill) &&
                         candidate->end > spill->end)) {
                        spill = candidate;
                        spillReg = r;
                    }
                }
                if (spill && spillPriority(*spill) <= spillPriority(iv)) {
                    unassignReg(spill);
                    spillInterval(*spill);
                    assignReg(iv, spillReg);
                } else {
                    spillInterval(iv);
                }
            }
        }

        std::unordered_map<int, int> vregToPhys;
        std::unordered_map<int, int> vregToSpill;
        int compactSpillSlots = 0;
        usedCalleeSaved.clear();
        for (auto& iv : vregIntervals) {
            if (iv.physReg != -1) {
                vregToPhys[iv.vreg] = iv.physReg;
                if (isCalleeSaved(iv.physReg)) usedCalleeSaved.insert(iv.physReg);
            } else {
                if (rematValues.count(iv.vreg)) {
                    vregToSpill[iv.vreg] = -1;
                } else {
                    vregToSpill[iv.vreg] = compactSpillSlots++;
                }
            }
        }

        int spillAreaSize = compactSpillSlots * RISCV_XLEN_BYTES;
        int allocaSize = 0;
        for (auto& instr : cfg[0].asmBlock->instrs) {
            if (instr.funcName == "__PROLOGUE__") {
                break;
            }
        }
        allocaSize = computeAllocaSize(cfg);
        bool hasCall = functionHasCall(cfg);

        int calleeSaveCount = (int)usedCalleeSaved.size();
        bool usesFrameBase = functionUsesPhysicalReg(cfg, 8);
        bool needsFrame = hasCall || usesFrameBase || allocaSize > 0 || spillAreaSize > 0 ||
                          calleeSaveCount > 0;
        int fixedSaveCount = hasCall ? 2 : (needsFrame ? 1 : 0);
        int frameSize = 0;
        if (needsFrame) {
            frameSize = allocaSize + spillAreaSize + calleeSaveCount * RISCV_XLEN_BYTES +
                        fixedSaveCount * RISCV_XLEN_BYTES;
            if (frameSize % 16 != 0) frameSize = ((frameSize / 16) + 1) * 16;
        }

        int raOffset = hasCall ? frameSize - RISCV_XLEN_BYTES : -1;
        int s0Offset = needsFrame ? frameSize - fixedSaveCount * RISCV_XLEN_BYTES : -1;
        int calleeSaveBase = allocaSize + spillAreaSize;

        std::vector<int> calleeSavedList(usedCalleeSaved.begin(), usedCalleeSaved.end());
        std::sort(calleeSavedList.begin(), calleeSavedList.end());

        for (auto& b : cfg) {
            std::vector<ASMInstr> newInstrs;
            for (auto& instr : b.asmBlock->instrs) {
                if (instr.funcName == "__PROLOGUE__" || instr.funcName == "__EPILOGUE__") {
                    newInstrs.push_back(instr);
                    continue;
                }
                if (instr.funcName == "__ALLOCA__") {
                    ASMInstr patched = instr;
                    patched.funcName = "";
                    auto replaceVreg = [&](Operand& op) {
                        if (op.type != OperandType::REG || op.value < 32) return;
                        int vreg = op.value;
                        if (vregToPhys.count(vreg)) op.value = vregToPhys[vreg];
                    };
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
                        int off = allocaSize + slot * RISCV_XLEN_BYTES - frameSize;
                        emitStore(newInstrs, SCRATCH1, 8, off);
                    }
                    continue;
                }

                auto uses = uniqueRegs(getUses(instr));
                auto defs = uniqueRegs(getDefs(instr));

                if (instr.op == ASMOp::LI &&
                    instr.rd.type == OperandType::REG &&
                    instr.rd.value >= 32 &&
                    vregToSpill.count(instr.rd.value) &&
                    rematValues.count(instr.rd.value) &&
                    instr.imm.type == OperandType::IMM &&
                    rematValues[instr.rd.value].imm == instr.imm.value) {
                    continue;
                }

                std::unordered_map<int, int> spillLoadMap; // vreg → scratch reg used
                int scratchIdx = 0;
                int scratchRegs[2] = {SCRATCH1, SCRATCH2};

                for (int r : uses) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        int scratch = scratchRegs[scratchIdx++ % 2];
                        spillLoadMap[r] = scratch;
                        auto remat = rematValues.find(r);
                        if (remat != rematValues.end()) {
                            emitRematerialize(newInstrs, scratch, remat->second);
                        } else {
                            int slot = vregToSpill[r];
                            int off = allocaSize + slot * RISCV_XLEN_BYTES - frameSize;
                            emitLoad(newInstrs, scratch, 8, off);
                        }
                    }
                }

                std::unordered_map<int, int> spillDefMap;
                for (int r : defs) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        int scratch;
                        if (spillLoadMap.count(r)) {
                            scratch = spillLoadMap[r];//既是use又是def的虚拟寄存器，直接复用之前的scratch寄存器，避免重复load
                        } else {
                            scratch = scratchRegs[scratchIdx++ % 2];
                        }
                        spillDefMap[r] = scratch;
                        spillLoadMap[r] = scratch;
                    }
                }

                ASMInstr rewritten = instr;
                rewriteOperand(rewritten, vregToPhys, spillLoadMap);
                newInstrs.push_back(rewritten);

                for (int r : defs) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        if (rematValues.count(r)) continue;
                        int slot = vregToSpill[r];
                        int off = allocaSize + slot * RISCV_XLEN_BYTES - frameSize;
                        int physUsed = spillDefMap[r];
                        emitStore(newInstrs, physUsed, 8, off);
                    }
                }
            }
            b.asmBlock->instrs = newInstrs;
        }

        {
            auto& instrs = cfg[0].asmBlock->instrs;
            for (int i = 0; i < (int)instrs.size(); i++) {
                if (instrs[i].funcName == "__PROLOGUE__") {
                    std::vector<ASMInstr> prologue;
                    emitPrologue(prologue, frameSize, raOffset, s0Offset,
                                 calleeSavedList, calleeSaveBase, hasCall);
                    instrs.erase(instrs.begin() + i);
                    instrs.insert(instrs.begin() + i, prologue.begin(), prologue.end());
                    break;
                }
            }
        }

        for (auto& b : cfg) {
            auto& instrs = b.asmBlock->instrs;
            for (int i = 0; i < (int)instrs.size(); i++) {
                if (instrs[i].funcName == "__EPILOGUE__") {
                    std::vector<ASMInstr> epilogue;
                    emitEpilogue(epilogue, frameSize, raOffset, s0Offset,
                                 calleeSavedList, calleeSaveBase, hasCall);
                    instrs.erase(instrs.begin() + i);
                    instrs.insert(instrs.begin() + i, epilogue.begin(), epilogue.end());
                    break;
                }
            }
        }
    }

    void buildEdges(std::vector<CFGBlock>& cfg, std::unordered_map<std::string, int>& labelToIdx,
                    int bi, std::vector<ASMInstr>& instrs) {
        auto formatLabel = [](const Operand &label) {
            if(label.type == OperandType::EXIT_LABEL){
                return ".Lexit" + std::to_string(label.value);
            }
            return ".L" + std::to_string(label.value);
        };
        bool seenUncondJump = false;
        for (int i = (int)instrs.size() - 1; i >= 0; i--) {
            auto& instr = instrs[i];
            if (instr.op == ASMOp::J || instr.op == ASMOp::JAL) {
                std::string target = formatLabel(instr.label);
                if (labelToIdx.count(target)) {
                    cfg[bi].succs.push_back(labelToIdx[target]);
                }
                seenUncondJump = true;
                continue;
            }
            if (instr.op == ASMOp::BNEZ || instr.op == ASMOp::BEQ || instr.op == ASMOp::BNE ||
                instr.op == ASMOp::BLT || instr.op == ASMOp::BGE || instr.op == ASMOp::BLTU ||
                instr.op == ASMOp::BGEU) {
                std::string target = formatLabel(instr.label);
                if (labelToIdx.count(target)) {
                    cfg[bi].succs.push_back(labelToIdx[target]);
                }
                if (!seenUncondJump && bi + 1 < (int)cfg.size()) {
                    cfg[bi].succs.push_back(bi + 1);
                }
                break;
            }
            if (instr.op == ASMOp::JR) {
                break;
            }
        }
        if (cfg[bi].succs.empty() && bi + 1 < (int)cfg.size()) {
            bool hasTerm = false;
            for (auto& instr : instrs) {
                if (instr.op == ASMOp::J || instr.op == ASMOp::JR || instr.op == ASMOp::BNEZ ||
                    instr.op == ASMOp::BEQ || instr.op == ASMOp::BNE ||
                    instr.op == ASMOp::BLT || instr.op == ASMOp::BGE ||
                    instr.op == ASMOp::BLTU || instr.op == ASMOp::BGEU) {
                    hasTerm = true; break;
                }
            }
            if (!hasTerm) {
                cfg[bi].succs.push_back(bi + 1);
            }
        }
    }

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
            case ASMOp::ADDW: case ASMOp::SUBW: case ASMOp::MULW: case ASMOp::DIVW:
            case ASMOp::DIVUW: case ASMOp::REMW: case ASMOp::REMUW:
            case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA:
            case ASMOp::SLLW: case ASMOp::SRLW: case ASMOp::SRAW:
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
            case ASMOp::LW: case ASMOp::LWU: case ASMOp::LD: case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
                if (instr.rd.type == OperandType::REG && instr.rd.value != 0)
                    defs.push_back(instr.rd.value);
                break;
            // Store: no def
            case ASMOp::SW: case ASMOp::SD: case ASMOp::SB: case ASMOp::SH:
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
            case ASMOp::ADDW: case ASMOp::SUBW: case ASMOp::MULW: case ASMOp::DIVW:
            case ASMOp::DIVUW: case ASMOp::REMW: case ASMOp::REMUW:
            case ASMOp::AND: case ASMOp::OR: case ASMOp::XOR:
            case ASMOp::SLL: case ASMOp::SRL: case ASMOp::SRA:
            case ASMOp::SLLW: case ASMOp::SRLW: case ASMOp::SRAW:
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
            case ASMOp::LW: case ASMOp::LWU: case ASMOp::LD: case ASMOp::LB: case ASMOp::LH: case ASMOp::LBU: case ASMOp::LHU:
                if (instr.rs1.type == OperandType::REG && instr.rs1.value != 0)
                    uses.push_back(instr.rs1.value);
                break;
            case ASMOp::SW: case ASMOp::SD: case ASMOp::SB: case ASMOp::SH:
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
                if (instr.rs1.type == OperandType::REG && instr.rs1.value == 1)
                    uses.push_back(10);
                break;
            case ASMOp::CALL:
                {
                    int argCount = instr.callArgCount >= 0 ? instr.callArgCount : 8;
                    if (argCount > 8) argCount = 8;
                    for (int i = 0; i < argCount; i++) uses.push_back(10 + i);
                }
                break;
            default: break;
        }
        return uses;
    }

    std::vector<int> uniqueRegs(std::vector<int> regs) {
        std::vector<int> unique;
        std::unordered_set<int> seen;
        unique.reserve(regs.size());
        for (int r : regs) {
            if (seen.insert(r).second) unique.push_back(r);
        }
        return unique;
    }

    void computeDefUse(CFGBlock& b) {
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

    void extendInterval(std::unordered_map<int, LiveInterval>& intervals, int reg, int start, int end) {
        auto it = intervals.find(reg);
        if (it == intervals.end()) {
            LiveInterval iv;
            iv.vreg = reg;
            iv.start = start;
            iv.end = end;
            iv.ranges.push_back({start, end});
            intervals[reg] = iv;
        } else {
            it->second.start = std::min(it->second.start, start);
            it->second.end = std::max(it->second.end, end);
            it->second.ranges.push_back({start, end});
        }
    }

    void normalizeRanges(LiveInterval& iv) {
        if (iv.ranges.empty()) {
            iv.ranges.push_back({iv.start, iv.end});
            return;
        }
        std::sort(iv.ranges.begin(), iv.ranges.end());
        std::vector<std::pair<int,int>> merged;
        for (auto [start, end] : iv.ranges) {
            if (merged.empty() || start > merged.back().second + 1) {
                merged.push_back({start, end});
            } else {
                merged.back().second = std::max(merged.back().second, end);
            }
        }
        iv.ranges = std::move(merged);
        iv.start = iv.ranges.front().first;
        iv.end = iv.ranges.back().second;
    }

    int computeAllocaSize(std::vector<CFGBlock>& cfg) {
        for (auto& b : cfg) {
            for (auto& instr : b.asmBlock->instrs) {
                if (instr.funcName == "__PROLOGUE__") {
                    int sz = instr.imm.value;
                    return (sz + RISCV_XLEN_BYTES - 1) / RISCV_XLEN_BYTES * RISCV_XLEN_BYTES;
                }
            }
        }
        return 0;
    }

    bool functionHasCall(const std::vector<CFGBlock>& cfg) {
        for (const auto& b : cfg) {
            for (const auto& instr : b.asmBlock->instrs) {
                if (instr.op == ASMOp::CALL) return true;
            }
        }
        return false;
    }

    bool functionUsesPhysicalReg(const std::vector<CFGBlock>& cfg, int reg) {
        auto hasReg = [&](const Operand& op) {
            return op.type == OperandType::REG && op.value == reg;
        };
        for (const auto& b : cfg) {
            for (const auto& instr : b.asmBlock->instrs) {
                if (instr.funcName == "__PROLOGUE__" || instr.funcName == "__EPILOGUE__") {
                    continue;
                }
                if (hasReg(instr.rd) || hasReg(instr.rs1) || hasReg(instr.rs2)) {
                    return true;
                }
            }
        }
        return false;
    }

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

    void emitLoad(std::vector<ASMInstr>& out, int dstReg, int baseReg, int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr ld;
            ld.op = ASMOp::LD;
            ld.rd = Operand(OperandType::REG, dstReg);
            ld.rs1 = Operand(OperandType::REG, baseReg);
            ld.imm = Operand(OperandType::IMM, offset);
            out.push_back(ld);
        } else {
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
            ASMInstr ld;
            ld.op = ASMOp::LD;
            ld.rd = Operand(OperandType::REG, dstReg);
            ld.rs1 = Operand(OperandType::REG, dstReg);
            ld.imm = Operand(OperandType::IMM, 0);
            out.push_back(ld);
        }
    }

    void emitRematerialize(std::vector<ASMInstr>& out, int dstReg, const RematValue& value) {
        if (value.op == ASMOp::LI) {
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, dstReg);
            li.imm = Operand(OperandType::IMM, value.imm);
            out.push_back(li);
        }
    }

    void emitStore(std::vector<ASMInstr>& out, int srcReg, int baseReg, int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr sd;
            sd.op = ASMOp::SD;
            sd.rs2 = Operand(OperandType::REG, srcReg);
            sd.rs1 = Operand(OperandType::REG, baseReg);
            sd.imm = Operand(OperandType::IMM, offset);
            out.push_back(sd);
        } else {
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
            ASMInstr sd;
            sd.op = ASMOp::SD;
            sd.rs2 = Operand(OperandType::REG, srcReg);
            sd.rs1 = Operand(OperandType::REG, addrReg);
            sd.imm = Operand(OperandType::IMM, 0);
            out.push_back(sd);
        }
    }

    void emitPrologue(std::vector<ASMInstr>& out, int frameSize, int raOffset, int s0Offset,
                      const std::vector<int>& calleeSaved, int calleeSaveBase, bool saveRa) {
        if (frameSize == 0) return;
        emitAddi(out, 2, 2, -frameSize);
        if (saveRa) emitStoreFixed(out, 1, 2, raOffset);
        emitStoreFixed(out, 8, 2, s0Offset);
        for (int i = 0; i < (int)calleeSaved.size(); i++) {
            emitStoreFixed(out, calleeSaved[i], 2, calleeSaveBase + i * RISCV_XLEN_BYTES);
        }
        emitAddi(out, 8, 2, frameSize);
    }

    void emitEpilogue(std::vector<ASMInstr>& out, int frameSize, int raOffset, int s0Offset,
                      const std::vector<int>& calleeSaved, int calleeSaveBase, bool saveRa) {
        if (frameSize == 0) return;
        for (int i = 0; i < (int)calleeSaved.size(); i++) {
            emitLoadFixed(out, calleeSaved[i], 2, calleeSaveBase + i * RISCV_XLEN_BYTES);
        }
        emitLoadFixed(out, 8, 2, s0Offset);
        if (saveRa) emitLoadFixed(out, 1, 2, raOffset);
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
            ASMInstr sd;
            sd.op = ASMOp::SD;
            sd.rs2 = Operand(OperandType::REG, srcReg);
            sd.rs1 = Operand(OperandType::REG, baseReg);
            sd.imm = Operand(OperandType::IMM, offset);
            out.push_back(sd);
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
            ASMInstr sd;
            sd.op = ASMOp::SD;
            sd.rs2 = Operand(OperandType::REG, srcReg);
            sd.rs1 = Operand(OperandType::REG, SCRATCH1);
            sd.imm = Operand(OperandType::IMM, 0);
            out.push_back(sd);
        }
    }

    void emitLoadFixed(std::vector<ASMInstr>& out, int dstReg, int baseReg, int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr ld;
            ld.op = ASMOp::LD;
            ld.rd = Operand(OperandType::REG, dstReg);
            ld.rs1 = Operand(OperandType::REG, baseReg);
            ld.imm = Operand(OperandType::IMM, offset);
            out.push_back(ld);
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
            ASMInstr ld;
            ld.op = ASMOp::LD;
            ld.rd = Operand(OperandType::REG, dstReg);
            ld.rs1 = Operand(OperandType::REG, SCRATCH1);
            ld.imm = Operand(OperandType::IMM, 0);
            out.push_back(ld);
        }
    }
};

} // namespace JaneZ
