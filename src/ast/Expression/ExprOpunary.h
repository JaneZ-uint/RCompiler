# pragma once

#include "expression.h"
#include <memory>


namespace JaneZ {
enum unaryOp {
    BORROW,

    DEREFERENCE,

    NOT, // !
    NEGATE, // -
};

class ExprOpunary : public Expression {
private:
    unaryOp op;
    std::unique_ptr<Expression> right;

public:
    ExprOpunary(unaryOp operation, std::unique_ptr<Expression> rightExpr)
        : op(operation), right(std::move(rightExpr)) {}

    ~ExprOpunary() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}