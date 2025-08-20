# include "parser.h"
# include "../token/token.h"
# include "../ast/Pattern/PatternPath.h"
# include "../ast/Pattern/PatternTupleStruct.h"
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

namespace JaneZ {
std::unique_ptr<Pattern> Parser::parse_pattern() {
    Token current = tokens[currentPos];
    switch (current.type) {
        case kINTEGER_LITERAL:
        case kCHAR_LITERAL:
        case kSTRING_LITERAL:
        case kRAW_STRING_LITERAL:
        case kCSTRING_LITERAL:
        case kRAW_CSTRING_LITERAL: {
            return parse_pattern_literal();
        }
        case kIDENTIFIER: {
            return parse_pattern_identifier();
        }
        case kAND:
        case kANDAND: {
            return parse_pattern_reference();
        }
        case kUNDERSCORE: {
            return parse_pattern_wildcard();
        }
        case kPATHSEP: {
            // include path tuple struct
            return parse_pattern_path();
        }
        default: {
            throw std::runtime_error("Wrong in pattern type.");
        }
    }
}

std::unique_ptr<PatternIdentifier> Parser::parse_pattern_identifier() {
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
    std::unique_ptr<Pattern> pattern = parse_pattern();
    return std::make_unique<PatternIdentifier>(std::move(identifier),std::move(pattern),is_ref,is_mut);
}

std::unique_ptr<PatternLiteral> Parser::parse_pattern_literal() {
    std::unique_ptr<ExprLiteral> res = parse_expr_literal();
    return std::make_unique<PatternLiteral>(tokens[currentPos].value,std::move(res));
}

std::unique_ptr<Pattern> Parser::parse_pattern_path() {
    std::unique_ptr<Path> pathInExpr = parse_path();
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type == kL_PAREN) {
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        std::vector<std::unique_ptr<Pattern>> TupleStructItems;
        do{
            if(currentPos == tokens.size()) {
                throw std::runtime_error("End of Program.");
            }
            std::unique_ptr<Pattern> pattern = parse_pattern();
            TupleStructItems.push_back(std::move(pattern));
            if(currentPos >= tokens.size()) {
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kCOMMA){
                currentPos ++;
                if(currentPos >= tokens.size()){
                    throw std::runtime_error("End of Program.");
                }
            }
        }while(tokens[currentPos].type != kR_PAREN);
        currentPos ++;
        return std::make_unique<PatternTupleStruct>(std::move(pathInExpr),std::move(TupleStructItems)) ;
    }else{
        return std::make_unique<PatternPath>(std::move(pathInExpr));
    }
}

std::unique_ptr<PatternReference> Parser::parse_pattern_reference() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
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
    std::unique_ptr<Pattern> pattern = parse_pattern();
    return std::make_unique<PatternReference>(std::move(pattern),is_mut);
}

/*std::unique_ptr<PatternStruct> Parser::parse_pattern_struct() {

}*/

/*std::unique_ptr<PatternTuple> Parser::parse_pattern_tuple_struct() {

}*/

std::unique_ptr<PatternWildCard> Parser::parse_pattern_wildcard() {
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<ExprUnderscore> expr = parse_expr_underscore();
    return std::make_unique<PatternWildCard>(std::move(expr));
}

}