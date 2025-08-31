# pragma once
# include "../ast.h"

namespace JaneZ {
class Statement : public ASTNode{
public:
    Statement() : ASTNode() {}
    virtual ~Statement() = default;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}