# pragma once

#include "expression.h"
#include <memory>

namespace JaneZ {
class ExprCast : public Expression {
public:
    std::shared_ptr<ASTNode> typeNoBounds;

    ExprCast(std::shared_ptr<ASTNode> typeNoBounds)
        : typeNoBounds(std::move(typeNoBounds)) {}

    ~ExprCast() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}