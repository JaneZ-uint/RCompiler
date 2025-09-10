# pragma once

#include "expression.h"
#include <memory>
namespace JaneZ {
class Path;
class ExprPath : public Expression {
public:
    std::shared_ptr<Path> pathFirst;
    std::shared_ptr<Path> pathSecond;

    ExprPath(std::shared_ptr<Path> _pathFirst, std::shared_ptr<Path> _pathSecond)
        : pathFirst(std::move(_pathFirst)), pathSecond(std::move(_pathSecond)) {}

    ~ExprPath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}