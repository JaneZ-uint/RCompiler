# pragma once

#include "expression.h"
#include <memory>
#include <iostream>

namespace JaneZ {
enum unaryOp {
    BORROW,

    DEREFERENCE,

    NOT, // !
    NEGATE, // -

    UNKNOWN,
};

inline void Print_Op_Unary(unaryOp op){
    switch (op) {
        case BORROW: {
            std::cout << "&";
            break;
        }
        case DEREFERENCE: {
            std::cout << "*";
            break;
        }
        case NOT: {
            std::cout << "!";
            break;
        }
        case NEGATE: {
            std::cout << "-";
            break;
        }
        default: {
            std::cout << "Unknown unary op";
            break;
        }
    }
}

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