# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRCall : public IRNode {
public:
    IRCall() : IRNode() {}
    virtual ~IRCall() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}