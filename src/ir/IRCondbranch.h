# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRCondbranch : public IRNode {
public:
    IRCondbranch() : IRNode() {}
    virtual ~IRCondbranch() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}