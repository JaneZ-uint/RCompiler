# pragma once

#include "expression.h"
#include <memory>

namespace JaneZ {
class ExprBlock;
class ExprIf : public Expression {
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<ExprBlock> thenBlock;
    std::unique_ptr<Expression> elseBlock;

    ExprIf(std::unique_ptr<Expression> cond,
          std::unique_ptr<ExprBlock> thenBlk,
          std::unique_ptr<Expression> elseBlk)
        : condition(std::move(cond)),
          thenBlock(std::move(thenBlk)),
          elseBlock(std::move(elseBlk)) {}

    ~ExprIf() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}