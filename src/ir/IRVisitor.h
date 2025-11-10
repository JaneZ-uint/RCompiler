# pragma once

namespace JaneZ {
class IRNode;
class IRBlock;

class IRVisitor {
public:
    IRVisitor() = default;
    virtual ~IRVisitor() = default;
    virtual void visit(IRNode &node) = 0;
    virtual void visit(IRBlock &node) = 0;
};

}   