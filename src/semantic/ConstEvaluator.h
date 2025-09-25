# pragma once

#include "../ast/astvisitor.h"

namespace JaneZ {
class ConstEvaluator : public ASTVisitor{
public:
    ConstEvaluator() = default;

    ~ConstEvaluator() = default;

};
}