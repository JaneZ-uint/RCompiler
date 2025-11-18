# pragma once
# include "IRNode.h"
# include "IRType.h"
# include "IRVisitor.h"
# include <memory>
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

    IRFunction() : IRNode() {}
    ~IRFunction() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}