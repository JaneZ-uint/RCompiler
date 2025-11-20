# pragma once
# include "../ast/astvisitor.h"
# include "IR.h"
# include "../ast/root.h"
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

namespace JaneZ {
class IR;
class IRBuilder : public ASTVisitor {
public:
    IR llvm_ir;

    ~IRBuilder() = default;

    //AST 
    void visit(ASTNode &node) override{
        if(auto *p = dynamic_cast<ASTRootNode *>(& node)){
            visit(*p);
        }else{
            throw std::runtime_error("IRBuilder visit ASTNode error");
        }
    }

    void visit(ASTRootNode &node) override{
        for(auto & item : node.child){
            item->accept(*this);
        }
    }

    //Expression
    void visit(Expression &node) override{
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
    void visit(ExprArray &node) override;
    void visit(ExprBlock &node) override;
    void visit(ExprBreak &node) override;
    void visit(ExprCall &node) override;
    void visit(ExprConstBlock &node) override;
    void visit(ExprContinue &node) override;
    void visit(ExprField &node) override;
    void visit(ExprGroup &node) override;
    void visit(ExprIf &node) override;
    void visit(ExprIndex &node) override;
    void visit(ExprLiteral &node) override;
    void visit(ExprLoop &node) override;
    void visit(ExprMethodcall &node) override;
    void visit(ExprOpbinary &node) override;
    void visit(ExprOpunary &node) override;
    void visit(ExprPath &node) override;
    void visit(ExprReturn &node) override;
    void visit(ExprStruct &node) override;
    void visit(ExprUnderscore &node) override;
    
    //Item 
    void visit(Item &node) override{
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
    void visit(ItemConstDecl &node) override;
    void visit(ItemEnumDecl &node) override;
    void visit(ItemFnDecl &node) override;
    void visit(ItemImplDecl &node) override;
    void visit(ItemStructDecl &node) override;
    void visit(ItemTraitDecl &node) override;

    //Pattern
    void visit(Pattern &node) override{
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
    void visit(PatternIdentifier &node) override;
    void visit(PatternLiteral &node) override;
    void visit(PatternPath &node) override;
    void visit(PatternReference &node) override;
    void visit(PatternWildCard &node) override;

    //Statement
    void visit(Statement &node) override{
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
    void visit(StmtEmpty &node) override;
    void visit(StmtExpr &node) override;
    void visit(StmtItem &node) override;
    void visit(StmtLet &node) override;

    //Type
    void visit(Type &node) override;
    void visit(TypeArray &node) override;
    void visit(TypePath &node) override;
    void visit(TypeReference &node) override;
    void visit(TypeUnit &node) override;

    //Path
    void visit(Path &node) override;
};

}