# pragma once
# include "IRNode.h"
#include "IRType.h"
# include "IRVisitor.h"
#include <memory>
#include <vector>


namespace JaneZ {
class IRImpl : public IRNode {
public:
    std::vector<std::shared_ptr<IRFunction>> functions;
    std::shared_ptr<IRType> mainStructType;

    IRImpl() = default;
    IRImpl(std::vector<std::shared_ptr<IRFunction>> funcs, std::shared_ptr<IRType> mainStruct)
        : functions(std::move(funcs)), mainStructType(std::move(mainStruct)) {}
    ~IRImpl() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }

};

}