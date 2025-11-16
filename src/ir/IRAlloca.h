# pragma once
# include "IRNode.h"
# include "IRType.h"
#include "IRVar.h"
# include "IRVisitor.h"
# include <memory>

namespace JaneZ {
class IRAlloca : public IRNode {
public:
    std::shared_ptr<IRType> allocatedType;
    std::shared_ptr<IRVar> var;

    IRAlloca(std::shared_ptr<IRType> at, std::shared_ptr<IRVar> v)
        : allocatedType(std::move(at)), var(std::move(v)) {}
    ~IRAlloca() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}