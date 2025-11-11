# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRStore : public IRNode {
public:
    IRStore() : IRNode() {}
    virtual ~IRStore() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}