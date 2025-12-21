# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
# include "IRType.h"
# include <memory>
# include <string>

extern long long int ir_cnt;

namespace JaneZ {
class IRVar : public IRNode {
public:
    std::shared_ptr<IRType> type;
    std::string varName;
    std::string reName;
    long long int serial;
    bool isSelf = false;

    IRVar(){
        serial = ir_cnt++;
    }
    IRVar(std::shared_ptr<IRType> tp, const std::string &vn, const std::string &irn)
        : type(std::move(tp)), varName(vn), reName(irn) {
        serial = ir_cnt++;
    }
    ~IRVar() = default; 
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}