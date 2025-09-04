# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprGroup : public Expression {
public:
    std::unique_ptr<Expression> expr;

    ExprGroup(std::unique_ptr<Expression> e)
        : expr(std::move(e)) {}

    ~ExprGroup() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}