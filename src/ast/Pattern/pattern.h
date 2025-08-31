# pragma once
# include "../ast.h"

namespace JaneZ {
class Pattern : public ASTNode{
public:
    Pattern() : ASTNode() {}
    virtual ~Pattern() = default;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}