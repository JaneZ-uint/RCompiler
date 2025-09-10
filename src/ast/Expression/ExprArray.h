# pragma once

#include "expression.h"
#include <memory>
#include <vector>

namespace JaneZ {
//Two forms : Array Expr & Array Index Expr
class ExprArray : public Expression {
public:
    std::vector<std::shared_ptr<Expression>> arrayExpr;
    std::shared_ptr<Expression> type;
    std::shared_ptr<Expression> size;
    
    ExprArray(std::vector<std::shared_ptr<Expression>> arrayExpr)
        : arrayExpr(std::move(arrayExpr)), type(nullptr), size(nullptr) {};

    ExprArray(std::shared_ptr<Expression> type, std::shared_ptr<Expression> size)
        : arrayExpr(),type(std::move(type)), size(std::move(size)) {};

    ~ExprArray()  = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
    
};
}