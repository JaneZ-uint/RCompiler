# pragma once

#include "expression.h"
#include <memory>


namespace JaneZ {
enum unaryOp {
    BORROW,

    DEREFERENCE,

    NOT, // !
    NEGATE, // -

    UNKNOWN,
};

class ExprOpunary : public Expression {
public:
    unaryOp op;
    bool is_mut = false;
    std::shared_ptr<Expression> right;

    ExprOpunary(unaryOp operation, std::shared_ptr<Expression> rightExpr, bool im = false)
        : op(operation), right(std::move(rightExpr)), is_mut(im) {}

    ~ExprOpunary() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}