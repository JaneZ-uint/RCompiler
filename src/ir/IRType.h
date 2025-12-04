# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
#include <memory>
#include <utility>
#include <vector>
#include <string>

namespace JaneZ {
enum class BaseType {
    INT,
    VOID,
    PTR,
    ARRAY,
    STRUCT,
};    

class IRType : public IRNode {
public:
    BaseType type;

    IRType(BaseType t) : type(t) {}
    virtual ~IRType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRIntType : public IRType {
public:
    int bitWidth;

    IRIntType(int bw) : IRType(BaseType::INT), bitWidth(bw) {}
    ~IRIntType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRVoidType : public IRType {
public:
    IRVoidType() : IRType(BaseType::VOID) {}
    ~IRVoidType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRPtrType : public IRType {
public:
    std::shared_ptr<IRType> baseType;

    IRPtrType(std::shared_ptr<IRType> bt) : IRType(BaseType::PTR), baseType(std::move(bt)) {}
    ~IRPtrType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRArrayType : public IRType {
public:
    std::shared_ptr<IRType> elementType;
    int size;

    IRArrayType(std::shared_ptr<IRType> et, int sz) : IRType(BaseType::ARRAY), elementType(std::move(et)), size(sz) {}
    ~IRArrayType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRStructType : public IRType {
public:
    std::string name;
    std::string true_name;
    std::vector<std::pair<std::string,std::shared_ptr<IRType>>> memberTypes;
    // for impl
    std::vector<std::shared_ptr<IRFunction>> memberFunctions;
    std::vector<std::pair<std::string, long long int>> memberConstants;
    
    IRStructType(std::string n, std::string tn, std::vector<std::pair<std::string,std::shared_ptr<IRType>>> mts,
        std::vector<std::shared_ptr<IRFunction>> mfs,std::vector<std::pair<std::string, long long int>> mcs) 
        : IRType(BaseType::STRUCT), name(n), true_name(tn), memberTypes(std::move(mts)), 
        memberFunctions(std::move(mfs)), memberConstants(std::move(mcs)) {}
    ~IRStructType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}