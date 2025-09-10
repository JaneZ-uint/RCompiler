# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprBreak : public Expression {
public:
    std::shared_ptr<Expression> expr;

    ExprBreak(std::shared_ptr<Expression> e) : expr(std::move(e)) {}

    ~ExprBreak() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}