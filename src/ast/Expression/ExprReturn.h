# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprReturn : public Expression {
private:
    std::unique_ptr<Expression> expr;

public:
    ExprReturn(std::unique_ptr<Expression> expression)
        : expr(std::move(expression)) {}

    ~ExprReturn() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}