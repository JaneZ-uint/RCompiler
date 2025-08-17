# pragma once

#include "pattern.h"
#include <memory>
#include <utility>
#include <vector>
namespace JaneZ {
class PatternStruct : public Pattern {
private:
    std::vector<std::pair<std::string, std::unique_ptr<Pattern>>> pattern_struct;

public:
    PatternStruct(std::vector<std::pair<std::string, std::unique_ptr<Pattern>>> ps):pattern_struct(std::move(ps)){}

    ~PatternStruct() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}