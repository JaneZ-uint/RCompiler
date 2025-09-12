# pragma once

#include "symbol.h"
#include <memory>
#include <stdexcept>
#include <unordered_map>


namespace JaneZ {
class SymbolTable{
public:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> value_space;
    std::unordered_map<std::string, std::shared_ptr<Symbol>> type_space;

    SymbolTable() = default;

    ~SymbolTable() = default;

    void add_symbol(const Symbol& sym) {
        switch (sym.getType()) {
            case SymbolType::Function:
            case SymbolType::Const:{
                if(value_space.find(sym.identifier) != value_space.end()) {
                    throw std::runtime_error("Symbol already exists in value space: " + sym.identifier);
                }
                value_space.emplace(sym.identifier, std::make_shared<Symbol>(sym));
                break;
            }
            case SymbolType::Enum:
            case SymbolType::Struct:
            case SymbolType::Trait:{
                if(type_space.find(sym.identifier) != type_space.end()) {
                    throw std::runtime_error("Symbol already exists in type space: " + sym.identifier);
                }
                type_space.emplace(sym.identifier, std::make_shared<Symbol>(sym));
                break;
            }
        }
    }
};
}