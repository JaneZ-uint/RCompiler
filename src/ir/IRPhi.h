# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRPhi : public IRNode {
public:
    IRPhi() : IRNode() {}
    virtual ~IRPhi() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}