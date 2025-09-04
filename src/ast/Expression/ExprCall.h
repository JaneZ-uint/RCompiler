# pragma once

#include "expression.h"
#include <memory>
#include <vector>
namespace JaneZ {
class ExprCall : public Expression {
public:
    std::unique_ptr<Expression> expr;
    std::vector<std::unique_ptr<Expression>> callParams;

    ExprCall(std::unique_ptr<Expression> e,
            std::vector<std::unique_ptr<Expression>> cp)
        : expr(std::move(e)), callParams(std::move(cp)) {}

    ~ExprCall() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}