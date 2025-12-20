# pragma once

#include "IRNode.h"
#include "IRVar.h"
#include <memory>
namespace JaneZ {
class IRGetint : public IRNode {
public:
    std::shared_ptr<IRVar> result;

    IRGetint() = default;
    IRGetint(std::shared_ptr<IRVar> result) : result(std::move(result)) {}
    ~IRGetint() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}