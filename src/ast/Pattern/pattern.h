# pragma once
# include "../ast.h"

namespace JaneZ {
class Pattern : public ASTNode{
public:
    Pattern() = default;
    virtual ~Pattern() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}