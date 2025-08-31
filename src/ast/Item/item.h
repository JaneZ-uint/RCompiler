# pragma once
# include "../ast.h"
#include <memory>
#include <string>

namespace JaneZ {
class Type;
class Expression;
class Item : public ASTNode{
public:
    Item() : ASTNode() {}
    virtual ~Item() = default;
    virtual void accept(ASTVisitor &visitor) = 0;
};

struct ItemTupleVariant{
    std::unique_ptr<ASTNode> tupleElem;
};

struct ItemStructVariant{
    std::unique_ptr<ASTNode> structElem;
    std::string identifier;
};

}