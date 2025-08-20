# pragma once

#include "item.h"
#include "../Pattern/pattern.h"
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace JaneZ {
class Statement;
struct ShortSelf{
    bool is_and = false;
    bool is_mut = false;
};
struct TypeSelf{
    bool is_mut = false;
    std::unique_ptr<Type> type;
};
struct selfParam{
    bool isShortSelf = false;
    ShortSelf short_self;
    TypeSelf type_self;
};
struct functionParam{
    std::unique_ptr<Pattern> pattern;
    std::unique_ptr<Type> type;
};
struct fnParameter{
    selfParam SelfParam;
    std::vector<functionParam> FunctionParam;
};
class ItemFnDecl : public Item {
private:
    std::string identifier = "";
    fnParameter fnParameters;
    std::unique_ptr<ExprBlock> fnBody;
    std::unique_ptr<Type> returnType;
    bool is_const = false;

public:
    ItemFnDecl(std::string _identifier, fnParameter fnP, 
        std::unique_ptr<ExprBlock> fnB, std::unique_ptr<Type> returnT,bool isC = false): 
        identifier(std::move(_identifier)),fnParameters(std::move(fnP)),fnBody(std::move(fnB)),returnType(std::move(returnT)),is_const(isC){}

    ~ItemFnDecl() = default;
    
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}