# pragma once
# include "IRNode.h"
#include "IRType.h"
#include "IRVar.h"
# include "IRVisitor.h"
#include <memory>

namespace JaneZ{
class IRGetptr: public IRNode{
public:
    std::shared_ptr<IRType> type;
    std::shared_ptr<IRVar> base;
    std::shared_ptr<IRVar> res;
    int offset = -1;
    std::shared_ptr<IRVar> index; // for array getptr

    IRGetptr(std::shared_ptr<IRType> type, std::shared_ptr<IRVar> base, std::shared_ptr<IRVar> res,int offset):
        type(std::move(type)), base(std::move(base)), res(std::move(res)),offset(offset){}
    IRGetptr(std::shared_ptr<IRType> type, std::shared_ptr<IRVar> base, std::shared_ptr<IRVar> res,std::shared_ptr<IRVar> index):
        type(std::move(type)), base(std::move(base)), res(std::move(res)),index(std::move(index)){}
    ~IRGetptr() override = default;
    void accept(IRVisitor &visitor) override{
        visitor.visit(*this);
    }
};

};