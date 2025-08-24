# pragma once

#include "ast.h"
#include <string>

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
private:
    PathIdentSegment pathSegments;

public:
    Path(PathIdentSegment segments)
        : pathSegments(segments) {}

    ~Path() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}