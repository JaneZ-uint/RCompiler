# pragma once

#include "expression.h"
#include <memory>
#include <vector>
namespace JaneZ {
class Statement;
class ExprBlock : public Expression {
private:
    std::vector<std::unique_ptr<Statement>> statements;
    std::unique_ptr<Expression> ExpressionWithoutBlock;

public:
    ExprBlock(std::vector<std::unique_ptr<Statement>> stmts,
              std::unique_ptr<Expression> EWB)
        : statements(std::move(stmts)),
          ExpressionWithoutBlock(std::move(EWB)) {}


    ~ExprBlock() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}