# pragma once
# include "IRNode.h"
#include "IRVar.h"
# include "IRVisitor.h"
# include "IRType.h"
# include <memory>

namespace JaneZ {
class IRConstant : public IRNode {
public:
    std::shared_ptr<IRType> allocatedType;
    std::shared_ptr<IRVar> var;

    IRConstant(std::shared_ptr<IRType> at, std::shared_ptr<IRVar> v)
        : allocatedType(std::move(at)), var(std::move(v)) {}
    ~IRConstant() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}