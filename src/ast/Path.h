# pragma once

#include "ast.h"
#include <memory>
#include <string>
#include "../semantic/symbol.h"

namespace JaneZ {
enum PathIdentSegmentType {
    IDENTIFIER,
    SELF_TYPE, //Self
    SELF,  // self
};

struct PathIdentSegment{
    PathIdentSegmentType type;
    std::string identifier;
};

class Path : public ASTNode{
public:
    PathIdentSegment pathSegments;

    std::shared_ptr<Symbol> resolvedSymbol = nullptr;

    Path(PathIdentSegment segments)
        : pathSegments(segments) {}

    ~Path() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}