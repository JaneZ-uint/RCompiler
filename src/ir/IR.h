# pragma once
#include "IRType.h"
#include "IRVar.h"
#include <memory>
#include <map>
#include <string>

namespace JaneZ {
class IRFunction;
class IRType;
class IRVar;
class IR{
public: 
    std::map<std::string, std::shared_ptr<IRFunction>> functions;
    std::map<std::string, std::shared_ptr<IRType>> types;
    std::map<std::string, std::shared_ptr<IRVar>> vars;
    std::map<std::string, int> vars_cnt;
    std::map<std::string, int> types_cnt;
    std::shared_ptr<IRNode> current_ir_node;
    int label_cnt = 0;
};

}