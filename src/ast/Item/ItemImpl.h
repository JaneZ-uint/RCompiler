# pragma once

#include "item.h"
#include <memory>
#include <vector>

namespace JaneZ {
class ItemFnDecl;
class ItemImplDecl : public Item {
private:
    std::string identifier = "";
    std::unique_ptr<Type> targetType;
    std::vector<Item> item_impl;

public:
    ItemImplDecl(std::string _identifier, std::unique_ptr<Type> _targetType, 
        std::vector<Item> _item_impl) 
        : identifier(std::move(_identifier)), targetType(std::move(_targetType)), 
          item_impl(std::move(_item_impl)){}

    ~ItemImplDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}