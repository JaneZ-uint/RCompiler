# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRCall : public IRNode {
public:
    IRCall() : IRNode() {}
    virtual ~IRCall() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}