# pragma once

#include "IRLiteral.h"
#include "IRNode.h"
#include "IRVar.h"
#include "IRValue.h"
#include <memory>
namespace JaneZ {
class IRPrint : public IRNode{
public:
    std::shared_ptr<IRValue> printVar;

    IRPrint() = default;
    IRPrint(std::shared_ptr<IRValue> printVar) : printVar(printVar) {}
    ~IRPrint() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}