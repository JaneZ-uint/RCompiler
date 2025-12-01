# pragma once
# include "IRNode.h"
# include "IRType.h"
# include "IRVisitor.h"
# include <memory>
#include <utility>
# include <vector>
# include <string>

namespace JaneZ {
class IRAlloca;
class IRStore;
class IRBlock;
class IRParam;
class IRFunction : public IRNode {
public:
    std::shared_ptr<IRType> retType;
    std::string name;
    std::shared_ptr<IRParam> paramList;
    std::vector<std::shared_ptr<IRAlloca>> allocaList;
    std::vector<std::shared_ptr<IRStore>> storeList;
    std::shared_ptr<IRBlock> body;

    bool isImplFn = false;
    std::shared_ptr<IRStructType> structType;

    IRFunction(std::shared_ptr<IRType> rT,
        std::string n , 
        std::shared_ptr<IRParam> pL,
        std::vector<std::shared_ptr<IRAlloca>> aL,
        std::vector<std::shared_ptr<IRStore>> sL, 
        std::shared_ptr<IRBlock> b): retType(std::move(rT)),name(std::move(n)),
        paramList(std::move(pL)),allocaList(std::move(aL)),storeList(std::move(sL)),body(std::move(b)){}
    ~IRFunction() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}