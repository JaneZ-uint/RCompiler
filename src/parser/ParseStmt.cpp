# include "parser.h"
# include "../token/token.h"
#include <memory>

namespace JaneZ {
std::unique_ptr<Statement> Parser::parse_statement() {
    Token current = tokens[currentPos];
    switch (current.type) {
        case kSEMI: {
            return parse_stmt_empty(current);
        }
        case kFN:
        case kSTRUCT:
        case kENUM:
        case kCONST:
        case kTRAIT:
        case kIMPL: {
            return parse_stmt_item(current);
        }
        case kLET: {
            return parse_stmt_let(current);
        }
        default:
            return parse_stmt_expr(current);
    }
}

std::unique_ptr<StmtEmpty> Parser::parse_stmt_empty(Token current) {
    currentPos ++;
    return std::make_unique<StmtEmpty>();
}

std::unique_ptr<StmtItem> Parser::parse_stmt_item(Token current) {
    
}

std::unique_ptr<StmtLet> Parser::parse_stmt_let(Token current){

}

std::unique_ptr<StmtExpr> Parser::parse_stmt_expr(Token current) {

}

}