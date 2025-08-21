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
    std::vector<std::unique_ptr<ItemConstDecl>> item_trait_const;
    std::vector<std::unique_ptr<ItemFnDecl>> item_trait_fn;

public:
    ItemImplDecl(std::string _identifier, std::unique_ptr<Type> _targetType,
                 std::vector<std::unique_ptr<ItemConstDecl>> _item_trait_const,
                 std::vector<std::unique_ptr<ItemFnDecl>> _item_trait_fn) 
        : identifier(std::move(_identifier)), targetType(std::move(_targetType)),
            item_trait_const(std::move(_item_trait_const)),
            item_trait_fn(std::move(_item_trait_fn)) {}

    ~ItemImplDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}