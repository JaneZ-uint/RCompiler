# pragma once

#include "expression.h"
#include <memory>
#include <string>

namespace JaneZ {
class ExprField : public Expression {
private:
    std::unique_ptr<Expression> expr;
    std::string identifier;

public:
    ExprField(std::unique_ptr<Expression> ex, std::string id)
        : expr(std::move(ex)), identifier(std::move(id)) {}

    ~ExprField() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}