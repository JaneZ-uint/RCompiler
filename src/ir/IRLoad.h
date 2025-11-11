# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRLoad : public IRNode {
public:
    IRLoad() : IRNode() {}
    virtual ~IRLoad() = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}