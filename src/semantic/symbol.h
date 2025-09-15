# pragma once

#include <memory>
#include "../ast/ast.h"
#include <string>
#include <vector>

namespace JaneZ {
class ScopeNode;

enum SymbolType{
    Variable,
    Function,
    Enum,
    Const,
    Struct,
    Trait,
};

class Symbol{
public:
    std::string identifier = "";
    ScopeNode * scope;
    //SymbolType type;
    explicit Symbol(std::string id) : identifier(std::move(id)) {}

    virtual ~Symbol() = default;

    virtual SymbolType getType() const = 0;
};

class VariableData : public Symbol{
public:
    //std::string identifier = "";
    std::shared_ptr<ASTNode> type;
    std::shared_ptr<Expression> value;
    bool is_mut = false;

    VariableData(std::string id,
        std::shared_ptr<ASTNode> t,
        std::shared_ptr<Expression> v,
        bool isM = false)
        : Symbol(std::move(id)), type(std::move(t)), value(std::move(v)), is_mut(isM) {}
        
    ~VariableData() = default;  

    SymbolType getType() const override {
        return SymbolType::Variable;
    }
};

class FunctionData : public Symbol{
public:
    //std::string identifier = "";
    std::vector<std::shared_ptr<Pattern>> param_name;
    std::vector<std::shared_ptr<ASTNode>> param_type;
    std::shared_ptr<ASTNode> return_type;
    std::shared_ptr<ItemFnDecl> owner;

    FunctionData(std::string id,
        std::vector<std::shared_ptr<Pattern>> p_name,
        std::vector<std::shared_ptr<ASTNode>> p_type,
        std::shared_ptr<ASTNode> r_type,
        std::shared_ptr<ItemFnDecl> own)
        : Symbol(std::move(id)), param_name(std::move(p_name)), param_type(std::move(p_type)), return_type(std::move(r_type)), owner(std::move(own)) {}

    ~FunctionData() = default;

    SymbolType getType() const override {
        return SymbolType::Function;
    }
};

class EnumData : public Symbol{
public:
    //std::string identifier = "";
    std::vector<std::string> variants;
    std::shared_ptr<ItemEnumDecl> owner;

    EnumData(std::string id,
        std::vector<std::string> vars,
        std::shared_ptr<ItemEnumDecl> own)
        : Symbol(std::move(id)), variants(std::move(vars)), owner(std::move(own)) {}

    ~EnumData() = default;

    SymbolType getType() const override {
        return SymbolType::Enum;
    }
};

class ConstData : public Symbol{
public:
    //std::string identifier = "";
    std::shared_ptr<ASTNode> type;
    std::shared_ptr<Expression> value; 
    std::shared_ptr<ItemConstDecl> owner;

    ConstData(std::string id,
        std::shared_ptr<ASTNode> t,
        std::shared_ptr<Expression> v,
        std::shared_ptr<ItemConstDecl> own)
        : Symbol(std::move(id)), type(std::move(t)), value(std::move(v)), owner(std::move(own)) {}

    ~ConstData() = default;

    SymbolType getType() const override {
        return SymbolType::Const;
    }
};

class StructData : public Symbol{
public:
    //std::string identifier = "";
    std::vector<std::pair<std::string,std::shared_ptr<ASTNode>>> fields;
    std::shared_ptr<ItemStructDecl> owner;

    StructData(std::string id,
        std::vector<std::pair<std::string,std::shared_ptr<ASTNode>>> f,
        std::shared_ptr<ItemStructDecl> own)
        : Symbol(std::move(id)), fields(std::move(f)), owner(std::move(own)) {}

    ~StructData() = default;

    SymbolType getType() const override {
        return SymbolType::Struct;
    }
};

class TraitData : public Symbol{
public:
    //std::string identifier = "";
    std::vector<std::shared_ptr<ItemFnDecl>> methods;
    std::vector<std::shared_ptr<ItemConstDecl>> associated_consts;
    std::shared_ptr<ItemTraitDecl> owner;

    TraitData(std::string id,
        std::vector<std::shared_ptr<ItemFnDecl>> m,
        std::vector<std::shared_ptr<ItemConstDecl>> a_c,
        std::shared_ptr<ItemTraitDecl> own)
        : Symbol(std::move(id)), methods(std::move(m)), associated_consts(std::move(a_c)), owner(std::move(own)) {}

    ~TraitData() = default;

    SymbolType getType() const override {
        return SymbolType::Trait;
    }
};

}