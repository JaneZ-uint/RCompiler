# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprGroup : public Expression {
public:
    std::shared_ptr<Expression> expr;

    ExprGroup(std::shared_ptr<Expression> e)
        : expr(std::move(e)) {}

    ~ExprGroup() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}