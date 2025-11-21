# pragma once
#include "IRLiteral.h"
# include "IRNode.h"
#include "IRType.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ {
class IRStore : public IRNode {
public:
    std::shared_ptr<IRType> valueType;
    std::shared_ptr<IRVar> storeValue;
    std::shared_ptr<IRLiteral> storeLiteral;
    std::shared_ptr<IRVar> address;

    IRStore(std::shared_ptr<IRType> vT,
            std::shared_ptr<IRVar> sV,
            std::shared_ptr<IRLiteral> sL,
            std::shared_ptr<IRVar> a)
        : IRNode(), valueType(std::move(vT)), storeValue(std::move(sV)), storeLiteral(std::move(sL)), address(std::move(a)) {}
    ~IRStore() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}