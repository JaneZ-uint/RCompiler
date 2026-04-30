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
    for (int r : CALLEE_SAVED) regs.push_back(r);
    for (int r : CALLER_SAVED) regs.push_back(r);
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
            case ASMOp::SW: case ASMOp::SB: case ASMOp::SH:
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

        std::unordered_map<int, LiveInterval> intervals; // vreg → interval
        for (auto& b : cfg) {
            for (int r : b.liveIn) {
                extendInterval(intervals, r, b.startIdx, b.startIdx);
            }
            for (int r : b.liveOut) {
                extendInterval(intervals, r, b.endIdx - 1, b.endIdx - 1);
            }
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

        std::vector<LiveInterval> vregIntervals;
        for (auto& [reg, iv] : intervals) {
            if (reg >= 32) {
                vregIntervals.push_back(iv);
            }
        }

        std::sort(vregIntervals.begin(), vregIntervals.end(),
                  [](const LiveInterval& a, const LiveInterval& b) { return a.start < b.start; });

        std::string funcName = blocks[fStart]->label;

        auto allocRegs = getAllocRegs();
        int numRegs = (int)allocRegs.size();
        std::set<int> freeRegs(allocRegs.begin(), allocRegs.end());
        std::vector<LiveInterval*> active;

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

        for (auto& iv : vregIntervals) {
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
            int chosen = -1;
            bool crossesCall = false;
            for (auto& [bs, be] : physRegBlocked.count(1) ? physRegBlocked[1] : std::vector<std::pair<int,int>>()) {
                if (bs >= iv.start && bs <= iv.end) { 
                    crossesCall = true; 
                    break; 
                }
            }

            if (crossesCall) {
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
                LiveInterval* spill = nullptr;
                if (!active.empty()) {
                    spill = active.back();
                }
                if (spill && spill->end > iv.end) {
                    iv.physReg = spill->physReg;
                    spill->physReg = -1;
                    spill->spillSlot = nextSpillSlot++;
                    active.pop_back();
                    active.push_back(&iv);
                    std::sort(active.begin(), active.end(),
                        [](LiveInterval* a, LiveInterval* b) { return a->end < b->end; });
                } else {
                    iv.spillSlot = nextSpillSlot++;
                }
            }
        }

        std::unordered_map<int, int> vregToPhys;
        std::unordered_map<int, int> vregToSpill;
        for (auto& iv : vregIntervals) {
            if (iv.physReg != -1) {
                vregToPhys[iv.vreg] = iv.physReg;
            } else {
                vregToSpill[iv.vreg] = iv.spillSlot;
            }
        }

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
                        int off = allocaSize + slot * 4;
                        emitStore(newInstrs, SCRATCH1, 2, off);
                    }
                    continue;
                }

                auto uses = getUses(instr);
                auto defs = getDefs(instr);

                std::unordered_map<int, int> spillLoadMap; // vreg → scratch reg used
                int scratchIdx = 0;
                int scratchRegs[2] = {SCRATCH1, SCRATCH2};

                for (int r : uses) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        int slot = vregToSpill[r];
                        int off = allocaSize + slot * 4;
                        int scratch = scratchRegs[scratchIdx++ % 2];
                        spillLoadMap[r] = scratch;
                        emitLoad(newInstrs, scratch, 2, off);
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
                        int slot = vregToSpill[r];
                        int off = allocaSize + slot * 4;
                        int physUsed = spillDefMap[r];
                        emitStore(newInstrs, physUsed, 2, off); // sw scratch, off(sp)
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
                                 calleeSavedList, calleeSaveBase);
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
                                 calleeSavedList, calleeSaveBase);
                    instrs.erase(instrs.begin() + i);
                    instrs.insert(instrs.begin() + i, epilogue.begin(), epilogue.end());
                    break;
                }
            }
        }
    }

    void buildEdges(std::vector<CFGBlock>& cfg, std::unordered_map<std::string, int>& labelToIdx,
                    int bi, std::vector<ASMInstr>& instrs) {
        bool seenUncondJump = false;
        for (int i = (int)instrs.size() - 1; i >= 0; i--) {
            auto& instr = instrs[i];
            if (instr.op == ASMOp::J || instr.op == ASMOp::JAL) {
                std::string target = ".L" + std::to_string(instr.label.value);
                if (labelToIdx.count(target)) {
                    cfg[bi].succs.push_back(labelToIdx[target]);
                }
                seenUncondJump = true;
                continue;
            }
            if (instr.op == ASMOp::BNEZ || instr.op == ASMOp::BEQ || instr.op == ASMOp::BNE ||
                instr.op == ASMOp::BLT || instr.op == ASMOp::BGE || instr.op == ASMOp::BLTU ||
                instr.op == ASMOp::BGEU) {
                std::string target = ".L" + std::to_string(instr.label.value);
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
                if (instr.rs1.type == OperandType::REG && instr.rs1.value == 1)
                    uses.push_back(10);
                break;
            case ASMOp::CALL:
                for (int i = 10; i <= 17; i++) uses.push_back(i);
                break;
            default: break;
        }
        return uses;
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
            intervals[reg] = iv;
        } else {
            it->second.start = std::min(it->second.start, start);
            it->second.end = std::max(it->second.end, end);
        }
    }

    int computeAllocaSize(std::vector<CFGBlock>& cfg) {
        for (auto& b : cfg) {
            for (auto& instr : b.asmBlock->instrs) {
                if (instr.funcName == "__PROLOGUE__") {
                    int sz = instr.imm.value;
                    return (sz + 3) / 4 * 4;
                }
            }
        }
        return 0;
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
            ASMInstr lw;
            lw.op = ASMOp::LW;
            lw.rd = Operand(OperandType::REG, dstReg);
            lw.rs1 = Operand(OperandType::REG, baseReg);
            lw.imm = Operand(OperandType::IMM, offset);
            out.push_back(lw);
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

    void emitPrologue(std::vector<ASMInstr>& out, int frameSize, int raOffset, int s0Offset,
                      const std::vector<int>& calleeSaved, int calleeSaveBase) {
        emitAddi(out, 2, 2, -frameSize);
        emitStoreFixed(out, 1, 2, raOffset);
        emitStoreFixed(out, 8, 2, s0Offset);
        for (int i = 0; i < (int)calleeSaved.size(); i++) {
            emitStoreFixed(out, calleeSaved[i], 2, calleeSaveBase + i * 4);
        }
        emitAddi(out, 8, 2, frameSize);
    }

    void emitEpilogue(std::vector<ASMInstr>& out, int frameSize, int raOffset, int s0Offset,
                      const std::vector<int>& calleeSaved, int calleeSaveBase) {
        for (int i = 0; i < (int)calleeSaved.size(); i++) {
            emitLoadFixed(out, calleeSaved[i], 2, calleeSaveBase + i * 4);
        }
        emitLoadFixed(out, 8, 2, s0Offset);
        emitLoadFixed(out, 1, 2, raOffset);
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
