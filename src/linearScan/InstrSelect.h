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

    int allocaOffset = 0; 
    std::unordered_map<IRNode*, int> allocaStackOffset;

    int getAllocaSlot(std::shared_ptr<IRNode> var, int size) {
        IRNode* key = var.get();
        auto it = allocaStackOffset.find(key);
        if (it != allocaStackOffset.end()) return it->second;
        int aligned = (size + RISCV_XLEN_BYTES - 1) / RISCV_XLEN_BYTES * RISCV_XLEN_BYTES;
        int off = allocaOffset;
        allocaOffset += aligned;
        allocaStackOffset[key] = off;
        return off;
    }

    int totalAllocaSize = 0;

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

    int materializeAs(std::shared_ptr<IRNode> val, std::shared_ptr<IRType> expectedType) {
        if (auto* lit = dynamic_cast<IRLiteral*>(val.get())) {
            long long imm = lit->intValue;
            if (auto intType = std::dynamic_pointer_cast<IRIntType>(expectedType)) {
                if (intType->bitWidth == 32) {
                    imm = normalize32Immediate(imm, intType->isUnsigned);
                }
            }
            int vr = freshVReg();
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, vr);
            li.imm = Operand(OperandType::IMM, imm);
            currentBlock->instrs.push_back(li);
            return vr;
        }
        int vr = materialize(val);
        if (auto intType = std::dynamic_pointer_cast<IRIntType>(expectedType)) {
            if (intType->isUnsigned && intType->bitWidth == 32) {
                int dst = freshVReg();
                ASMInstr mv;
                mv.op = ASMOp::MV;
                mv.rd = Operand(OperandType::REG, dst);
                mv.rs1 = Operand(OperandType::REG, vr);
                currentBlock->instrs.push_back(mv);
                emitZeroExtend32(dst);
                vr = dst;
            } else if (intType->bitWidth == 64) {
                if (auto var = std::dynamic_pointer_cast<IRVar>(val)) {
                    if (auto srcType = std::dynamic_pointer_cast<IRIntType>(var->type)) {
                        if (srcType->bitWidth == 32) {
                            int dst = freshVReg();
                            ASMInstr mv;
                            mv.op = ASMOp::MV;
                            mv.rd = Operand(OperandType::REG, dst);
                            mv.rs1 = Operand(OperandType::REG, vr);
                            currentBlock->instrs.push_back(mv);
                            if (srcType->isUnsigned) {
                                emitZeroExtend32(dst);
                            } else {
                                emitSignExtend32(dst);
                            }
                            vr = dst;
                        }
                    }
                }
            }
        }
        return vr;
    }

    long long normalize32Immediate(long long value, bool isUnsigned) {
        long long low = static_cast<long long>(static_cast<unsigned long long>(value) & 0xffffffffULL);
        if (!isUnsigned && (low & 0x80000000LL)) {
            low -= 0x100000000LL;
        }
        return low;
    }

    std::string asmFunctionName(const std::shared_ptr<IRFunction>& func) {
        std::string name = func->name;
        if (func->parentStructType) {
            name = func->parentStructType->name + "_" + name;
        }
        if (name == "main") return name;
        return "__rcompiler_user_" + name;
    }

    void emitAdjustSp(long long int bytes) {
        if (bytes >= -2048 && bytes <= 2047) {
            ASMInstr addi;
            addi.op = ASMOp::ADDI;
            addi.rd = Operand(OperandType::REG, 2);
            addi.rs1 = Operand(OperandType::REG, 2);
            addi.imm = Operand(OperandType::IMM, bytes);
            currentBlock->instrs.push_back(addi);
        } else {
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, 31);
            li.imm = Operand(OperandType::IMM, bytes);
            currentBlock->instrs.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, 2);
            add.rs1 = Operand(OperandType::REG, 2);
            add.rs2 = Operand(OperandType::REG, 31);
            currentBlock->instrs.push_back(add);
        }
    }

    int materializeSpOffset(long long int offset) {
        int dst = freshVReg();
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr addi;
            addi.op = ASMOp::ADDI;
            addi.rd = Operand(OperandType::REG, dst);
            addi.rs1 = Operand(OperandType::REG, 2);
            addi.imm = Operand(OperandType::IMM, offset);
            currentBlock->instrs.push_back(addi);
        } else {
            int tmp = freshVReg();
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, tmp);
            li.imm = Operand(OperandType::IMM, offset);
            currentBlock->instrs.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, dst);
            add.rs1 = Operand(OperandType::REG, 2);
            add.rs2 = Operand(OperandType::REG, tmp);
            currentBlock->instrs.push_back(add);
        }
        return dst;
    }

    void emitStackStore(int src, int baseReg, long long int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr sd;
            sd.op = ASMOp::SD;
            sd.rs2 = Operand(OperandType::REG, src);
            sd.rs1 = Operand(OperandType::REG, baseReg);
            sd.imm = Operand(OperandType::IMM, offset);
            currentBlock->instrs.push_back(sd);
        } else {
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, 31);
            li.imm = Operand(OperandType::IMM, offset);
            currentBlock->instrs.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, 31);
            add.rs1 = Operand(OperandType::REG, baseReg);
            add.rs2 = Operand(OperandType::REG, 31);
            currentBlock->instrs.push_back(add);
            ASMInstr sd;
            sd.op = ASMOp::SD;
            sd.rs2 = Operand(OperandType::REG, src);
            sd.rs1 = Operand(OperandType::REG, 31);
            sd.imm = Operand(OperandType::IMM, 0);
            currentBlock->instrs.push_back(sd);
        }
    }

    void emitStackLoad(int dst, int baseReg, long long int offset) {
        if (offset >= -2048 && offset <= 2047) {
            ASMInstr ld;
            ld.op = ASMOp::LD;
            ld.rd = Operand(OperandType::REG, dst);
            ld.rs1 = Operand(OperandType::REG, baseReg);
            ld.imm = Operand(OperandType::IMM, offset);
            currentBlock->instrs.push_back(ld);
        } else {
            ASMInstr li;
            li.op = ASMOp::LI;
            li.rd = Operand(OperandType::REG, 31);
            li.imm = Operand(OperandType::IMM, offset);
            currentBlock->instrs.push_back(li);
            ASMInstr add;
            add.op = ASMOp::ADD;
            add.rd = Operand(OperandType::REG, 31);
            add.rs1 = Operand(OperandType::REG, baseReg);
            add.rs2 = Operand(OperandType::REG, 31);
            currentBlock->instrs.push_back(add);
            ASMInstr ld;
            ld.op = ASMOp::LD;
            ld.rd = Operand(OperandType::REG, dst);
            ld.rs1 = Operand(OperandType::REG, 31);
            ld.imm = Operand(OperandType::IMM, 0);
            currentBlock->instrs.push_back(ld);
        }
    }

    void emitZeroExtend32(int reg) {
        ASMInstr sl;
        sl.op = ASMOp::SLLI;
        sl.rd = Operand(OperandType::REG, reg);
        sl.rs1 = Operand(OperandType::REG, reg);
        sl.imm = Operand(OperandType::IMM, 32);
        currentBlock->instrs.push_back(sl);

        ASMInstr sr;
        sr.op = ASMOp::SRLI;
        sr.rd = Operand(OperandType::REG, reg);
        sr.rs1 = Operand(OperandType::REG, reg);
        sr.imm = Operand(OperandType::IMM, 32);
        currentBlock->instrs.push_back(sr);
    }

    void emitSignExtend32(int reg) {
        ASMInstr sl;
        sl.op = ASMOp::SLLI;
        sl.rd = Operand(OperandType::REG, reg);
        sl.rs1 = Operand(OperandType::REG, reg);
        sl.imm = Operand(OperandType::IMM, 32);
        currentBlock->instrs.push_back(sl);

        ASMInstr sr;
        sr.op = ASMOp::SRAI;
        sr.rd = Operand(OperandType::REG, reg);
        sr.rs1 = Operand(OperandType::REG, reg);
        sr.imm = Operand(OperandType::IMM, 32);
        currentBlock->instrs.push_back(sr);
    }

    void emitNormalizeTo32(int reg, std::shared_ptr<IRType> targetType) {
        bool isUnsigned = false;
        if (auto intType = std::dynamic_pointer_cast<IRIntType>(targetType)) {
            isUnsigned = intType->isUnsigned;
        }
        if (isUnsigned) {
            emitZeroExtend32(reg);
        } else {
            emitSignExtend32(reg);
        }
    }

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

    void selectFunc(std::shared_ptr<IRFunction> irFunc) {
        blockMap.clear();
        nextVReg = 32;
        valueToVReg.clear();
        allocaOffset = 0;
        allocaStackOffset.clear();

        for (auto& nested : irFunc->funcList) {
            selectFunc(nested);
        }

        int myExitBlockID = exitblock++;
        currenctExitBlock = myExitBlockID;
        currentFuncExitLabel = ".Lexit" + std::to_string(currenctExitBlock);

        std::string funcName = asmFunctionName(irFunc);

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

        {
            ASMInstr marker;
            marker.op = ASMOp::ADDI;
            marker.rd = Operand(OperandType::REG, 0);
            marker.rs1 = Operand(OperandType::REG, 0);
            marker.imm = Operand(OperandType::IMM, 0);
            marker.funcName = "__PROLOGUE__";
            currentBlock->instrs.push_back(marker);
        }

        long long int argCount = static_cast<long long int>(irFunc->paramList->paramList.size());
        for (long long int i = 0; i < argCount; i++) {
            auto paramIndex = static_cast<size_t>(i);
            int vr = getVReg(irFunc->paramList->paramList[paramIndex]);
            if (i < 8) {
                ASMInstr mv;
                mv.op = ASMOp::MV;
                mv.rd = Operand(OperandType::REG, vr);
                mv.rs1 = Operand(OperandType::REG, 10 + i); // a0-a7
                currentBlock->instrs.push_back(mv);
            } else {
                long long int stackParamOffset = (i - 8) * RISCV_XLEN_BYTES;
                emitStackLoad(vr, 8, stackParamOffset);
            }
        }

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

        for (auto& instr : entryBlock->instrs) {
            if (instr.funcName == "__PROLOGUE__") {
                instr.imm = Operand(OperandType::IMM, totalAllocaSize);
                break;
            }
        }

        for (auto& instr : irFunc->body->instrList) {
            if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                emitAllocaAddr(alloca);
            }
        }
        for (auto& block : irFunc->body->blockList) {
            for (auto& instr : block->instrList) {
                if (auto alloca = std::dynamic_pointer_cast<IRAlloca>(instr)) {
                    auto savedBlock = currentBlock;
                    currentBlock = blockMap[irFunc->body];
                    emitAllocaAddr(alloca);
                    currentBlock = savedBlock;
                }
            }
        }

        for (auto& instr : irFunc->body->instrList) {
            if (std::dynamic_pointer_cast<IRAlloca>(instr)) continue;
            selectInstr(instr);
        }

        for (auto& block : irFunc->body->blockList) {
            currentBlock = blockMap[block];
            currentIRBlock = block;
            for (auto& instr : block->instrList) {
                if (std::dynamic_pointer_cast<IRAlloca>(instr)) continue;
                selectInstr(instr);
            }
        }

        auto exitBlock = std::make_shared<ASMBlock>(currentFuncExitLabel);
        currentBlock = exitBlock;
        asmBlocks.push_back(exitBlock);

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

        {
            ASMInstr marker;
            marker.op = ASMOp::ADDI;
            marker.rd = Operand(OperandType::REG, 0);
            marker.rs1 = Operand(OperandType::REG, 0);
            marker.imm = Operand(OperandType::IMM, 0);
            marker.funcName = "__EPILOGUE__";
            currentBlock->instrs.push_back(marker);
        }

        ASMInstr jr;
        jr.op = ASMOp::JR;
        jr.rs1 = Operand(OperandType::REG, 1); // ra
        currentBlock->instrs.push_back(jr);
    }

    void processAlloca(std::shared_ptr<IRAlloca> alloca) {
        int size = alloca->allocatedType->size;
        if (size == 0) size = 4;
        if (alloca->w64tag) size = 8;
        getAllocaSlot(alloca->var, size);
    }

    void emitAllocaAddr(std::shared_ptr<IRAlloca> alloca) {
        int off = allocaStackOffset[alloca->var.get()];
        int vr = getVReg(alloca->var);
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

    void selectBinaryOp(std::shared_ptr<IRBinaryop> op) {
        int lhs = materialize(op->leftValue);
        int rhs = materialize(op->rightValue);
        int dst = getVReg(op->result);
        bool zextU32Result = op->utag && !op->w64tag &&
                             op->result && op->result->type &&
                             op->result->type->type == BaseType::INT &&
                             std::dynamic_pointer_cast<IRIntType>(op->result->type) &&
                             std::dynamic_pointer_cast<IRIntType>(op->result->type)->bitWidth == 32 &&
                             std::dynamic_pointer_cast<IRIntType>(op->result->type)->isUnsigned;

        auto emit = [&](ASMOp asmOp) {
            ASMInstr i;
            i.op = asmOp;
            i.rd = Operand(OperandType::REG, dst);
            i.rs1 = Operand(OperandType::REG, lhs);
            i.rs2 = Operand(OperandType::REG, rhs);
            currentBlock->instrs.push_back(i);
        };

        switch (op->op) {
            case IROp::ADD:
                emit(op->w64tag ? ASMOp::ADD : ASMOp::ADDW);
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::SUB:
                emit(op->w64tag ? ASMOp::SUB : ASMOp::SUBW);
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::MUL:
                emit(op->w64tag ? ASMOp::MUL : ASMOp::MULW);
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::DIV:
                emit(op->w64tag ? (op->utag ? ASMOp::DIVU : ASMOp::DIV) : (op->utag ? ASMOp::DIVUW : ASMOp::DIVW));
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::MOD:
                emit(op->w64tag ? (op->utag ? ASMOp::REMU : ASMOp::REM) : (op->utag ? ASMOp::REMUW : ASMOp::REMW));
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::LT:  emit(op->utag ? ASMOp::SLTU : ASMOp::SLT); break;
            case IROp::GT: {
                ASMInstr i;
                i.op = op->utag ? ASMOp::SLTU : ASMOp::SLT;
                i.rd = Operand(OperandType::REG, dst);
                i.rs1 = Operand(OperandType::REG, rhs);
                i.rs2 = Operand(OperandType::REG, lhs);
                currentBlock->instrs.push_back(i);
                break;
            }
            case IROp::LEQ: {
                // a <= b  ⟺  !(b < a)
                ASMInstr slt;
                slt.op = op->utag ? ASMOp::SLTU : ASMOp::SLT;
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
                slt.op = op->utag ? ASMOp::SLTU : ASMOp::SLT;
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
            case IROp::ANDOP:
                emit(ASMOp::AND);
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::OROP:
                emit(ASMOp::OR);
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::XOROP:
                emit(ASMOp::XOR);
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::LEFTSHIFTOP:
                emit(op->w64tag ? ASMOp::SLL : ASMOp::SLLW);
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            case IROp::RIGHTSHIFTOP:
                emit(op->w64tag ? (op->utag ? ASMOp::SRL : ASMOp::SRA) : (op->utag ? ASMOp::SRLW : ASMOp::SRAW));
                if (zextU32Result) emitZeroExtend32(dst);
                break;
            default: break;
        }
    }

    void selectLoad(std::shared_ptr<IRLoad> op) {
        int addr = materialize(op->addressVar);
        int dst = getVReg(op->tmp);
        if (op->type->type == BaseType::PTR) {
            if (op->addressVar && op->addressVar->isPtrStorage) {
                ASMInstr ld;
                ld.op = ASMOp::LD;
                ld.rd = Operand(OperandType::REG, dst);
                ld.rs1 = Operand(OperandType::REG, addr);
                ld.imm = Operand(OperandType::IMM, 0);
                currentBlock->instrs.push_back(ld);
            } else {
                ASMInstr mv;
                mv.op = ASMOp::MV;
                mv.rd = Operand(OperandType::REG, dst);
                mv.rs1 = Operand(OperandType::REG, addr);
                currentBlock->instrs.push_back(mv);
            }
        } else {
            bool wide = false;
            if (auto it = std::dynamic_pointer_cast<IRIntType>(op->type)) {
                wide = (it->bitWidth == 64);
                if (it->bitWidth == 32 && it->isUnsigned) op->utag = true;
            }
            if (op->w64tag) wide = true;
            ASMInstr lw;
            lw.op = wide ? ASMOp::LD : (op->utag ? ASMOp::LWU : ASMOp::LW);
            lw.rd = Operand(OperandType::REG, dst);
            lw.rs1 = Operand(OperandType::REG, addr);
            lw.imm = Operand(OperandType::IMM, 0);
            currentBlock->instrs.push_back(lw);
        }
    }

    void selectStore(std::shared_ptr<IRStore> op) {
        if (op->valueType->type == BaseType::PTR) {
            int val = materialize(op->storeValue);
            if (op->address && op->address->isPtrStorage) {
                int addr = materialize(op->address);
                ASMInstr sd;
                sd.op = ASMOp::SD;
                sd.rs2 = Operand(OperandType::REG, val);
                sd.rs1 = Operand(OperandType::REG, addr);
                sd.imm = Operand(OperandType::IMM, 0);
                currentBlock->instrs.push_back(sd);
            } else {
                int dst = getVReg(op->address);
                ASMInstr mv;
                mv.op = ASMOp::MV;
                mv.rd = Operand(OperandType::REG, dst);
                mv.rs1 = Operand(OperandType::REG, val);
                currentBlock->instrs.push_back(mv);
            }
            return;
        }
        int val;
        if (op->storeLiteral)
            val = materialize(op->storeLiteral);
        else
            val = materialize(op->storeValue);
        int addr = materialize(op->address);
        bool wide = false;
        if (auto it = std::dynamic_pointer_cast<IRIntType>(op->valueType)) {
            wide = (it->bitWidth == 64);
        }
        if (op->w64tag) wide = true;
        ASMInstr sw;
        sw.op = wide ? ASMOp::SD : ASMOp::SW;
        sw.rs2 = Operand(OperandType::REG, val);
        sw.rs1 = Operand(OperandType::REG, addr);
        sw.imm = Operand(OperandType::IMM, 0);
        currentBlock->instrs.push_back(sw);
    }

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

    void handlePhiCopies(std::shared_ptr<IRBlock> targetBlock) {
        if (!targetBlock) return;
        std::vector<std::pair<int, int>> copies;
        for (auto& instr : targetBlock->instrList) {
            if (auto* phi = dynamic_cast<IRPhi*>(instr.get())) {
                int dst = getVReg(phi->result);
                if (phi->firstBlock == currentIRBlock) {
                    int immVal = phi->firstState ? 1 : 0;
                    int tmp = freshVReg();
                    ASMInstr li;
                    li.op = ASMOp::LI;
                    li.rd = Operand(OperandType::REG, tmp);
                    li.imm = Operand(OperandType::IMM, immVal);
                    currentBlock->instrs.push_back(li);
                    copies.push_back({dst, tmp});
                } else if (phi->secondBlock == currentIRBlock) {
                    if (phi->secondState) {
                        int src = materialize(phi->secondState);
                        int tmp = freshVReg();
                        ASMInstr mv;
                        mv.op = ASMOp::MV;
                        mv.rd = Operand(OperandType::REG, tmp);
                        mv.rs1 = Operand(OperandType::REG, src);
                        currentBlock->instrs.push_back(mv);
                        copies.push_back({dst, tmp});
                    }
                }
            } else if (auto* phi = dynamic_cast<IRPHI*>(instr.get())) {
                int dst = getVReg(phi->result);
                std::shared_ptr<IRValue> srcNode = nullptr;
                if (phi->firstBlock && phi->firstBlock == currentIRBlock) srcNode = phi->firstState;
                else if (phi->secondBlock && phi->secondBlock == currentIRBlock) srcNode = phi->secondState;
                else {
                    for (auto& entry : phi->entries) {
                        if (entry.second == currentIRBlock) { srcNode = entry.first; break; }
                    }
                }
                if (!srcNode) continue;
                int src = materialize(srcNode);
                int tmp = freshVReg();
                ASMInstr mv;
                mv.op = ASMOp::MV;
                mv.rd = Operand(OperandType::REG, tmp);
                mv.rs1 = Operand(OperandType::REG, src);
                currentBlock->instrs.push_back(mv);
                copies.push_back({dst, tmp});
            }
        }
        for (auto& [dst, tmp] : copies) {
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, tmp);
            currentBlock->instrs.push_back(mv);
        }
    }

    void selectBr(std::shared_ptr<IRBr> op) {
        if (op->condition) {
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

    void selectReturn(std::shared_ptr<IRReturn> op) {
        if (op->returnType && op->returnType->type == BaseType::VOID) {
            ASMInstr j;
            j.op = ASMOp::J;
            j.label = Operand(OperandType::EXIT_LABEL, currenctExitBlock);
            currentBlock->instrs.push_back(j);
            return;
        }

        int val;
        if (op->returnLiteral)
            val = materializeAs(op->returnLiteral, op->returnType);
        else
            val = materializeAs(op->returnValue, op->returnType);
        if (!op->returnLiteral) {
            if (auto intType = std::dynamic_pointer_cast<IRIntType>(op->returnType)) {
                if (intType->isUnsigned && intType->bitWidth == 32) {
                    emitZeroExtend32(val);
                }
            }
        }
        // mv a0, val
        ASMInstr mv;
        mv.op = ASMOp::MV;
        mv.rd = Operand(OperandType::REG, 10); // a0
        mv.rs1 = Operand(OperandType::REG, val);
        currentBlock->instrs.push_back(mv);
        // j exitLabel
        ASMInstr j;
        j.op = ASMOp::J;
        j.label = Operand(OperandType::EXIT_LABEL, currenctExitBlock);
        currentBlock->instrs.push_back(j);
    }

    void selectCall(std::shared_ptr<IRCall> op) {
        long long int totalParams = static_cast<long long int>(op->pList->paramList.size());
        int regParams = static_cast<int>(std::min<long long int>(totalParams, 8));

        // Stack args (>8). Keep sp stable while materializing arguments so
        // spill reloads/stores inserted by register allocation still address
        // this function's frame correctly.
        long long int stackBytes = 0;
        if (totalParams > 8) {
            long long int rawStackBytes = (totalParams - 8) * RISCV_XLEN_BYTES;
            stackBytes = (rawStackBytes + 15) / 16 * 16;
            int outgoingBase = materializeSpOffset(-stackBytes);

            for (long long int i = 8; i < totalParams; i++) {
                auto paramIndex = static_cast<size_t>(i);
                auto expectedType = (op->function && paramIndex < op->function->typeList.size())
                    ? op->function->typeList[paramIndex]
                    : nullptr;
                int src = materializeAs(op->pList->paramList[paramIndex], expectedType);
                emitStackStore(src, outgoingBase, (i - 8) * RISCV_XLEN_BYTES);
            }
        }

        // Stage register args first. Later materialization can allocate or
        // clobber a0-a7, so only move into ABI registers after all sources are ready.
        std::vector<int> regArgSources;
        regArgSources.reserve(regParams);
        for (int i = 0; i < regParams; i++) {
            auto expectedType = (op->function && i < (int)op->function->typeList.size())
                ? op->function->typeList[i]
                : nullptr;
            regArgSources.push_back(materializeAs(op->pList->paramList[i], expectedType));
        }
        for (int i = 0; i < regParams; i++) {
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, 10 + i); // a0-a7
            mv.rs1 = Operand(OperandType::REG, regArgSources[i]);
            currentBlock->instrs.push_back(mv);
        }

        if (totalParams > 8) {
            emitAdjustSp(-stackBytes);
        }

        ASMInstr call;
        call.op = ASMOp::CALL;
        call.funcName = asmFunctionName(op->function);
        currentBlock->instrs.push_back(call);

        if (totalParams > 8) {
            emitAdjustSp(stackBytes);
        }

        if (op->retVar) {
            if (op->retVar->type &&
                (op->retVar->type->type == BaseType::STRUCT || op->retVar->type->type == BaseType::ARRAY)) {
                return;
            }
            int dst = getVReg(op->retVar);
            ASMInstr mv;
            mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, 10); // a0
            currentBlock->instrs.push_back(mv);
            if (op->retVar->type && op->retVar->type->type == BaseType::INT) {
                auto intType = std::dynamic_pointer_cast<IRIntType>(op->retVar->type);
                if (intType && intType->bitWidth == 32 && intType->isUnsigned) {
                    emitZeroExtend32(dst);
                }
            }
        }
    }

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

    void selectTrunc(std::shared_ptr<IRTrunc> op) {
        int src = materialize(op->value);
        int dst = getVReg(op->result);
        ASMInstr mv; mv.op = ASMOp::MV;
        mv.rd = Operand(OperandType::REG, dst);
        mv.rs1 = Operand(OperandType::REG, src);
        currentBlock->instrs.push_back(mv);
        if (op->targetType && op->targetType->type == BaseType::INT) {
            if (auto intType = std::dynamic_pointer_cast<IRIntType>(op->targetType)) {
                if (intType->bitWidth == 32) {
                    emitNormalizeTo32(dst, op->targetType);
                }
            }
        }
    }
    void selectZext(std::shared_ptr<IRZext> op) {
        int src = materialize(op->value);
        int dst = getVReg(op->result);
        // 32-bit -> 64-bit zero extension: slli + srli by 32.
        // Use the destination as scratch.
        bool from32 = (op->originalType && op->originalType->size <= 4);
        bool to64 = (op->targetType && op->targetType->size == 8);
        if(from32 && to64){
            ASMInstr sl; sl.op = ASMOp::SLLI;
            sl.rd = Operand(OperandType::REG, dst);
            sl.rs1 = Operand(OperandType::REG, src);
            sl.imm = Operand(OperandType::IMM, 32);
            currentBlock->instrs.push_back(sl);
            ASMInstr sr; sr.op = ASMOp::SRLI;
            sr.rd = Operand(OperandType::REG, dst);
            sr.rs1 = Operand(OperandType::REG, dst);
            sr.imm = Operand(OperandType::IMM, 32);
            currentBlock->instrs.push_back(sr);
        }else{
            ASMInstr mv; mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, src);
            currentBlock->instrs.push_back(mv);
            if (op->targetType && op->targetType->type == BaseType::INT) {
                if (auto intType = std::dynamic_pointer_cast<IRIntType>(op->targetType)) {
                    if (intType->bitWidth == 32) {
                        emitNormalizeTo32(dst, op->targetType);
                    }
                }
            }
        }
    }
    void selectSext(std::shared_ptr<IRSext> op) {
        int src = materialize(op->value);
        int dst = getVReg(op->result);
        // 32-bit -> 64-bit sign extension: slli 32 then srai 32.
        bool from32 = (op->originalType && op->originalType->size <= 4);
        bool to64 = (op->targetType && op->targetType->size == 8);
        if(from32 && to64){
            ASMInstr sl; sl.op = ASMOp::SLLI;
            sl.rd = Operand(OperandType::REG, dst);
            sl.rs1 = Operand(OperandType::REG, src);
            sl.imm = Operand(OperandType::IMM, 32);
            currentBlock->instrs.push_back(sl);
            ASMInstr sr; sr.op = ASMOp::SRAI;
            sr.rd = Operand(OperandType::REG, dst);
            sr.rs1 = Operand(OperandType::REG, dst);
            sr.imm = Operand(OperandType::IMM, 32);
            currentBlock->instrs.push_back(sr);
        }else{
            ASMInstr mv; mv.op = ASMOp::MV;
            mv.rd = Operand(OperandType::REG, dst);
            mv.rs1 = Operand(OperandType::REG, src);
            currentBlock->instrs.push_back(mv);
            if (op->targetType && op->targetType->type == BaseType::INT) {
                if (auto intType = std::dynamic_pointer_cast<IRIntType>(op->targetType)) {
                    if (intType->bitWidth == 32) {
                        emitNormalizeTo32(dst, op->targetType);
                    }
                }
            }
        }
    }
};

} // namespace JaneZ
