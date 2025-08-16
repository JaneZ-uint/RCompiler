# pragma once
# include "../ast.h"
#include <memory>
#include <string>
#include <vector>

namespace JaneZ {
class Type;
class Expression;
class Item : public ASTNode{
public:
    Item() = default;
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

struct ItemEnumVariant{
    std::string identifier;
    std::vector<std::unique_ptr<ItemTupleVariant>> item_tuple;
    std::vector<std::unique_ptr<ItemStructVariant>> item_struct;
    std::unique_ptr<Expression> item_discriminant;
};
}