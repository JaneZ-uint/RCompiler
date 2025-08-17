# pragma once

#include "pattern.h"
#include "../Path.h"

namespace JaneZ {
class PatternPath : public Pattern {
private:
    Path path;

public:
    PatternPath(Path p): path(std::move(p)) {}

    ~PatternPath() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}