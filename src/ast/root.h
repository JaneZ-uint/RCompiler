# pragma once
#include "Item/item.h"
# include "ast.h"
#include <memory>
#include <vector>

namespace JaneZ {
class Item;
class  ASTRootNode: public ASTNode{
private:
    std::vector<std::unique_ptr<Item>> child;

public:
    ASTRootNode(std::vector<std::unique_ptr<Item>> _child) : child(std::move(_child)) {}

    ~ASTRootNode() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}