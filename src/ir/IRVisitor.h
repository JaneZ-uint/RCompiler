# pragma once
# include "../visitor/visitor.h"

namespace JaneZ {
//IR Part
class IRNode;

class IRAlloca;
class IRBinaryop;
class IRBlock;
class IRBranch;
class IRCall;
class IRCondbranch;
class IRFunction;
class IRLoad;
class IRParam;
class IRPhi;
class IRReturn;
class IRStore;

class IRVisitor {
public:
    IRVisitor() = default;
    virtual ~IRVisitor() = default;

    virtual void visit(IRNode &node) = 0;

    virtual void visit(IRAlloca &node) = 0;
    virtual void visit(IRBinaryop &node) = 0;
    virtual void visit(IRBlock &node) = 0;
    virtual void visit(IRBranch &node) = 0;
    virtual void visit(IRCall &node) = 0;
    virtual void visit(IRCondbranch &node) = 0;
    virtual void visit(IRFunction &node) = 0;
    virtual void visit(IRLoad &node) = 0;
    virtual void visit(IRParam &node) = 0;
    virtual void visit(IRPhi &node) = 0;
    virtual void visit(IRReturn &node) = 0;
    virtual void visit(IRStore &node) = 0;
};
}