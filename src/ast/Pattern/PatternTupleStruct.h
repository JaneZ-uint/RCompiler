# pragma once

#include "pattern.h"
#include <vector>
#include <memory>
#include "../Path.h"

namespace JaneZ {
class PatternTupleStruct : public Pattern {
private:
    std::unique_ptr<Path> pathInExpr; 
    std::vector<std::unique_ptr<Pattern>> tuple_struct_item;

public:
    PatternTupleStruct(std::unique_ptr<Path> pIE,std::vector<std::unique_ptr<Pattern>> tsi): 
        pathInExpr(std::move(pIE)), tuple_struct_item(std::move(tsi)){}

    ~PatternTupleStruct() = default;

    void accept(ASTVisitor &visitor) override {
        visitor.visit(*this);
    }
};
}