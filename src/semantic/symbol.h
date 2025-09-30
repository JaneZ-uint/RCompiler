# pragma once

#include "../ast/ast.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace JaneZ {
enum SymbolType{
    Variable,
    Function,
    Const,
    Struct,
    Enum,
    EnumVariant,
    Trait,
};

class Symbol{
public:
    //std::shared_ptr<ASTNode> ast_node;
    SymbolType symbol_type;
    std::string identifier;

    Symbol(SymbolType st, std::string id) : symbol_type(st), identifier(std::move(id)) {}

    Symbol() = default;

    virtual ~Symbol() = default;
};

class VariableSymbol : public Symbol{
public:
    std::shared_ptr<ASTNode> type;
    bool is_mut = false;

    VariableSymbol(std::shared_ptr<ASTNode> t, std::string id) : Symbol(Variable, std::move(id)), type(std::move(t)) {}   
    
    VariableSymbol() = default;

    ~VariableSymbol() = default;
};

class FunctionSymbol : public Symbol{
public:
    struct Param{
        std::string name;
        std::shared_ptr<ASTNode> type;
    };
    std::vector<Param> parameters;
    std::shared_ptr<ASTNode> return_type;

    FunctionSymbol(std::vector<Param> params, std::shared_ptr<ASTNode> ret_type, std::string id) 
        : Symbol(Function, std::move(id)), parameters(std::move(params)), return_type(std::move(ret_type)) {}

    FunctionSymbol() = default;

    ~FunctionSymbol() = default;
};

class ConstSymbol : public Symbol{
public:
    std::shared_ptr<ASTNode> type;
    std::shared_ptr<Expression> value;

    ConstSymbol(std::shared_ptr<ASTNode> t, std::shared_ptr<Expression> v, std::string id) 
        : Symbol(Const, std::move(id)), type(std::move(t)), value(std::move(v)) {}

    ConstSymbol() = default;

    ~ConstSymbol() = default;
};

class StructSymbol : public Symbol{
public:
    struct Field{
        std::string name;
        std::shared_ptr<ASTNode> type;
    };
    std::vector<Field> fields;
    std::unordered_map<std::string, std::shared_ptr<FunctionSymbol>> methods;
    std::unordered_map<std::string, std::shared_ptr<ConstSymbol>> associated_consts;
    //may add triats later

    StructSymbol(std::vector<Field> f, std::string id) 
        : Symbol(Struct, std::move(id)), fields(std::move(f)) {}

    StructSymbol() = default;

    ~StructSymbol() = default;
};

class EnumSymbol : public Symbol{
public:
    std::vector<std::string> variants;

    EnumSymbol(std::vector<std::string> v, std::string id) 
        : Symbol(Enum, std::move(id)), variants(std::move(v)) {}

    EnumSymbol() = default;

    ~EnumSymbol() = default;
};

class EnumVariantSymbol : public Symbol{
public:
    std::string enum_name;
    std::shared_ptr<ItemEnumDecl> enum_decl;

    EnumVariantSymbol(std::string en, std::shared_ptr<ItemEnumDecl> ed, std::string id) 
        : Symbol(Variable, std::move(id)), enum_name(std::move(en)), enum_decl(std::move(ed)) {}

    EnumVariantSymbol() = default;

    ~EnumVariantSymbol() = default;
};

class TraitSymbol : public Symbol{
public:
    std::unordered_map<std::string, std::shared_ptr<FunctionSymbol>> methods;
    std::unordered_map<std::string, std::shared_ptr<ConstSymbol>> associated_consts;

    TraitSymbol(std::string id) : Symbol(Trait, std::move(id)) {}

    TraitSymbol() = default;

    ~TraitSymbol() = default;
};
}