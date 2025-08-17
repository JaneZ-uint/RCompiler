# pragma once

#include "type.h"
#include <memory>
namespace JaneZ {
class TypeArray : public Type {
class Expression;
private:
    std::unique_ptr<Type> type;
    std::unique_ptr<Expression> expr;

public:
    TypeArray(std::unique_ptr<Type> t,std::unique_ptr<Expression> ex) : type(std::move(t)),expr(std::move(ex)) {}

    ~TypeArray() = default;
    
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}