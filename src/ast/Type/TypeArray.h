# pragma once
#include "../ast.h"
#include "../Expression/expression.h"
#include <memory>

namespace JaneZ {
class TypeArray : public ASTNode {
public:
    std::unique_ptr<ASTNode> type;
    std::unique_ptr<Expression> expr;

    TypeArray(std::unique_ptr<ASTNode> t,std::unique_ptr<Expression> ex) : 
    type(std::move(t)),expr(std::move(ex)) {}

    ~TypeArray() = default;
    
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}