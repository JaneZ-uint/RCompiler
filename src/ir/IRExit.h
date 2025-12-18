# pragma once

#include "IRNode.h"
#include "IRVisitor.h"
namespace JaneZ {
class IRExit: public IRNode {
public:
    IRExit() = default;

    ~IRExit() = default;

    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}