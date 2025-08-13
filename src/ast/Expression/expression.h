# pragma once
# include "../ast.h"

namespace JaneZ {
class Expression : public ASTNode{
public:
public:
    Expression() = default;
    virtual ~Expression() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}