# pragma once

#include "item.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace JaneZ {
class Statement;
class ItemFnDecl : public Item {
private:
    std::string identifier = "";
    std::vector<std::pair<std::string, std::unique_ptr<Type>>> fnParameters;
    std::unique_ptr<ExprBlock> fnBody;
    std::unique_ptr<Type> returnType;

public:
    ItemFnDecl(std::string _identifier, std::vector<std::pair<std::string, std::unique_ptr<Type>>> fnP, 
        std::unique_ptr<ExprBlock> fnB, std::unique_ptr<Type> returnT): 
        identifier(std::move(_identifier)),fnParameters(std::move(fnP)),fnBody(std::move(fnB)),returnType(std::move(returnT)){}

    ~ItemFnDecl() = default;
    
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}