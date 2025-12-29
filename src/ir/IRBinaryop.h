# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
# include "IRValue.h"
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
    XOROP,
    XOROPEQ,
    OROP,
    ANDOP,
    LEFTSHIFTOP,
    RIGHTSHIFTOP,
    LEFTSHIFTOPEQ,
    RIGHTSHIFTOPEQ,
};

class IRBinaryop : public IRNode {
public:
    IROp op;
    std::shared_ptr<IRValue> leftValue;
    std::shared_ptr<IRValue> rightValue;
    std::shared_ptr<IRVar> result;
    bool utag = false; // unsigned tag
    bool i8tag = false; // i8 tag

    IRBinaryop() = default;
    IRBinaryop(IROp operation,std::shared_ptr<IRVar> res) : IRNode(), op(operation), result(std::move(res)) {}
    virtual ~IRBinaryop() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};
} // namespace JaneZ