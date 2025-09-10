# pragma once

#include "item.h"
#include <memory>
#include <string>
#include <utility>
namespace JaneZ {
class Type;
class Expression;
class ItemConstDecl : public Item {
public:
    std::string identifier;
    std::shared_ptr<ASTNode> type;
    std::shared_ptr<Expression> expr;

    ItemConstDecl(std::string _identifier,std::shared_ptr<ASTNode> t,std::shared_ptr<Expression> e): identifier(std::move(_identifier)), type(std::move(t)), expr(std::move(e)){}

    ~ItemConstDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}