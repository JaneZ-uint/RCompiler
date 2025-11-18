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
};

class IRBinaryop : public IRNode {
public:
    IROp op;

    IRBinaryop(IROp operation) : IRNode(), op(operation) {}
    virtual ~IRBinaryop() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

class IRAdd : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IRAdd(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(ADD), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRAdd() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRSub : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;  

    IRSub(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(SUB), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRSub() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRMul : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IRMul(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(MUL), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRMul() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRDiv : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IRDiv(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(DIV), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRDiv() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRMod : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IRMod(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(MOD), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRMod() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRAddEq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;
    std::shared_ptr<IRStore> storeInstr;

    IRAddEq(std::shared_ptr<IRLoad> ll,
            std::shared_ptr<IRLoad> rl,
            std::shared_ptr<IRVar> l,
            std::shared_ptr<IRVar> r,
            std::shared_ptr<IRLiteral> rlit,
            std::shared_ptr<IRVar> res,std::shared_ptr<IRStore> store)
        : IRBinaryop(ADD_EQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)), storeInstr(std::move(store)) {}
    ~IRAddEq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRSubEq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;
    std::shared_ptr<IRStore> storeInstr;

    IRSubEq(std::shared_ptr<IRLoad> ll,
            std::shared_ptr<IRLoad> rl,
            std::shared_ptr<IRVar> l,
            std::shared_ptr<IRVar> r,
            std::shared_ptr<IRLiteral> rlit,
            std::shared_ptr<IRVar> res,std::shared_ptr<IRStore> store)
        : IRBinaryop(SUB_EQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)), storeInstr(std::move(store)) {}
    ~IRSubEq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRMulEq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;  
    std::shared_ptr<IRStore> storeInstr;

    IRMulEq(std::shared_ptr<IRLoad> ll,
            std::shared_ptr<IRLoad> rl,
            std::shared_ptr<IRVar> l,
            std::shared_ptr<IRVar> r,
            std::shared_ptr<IRLiteral> rlit,
            std::shared_ptr<IRVar> res,std::shared_ptr<IRStore> store)
        : IRBinaryop(MUL_EQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)), storeInstr(std::move(store)) {}
    ~IRMulEq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRDivEq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;
    std::shared_ptr<IRStore> storeInstr;

    IRDivEq(std::shared_ptr<IRLoad> ll,
            std::shared_ptr<IRLoad> rl,
            std::shared_ptr<IRVar> l,
            std::shared_ptr<IRVar> r,
            std::shared_ptr<IRLiteral> rlit,
            std::shared_ptr<IRVar> res,std::shared_ptr<IRStore> store)
        : IRBinaryop(DIV_EQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)), storeInstr(std::move(store)) {}
    ~IRDivEq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRModEq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;
    std::shared_ptr<IRStore> storeInstr;

    IRModEq(std::shared_ptr<IRLoad> ll,
            std::shared_ptr<IRLoad> rl,
            std::shared_ptr<IRVar> l,
            std::shared_ptr<IRVar> r,
            std::shared_ptr<IRLiteral> rlit,
            std::shared_ptr<IRVar> res,std::shared_ptr<IRStore> store)
        : IRBinaryop(MOD_EQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)), storeInstr(std::move(store)) {}
    ~IRModEq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IREq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IREq(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(EQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
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
    std::shared_ptr<IRVar> result;

    IRNeq(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(NEQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRNeq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRLt : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IRLt(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(LT), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRLt() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRGt : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;          

    IRGt(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(GT), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRGt() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRLeq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IRLeq(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(LEQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRLeq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class IRGeq : public IRBinaryop {
public:
    std::shared_ptr<IRLoad> leftLoad;
    std::shared_ptr<IRLoad> rightLoad;
    std::shared_ptr<IRVar> left;
    std::shared_ptr<IRLiteral> leftLiteral;
    std::shared_ptr<IRVar> right;
    std::shared_ptr<IRLiteral> rightLiteral;
    std::shared_ptr<IRVar> result;

    IRGeq(std::shared_ptr<IRLoad> ll,
          std::shared_ptr<IRLoad> rl,
          std::shared_ptr<IRVar> l,
          std::shared_ptr<IRLiteral> llit,
          std::shared_ptr<IRVar> r,
          std::shared_ptr<IRLiteral> rlit,
          std::shared_ptr<IRVar> res)
        : IRBinaryop(GEQ), leftLoad(std::move(ll)), rightLoad(std::move(rl)),
          left(std::move(l)), leftLiteral(std::move(llit)),
          right(std::move(r)), rightLiteral(std::move(rlit)),
          result(std::move(res)) {}
    ~IRGeq() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}