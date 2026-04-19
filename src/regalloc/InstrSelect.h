# pragma once
# include "ASM.h"
# include "../ir/IRNode.h"
# include "../ir/IRBinaryop.h"
# include "../ir/IRLiteral.h"
# include "../ir/IRStore.h"
# include "../ir/IRLoad.h"
# include "../ir/IRBr.h"
# include "../ir/IRReturn.h"
# include "../ir/IRBlock.h"
# include "../ir/IRFunction.h"
# include "../ir/IRCall.h"
# include "../ir/IRBr.h"
# include "../ir/IRType.h"
# include "../ir/IRParam.h"
# include "../ir/IRGetptr.h"
# include "../ir/IRAlloca.h"
# include "../ir/IRRoot.h"
# include "../ir/IRPhi.h"
# include "../ir/IRPHI.h"
# include "../ir/IRImpl.h"
# include "../ir/IRPrint.h"
# include "../ir/IRExit.h"
# include "../ir/IRGetint.h"
# include "../ir/IRMem.h"
# include "../ir/IRTrunc.h"
# include "../ir/IRZext.h"
# include "../ir/IRSext.h"
#include <memory>
#include <vector>
#include <unordered_map>
#include <iostream>

namespace JaneZ {

class InstrSelect {
public:
    std::vector<std::shared_ptr<ASMBlock>> asmBlocks;
    std::shared_ptr<ASMBlock> currentBlock;
    std::shared_ptr<IRBlock> currentIRBlock;
    std::unordered_map<std::shared_ptr<IRBlock>, std::shared_ptr<ASMBlock>> blockMap;

    int exitblock = 1;
    int currenctExitBlock = 1;
    std::string currentFuncExitLabel;

    // ---- vreg allocator ----
    int nextVReg = 32;
    std::unordered_map<IRNode*, int> valueToVReg;

    int getVReg(std::shared_ptr<IRNode> val) {
        IRNode* key = val.get();
        auto it = valueToVReg.find(key);
        if (it != valueToVReg.end()) return it->second;
        int vr = nextVReg++;
        valueToVReg[key] = vr;
        return vr;
    }
    int freshVReg() { return nextVReg++; }

    // ---- alloca tracking ----
    int allocaOffset = 0; // grows upward from sp
    std::unordered_map<IRNode*, int> allocaStackOffset; // IRVar* → sp-relative offset

    int getAllocaSlot(std::shared_ptr<IRNode> var, int size) {
        IRNode* key = var.get();
        auto it = allocaStackOffset.find(key);
        if (it != allocaStackOffset.end()) return it->second;
        int aligned = (size + 3) / 4 * 4;
        int off = allocaOffset;
        allocaOffset += aligned;
        allocaStackOffset[key] = off;
        return off;
    }

    int totalAllocaSize = 0; // set after processing all allocas

    // Materialize an IR value into a vreg: literal → li, var → mapped vreg
    int materialize(std::shared_ptr<IRNode> val) {
        if (auto* lit = dynamic_cast<IRLiteral*>(val.get())) {
            int vr = freshVReg();
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, vr);
            li.imm = Operand(OperandType::IMM, lit->intValue);
            currentBlock->instrs.push_back(li);
            return vr;
        }
        return getVReg(val);
    }

    // ========== entry ==========
    void select(std::shared_ptr<IRRoot> irRoot) {
        asmBlocks.clear();
        for (auto& func : irRoot->children) {
            if (auto* irFunc = dynamic_cast<IRFunction*>(func.get())) {
                selectFunc(std::make_shared<IRFunction>(*irFunc));
            } else if (auto* irImpl = dynamic_cast<IRImpl*>(func.get())) {
                for (auto& implFunc : irImpl->functions) {
                    selectFunc(std::make_shared<IRFunction>(*implFunc));
                }
            }
        }
    }

    // Per-function state kept in a struct so recursion on nested funcs works
    void selectFunc(std::shared_ptr<IRFunction> irFunc) {
        blockMap.clear();
        nextVReg = 32;
        valueToVReg.clear();
        allocaOffset = 0;
        allocaStackOffset.clear();

        // Recurse into nested functions first
        for (auto& nested : irFunc->funcList) {
            selectFunc(nested);
        }

        int myExitBlockID = exitblock++;
        currenctExitBlock = myExitBlockID;
        currentFuncExitLabel = ".L" + std::to_string(currenctExitBlock);

        std::string funcName = irFunc->name;
        if (irFunc->parentStructType) {
            funcName = irFunc->parentStructType->name + "_" + funcName;
        }

        auto entryBlock = std::make_shared<ASMBlock>(funcName);
        asmBlocks.push_back(entryBlock);

        if (!irFunc->body) return;

        blockMap[irFunc->body] = entryBlock;
        for (auto& block : irFunc->body->blockList) {
            int id = (int)block->label;
            auto ab = std::make_shared<ASMBlock>(".L" + std::to_string(id));
            blockMap[block] = ab;
            asmBlocks.push_back(ab);
        }

        currentBlock = entryBlock;
        currentIRBlock = irFunc->body;

        // ---- Emit PLACEHOLDER prologue marker ----
        // We insert a NOP-like marker; LinearScan will patch it later.
        // The marker is: addi x0, x0, 0  (effectively nop, with funcName tag)
        {
            ASMInstr marker;
            marker.op = ASMOp::ADDI;
            marker.rd = Operand(OperandType::REG, 0);
            marker.rs1 = Operand(OperandType::REG, 0);
            marker.imm = Operand(OperandType::IMM, 0);
            marker.funcName = "__PROLOGUE__";
            currentBlock->instrs.push_back(marker);
        }

        // ---- Move arguments from physical regs to vregs ----
        int argCount = irFunc->paramList->paramList.size();
        for (int i = 0; i < argCount; i++) {
            int vr = getVReg(irFunc->paramList->paramList[i]);
            if (i < 8) {
                // mv vreg, a{i}
                ASMInstr mv;
                mv.op = ASMOp::MV;
                mv.rd = Operand(OperandType::REG, vr);
                mv.rs1 = Operand(OperandType::REG, 10 + i); // a0-a7
                currentBlock->instrs.push_back(mv);
            } else {
                // lw vreg, offset(s0)  — s0 points to old sp
                // Caller pushed extra args starting at old_sp + 0
                int stackParamOffset = (i - 8) * 4;
                ASMInstr lw;
                lw.op = ASMOp::LW;
                lw.rd = Operand(OperandType::REG, vr);
                lw.rs1 = Operand(OperandType::REG, 8); // s0
                lw.imm = Operand(OperandType::IMM, stackParamOffset);
                currentBlock->instrs.push_back(lw);
            }
        }

        // ---- First pass: collect all allocas and assign stack offsets ----
        for (auto& instr : irFunc->body->instrList) {
            if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                processAlloca(alloca);
            }
        }
        for (auto& block : irFunc->body->blockList) {
            for (auto& instr : block->instrList) {
                if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                    processAlloca(alloca);
                }
            }
        }
        totalAllocaSize = allocaOffset;

        // Patch the prologue marker with totalAllocaSize
        for (auto& instr : entryBlock->instrs) {
            if (instr.funcName == "__PROLOGUE__") {
                instr.imm = Operand(OperandType::IMM, totalAllocaSize);
                break;
            }
        }

        // ---- Emit alloca address instructions (in entry block) ----
        for (auto& instr : irFunc->body->instrList) {
            if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                emitAllocaAddr(alloca);
            }
        }
        for (auto& block : irFunc->body->blockList) {
            for (auto& instr : block->instrList) {
                if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                    // Emit alloca addr in the entry block, not in the alloca's block
                    auto savedBlock = currentBlock;
                    currentBlock = blockMap[irFunc->body];
                    emitAllocaAddr(alloca);
                    currentBlock = savedBlock;
                }
            }
        }

        // ---- Second pass: emit instructions for entry block (skip alloca) ----
        for (auto& instr : irFunc->body->instrList) {
            if (std::dynamic_pointer_cast<IRAlloca>(instr)) continue;
            selectInstr(instr);
        }

        // ---- Emit instructions for other blocks ----
        for (auto& block : irFunc->body->blockList) {
            currentBlock = blockMap[block];
            currentIRBlock = block;
            for (auto& instr : block->instrList) {
                if (std::dynamic_pointer_cast<IRAlloca>(instr)) continue;
                selectInstr(instr);
            }
        }

        // ---- Exit block ----
        auto exitBlock = std::make_shared<ASMBlock>(currentFuncExitLabel);
        currentBlock = exitBlock;
        asmBlocks.push_back(exitBlock);

        // Handle struct/array return: load last param (ptr) into a0
        if (std::dynamic_pointer_cast<IRStructType>(irFunc->retType) ||
            std::dynamic_pointer_cast<IRArrayType>(irFunc->retType)) {
            auto lastParam = irFunc->paramList->paramList.back();
            int vr = materialize(lastParam);
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, 10); // a0
            mv.rs1 = Operand(OperandType::REG, vr);
            currentBlock->instrs.push_back(mv);
        }

        // Epilogue placeholder
        {
            ASMInstr marker;
            marker.op = ASMOp::ADDI;
            marker.rd = Operand(OperandType::REG, 0);
            marker.rs1 = Operand(OperandType::REG, 0);
            marker.imm = Operand(OperandType::IMM, 0);
            marker.funcName = "__EPILOGUE__";
            currentBlock->instrs.push_back(marker);
        }

        // jr ra
        ASMInstr jr;
        jr.op = ASMOp::JR;
        jr.rs1 = Operand(OperandType::REG, 1); // ra
        currentBlock->instrs.push_back(jr);
    }

    // ---- alloca: compute sp-relative address into vreg ----
    void processAlloca(std::shared_ptr<IRAlloca> alloca) {
        int size = alloca->allocatedType->size;
        if (size == 0) size = 4;
        getAllocaSlot(alloca->var, size);
    }

    void emitAllocaAddr(std::shared_ptr<IRAlloca> alloca) {
        int off = allocaStackOffset[alloca->var.get()];
        int vr = getVReg(alloca->var);
        // The actual sp-relative offset will be patched after frame layout.
        // For now we store the alloca-region-relative offset and mark it.
        // We use: addi vr, sp, off  — the 'off' is alloca-region relative.
        // LinearScan will add the spill-area size to adjust.
        if (off >= -2048 && off <= 2047) {
            ASMInstr addi;
            addi.op = ASMOp::ADDI;
            addi.rd = Operand(OperandType::REG, vr);
            addi.rs1 = Operand(OperandType::REG, 2); // sp
            addi.imm = Operand(OperandType::IMM, off);
            addi.funcName = "__ALLOCA__";
            currentBlock->instrs.push_back(addi);
        } else {
            int tmp = freshVReg();
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, tmp);
            li.imm = Operand(OperandType::IMM, off);
            currentBlock->instrs.push_back(li);

            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, vr);
            add.rs1 = Operand(OperandType::REG, 2); // sp
            add.rs2 = Operand(OperandType::REG, tmp);
            add.funcName = "__ALLOCA__";
            currentBlock->instrs.push_back(add);
        }
    }

    // ========== dispatch ==========
    void selectInstr(std::shared_ptr<IRNode> instr) {
        if (auto op = std::dynamic_pointer_cast<IRBinaryop>(instr)) selectBinaryOp(op);
        else if (auto op = std::dynamic_pointer_cast<IRAlloca>(instr)) emitAllocaAddr(op);
        else if (auto op = std::dynamic_pointer_cast<IRLoad>(instr)) selectLoad(op);
        else if (auto op = std::dynamic_pointer_cast<IRStore>(instr)) selectStore(op);
        else if (auto op = std::dynamic_pointer_cast<IRGetptr>(instr)) selectGetptr(op);
        else if (auto op = std::dynamic_pointer_cast<IRBr>(instr)) selectBr(op);
        else if (auto op = std::dynamic_pointer_cast<IRReturn>(instr)) selectReturn(op);
        else if (auto op = std::dynamic_pointer_cast<IRCall>(instr)) selectCall(op);
        else if (auto op = std::dynamic_pointer_cast<IRPrint>(instr)) selectPrint(op);
        else if (auto op = std::dynamic_pointer_cast<IRExit>(instr)) selectExit(op);
        else if (auto op = std::dynamic_pointer_cast<IRGetint>(instr)) selectGetint(op);
        else if (auto op = std::dynamic_pointer_cast<IRMemcpy>(instr)) selectMemcpy(op);
        else if (auto op = std::dynamic_pointer_cast<IRMemset>(instr)) selectMemset(op);
        else if (auto op = std::dynamic_pointer_cast<IRTrunc>(instr)) selectTrunc(op);
        else if (auto op = std::dynamic_pointer_cast<IRZext>(instr)) selectZext(op);
        else if (auto op = std::dynamic_pointer_cast<IRSext>(instr)) selectSext(op);
    }

    // ========== BinaryOp ==========
    void selectBinaryOp(std::shared_ptr<IRBinaryop> op) {
        int lhs = materialize(op->leftValue);
        int rhs = materialize(op->rightValue);
        int dst = getVReg(op->result);

        auto emit = [&](ASMOp asmOp) {
            ASMInstr i;
            i.op = asmOp;
            i.rd = Operand(OperandType::REG, dst);
            i.rs1 = Operand(OperandType::REG, lhs);
            i.rs2 = Operand(OperandType::REG, rhs);
            currentBlock->instrs.push_back(i);
        };

        switch (op->op) {
            case IROp::ADD: emit(ASMOp::ADD); break;
            case IROp::SUB: emit(ASMOp::SUB); break;
            case IROp::MUL: emit(ASMOp::MUL); break;
            case IROp::DIV: emit(op->utag ? ASMOp::DIVU : ASMOp::DIV); break;
            case IROp::MOD: emit(op->utag ? ASMOp::REMU : ASMOp::REM); break;
            case IROp::LT:  emit(ASMOp::SLT); break;
            case IROp::GT: {
                // a > b  ⟺  b < a
                ASMInstr i;
                i.op = ASMOp::SLT;
                i.rd = Operand(OperandType::REG, dst);
                i.rs1 = Operand(OperandType::REG, rhs);
                i.rs2 = Operand(OperandType::REG, lhs);
                currentBlock->instrs.push_back(i);
                break;
            }
            case IROp::LEQ: {
                // a <= b  ⟺  !(b < a)
                ASMInstr slt;
                slt.op = ASMOp::SLT;
                slt.rd = Operand(OperandType::REG, dst);
                slt.rs1 = Operand(OperandType::REG, rhs);
                slt.rs2 = Operand(OperandType::REG, lhs);
                currentBlock->instrs.push_back(slt);
                ASMInstr x;
                x.op = ASMOp::XORI;
                x.rd = Operand(OperandType::REG, dst);
                x.rs1 = Operand(OperandType::REG, dst);
                x.imm = Operand(OperandType::IMM, 1);
                currentBlock->instrs.push_back(x);
                break;
            }
            case IROp::GEQ: {
                // a >= b  ⟺  !(a < b)
                ASMInstr slt;
                slt.op = ASMOp::SLT;
                slt.rd = Operand(OperandType::REG, dst);
                slt.rs1 = Operand(OperandType::REG, lhs);
                slt.rs2 = Operand(OperandType::REG, rhs);
                currentBlock->instrs.push_back(slt);
                ASMInstr x;
                x.op = ASMOp::XORI;
                x.rd = Operand(OperandType::REG, dst);
                x.rs1 = Operand(OperandType::REG, dst);
                x.imm = Operand(OperandType::IMM, 1);
                currentBlock->instrs.push_back(x);
                break;
            }
            case IROp::EQ: {
                ASMInstr sub;
                sub.op = ASMOp::SUB;
                sub.rd = Operand(OperandType::REG, dst);
                sub.rs1 = Operand(OperandType::REG, lhs);
                sub.rs2 = Operand(OperandType::REG, rhs);
                currentBlock->instrs.push_back(sub);
                ASMInstr seqz;
                seqz.op = ASMOp::SEQZ;
                seqz.rd = Operand(OperandType::REG, dst);
                seqz.rs1 = Operand(OperandType::REG, dst);
                currentBlock->instrs.push_back(seqz);
                break;
            }
            case IROp::NEQ: {
                ASMInstr sub;
                sub.op = ASMOp::SUB;
                sub.rd = Operand(OperandType::REG, dst);
                sub.rs1 = Operand(OperandType::REG, lhs);
                sub.rs2 = Operand(OperandType::REG, rhs);
                currentBlock->instrs.push_back(sub);
                ASMInstr snez;
                snez.op = ASMOp::SNEZ;
                snez.rd = Operand(OperandType::REG, dst);
                snez.rs1 = Operand(OperandType::REG, dst);
                currentBlock->instrs.push_back(snez);
                break;
            }
            case IROp::ANDOP: emit(ASMOp::AND); break;
            case IROp::OROP:  emit(ASMOp::OR); break;
            case IROp::XOROP: emit(ASMOp::XOR); break;
            case IROp::LEFTSHIFTOP:  emit(ASMOp::SLL); break;
            case IROp::RIGHTSHIFTOP: emit(ASMOp::SRA); break;
            default: break;
        }
    }

    // ========== Load ==========
    void selectLoad(std::shared_ptr<IRLoad> op) {
        int addr = materialize(op->addressVar);
        int dst = getVReg(op->tmp);
        if (op->type->type == BaseType::PTR) {
            // pointer load = just copy the address
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, addr);
            currentBlock->instrs.push_back(mv);
        } else {
            ASMInstr lw;
            lw.op = ASMOp::LW;
            lw.rd = Operand(OperandType::REG, dst);
            lw.rs1 = Operand(OperandType::REG, addr);
            lw.imm = Operand(OperandType::IMM, 0);
            currentBlock->instrs.push_back(lw);
        }
    }

    // ========== Store ==========
    void selectStore(std::shared_ptr<IRStore> op) {
        if (op->valueType->type == BaseType::PTR) {
            int val = materialize(op->storeValue);
            int dst = getVReg(op->address);
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, val);
            currentBlock->instrs.push_back(mv);
            return;
        }
        int val;
        if (op->storeLiteral)
            val = materialize(op->storeLiteral);
        else
            val = materialize(op->storeValue);
        int addr = materialize(op->address);
        ASMInstr sw;
        sw.op = ASMOp::SW;
        sw.rs2 = Operand(OperandType::REG, val);
        sw.rs1 = Operand(OperandType::REG, addr);
        sw.imm = Operand(OperandType::IMM, 0);
        currentBlock->instrs.push_back(sw);
    }

    // ========== Getptr ==========
    int calculateStructOffset(std::shared_ptr<IRStructType> st, int idx) {
        int off = 0;
        for (int i = 0; i < idx; i++) off += st->memberTypes[i].second->size;
        return off;
    }

    void selectGetptr(std::shared_ptr<IRGetptr> op) {
        int base = materialize(op->base);
        int dst = getVReg(op->res);

        std::shared_ptr<IRType> pointedType = nullptr;
        if (auto pt = std::dynamic_pointer_cast<IRPtrType>(op->base->type))
            pointedType = pt->baseType;
        else
            pointedType = op->base->type;

        if (op->index) {
            int elemSize = 0;
            if (auto arr = std::dynamic_pointer_cast<IRArrayType>(pointedType))
                elemSize = arr->elementType->size;
            else
                elemSize = pointedType->size;

            int idx = materialize(op->index);
            int sz = freshVReg();
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, sz);
            li.imm = Operand(OperandType::IMM, elemSize);
            currentBlock->instrs.push_back(li);

            int prod = freshVReg();
            ASMInstr mul;
            mul.op = ASMOp::MUL;
            mul.rd = Operand(OperandType::REG, prod);
            mul.rs1 = Operand(OperandType::REG, idx);
            mul.rs2 = Operand(OperandType::REG, sz);
            currentBlock->instrs.push_back(mul);

            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, dst);
            add.rs1 = Operand(OperandType::REG, base);
            add.rs2 = Operand(OperandType::REG, prod);
            currentBlock->instrs.push_back(add);
        } else if (op->offset != -1) {
            int off = 0;
            if (auto st = std::dynamic_pointer_cast<IRStructType>(pointedType))
                off = calculateStructOffset(st, op->offset);
            else if (auto arr = std::dynamic_pointer_cast<IRArrayType>(pointedType))
                off = op->offset * arr->elementType->size;
            else
                off = op->offset * pointedType->size;

            if (off == 0) {
                ASMInstr mv;
                mv.op = ASMOp::MV;
                mv.rd = Operand(OperandType::REG, dst);
                mv.rs1 = Operand(OperandType::REG, base);
                currentBlock->instrs.push_back(mv);
            } else if (off >= -2048 && off <= 2047) {
                ASMInstr addi;
                addi.op = ASMOp::ADDI;
                addi.rd = Operand(OperandType::REG, dst);
                addi.rs1 = Operand(OperandType::REG, base);
                addi.imm = Operand(OperandType::IMM, off);
                currentBlock->instrs.push_back(addi);
            } else {
                int tmp = freshVReg();
                ASMInstr li;
                li.op = ASMOp::LI;
                li.rd = Operand(OperandType::REG, tmp);
                li.imm = Operand(OperandType::IMM, off);
                currentBlock->instrs.push_back(li);
                ASMInstr add;
                add.op = ASMOp::ADD;
                add.rd = Operand(OperandType::REG, dst);
                add.rs1 = Operand(OperandType::REG, base);
                add.rs2 = Operand(OperandType::REG, tmp);
                currentBlock->instrs.push_back(add);
            }
        } else {
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, base);
            currentBlock->instrs.push_back(mv);
        }
    }

    // ========== Branch ==========
    void handlePhiCopies(std::shared_ptr<IRBlock> targetBlock) {
        if (!targetBlock) return;
        for (auto& instr : targetBlock->instrList) {
            if (auto* phi = dynamic_cast<IRPhi*>(instr.get())) {
                int dst = getVReg(phi->result);
                if (phi->firstBlock == currentIRBlock) {
                    int immVal = phi->firstState ? 1 : 0;
                    ASMInstr li;
                    li.op = ASMOp::LI;
                    li.rd = Operand(OperandType::REG, dst);
                    li.imm = Operand(OperandType::IMM, immVal);
                    currentBlock->instrs.push_back(li);
                } else if (phi->secondBlock == currentIRBlock) {
                    if (phi->secondState) {
                        int src = materialize(phi->secondState);
                        ASMInstr mv;
                        mv.op = ASMOp::MV;
                        mv.rd = Operand(OperandType::REG, dst);
                        mv.rs1 = Operand(OperandType::REG, src);
                        currentBlock->instrs.push_back(mv);
                    }
                }
            } else if (auto* phi = dynamic_cast<IRPHI*>(instr.get())) {
                int dst = getVReg(phi->result);
                std::shared_ptr<IRValue> srcNode = nullptr;
                if (phi->firstBlock == currentIRBlock) srcNode = phi->firstState;
                else if (phi->secondBlock == currentIRBlock) srcNode = phi->secondState;
                else continue;
                if (srcNode) {
                    int src = materialize(srcNode);
                    ASMInstr mv;
                    mv.op = ASMOp::MV;
                    mv.rd = Operand(OperandType::REG, dst);
                    mv.rs1 = Operand(OperandType::REG, src);
                    currentBlock->instrs.push_back(mv);
                }
            }
        }
    }

    void selectBr(std::shared_ptr<IRBr> op) {
        if (op->condition) {
            // Conditional: emit phi copies for both targets before branching
            // We need a temporary block split to handle phi copies correctly.
            // For simplicity: emit true-path phi copies, then false-path phi copies,
            // then branch. This works because phi dst vregs are only written once.
            handlePhiCopies(op->trueLabel);
            handlePhiCopies(op->falseLabel);

            int cond = materialize(op->condition);
            ASMInstr bnez;
            bnez.op = ASMOp::BNEZ;
            bnez.rs1 = Operand(OperandType::REG, cond);
            bnez.label = Operand(OperandType::LABEL, (int)op->trueLabel->label);
            currentBlock->instrs.push_back(bnez);

            ASMInstr j;
            j.op = ASMOp::J;
            j.label = Operand(OperandType::LABEL, (int)op->falseLabel->label);
            currentBlock->instrs.push_back(j);
        } else {
            handlePhiCopies(op->trueLabel);
            ASMInstr j;
            j.op = ASMOp::J;
            j.label = Operand(OperandType::LABEL, (int)op->trueLabel->label);
            currentBlock->instrs.push_back(j);
        }
    }

    // ========== Return ==========
    void selectReturn(std::shared_ptr<IRReturn> op) {
        int val;
        if (op->returnLiteral)
            val = materialize(op->returnLiteral);
        else
            val = materialize(op->returnValue);
        // mv a0, val
        ASMInstr mv;
        mv.op = ASMOp::MV;
        mv.rd = Operand(OperandType::REG, 10); // a0
        mv.rs1 = Operand(OperandType::REG, val);
        currentBlock->instrs.push_back(mv);
        // j exitLabel
        ASMInstr j;
        j.op = ASMOp::J;
        j.label = Operand(OperandType::LABEL, currenctExitBlock);
        currentBlock->instrs.push_back(j);
    }

    // ========== Call ==========
    void selectCall(std::shared_ptr<IRCall> op) {
        int totalParams = op->pList->paramList.size();
        int regParams = std::min(totalParams, 8);

        // Move first 8 args to a0-a7
        for (int i = 0; i < regParams; i++) {
            int src = materialize(op->pList->paramList[i]);
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, 10 + i); // a0-a7
            mv.rs1 = Operand(OperandType::REG, src);
            currentBlock->instrs.push_back(mv);
        }

        // Stack args (>8)
        // Store at negative offsets BEFORE adjusting sp, so that any
        // spill loads emitted by regalloc still use the correct sp.
        if (totalParams > 8) {
            int stackBytes = (totalParams - 8) * 4;

            for (int i = 8; i < totalParams; i++) {
                int src = materialize(op->pList->paramList[i]);
                ASMInstr sw;
                sw.op = ASMOp::SW;
                sw.rs2 = Operand(OperandType::REG, src);
                sw.rs1 = Operand(OperandType::REG, 2); // sp
                sw.imm = Operand(OperandType::IMM, (i - 8) * 4 - stackBytes);
                currentBlock->instrs.push_back(sw);
            }

            ASMInstr addiSp;
            addiSp.op = ASMOp::ADDI;
            addiSp.rd = Operand(OperandType::REG, 2);
            addiSp.rs1 = Operand(OperandType::REG, 2);
            addiSp.imm = Operand(OperandType::IMM, -stackBytes);
            currentBlock->instrs.push_back(addiSp);
        }

        // call
        ASMInstr call;
        call.op = ASMOp::CALL;
        std::string target = op->function->name;
        if (op->function->parentStructType)
            target = op->function->parentStructType->name + "_" + target;
        call.funcName = target;
        currentBlock->instrs.push_back(call);

        // Cleanup stack args
        if (totalParams > 8) {
            int stackBytes = (totalParams - 8) * 4;
            ASMInstr addiSp;
            addiSp.op = ASMOp::ADDI;
            addiSp.rd = Operand(OperandType::REG, 2);
            addiSp.rs1 = Operand(OperandType::REG, 2);
            addiSp.imm = Operand(OperandType::IMM, stackBytes);
            currentBlock->instrs.push_back(addiSp);
        }

        // Collect return value
        if (op->retVar) {
            int dst = getVReg(op->retVar);
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, 10); // a0
            currentBlock->instrs.push_back(mv);
        }
    }

    // ========== Print ==========
    void selectPrint(std::shared_ptr<IRPrint> op) {
        if (op->printVar) {
            int val = materialize(op->printVar);
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, 10); // a0
            mv.rs1 = Operand(OperandType::REG, val);
            currentBlock->instrs.push_back(mv);

            ASMInstr call;
            call.op = ASMOp::CALL;
            call.funcName = op->inttag ? "printInt" : "printlnInt";
            currentBlock->instrs.push_back(call);
        }
    }

    // ========== Exit ==========
    void selectExit(std::shared_ptr<IRExit> op) {
        if (op->exitCode) {
            int val = materialize(op->exitCode);
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, 10);
            mv.rs1 = Operand(OperandType::REG, val);
            currentBlock->instrs.push_back(mv);
        } else {
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, 10);
            li.imm = Operand(OperandType::IMM, 0);
            currentBlock->instrs.push_back(li);
        }
        ASMInstr call;
        call.op = ASMOp::CALL;
        call.funcName = "__builtin_exit";
        currentBlock->instrs.push_back(call);
    }

    // ========== Getint ==========
    void selectGetint(std::shared_ptr<IRGetint> op) {
        ASMInstr call;
        call.op = ASMOp::CALL;
        call.funcName = "getInt";
        currentBlock->instrs.push_back(call);
        int dst = getVReg(op->result);
        ASMInstr mv;
        mv.op = ASMOp::MV;
        mv.rd = Operand(OperandType::REG, dst);
        mv.rs1 = Operand(OperandType::REG, 10); // a0
        currentBlock->instrs.push_back(mv);
    }

    // ========== Memcpy ==========
    void selectMemcpy(std::shared_ptr<IRMemcpy> op) {
        int dest = materialize(op->dest);
        int src = materialize(op->value);
        ASMInstr mvA0; mvA0.op = ASMOp::MV;
        mvA0.rd = Operand(OperandType::REG, 10);
        mvA0.rs1 = Operand(OperandType::REG, dest);
        currentBlock->instrs.push_back(mvA0);
        ASMInstr mvA1; mvA1.op = ASMOp::MV;
        mvA1.rd = Operand(OperandType::REG, 11);
        mvA1.rs1 = Operand(OperandType::REG, src);
        currentBlock->instrs.push_back(mvA1);
        ASMInstr liA2; liA2.op = ASMOp::LI;
        liA2.rd = Operand(OperandType::REG, 12);
        liA2.imm = Operand(OperandType::IMM, op->size);
        currentBlock->instrs.push_back(liA2);
        ASMInstr call; call.op = ASMOp::CALL;
        call.funcName = "memcpy";
        currentBlock->instrs.push_back(call);
    }

    // ========== Memset ==========
    void selectMemset(std::shared_ptr<IRMemset> op) {
        int dest = materialize(op->dest);
        ASMInstr mvA0; mvA0.op = ASMOp::MV;
        mvA0.rd = Operand(OperandType::REG, 10);
        mvA0.rs1 = Operand(OperandType::REG, dest);
        currentBlock->instrs.push_back(mvA0);
        ASMInstr liA1; liA1.op = ASMOp::LI;
        liA1.rd = Operand(OperandType::REG, 11);
        liA1.imm = Operand(OperandType::IMM, op->value);
        currentBlock->instrs.push_back(liA1);
        ASMInstr liA2; liA2.op = ASMOp::LI;
        liA2.rd = Operand(OperandType::REG, 12);
        liA2.imm = Operand(OperandType::IMM, op->size);
        currentBlock->instrs.push_back(liA2);
        ASMInstr call; call.op = ASMOp::CALL;
        call.funcName = "memset";
        currentBlock->instrs.push_back(call);
    }

    // ========== Trunc/Zext/Sext ==========
    void selectTrunc(std::shared_ptr<IRTrunc> op) {
        int src = materialize(op->value);
        int dst = getVReg(op->result);
        ASMInstr mv; mv.op = ASMOp::MV;
        mv.rd = Operand(OperandType::REG, dst);
        mv.rs1 = Operand(OperandType::REG, src);
        currentBlock->instrs.push_back(mv);
    }
    void selectZext(std::shared_ptr<IRZext> op) {
        int src = materialize(op->value);
        int dst = getVReg(op->result);
        ASMInstr mv; mv.op = ASMOp::MV;
        mv.rd = Operand(OperandType::REG, dst);
        mv.rs1 = Operand(OperandType::REG, src);
        currentBlock->instrs.push_back(mv);
    }
    void selectSext(std::shared_ptr<IRSext> op) {
        int src = materialize(op->value);
        int dst = getVReg(op->result);
        ASMInstr mv; mv.op = ASMOp::MV;
        mv.rd = Operand(OperandType::REG, dst);
        mv.rs1 = Operand(OperandType::REG, src);
        currentBlock->instrs.push_back(mv);
    }
};

} // namespace JaneZ
