# pragma once

#include "expression.h"
#include <string>

namespace JaneZ {
enum LiteralType{
    CHAR_LITERAL,
    STRING_LITERAL,
    RAW_STRING_LITERAL,
    C_STRING_LITERAL,
    RAW_C_STRING_LITERAL,
    INTEGER_LITERAL,
    TRUE,
    FALSE
};
class ExprLiteral : public Expression {
private:
    std::string literal;
    LiteralType type;

public:
    ExprLiteral(std::string lit, LiteralType t)
        : literal(std::move(lit)), type(t) {}
    
    ~ExprLiteral() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}