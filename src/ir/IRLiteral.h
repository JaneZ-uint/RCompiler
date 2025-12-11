# pragma once
# include "IRNode.h"
# include "IRVisitor.h"

namespace JaneZ {
enum IRLiteralType {
    INT_LITERAL,
    BOOL_LITERAL,
    NULL_LITERAL,
};

class IRLiteral : public IRNode {
public:
    IRLiteralType literalType;
    long long intValue;
    bool boolValue;

    IRLiteral(IRLiteralType lt, long long iv = 0, bool bv = false)
        : IRNode(), literalType(lt), intValue(iv), boolValue(bv) {}
    virtual ~IRLiteral() = default;
    void accept(IRVisitor &visitor) override {
        visitor.visit(*this);
    }
};

}