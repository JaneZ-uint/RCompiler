# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
#include <memory>
#include <vector>

namespace JaneZ {
class IRParam : public IRNode {
public:
    std::vector<std::shared_ptr<IRNode>> paramList; // IRVar or IRLiteral 

    IRParam() = default;
    IRParam(std::vector<std::shared_ptr<IRNode>> param_list)
        : paramList(std::move(param_list)) {}
    ~IRParam() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);   
    }
};

}