# pragma once
# include "IRNode.h"
#include "IRType.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRLoad : public IRNode {
public:
    std::shared_ptr<IRVar> tmp;
    std::shared_ptr<IRVar> addressVar;
    std::shared_ptr<IRType> type;
    bool w64tag = false; // 64-bit width tag (usize/isize destination)
    bool utag = false; // unsigned load tag (u32 on RV64 must use lwu)

    IRLoad() = default;
    IRLoad(std::shared_ptr<IRVar> lV,
           std::shared_ptr<IRVar> aV,
           std::shared_ptr<IRType> t)
        : IRNode(), tmp(std::move(lV)), addressVar(std::move(aV)), type(std::move(t)) {}
    ~IRLoad() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}
