# pragma once

#include "statement.h"
namespace JaneZ {
class StmtEmpty : public Statement {
public:
    StmtEmpty(){}

    ~StmtEmpty() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}