# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRBlock : public IRNode {
public:
    IRBlock() : IRNode() {}
    virtual ~IRBlock() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}