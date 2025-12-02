# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
# include "IRType.h"
# include <memory>
# include <string>

namespace JaneZ {
class IRVar : public IRNode {
public:
    std::shared_ptr<IRType> type;
    std::string varName;
    std::string reName;

    IRVar(std::shared_ptr<IRType> tp, const std::string &vn, const std::string &irn)
        : type(std::move(tp)), varName(vn), reName(irn) {}
    ~IRVar() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}