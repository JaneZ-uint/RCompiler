# pragma once

#include "item.h"
#include <memory>
#include <vector>
namespace JaneZ {
class ItemStructDecl : public Item {
private:
    std::string identifier;
    std::vector<std::unique_ptr<ItemStructVariant>> item_struct;
public:
    ItemStructDecl(std::string _identifier, 
                    std::vector<std::unique_ptr<ItemStructVariant>> _item_struct) 
        : identifier(std::move(_identifier)), item_struct(std::move(_item_struct)) {}

    ~ItemStructDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}