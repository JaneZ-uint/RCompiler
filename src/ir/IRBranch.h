# pragma once
# include "IRNode.h"
# include "../ast/astvisitor.h"

namespace JaneZ {
class IRBranch : public IRNode {
public:
    IRBranch() : IRNode() {}
    virtual ~IRBranch() = default;
    void accept(ASTVisitor &visitor) override { 
        visitor.visit(*this);   
    }
};

}