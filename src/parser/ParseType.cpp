#include "parser.h"
#include <memory>
#include <stdexcept>

namespace JaneZ {
std::shared_ptr<ASTNode> Parser::parse_type() {
    if(tokens[currentPos].value == "bool"){
        currentPos ++;
        return std::make_shared<Type>(BOOL);
    }else if(tokens[currentPos].value == "u32"){
        currentPos ++;
        return std::make_shared<Type>(U32);
    }else if(tokens[currentPos].value == "i32"){
        currentPos ++;
        return std::make_shared<Type>(I32);
    }else if(tokens[currentPos].value == "usize"){
        currentPos ++;
        return std::make_shared<Type>(USIZE);
    }else if(tokens[currentPos].value == "isize"){
        currentPos ++;
        return std::make_shared<Type>(ISIZE);
    }else if(tokens[currentPos].value == "char"){
        currentPos ++;
        return std::make_shared<Type>(CHAR);
    }else if(tokens[currentPos].value == "str"){
        currentPos ++;
        return std::make_shared<Type>(STR);
    }else if(tokens[currentPos].value == "enum"){
        currentPos ++;
        return std::make_shared<Type>(ENUM);
    }else if(tokens[currentPos].type == kL_BRACKET){
        return parse_type_array();
    }else if(tokens[currentPos].type == kAND){
        return parse_type_reference();
    }else if(tokens[currentPos].type == kIDENTIFIER){
        return parse_path();
    }else if(tokens[currentPos].type == kSELF_TYPE){
        return parse_path();
    }else if(tokens[currentPos].type == kSELF){
        return parse_path();
    }else if(tokens[currentPos].type == kL_PAREN){
        return parse_type_unit();
    }else{
        throw std::runtime_error("Wrong type in type parsing.");
    }
}

std::shared_ptr<TypeArray> Parser::parse_type_array() {
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<ASTNode> type = nullptr;
    std::shared_ptr<Expression> expr = nullptr;
    type = parse_type();
    if(tokens[currentPos].type != kSEMI){
        throw std::runtime_error("Wrong in type array parsing, missing semi.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    expr = parse_expr();
    if(tokens[currentPos].type != kR_BRACKET){
        throw std::runtime_error("Wrong in type array parsing, missing R_BRACKET.");
    }
    currentPos ++;
    return std::make_shared<TypeArray>(std::move(type),std::move(expr));
}

std::shared_ptr<TypeReference> Parser::parse_type_reference() {
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    bool is_mut = false;
    if(tokens[currentPos].type == kMUT){
        is_mut = true;
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    std::shared_ptr<ASTNode> typeNoBounds = nullptr;
    typeNoBounds = parse_type();
    return std::make_shared<TypeReference>(std::move(typeNoBounds),std::move(is_mut));
}

std::shared_ptr<TypeUnit> Parser::parse_type_unit() {
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong in type unit parsing, missing L_PAREN.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kR_PAREN) {
        throw std::runtime_error("Wrong in type unit parsing, missing R_PAREN.");
    }
    currentPos ++;
    return std::shared_ptr<TypeUnit>();
}

}