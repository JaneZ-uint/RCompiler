# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
#include <memory>
#include <vector>

namespace JaneZ {
enum class BaseType {
    INT,
    VOID,
    PTR,
    ARRAY,
    FUNC,
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

class IRFuncType : public IRType {
public:
    std::shared_ptr<IRType> returnType;
    std::vector<std::shared_ptr<IRType>> paramTypes;

    IRFuncType(std::shared_ptr<IRType> rt, std::vector<std::shared_ptr<IRType>> pts) 
        : IRType(BaseType::FUNC), returnType(std::move(rt)), paramTypes(std::move(pts)) {}
    ~IRFuncType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRStructType : public IRType {
public:
    std::vector<std::shared_ptr<IRType>> memberTypes;
    
    IRStructType(std::vector<std::shared_ptr<IRType>> mts) 
        : IRType(BaseType::STRUCT), memberTypes(std::move(mts)) {}
    ~IRStructType() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}