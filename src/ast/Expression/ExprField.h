# pragma once

#include "expression.h"
#include <memory>
#include <string>

namespace JaneZ {
class ExprField : public Expression {
public:
    std::shared_ptr<Expression> expr;
    std::string identifier;

    ExprField(std::shared_ptr<Expression> ex, std::string id)
        : expr(std::move(ex)), identifier(std::move(id)) {}

    ~ExprField() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}