# pragma once

#include "expression.h"
#include <memory>
#include <vector>

namespace JaneZ {
//Two forms : Array Expr & Array Index Expr
class ExprArray : public Expression {
private:
    std::vector<std::unique_ptr<Expression>> arrayExpr;
    std::unique_ptr<Expression> type;
    std::unique_ptr<Expression> size;
    
public:
    ExprArray(std::vector<std::unique_ptr<Expression>> arrayExpr)
        : arrayExpr(std::move(arrayExpr)), type(nullptr), size(nullptr) {};

    ExprArray(std::unique_ptr<Expression> type, std::unique_ptr<Expression> size)
        : arrayExpr(),type(std::move(type)), size(std::move(size)) {};

    ~ExprArray()  = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
    
};
}