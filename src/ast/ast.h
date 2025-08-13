# pragma once
#include "astvisitor.h"

namespace JaneZ {
class ASTNode{
public:
    ASTNode() = default;
    virtual ~ASTNode() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};

}