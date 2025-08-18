# pragma once

#include "expression.h"
namespace JaneZ {
class ExprContinue : public Expression {
public:
    ExprContinue(){}

    ~ExprContinue() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}