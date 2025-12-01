# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
class IRSelf : public IRNode {
public:
    IRSelf(){}

    ~IRSelf() = default;

    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}