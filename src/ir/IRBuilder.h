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
#include "IRFunction.h"
#include "IRNode.h"
#include "IRParam.h"
#include "IRRoot.h"
#include "IRType.h"
#include "IRSelf.h"
#include "IRScope.h"
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
        for(auto &typeElem: globalBuilder.globalScope->type_table){
            //todo
        }
        irRoot = std::make_shared<IRRoot>();
        for(auto & item : node.child){
            irRoot->children.push_back(visit(*item));
        }
        return irRoot;
    }

    //Expression
    void visit(Expression &node){
        if(auto *p = dynamic_cast<ExprArray *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprBlock *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprBreak *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprCall *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprConstBlock *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprContinue *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprField *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprGroup *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprIf *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprIndex *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprLiteral *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprLoop *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprMatch *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprMethodcall *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpbinary *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpunary *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprPath *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprReturn *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprStruct *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprUnderscore *>(& node)) {
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Expression error");
        }
    }
    void visit(ExprArray &node){
        if(!node.arrayExpr.empty()){
            //TODO: have no idea yet
        }else{
            // rmk: 疑似在建ASTNode的时候认为是 [type;size] ，实际上是和ArrayType搞混了
            // 所以这里的type完全是一个虚假的名字 应该是
            // [initial;size] 滑跪了
            
        }
    }
    void visit(ExprBlock &node);
    void visit(ExprBreak &node);
    void visit(ExprCall &node);
    void visit(ExprConstBlock &node);
    void visit(ExprContinue &node);
    void visit(ExprField &node);
    void visit(ExprGroup &node);
    void visit(ExprIf &node);
    void visit(ExprIndex &node);
    void visit(ExprLiteral &node);
    void visit(ExprLoop &node);
    void visit(ExprMethodcall &node);
    void visit(ExprOpbinary &node);
    void visit(ExprOpunary &node);
    void visit(ExprPath &node);
    void visit(ExprReturn &node);
    void visit(ExprStruct &node);
    void visit(ExprUnderscore &node);
    
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
                        //todo
                        std::shared_ptr<IRType> returnType;
                        if(p->returnType){
                            returnType = resolveType(*p->returnType);
                        }
                        std::string funcName = p->identifier;
                    }else if(auto *p = dynamic_cast<ItemImplDecl *>(& *itemStmt)){
                        //todo
                    }else if(auto *p = dynamic_cast<ItemStructDecl *>(& *itemStmt)){
                        //todo
                    }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& *itemStmt)){
                        //todo
                    }
                }
            }
        }
    }
    std::shared_ptr<IRNode> visit(ItemImplDecl &node){
        
    }
    std::shared_ptr<IRNode> visit(ItemStructDecl &node);
    std::shared_ptr<IRNode> visit(ItemTraitDecl &node);

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
    void visit(Statement &node){
        if(auto *p = dynamic_cast<StmtEmpty *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<StmtExpr *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<StmtItem *>(& node)) {
            visit(*p);
        }else if(auto *p = dynamic_cast<StmtLet *>(& node)) {
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit Statement error");
        }
    }
    void visit(StmtEmpty &node);
    void visit(StmtExpr &node);
    void visit(StmtItem &node);
    void visit(StmtLet &node);

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