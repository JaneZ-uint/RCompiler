# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRReturn : public IRNode {
public:
    IRReturn() : IRNode() {}
    virtual ~IRReturn() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}