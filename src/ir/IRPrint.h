# pragma once

#include "IRLiteral.h"
#include "IRNode.h"
#include "IRVar.h"
#include <memory>
namespace JaneZ {
class IRPrint : public IRNode{
public:
    std::shared_ptr<IRVar> printVar;
    std::shared_ptr<IRLiteral> printLiteral;

    IRPrint(std::shared_ptr<IRVar> var):printVar(std::move(var)),printLiteral(nullptr){}
    IRPrint(std::shared_ptr<IRLiteral> literal):printVar(nullptr),printLiteral(std::move(literal)){}
    ~IRPrint() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}