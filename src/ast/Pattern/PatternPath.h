# pragma once

#include "pattern.h"
#include "../Path.h"
#include <memory>

namespace JaneZ {
class PatternPath : public Pattern {
private:
    std::unique_ptr<Path> path;

public:
    PatternPath(std::unique_ptr<Path> p) : path(std::move(p)) {}    

    ~PatternPath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}