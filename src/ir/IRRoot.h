# pragma once

#include "IRNode.h"
#include <memory>
#include <vector>

namespace JaneZ {
class IRRoot : public IRNode {
public:
    std::vector<std::shared_ptr<IRNode>> children;

    IRRoot() = default;

    ~IRRoot() override = default;   

    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}