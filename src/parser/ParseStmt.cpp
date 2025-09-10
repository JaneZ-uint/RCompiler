# include "parser.h"
# include "../token/token.h"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

namespace JaneZ {
std::shared_ptr<Statement> Parser::parse_statement() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    Token current = tokens[currentPos];
    switch (current.type) {
        case kSEMI: {
            return parse_stmt_empty();
        }
        case kFN:
        case kSTRUCT:
        case kENUM:
        case kCONST:
        case kTRAIT:
        case kIMPL: {
            return parse_stmt_item();
        }
        case kLET: {
            return parse_stmt_let();
        }
        default:
            return parse_stmt_expr();
    }
}

std::shared_ptr<StmtEmpty> Parser::parse_stmt_empty() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    currentPos ++;
    return std::make_shared<StmtEmpty>();
}

std::shared_ptr<StmtItem> Parser::parse_stmt_item() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    Token current = tokens[currentPos];
    std::shared_ptr<Item> stmt_item = nullptr;
    switch (current.type) {
        case kFN: 
        case kSTRUCT:
        case kENUM: 
        case kCONST:
        case kTRAIT: 
        case kIMPL: {
            stmt_item = parse_item();
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            //problem here!
            /*currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type != kSEMI) {
                throw std::runtime_error("Wrong in stmt parsing, missing semi.");
            }
            currentPos ++;*/
            break;
        }   
        default:{
            break;
        }
    }
    return std::make_shared<StmtItem>(std::move(stmt_item));
}

std::shared_ptr<StmtLet> Parser::parse_stmt_let(){
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Pattern> pattern = parse_pattern();
    std::shared_ptr<ASTNode> type = nullptr;
    if (tokens[currentPos].type == kCOLON) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        type = parse_type();
    }else{
        throw std::runtime_error("Wring in stmt let parsing, missing type.");
    }
    std::shared_ptr<Expression> expr = nullptr;
    if(tokens[currentPos].type == kEQ) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        expr = parse_expr();
    }
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kSEMI) {
        throw std::runtime_error("Wrong in stmt parsing, missing semi.");
    }
    currentPos ++;
    return std::make_shared<StmtLet>(std::move(pattern),std::move(type),std::move(expr));
}

std::shared_ptr<StmtExpr> Parser::parse_stmt_expr() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<Expression> expr = parse_expr();
    if(auto *p = dynamic_cast<ExprArray *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprBreak *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprCall *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprContinue *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprField *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprGroup *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprIndex *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprLiteral *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprMethodcall *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprOpbinary *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprOpunary *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprPath *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprReturn *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else if(auto *p = dynamic_cast<ExprUnderscore *>(& *expr)) {
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSEMI) {
            throw std::runtime_error("Wrong in stmt parsing, missing semi.");
        }
        currentPos ++;
    }else{
        if(currentPos < tokens.size()){
            if(tokens[currentPos].type == kSEMI) {
                currentPos ++;
            }
        }
    }
    return std::make_shared<StmtExpr>(std::move(expr));
}

}