# pragma once

#include "pattern.h"
#include <memory>

namespace JaneZ {
class PatternPath : public Pattern {
private:
    std::unique_ptr<ExprPath> path;

public:
    PatternPath(std::unique_ptr<ExprPath> p) : path(std::move(p)) {}    

    ~PatternPath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}