# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class Path;
class ExprPath : public Expression {
public:
    std::unique_ptr<Path> pathFirst;
    std::unique_ptr<Path> pathSecond;

    ExprPath(std::unique_ptr<Path> _pathFirst, std::unique_ptr<Path> _pathSecond)
        : pathFirst(std::move(_pathFirst)), pathSecond(std::move(_pathSecond)) {}

    ~ExprPath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}