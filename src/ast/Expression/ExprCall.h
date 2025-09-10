# pragma once

#include "expression.h"
#include <memory>
#include <vector>
namespace JaneZ {
class ExprCall : public Expression {
public:
    std::shared_ptr<Expression> expr;
    std::vector<std::shared_ptr<Expression>> callParams;

    ExprCall(std::shared_ptr<Expression> e,
            std::vector<std::shared_ptr<Expression>> cp)
        : expr(std::move(e)), callParams(std::move(cp)) {}

    ~ExprCall() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}