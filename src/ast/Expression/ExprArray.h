# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
//Two forms : Array Expr & Array Index Expr
class ExprArray : public Expression {
private:
    std::unique_ptr<Expression> type;
    std::unique_ptr<Expression> size;
    
public:
    ExprArray() = default;
    ~ExprArray() override = default;
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
    
};
}