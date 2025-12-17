# pragma once
#include "IRLiteral.h"
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
    std::shared_ptr<IRLiteral> returnLiteral;

    IRReturn() = default;
    IRReturn(std::shared_ptr<IRType> type, std::shared_ptr<IRVar> value)
        : returnType(type), returnValue(value) {}
    IRReturn(std::shared_ptr<IRType> type, std::shared_ptr<IRLiteral> literal)
        : returnType(type), returnLiteral(literal) {}
    ~IRReturn() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}