# pragma once
#include "../ast.h"
#include "../Expression/expression.h"
#include <memory>

namespace JaneZ {
class TypeArray : public ASTNode {
public:
    std::shared_ptr<ASTNode> type;
    std::shared_ptr<Expression> expr;

    TypeArray(std::shared_ptr<ASTNode> t,std::shared_ptr<Expression> ex) : 
    type(std::move(t)),expr(std::move(ex)) {}

    ~TypeArray() = default;
    
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}