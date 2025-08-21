# pragma once

#include "item.h"
#include <string>
#include <vector>

namespace JaneZ {
class ItemEnumDecl : public Item {
private:
    std::string identifier;
    std::vector<std::string> item_enum;
    
public:
    ItemEnumDecl(std::string _identifier, std::vector<std::string> _itemEnum) : identifier(_identifier),item_enum(_itemEnum){} 

    ~ItemEnumDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}