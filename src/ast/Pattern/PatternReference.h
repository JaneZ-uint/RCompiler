# pragma once

#include "pattern.h"
#include <memory>
#include <utility>

namespace JaneZ {
class PatternReference : public Pattern {
public:
    bool isANDAND = false;
    bool is_mut;
    std::unique_ptr<Pattern> patternWithoutRange;

    PatternReference(std::unique_ptr<Pattern> pWR, bool _isANDAND = false, bool im = false): patternWithoutRange(std::move(pWR)), isANDAND(_isANDAND), is_mut(std::move(im)) {}    

    ~PatternReference() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}