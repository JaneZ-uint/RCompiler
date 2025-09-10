# pragma once

#include "expression.h"
#include <memory>

namespace JaneZ {
enum binaryOp {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    AND,
    OR,
    XOR,
    LEFT_SHIFT,
    RIGHT_SHIFT,

    PLUS_EQUAL,
    MINUS_EQUAL,
    MULTIPLY_EQUAL,
    DIVIDE_EQUAL,
    MODULO_EQUAL,
    AND_EQUAL,
    OR_EQUAL,
    XOR_EQUAL,
    LEFT_SHIFT_EQUAL,
    RIGHT_SHIFT_EQUAL,

    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN_OR_EQUAL,

    ASSIGN,

    LOGICAL_AND,
    LOGICAL_OR,

    AS_CAST,
};

class ExprOpbinary : public Expression {
public:
    std::shared_ptr<Expression> left;
    binaryOp op;
    std::shared_ptr<Expression> right;

    ExprOpbinary(std::shared_ptr<Expression> leftExpr, binaryOp operation, std::shared_ptr<Expression> rightExpr)
        : left(std::move(leftExpr)), op(operation), right(std::move(rightExpr)) {}

    ~ExprOpbinary() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}