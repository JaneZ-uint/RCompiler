# pragma once                                                                                                                                                                                                                                        # pragma once

#include "../ast/ast.h"
#include "../ast/Expression/expression.h"
#include "../ast/Expression/ExprConstBlock.h"
#include "../ast/Expression/ExprStruct.h"
#include "../ast/Expression/ExprArray.h"
#include "../ast/Expression/ExprBlock.h"
#include "../ast/Expression/ExprBreak.h"
#include "../ast/Expression/ExprCall.h"
#include "../ast/Expression/ExprContinue.h"
#include "../ast/Expression/ExprField.h"
#include "../ast/Expression/ExprGroup.h"
#include "../ast/Expression/ExprIf.h"
#include "../ast/Expression/ExprIndex.h"
#include "../ast/Expression/ExprLiteral.h"
#include "../ast/Expression/ExprLoop.h"
#include "../ast/Expression/ExprMatch.h"
#include "../ast/Expression/ExprMethodcall.h"
#include "../ast/Expression/ExprOpbinary.h"
#include "../ast/Expression/ExprOpunary.h"
#include "../ast/Expression/ExprPath.h"
#include "../ast/Expression/ExprReturn.h"
#include "../ast/Expression/ExprUnderscore.h"

namespace JaneZ {
struct ConstPair{
    long long int_val;
    bool isEvaluated = false;
};

class ConstEvaluator {
public:
    ConstEvaluator() = default;

    ~ConstEvaluator() = default;

    ConstPair visit(ASTNode &node)  {
        if(auto *p = dynamic_cast<Expression *>(& node)) {
            return visit(*p);
        }
        return ConstPair{};
    }   

    ConstPair visit(Expression &node)  {
        if(auto *p = dynamic_cast<ExprArray *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprBlock *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprBreak *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprCall *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprConstBlock *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprContinue *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprField *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprGroup *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprIf *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprIndex *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprLiteral *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprLoop *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprMatch *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprMethodcall *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpbinary *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprOpunary *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprPath *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprReturn *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprStruct *>(& node)) {
            return visit(*p);
        }else if(auto *p = dynamic_cast<ExprUnderscore *>(& node)) {
            return visit(*p);
        }else{
            std::cout << "Unknown Expression type in ConstEvaluator\n";
        }
    }

    //Expression
    ConstPair visit(ExprArray &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprBlock &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprBreak &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprCall &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprConstBlock &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprContinue &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprField &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprGroup &node) {
        return visit(*node.expr);
    }

    ConstPair visit(ExprIf &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprIndex &node) {
        return visit(*node.index);
    }

    ConstPair visit(ExprLiteral &node) {
        if(node.type == LiteralType::INTEGER_LITERAL) {
            return ConstPair{static_cast<long long int>(node.integer), true};
        }
        return ConstPair{};
    }

    ConstPair visit(ExprLoop &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprMatch &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprMethodcall &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprOpbinary &node) {
        ConstPair left = visit(*node.left);
        ConstPair right = visit(*node.right);
        if (left.isEvaluated && right.isEvaluated) {
            if(node.op == binaryOp::PLUS) {
                return ConstPair{left.int_val + right.int_val, true};
            }else if(node.op == binaryOp::MINUS) {
                return ConstPair{left.int_val - right.int_val, true};
            }else if(node.op == binaryOp::MULTIPLY) {
                return ConstPair{left.int_val * right.int_val, true};
            }else if(node.op == binaryOp::DIVIDE) {
                if(right.int_val == 0) {
                    throw std::runtime_error("Division by zero in constant expression");
                }
                return ConstPair{left.int_val / right.int_val, true};
            }else if(node.op == binaryOp::MODULO) {               
                if(right.int_val == 0) {
                    throw std::runtime_error("Modulo by zero in constant expression");
                }
                return ConstPair{left.int_val % right.int_val, true};
            }else if(node.op == binaryOp::LEFT_SHIFT) {
                return ConstPair{left.int_val << right.int_val, true};
            }else if(node.op == binaryOp::RIGHT_SHIFT) {
                return ConstPair{left.int_val >> right.int_val, true};
            }else if(node.op == binaryOp::AND) {
                return ConstPair{left.int_val & right.int_val, true};
            }else if(node.op == binaryOp::OR) {
                return ConstPair{left.int_val | right.int_val, true};
            }else if(node.op == binaryOp::XOR) {
                return ConstPair{left.int_val ^ right.int_val, true};
            }else if(node.op == binaryOp::EQUAL) {
                return ConstPair{left.int_val == right.int_val, true};
            }else if(node.op == binaryOp::NOT_EQUAL) {
                return ConstPair{left.int_val != right.int_val, true};
            }else if(node.op == binaryOp::GREATER_THAN) {
                return ConstPair{left.int_val > right.int_val, true};
            }else if(node.op == binaryOp::LESS_THAN) {
                return ConstPair{left.int_val < right.int_val, true};
            }else if(node.op == binaryOp::GREATER_THAN_OR_EQUAL) {
                return ConstPair{left.int_val >= right.int_val, true};
            }else if(node.op == binaryOp::LESS_THAN_OR_EQUAL) {
                return ConstPair{left.int_val <= right.int_val, true};
            }else{              
                return ConstPair{};
            }
        }
    }

    ConstPair visit(ExprOpunary &node) {
        ConstPair expr = visit(*node.right);
        if(expr.isEvaluated) {
            if(node.op == unaryOp::NEGATE){
                return ConstPair{-expr.int_val, true};
            }else{
                return ConstPair{};
            }
        }
        return ConstPair{};
    }

    ConstPair visit(ExprPath &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprReturn &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprStruct &node) {
        return ConstPair{};
    }

    ConstPair visit(ExprUnderscore &node) {
        return ConstPair{};
    }

};
}