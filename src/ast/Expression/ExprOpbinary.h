# pragma once

#include "expression.h"
#include <memory>
#include <iostream>

namespace JaneZ {
enum binaryOp {
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    MODULO,
    AND,
    OR,
    XOR,
    LEFT_SHIFT,
    RIGHT_SHIFT,

    PLUS_EQUAL,
    MINUS_EQUAL,
    MULTIPLY_EQUAL,
    DIVIDE_EQUAL,
    MODULO_EQUAL,
    AND_EQUAL,
    OR_EQUAL,
    XOR_EQUAL,
    LEFT_SHIFT_EQUAL,
    RIGHT_SHIFT_EQUAL,

    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_THAN_OR_EQUAL,
    LESS_THAN_OR_EQUAL,

    ASSIGN,

    LOGICAL_AND,
    LOGICAL_OR,

    AS_CAST,
};

inline void Print_Op_Binary(binaryOp op) {
    if(op == PLUS) {
        std::cout << "+";
    }else if(op == MINUS) {
        std::cout << "-";
    }else if(op == MULTIPLY) {
        std::cout << "*";
    }else if(op == DIVIDE) {
        std::cout << "/";
    }else if(op == MODULO) {
        std::cout << "%";
    }else if(op == AND) {
        std::cout << "&";
    }else if(op == OR) {
        std::cout << "|";
    }else if(op == XOR) {
        std::cout << "^";
    }else if(op == LEFT_SHIFT) {
        std::cout << "<<";
    }else if(op == RIGHT_SHIFT) {        
        std::cout << ">>";
    }else if(op == PLUS_EQUAL) {
        std::cout << "+=";
    }else if(op == MINUS_EQUAL) {        
        std::cout << "-=";
    }else if(op == MULTIPLY_EQUAL) {
        std::cout << "*=";
    }else if(op == DIVIDE_EQUAL) {
        std::cout << "/=";
    }else if(op == MODULO_EQUAL) {
        std::cout << "%=";
    }else if(op == AND_EQUAL) {
        std::cout << "&=";
    }else if(op == OR_EQUAL) {        
        std::cout << "|=";
    }else if(op == XOR_EQUAL) {
        std::cout << "^=";
    }else if(op == LEFT_SHIFT_EQUAL) {
        std::cout << "<<=";
    }else if(op == RIGHT_SHIFT_EQUAL) {
        std::cout << ">>=";
    }else if(op == EQUAL) {
        std::cout << "==";
    }else if(op == NOT_EQUAL) {
        std::cout << "!=";
    }else if(op == GREATER_THAN) {
        std::cout << ">";
    }else if(op == LESS_THAN) {
        std::cout << "<";
    }else if(op == GREATER_THAN_OR_EQUAL) {        
        std::cout << ">=";
    }else if(op == LESS_THAN_OR_EQUAL) {
        std::cout << "<=";      
    }else if(op == ASSIGN) {
        std::cout << "=";
    }else if(op == LOGICAL_AND) {
        std::cout << "&&";  
    }else if(op == LOGICAL_OR) {
        std::cout << "||";
    }else if(op == AS_CAST) {
        std::cout << "as";
    }else{
        std::cout << "Unknown binary op";
    }
}

class ExprOpbinary : public Expression {
public:
    std::shared_ptr<Expression> left;
    binaryOp op;
    std::shared_ptr<Expression> right;

    ExprOpbinary(std::shared_ptr<Expression> leftExpr, binaryOp operation, std::shared_ptr<Expression> rightExpr)
        : left(std::move(leftExpr)), op(operation), right(std::move(rightExpr)) {}

    ~ExprOpbinary() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}