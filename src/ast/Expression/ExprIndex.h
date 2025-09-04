# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprIndex : public Expression {
public:
    std::unique_ptr<Expression> name;
    std::unique_ptr<Expression> index;

    ExprIndex(std::unique_ptr<Expression> nameExpr, std::unique_ptr<Expression> indexExpr)
        : name(std::move(nameExpr)), index(std::move(indexExpr)) {}

    ~ExprIndex() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}