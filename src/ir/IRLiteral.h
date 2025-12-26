# pragma once
# include "IRNode.h"
# include "IRVisitor.h"
# include "IRValue.h"

namespace JaneZ {
enum IRLiteralType {
    INT_LITERAL,
    BOOL_LITERAL,
    NULL_LITERAL,
};

class IRLiteral : public IRValue {
public:
    IRLiteralType literalType;
    long long intValue;
    bool boolValue;

    IRLiteral() = default;
    IRLiteral(IRLiteralType lt, long long iv = 0, bool bv = false)
        : IRValue(), literalType(lt), intValue(iv), boolValue(bv) {}
    ~IRLiteral() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}