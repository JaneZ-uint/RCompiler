# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprBreak : public Expression {
private:
    std::unique_ptr<Expression> expr;

public:
    ExprBreak(std::unique_ptr<Expression> e) : expr(std::move(e)) {}

    ~ExprBreak() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}