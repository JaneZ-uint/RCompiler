#include "parser.h"
#include <cstddef>
#include <memory>
#include <stdexcept>

namespace JaneZ {
std::unique_ptr<Item> Parser::parse_item(){
    Token current = tokens[currentPos];
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    Token next = tokens[currentPos + 1];
    switch (current.type) {
        case kFN: {
            return parse_item_fn();
        }
        case kSTRUCT: {
            return parse_item_struct();
        }
        case kENUM: {
            return parse_item_enum();
        }
        case kCONST: {
            if(next.type == kFN){
                return parse_item_fn();
            }else{
                return parse_item_const();
            }
        }
        case kTRAIT: {
            return parse_item_trait();
        }
        case kIMPL: {
            return parse_item_impl();
        }
        default: {
            throw std::runtime_error("Wrong type when parsing item.");
        }
    }
}

std::unique_ptr<ItemFnDecl> Parser::parse_item_fn() {
    bool is_const = false;
    if(tokens[currentPos].type == kCONST){
        is_const = true;
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    if(tokens[currentPos].type != kFN){
        throw std::runtime_error("Wrong format in item fn.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    std::string identifier = "";
    identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()){
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kL_PAREN) {
        throw std::runtime_error("Wrong format in item fn parsing.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
       throw std::runtime_error("End of Program.");
    }
    fnParameter param;
    if(tokens[currentPos].type == kAND){
        param.SelfParam.isShortSelf = true;
        param.SelfParam.short_self.is_and = true;
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type == kMUT){
            param.SelfParam.short_self.is_mut = true;
            currentPos ++;
        }
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kSELF){
            throw std::runtime_error("Wrong in item fn with short self.");
        }
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kCOMMA && tokens[currentPos].type != kR_PAREN){
            throw std::runtime_error("Wrong in item fn with comma missing.");
        }
        if(tokens[currentPos].type != kR_PAREN){ 
            // jump comma
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type != kR_PAREN){
                functionParam tmp;
                tmp.pattern = parse_pattern();
                if(tokens[currentPos].type != kCOLON){
                    throw std::runtime_error("Wrong in item fn with colon missing.");
                }
                currentPos ++;
                if(currentPos >= tokens.size()){
                    throw std::runtime_error("End of Program.");
                }
                tmp.type = parse_type();
                if(tokens[currentPos].type == kCOMMA){
                    currentPos ++;
                    if(currentPos >= tokens.size()){
                        throw std::runtime_error("End of Program.");
                    }
                }
                param.FunctionParam.push_back(tmp);
                while(tokens[currentPos].type != kR_PAREN){
                    functionParam tp;
                    tp.pattern = parse_pattern();
                    if(tokens[currentPos].type != kCOLON){
                        throw std::runtime_error("Wrong in item fn with colon missing.");
                    }
                    currentPos ++;
                    if(currentPos >= tokens.size()){
                        throw std::runtime_error("End of Program.");
                    }
                    tp.type = parse_type();
                    param.FunctionParam.push_back(tp);
                    if(tokens[currentPos].type == kCOMMA){
                        currentPos ++;
                        if(currentPos >= tokens.size()){
                            throw std::runtime_error("End of Program.");
                        }
                    }
                }
            }
        }
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }else{
        if(tokens[currentPos].type == kMUT){
            if(currentPos + 1 < tokens.size()){
                if(tokens[currentPos + 1].type != kSELF){
                    throw std::runtime_error("Wrong format in item fn with missing self.");
                }
                if(currentPos + 2 < tokens.size()){
                    if(tokens[currentPos + 2].type == kCOLON){
                        param.SelfParam.isShortSelf = false;
                        param.SelfParam.type_self.is_mut = true;
                        currentPos += 3;
                        param.SelfParam.type_self.type = parse_type();
                    }else{
                        param.SelfParam.isShortSelf = true;
                        param.SelfParam.short_self.is_and = false;
                        param.SelfParam.short_self.is_mut = true;
                        currentPos += 2;
                        if(currentPos >= tokens.size()){
                            throw std::runtime_error("End of Program.");
                        }
                    }
                }else{
                    throw std::runtime_error("End of Program.");
                }
            }else{
                throw std::runtime_error("End of Program.");
            }
        }else{
            if(tokens[currentPos].type != kSELF){
                throw std::runtime_error("Wrong format in item fn with missing self.");
            }
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kCOLON){
                param.SelfParam.isShortSelf = false;
                param.SelfParam.type_self.is_mut = false;
                currentPos ++;
                if(currentPos >= tokens.size()){
                    throw std::runtime_error("End of Program.");
                }
                param.SelfParam.type_self.type = parse_type();
            }else{
                param.SelfParam.isShortSelf = true;
                param.SelfParam.short_self.is_and = false;
                param.SelfParam.short_self.is_mut = false;
            }
        }
        if(tokens[currentPos].type != kCOMMA && tokens[currentPos].type != kR_PAREN){
            throw std::runtime_error("Wrong in item fn with comma missing.");
        }
        if(tokens[currentPos].type != kR_PAREN){ 
            // jump comma
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type != kR_PAREN){
                functionParam tmp;
                tmp.pattern = parse_pattern();
                if(tokens[currentPos].type != kCOLON){
                    throw std::runtime_error("Wrong in item fn with colon missing.");
                }
                currentPos ++;
                if(currentPos >= tokens.size()){
                    throw std::runtime_error("End of Program.");
                }
                tmp.type = parse_type();
                if(tokens[currentPos].type == kCOMMA){
                    currentPos ++;
                    if(currentPos >= tokens.size()){
                        throw std::runtime_error("End of Program.");
                    }
                }
                param.FunctionParam.push_back(tmp);
                while(tokens[currentPos].type != kR_PAREN){
                    functionParam tp;
                    tp.pattern = parse_pattern();
                    if(tokens[currentPos].type != kCOLON){
                        throw std::runtime_error("Wrong in item fn with colon missing.");
                    }
                    currentPos ++;
                    if(currentPos >= tokens.size()){
                        throw std::runtime_error("End of Program.");
                    }
                    tp.type = parse_type();
                    param.FunctionParam.push_back(tp);
                    if(tokens[currentPos].type == kCOMMA){
                        currentPos ++;
                        if(currentPos >= tokens.size()){
                            throw std::runtime_error("End of Program.");
                        }
                    }
                }
            }
        }
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }
    currentPos ++;
    if(currentPos >= tokens.size()){
       throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<Type> returnType = nullptr;
    if(tokens[currentPos].type != kL_PAREN){
        //exist fn return type
        if(tokens[currentPos].type != kRARROW){
            throw std::runtime_error("Wrong format with item fn return type.");
        }
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
        returnType = parse_type();
    }
    if(tokens[currentPos].type != kL_PAREN){
        throw std::runtime_error("Wrong format with item fn body.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::unique_ptr<ExprBlock> fnBody = nullptr;
    if(tokens[currentPos].type == kSEMI){
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
    }else{
        fnBody = parse_expr_block();
    }
    if(tokens[currentPos].type != kR_PAREN){
        throw std::runtime_error("Wrong format with item fn body.");
    }
    return std::make_unique<ItemFnDecl>(std::move(identifier),std::move(param),std::move(fnBody),std::move(returnType),is_const);
}

std::unique_ptr<ItemConstDecl> Parser::parse_item_const() {

}

std::unique_ptr<ItemEnumDecl> Parser::parse_item_enum() {

}

std::unique_ptr<ItemImplDecl> Parser::parse_item_impl() {

}

std::unique_ptr<ItemStructDecl> Parser::parse_item_struct() {

}

std::unique_ptr<ItemTraitDecl> Parser::parse_item_trait() {
    
}

}