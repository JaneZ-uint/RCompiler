# pragma once

#include "expression.h"
#include "../Path.h"
#include <memory>
#include <vector>

namespace JaneZ {
class ExprMethodcall : public Expression {
public:
    std::unique_ptr<Expression> expr;
    std::unique_ptr<Path> PathExprSegment;
    std::vector<std::unique_ptr<Expression>> callParams;
    
    ExprMethodcall(std::unique_ptr<Expression> expr, std::unique_ptr<Path> pathExprSegment, 
        std::vector<std::unique_ptr<Expression>> callParams)
        : expr(std::move(expr)), PathExprSegment(std::move(pathExprSegment)), callParams(std::move(callParams)) {}

    ~ExprMethodcall() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}