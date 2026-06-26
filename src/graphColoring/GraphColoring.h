# pragma once

#include "../linearScan/ASM.h"
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
};

struct CopyHint {
    int lhs = -1;
    int rhs = -1;
    int weight = 1;
};

struct AllocationStats {
    int spillSlots = 0;
    int calleeSaved = 0;
    long long spillWeight = 0;
    long long copyPenalty = 0;
};

struct FuncInfo {
    std::string name;
    int firstBlock;
    int lastBlock;
    int allocaSize;
    int numVRegs;
};

class GraphColoring {
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

        std::unordered_map<int, LiveInterval> intervals; // vreg -> interval
        std::unordered_map<int, int> useWeight;
        std::vector<CopyHint> copyHints;
        for (auto& b : cfg) {
            for (int r : b.liveIn) {
                extendInterval(intervals, r, b.startIdx, b.startIdx);
            }
            for (int r : b.liveOut) {
                extendInterval(intervals, r, b.endIdx - 1, b.endIdx - 1);
            }
            int idx = b.startIdx;
            for (auto& instr : b.asmBlock->instrs) {
                auto uses = uniqueRegs(getUses(instr));
                auto defs = uniqueRegs(getDefs(instr));
                int weight = blockWeight(b);
                for (int r : uses) {
                    if (r >= 32 || isAllocatable(r)) {
                        extendInterval(intervals, r, idx, idx);
                        if (r >= 32) useWeight[r] += weight;
                    }
                }
                for (int r : defs) {
                    if (r >= 32 || isAllocatable(r)) {
                        extendInterval(intervals, r, idx, idx);
                        if (r >= 32) useWeight[r] += weight;
                    }
                }
                if (instr.op == ASMOp::MV &&
                    instr.rd.type == OperandType::REG &&
                    instr.rs1.type == OperandType::REG &&
                    instr.rd.value >= 32 &&
                    instr.rs1.value >= 32 &&
                    instr.rd.value != instr.rs1.value) {
                    copyHints.push_back(CopyHint{(int)instr.rd.value, (int)instr.rs1.value, weight});
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

        int nextSpillSlot = 0;
        std::set<int> usedCalleeSaved;
        colorIntervals(vregIntervals, allocRegs, physRegBlocked, useWeight,
                       copyHints, nextSpillSlot, usedCalleeSaved);

        std::unordered_map<int, int> vregToPhys;
        std::unordered_map<int, int> vregToSpill;
        for (auto& iv : vregIntervals) {
            if (iv.physReg != -1) {
                vregToPhys[iv.vreg] = iv.physReg;
            } else {
                vregToSpill[iv.vreg] = iv.spillSlot;
            }
        }

        int spillAreaSize = nextSpillSlot * RISCV_XLEN_BYTES;
        int allocaSize = 0;
        for (auto& instr : cfg[0].asmBlock->instrs) {
            if (instr.funcName == "__PROLOGUE__") {
                break;
            }
        }
        allocaSize = computeAllocaSize(cfg);
        bool hasCall = functionHasCall(cfg);

        int calleeSaveCount = (int)usedCalleeSaved.size();
        int fixedSaveCount = hasCall ? 2 : 1;
        int frameSize = allocaSize + spillAreaSize + calleeSaveCount * RISCV_XLEN_BYTES +
                        fixedSaveCount * RISCV_XLEN_BYTES;
        if (frameSize % 16 != 0) frameSize = ((frameSize / 16) + 1) * 16;

        int raOffset = hasCall ? frameSize - RISCV_XLEN_BYTES : -1;
        int s0Offset = frameSize - fixedSaveCount * RISCV_XLEN_BYTES;
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

                std::unordered_map<int, int> spillLoadMap; // vreg → scratch reg used
                int scratchIdx = 0;
                int scratchRegs[2] = {SCRATCH1, SCRATCH2};

                for (int r : uses) {
                    if (r >= 32 && vregToSpill.count(r)) {
                        int slot = vregToSpill[r];
                        int off = allocaSize + slot * RISCV_XLEN_BYTES - frameSize;
                        int scratch = scratchRegs[scratchIdx++ % 2];
                        spillLoadMap[r] = scratch;
                        emitLoad(newInstrs, scratch, 8, off);
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
                for (int i = 10; i <= 17; i++) uses.push_back(i);
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

    bool intervalsOverlap(const LiveInterval &a, const LiveInterval &b) const {
        return a.start <= b.end && b.start <= a.end;
    }

    bool intervalsTouchOrOverlap(const LiveInterval &a, const LiveInterval &b) const {
        return a.start <= b.end + 1 && b.start <= a.end + 1;
    }

    int blockWeight(const CFGBlock &b) const {
        for (int succ : b.succs) {
            if (succ <= b.id) return 8;
        }
        return 1;
    }

    bool physRegBlockedForInterval(
        int physReg,
        const LiveInterval &iv,
        const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked) const {
        auto it = physRegBlocked.find(physReg);
        if (it == physRegBlocked.end()) return false;
        for (const auto &range : it->second) {
            if (range.first <= iv.end && range.second >= iv.start) return true;
        }
        return false;
    }

    bool crossesCall(
        const LiveInterval &iv,
        const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked) const {
        auto it = physRegBlocked.find(1);
        if (it == physRegBlocked.end()) return false;
        for (const auto &range : it->second) {
            if (range.first >= iv.start && range.first <= iv.end) return true;
        }
        return false;
    }

    int intervalLength(const LiveInterval &iv) const {
        return std::max(1, iv.end - iv.start + 1);
    }

    int intervalUseWeight(const LiveInterval &iv,
                          const std::unordered_map<int, int> &useWeight) const {
        auto it = useWeight.find(iv.vreg);
        return it == useWeight.end() ? intervalLength(iv) : std::max(1, it->second);
    }

    long long spillCost(const LiveInterval &iv,
                        const std::unordered_map<int, int> &useWeight,
                        const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked) const {
        long long cost = intervalUseWeight(iv, useWeight) * 16LL + intervalLength(iv);
        if (crossesCall(iv, physRegBlocked)) cost += 200;
        return cost;
    }

    long long colorChoiceCost(int physReg,
                             const LiveInterval &iv,
                             const std::set<int> &usedCalleeSaved,
                             const std::unordered_map<int, int> &useWeight,
                             const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked) const {
        long long cost = 0;
        bool ivCrossesCall = crossesCall(iv, physRegBlocked);
        if (isCalleeSaved(physReg)) {
            if (!usedCalleeSaved.count(physReg)) cost += 48;
            cost += ivCrossesCall ? 0 : 12;
        } else if (ivCrossesCall) {
            cost += 300 + intervalUseWeight(iv, useWeight);
        }
        return cost;
    }

    int findSet(std::unordered_map<int, int> &parent, int v) const {
        auto it = parent.find(v);
        if (it == parent.end() || it->second == v) return v;
        it->second = findSet(parent, it->second);
        return it->second;
    }

    int findSetConst(const std::unordered_map<int, int> &parent, int v) const {
        auto it = parent.find(v);
        while (it != parent.end() && it->second != v) {
            v = it->second;
            it = parent.find(v);
        }
        return v;
    }

    bool canMergeIntervals(const LiveInterval &a, const LiveInterval &b) const {
        return !intervalsOverlap(a, b);
    }

    std::vector<LiveInterval> coalesceIntervals(
        const std::vector<LiveInterval> &intervals,
        const std::vector<CopyHint> &copyHints,
        const std::unordered_map<int, int> &useWeight,
        std::unordered_map<int, int> &alias) const {
        std::unordered_map<int, LiveInterval> merged;
        std::unordered_map<int, int> parent;
        for (const auto &iv : intervals) {
            parent[iv.vreg] = iv.vreg;
            merged[iv.vreg] = iv;
        }

        auto hints = copyHints;
        std::sort(hints.begin(), hints.end(),
            [](const CopyHint &a, const CopyHint &b) { return a.weight > b.weight; });

        for (const auto &hint : hints) {
            if (!parent.count(hint.lhs) || !parent.count(hint.rhs)) continue;
            int a = findSet(parent, hint.lhs);
            int b = findSet(parent, hint.rhs);
            if (a == b) continue;
            if (!canMergeIntervals(merged[a], merged[b])) continue;
            int keep = a;
            int kill = b;
            int weightA = useWeight.count(a) ? useWeight.at(a) : 0;
            int weightB = useWeight.count(b) ? useWeight.at(b) : 0;
            if (weightB > weightA) {
                keep = b;
                kill = a;
            }
            parent[kill] = keep;
            merged[keep].start = std::min(merged[keep].start, merged[kill].start);
            merged[keep].end = std::max(merged[keep].end, merged[kill].end);
            merged.erase(kill);
        }

        alias.clear();
        std::unordered_set<int> seenRoots;
        std::vector<LiveInterval> out;
        out.reserve(merged.size());
        for (const auto &iv : intervals) {
            int root = findSet(parent, iv.vreg);
            alias[iv.vreg] = root;
            if (seenRoots.insert(root).second) {
                out.push_back(merged[root]);
            }
        }
        std::sort(out.begin(), out.end(),
            [](const LiveInterval &a, const LiveInterval &b) { return a.start < b.start; });
        return out;
    }

    std::unordered_map<int, int> buildIndex(const std::vector<LiveInterval> &intervals) const {
        std::unordered_map<int, int> idx;
        for (int i = 0; i < static_cast<int>(intervals.size()); i++) {
            idx[intervals[i].vreg] = i;
        }
        return idx;
    }

    std::vector<std::set<int>> buildInterferenceGraph(
        const std::vector<LiveInterval> &intervals,
        bool &tooDense) const {
        tooDense = false;
        const long long maxEdges = 800000;
        const int maxActive = 900;
        long long edgeCount = 0;
        std::vector<std::set<int>> graph(intervals.size());
        std::vector<int> order(intervals.size());
        for (int i = 0; i < static_cast<int>(intervals.size()); i++) order[i] = i;
        std::sort(order.begin(), order.end(), [&](int a, int b) {
            if (intervals[a].start != intervals[b].start) {
                return intervals[a].start < intervals[b].start;
            }
            return intervals[a].end < intervals[b].end;
        });

        std::vector<int> active;
        for (int idx : order) {
            active.erase(std::remove_if(active.begin(), active.end(), [&](int other) {
                return intervals[other].end < intervals[idx].start;
            }), active.end());
            if (static_cast<int>(active.size()) > maxActive) {
                tooDense = true;
                return graph;
            }
            for (int other : active) {
                if (intervalsOverlap(intervals[idx], intervals[other])) {
                    graph[idx].insert(other);
                    graph[other].insert(idx);
                    edgeCount++;
                    if (edgeCount > maxEdges) {
                        tooDense = true;
                        return graph;
                    }
                }
            }
            active.push_back(idx);
        }
        return graph;
    }

    long long allocationCost(
        const std::vector<LiveInterval> &intervals,
        const std::set<int> &usedCalleeSaved,
        const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked) const {
        long long cost = static_cast<long long>(usedCalleeSaved.size()) * 40;
        for (const auto &iv : intervals) {
            int len = intervalLength(iv);
            if (iv.spillSlot >= 0) {
                cost += 1000 + len * 20;
                if (crossesCall(iv, physRegBlocked)) cost += 500;
            } else if (iv.physReg >= 0) {
                if (crossesCall(iv, physRegBlocked) && !isCalleeSaved(iv.physReg)) {
                    cost += 200 + len;
                }
                if (isCalleeSaved(iv.physReg)) {
                    cost += 8;
                }
            }
        }
        return cost;
    }

    AllocationStats allocationStats(
        const std::vector<LiveInterval> &intervals,
        const std::set<int> &usedCalleeSaved,
        const std::vector<CopyHint> &copyHints,
        const std::unordered_map<int, int> &useWeight,
        const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked) const {
        AllocationStats stats;
        stats.calleeSaved = static_cast<int>(usedCalleeSaved.size());
        std::unordered_map<int, const LiveInterval*> byReg;
        for (const auto &iv : intervals) {
            byReg[iv.vreg] = &iv;
            if (iv.spillSlot >= 0) {
                stats.spillSlots++;
                int weight = useWeight.count(iv.vreg) ? useWeight.at(iv.vreg) : intervalLength(iv);
                stats.spillWeight += 1000 + static_cast<long long>(weight) * 40;
                if (crossesCall(iv, physRegBlocked)) stats.spillWeight += 500;
            }
        }
        for (const auto &hint : copyHints) {
            auto lhs = byReg.find(hint.lhs);
            auto rhs = byReg.find(hint.rhs);
            if (lhs == byReg.end() || rhs == byReg.end()) continue;
            const auto *a = lhs->second;
            const auto *b = rhs->second;
            if (a->spillSlot >= 0 || b->spillSlot >= 0) {
                stats.copyPenalty += hint.weight * 2;
            } else if (a->physReg != b->physReg) {
                stats.copyPenalty += hint.weight;
            }
        }
        return stats;
    }

    bool graphColoringIsBetter(const AllocationStats &color,
                               const AllocationStats &fallback) const {
        if (color.spillSlots < fallback.spillSlots &&
            color.calleeSaved <= fallback.calleeSaved + 1) {
            return true;
        }
        if (color.spillSlots == fallback.spillSlots &&
            color.spillWeight <= fallback.spillWeight &&
            color.calleeSaved <= fallback.calleeSaved &&
            color.copyPenalty + 8 < fallback.copyPenalty) {
            return true;
        }
        return false;
    }

    std::vector<int> preferredColorOrder(const LiveInterval &iv,
                                         const std::vector<int> &allocRegs,
                                         bool ivCrossesCall) const {
        std::vector<int> ordered;
        ordered.reserve(allocRegs.size());
        auto appendIf = [&](bool wantCallee) {
            for (int r : allocRegs) {
                if ((isCalleeSaved(r) && wantCallee) ||
                    (!isCalleeSaved(r) && !wantCallee)) {
                    ordered.push_back(r);
                }
            }
        };
        if (ivCrossesCall) {
            appendIf(true);
            appendIf(false);
        } else {
            appendIf(false);
            appendIf(true);
        }
        return ordered;
    }

    void linearScanFallback(
        std::vector<LiveInterval> &intervals,
        const std::vector<int> &allocRegs,
        const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked,
        int &nextSpillSlot,
        std::set<int> &usedCalleeSaved) {
        std::set<int> freeRegs(allocRegs.begin(), allocRegs.end());
        std::vector<LiveInterval*> active;
        auto isBlocked = [&](int physReg, int start, int end) -> bool {
            auto it = physRegBlocked.find(physReg);
            if (it == physRegBlocked.end()) return false;
            for (const auto &range : it->second) {
                if (range.first <= end && range.second >= start) return true;
            }
            return false;
        };

        for (auto &iv : intervals) {
            active.erase(
                std::remove_if(active.begin(), active.end(),
                    [&](LiveInterval *j) {
                        if (j->end < iv.start) {
                            freeRegs.insert(j->physReg);
                            return true;
                        }
                        return false;
                    }),
                active.end());

            int chosen = -1;
            bool ivCrossesCall = crossesCall(iv, physRegBlocked);
            if (ivCrossesCall) {
                for (int r : CALLEE_SAVED) {
                    if (freeRegs.count(r) && !isBlocked(r, iv.start, iv.end)) {
                        chosen = r;
                        break;
                    }
                }
            }
            if (chosen == -1) {
                for (int r : allocRegs) {
                    if (freeRegs.count(r) && !isBlocked(r, iv.start, iv.end)) {
                        chosen = r;
                        break;
                    }
                }
            }

            if (chosen != -1) {
                iv.physReg = chosen;
                freeRegs.erase(chosen);
                if (isCalleeSaved(chosen)) usedCalleeSaved.insert(chosen);
                active.push_back(&iv);
                std::sort(active.begin(), active.end(),
                    [](LiveInterval *a, LiveInterval *b) { return a->end < b->end; });
            } else {
                LiveInterval *spill = nullptr;
                for (auto it = active.rbegin(); it != active.rend(); ++it) {
                    if ((*it)->end > iv.end && !isBlocked((*it)->physReg, iv.start, iv.end)) {
                        spill = *it;
                        break;
                    }
                }
                if (spill) {
                    iv.physReg = spill->physReg;
                    spill->physReg = -1;
                    spill->spillSlot = nextSpillSlot++;
                    active.erase(std::remove(active.begin(), active.end(), spill), active.end());
                    active.push_back(&iv);
                    std::sort(active.begin(), active.end(),
                        [](LiveInterval *a, LiveInterval *b) { return a->end < b->end; });
                } else {
                    iv.spillSlot = nextSpillSlot++;
                }
            }
        }
    }

    void colorIntervals(
        std::vector<LiveInterval> &intervals,
        const std::vector<int> &allocRegs,
        const std::unordered_map<int, std::vector<std::pair<int,int>>> &physRegBlocked,
        const std::unordered_map<int, int> &useWeight,
        const std::vector<CopyHint> &copyHints,
        int &nextSpillSlot,
        std::set<int> &usedCalleeSaved) {
        const int K = static_cast<int>(allocRegs.size());
        for (int i = 0; i < static_cast<int>(intervals.size()); i++) {
            intervals[i].physReg = -1;
            intervals[i].spillSlot = -1;
        }
        auto fallbackIntervals = intervals;
        int fallbackSpillSlots = 0;
        std::set<int> fallbackCalleeSaved;
        linearScanFallback(fallbackIntervals, allocRegs, physRegBlocked,
                           fallbackSpillSlots, fallbackCalleeSaved);
        const long long n = static_cast<long long>(intervals.size());
        if (n > 4000) {
            intervals = std::move(fallbackIntervals);
            nextSpillSlot = fallbackSpillSlots;
            usedCalleeSaved = std::move(fallbackCalleeSaved);
            return;
        }

        std::unordered_map<int, int> alias;
        auto colorIntervals = coalesceIntervals(intervals, copyHints, useWeight, alias);
        bool tooDense = false;
        auto graph = buildInterferenceGraph(colorIntervals, tooDense);
        if (tooDense) {
            intervals = std::move(fallbackIntervals);
            nextSpillSlot = fallbackSpillSlots;
            usedCalleeSaved = std::move(fallbackCalleeSaved);
            return;
        }

        std::vector<std::set<int>> workGraph = graph;
        std::vector<bool> removed(colorIntervals.size(), false);
        std::vector<int> stack;
        stack.reserve(colorIntervals.size());
        int remaining = static_cast<int>(colorIntervals.size());

        while (remaining > 0) {
            int pick = -1;
            for (int i = 0; i < static_cast<int>(colorIntervals.size()); i++) {
                if (!removed[i] && static_cast<int>(workGraph[i].size()) < K) {
                    if (pick < 0 || intervalLength(colorIntervals[i]) < intervalLength(colorIntervals[pick])) {
                        pick = i;
                    }
                }
            }
            if (pick < 0) {
                for (int i = 0; i < static_cast<int>(colorIntervals.size()); i++) {
                    if (removed[i]) continue;
                    long long lhsCost = spillCost(colorIntervals[i], useWeight, physRegBlocked);
                    long long rhsCost = pick < 0 ? -1 : spillCost(colorIntervals[pick], useWeight, physRegBlocked);
                    if (pick < 0 || lhsCost < rhsCost ||
                        (lhsCost == rhsCost &&
                         static_cast<int>(workGraph[i].size()) > static_cast<int>(workGraph[pick].size()))) {
                        pick = i;
                    }
                }
            }

            removed[pick] = true;
            remaining--;
            stack.push_back(pick);
            for (int neighbor : workGraph[pick]) {
                workGraph[neighbor].erase(pick);
            }
            workGraph[pick].clear();
        }

        while (!stack.empty()) {
            int idx = stack.back();
            stack.pop_back();
            const auto &iv = colorIntervals[idx];
            std::set<int> forbidden;
            for (int neighbor : graph[idx]) {
                int color = colorIntervals[neighbor].physReg;
                if (color >= 0) forbidden.insert(color);
            }

            bool ivCrossesCall = crossesCall(iv, physRegBlocked);
            int chosen = -1;
            long long bestCost = 0;
            for (int reg : preferredColorOrder(iv, allocRegs, ivCrossesCall)) {
                if (forbidden.count(reg)) continue;
                if (physRegBlockedForInterval(reg, iv, physRegBlocked)) continue;
                long long cost = colorChoiceCost(reg, iv, usedCalleeSaved, useWeight, physRegBlocked);
                if (chosen < 0 || cost < bestCost) {
                    chosen = reg;
                    bestCost = cost;
                }
            }

            if (chosen >= 0) {
                colorIntervals[idx].physReg = chosen;
                if (isCalleeSaved(chosen)) usedCalleeSaved.insert(chosen);
            } else {
                colorIntervals[idx].spillSlot = nextSpillSlot++;
            }
        }

        auto coloredByRoot = buildIndex(colorIntervals);
        int maxSpillSlot = nextSpillSlot;
        for (auto &iv : intervals) {
            int root = alias.count(iv.vreg) ? alias[iv.vreg] : iv.vreg;
            int idx = coloredByRoot.count(root) ? coloredByRoot[root] : -1;
            if (idx < 0) continue;
            iv.physReg = colorIntervals[idx].physReg;
            iv.spillSlot = colorIntervals[idx].spillSlot;
            if (iv.spillSlot >= maxSpillSlot) maxSpillSlot = iv.spillSlot + 1;
        }
        nextSpillSlot = maxSpillSlot;

        auto colorStats = allocationStats(intervals, usedCalleeSaved, copyHints,
                                          useWeight, physRegBlocked);
        auto fallbackStats = allocationStats(fallbackIntervals, fallbackCalleeSaved,
                                             copyHints, useWeight, physRegBlocked);
        if (!graphColoringIsBetter(colorStats, fallbackStats)) {
            intervals = std::move(fallbackIntervals);
            nextSpillSlot = fallbackSpillSlots;
            usedCalleeSaved = std::move(fallbackCalleeSaved);
        }
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
