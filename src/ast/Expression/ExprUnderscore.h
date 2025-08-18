# pragma once

#include "expression.h"
namespace JaneZ {
class ExprUnderscore : public Expression {
public:
    ExprUnderscore(){}

    ~ExprUnderscore() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}