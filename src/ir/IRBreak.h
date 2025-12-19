# pragma once

#include "IRNode.h"
namespace JaneZ {
class IRBreak : public IRNode{
public:
    IRBreak() = default;
    ~IRBreak() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}