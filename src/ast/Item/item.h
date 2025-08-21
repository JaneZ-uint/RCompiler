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
    virtual ~Item() = 0;
    virtual void accept(ASTVisitor &visitor) = 0;
};

struct ItemTupleVariant{
    std::unique_ptr<Type> tupleElem;
};

struct ItemStructVariant{
    std::unique_ptr<Type> structElem;
    std::string identifier;
};

}