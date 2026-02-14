# pragma once
# include "../ir/IRFunction.h"
# include "Stack.h"
#include <memory>

namespace JaneZ {
class CodegenFunction{
public:
    std::shared_ptr<IRFunction> irFunc;
    Stack stack;
};
}