# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
# include "IRType.h"
# include <memory>
# include <string>

namespace JaneZ {
enum VarType{
    Alloca,
    Global,
    Constant,
};

class IRVar : public IRNode {
public:
    VarType varType;
    std::shared_ptr<IRType> type;
    std::string varName;
    std::string irName;

    IRVar(VarType vt,std::shared_ptr<IRType> tp, const std::string &vn, const std::string &irn)
        : varType(vt), type(std::move(tp)), varName(vn), irName(irn) {}
    ~IRVar() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}