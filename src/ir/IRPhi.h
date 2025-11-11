# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRPhi : public IRNode {
public:
    IRPhi() : IRNode() {}
    virtual ~IRPhi() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}