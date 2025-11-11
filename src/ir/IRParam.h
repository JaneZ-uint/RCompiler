# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRBinaryop : public IRNode {
public:
    IRBinaryop() : IRNode() {}
    virtual ~IRBinaryop() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}