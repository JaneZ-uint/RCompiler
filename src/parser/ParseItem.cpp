#include "parser.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace JaneZ {
std::shared_ptr<Item> Parser::parse_item(){
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

std::shared_ptr<ItemFnDecl> Parser::parse_item_fn() {
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
    bool isStraightParam = false;
    if(tokens[currentPos].type == kR_PAREN){
        currentPos ++;
        if(currentPos >= tokens.size()){
            throw std::runtime_error("End of Program.");
        }
    }else{
        // 属于 SelfParam -- ShorthandSelf
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
                    param.FunctionParam.push_back(std::move(tmp));
                    bool flag = false;
                    while(tokens[currentPos].type != kR_PAREN){
                        if(tokens[currentPos].type == kCOMMA){
                            flag = true;
                            currentPos ++;
                            if(currentPos >= tokens.size()){
                                throw std::runtime_error("End of Program.");
                            }
                            if(tokens[currentPos].type == kR_PAREN) {
                                break;
                            }
                        }else if(flag){
                            throw std::runtime_error("Wrong in item fn with comma missing.");
                        }
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
                        param.FunctionParam.push_back(std::move(tp)); 
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
                if(tokens[currentPos].type == kSELF){
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
                }else{
                    isStraightParam = true;
                }
            }
            if(tokens[currentPos].type != kCOMMA && tokens[currentPos].type != kR_PAREN && !isStraightParam){
                throw std::runtime_error("Wrong in item fn with comma missing.");
            }
            if(tokens[currentPos].type == kCOMMA){ 
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
                    param.FunctionParam.push_back(std::move(tmp));
                    bool flag = false;
                    while(tokens[currentPos].type != kR_PAREN){
                        if(tokens[currentPos].type == kCOMMA){
                            flag = true;
                            currentPos ++;
                            if(currentPos >= tokens.size()){
                                throw std::runtime_error("End of Program.");
                            }
                            if(tokens[currentPos].type == kR_PAREN) {
                                break;
                            }
                        }else if(flag){
                            throw std::runtime_error("Wrong in item fn with comma missing.");
                        }
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
                        param.FunctionParam.push_back(std::move(tp));
                    }
                }
            }else if(isStraightParam){
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
                param.FunctionParam.push_back(std::move(tmp));
                bool flag = false;
                while(tokens[currentPos].type != kR_PAREN){
                    if(tokens[currentPos].type == kCOMMA){
                        flag = true;
                        currentPos ++;
                        if(currentPos >= tokens.size()){
                            throw std::runtime_error("End of Program.");
                        }
                        if(tokens[currentPos].type == kR_PAREN) {
                            break;
                        }
                    }else if(flag){
                        throw std::runtime_error("Wrong in item fn with comma missing.");
                    }
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
                    param.FunctionParam.push_back(std::move(tp));
                }
            }
            currentPos ++;
            if(currentPos >= tokens.size()){
                throw std::runtime_error("End of Program.");
            }
        }
    }

    std::shared_ptr<ASTNode> returnType = nullptr;
    if(tokens[currentPos].type != kL_BRACE){
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
    if(tokens[currentPos].type != kL_BRACE){
        throw std::runtime_error("Wrong format with item fn body.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<ExprBlock> fnBody = nullptr;
    if(tokens[currentPos].type == kSEMI){
        currentPos ++;
    }else{
        currentPos --;
        fnBody = parse_expr_block();
    }
    return std::make_shared<ItemFnDecl>(std::move(identifier),std::move(param),std::move(fnBody),std::move(returnType),is_const);
}

std::shared_ptr<ItemConstDecl> Parser::parse_item_const() {
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kIDENTIFIER){
        throw std::runtime_error("Wrong in item const parsing, missing identifier.");
    }
    std::string identifier = "";
    identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kCOLON){
        throw std::runtime_error("Wrong in item const parsing, missing colon.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::shared_ptr<ASTNode> type;
    std::shared_ptr<Expression> expr = nullptr;
    type = parse_type();
    if(tokens[currentPos].type == kSEMI){
        currentPos ++;
        return std::make_shared<ItemConstDecl>(std::move(identifier),std::move(type),std::move(expr));
    }
    if(tokens[currentPos].type != kEQ){
        throw std::runtime_error("Wrong in item const parsing, missing EQ.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    expr = parse_expr();
    if(tokens[currentPos].type != kSEMI){
        throw std::runtime_error("Wrong in item const parsing, missing SEMI.");
    }
    currentPos ++;
    return std::make_shared<ItemConstDecl>(std::move(identifier),std::move(type),std::move(expr));
}

std::shared_ptr<ItemEnumDecl> Parser::parse_item_enum() {
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kIDENTIFIER){
        throw std::runtime_error("Wrong in item enum parsing, missing identifier.");
    }
    std::string identifier = "";
    identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kL_BRACE){
        throw std::runtime_error("Wrong in item enum parsing, missing L_BRACE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::vector<std::string> item_enum;
    if(tokens[currentPos].type == kR_BRACE){
        currentPos ++;
        return std::make_shared<ItemEnumDecl>(std::move(identifier),std::move(item_enum));
    }
    std::string tmp = "";
    if(tokens[currentPos].type != kIDENTIFIER){
        throw std::runtime_error("Wrong in item enum parsing, missing IDENTIFIER.");
    }
    tmp = tokens[currentPos].value;
    item_enum.push_back(tmp);
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kCOMMA && tokens[currentPos].type != kR_BRACE){
        throw std::runtime_error("Wrong in item enum parsing.");
    }
    if(tokens[currentPos].type == kCOMMA){
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
    }
    bool flag = false;
    while(tokens[currentPos].type != kR_BRACE){
        if(tokens[currentPos].type != kIDENTIFIER && tokens[currentPos].type != kCOMMA){
            throw std::runtime_error("Wrong in item enum parsing, missing identifier or comma.");
        }
        if(tokens[currentPos].type == kCOMMA){
            flag = true;
            currentPos ++;
            if(currentPos >= tokens.size()) {
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kR_BRACE) {
                break;
            }
        }else if(flag){
            throw std::runtime_error("Wrong in item enum parsing, missing comma.");
        }
        if(tokens[currentPos].type != kIDENTIFIER){
            throw std::runtime_error("Wrong in item enum parsing, missing identifier.");
        }
        item_enum.push_back(tokens[currentPos].value);
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
    }
    currentPos ++;
    return std::make_shared<ItemEnumDecl>(std::move(identifier),std::move(item_enum));
}

std::shared_ptr<ItemImplDecl> Parser::parse_item_impl() {
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::string identifier = "";
    std::shared_ptr<ASTNode> targetType;
    std::vector<std::shared_ptr<ItemConstDecl>> item_trait_const;
    std::vector<std::shared_ptr<ItemFnDecl>> item_trait_fn;
    // first : TraitImpl
    bool isTraitImpl = false;
    if(tokens[currentPos].type == kIDENTIFIER){
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type == kFOR){
            isTraitImpl = true;
        }else{
            currentPos --;
        }
        if(isTraitImpl){
            currentPos ++;
            if(currentPos >= tokens.size()) {
                throw std::runtime_error("End of Program.");
            }
            targetType = parse_type();
            if(tokens[currentPos].type != kL_BRACE){
                throw std::runtime_error("Wrong in item impl parsing, missing L_BRACE.");
            }
            currentPos ++;
            if(currentPos >= tokens.size()) {
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kR_BRACE){
                currentPos ++;
                return std::make_shared<ItemImplDecl>(std::move(identifier),std::move(targetType),std::move(item_trait_const),std::move(item_trait_fn));
            }
            while(tokens[currentPos].type != kR_BRACE){
                std::shared_ptr<ItemConstDecl> tmpConst = nullptr;
                std::shared_ptr<ItemFnDecl> tmpFn = nullptr;
                if(tokens[currentPos].type == kCONST){
                    tmpConst = parse_item_const();
                    item_trait_const.push_back(std::move(tmpConst));
                }else if(tokens[currentPos].type == kFN){
                    tmpFn = parse_item_fn();
                    item_trait_fn.push_back(std::move(tmpFn));
                }else{
                    throw std::runtime_error("Wrong in item trait parsing, missing AssociatedItem.");
                }
            }
            currentPos ++;
            return std::make_shared<ItemImplDecl>(std::move(identifier),std::move(targetType),std::move(item_trait_const),std::move(item_trait_fn));
        }
    }
    //second : InherentImpl
    targetType = parse_type();
    if(tokens[currentPos].type != kL_BRACE){
        throw std::runtime_error("Wrong in item impl parsing, missing L_BRACE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type == kR_BRACE){
        currentPos ++;
        return std::make_shared<ItemImplDecl>(std::move(identifier),std::move(targetType),std::move(item_trait_const),std::move(item_trait_fn));
    }
    while(tokens[currentPos].type != kR_BRACE){
        std::shared_ptr<ItemConstDecl> tmpConst = nullptr;
        std::shared_ptr<ItemFnDecl> tmpFn = nullptr;
        if(tokens[currentPos].type == kCONST){
            tmpConst = parse_item_const();
            item_trait_const.push_back(std::move(tmpConst));
        }else if(tokens[currentPos].type == kFN){
            tmpFn = parse_item_fn();
            item_trait_fn.push_back(std::move(tmpFn));
        }else{
            throw std::runtime_error("Wrong in item trait parsing, missing AssociatedItem.");
        }
    }
    currentPos ++;
    return std::make_shared<ItemImplDecl>(std::move(identifier),std::move(targetType),std::move(item_trait_const),std::move(item_trait_fn));
    
}

std::shared_ptr<ItemStructDecl> Parser::parse_item_struct() {
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::string identifier = "";
    identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::vector<ItemStructVariant> item_struct;
    if(tokens[currentPos].type == kSEMI){
        currentPos ++;
        return std::make_shared<ItemStructDecl>(std::move(identifier),std::move(item_struct));
    }
    if(tokens[currentPos].type != kL_BRACE){
        throw std::runtime_error("Wrong in item struct parsing, missing L_BRACE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type == kR_BRACE){
        currentPos ++;
        return std::make_shared<ItemStructDecl>(std::move(identifier),std::move(item_struct));
    }
    // Start Structfields
    ItemStructVariant tmp;
    if(tokens[currentPos].type != kIDENTIFIER){
        throw std::runtime_error("Wrong in item struct parsing, missing identifier.");
    }
    tmp.identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kCOLON){
        throw std::runtime_error("Wrong in item struct parsing, missing colon.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    tmp.structElem = parse_type();
    if(tokens[currentPos].type == kCOMMA){
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
    }
    item_struct.push_back(std::move(tmp));
    bool flag = false;
    while (tokens[currentPos].type != kR_BRACE){
        if(tokens[currentPos].type != kIDENTIFIER && tokens[currentPos].type != kCOMMA){
            throw std::runtime_error("Wrong in item struct parsing, missing identifier or comma.");
        }
        if(tokens[currentPos].type == kCOMMA){
            flag = true;
            currentPos ++;
            if(currentPos >= tokens.size()) {
                throw std::runtime_error("End of Program.");
            }
            if(tokens[currentPos].type == kR_BRACE) {
                break;
            }
        }else if(flag){
            throw std::runtime_error("Wrong in item struct parsing, missing comma.");
        }
        ItemStructVariant tp;
        tp.identifier = tokens[currentPos].value;
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
        if(tokens[currentPos].type != kCOLON) {
            throw std::runtime_error("Wrong in item struct parsing, missing colon.");
        }
        currentPos ++;
        if(currentPos >= tokens.size()) {
            throw std::runtime_error("End of Program.");
        }
        tp.structElem = parse_type();
        item_struct.push_back(std::move(tp));
    }
    currentPos ++;
    return std::make_shared<ItemStructDecl>(std::move(identifier),std::move(item_struct));
}

std::shared_ptr<ItemTraitDecl> Parser::parse_item_trait() {
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kIDENTIFIER){
        throw std::runtime_error("Wrong in item trait parsing, missing IDENTIFIER.");
    }
    std::string identifier = "";
    identifier = tokens[currentPos].value;
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    if(tokens[currentPos].type != kL_BRACE){
        throw std::runtime_error("Wrong in item trait parsing, missing L_BRACE.");
    }
    currentPos ++;
    if(currentPos >= tokens.size()) {
        throw std::runtime_error("End of Program.");
    }
    std::vector<std::shared_ptr<ItemConstDecl>> item_trait_const;
    std::vector<std::shared_ptr<ItemFnDecl>> item_trait_fn;
    if(tokens[currentPos].type == kR_BRACE){
        currentPos ++;
        return std::make_shared<ItemTraitDecl>(std::move(identifier),std::move(item_trait_const),std::move(item_trait_fn));
    }
    while(tokens[currentPos].type != kR_BRACE){
        std::shared_ptr<ItemConstDecl> tmpConst = nullptr;
        std::shared_ptr<ItemFnDecl> tmpFn = nullptr;
        if(tokens[currentPos].type == kCONST){
            tmpConst = parse_item_const();
            item_trait_const.push_back(std::move(tmpConst));
        }else if(tokens[currentPos].type == kFN){
            tmpFn = parse_item_fn();
            item_trait_fn.push_back(std::move(tmpFn));
        }else{
            throw std::runtime_error("Wrong in item trait parsing, missing AssociatedItem.");
        }
    }
    currentPos ++;
    return std::make_shared<ItemTraitDecl>(std::move(identifier),std::move(item_trait_const),std::move(item_trait_fn));
}

}