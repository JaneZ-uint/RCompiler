# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRAlloca : public IRNode {
public:
    IRAlloca() : IRNode() {}
    virtual ~IRAlloca() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}