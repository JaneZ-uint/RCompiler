# pragma once

#include "pattern.h"
#include <string>

namespace JaneZ {
class PatternIdentifier : public Pattern {
public:
    std::string identifier;
    bool is_ref;
    bool is_mut;

    PatternIdentifier(std::string id, bool ref = false, bool mut = false)
        : identifier(std::move(id)), is_ref(ref), is_mut(mut) {}

    ~PatternIdentifier() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}