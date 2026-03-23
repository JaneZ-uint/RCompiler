# pragma once
# include "../ir/IRFunction.h"
#include "ASM.h"
# include "Stack.h"
#include <memory>
#include <vector>

namespace JaneZ {
class CodegenFunction{
public:
    std::shared_ptr<IRFunction> irFunc;

    std::vector<ASMBlock> asmBlocks;
    
    Stack stack;
    
    CodegenFunction() = default;
    CodegenFunction(std::shared_ptr<IRFunction> func) : irFunc(func) {}
};
}