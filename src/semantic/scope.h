# pragma once

#include <memory>
#include <stdexcept>
#include <unordered_map>
#include "../ast/ast.h"
#include "symbol.h"


namespace JaneZ {
class ScopeNode{    
public:
    std::shared_ptr<ASTNode> ast_node;
    std::shared_ptr<ScopeNode> parent = nullptr;
   
    std::unordered_map<std::string, std::shared_ptr<Symbol>> type_table;// struct enum trait
    std::unordered_map<std::string, std::shared_ptr<Symbol>> value_table;// variable function const 

    ScopeNode() = default;

    void addTypeSymbol(const std::string &id, std::shared_ptr<Symbol> symbol) {
        if(type_table.find(id) != type_table.end()) {
            throw std::runtime_error("Type symbol redefinition: " + id);
        }
        type_table[id] = symbol;
    }

    void addValueSymbol(const std::string &id, std::shared_ptr<Symbol> symbol) {
        if(value_table.find(id) != value_table.end()) {
            if(symbol->symbol_type == Variable && value_table[id]->symbol_type == Variable) {
                // 允许变量重复定义（覆盖）
            } else{
                throw std::runtime_error("Value symbol redefinition: " + id);
            }
        }
        value_table[id] = symbol;
    }

    std::shared_ptr<Symbol> lookupTypeSymbol(const std::string &id) {
        if(type_table.find(id) != type_table.end()) {
            return type_table[id];
        } else if(parent) {
            return parent->lookupTypeSymbol(id);
        } else {
            return nullptr;
        }
    }

    std::shared_ptr<Symbol> lookupValueSymbol(const std::string &id) {
        if(value_table.find(id) != value_table.end()) {
            return value_table[id];
        } else if(parent) {
            return parent->lookupValueSymbol(id);
        } else {
            return nullptr;
        }
    }

};

}