# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprIndex : public Expression {
public:
    std::shared_ptr<Expression> name;
    std::shared_ptr<Expression> index;

    ExprIndex(std::shared_ptr<Expression> nameExpr, std::shared_ptr<Expression> indexExpr)
        : name(std::move(nameExpr)), index(std::move(indexExpr)) {}

    ~ExprIndex() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}