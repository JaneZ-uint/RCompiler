# include "parser.h"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace JaneZ{
struct bindingPower{
    size_t leftPower = 0;
    size_t rightPower = 0;
};

static std::unordered_map<tokenType,bindingPower> bindingPowerMap = {
    {kMINUS,{0,22}},
    {kNOT,{0,22}},
    {kSTAR,{0,22}},
    {kAND,{0,22}},
    {kANDAND,{0,22}},

    {kAS,{20,21}},

    {kSTAR,{18,19}},
    {kSLASH,{18,19}},
    {kPERCENT,{18,19}},

    {kPLUS,{16,17}},
    {kMINUS,{16,17}},

    {kSHL,{14,15}},
    {kSHR,{14,15}},

    {kAND,{12,13}},

    {kCARET,{10,11}},

    {kOR,{8,9}},

    {kEQEQ,{7,7}},
    {kNE,{7,7}},
    {kLT,{7,7}},
    {kLE,{7,7}},
    {kGT,{7,7}},
    {kGE,{7,7}},

    {kANDAND,{5,6}},

    {kOROR,{3,4}},

    //right to left
    {kEQ,{2,1}},
    {kPLUSEQ,{2,1}},
    {kMINUSEQ,{2,1}},
    {kSTAREQ,{2,1}},
    {kSLASHEQ,{2,1}},
    {kPERCENTEQ,{2,1}},
    {kCARETEQ,{2,1}},
    {kANDEQ,{2,1}},
    {kOREQ,{2,1}},
    {kSHLEQ,{2,1}},
    {kSHREQ,{2,1}},

    {kL_PAREN,{0,0}},
    {kR_PAREN,{0,0}},
    //TODO 
};

binaryOp getBinaryOp(tokenType current){
    switch (current) {
        case kPLUS:{
            return PLUS;
        }
        case kMINUS:{
            return MINUS;
        }
        case kSTAR:{
            return MULTIPLY;
        }
        case kSLASH:{
            return DIVIDE;
        }
        case kPERCENT:{
            return MODULO;
        }
        case kAND:{
            return AND;
        }
        case kOR:{
            return OR;
        }
        case kCARET:{
            return XOR;
        }
        case kSHL:{
            return LEFT_SHIFT;
        }
        case kSHR:{
            return RIGHT_SHIFT;
        }
        case kPLUSEQ:{
            return PLUS_EQUAL;
        }
        case kMINUSEQ:{
            return MINUS_EQUAL;
        }
        case kSTAREQ:{
            return MULTIPLY_EQUAL;
        }
        case kSLASHEQ:{
            return DIVIDE_EQUAL;
        }
        case kPERCENTEQ:{
            return MODULO_EQUAL;
        }
        case kCARETEQ:{
            return XOR_EQUAL;
        }
        case kANDEQ:{
            return AND_EQUAL;
        }
        case kOREQ:{
            return OR_EQUAL;
        }
        case kSHLEQ:{
            return LEFT_SHIFT_EQUAL;
        }
        case kSHREQ:{
            return RIGHT_SHIFT_EQUAL;
        }
        case kEQ:{
            return ASSIGN;
        }
        case kEQEQ:{
            return EQUAL;
        }
        case kNE:{
            return NOT_EQUAL;
        }
        case kGT:{
            return GREATER_THAN;
        }
        case kLT:{
            return LESS_THAN;
        }
        case kGE:{
            return GREATER_THAN_OR_EQUAL;
        }
        case kLE:{
            return LESS_THAN_OR_EQUAL;
        }
        case kANDAND:{
            return LOGICAL_AND;
        }
        case kOROR:{
            return LOGICAL_OR;
        }
        case kAS: {
            return AS_CAST;
        }
        default: {
            throw std::runtime_error("Not a binary op.");
        }
    }
}

unaryOp getUnaryOp(tokenType current) {
    switch (current) {
        case kAND: {
            return BORROW;
        }
        case kANDAND: {
            return BORROW;
        }
        case kSTAR: {
            return DEREFERENCE;
        }
        case kNOT: {
            return NOT;
        }
        case kMINUS: {
            return NEGATE;
        }
        default: {
            throw std::runtime_error("Not an unary type.");
        }
    }
}

std::unique_ptr<Expression> Parser::parse_expr() {
    
}

std::unique_ptr<ExprArray> Parser::parse_expr_array() {
    if(tokens[currentPos].type != kL_BRACKET){
        throw std::runtime_error("Wrong in expr array parsing, missing L_BRACKET.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> type;
    std::unique_ptr<Expression> size;
    std::unique_ptr<Expression> expr = nullptr;
    std::vector<std::unique_ptr<Expression>> arrayExpr;
    expr = parse_expr();
    if(tokens[currentPos].type == kSEMI){
        type = std::move(expr);
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        size = parse_expr();
        if(tokens[currentPos].type != kR_BRACKET){
            throw std::runtime_error("Wrong in expr array parsing, missing R_BRACKET.");
        }
        currentPos ++;
        return std::make_unique<ExprArray>(std::move(type),std::move(size));
    }
    arrayExpr.push_back(std::move(expr));
    if(tokens[currentPos].type == kCOMMA){
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    if(tokens[currentPos].type == kR_BRACKET){
        currentPos ++;
        return std::make_unique<ExprArray>(std::move(arrayExpr));
    }
    while(tokens[currentPos].type != kR_BRACKET){
        if(tokens[currentPos].type == kCOMMA){
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
        }
        std::unique_ptr<Expression> tmp;
        tmp = parse_expr();
        arrayExpr.push_back(std::move(tmp));
    }
    return std::make_unique<ExprArray>(std::move(arrayExpr));
}

std::unique_ptr<ExprBlock> Parser::parse_expr_block() {
    if(tokens[currentPos].type != kL_BRACE){
        throw std::runtime_error("Wrong in expr block parsing, missing L_BRACE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::vector<std::unique_ptr<Statement>> statements;
    std::unique_ptr<Expression> ExpressionWithoutBlock;
    std::unique_ptr<Statement> tmp;
    size_t originPos = currentPos;
    bool isExprBlock = false;
    try {
        tmp = parse_statement();
        statements.push_back(std::move(tmp));
    } catch (...) {
        currentPos = originPos;
        isExprBlock = true;
        ExpressionWithoutBlock = parse_expr();
    }
    if(isExprBlock){
        if(tokens[currentPos].type != kR_BRACE){
            throw std::runtime_error("Wrong in expr block parsing, missing R_BRACE.");
        }
        currentPos ++;
        return std::make_unique<ExprBlock>(std::move(statements),std::move(ExpressionWithoutBlock));
    }
    while(true){
        originPos = currentPos;
        try {
            tmp = parse_statement();
            statements.push_back(std::move(tmp));
        } catch (...) {
            currentPos = originPos;
            isExprBlock = true;
            ExpressionWithoutBlock = parse_expr();
        }
        if(isExprBlock){
            break;
        }
    }
    if(tokens[currentPos].type != kR_BRACE){
        throw std::runtime_error("Wrong in expr block parsing, missing R_BRACE.");
    }
    currentPos ++;
    return std::make_unique<ExprBlock>(std::move(statements),std::move(ExpressionWithoutBlock));
}

std::unique_ptr<ExprBreak> Parser::parse_expr_break() {
    if(tokens[currentPos].type != kBREAK){
        throw std::runtime_error("Wrong in expr break parsing, missing BREAK.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> expr = nullptr;
    //TODO 
}

std::unique_ptr<ExprCall> Parser::parse_expr_call() {

}

std::unique_ptr<ExprConstBlock> Parser::parse_expr_constblock() {

}

std::unique_ptr<ExprContinue> Parser::parse_expr_continue() {

}

std::unique_ptr<ExprField> Parser::parse_expr_field() {

}

std::unique_ptr<ExprGroup> Parser::parse_expr_group() {

}

std::unique_ptr<ExprIf> Parser::parse_expr_if() {

}

std::unique_ptr<ExprLiteral> Parser::parse_expr_literal() {

}

std::unique_ptr<ExprLoop> Parser::parse_expr_loop() {

}

std::unique_ptr<ExprMatch> Parser::parse_expr_match() {

}

std::unique_ptr<ExprMethodcall> Parser::parse_expr_methodcall() {

}

std::unique_ptr<ExprOpbinary> Parser::parse_expr_opbinary(){

}

std::unique_ptr<ExprOpunary> Parser::parse_expr_opunary() {

}

std::unique_ptr<ExprPath> Parser::parse_expr_path() {

}

std::unique_ptr<ExprReturn> Parser::parse_expr_return() {

}

std::unique_ptr<ExprStruct> Parser::parse_expr_struct() {

}

std::unique_ptr<ExprUnderscore> Parser::parse_expr_underscore() {
     
}
}