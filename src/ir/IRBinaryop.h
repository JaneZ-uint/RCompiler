# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRVar;
class IRLiteral;
class IRLoad;
class IRStore;
enum IROp{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    ADD_EQ,
    SUB_EQ,
    MUL_EQ,
    DIV_EQ,
    MOD_EQ,
    EQ,
    NEQ,
    LT,
    GT,
    LEQ,
    GEQ,
    LOGICALAND,
    LOGICALOR,
    ASSIGNEQ,
    ASCAST,
};

class IRBinaryop : public IRNode {
public:
    IROp op;
    std::shared_ptr<IRVar> result;

    IRBinaryop() = default;
    IRBinaryop(IROp operation,std::shared_ptr<IRVar> res) : IRNode(), op(operation), result(std::move(res)) {}
    virtual ~IRBinaryop() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRAdd : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRAdd(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(ADD,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)) {}
    ~IRAdd() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRSub : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;  

    IRSub(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(SUB,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)) {}
    ~IRSub() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRMul : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRMul(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(MUL,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)) {}
    ~IRMul() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRDiv : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRDiv(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(DIV,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRDiv() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRMod : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRMod(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(MOD,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRMod() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IREq : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IREq() = default;
    IREq( std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(EQ,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IREq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRNeq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;   
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRNeq() = default;
    IRNeq(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(NEQ,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRNeq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRLt : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRLt( std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(LT,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRLt() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRGt : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;          

    IRGt( std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(GT,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRGt() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRLeq : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRLeq(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(LEQ,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRLeq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRGeq : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRGeq(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(GEQ,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRGeq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRLogicalAnd : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;

    IRLogicalAnd(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(LOGICALAND,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRLogicalAnd() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRLogicalOr : public IRBinaryop {
public:
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;  

    IRLogicalOr(std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(LOGICALOR,std::move(res)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)){}
    ~IRLogicalOr() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}