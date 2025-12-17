# pragma once
# include "IRNode.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRParam;
class IRLoad;
class IRVar;
class IRFunction;
class IRCall : public IRNode {
public:
    std::shared_ptr<IRParam> pList;
    //std::vector<std::shared_ptr<IRLoad>> loadList;
    std::shared_ptr<IRVar> retVar; // can be nullptr if void
    //std::shared_ptr<IRType> retType;
    std::shared_ptr<IRFunction> function;

    IRCall() = default;
    IRCall(std::shared_ptr<IRParam> pl,
           std::shared_ptr<IRVar> rv,
           std::shared_ptr<IRFunction> func)
        : pList(std::move(pl)),  retVar(std::move(rv)),
           function(std::move(func)) {}
    ~IRCall() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}