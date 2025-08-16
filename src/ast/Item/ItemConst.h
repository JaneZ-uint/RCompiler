# pragma once

#include "item.h"
#include <memory>
#include <string>
#include <utility>
namespace JaneZ {
class Type;
class Expression;
class ItemConstDecl : public Item {
private:
    std::string identifier;
    std::unique_ptr<Type> type;
    std::unique_ptr<Expression> expr;

public:
    ItemConstDecl(std::string _identifier,std::unique_ptr<Type> t,std::unique_ptr<Expression> e): identifier(std::move(_identifier)), type(std::move(t)), expr(std::move(e)){}

    ~ItemConstDecl() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}