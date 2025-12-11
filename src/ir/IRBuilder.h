# pragma once
#include "../ast/astvisitor.h"
#include "../ast/root.h"
#include "../ast/Expression/ExprConstBlock.h"
#include "../ast/Expression/ExprStruct.h"
#include "../ast/Expression/expression.h"
#include "../ast/Expression/ExprArray.h"
#include "../ast/Expression/ExprBlock.h"
#include "../ast/Expression/ExprBreak.h"
#include "../ast/Expression/ExprCall.h"
#include "../ast/Expression/ExprContinue.h"
#include "../ast/Expression/ExprField.h"
#include "../ast/Expression/ExprGroup.h"
#include "../ast/Expression/ExprIf.h"
#include "../ast/Expression/ExprIndex.h"
#include "../ast/Expression/ExprLiteral.h"
#include "../ast/Expression/ExprLoop.h"
#include "../ast/Expression/ExprMatch.h"
#include "../ast/Expression/ExprMethodcall.h"
#include "../ast/Expression/ExprOpbinary.h"
#include "../ast/Expression/ExprOpunary.h"
#include "../ast/Expression/ExprPath.h"
#include "../ast/Expression/ExprReturn.h"
#include "../ast/Expression/ExprUnderscore.h"
#include "../ast/Item/ItemConst.h"
#include "../ast/Item/ItemEnum.h"
#include "../ast/Item/ItemFn.h"
#include "../ast/Item/ItemImpl.h"
#include "../ast/Item/ItemStruct.h"
#include "../ast/Item/ItemTrait.h"
#include "../ast/Pattern/PatternIdentifier.h"
#include "../ast/Pattern/PatternLiteral.h"
#include "../ast/Pattern/PatternPath.h"
#include "../ast/Pattern/PatternReference.h"
#include "../ast/Pattern/PatternWildcard.h"
#include "../ast/Statement/StmtEmpty.h"
#include "../ast/Statement/StmtExpr.h"
#include "../ast/Statement/StmtItem.h"
#include "../ast/Statement/StmtLet.h"
#include "../ast/Type/type.h"
#include "../ast/Type/TypeArray.h"
#include "../ast/Type/TypePath.h"
#include "../ast/Type/TypeReference.h"
#include "../ast/Type/TypeUnit.h"
#include "IRAlloca.h"
#include "IRFunction.h"
#include "IRLiteral.h"
#include "IRNode.h"
#include "IRParam.h"
#include "IRRoot.h"
#include "IRType.h"
#include "IRSelf.h"
#include "IRScope.h"
#include "IRLoad.h"
#include "IRCall.h"
#include "IRBlock.h"
#include "IRGlobalbuilder.h"
#include <memory>
#include <map>
#include <vector>

namespace JaneZ {
class IR;
class IRVar;
class IRBuilder {
public:
    std::map<std::string, int> vars_cnt;
    std::map<std::string, int> types_cnt;
    std::map<std::string, int> funcs_cnt;
    std::map<std::string, int> constant_cnt;

    int label_cnt = 0;
    
    std::shared_ptr<IRScope> currentScope;

    std::shared_ptr<IRRoot> irRoot;

    IRGlobalBuilder globalBuilder;

    IRBuilder() = default;

    ~IRBuilder() = default;

    //AST 
    void visit(ASTNode &node){
        if(auto *p = dynamic_cast<ASTRootNode *>(& node)){
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit ASTNode error");
        }
    }

    std::shared_ptr<IRRoot> visit(ASTRootNode &node){
        for(auto &varElem: globalBuilder.globalScope->value_table){
            vars_cnt[varElem.first] = 1;
        }
        for(auto &typeElem: globalBuilder.globalScope->type_table){
            types_cnt[typeElem.first] = 1;
        }
        for(auto &funcElem: globalBuilder.globalScope->function_table){
            funcs_cnt[funcElem.first] = 1;
        }
        for(auto &constElem: globalBuilder.globalScope->constant_table){
            constant_cnt[constElem.first] = 1;
        }
        currentScope = globalBuilder.globalScope;
        irRoot = std::make_shared<IRRoot>();
        //may left with some special functions like print exit...
        for(auto & item : node.child){
            irRoot->children.push_back(visit(*item));
        }
        return irRoot;
    }

    //Expression
    std::vector<std::shared_ptr<IRNode>> visit(Expression &node){
        if(auto *p = dynamic_cast<ExprArray *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprBlock *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprBreak *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprCall *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprConstBlock *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprContinue *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprField *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprGroup *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprIf *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprIndex *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprLiteral *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprLoop *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprMatch *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprMethodcall *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpbinary *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpunary *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprPath *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprReturn *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprStruct *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprUnderscore *>(& node)) {
            return visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Expression error");
        }
    }
    std::vector<std::shared_ptr<IRNode>> visit(ExprArray &node){
        if(!node.arrayExpr.empty()){
            //TODO: have no idea yet
        }else{
            // rmk: 疑似在建ASTNode的时候认为是 [type;size] ，实际上是和ArrayType搞混了
            // 所以这里的type完全是一个虚假的名字 应该是
            // [initial;size] 滑跪了
            
        }
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprBlock &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprBreak &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprCall &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        std::string funcName = "";
        if(auto *p = dynamic_cast<ExprPath *>(& *node.expr)){
            if(p->pathFirst->pathSegments.type == IDENTIFIER){
                funcName = p->pathFirst->pathSegments.identifier;
            }
        }
        auto currentIRFunc = currentScope->lookupFunctionSymbol(funcName);
        auto currentCallInstr = std::make_shared<IRCall>();
        currentCallInstr->function = currentIRFunc;
        auto callRet = std::make_shared<IRVar>();
        currentCallInstr->retVar = callRet;
        for(auto & arg : node.callParams){
            //TODO process arguments
            if(auto *p = dynamic_cast<ExprPath *>(& *arg)){
                if(p->pathFirst->pathSegments.type == IDENTIFIER){
                    std::string varName = p->pathFirst->pathSegments.identifier;
                    auto varSymbol = currentScope->lookupValueSymbol(varName);
                    //TODO load instruction
                    if(varSymbol == nullptr){
                        //constant
                        long long int res = currentScope->lookupConstantSymbol(varName);
                        currentCallInstr->pList->paramList.push_back(std::make_shared<IRLiteral>(INT_LITERAL, res));
                        continue;
                    }
                    auto currentParamVar = std::make_shared<IRVar>();
                    currentParamVar->varName = varSymbol->varName;
                    if(vars_cnt.find(currentParamVar->varName) != vars_cnt.end()){
                        vars_cnt[currentParamVar->varName] += 1;
                        currentParamVar->reName = currentParamVar->varName + "_" + std::to_string(vars_cnt[currentParamVar->varName]);
                    }else{
                        vars_cnt[currentParamVar->varName] = 1;
                        currentParamVar->reName = currentParamVar->varName;
                    }
                    currentParamVar->type = varSymbol->type;
                    instrs.push_back(std::make_shared<IRLoad>(currentParamVar, varSymbol,varSymbol->type));
                    currentCallInstr->pList->paramList.push_back(currentParamVar);
                }
            }else if(auto *p = dynamic_cast<ExprLiteral *>(& *arg)){
                if(p->type == INTEGER_LITERAL){
                    currentCallInstr->pList->paramList.push_back(std::make_shared<IRLiteral>(INT_LITERAL, p->constValue));
                }
            }
        }
        instrs.push_back(currentCallInstr);
        return instrs;
    }
    
    std::vector<std::shared_ptr<IRNode>> visit(ExprConstBlock &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(ExprContinue &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprField &node);

    std::vector<std::shared_ptr<IRNode>> visit(ExprGroup &node){
        return {};
    }
    std::vector<std::shared_ptr<IRNode>> visit(ExprIf &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprIndex &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprLiteral &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprLoop &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprMethodcall &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprOpbinary &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprOpunary &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprPath &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprReturn &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprStruct &node);
    std::vector<std::shared_ptr<IRNode>> visit(ExprUnderscore &node);
    
    //Item 
    std::shared_ptr<IRNode> visit(Item &node){
        if(auto *p = dynamic_cast<ItemConstDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemFnDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemImplDecl *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemStructDecl *>(& node)) {    
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& node)) {
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Item error");
        }
    }

    std::shared_ptr<IRNode> visit(ItemConstDecl &node);

    std::shared_ptr<IRNode> visit(ItemEnumDecl &node);

    std::shared_ptr<IRFunction> visit(ItemFnDecl &node){
        auto currentIRFunc = currentScope->lookupFunctionSymbol(node.identifier);
        auto funcScope = std::make_shared<IRScope>();
        funcScope->parent = currentScope;
        currentScope->children.push_back(funcScope);
        currentScope = funcScope;
        if(node.fnBody){
            for(auto & stmt : node.fnBody->statements){
                if(auto *itemStmt = dynamic_cast<StmtItem *>(& *stmt)){
                    if(auto *p = dynamic_cast<ItemConstDecl *>(& *itemStmt)){
                        currentScope->addConstantSymbol(p->identifier, p->value);
                    }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& *itemStmt)){
                        //todo idk just wait and see
                    }else if(auto *p = dynamic_cast<ItemFnDecl *>(& *itemStmt)){
                        std::shared_ptr<IRType> returnType;
                        if(p->returnType){
                            returnType = resolveType(*p->returnType);
                        }
                        std::string funcName = p->identifier;
                        std::shared_ptr<IRParam> irParam;
                        if(node.fnParameters.SelfParam.isShortSelf){
                            auto selfType = std::make_shared<IRSelf>();
                            irParam->paramList.push_back(selfType);
                        }
                        if(!p->fnParameters.FunctionParam.empty()){
                            for(auto & param : p->fnParameters.FunctionParam){
                                auto currentVar = std::make_shared<IRVar>();
                                if(auto *q = dynamic_cast<PatternIdentifier *>(& *param.pattern)){
                                    currentVar->varName = q->identifier;
                                }else if(auto *q = dynamic_cast<PatternReference *>(& *param.pattern)){
                                    if(auto *r = dynamic_cast<PatternIdentifier *>(& *q->patternWithoutRange)){
                                        currentVar->varName = r->identifier;
                                    }
                                }
                                if(vars_cnt.find(currentVar->varName) != vars_cnt.end()){
                                    vars_cnt[currentVar->varName] += 1;
                                    currentVar->reName = currentVar->varName + "_" + std::to_string(vars_cnt[currentVar->varName]);
                                }else{
                                    vars_cnt[currentVar->varName] = 1;
                                    currentVar->reName = currentVar->varName;
                                }
                                if(param.type){
                                    currentVar->type = resolveType(*param.type);
                                }
                                irParam->paramList.push_back(currentVar);
                            }
                        }
                        currentScope->addFunctionSymbol(funcName, std::make_shared<IRFunction>(returnType, irParam, funcName));
                    }else if(auto *p = dynamic_cast<ItemImplDecl *>(& *itemStmt)){
                        //no need to do anything
                    }else if(auto *p = dynamic_cast<ItemStructDecl *>(& *itemStmt)){
                        //todo
                        std::vector<std::pair<std::string,std::shared_ptr<IRType>>> fieldTypes;
                        std::string structName = p->identifier;
                        for(auto & field : p->item_struct){
                            if(field.structElem){
                                fieldTypes.push_back({field.identifier, resolveType(*field.structElem)});
                            }
                        }
                        currentScope->addTypeSymbol(structName, std::make_shared<IRStructType>(structName, fieldTypes));
                    }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& *itemStmt)){
                        //no need to do anything
                    }
                }
            }
        }
        //todo processing the function body
        if(node.fnBody){
            for(auto & stmt : node.fnBody->statements){
                std::vector<std::shared_ptr<IRNode>> instructions = visit(*stmt);
                for(auto & instr : instructions){
                    currentIRFunc->body->instrList.push_back(instr);
                }
            }
            if(node.fnBody->ExpressionWithoutBlock){
                //todo about br instruction
            }
        }
    }


    std::shared_ptr<IRNode> visit(ItemImplDecl &node){
        // no need to do anything
        // I plan to do the IRFunction build in IRGlobalBuilder
        return nullptr;
    }

    std::shared_ptr<IRNode> visit(ItemStructDecl &node){
        auto currentStruct = currentScope->lookupTypeSymbol(node.identifier);
        return currentStruct;
    }

    std::shared_ptr<IRNode> visit(ItemTraitDecl &node){
        // no need to do anything
        return nullptr;
    }

    //Pattern
    void visit(Pattern &node){
        if(auto *p = dynamic_cast<PatternIdentifier *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternLiteral *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternPath *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternReference *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<PatternWildCard *>(& node)) {   
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Pattern error");
        }
    }
    void visit(PatternIdentifier &node);
    void visit(PatternLiteral &node);
    void visit(PatternPath &node);
    void visit(PatternReference &node);
    void visit(PatternWildCard &node);

    //Statement
    std::vector<std::shared_ptr<IRNode>> visit(Statement &node){
        if(auto *p = dynamic_cast<StmtEmpty *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<StmtExpr *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<StmtItem *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<StmtLet *>(& node)) {
            return visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Statement error");
        }
    }

    std::vector<std::shared_ptr<IRNode>> visit(StmtEmpty &node){
        return {};
    }

    std::vector<std::shared_ptr<IRNode>> visit(StmtExpr &node){
        //TODO
    }

    std::vector<std::shared_ptr<IRNode>> visit(StmtItem &node){
        std::vector<std::shared_ptr<IRNode>> res;
        res.push_back(visit(*node.stmt_item));
        return res;
    }

    std::vector<std::shared_ptr<IRNode>> visit(StmtLet &node){
        std::vector<std::shared_ptr<IRNode>> instrs;
        //todo
        std::string varName;
        std::string reName;
        if(auto *p = dynamic_cast<PatternIdentifier *>(& *node.PatternNoTopAlt)){
            varName = p->identifier;
        }else if(auto *p = dynamic_cast<PatternReference *>(& *node.PatternNoTopAlt)){
            if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                varName = q->identifier;
            }
        }
        if(vars_cnt.find(varName) != vars_cnt.end()){
            vars_cnt[varName] += 1;
            reName = varName + "_" + std::to_string(vars_cnt[varName]);
        }else{
            vars_cnt[varName] = 1;
            reName = varName;
        }
        //todo
        std::shared_ptr<IRType> varType = resolveType(*node.type);
        auto currentVar = std::make_shared<IRVar>(varName, reName, varType);
        currentScope->addValueSymbol(varName, currentVar);
        instrs.push_back(std::make_shared<IRAlloca>(varType,currentVar));
        //todo init expr

    }

    //Type
    std::shared_ptr<IRType> resolveType(ASTNode &node){
        if(auto *p = dynamic_cast<Type *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeArray *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<Path *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeReference *>(& node)){
            return visit(*p);
        }else if(auto *p = dynamic_cast<TypeUnit *>(& node)){
            return visit(*p);
        }
        throw std::runtime_error("IRBuilder resolveType error");
    }

    std::shared_ptr<IRIntType> visit(Type &node){
        if(node.type == I32){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("i32"));
        }else if(node.type == U32){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("u32"));
        }else if(node.type == ISIZE){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("isize"));
        }else if(node.type == USIZE){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("usize"));
        }else if(node.type == BOOL){
            return std::dynamic_pointer_cast<IRIntType>(currentScope->lookupTypeSymbol("bool"));
        }
        throw std::runtime_error("IRBuilder visit Type error: unknown primitive type");
    }

    std::shared_ptr<IRArrayType> visit(TypeArray &node){
        auto currentType = std::make_shared<IRType>();
        int size = 0;
        if(node.type){
            currentType = resolveType(*node.type);
        }
        if(node.expr){
            size = node.expr->constValue;
        }
        return std::make_shared<IRArrayType>(currentType, size);
    }

    std::shared_ptr<IRStructType> visit(Path &node){
        if(node.pathSegments.type == IDENTIFIER){
            auto typeName = node.pathSegments.identifier;
            auto structType = currentScope->lookupTypeSymbol(typeName);
            if(structType){
                return std::dynamic_pointer_cast<IRStructType>(structType);
            }else{
                throw std::runtime_error("IRBuilder visit Path error: unknown type " + typeName);
            }
        }
        //TODO self
    }

    std::shared_ptr<IRPtrType> visit(TypeReference &node){
        auto refType = std::make_shared<IRPtrType>();
        if(node.typeNoBounds){
            refType->baseType = resolveType(*node.typeNoBounds);
        }
        return refType;
    }

    std::shared_ptr<IRVoidType> visit(TypeUnit &node){
        return std::dynamic_pointer_cast<IRVoidType>(currentScope->lookupTypeSymbol("void"));
    }
};

}