# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRBranch : public IRNode {
public:
    IRBranch() : IRNode() {}
    virtual ~IRBranch() = default;
    void accept(IRVisitor &visitor) override { 
        visitor.visit(*this);   
    }
};

}