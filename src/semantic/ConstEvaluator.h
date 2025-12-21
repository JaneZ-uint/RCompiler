# pragma once                                                                                                                                                                                                                                       
#include <memory>
#include "scope.h"
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
namespace JaneZ {
class ConstEvaluator : public ASTVisitor {
public:
    std::shared_ptr<ScopeNode> ConstRoot;
    std::shared_ptr<ScopeNode> current_scope;
    std::shared_ptr<ASTRootNode> root;

    ConstEvaluator() = default;

    ~ConstEvaluator() = default;

    void visit(ASTNode &node) override{
        if(auto *p = dynamic_cast<ASTRootNode *>(& node)){
            p->accept(*this);
        }else if(auto *p = dynamic_cast<Expression *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<Item *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<Pattern *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<Statement *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<Type *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<TypeArray *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<TypePath *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<TypeReference *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<TypeUnit *>(& node)) {
            node.accept(*this);
        }else if(auto *p = dynamic_cast<Path *>(& node)) {
            node.accept(*this);
        }else{
            throw std::runtime_error("ConstEvaluator: Unhandled ASTNode type in visit(ASTNode&)");
        }
    }

    void visit(ASTRootNode &node) override{
        current_scope = std::make_shared<ScopeNode>();
        ConstRoot = current_scope;
        for(auto & item : node.child){
            item->accept(*this);
        }
    }

    //Expression
    void visit(Expression &node) override{
        if(auto *p = dynamic_cast<ExprArray *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprBlock *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprBreak *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprCall *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprConstBlock *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprContinue *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprField *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprGroup *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprIf *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprIndex *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprLiteral *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprLoop *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprMethodcall *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpbinary *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpunary *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprPath *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprReturn *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprStruct *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ExprUnderscore *>(& node)){
            visit(*p);
        }else{
            throw std::runtime_error("ConstEvaluator: Unhandled Expression type in visit(Expression&)");
        }
    }

    void visit(ExprArray &node) override{}

    void visit(ExprBlock &node) override{
        auto block_scope = std::make_shared<ScopeNode>();
        current_scope->children.push_back(block_scope);
        block_scope->parent = current_scope;
        current_scope = block_scope;
        for(auto & stmt : node.statements){
            visit(*stmt);
        }
        current_scope = current_scope->parent;
    }

    void visit(ExprBreak &node) override{}

    void visit(ExprCall &node) override{}

    void visit(ExprConstBlock &node) override{}

    void visit(ExprContinue &node) override{}

    void visit(ExprField &node) override{}

    void visit(ExprGroup &node) override{}

    void visit(ExprIf &node) override{
        auto if_scope = std::make_shared<ScopeNode>();
        current_scope->children.push_back(if_scope);
        if_scope->parent = current_scope;
        current_scope = if_scope;
        if(node.thenBlock){
            for(auto & stmt : node.thenBlock->statements){
                visit(*stmt);
            }
        }
        current_scope = current_scope->parent;
        if(node.elseBlock){
            if(auto *p = dynamic_cast<ExprBlock *>(& *node.elseBlock)){
                auto else_scope = std::make_shared<ScopeNode>();
                current_scope->children.push_back(else_scope);
                else_scope->parent = current_scope;
                current_scope = else_scope;
                for(auto & stmt : p->statements){
                    visit(*stmt);
                }
                current_scope = current_scope->parent;
            }else if(auto *p = dynamic_cast<ExprIf *>(& *node.elseBlock)){
                visit(*p);
            }
        }
    }

    void visit(ExprIndex &node) override{}

    void visit(ExprLiteral &node) override{}

    void visit(ExprLoop &node) override{
        if(node.infinitieLoop){
            auto loop_scope = std::make_shared<ScopeNode>();
            current_scope->children.push_back(loop_scope);
            loop_scope->parent = current_scope;
            current_scope = loop_scope;
            for(auto & stmt : node.infinitieLoop->statements){
                visit(*stmt);
            }
            current_scope = current_scope->parent;
        }else if(node.PredicateLoopExpression){
            auto loop_scope = std::make_shared<ScopeNode>();
            current_scope->children.push_back(loop_scope);
            loop_scope->parent = current_scope;
            current_scope = loop_scope;
            for(auto & stmt : node.PredicateLoopExpression->statements){
                visit(*stmt);
            }
            current_scope = current_scope->parent;
        }
    }

    void visit(ExprMethodcall &node) override{}

    void visit(ExprOpbinary &node) override{}

    void visit(ExprOpunary &node) override{}

    void visit(ExprPath &node) override{}

    void visit(ExprReturn &node) override{}

    void visit(ExprStruct &node) override{}

    void visit(ExprUnderscore &node) override{}
    
    //Item 
    void visit(Item &node) override{
        if(auto *p = dynamic_cast<ItemConstDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemFnDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemImplDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemStructDecl *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& node)){
            visit(*p);
        }else{
            throw std::runtime_error("ConstEvaluator: Unhandled Item type in visit(Item&)");
        }
    }

    void visit(ItemConstDecl &node) override{
        if(node.type){
            if(auto *p = dynamic_cast<Type *>(& *node.type)){
                if(p->type == I32 || p->type == U32 || p->type == ISIZE || p->type == USIZE ){
                    if(node.expr){
                        if(auto *expr_lit = dynamic_cast<ExprLiteral *>(& *node.expr)){
                            if(expr_lit->type== INTEGER_LITERAL){
                                long long int val = expr_lit->integer;
                                node.value = val;
                                auto var_symbol = std::make_shared<VariableSymbol>(node.type, val, node.identifier);
                                current_scope->addValueSymbol(node.identifier,var_symbol);
                            }else{
                                throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, expected IntLiteral");
                            }
                        }else if(auto *expr_lit = dynamic_cast<ExprOpbinary *>(& *node.expr)){
                            if(auto *left_lit = dynamic_cast<ExprLiteral *>(& *expr_lit->left)){
                                if(auto *right_lit = dynamic_cast<ExprLiteral *>(& *expr_lit->right)){
                                    if(left_lit->type== INTEGER_LITERAL && right_lit->type== INTEGER_LITERAL){
                                        long long int val;
                                        if(expr_lit->op == PLUS){
                                            val = left_lit->integer + right_lit->integer;
                                        }else if(expr_lit->op == MINUS){
                                            val = left_lit->integer - right_lit->integer;
                                        }else if(expr_lit->op == MULTIPLY){
                                            val = left_lit->integer * right_lit->integer;
                                        }else if(expr_lit->op == DIVIDE){
                                            val = left_lit->integer / right_lit->integer;
                                        }
                                        node.value = val;
                                        auto var_symbol = std::make_shared<VariableSymbol>(node.type, val, node.identifier);
                                        current_scope->addValueSymbol(node.identifier,var_symbol);
                                    }else{
                                        throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, expected IntLiteral");
                                    }
                                }else if(auto *right_lit = dynamic_cast<Path *>(& *expr_lit->right)){
                                    std::string right_name = right_lit->pathSegments.identifier;
                                    auto symbol = current_scope->lookupValueSymbol(right_name);
                                    if(symbol){
                                        if(auto var_symbol = std::dynamic_pointer_cast<VariableSymbol>(symbol)){
                                            if(left_lit->type== INTEGER_LITERAL){
                                                long long int val;
                                                if(expr_lit->op == PLUS){
                                                    val = left_lit->integer + var_symbol->value;
                                                }else if(expr_lit->op == MINUS){
                                                    val = left_lit->integer - var_symbol->value;
                                                }else if(expr_lit->op == MULTIPLY){
                                                    val = left_lit->integer * var_symbol->value;
                                                }else if(expr_lit->op == DIVIDE){
                                                    val = left_lit->integer / var_symbol->value;
                                                }
                                                node.value = val;
                                                auto new_var_symbol = std::make_shared<VariableSymbol>(node.type, val, node.identifier);
                                                current_scope->addValueSymbol(node.identifier,new_var_symbol);
                                            }else{
                                                throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, expected IntLiteral");
                                            }
                                        }
                                    }else{
                                        throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, unresolved symbol in expression");
                                    }
                                }
                            }else if(auto *right_lit = dynamic_cast<ExprLiteral *>(& *expr_lit->right)){
                                if(auto *left_lit = dynamic_cast<ExprLiteral *>(& *expr_lit->left)){
                                    if(left_lit->type== INTEGER_LITERAL && right_lit->type== INTEGER_LITERAL){
                                        long long int val;
                                        if(expr_lit->op == PLUS){
                                            val = left_lit->integer + right_lit->integer;
                                        }else if(expr_lit->op == MINUS){
                                            val = left_lit->integer - right_lit->integer;
                                        }else if(expr_lit->op == MULTIPLY){
                                            val = left_lit->integer * right_lit->integer;
                                        }else if(expr_lit->op == DIVIDE){
                                            val = left_lit->integer / right_lit->integer;
                                        }
                                        node.value = val;
                                        auto var_symbol = std::make_shared<VariableSymbol>(node.type, val, node.identifier);
                                        current_scope->addValueSymbol(node.identifier,var_symbol);
                                    }else{
                                        throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, expected IntLiteral");
                                    }
                                }else if(auto *left_lit = dynamic_cast<Path *>(& *expr_lit->left)){
                                    std::string left_name = left_lit->pathSegments.identifier;
                                    auto symbol = current_scope->lookupValueSymbol(left_name);
                                    if(symbol){
                                        if(auto var_symbol = std::dynamic_pointer_cast<VariableSymbol>(symbol)){
                                            if(right_lit->type== INTEGER_LITERAL){
                                                long long int val;
                                                if(expr_lit->op == PLUS){
                                                    val = var_symbol->value + right_lit->integer;
                                                }else if(expr_lit->op == MINUS){
                                                    val = var_symbol->value - right_lit->integer;
                                                }else if(expr_lit->op == MULTIPLY){
                                                    val = var_symbol->value * right_lit->integer;
                                                }else if(expr_lit->op == DIVIDE){
                                                    val = var_symbol->value / right_lit->integer;
                                                }
                                                node.value = val;
                                                auto new_var_symbol = std::make_shared<VariableSymbol>(node.type, val, node.identifier);
                                                current_scope->addValueSymbol(node.identifier,new_var_symbol);
                                            }
                                        }else{
                                            throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, expected VariableSymbol");
                                        }
                                    }else{
                                        throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, unresolved symbol in expression");
                                    }
                                }
                            }else if(auto *left_lit = dynamic_cast<ExprOpbinary *>(& *expr_lit->left)){
                                if(left_lit->op == PLUS){
                                    if(auto *left_left_lit = dynamic_cast<Path *>(& *left_lit->left)){
                                        std::string left_left_name = left_left_lit->pathSegments.identifier;
                                        auto left_left_symbol = current_scope->lookupValueSymbol(left_left_name);
                                        if(auto var_symbol = std::dynamic_pointer_cast<VariableSymbol>(left_left_symbol)){
                                            if(auto *left_right_lit = dynamic_cast<ExprLiteral *>(& *left_lit->right)){
                                                if(left_right_lit->type== INTEGER_LITERAL){
                                                    long long int val = var_symbol->value + left_right_lit->integer;
                                                    left_lit->constValue = val;
                                                }
                                            }
                                        }                            
                                    }
                                }else if(left_lit->op == MINUS){
                                    if(auto *left_left_lit = dynamic_cast<Path *>(& *left_lit->left)){
                                        std::string left_left_name = left_left_lit->pathSegments.identifier;
                                        auto left_left_symbol = current_scope->lookupValueSymbol(left_left_name);
                                        if(auto var_symbol = std::dynamic_pointer_cast<VariableSymbol>(left_left_symbol)){
                                            if(auto *left_right_lit = dynamic_cast<ExprLiteral *>(& *left_lit->right)){
                                                if(left_right_lit->type== INTEGER_LITERAL){
                                                    long long int val = var_symbol->value - left_right_lit->integer;
                                                    left_lit->constValue = val;
                                                }
                                            }
                                        }                                 
                                    }
                                }else if(left_lit->op == MULTIPLY){
                                    if(auto *left_left_lit = dynamic_cast<Path *>(& *left_lit->left)){
                                        std::string left_left_name = left_left_lit->pathSegments.identifier;
                                        auto left_left_symbol = current_scope->lookupValueSymbol(left_left_name);
                                        if(auto var_symbol = std::dynamic_pointer_cast<VariableSymbol>(left_left_symbol)){
                                            if(auto *left_right_lit = dynamic_cast<ExprLiteral *>(& *left_lit->right)){
                                                if(left_right_lit->type== INTEGER_LITERAL){
                                                    long long int val = var_symbol->value * left_right_lit->integer;
                                                    left_lit->constValue = val;
                                                }
                                            }
                                        }                                 
                                    }
                                }else if(left_lit->op == DIVIDE){
                                    if(auto *left_left_lit = dynamic_cast<Path *>(& *left_lit->left)){
                                        std::string left_left_name = left_left_lit->pathSegments.identifier;
                                        auto left_left_symbol = current_scope->lookupValueSymbol(left_left_name);
                                        if(auto var_symbol = std::dynamic_pointer_cast<VariableSymbol>(left_left_symbol)){
                                            if(auto *left_right_lit = dynamic_cast<ExprLiteral *>(& *left_lit->right)){
                                                if(left_right_lit->type== INTEGER_LITERAL){
                                                    long long int val = var_symbol->value / left_right_lit->integer;
                                                    left_lit->constValue = val;
                                                }
                                            }
                                        }                                 
                                    }
                                }

                                if(auto *right_lit = dynamic_cast<ExprLiteral *>(& *expr_lit->right)){
                                    if(right_lit->type== INTEGER_LITERAL){
                                        long long int val;
                                        if(expr_lit->op == PLUS){
                                            val = left_lit->constValue + right_lit->integer;
                                        }else if(expr_lit->op == MINUS){
                                            val = left_lit->constValue - right_lit->integer;
                                        }else if(expr_lit->op == MULTIPLY){
                                            val = left_lit->constValue * right_lit->integer;
                                        }else if(expr_lit->op == DIVIDE){
                                            val = left_lit->constValue / right_lit->integer;
                                        }
                                        node.value = val;
                                        auto var_symbol = std::make_shared<VariableSymbol>(node.type, val, node.identifier);
                                        current_scope->addValueSymbol(node.identifier,var_symbol);
                                    }else{
                                        throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, expected IntLiteral");
                                    }
                                }
                            }
                            
                        }
                    }
                    //todo
                }else if(p->type == BOOL){
                    if(node.expr){
                        if(auto *expr_lit = dynamic_cast<ExprLiteral *>(& *node.expr)){
                            if(expr_lit->type== TRUE){
                                node.value = 1;
                                auto var_symbol = std::make_shared<VariableSymbol>(node.type, 1, node.identifier);
                                current_scope->addValueSymbol(node.identifier,var_symbol);
                            }else if(expr_lit->type== FALSE){
                                node.value = 0;
                                auto var_symbol = std::make_shared<VariableSymbol>(node.type, 0, node.identifier);
                                current_scope->addValueSymbol(node.identifier,var_symbol);
                            }else{
                                throw std::runtime_error("ConstEvaluator: ConstDecl value type mismatch, expected BoolLiteral");
                            }
                        }
                    }
                    //todo
                }
            }
        }
    }
    void visit(ItemEnumDecl &node) override{}
    void visit(ItemFnDecl &node) override{
        auto fn_scope = std::make_shared<ScopeNode>();
        current_scope->children.push_back(fn_scope);
        fn_scope->parent = current_scope;
        current_scope = fn_scope;
        if(node.fnBody){
            for(auto & stmt : node.fnBody->statements){
                visit(*stmt);
            }
        }
        current_scope = current_scope->parent;
    }
    void visit(ItemImplDecl &node) override{
        for (auto & item_const: node.item_trait_const) {
            visit(*item_const);
        }
        for(auto & item_fn : node.item_trait_fn){
            visit(*item_fn);
        }
    }
    void visit(ItemStructDecl &node) override{
        for(auto &structVar : node.item_struct){
            visit(*structVar.structElem);
        }
    }
    void visit(ItemTraitDecl &node) override{}

    //Pattern
    void visit(Pattern &node) override{}
    void visit(PatternIdentifier &node) override{}
    void visit(PatternLiteral &node) override{}
    void visit(PatternPath &node) override{}
    void visit(PatternReference &node) override{}
    void visit(PatternWildCard &node) override{}

    //Statement
    void visit(Statement &node) override{
        if(auto *p = dynamic_cast<StmtEmpty *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<StmtExpr *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<StmtItem *>(& node)){
            visit(*p);
        }else if(auto *p = dynamic_cast<StmtLet *>(& node)){
            visit(*p);
        }else{
            throw std::runtime_error("ConstEvaluator: Unhandled Statement type in visit(Statement&)");
        }
    }

    void visit(StmtEmpty &node) override{}

    void visit(StmtExpr &node) override{
        visit(*node.stmtExpr);
    }

    void visit(StmtItem &node) override{
        visit(*node.stmt_item);
    }

    void visit(StmtLet &node) override{
        if(node.type){
            visit(*node.type);
        }
        if(node.expression){
            visit(*node.expression);
        }
    }

    //Type
    void visit(Type &node) override{}

    void visit(TypeArray &node) override{
        if(node.type){
            visit(*node.type);
        }
        if(node.expr){
            visit(*node.expr);
        }
    }

    void visit(TypePath &node) override{}

    void visit(TypeReference &node) override{}

    void visit(TypeUnit &node) override{}

    //Path
    void visit(Path &node) override{}
};
}