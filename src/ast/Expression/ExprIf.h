# pragma once

#include "expression.h"
#include <memory>

namespace JaneZ {
class ExprBlock;
class ExprIf : public Expression {
public:
    std::shared_ptr<Expression> condition;
    std::shared_ptr<ExprBlock> thenBlock;
    std::shared_ptr<Expression> elseBlock;

    ExprIf(std::shared_ptr<Expression> cond,
          std::shared_ptr<ExprBlock> thenBlk,
          std::shared_ptr<Expression> elseBlk)
        : condition(std::move(cond)),
          thenBlock(std::move(thenBlk)),
          elseBlock(std::move(elseBlk)) {}

    ~ExprIf() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}