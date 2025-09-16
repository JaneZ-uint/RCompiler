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
    //{kSTAR,{0,22}},
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

    {kL_PAREN,{23,0}},
    {kL_BRACE,{23,0}}, //TODO Wait and see.
    {kL_BRACKET,{23,0}},
    {kDOT,{23,0}},
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

int Parser::getLeftpower(tokenType type) {
    if(bindingPowerMap.find(type) != bindingPowerMap.end()) {
        return bindingPowerMap.find(type)->second.leftPower;
    }
    return -1;
}

int Parser::getRightpower(tokenType type) {
    if(bindingPowerMap.find(type) != bindingPowerMap.end()) {
        return bindingPowerMap.find(type)->second.rightPower;
    }
    return -1;
}

std::shared_ptr<Expression> Parser::parse_expr() {
    return parse_expr_interface(0);
}

std::shared_ptr<Expression> Parser::parse_expr_interface(int power) {
    //size_t originPos = currentPos;
    std::shared_ptr<Expression> left = parse_expr_prefix();
    while(true) {
        if(currentPos == tokens.size()){
            break;
        }
        Token current = tokens[currentPos];
        if(getLeftpower(current.type) <= power) {
            break;
        }
        left = parse_expr_infix(std::move(left));
    }
    return left;
}

std::shared_ptr<Expression> Parser::parse_expr_prefix() {
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

std::shared_ptr<Expression> Parser::parse_expr_infix(std::shared_ptr<Expression> &&firstExpr) {
    //size_t originPos = currentPos;
    //std::shared_ptr<Expression> firstExpr;
    //firstExpr = parse_expr();
    switch (tokens[currentPos].type) {
        case kL_BRACKET: {
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            std::shared_ptr<Expression> index;
            index = parse_expr();
            if(tokens[currentPos].type != kR_BRACKET) {
                throw std::runtime_error("Wrong in expr index parsing, missing kR_BRACKET.");
            }
            currentPos ++;
            return std::make_shared<ExprIndex>(std::move(firstExpr),std::move(index));
        }
        case kL_BRACE: {
            //currentPos = originPos;
            return parse_expr_struct(std::move(firstExpr));
        }
        case kL_PAREN: {
            //currentPos = originPos;
            return parse_expr_call(std::move(firstExpr));
        }
        case kDOT: {
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kSELF || tokens[currentPos].type == kSELF) {
                //currentPos = originPos;
                return parse_expr_methodcall(std::move(firstExpr));
            }
            if(tokens[currentPos].type != kIDENTIFIER) {
                throw std::runtime_error("Wrong in expr infix parsing, missing identifier.");
            }
            currentPos ++;
            if(currentPos == tokens.size()) {
                currentPos -= 2;
                return parse_expr_field(std::move(firstExpr));
            }
            if(tokens[currentPos].type == kL_PAREN) {
                //currentPos = originPos;
                currentPos --;
                return parse_expr_methodcall(std::move(firstExpr));
            }
            currentPos -= 2;
            return parse_expr_field(std::move(firstExpr));
        }
        default:;
    }
    //currentPos ++;
    tokenType type = tokens[currentPos].type;
    currentPos ++;
    std::shared_ptr<Expression> right = parse_expr_interface(getRightpower(type));
    return std::make_shared<ExprOpbinary>(std::move(firstExpr),getBinaryOp(type),std::move(right));
}

std::shared_ptr<ExprArray> Parser::parse_expr_array() {
    if(tokens[currentPos].type != kL_BRACKET){
        throw std::runtime_error("Wrong in expr array parsing, missing L_BRACKET.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Expression> type;
    std::shared_ptr<Expression> size;
    std::shared_ptr<Expression> expr = nullptr;
    std::vector<std::shared_ptr<Expression>> arrayExpr;
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
        return std::make_shared<ExprArray>(std::move(type),std::move(size));
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
        return std::make_shared<ExprArray>(std::move(arrayExpr));
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
        std::shared_ptr<Expression> tmp;
        tmp = parse_expr();
        arrayExpr.push_back(std::move(tmp));
    }
    currentPos ++;
    return std::make_shared<ExprArray>(std::move(arrayExpr));
}

std::shared_ptr<ExprBlock> Parser::parse_expr_block() {
    if(tokens[currentPos].type != kL_BRACE){
        throw std::runtime_error("Wrong in expr block parsing, missing L_BRACE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::vector<std::shared_ptr<Statement>> statements;
    std::shared_ptr<Expression> ExpressionWithoutBlock;
    std::shared_ptr<Statement> tmp;
    bool isExprBlock = false;
    size_t ptr = currentPos;
    size_t bracePair = 1;
    bool isBracket = false;
    while(true){
        if(tokens[ptr].type == kR_BRACE){
            bracePair --;
        }else if(tokens[ptr].type == kL_BRACE){
            bracePair ++;
        }else if(tokens[ptr].type == kL_BRACKET){
            isBracket = true;
        }else if(tokens[ptr].type == kR_BRACKET) {
            if(isBracket) {
                isBracket = false;
            }
        }
        if(bracePair == 0){
            isExprBlock = true;
            break;
        }
        if(tokens[ptr].type == kSEMI) {
            if(!isBracket) {
                break;
            }
        }
        ptr ++;
    }
    if(isExprBlock){
        ExpressionWithoutBlock = parse_expr();
        if(tokens[currentPos].type != kR_BRACE){
            throw std::runtime_error("Wrong in expr block parsing, missing R_BRACE.");
        }
        currentPos ++;
        return std::make_shared<ExprBlock>(std::move(statements),std::move(ExpressionWithoutBlock));
    }
    int lastSemi = -1;
    size_t pos = currentPos;
    int pair = 1;
    isBracket = false;
    while(true) {
        if(tokens[pos].type == kR_BRACE) {
            pair --;
            if(pair == 1){
                lastSemi = pos;
            }
        }else if(tokens[pos].type == kL_BRACE) {
            pair ++;
        }else if(tokens[pos].type == kL_BRACKET){
            isBracket = true;
        }else if(tokens[pos].type == kR_BRACKET) {
            if(isBracket) {
                isBracket = false;
            }
        }else if(!isBracket && tokens[pos].type == kSEMI) {
            lastSemi = pos;
        }
        if(pair == 0){
            break;
        }
        pos ++;
    }
    if(lastSemi == pos - 1){
        while(tokens[currentPos].type != kR_BRACE){
            tmp = parse_statement();
            statements.push_back(std::move(tmp));
        }
    }else{
        while(tokens[currentPos].type != kR_BRACE){
            if(currentPos == lastSemi + 1){
                ExpressionWithoutBlock = parse_expr();
                continue;
            }
            tmp = parse_statement();
            statements.push_back(std::move(tmp));
        }
    }
    if(tokens[currentPos].type != kR_BRACE){
        throw std::runtime_error("Wrong in expr block parsing, missing R_BRACE.");
    }
    currentPos ++;
    return std::make_shared<ExprBlock>(std::move(statements),std::move(ExpressionWithoutBlock));
}

std::shared_ptr<ExprBreak> Parser::parse_expr_break() {
    if(tokens[currentPos].type != kBREAK){
        throw std::runtime_error("Wrong in expr break parsing, missing BREAK.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Expression> expr = nullptr;
    if(tokens[currentPos].type == kSEMI){
        //currentPos ++;
        return std::make_shared<ExprBreak>(std::move(expr));
    }
    expr = parse_expr();
    if(tokens[currentPos].type != kSEMI){
        throw std::runtime_error("Wrong in expr break parsing, missing SEMI.");
    }
    //currentPos ++;
    return std::make_shared<ExprBreak>(std::move(expr));
}

std::shared_ptr<ExprCall> Parser::parse_expr_call(std::shared_ptr<Expression> &&expr) {
    //std::shared_ptr<Expression> expr;
    std::vector<std::shared_ptr<Expression>> callParams;
    //expr = parse_expr();
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in expr call parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Expression> tmp;
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
        return std::make_shared<ExprCall>(std::move(expr),std::move(callParams));
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
    return std::make_shared<ExprCall>(std::move(expr),std::move(callParams));
}

std::shared_ptr<ExprConstBlock> Parser::parse_expr_constblock() {
    if(tokens[currentPos].type != kCONST){
        throw std::runtime_error("Wrong in expr constblock parsing, missing CONST.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<ExprBlock> expr;
    expr = parse_expr_block();
    return std::make_shared<ExprConstBlock>(std::move(expr));
}

std::shared_ptr<ExprContinue> Parser::parse_expr_continue() {
    if(tokens[currentPos].type != kCONTINUE){
        throw std::runtime_error("Wrong in expr continue parsing, missing CONTINUE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    return std::make_shared<ExprContinue>();
}

std::shared_ptr<ExprField> Parser::parse_expr_field(std::shared_ptr<Expression> &&expr) {
    //std::shared_ptr<Expression> expr;
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
    return std::make_shared<ExprField>(std::move(expr),std::move(identifier));
}

std::shared_ptr<ExprGroup> Parser::parse_expr_group() {
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in expr group parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Expression> expr;
    expr = parse_expr();
    if(tokens[currentPos].type != kR_PAREN){
        throw std::runtime_error("Wrong in expr group parsing, missing R_PAREN.");
    }
    currentPos ++;
    return std::make_shared<ExprGroup>(std::move(expr));
}

std::shared_ptr<ExprIf> Parser::parse_expr_if() {
    if(tokens[currentPos].type != kIF){
        throw std::runtime_error("Wrong in expr if parsing, missing IF.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Expression> condition = nullptr;
    std::shared_ptr<ExprBlock> thenBlock = nullptr;
    std::shared_ptr<Expression> elseBlock = nullptr;
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
        return std::make_shared<ExprIf>(std::move(condition),std::move(thenBlock),std::move(elseBlock));
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    elseBlock = parse_expr();
    return std::make_shared<ExprIf>(std::move(condition),std::move(thenBlock),std::move(elseBlock));
}

std::shared_ptr<ExprLiteral> Parser::parse_expr_literal() {
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
    return std::make_shared<ExprLiteral>(std::move(literal),type);
}

std::shared_ptr<ExprLoop> Parser::parse_expr_loop() {
    std::shared_ptr<ExprBlock> infinitieLoop;
    std::shared_ptr<Expression> condition;
    std::shared_ptr<ExprBlock> PredicateLoopExpression;
    if(tokens[currentPos].type == kLOOP){
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        infinitieLoop = parse_expr_block();
        return std::make_shared<ExprLoop>(std::move(infinitieLoop));
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
        return std::make_shared<ExprLoop>(std::move(condition),std::move(PredicateLoopExpression));
    }else {
        throw std::runtime_error("Wrong in expr loop parsing, missing LOOP or WHILE.");
    }
}

std::shared_ptr<ExprMethodcall> Parser::parse_expr_methodcall(std::shared_ptr<Expression> &&expr) {
    //std::shared_ptr<Expression> expr;
    std::shared_ptr<Path> PathExprSegment;
    std::vector<std::shared_ptr<Expression>> callParams;
    //expr = parse_expr();
    /*if(tokens[currentPos].type != kDOT){
        throw std::runtime_error("Wrong in expr methodcall parsing, missing DOT.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }*/
    PathExprSegment = parse_path();
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in expr methodcall parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type == kR_PAREN){
        currentPos ++;
        return std::make_shared<ExprMethodcall>(std::move(expr),std::move(PathExprSegment),std::move(callParams));
    }
    std::shared_ptr<Expression> tmp;
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
        return std::make_shared<ExprMethodcall>(std::move(expr),std::move(PathExprSegment),std::move(callParams));
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
    return std::make_shared<ExprMethodcall>(std::move(expr),std::move(PathExprSegment),std::move(callParams));
}


std::shared_ptr<ExprOpunary> Parser::parse_expr_opunary() {
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
    std::shared_ptr<Expression> right = nullptr;
    right = parse_expr();
    return std::make_shared<ExprOpunary>(op, right, is_mut);
}

std::shared_ptr<ExprPath> Parser::parse_expr_path() {
    std::shared_ptr<Path> pathFirst = nullptr;
    std::shared_ptr<Path> pathSecond = nullptr;
    pathFirst = parse_path();
    if(tokens[currentPos].type == kPATHSEP){
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        pathSecond = parse_path();
        return std::make_shared<ExprPath>(std::move(pathFirst),std::move(pathSecond));
    }
    return std::make_shared<ExprPath>(std::move(pathFirst),std::move(pathSecond));
}

std::shared_ptr<ExprReturn> Parser::parse_expr_return() {
    if(tokens[currentPos].type != kRETURN){
        throw std::runtime_error("Wrong in expr return parsing, missing return.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Expression> expr;
    expr = parse_expr();
    return std::make_shared<ExprReturn>(std::move(expr));
}

std::shared_ptr<ExprStruct> Parser::parse_expr_struct(std::shared_ptr<Expression> &&pathInExpr) {
    //std::shared_ptr<ExprPath> pathInExpr;
    std::vector<StructExprField> structExprFields;
    //pathInExpr = parse_expr_path();
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
    structExprFields.push_back(std::move(tmp));
    if(tokens[currentPos].type == kCOMMA) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    if(tokens[currentPos].type == kR_BRACE) {
        currentPos ++;
        return std::make_shared<ExprStruct>(std::move(pathInExpr),std::move(structExprFields));
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
        structExprFields.push_back(std::move(tmp));
    }
    currentPos ++;
    return std::make_shared<ExprStruct>(std::move(pathInExpr),std::move(structExprFields));
}

std::shared_ptr<ExprUnderscore> Parser::parse_expr_underscore() {
    if(tokens[currentPos].type != kUNDERSCORE){
        throw std::runtime_error("Wrong in expr underscore parsing, missing UNDERSCORE.");
    }
    currentPos ++;
    return std::make_shared<ExprUnderscore>();
}
}