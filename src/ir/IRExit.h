# pragma once

#include "IRNode.h"
#include "IRVisitor.h"
namespace JaneZ {
class IRExit: public IRNode {
public:
    std::shared_ptr<IRValue> exitCode;
    IRExit() = default;
    IRExit(std::shared_ptr<IRValue> ec) : exitCode(ec) {}
    ~IRExit() = default;

    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}