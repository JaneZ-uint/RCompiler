# pragma once
# include "../ast.h"

namespace JaneZ {
class Item : public ASTNode{
public:
    Item() = default;
    virtual ~Item() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};

}