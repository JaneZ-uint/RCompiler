# pragma once

#include "statement.h"
#include <memory>
namespace JaneZ {
class Expression;
class StmtExpr : public Statement {
private:
    std::unique_ptr<Expression> stmtExpr;

public:
    StmtExpr(std::unique_ptr<Expression> se) : stmtExpr(std::move(se)) {}

    ~StmtExpr() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}