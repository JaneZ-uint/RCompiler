# pragma once

#include "expression.h"
#include <memory>
#include <string>
#include <vector>

namespace JaneZ {
class Path;
struct StructExprField{
    std::string identifier;
    std::unique_ptr<Expression> expr;
};

class ExprStruct : public Expression {
public:
    std::unique_ptr<Expression> pathInExpr;
    std::vector<StructExprField> structExprFields;

    ExprStruct(std::unique_ptr<Expression> path, std::vector<StructExprField> fields)
        : pathInExpr(std::move(path)), structExprFields(std::move(fields)) {}

    ~ExprStruct() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}