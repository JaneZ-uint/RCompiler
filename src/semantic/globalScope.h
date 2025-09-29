# pragma once

#include "scope.h"
#include "../ast/astvisitor.h"
#include "../ast/root.h"
#include "../ast/Item/ItemConst.h"
#include "../ast/Item/ItemEnum.h"
#include "../ast/Item/ItemFn.h"
#include "../ast/Item/ItemImpl.h"
#include "../ast/Item/ItemStruct.h"
#include "../ast/Item/ItemTrait.h"
#include "../ast/Pattern/PatternIdentifier.h"
#include "../ast/Pattern/PatternReference.h"
#include "../ast/Type/TypePath.h"
#include "../ast/Path.h"
#include "symbol.h"
#include <iostream>
#include <memory>
#include <vector>


namespace JaneZ { 
class GlobalScopeBuilder: public ASTVisitor{
public:
    std::shared_ptr<ScopeNode> global_scope;

    std::vector<ItemImplDecl> impls; //store all impls for later use

    GlobalScopeBuilder() = default;

    ~GlobalScopeBuilder() = default;

    void visit(ASTNode &node) override {}

    void visit(ASTRootNode &node) override {
        global_scope = std::make_shared<ScopeNode>();
        global_scope->ast_node = std::make_shared<ASTRootNode>(node);
        std::shared_ptr<FunctionSymbol> exitFunc = std::make_shared<FunctionSymbol>();
        exitFunc->symbol_type = Function;
        exitFunc->identifier = "exit";
        exitFunc->return_type = std::dynamic_pointer_cast<ASTNode>(std::make_shared<TypeUnit>());
        global_scope->addValueSymbol("exit", exitFunc);
        for(auto &item : node.child) {
            visit(*item);
        }
        //After visiting all items, process impls
        for(auto &impl : impls) {
            visit(impl);
        }
    }

    //Item
    void visit(Item &node) override {
        if(auto *p = dynamic_cast<ItemConstDecl *>(& node)) {
            p->accept(*this);
        }else if(auto *p = dynamic_cast<ItemEnumDecl *>(& node)) {
            p->accept(*this);
        }else if(auto *p = dynamic_cast<ItemFnDecl *>(& node)) {
            p->accept(*this);
        }else if(auto *p = dynamic_cast<ItemImplDecl *>(& node)) {
            //p->accept(*this);
            impls.push_back(*p);
        }else if(auto *p = dynamic_cast<ItemStructDecl *>(& node)) {    
            p->accept(*this);
        }else if(auto *p = dynamic_cast<ItemTraitDecl *>(& node)) {
            p->accept(*this);
        }else{
            std::cerr << "Unknown Item type in GlobalScopeBuilder\n";
        }
    }

    void visit(ItemConstDecl &node) override{
        std::shared_ptr<ConstSymbol> symbol = std::make_shared<ConstSymbol>();
        symbol->symbol_type = Const;
        symbol->identifier = node.identifier;
        symbol->type = node.type;
        symbol->value = node.expr;
        global_scope->addValueSymbol(node.identifier, symbol);
    }

    void visit(ItemFnDecl &node) override{
        std::shared_ptr<FunctionSymbol> symbol = std::make_shared<FunctionSymbol>();
        symbol->symbol_type = Function;
        symbol->identifier = node.identifier;
        if(node.fnParameters.FunctionParam.size() > 0){
            for(auto &param : node.fnParameters.FunctionParam){
                if(auto *p = dynamic_cast<PatternIdentifier *>(& *param.pattern)){
                    symbol->parameters.push_back({p->identifier,param.type});
                }else if(auto *p = dynamic_cast<PatternReference *>(& *param.pattern)){
                    if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                        symbol->parameters.push_back({q->identifier,param.type});
                    }else{
                        std::cerr << "Unsupported pattern in function parameter in GlobalScopeBuilder\n";
                    }
                }
            }
        }
        if(node.returnType){
            symbol->return_type = node.returnType;
        }else{
            symbol->return_type = std::dynamic_pointer_cast<ASTNode>(std::make_shared<TypeUnit>());
        }
        global_scope->addValueSymbol(node.identifier, symbol);
    }

    void visit(ItemEnumDecl &node) override{
        std::shared_ptr<EnumSymbol> symbol = std::make_shared<EnumSymbol>();
        symbol->symbol_type = Enum;
        symbol->identifier = node.identifier;
        if(node.item_enum.size() > 0) {
            for(auto &var : node.item_enum) {
                symbol->variants.push_back(var);
            }
        }
        global_scope->addTypeSymbol(node.identifier, symbol);
    }

    void visit(ItemImplDecl &node) override{
        if(node.identifier == ""){
            std::string typeName = "";
            if(auto *p = dynamic_cast<Path *>(& *node.targetType)){
                typeName = p->pathSegments.identifier;
            }
            auto structSymbol = global_scope->lookupTypeSymbol(typeName);
            if(!structSymbol) {
                throw std::runtime_error("Type symbol not found: " + typeName);
            }
            if(structSymbol->symbol_type != Struct) {
                throw std::runtime_error("Type symbol is not a struct: " + typeName);
            }
            for(auto &const_item : node.item_trait_const) {
                std::shared_ptr<ConstSymbol> symbol = std::make_shared<ConstSymbol>();
                symbol->symbol_type = Const;
                symbol->identifier = const_item->identifier;
                symbol->type = const_item->type;
                symbol->value = const_item->expr;
                if(std::dynamic_pointer_cast<StructSymbol>(structSymbol)->associated_consts.find(const_item->identifier) != std::dynamic_pointer_cast<StructSymbol>(structSymbol)->associated_consts.end()){
                    throw std::runtime_error("Duplicate associated const in impl: " + const_item->identifier);
                }
                std::dynamic_pointer_cast<StructSymbol>(structSymbol)->associated_consts[const_item->identifier] = symbol;
            }
            for(auto &fn_item : node.item_trait_fn) {
                std::shared_ptr<FunctionSymbol> symbol = std::make_shared<FunctionSymbol>();
                symbol->symbol_type = Function;
                symbol->identifier = fn_item->identifier;
                if(fn_item->fnParameters.FunctionParam.size() > 0){
                    for(auto &param : fn_item->fnParameters.FunctionParam){
                        if(auto *p = dynamic_cast<PatternIdentifier *>(& *param.pattern)){
                            symbol->parameters.push_back({p->identifier,param.type});
                        }else if(auto *p = dynamic_cast<PatternReference *>(& *param.pattern)){
                            if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                                symbol->parameters.push_back({q->identifier,param.type});
                            }else{
                                std::cerr << "Unsupported pattern in function parameter in GlobalScopeBuilder\n";
                            }
                        }
                    }
                }
                if(fn_item->returnType){
                    symbol->return_type = fn_item->returnType;
                }else{
                    symbol->return_type = std::dynamic_pointer_cast<ASTNode>(std::make_shared<TypeUnit>());
                }
                if(std::dynamic_pointer_cast<StructSymbol>(structSymbol)->methods.find(fn_item->identifier) != std::dynamic_pointer_cast<StructSymbol>(structSymbol)->methods.end()){
                    throw std::runtime_error("Duplicate method in impl: " + fn_item->identifier);
                }
                std::dynamic_pointer_cast<StructSymbol>(structSymbol)->methods[fn_item->identifier] = symbol;
            }
        }else{
            auto traitSymbol = global_scope->lookupTypeSymbol(node.identifier);
            if(!traitSymbol) {
                throw std::runtime_error("Type symbol not found: " + node.identifier);
            }
            if(traitSymbol->symbol_type != Trait) {
                throw std::runtime_error("Type symbol is not a trait: " + node.identifier);
            }
            for(auto &const_item : node.item_trait_const) {
                if(std::dynamic_pointer_cast<TraitSymbol>(traitSymbol)->associated_consts.find(const_item->identifier) == std::dynamic_pointer_cast<TraitSymbol>(traitSymbol)->associated_consts.end()){
                    throw std::runtime_error("Associated const not found in trait: " + const_item->identifier);
                }
                //std::dynami
                // c_pointer_cast<TraitSymbol>(traitSymbol)->associated_consts[const_item->identifier] = symbol;
            }
            if(node.item_trait_fn.size() != std::dynamic_pointer_cast<TraitSymbol>(global_scope->lookupTypeSymbol(node.identifier))->methods.size()){
                throw std::runtime_error("Impl does not implement all methods of the trait: " + node.identifier);
            }
            for(auto &fn_item : node.item_trait_fn) {
                if(std::dynamic_pointer_cast<TraitSymbol>(traitSymbol)->methods.find(fn_item->identifier) == std::dynamic_pointer_cast<TraitSymbol>(traitSymbol)->methods.end()){
                    throw std::runtime_error("Method not found in trait: " + fn_item->identifier);
                }
                //std::dynamic_pointer_cast<TraitSymbol>(traitSymbol)->methods[fn_item->identifier] = symbol;
            }
        }
    }

    void visit(ItemStructDecl &node) override{
        std::shared_ptr<StructSymbol> symbol = std::make_shared<StructSymbol>();
        symbol->symbol_type = Struct;
        symbol->identifier = node.identifier;
        for(auto &struct_field: node.item_struct) {
            symbol->fields.push_back({struct_field.identifier, struct_field.structElem});
        }
        global_scope->addTypeSymbol(node.identifier, symbol);
    }

    void visit(ItemTraitDecl &node) override{
        std::shared_ptr<TraitSymbol> symbol = std::make_shared<TraitSymbol>();
        symbol->symbol_type = Trait;
        symbol->identifier = node.identifier;
        for(auto &const_item : node.item_trait_const) {
            std::shared_ptr<ConstSymbol> const_symbol = std::make_shared<ConstSymbol>();
            const_symbol->symbol_type = Const;
            const_symbol->identifier = const_item->identifier;
            const_symbol->type = const_item->type;
            const_symbol->value = const_item->expr;
            if(symbol->associated_consts.find(const_item->identifier) != symbol->associated_consts.end()){
                throw std::runtime_error("Duplicate associated const in trait: " + const_item->identifier);
            }
            symbol->associated_consts[const_item->identifier] = const_symbol;
        }
        for(auto &fn_item : node.item_trait_fn) {
            std::shared_ptr<FunctionSymbol> fn_symbol = std::make_shared<FunctionSymbol>();
            fn_symbol->symbol_type = Function;
            fn_symbol->identifier = fn_item->identifier;
            if(fn_item->fnParameters.FunctionParam.size() > 0){
                for(auto &param : fn_item->fnParameters.FunctionParam){
                    if(auto *p = dynamic_cast<PatternIdentifier *>(& *param.pattern)){
                        fn_symbol->parameters.push_back({p->identifier,param.type});
                    }else if(auto *p = dynamic_cast<PatternReference *>(& *param.pattern)){
                        if(auto *q = dynamic_cast<PatternIdentifier *>(& *p->patternWithoutRange)){
                            fn_symbol->parameters.push_back({q->identifier,param.type});
                        }else{
                            std::cerr << "Unsupported pattern in function parameter in GlobalScopeBuilder\n";
                        }
                    }
                }
            }
            if(fn_item->returnType){
                fn_symbol->return_type = fn_item->returnType;
            }else{
                fn_symbol->return_type = std::dynamic_pointer_cast<ASTNode>(std::make_shared<TypeUnit>());
            }
            if(symbol->methods.find(fn_item->identifier) != symbol->methods.end()){
                throw std::runtime_error("Duplicate method in trait: " + fn_item->identifier);
            }
            symbol->methods[fn_item->identifier] = fn_symbol;
        }
        global_scope->addTypeSymbol(node.identifier, symbol);
    }

    //Start generated by github copilot.
    //Expression
    void visit(Expression &node) override {}

    void visit(ExprArray &node) override{}

    void visit(ExprBlock &node) override{}

    void visit(ExprBreak &node) override{}

    void visit(ExprCall &node) override{}

    void visit(ExprConstBlock &node) override{} 

    void visit(ExprContinue &node) override{}

    void visit(ExprField &node) override{}

    void visit(ExprGroup &node) override{}

    void visit(ExprIf &node) override{}

    void visit(ExprIndex &node) override{}

    void visit(ExprLiteral &node) override{}

    void visit(ExprLoop &node) override{}

    //void visit(ExprMatch &node) override{}

    void visit(ExprMethodcall &node) override{}

    void visit(ExprOpbinary &node) override{}

    void visit(ExprOpunary &node) override{}

    void visit(ExprPath &node) override{}

    void visit(ExprReturn &node) override{}

    void visit(ExprStruct &node) override{}

    void visit(ExprUnderscore &node) override{}

    //Pattern
    void visit(Pattern &node) override{}

    void visit(PatternIdentifier &node) override{}

    void visit(PatternLiteral &node) override{}

    void visit(PatternPath &node) override{}

    void visit(PatternReference &node) override{}

    void visit(PatternWildCard &node) override{}

    //Statement
    void visit(Statement &node) override {}

    void visit(StmtEmpty &node) override{}

    void visit(StmtExpr &node) override{}

    void visit(StmtItem &node) override{}

    void visit(StmtLet &node) override{}

    //Type
    void visit(Type &node) override {}

    void visit(TypeArray &node) override{}

    void visit(TypePath &node) override{}

    void visit(TypeReference &node) override{}

    void visit(TypeUnit &node) override{}

    //Path
    void visit(Path &node) override{}

    //End generated by github copilot.
};
}