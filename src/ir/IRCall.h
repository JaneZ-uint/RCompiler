# pragma once
# include "IRNode.h"
#include "IRType.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>
#include <vector>

namespace JaneZ {
class IRParam;
class IRLoad;
class IRVar;
class IRFunction;
class IRCall : public IRNode {
public:
    std::shared_ptr<IRParam> paramList;
    std::vector<std::shared_ptr<IRLoad>> loadList;
    std::shared_ptr<IRVar> retVar; // can be nullptr if void
    std::shared_ptr<IRType> retType;
    std::shared_ptr<IRFunction> function;

    IRCall(std::shared_ptr<IRParam> pl,
           std::vector<std::shared_ptr<IRLoad>> ll,
           std::shared_ptr<IRVar> rv,
           std::shared_ptr<IRType> rt,
           std::shared_ptr<IRFunction> func)
        : paramList(std::move(pl)), loadList(std::move(ll)), retVar(std::move(rv)),
          retType(std::move(rt)), function(std::move(func)) {}
    ~IRCall() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}