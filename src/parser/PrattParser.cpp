# include "parser.h"
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <unordered_map>

namespace JaneZ{
struct ExprToken{
    Token current;
    size_t leftPower = 0;
    size_t rightPower = 0;
};

struct bindingPower{
    size_t leftPower = 0;
    size_t rightPower = 0;
};

static std::unordered_map<tokenType,bindingPower> bindingPowerMap = {

};

binaryOp getBinaryOp(tokenType current){
    switch (current) {
        case kPLUS:{
            return PLUS;
        }
        case kMINUS:{
            return MINUS;
        }
        case kSTAR:{
            return MULTIPLY;
        }
        case kSLASH:{
            return DIVIDE;
        }
        case kPERCENT:{
            return MODULO;
        }
        case kAND:{
            return AND;
        }
        case kOR:{
            return OR;
        }
        case kCARET:{
            return XOR;
        }
        case kSHL:{
            return LEFT_SHIFT;
        }
        case kSHR:{
            return RIGHT_SHIFT;
        }
        case kPLUSEQ:{
            return PLUS_EQUAL;
        }
        case kMINUSEQ:{
            return MINUS_EQUAL;
        }
        case kSTAREQ:{
            return MULTIPLY_EQUAL;
        }
        case kSLASHEQ:{
            return DIVIDE_EQUAL;
        }
        case kPERCENTEQ:{
            return MODULO_EQUAL;
        }
        case kCARETEQ:{
            return XOR_EQUAL;
        }
        case kANDEQ:{
            return AND_EQUAL;
        }
        case kOREQ:{
            return OR_EQUAL;
        }
        case kSHLEQ:{
            return LEFT_SHIFT_EQUAL;
        }
        case kSHREQ:{
            return RIGHT_SHIFT_EQUAL;
        }
        case kEQ:{
            return ASSIGN;
        }
        case kEQEQ:{
            return EQUAL;
        }
        case kNE:{
            return NOT_EQUAL;
        }
        case kGT:{
            return GREATER_THAN;
        }
        case kLT:{
            return LESS_THAN;
        }
        case kGE:{
            return GREATER_THAN_OR_EQUAL;
        }
        case kLE:{
            return LESS_THAN_OR_EQUAL;
        }
        case kANDAND:{
            return LOGICAL_AND;
        }
        case kOROR:{
            return LOGICAL_OR;
        }
        case kAS: {
            return AS_CAST;
        }
        default: {
            throw std::runtime_error("Not a binary op.");
        }
    }
}

std::unique_ptr<Expression> Parser::parse_expr() {
    
}

}