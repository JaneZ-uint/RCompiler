# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class Path;
class ExprPath : public Expression {
private:
    std::unique_ptr<Path> path;

public:
    ExprPath(std::unique_ptr<Path> p) : path(std::move(p)) {}

    ~ExprPath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}