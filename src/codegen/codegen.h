# pragma once
# include "../ir/IRRoot.h"
#include <memory>

namespace JaneZ {
class codegen{
public:
    void generate(std::shared_ptr<IRRoot> root);
};
}