# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprGroup : public Expression {
private:
    std::unique_ptr<Expression> expr;

public:
    ExprGroup(std::unique_ptr<Expression> e)
        : expr(std::move(e)) {}

    ~ExprGroup() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}