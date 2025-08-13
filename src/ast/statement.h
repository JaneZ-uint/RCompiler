# pragma once
# include "ast.h"

namespace JaneZ {
class Statement : public ASTNode{
public:
    Statement() = default;
    virtual ~Statement() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}