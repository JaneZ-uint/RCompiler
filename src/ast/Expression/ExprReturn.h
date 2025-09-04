# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprReturn : public Expression {
public:
    std::unique_ptr<Expression> expr;

    ExprReturn(std::unique_ptr<Expression> expression)
        : expr(std::move(expression)) {}

    ~ExprReturn() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}