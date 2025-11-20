# pragma once
#include "IRType.h"
#include <memory>
#include <map>

namespace JaneZ {
class IRFunction;
class IRType;
class IR{
public: 
    std::map<std::string, std::shared_ptr<IRFunction>> functions;
    std::map<std::string, std::shared_ptr<IRType>> types;
};

}