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
private:
    unaryOp op;
    bool is_mut = false;
    std::unique_ptr<Expression> right;

public:
    ExprOpunary(unaryOp operation, std::unique_ptr<Expression> rightExpr, bool im = false)
        : op(operation), right(std::move(rightExpr)), is_mut(im) {}

    ~ExprOpunary() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}