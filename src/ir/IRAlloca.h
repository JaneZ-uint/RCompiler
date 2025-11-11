# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRAlloca : public IRNode {
public:
    IRAlloca() : IRNode() {}
    virtual ~IRAlloca() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}