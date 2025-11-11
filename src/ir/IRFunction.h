# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRFunction : public IRNode {
public:
    IRFunction() : IRNode() {}
    virtual ~IRFunction() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}