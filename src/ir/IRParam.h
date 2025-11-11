# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRBinaryop : public IRNode {
public:
    IRBinaryop() : IRNode() {}
    virtual ~IRBinaryop() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}