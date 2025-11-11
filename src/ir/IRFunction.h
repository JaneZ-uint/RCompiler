# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRFunction : public IRNode {
public:
    IRFunction() : IRNode() {}
    virtual ~IRFunction() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}