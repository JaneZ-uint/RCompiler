# pragma once
#include "astvisitor.h"

namespace JaneZ {
class ASTNode{
public:
    ASTNode() = default;
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor &visitor) = 0;
};

}