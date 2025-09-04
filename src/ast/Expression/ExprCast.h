# pragma once

#include "expression.h"
#include <memory>

namespace JaneZ {
class ExprCast : public Expression {
public:
    std::unique_ptr<ASTNode> typeNoBounds;

    ExprCast(std::unique_ptr<ASTNode> typeNoBounds)
        : typeNoBounds(std::move(typeNoBounds)) {}

    ~ExprCast() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}