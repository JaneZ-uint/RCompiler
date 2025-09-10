# pragma once

#include "expression.h"
#include <memory>
#include <vector>
namespace JaneZ {
class Statement;
class ExprBlock : public Expression {
public:
    std::vector<std::shared_ptr<Statement>> statements;
    std::shared_ptr<Expression> ExpressionWithoutBlock;

    ExprBlock(std::vector<std::shared_ptr<Statement>> stmts,
              std::shared_ptr<Expression> EWB)
        : statements(std::move(stmts)),
          ExpressionWithoutBlock(std::move(EWB)) {}


    ~ExprBlock() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}