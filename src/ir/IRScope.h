# pragma once

# include <memory>
# include <unordered_map>
#include "IRFunction.h"
# include "IRType.h"
# include "IRVar.h"
# include <stdexcept>

namespace JaneZ {
class IRScope {
public:
    std::shared_ptr<IRScope> parent = nullptr;

    std::unordered_map<std::string, std::shared_ptr<IRType>> type_table;
    std::unordered_map<std::string, std::shared_ptr<IRVar>> value_table;
    std::unordered_map<std::string, std::shared_ptr<IRFunction>> function_table;
    std::unordered_map<std::string ,long long int> constant_table;

    IRScope() = default;

    void addTypeSymbol(const std::string &name, std::shared_ptr<IRType> type) {
        if(type_table.find(name) != type_table.end()) {
            throw std::runtime_error("Type " + name + " already defined in this scope.");
        }
        type_table[name] = type;
    }

    void addValueSymbol(const std::string &name, std::shared_ptr<IRVar> var) {
        if(value_table.find(name) != value_table.end()) {
            throw std::runtime_error("Variable " + name + " already defined in this scope.");
        }
        value_table[name] = var;
    }

    void addFunctionSymbol(const std::string &name, std::shared_ptr<IRFunction> func) {
        if(function_table.find(name) != function_table.end()) {
            throw std::runtime_error("Function " + name + " already defined in this scope.");
        }
        function_table[name] = func;
    }

    void addConstantSymbol(const std::string &name, long long int value) {
        if(constant_table.find(name) != constant_table.end()) {
            throw std::runtime_error("Constant " + name + " already defined in this scope.");
        }
        constant_table[name] = value;
    }

    std::shared_ptr<IRType> lookupTypeSymbol(const std::string &name) {
        if(type_table.find(name) != type_table.end()) {
            return type_table[name];
        } else if(parent != nullptr) {
            return parent->lookupTypeSymbol(name);
        } else {
            throw std::runtime_error("Type " + name + " not found.");
        }
    }

    std::shared_ptr<IRVar> lookupValueSymbol(const std::string &name) {
        if(value_table.find(name) != value_table.end()) {
            return value_table[name];
        } else if(parent != nullptr) {
            return parent->lookupValueSymbol(name);
        } else {
            throw std::runtime_error("Variable " + name + " not found.");
        }
    }

    std::shared_ptr<IRFunction> lookupFunctionSymbol(const std::string &name) {
        if(function_table.find(name) != function_table.end()) {
            return function_table[name];
        } else if(parent != nullptr) {
            return parent->lookupFunctionSymbol(name);
        } else {
            throw std::runtime_error("Function " + name + " not found.");
        }
    }

    long long int lookupConstantSymbol(const std::string &name) {
        if(constant_table.find(name) != constant_table.end()) {
            return constant_table[name];
        } else if(parent != nullptr) {
            return parent->lookupConstantSymbol(name);
        } else {
            throw std::runtime_error("Constant " + name + " not found.");
        }
    }
};  
}