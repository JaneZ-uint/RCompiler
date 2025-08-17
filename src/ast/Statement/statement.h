# pragma once
# include "../ast.h"

namespace JaneZ {
class Statement : public ASTNode{
public:
    Statement() : ASTNode() {}
    virtual ~Statement() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}