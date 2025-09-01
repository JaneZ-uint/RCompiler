# pragma once

#include "astvisitor.h"

namespace JaneZ {
class PrintVisitor : public ASTVisitor{
public:
    ~PrintVisitor() = default;

    void visit(ASTNode &node) override;

    void visit(ASTRootNode &node) override;

    //Expression
    void visit(ExprArray &node) override;
    void visit(ExprBlock &node) override;
    void visit(ExprBreak &node) override;
    void visit(ExprCall &node) override;
    void visit(ExprContinue &node) override;
    void visit(ExprField &node) override;
    void visit(ExprGroup &node) override;
    void visit(ExprIf &node) override;
    void visit(ExprIndex &node) override;
    void visit(ExprLiteral &node) override;
    void visit(ExprLoop &node) override;
    void visit(ExprMatch &node) override;
    void visit(ExprMethodcall &node) override;
    void visit(ExprOpbinary &node) override;
    void visit(ExprOpunary &node) override;
    void visit(ExprPath &node) override;
    void visit(ExprReturn &node) override;
    void visit(ExprTuple &node) override;
    void visit(ExprUnderscore &node) override;
    void visit(ExprWhile &node) override;
    
    //Item 
    void visit(ItemConstDecl &node) override;
    void visit(ItemEnumDecl &node) override;
    void visit(ItemFnDecl &node) override;
    void visit(ItemImplDecl &node) override;
    void visit(ItemModuleDecl &node) override;
    void visit(ItemStructDecl &node) override;
    void visit(ItemTraitDecl &node) override;

    //Pattern
    void visit(PatternGroup &node) override;
    void visit(PatternIdentifier &node) override;
    void visit(PatternStruct &node) override;
    void visit(PatternLiteral &node) override;
    void visit(PatternPath &node) override;
    void visit(PatternReference &node) override;
    void visit(PatternRest &node) override;
    void visit(PatternSlice &node) override;
    void visit(PatternWildCard &node) override;
    void visit(PatternTuple &node) override;

    //Statement
    void visit(StmtEmpty &node) override;
    void visit(StmtExpr &node) override;
    void visit(StmtItem &node) override;
    void visit(StmtLet &node) override;

    //Type
    void visit(TypeArray &node) override;
    void visit(TypeRawptr &node) override;
    void visit(TypeReference &node) override;
    void visit(TypeSlice &node) override;
    void visit(TypeTuple &node) override;
};
}