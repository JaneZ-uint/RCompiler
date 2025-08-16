# pragma once

#include "item.h"
#include <memory>
#include <vector>
namespace JaneZ {
class ItemModuleDecl : public Item {
private:
    std::string identifier;
    std::vector<std::unique_ptr<Item>> item_module;
public:
    ItemModuleDecl(std::string _identifier, 
                    std::vector<std::unique_ptr<Item>> _item_module) 
        : identifier(std::move(_identifier)), item_module(std::move(_item_module)) {}

    ~ItemModuleDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}