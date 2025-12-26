# pragma once
# include "IRNode.h"
# include "IRType.h"
# include "IRVisitor.h"
# include "IRValue.h"
# include <memory>
#include <utility>
# include <string>
#include <vector>

namespace JaneZ {
class IRAlloca;
class IRStore;
class IRBlock;
class IRParam;
class IRFunction : public IRValue {
public:
    std::shared_ptr<IRType> retType;
    std::string name;
    std::shared_ptr<IRParam> paramList;
    std::shared_ptr<IRBlock> body;
    std::shared_ptr<IRStructType> parentStructType; // null if not a member function
    std::vector<std::shared_ptr<IRType>> typeList;

    IRFunction() = default;
    IRFunction(std::shared_ptr<IRType> retType, std::string name,
               std::shared_ptr<IRParam> paramList,
               std::shared_ptr<IRBlock> body)
        : retType(std::move(retType)), name(std::move(name)),
          paramList(std::move(paramList)), body(std::move(body)){}
    IRFunction(std::shared_ptr<IRType> retType, std::string name,
               std::shared_ptr<IRParam> paramList):
        retType(std::move(retType)), name(std::move(name)),
        paramList(std::move(paramList)){}
    ~IRFunction() = default;

    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}