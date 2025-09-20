# pragma once
#include "../ast.h"

namespace JaneZ {
enum RustType{
    BOOL,
    U32,
    I32,
    USIZE,
    ISIZE,
    CHAR,
    STR,
    ENUM,
    ARRAY,
    PATH,
    REFERENCE,
    UNIT,
};

class Type : public ASTNode {
public:
    RustType type;

    Type(RustType t) : type(t) {}

    ~Type() = default;
  
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}