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

void checkReturntypeInConditionBlock(std::shared_ptr<ExprIf> &&exprIf, RustType tp){
    if(exprIf->thenBlock){
        if(exprIf->thenBlock->ExpressionWithoutBlock){
            if(auto *r = dynamic_cast<ExprReturn *>(& *exprIf->thenBlock->ExpressionWithoutBlock)){
                if(r->expr){
                    if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                        if(auto *s = dynamic_cast<ExprLiteral *>(& *r->expr)){
                            if(s->type != INTEGER_LITERAL){
                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                            }
                        }
                    }else if(tp == RustType::BOOL){
                        if(auto *s = dynamic_cast<ExprLiteral *>(& *r->expr)){
                            if(s->type != TRUE && s->type != FALSE){
                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                            }
                        }
                    }else if(tp == RustType::CHAR){
                        if(auto *s = dynamic_cast<ExprLiteral *>(& *r->expr)){
                            if(s->type != CHAR_LITERAL){
                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                            }
                        }
                    }
                    // todo other literals check
                }
            }else if(auto *r = dynamic_cast<ExprLiteral *>(& *exprIf->thenBlock->ExpressionWithoutBlock)){
                if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                    if(r->type != INTEGER_LITERAL){
                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                    }
                }else if(tp == RustType::BOOL){
                    if(r->type != TRUE && r->type != FALSE){
                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                    }
                }else if(tp == RustType::CHAR){
                    if(r->type != CHAR_LITERAL){
                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                    }
                }
                // todo other literals check
            }else if(auto *r = dynamic_cast<ExprUnderscore *>(& *exprIf->thenBlock->ExpressionWithoutBlock)){
                throw std::runtime_error("Wrong in item fn body with underscore.");
            }
        }else if(!exprIf->thenBlock->statements.empty()){
            if(auto *r = dynamic_cast<StmtExpr *>(& *exprIf->thenBlock->statements[exprIf->thenBlock->statements.size() - 1])){
                if(auto *s = dynamic_cast<ExprReturn *>(& *r->stmtExpr)){
                    if(s->expr){
                        if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                            if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                if(t->type != INTEGER_LITERAL){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }else if(tp == RustType::BOOL){
                            if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                if(t->type != TRUE && t->type != FALSE){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }else if(tp == RustType::CHAR){
                            if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                if(t->type != CHAR_LITERAL){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }
                        // todo other literals check    
                    }
                }else if(auto *s = dynamic_cast<ExprLiteral *>(& *r->stmtExpr)){
                    if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                        if(s->type != INTEGER_LITERAL){
                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                        }
                    }else if(tp == RustType::BOOL){
                        if(s->type != TRUE && s->type != FALSE){
                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                        }
                    }else if(tp == RustType::CHAR){
                        if(s->type != CHAR_LITERAL){
                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                        }
                    }
                    // todo other literals check
                }else if(auto *s = dynamic_cast<ExprUnderscore *>(& *r->stmtExpr)){
                    throw std::runtime_error("Wrong in item fn body with underscore.");
                }
            }
        }
    }
    if(exprIf->elseBlock){
        if(auto *r = dynamic_cast<ExprIf *>(& *exprIf->elseBlock)){
            checkReturntypeInConditionBlock(std::make_shared<ExprIf>(std::move(*r)), tp);
        }else if(auto *r = dynamic_cast<ExprBlock *>(& *exprIf->elseBlock)){
            if(r->ExpressionWithoutBlock){
                if(auto *s = dynamic_cast<ExprReturn *>(& *r->ExpressionWithoutBlock)){
                    if(s->expr){
                        if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                            if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                if(t->type != INTEGER_LITERAL){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }else if(tp == RustType::BOOL){
                            if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                if(t->type != TRUE && t->type != FALSE){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }else if(tp == RustType::CHAR){
                            if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                if(t->type != CHAR_LITERAL){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }
                        // todo other literals check    
                    }
                }else if(auto *s = dynamic_cast<ExprLiteral *>(& *r->ExpressionWithoutBlock)){
                    if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                        if(s->type != INTEGER_LITERAL){
                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                        }
                    }else if(tp == RustType::BOOL){
                        if(s->type != TRUE && s->type != FALSE){
                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                        }
                    }else if(tp == RustType::CHAR){
                        if(s->type != CHAR_LITERAL){
                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                        }
                    }
                    // todo other literals check
                }else if(auto *s = dynamic_cast<ExprUnderscore *>(& *r->ExpressionWithoutBlock)){
                    throw std::runtime_error("Wrong in item fn body with underscore.");
                }
            }else if(!r->statements.empty()){
                if(auto *s = dynamic_cast<StmtExpr *>(& *r->statements[r->statements.size() - 1])){
                    if(auto *t = dynamic_cast<ExprReturn *>(& *s->stmtExpr)){
                        if(t->expr){
                            if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                if(auto *u = dynamic_cast<ExprLiteral *>(& *t->expr)){
                                    if(u->type != INTEGER_LITERAL){
                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                    }       
                                }
                            }else if(tp == RustType::BOOL){
                                if(auto *u = dynamic_cast<ExprLiteral *>(& *t->expr)){
                                    if(u->type != TRUE && u->type != FALSE){
                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                    }       
                                }
                            }else if(tp == RustType::CHAR){
                                if(auto *u = dynamic_cast<ExprLiteral *>(& *t->expr)){
                                    if(u->type != CHAR_LITERAL){
                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                    }       
                                }   
                            }
                            // todo other literals check
                        }
                    }else if(auto *t = dynamic_cast<ExprLiteral *>(& *s->stmtExpr)){
                        if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                            if(t->type != INTEGER_LITERAL){
                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                            }
                        }else if(tp == RustType::BOOL){
                            if(t->type != TRUE && t->type != FALSE){
                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                            }
                        }else if(tp == RustType::CHAR){
                            if(t->type != CHAR_LITERAL){
                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                            }
                        }
                        // todo other literals check
                    }else if(auto *t = dynamic_cast<ExprUnderscore *>(& *s->stmtExpr)){ 
                        throw std::runtime_error("Wrong in item fn body with underscore.");
                    }
                }
            }
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
                    /*if(tokens[currentPos + 1].type != kSELF){
                        throw std::runtime_error("Wrong format in item fn with missing self.");
                    }*/
                    if(tokens[currentPos + 1].type == kSELF){
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
                        isStraightParam = true;
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

    if(tokens[currentPos].type == kSEMI){
        currentPos ++;
        return std::make_shared<ItemFnDecl>(std::move(identifier),std::move(param),nullptr,nullptr,is_const);
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
        //main function return type check
        if(identifier == "main"){
            if(auto *p = dynamic_cast<TypeUnit *>(&*returnType)){
                //correct
            }else{
                throw std::runtime_error("Wrong format with main function return type.");
            }
        }
    }
    RustType tp;
    if(returnType){
        if(auto *p = dynamic_cast<Type *>(& *returnType)){
            if(p->type == BOOL){
                tp = RustType::BOOL;
            }else if(p->type == I32){
                tp = RustType::I32;
            }else if(p->type == U32){
                tp = RustType::U32;
            }else if(p->type == ISIZE){
                tp = RustType::ISIZE;
            }else if(p->type == USIZE){
                tp = RustType::USIZE;
            }else if(p->type == CHAR){
                tp = RustType::CHAR;
            }else if(p->type == STR){
                tp = RustType::STR; 
            }else if(p->type == ENUM){
                tp = RustType::ENUM;
            }
        }else if(auto *p = dynamic_cast<TypeReference *>(& *returnType)){
            tp = RustType::REFERENCE;
        }else if(auto *p = dynamic_cast<TypeArray *>(& *returnType)){
            tp = RustType::ARRAY;
        }else if(auto *p = dynamic_cast<TypeUnit *>(& *returnType)){
            tp = RustType::UNIT;
        }else if(auto *p = dynamic_cast<Path *>(& *returnType)){
            tp = RustType::PATH;
        }else{
            throw std::runtime_error("Wrong in item fn parsing, invalid return type.");
        }
    }
    if(tokens[currentPos].type == kSEMI) {
        currentPos ++;
        return std::make_shared<ItemFnDecl>(std::move(identifier),std::move(param),nullptr,std::move(returnType),is_const);
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
        //underscore check
        if(fnBody->ExpressionWithoutBlock){
            if(auto *p = dynamic_cast<ExprUnderscore *>(& *fnBody->ExpressionWithoutBlock)){
                throw std::runtime_error("Wrong in item fn body with underscore.");
            }
        }else if(!fnBody->statements.empty()){
            if(auto *p = dynamic_cast<ExprUnderscore *>(& *fnBody->statements[fnBody->statements.size() - 1])){
                throw std::runtime_error("Wrong in item fn body with underscore.");
            }
        }
        //break statement check
        if(!fnBody->statements.empty() ){
            for (auto &stmt : fnBody->statements) {
                if (auto *p = dynamic_cast<StmtExpr *>(&*stmt)) {
                    if (auto *q = dynamic_cast<ExprBreak *>(&*p->stmtExpr)) {
                        throw std::runtime_error("Wrong in item fn body with break statement.");
                    }
                }
            
            }
        }
        if(fnBody->ExpressionWithoutBlock){
            if (auto *p = dynamic_cast<ExprBreak *>(&*fnBody->ExpressionWithoutBlock)) {
                throw std::runtime_error("Wrong in item fn body with break statement.");
            }
        }
        //main function check
        if(identifier == "main"){
            if(fnBody->ExpressionWithoutBlock){
                if(auto *p = dynamic_cast<ExprCall *>(& *fnBody->ExpressionWithoutBlock)){
                    if(auto *q = dynamic_cast<ExprPath *>(& *p->expr)){
                        if(q ->pathFirst->pathSegments.identifier == "exit" && q->pathSecond == nullptr){
                            // remain call param check (i32 is all you need.)
                        }else{
                            throw std::runtime_error("Wrong format with main function body, last expression must be exit function call.");
                        }
                    }else{
                        throw std::runtime_error("Wrong format with main function body, last expression must be exit function call.");
                    }
                }else{
                    throw std::runtime_error("Wrong format with main function body, last expression must be exit function call.");
                }    
            }else{
                if(!fnBody->statements.empty()) {
                    if(auto *p = dynamic_cast<StmtExpr *>(& *fnBody->statements[fnBody->statements.size() - 1])){
                        if(auto *q = dynamic_cast<ExprCall *>(& *p->stmtExpr)){
                            if(auto *r = dynamic_cast<ExprPath *>(& *q->expr)){
                                if(r ->pathFirst->pathSegments.identifier == "exit" && r->pathSecond == nullptr){
                                    // remain call param check (i32 is all you need.)
                                }else{
                                    throw std::runtime_error("Wrong format with main function body, last expression must be exit function call.");
                                }
                            }else{
                                throw std::runtime_error("Wrong format with main function body, last expression must be exit function call.");
                            }
                        }else{
                            throw std::runtime_error("Wrong format with main function body, last expression must be exit function call.");
                        }
                    }else{
                        throw std::runtime_error("Wrong format with main function body, last expression must be exit function call.");
                    }
                }
            }
        }
        // other function no exit function call check
        if(identifier != "main"){
            if(fnBody->ExpressionWithoutBlock){
                if(auto *p = dynamic_cast<ExprCall *>(& *fnBody->ExpressionWithoutBlock)){
                    if(auto *q = dynamic_cast<ExprPath *>(& *p->expr)){
                        if(q ->pathFirst->pathSegments.identifier == "exit" && q->pathSecond == nullptr){
                            throw std::runtime_error("Wrong format with function body, exit function call is not allowed.");
                        }
                    }
                }
            }
            if(!fnBody->statements.empty()){
                for(auto &stmt : fnBody->statements) {
                    if (auto *p = dynamic_cast<StmtExpr *>(& *stmt)) {
                        if (auto *q = dynamic_cast<ExprCall *>(& *p->stmtExpr)) {
                            if (auto *r = dynamic_cast<ExprPath *>(& *q->expr)) {
                                if (r->pathFirst->pathSegments.identifier == "exit" && r->pathSecond == nullptr) {
                                    throw std::runtime_error("Wrong format with function body, exit function call is not allowed.");
                                }
                            }
                        }
                    }
                }
            }
        }
        // function return type mismatch check
        if(returnType){
            if(fnBody->ExpressionWithoutBlock){
                if(auto *p = dynamic_cast<ExprReturn *>(& *fnBody->ExpressionWithoutBlock)){
                    if(p->expr){
                        if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                            if(auto *q = dynamic_cast<ExprLiteral *>(& *p->expr)){
                                if(q->type != INTEGER_LITERAL){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }else if(tp == RustType::BOOL){
                            if(auto *q = dynamic_cast<ExprLiteral *>(& *p->expr)){
                                if(q->type != TRUE && q->type != FALSE){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }else if(tp == RustType::CHAR){
                            if(auto *q = dynamic_cast<ExprLiteral *>(& *p->expr)){
                                if(q->type != CHAR_LITERAL){
                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                }
                            }
                        }
                        // todo other literals check
                    }
                }
            }else{
                if(!fnBody->statements.empty()) {
                    if(auto *p = dynamic_cast<StmtExpr *>(& *fnBody->statements[fnBody->statements.size() - 1])){
                        if(auto *q = dynamic_cast<ExprReturn *>(& *p->stmtExpr)){
                            if(q->expr){
                                if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                    if(auto *r = dynamic_cast<ExprLiteral *>(& *q->expr)){
                                        if(r->type != INTEGER_LITERAL){
                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                        }
                                    }
                                }else if(tp == RustType::BOOL){
                                    if(auto *r = dynamic_cast<ExprLiteral *>(& *q->expr)){
                                        if(r->type != TRUE && r->type != FALSE){
                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                        }
                                    }
                                }else if(tp == RustType::CHAR){
                                    if(auto *r = dynamic_cast<ExprLiteral *>(& *q->expr)){
                                        if(r->type != CHAR_LITERAL){
                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                        }
                                    }
                                }
                                // todo other literals check
                            }
                        }
                    }
                }
            }
        }
        // return type check in conditional blocks
        if(returnType){
            if(!fnBody->statements.empty()){
                for(auto &stmt: fnBody->statements){
                    if(auto *p = dynamic_cast<StmtExpr *>(& *stmt)){
                        if(auto *q = dynamic_cast<ExprIf *>(& *p->stmtExpr)){
                            if(q->thenBlock){
                                if(q->thenBlock->ExpressionWithoutBlock){
                                    if(auto *r = dynamic_cast<ExprReturn *>(& *q->thenBlock->ExpressionWithoutBlock)){
                                        if(r->expr){
                                            if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                                if(auto *s = dynamic_cast<ExprLiteral *>(& *r->expr)){
                                                    if(s->type != INTEGER_LITERAL){
                                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                    }
                                                }
                                            }else if(tp == RustType::BOOL){
                                                if(auto *s = dynamic_cast<ExprLiteral *>(& *r->expr)){
                                                    if(s->type != TRUE && s->type != FALSE){
                                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                    }
                                                }
                                            }else if(tp == RustType::CHAR){
                                                if(auto *s = dynamic_cast<ExprLiteral *>(& *r->expr)){
                                                    if(s->type != CHAR_LITERAL){
                                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                    }
                                                }
                                            }
                                            // todo other literals check
                                        }
                                    }else if(auto *r = dynamic_cast<ExprLiteral *>(& *q->thenBlock->ExpressionWithoutBlock)){
                                        if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                            if(r->type != INTEGER_LITERAL){
                                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                            }
                                        }else if(tp == RustType::BOOL){
                                            if(r->type != TRUE && r->type != FALSE){
                                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                            }
                                        }else if(tp == RustType::CHAR){
                                            if(r->type != CHAR_LITERAL){
                                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                            }
                                        }
                                        // todo other literals check
                                    }else if(auto *r = dynamic_cast<ExprUnderscore *>(& *q->thenBlock->ExpressionWithoutBlock)){
                                        throw std::runtime_error("Wrong in item fn body with underscore.");
                                    }
                                }else if(!q->thenBlock->statements.empty()){
                                    if(auto *r = dynamic_cast<StmtExpr *>(& *q->thenBlock->statements[q->thenBlock->statements.size() - 1])){
                                        if(auto *s = dynamic_cast<ExprReturn *>(& *r->stmtExpr)){
                                            if(s->expr){
                                                if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                                    if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                                        if(t->type != INTEGER_LITERAL){
                                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                        }
                                                    }
                                                }else if(tp == RustType::BOOL){
                                                    if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                                        if(t->type != TRUE && t->type != FALSE){
                                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                        }
                                                    }
                                                }else if(tp == RustType::CHAR){
                                                    if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                                        if(t->type != CHAR_LITERAL){
                                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                        }
                                                    }
                                                }
                                                // todo other literals check
                                            }
                                        }else if(auto *s = dynamic_cast<ExprLiteral *>(& *r->stmtExpr)){
                                            if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                                if(s->type != INTEGER_LITERAL){
                                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                }
                                            }else if(tp == RustType::BOOL){
                                                if(s->type != TRUE && s->type != FALSE){
                                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                }
                                            }else if(tp == RustType::CHAR){
                                                if(s->type != CHAR_LITERAL){
                                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                }
                                            }
                                            // todo other literals check
                                        }else if(auto *s = dynamic_cast<ExprUnderscore *>(& *r->stmtExpr)){
                                            throw std::runtime_error("Wrong in item fn body with underscore.");
                                        }
                                    }
                                }
                            }
                            if(q->elseBlock){
                                if(auto *r = dynamic_cast<ExprIf *>(& *q->elseBlock)){
                                    checkReturntypeInConditionBlock(std::make_shared<ExprIf>(std::move(*r)), tp);
                                }else if(auto *r = dynamic_cast<ExprBlock *>(& *q->elseBlock)){
                                    if(r->ExpressionWithoutBlock){
                                        if(auto *s = dynamic_cast<ExprReturn *>(& *r->ExpressionWithoutBlock)){
                                            if(s->expr){
                                                if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                                    if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                                        if(t->type != INTEGER_LITERAL){
                                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                        }
                                                    }
                                                }else if(tp == RustType::BOOL){
                                                    if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                                        if(t->type != TRUE && t->type != FALSE){
                                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                        }
                                                    }
                                                }else if(tp == RustType::CHAR){
                                                    if(auto *t = dynamic_cast<ExprLiteral *>(& *s->expr)){
                                                        if(t->type != CHAR_LITERAL){
                                                            throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                        }
                                                    }
                                                }
                                                // todo other literals check
                                            }
                                        }else if (auto *s = dynamic_cast<ExprLiteral *>(& *r->ExpressionWithoutBlock)){ 
                                            if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                                if(s->type != INTEGER_LITERAL){
                                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                }
                                            }else if(tp == RustType::BOOL){
                                                if(s->type != TRUE && s->type != FALSE){
                                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                }
                                            }else if(tp == RustType::CHAR){
                                                if(s->type != CHAR_LITERAL){
                                                    throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                }
                                            }
                                            // todo other literals check
                                        }else if(auto *s = dynamic_cast<ExprUnderscore *>(& *r->ExpressionWithoutBlock)){
                                            throw std::runtime_error("Wrong in item fn body with underscore.");
                                        }
                                    }else if(!r->statements.empty()){
                                        if(auto *s = dynamic_cast<StmtExpr *>(& *r->statements[r->statements.size() - 1])){
                                            if(auto *t = dynamic_cast<ExprReturn *>(& *s->stmtExpr)){
                                                if(t->expr){
                                                    if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                                        if(auto *u = dynamic_cast<ExprLiteral *>(& *t->expr)){
                                                            if(u->type != INTEGER_LITERAL){
                                                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                            }
                                                        }
                                                    }else if(tp == RustType::BOOL){
                                                        if(auto *u = dynamic_cast<ExprLiteral *>(& *t->expr)){
                                                            if(u->type != TRUE && u->type != FALSE){
                                                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                            }
                                                        }
                                                    }else if(tp == RustType::CHAR){
                                                        if(auto *u = dynamic_cast<ExprLiteral *>(& *t->expr)){
                                                            if(u->type != CHAR_LITERAL){
                                                                throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                            }       
                                                        }
                                                    }
                                                    // todo other literals check
                                                }
                                            }else if(auto *t = dynamic_cast<ExprLiteral *>(& *s->stmtExpr)){
                                                if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
                                                    if(t->type != INTEGER_LITERAL){
                                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                    }
                                                }else if(tp == RustType::BOOL){
                                                    if(t->type != TRUE && t->type != FALSE){
                                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                    }
                                                }else if(tp == RustType::CHAR){
                                                    if(t->type != CHAR_LITERAL){
                                                        throw std::runtime_error("Wrong in item fn body with return type mismatch.");
                                                    }
                                                }
                                                // todo other literals check
                                            }else if(auto *t = dynamic_cast<ExprUnderscore *>(& *s->stmtExpr)){
                                                throw std::runtime_error("Wrong in item fn body with underscore.");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
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
    //type check 
    RustType tp;
    if(auto *p = dynamic_cast<Type *>(& *type)){
        if(p->type == BOOL){
            tp = RustType::BOOL;
        }else if(p->type == I32){
            tp = RustType::I32;
        }else if(p->type == U32){
            tp = RustType::U32;
        }else if(p->type == ISIZE){
            tp = RustType::ISIZE;
        }else if(p->type == USIZE){
            tp = RustType::USIZE;
        }else if(p->type == CHAR){
            tp = RustType::CHAR;
        }else if(p->type == STR){
            tp = RustType::STR;
        }else if(p->type == ENUM){
            tp = RustType::ENUM;    
        }
    }else if(auto *p = dynamic_cast<TypeReference *>(& *type)){
        tp = RustType::REFERENCE;
    }else if(auto *p = dynamic_cast<TypeArray *>(& *type)){
        tp = RustType::ARRAY;
    }else if(auto *p = dynamic_cast<TypeUnit *>(& *type)){
        tp = RustType::UNIT;
    }else if(auto *p = dynamic_cast<Path *>(& *type)){
        tp = RustType::PATH;
    }else{
        throw std::runtime_error("Wrong in item const parsing, invalid type.");
    }
    if(auto *r = dynamic_cast<ExprLiteral *>(& *expr)){
        if(tp == RustType::U32 || tp == RustType::I32 || tp == RustType::ISIZE || tp == RustType::USIZE ){
            if(r->type != INTEGER_LITERAL){
                throw std::runtime_error("Wrong in item const with type mismatch.");
            }
        }else if(tp == RustType::BOOL){
            if(r->type != TRUE && r->type != FALSE){
                throw std::runtime_error("Wrong in item const with type mismatch.");
            }
        }else if(tp == RustType::CHAR){
            if(r->type != CHAR_LITERAL){
                throw std::runtime_error("Wrong in item const with type mismatch.");
            }
        }
        // todo other literals check
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
                    if(currentPos + 1 < tokens.size()){
                        if(tokens[currentPos + 1].type != kFN){
                            tmpConst = parse_item_const();
                            item_trait_const.push_back(std::move(tmpConst));
                        }
                    }else{
                        tmpFn = parse_item_fn();
                        item_trait_fn.push_back(std::move(tmpFn));
                    }
                }else if(tokens[currentPos].type == kFN){
                    tmpFn = parse_item_fn();
                    item_trait_fn.push_back(std::move(tmpFn));
                }else{
                    throw std::runtime_error("Wrong in item trait parsing, missing AssociatedItem.");
                }
            }
            if(!item_trait_fn.empty()){
                for(auto &it : item_trait_fn){
                    if(it->identifier == "main"){
                        if(it->fnBody){
                            if(it->fnBody->ExpressionWithoutBlock){
                                if(auto *p = dynamic_cast<ExprCall *>(& *it->fnBody->ExpressionWithoutBlock)){
                                    if(auto *q = dynamic_cast<ExprPath *>(& *p->expr)){
                                        if(q ->pathFirst->pathSegments.identifier == "exit" && q->pathSecond == nullptr){
                                            throw std::runtime_error("Wrong format with main function in trait impl, exit function call is not allowed.");
                                        }
                                    }
                                }
                            }
                            if(!it->fnBody->statements.empty()){
                                for(auto &stmt : it->fnBody->statements) {
                                    if (auto *p = dynamic_cast<StmtExpr *>(& *stmt)) {
                                        if (auto *q = dynamic_cast<ExprCall *>(& *p->stmtExpr)) {
                                            if (auto *r = dynamic_cast<ExprPath *>(& *q->expr)) {
                                                if (r->pathFirst->pathSegments.identifier == "exit" && r->pathSecond == nullptr) {
                                                    throw std::runtime_error("Wrong format with main function in trait impl, exit function call is not allowed.");
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
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
    if(!item_trait_fn.empty()){
        for(auto &it : item_trait_fn){
            if(it->identifier == "main"){
                if(it->fnBody){
                    if(it->fnBody->ExpressionWithoutBlock){
                        if(auto *p = dynamic_cast<ExprCall *>(& *it->fnBody->ExpressionWithoutBlock)){
                            if(auto *q = dynamic_cast<ExprPath *>(& *p->expr)){
                                if(q ->pathFirst->pathSegments.identifier == "exit" && q->pathSecond == nullptr){
                                    throw std::runtime_error("Wrong format with main function in inherent impl, exit function call is not allowed.");
                                }
                            }
                        }
                    }
                    if(!it->fnBody->statements.empty()){
                        for(auto &stmt : it->fnBody->statements) {
                            if (auto *p = dynamic_cast<StmtExpr *>(& *stmt)) {
                                if (auto *q = dynamic_cast<ExprCall *>(& *p->stmtExpr)) {
                                    if (auto *r = dynamic_cast<ExprPath *>(& *q->expr)) {
                                        if (r->pathFirst->pathSegments.identifier == "exit" && r->pathSecond == nullptr) {
                                            throw std::runtime_error("Wrong format with main function in inherent impl, exit function call is not allowed.");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
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
    // main function exit check (not allowed in trait)
    if(!item_trait_fn.empty()){
        for(auto &it : item_trait_fn){
            if(it->identifier == "main"){
                if(it->fnBody){
                    if(it->fnBody->ExpressionWithoutBlock){
                        if(auto *p = dynamic_cast<ExprCall *>(& *it->fnBody->ExpressionWithoutBlock)){
                            if(auto *q = dynamic_cast<ExprPath *>(& *p->expr)){
                                if(q ->pathFirst->pathSegments.identifier == "exit" && q->pathSecond == nullptr){
                                    throw std::runtime_error("Wrong format with main function in trait, exit function call is not allowed.");
                                }
                            }
                        }
                    }
                    if(!it->fnBody->statements.empty()){
                        for(auto &stmt : it->fnBody->statements) {
                            if (auto *p = dynamic_cast<StmtExpr *>(& *stmt)) {
                                if (auto *q = dynamic_cast<ExprCall *>(& *p->stmtExpr)) {
                                    if (auto *r = dynamic_cast<ExprPath *>(& *q->expr)) {
                                        if (r->pathFirst->pathSegments.identifier == "exit" && r->pathSecond == nullptr) {
                                            throw std::runtime_error("Wrong format with main function in trait, exit function call is not allowed.");
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    currentPos ++;
    return std::make_shared<ItemTraitDecl>(std::move(identifier),std::move(item_trait_const),std::move(item_trait_fn));
}

}