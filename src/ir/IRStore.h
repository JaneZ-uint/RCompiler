# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRStore : public IRNode {
public:
    IRStore() : IRNode() {}
    virtual ~IRStore() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}