# pragma once
# include "../ast.h"

namespace JaneZ {
class Pattern : public ASTNode{
public:
    Pattern() : ASTNode() {}
    virtual ~Pattern() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}