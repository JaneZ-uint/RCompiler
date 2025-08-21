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
    ARRAY,
    STRUCT,
    ENUM,
    REF,
};

class Type : public ASTNode {
private:
    RustType type;

public:
    Type(RustType t) : type(t) {}

    ~Type() = default;
  
    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}