# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRCondbranch : public IRNode {
public:
    IRCondbranch() : IRNode() {}
    virtual ~IRCondbranch() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}