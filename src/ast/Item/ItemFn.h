# pragma once

#include "item.h"
#include <string>
namespace JaneZ {
class ItemFnDecl : public Item {
private:
    std::string identifier;
    
public:
    ~ItemFnDecl() = default;
    
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}