# pragma once
#include "ast.h"

namespace JaneZ {
class Type : public ASTNode {
public:
    Type() = default;
    virtual ~Type() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};
}