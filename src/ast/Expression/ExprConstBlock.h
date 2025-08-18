# pragma once

#include "ExprBlock.h"
#include "expression.h"
#include <memory>
namespace JaneZ {
class ExprConstBlock : public Expression {
private:
    std::unique_ptr<ExprBlock> expr;

public:
    ExprConstBlock(std::unique_ptr<ExprBlock> exprBlock)
        : expr(std::move(exprBlock)) {}

    ~ExprConstBlock() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}