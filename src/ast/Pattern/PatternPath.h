# pragma once

#include "pattern.h"
#include <memory>

namespace JaneZ {
class PatternPath : public Pattern {
public:
    std::shared_ptr<ExprPath> path;

    PatternPath(std::shared_ptr<ExprPath> p) : path(std::move(p)) {}    

    ~PatternPath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}