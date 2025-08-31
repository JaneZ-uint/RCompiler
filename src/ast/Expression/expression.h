# pragma once
# include "../ast.h"

namespace JaneZ {
class Expression : public ASTNode{
public:
public:
    Expression() : ASTNode() {}
    virtual ~Expression() = default;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}