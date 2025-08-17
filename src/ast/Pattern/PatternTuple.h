# pragma once

#include "pattern.h"
#include <vector>
#include <memory>

namespace JaneZ {
class PatternTuple : public Pattern {
private:
    std::vector<std::unique_ptr<Pattern>> tuple_struct_item;

public:
    PatternTuple(std::vector<std::unique_ptr<Pattern>> tsi): tuple_struct_item(std::move(tsi)){}

    ~PatternTuple() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}