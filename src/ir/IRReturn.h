# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRReturn : public IRNode {
public:
    IRReturn() : IRNode() {}
    virtual ~IRReturn() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}