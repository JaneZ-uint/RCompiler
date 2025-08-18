# pragma once

#include "expression.h"
#include <memory>
#include <vector>
namespace JaneZ {
class ExprCall : public Expression {
private:
    std::unique_ptr<Expression> expr;
    std::vector<std::unique_ptr<Expression>> callPrograms;

public:
    ExprCall(std::unique_ptr<Expression> e,
            std::vector<std::unique_ptr<Expression>> cp)
        : expr(std::move(e)), callPrograms(std::move(cp)) {}

    ~ExprCall() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}