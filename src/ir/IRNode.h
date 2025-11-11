# pragma once
# include "../ast/astvisitor.h"

namespace JaneZ{
class IRNode {
public:
    IRNode() = default;
    virtual ~IRNode() = default;
    virtual void accept(ASTVisitor &visitor) = 0;
};

}