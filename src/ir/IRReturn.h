# pragma once
# include "IRNode.h"
#include "IRType.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRReturn : public IRNode {
public:
    std::shared_ptr<IRType> returnType;
    std::shared_ptr<IRVar> returnValue;

    IRReturn(std::shared_ptr<IRType> type, std::shared_ptr<IRVar> value)
        : returnType(type), returnValue(value) {}
    ~IRReturn() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}