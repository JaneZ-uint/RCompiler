# pragma once
# include "IRNode.h"
#include "IRVar.h"
# include "IRVisitor.h"
# include "IRType.h"
# include <memory>

namespace JaneZ {
class IRGlobal : public IRNode {
public:
    std::shared_ptr<IRType> allocatedType;
    std::shared_ptr<IRVar> var;

    IRGlobal(std::shared_ptr<IRType> at, std::shared_ptr<IRVar> v)
        : allocatedType(std::move(at)), var(std::move(v)) {}
    ~IRGlobal() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}