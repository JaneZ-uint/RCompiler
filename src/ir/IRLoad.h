# pragma once
# include "IRNode.h"
#include "IRType.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRLoad : public IRNode {
public:
    std::shared_ptr<IRVar> loadedVar;
    std::shared_ptr<IRVar> addressVar;
    std::shared_ptr<IRType> type;

    IRLoad(std::shared_ptr<IRVar> lV,
           std::shared_ptr<IRVar> aV,
           std::shared_ptr<IRType> t)
        : IRNode(), loadedVar(std::move(lV)), addressVar(std::move(aV)), type(std::move(t)) {}
    ~IRLoad() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}