# pragma once

#include "item.h"
#include <string>
#include <vector>

namespace JaneZ {
class ItemEnumDecl : public Item {
public:
    std::string identifier;
    std::vector<std::string> item_enum;
    
    ItemEnumDecl(std::string _identifier, std::vector<std::string> _itemEnum) : identifier(_identifier),item_enum(_itemEnum){} 

    ~ItemEnumDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}