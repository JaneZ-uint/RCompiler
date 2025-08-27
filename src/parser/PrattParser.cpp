# include "parser.h"
#include <cctype>
#include <cmath>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <utility>
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

binaryOp Parser::getBinaryOp(tokenType current){
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

unaryOp Parser::getUnaryOp(tokenType current) {
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
            return UNKNOWN;
        }
    }
}

int Parser::getPrecedence(tokenType type) {
    if(bindingPowerMap.find(type) != bindingPowerMap.end()) {
        return bindingPowerMap.find(type)->second.rightPower;
    }
    return -1;
}

std::unique_ptr<Expression> Parser::parse_expr() {
    std::unique_ptr<Expression> left = nullptr;
    //TODO 
}

// most cases except binaryOp
std::unique_ptr<Expression> Parser::parse_expr_prefix() {
    switch (tokens[currentPos].type) {
        case kCHAR_LITERAL:
        case kSTRING_LITERAL:
        case kRAW_STRING_LITERAL:
        case kCSTRING_LITERAL:
        case kRAW_CSTRING_LITERAL:
        case kINTEGER_LITERAL:
        case kTRUE:
        case kFALSE: {
            return parse_expr_literal();
        }
        case kIDENTIFIER:
        case kSELF:
        case kSELF_TYPE: {
            return parse_expr_path();
        }
        case kL_PAREN: {
            return parse_expr_group();
        }
        case kL_BRACKET: {
            return parse_expr_array();
        }
        case kCONTINUE: {
            return parse_expr_continue();
        }
        case kBREAK: {
            return parse_expr_break();
        }
        case kRETURN: {
            return parse_expr_return();
        }
        case kUNDERSCORE: {
            return parse_expr_underscore();
        }
        case kL_BRACE: {
            return parse_expr_block();
        }
        case kCONST: {
            return parse_expr_constblock();
        }
        case kLOOP:
        case kWHILE: {
            return parse_expr_loop();
        }
        case kIF: {
            return parse_expr_if();
        }
        case kAND:
        case kANDAND:
        case kMINUS:
        case kNOT:
        case kSTAR: {
            return parse_expr_opunary();
        }
        default:{
            throw std::runtime_error("Not a prefix.");
        }
    }
}

std::unique_ptr<Expression> Parser::parse_expr_infix() {
    size_t originPos = currentPos;
    std::unique_ptr<Expression> firstExpr;
    firstExpr = parse_expr();
    switch (tokens[currentPos].type) {
        case kL_BRACKET: {
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            std::unique_ptr<Expression> index;
            index = parse_expr();
            if(tokens[currentPos].type != kR_BRACKET) {
                throw std::runtime_error("Wrong in expr index parsing, missing kR_BRACKET.");
            }
            currentPos ++;
            return std::make_unique<ExprIndex>(std::move(firstExpr),std::move(index));
        }
        case kL_BRACE: {
            currentPos = originPos;
            return parse_expr_struct();
        }
        case kL_PAREN: {
            currentPos = originPos;
            return parse_expr_call();
        }
        case kDOT: {
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kSELF || tokens[currentPos].type == kSELF) {
                currentPos = originPos;
                return parse_expr_methodcall();
            }
            if(tokens[currentPos].type != kIDENTIFIER) {
                throw std::runtime_error("Wrong in expr infix parsing, missing identifier.");
            }
            currentPos ++;
            if(currentPos == tokens.size()) {
                currentPos = originPos;
                return parse_expr_field();
            }
            if(tokens[currentPos].type == kL_PAREN) {
                currentPos = originPos;
                return parse_expr_methodcall();
            }
            currentPos = originPos;
            return parse_expr_field();
        }
    }
    //TODO Left with binary op.
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
    bool flag = false;
    while(tokens[currentPos].type != kR_BRACKET){
        if(tokens[currentPos].type == kCOMMA){
            flag = true;
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kR_BRACKET) {
                break;
            }
        }else if(flag){
            throw std::runtime_error("Wrong in expr array parsing, missing COMMA.");
        }
        std::unique_ptr<Expression> tmp;
        tmp = parse_expr();
        arrayExpr.push_back(std::move(tmp));
    }
    currentPos ++;
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
    bool isExprBlock = false;
    size_t ptr = currentPos;
    /*
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
    currentPos ++;*/
    size_t bracePair = 1;
    while(tokens[ptr].type != kSEMI){
        ptr ++;
        if(tokens[ptr].type == kR_BRACE){
            bracePair --;
        }else if(tokens[ptr].type == kL_BRACE){
            bracePair ++;
        }
        if(bracePair == 0){
            isExprBlock = true;
            break;
        }
    }
    if(isExprBlock){
        ExpressionWithoutBlock = parse_expr();
        if(tokens[currentPos].type != kR_BRACE){
            throw std::runtime_error("Wrong in expr block parsing, missing R_BRACE.");
        }
        currentPos ++;
        return std::make_unique<ExprBlock>(std::move(statements),std::move(ExpressionWithoutBlock));
    }
    while(tokens[currentPos].type != kR_BRACE){
        tmp = parse_statement();
        statements.push_back(std::move(tmp));
        if(tokens[currentPos - 1].type != kSEMI){
            ExpressionWithoutBlock = parse_expr();
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
    if(tokens[currentPos].type == kSEMI){
        currentPos ++;
        return std::make_unique<ExprBreak>(std::move(expr));
    }
    expr = parse_expr();
    if(tokens[currentPos].type != kSEMI){
        throw std::runtime_error("Wrong in expr break parsing, missing SEMI.");
    }
    currentPos ++;
    return std::make_unique<ExprBreak>(std::move(expr));
}

std::unique_ptr<ExprCall> Parser::parse_expr_call() {
    std::unique_ptr<Expression> expr;
    std::vector<std::unique_ptr<Expression>> callParams;
    expr = parse_expr();
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in expr call parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> tmp;
    tmp = parse_expr();
    callParams.push_back(std::move(tmp));
    if(tokens[currentPos].type == kCOMMA) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    if(tokens[currentPos].type == kR_PAREN){
        currentPos ++;
        return std::make_unique<ExprCall>(std::move(expr),std::move(callParams));
    }
    bool flag = false;
    while(tokens[currentPos].type != kR_PAREN){
        if(tokens[currentPos].type == kCOMMA){
            flag = true;
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kR_PAREN){
                break;
            }
        }else if(flag){
            throw std::runtime_error("Wrong in expr call parsing, missing COMMA.");
        }
        tmp = parse_expr();
        callParams.push_back(std::move(tmp));
    }
    currentPos ++;
    return std::make_unique<ExprCall>(std::move(expr),std::move(callParams));
}

std::unique_ptr<ExprConstBlock> Parser::parse_expr_constblock() {
    if(tokens[currentPos].type != kCONST){
        throw std::runtime_error("Wrong in expr constblock parsing, missing CONST.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<ExprBlock> expr;
    expr = parse_expr_block();
    return std::make_unique<ExprConstBlock>(std::move(expr));
}

std::unique_ptr<ExprContinue> Parser::parse_expr_continue() {
    if(tokens[currentPos].type != kCONTINUE){
        throw std::runtime_error("Wrong in expr continue parsing, missing CONTINUE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    return std::make_unique<ExprContinue>();
}

std::unique_ptr<ExprField> Parser::parse_expr_field() {
    std::unique_ptr<Expression> expr;
    std::string identifier;
    expr = parse_expr();
    if(tokens[currentPos].type != kDOT){
        throw std::runtime_error("Wrong in expr field parsing, missing DOT.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kIDENTIFIER){
        throw std::runtime_error("Wrong in expr field parsing, missing IDENTIFIER.");
    }
    identifier = tokens[currentPos].value;
    currentPos ++;
    return std::make_unique<ExprField>(std::move(expr),std::move(identifier));
}

std::unique_ptr<ExprGroup> Parser::parse_expr_group() {
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in expr group parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> expr;
    expr = parse_expr();
    if(tokens[currentPos].type != kR_PAREN){
        throw std::runtime_error("Wrong in expr group parsing, missing R_PAREN.");
    }
    currentPos ++;
    return std::make_unique<ExprGroup>(std::move(expr));
}

std::unique_ptr<ExprIf> Parser::parse_expr_if() {
    if(tokens[currentPos].type != kIF){
        throw std::runtime_error("Wrong in expr if parsing, missing IF.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> condition = nullptr;
    std::unique_ptr<ExprBlock> thenBlock = nullptr;
    std::unique_ptr<Expression> elseBlock = nullptr;
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in expr if parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    condition = parse_expr();
    //TODO maybe left with a struct expr check.
    if(tokens[currentPos].type != kR_PAREN){
        throw std::runtime_error("Wrong in expr if parsing, missing R_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    thenBlock = parse_expr_block();
    if(tokens[currentPos].type != kELSE){
        return std::make_unique<ExprIf>(std::move(condition),std::move(thenBlock),std::move(elseBlock));
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    elseBlock = parse_expr();
    return std::make_unique<ExprIf>(std::move(condition),std::move(thenBlock),std::move(elseBlock));
}

std::unique_ptr<ExprLiteral> Parser::parse_expr_literal() {
    std::string literal;
    LiteralType type;
    switch (tokens[currentPos].type) {
        case kCHAR_LITERAL: {
            literal = tokens[currentPos].value;
            type = CHAR_LITERAL;
            break;
        }
        case kSTRING_LITERAL: {
            literal = tokens[currentPos].value;
            type = STRING_LITERAL;
            break;
        }
        case kRAW_STRING_LITERAL: {
            literal = tokens[currentPos].value;
            type = RAW_STRING_LITERAL;
            break;
        }
        case kCSTRING_LITERAL: {
            literal = tokens[currentPos].value;
            type = C_STRING_LITERAL;
            break;
        }
        case kRAW_CSTRING_LITERAL: {
            literal = tokens[currentPos].value;
            type = RAW_C_STRING_LITERAL;
            break;
        }
        case kINTEGER_LITERAL :{
            literal = tokens[currentPos].value;
            type = INTEGER_LITERAL;
            break;
        }
        case kTRUE:{
            literal = "true";
            type = TRUE;
            break;
        }
        case kFALSE:{
            literal = "false";
            type = FALSE;
            break;
        }
        default:{
            throw std::runtime_error("Wrong in expr literal parsing, missing literal.");
        }
    }
    currentPos ++;
    return std::make_unique<ExprLiteral>(std::move(literal),type);
}

std::unique_ptr<ExprLoop> Parser::parse_expr_loop() {
    std::unique_ptr<ExprBlock> infinitieLoop;
    std::unique_ptr<Expression> condition;
    std::unique_ptr<ExprBlock> PredicateLoopExpression;
    if(tokens[currentPos].type == kLOOP){
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        infinitieLoop = parse_expr_block();
        return std::make_unique<ExprLoop>(std::move(infinitieLoop));
    }else if(tokens[currentPos].type == kWHILE){
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kL_PAREN){
            throw std::runtime_error("Wrong in expr loop parsing, missing L_PAREN.");
        }
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        condition = parse_expr();
        //TODO maybe left with a struct expr check.
        if(tokens[currentPos].type != kR_PAREN){
            throw std::runtime_error("Wrong in expr loop parsing, missing R_PAREN.");
        }
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        PredicateLoopExpression = parse_expr_block();
        return std::make_unique<ExprLoop>(std::move(condition),std::move(PredicateLoopExpression));
    }else {
        throw std::runtime_error("Wrong in expr loop parsing, missing LOOP or WHILE.");
    }
}

std::unique_ptr<ExprMethodcall> Parser::parse_expr_methodcall() {
    std::unique_ptr<Expression> expr;
    std::unique_ptr<Path> PathExprSegment;
    std::vector<std::unique_ptr<Expression>> callParams;
    expr = parse_expr();
    if(tokens[currentPos].type != kDOT){
        throw std::runtime_error("Wrong in expr methodcall parsing, missing DOT.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    PathExprSegment = parse_path();
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in expr methodcall parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> tmp;
    tmp = parse_expr();
    callParams.push_back(std::move(tmp));
    if(tokens[currentPos].type == kCOMMA) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    if(tokens[currentPos].type == kR_PAREN){
        currentPos ++;
        return std::make_unique<ExprMethodcall>(std::move(expr),std::move(PathExprSegment),std::move(callParams));
    }
    bool flag = false;
    while(tokens[currentPos].type != kR_PAREN){
        if(tokens[currentPos].type == kCOMMA){
            flag = true;
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kR_PAREN){
                break;
            }
        }else if(flag){
            throw std::runtime_error("Wrong in expr methodcall parsing, missing COMMA.");
        }
        tmp = parse_expr();
        callParams.push_back(std::move(tmp));
    }
    currentPos ++;
    return std::make_unique<ExprMethodcall>(std::move(expr),std::move(PathExprSegment),std::move(callParams));
}

std::unique_ptr<ExprOpbinary> Parser::parse_expr_opbinary(){

}

std::unique_ptr<ExprOpunary> Parser::parse_expr_opunary() {
    unaryOp op;
    op = getUnaryOp(tokens[currentPos].type);
    bool is_mut = false;
    if(op == UNKNOWN) {
        throw std::runtime_error("Wrong in expr unaryOp parsing, wrong type.");
    }
    if(tokens[currentPos].type == kAND || tokens[currentPos].type == kANDAND) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type == kMUT) {
            is_mut = true;
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
        }
    }else{
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    std::unique_ptr<Expression> right = nullptr;
    //TODO
}

std::unique_ptr<ExprPath> Parser::parse_expr_path() {
    std::unique_ptr<Path> pathFirst = nullptr;
    std::unique_ptr<Path> pathSecond = nullptr;
    pathFirst = parse_path();
    if(tokens[currentPos].type == kPATHSEP){
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        pathSecond = parse_path();
        return std::make_unique<ExprPath>(std::move(pathFirst),std::move(pathSecond));
    }
    return std::make_unique<ExprPath>(std::move(pathFirst),std::move(pathSecond));
}

std::unique_ptr<ExprReturn> Parser::parse_expr_return() {
    if(tokens[currentPos].type != kRETURN){
        throw std::runtime_error("Wrong in expr return parsing, missing return.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> expr;
    expr = parse_expr();
    return std::make_unique<ExprReturn>(std::move(expr));
}

std::unique_ptr<ExprStruct> Parser::parse_expr_struct() {
    std::unique_ptr<ExprPath> pathInExpr;
    std::vector<StructExprField> structExprFields;
    pathInExpr = parse_expr_path();
    if(tokens[currentPos].type != kL_BRACE) {
        throw std::runtime_error("Wrong in expr struct parsing, missing L_BRACE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    StructExprField tmp;
    if(tokens[currentPos].type != kIDENTIFIER){
        throw std::runtime_error("Wrong in expr struct parsing, missing IDENTIFIER.");
    }
    tmp.identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    //TODO Left with struct expr fields parsing.
    if(tokens[currentPos].type == kCOLON) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        tmp.expr = parse_expr();
    }
    structExprFields.push_back(tmp);
    if(tokens[currentPos].type == kCOMMA) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    if(tokens[currentPos].type == kR_BRACE) {
        currentPos ++;
        return std::make_unique<ExprStruct>(std::move(pathInExpr),std::move(structExprFields));
    }
    bool flag = false;
    while(tokens[currentPos].type != kR_BRACE) {
        if(tokens[currentPos].type == kCOMMA){
            flag = true;
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kR_BRACE){
                break;
            }
        }else if(flag){
            throw std::runtime_error("Wrong in expr struct parsing, missing COMMA.");
        }
        if(tokens[currentPos].type != kIDENTIFIER){
            throw std::runtime_error("Wrong in expr struct parsing, missing IDENTIFIER.");
        }
        tmp.identifier = tokens[currentPos].value;
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type == kCOLON) {
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            tmp.expr = parse_expr();
        }
        structExprFields.push_back(tmp);
    }
    currentPos ++;
    return std::make_unique<ExprStruct>(std::move(pathInExpr),std::move(structExprFields));
}

std::unique_ptr<ExprUnderscore> Parser::parse_expr_underscore() {
    if(tokens[currentPos].type != kUNDERSCORE){
        throw std::runtime_error("Wrong in expr underscore parsing, missing UNDERSCORE.");
    }
    currentPos ++;
    return std::make_unique<ExprUnderscore>();
}
}