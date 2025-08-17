# pragma once

#include "pattern.h"
#include <memory>
#include <utility>

namespace JaneZ {
class PatternReference : public Pattern {
private:
    bool is_mut;
    std::unique_ptr<Pattern> patternWithoutRange;

public:
    PatternReference(std::unique_ptr<Pattern> pWR, bool im = false): patternWithoutRange(std::move(pWR)),is_mut(std::move(im)) {}    

    ~PatternReference() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}