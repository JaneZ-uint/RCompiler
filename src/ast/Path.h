# pragma once

#include "ast.h"
#include <memory>
#include <string>
#include <vector>

namespace JaneZ {
class Path{
private:
    std::vector<std::string> pathSegments;

public:
    Path(std::vector<std::string> ps): pathSegments(std::move(ps)){}

    ~Path() = default;

};
}