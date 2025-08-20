# pragma once

#include "ast.h"
#include <string>
#include <vector>

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
    std::vector<PathIdentSegment> pathSegments;

public:
    Path(std::vector<PathIdentSegment> segments)
        : pathSegments(std::move(segments)) {}

    ~Path() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}