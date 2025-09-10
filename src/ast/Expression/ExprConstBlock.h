# pragma once

#include "ExprBlock.h"
#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprConstBlock : public Expression {
public:
    std::shared_ptr<ExprBlock> expr;

    ExprConstBlock(std::shared_ptr<ExprBlock> exprBlock)
        : expr(std::move(exprBlock)) {}

    ~ExprConstBlock() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}