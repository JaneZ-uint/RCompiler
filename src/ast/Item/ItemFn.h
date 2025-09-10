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
    std::shared_ptr<ASTNode> type;
};
struct selfParam{
    bool isShortSelf = false;
    ShortSelf short_self;
    TypeSelf type_self;
};
struct functionParam{
    std::shared_ptr<Pattern> pattern;
    std::shared_ptr<ASTNode> type;
};
struct fnParameter{
    selfParam SelfParam;
    std::vector<functionParam> FunctionParam;
};
class ItemFnDecl : public Item {
public:
    std::string identifier = "";
    fnParameter fnParameters;
    std::shared_ptr<ExprBlock> fnBody;
    std::shared_ptr<ASTNode> returnType;
    bool is_const = false;

    ItemFnDecl(std::string _identifier, fnParameter fnP, 
        std::shared_ptr<ExprBlock> fnB, std::shared_ptr<ASTNode> returnT,bool isC = false): 
        identifier(std::move(_identifier)),fnParameters(std::move(fnP)),fnBody(std::move(fnB)),returnType(std::move(returnT)),is_const(isC){}

    ~ItemFnDecl() = default;
    
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}