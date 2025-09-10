# pragma once

#include "item.h"
#include <memory>
#include <vector>

namespace JaneZ {
class ItemFnDecl;
class ItemImplDecl : public Item {
public:
    std::string identifier = "";
    std::shared_ptr<ASTNode> targetType;
    std::vector<std::shared_ptr<ItemConstDecl>> item_trait_const;
    std::vector<std::shared_ptr<ItemFnDecl>> item_trait_fn;

    ItemImplDecl(std::string _identifier, std::shared_ptr<ASTNode> _targetType,
                 std::vector<std::shared_ptr<ItemConstDecl>> _item_trait_const,
                 std::vector<std::shared_ptr<ItemFnDecl>> _item_trait_fn) 
        : identifier(std::move(_identifier)), targetType(std::move(_targetType)),
            item_trait_const(std::move(_item_trait_const)),
            item_trait_fn(std::move(_item_trait_fn)) {}

    ~ItemImplDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}