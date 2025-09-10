# include "parser.h"
# include "../token/token.h"
# include "../ast/Pattern/PatternPath.h"
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace JaneZ {
std::shared_ptr<Pattern> Parser::parse_pattern() {
    Token current = tokens[currentPos];
    switch (current.type) {
        case kMINUS:
        case kINTEGER_LITERAL:
        case kCHAR_LITERAL:
        case kSTRING_LITERAL:
        case kRAW_STRING_LITERAL:
        case kCSTRING_LITERAL:
        case kRAW_CSTRING_LITERAL: {
            return parse_pattern_literal();
        }
        case kMUT:
        case kREF: {
            return parse_pattern_identifier();
        }
        case kSELF_TYPE:
        case kSELF: {
            return parse_pattern_path();
        }

        case kIDENTIFIER: {
            // identifier / path /  maybe a problem here.
            return parse_pattern_identifier();
        }
        case kAND:
        case kANDAND: {
            return parse_pattern_reference();
        }
        case kUNDERSCORE: {
            return parse_pattern_wildcard();
        }

        default: {
            throw std::runtime_error("Wrong in pattern type.");
        }
    }
}

std::shared_ptr<PatternIdentifier> Parser::parse_pattern_identifier() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    bool is_ref = false;
    bool is_mut = false;
    if(tokens[currentPos].type == kREF){
        is_ref = true;
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    if(tokens[currentPos].type == kMUT){
        is_mut = true;
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    std::string identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    //std::shared_ptr<Pattern> pattern = parse_pattern();
    return std::make_shared<PatternIdentifier>(std::move(identifier),is_ref,is_mut);
}

std::shared_ptr<PatternLiteral> Parser::parse_pattern_literal() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    bool isMinus = false;
    if(tokens[currentPos].type == kMINUS) {
        isMinus = true;
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<ExprLiteral> res = parse_expr_literal();
    return std::make_shared<PatternLiteral>(isMinus,std::move(res));
}

std::shared_ptr<PatternPath> Parser::parse_pattern_path() {
    std::shared_ptr<ExprPath> pathInExpr = parse_expr_path();
    return std::make_shared<PatternPath>(std::move(pathInExpr));
}

std::shared_ptr<PatternReference> Parser::parse_pattern_reference() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    bool isANDAND = false;
    if(tokens[currentPos].type == kANDAND){
        isANDAND = true;
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    bool is_mut = false;
    if(tokens[currentPos].type == kMUT){
        is_mut = true;
        currentPos ++;
        if(currentPos >= tokens.size()) { 
            throw std::runtime_error("End of Program.");
        }
    }
    std::shared_ptr<Pattern> pattern = parse_pattern();
    return std::make_shared<PatternReference>(std::move(pattern),isANDAND,is_mut);
}

/*std::shared_ptr<PatternStruct> Parser::parse_pattern_struct() {

}*/

/*std::shared_ptr<PatternTuple> Parser::parse_pattern_tuple_struct() {

}*/

std::shared_ptr<PatternWildCard> Parser::parse_pattern_wildcard() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<ExprUnderscore> expr = parse_expr_underscore();
    return std::make_shared<PatternWildCard>(std::move(expr));
}

}