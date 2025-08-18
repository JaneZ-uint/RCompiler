# pragma once

#include "expression.h"
#include <memory>
#include <string>
#include <vector>

namespace JaneZ {
class ExprMethodcall : public Expression {
private:
    std::unique_ptr<Expression> expr;
    std::string PathExprSegment;
    std::vector<std::unique_ptr<Expression>> callParams;

public:
    ExprMethodcall(std::unique_ptr<Expression> expr, std::string pathExprSegment, 
        std::vector<std::unique_ptr<Expression>> callParams)
        : expr(std::move(expr)), PathExprSegment(std::move(pathExprSegment)), callParams(std::move(callParams)) {}

    ~ExprMethodcall() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}