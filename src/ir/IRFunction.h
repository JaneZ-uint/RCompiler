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
    std::shared_ptr<IRBlock> body;
    std::shared_ptr<IRBlock> retBlock;

    IRFunction(std::shared_ptr<IRType> retType, std::string name,
               std::shared_ptr<IRParam> paramList,
               std::shared_ptr<IRBlock> body = nullptr)
        : retType(std::move(retType)), name(std::move(name)),
          paramList(std::move(paramList)), body(std::move(body)){}
    ~IRFunction() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}