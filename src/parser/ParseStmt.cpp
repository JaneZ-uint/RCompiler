# include "parser.h"
# include "../token/token.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace JaneZ {
std::unique_ptr<Statement> Parser::parse_statement() {
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

std::unique_ptr<StmtEmpty> Parser::parse_stmt_empty() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    currentPos ++;
    return std::make_unique<StmtEmpty>();
}

std::unique_ptr<StmtItem> Parser::parse_stmt_item() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    Token current = tokens[currentPos];
    switch (current.type) {
        case kFN: 
        case kSTRUCT:
        case kENUM: 
        case kCONST:
        case kTRAIT: 
        case kIMPL: {
            return std::make_unique<StmtItem>(parse_item());
        }   
    }
}

std::unique_ptr<StmtLet> Parser::parse_stmt_let(){
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Pattern> pattern = parse_pattern();
    std::unique_ptr<Type> type = nullptr;
    if (tokens[currentPos].type == kCOLON) {
        type = parse_type();
    }
    std::unique_ptr<Expression> expr = nullptr;
    if(tokens[currentPos].type == kEQ) {
        expr = parse_expr();
    }
    return std::make_unique<StmtLet>(std::move(pattern),std::move(type),std::move(expr));
    
}

std::unique_ptr<StmtExpr> Parser::parse_stmt_expr() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Expression> expr = parse_expr();
    if(tokens[currentPos].type == kSEMI){
        currentPos ++;
    }
    return std::make_unique<StmtExpr>(std::move(expr));
}

}