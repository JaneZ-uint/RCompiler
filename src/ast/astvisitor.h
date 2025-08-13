# pragma once

namespace JaneZ {
class ExprArray;
class ExprBlock;
class ExprBreak;
class ExprCall;
class ExprContinue;
class ExprField;
class ExprGroup;
class ExprIf;
class ExprIndex;
class ExprLiteral;
class ExprLoop;
class ExprMatch;
class ExprMethodcall;
class ExprOpbinary;
class ExprOpunary;
class ExprPath;
class ExprReturn;
class ExprTuple;
class ExprUnderscore;
class ExprWhile;

class ItemConstDecl;
class ItemEnumDecl;
class ItemFnDecl;
class ItemImplDecl;
class ItemModuleDecl;
class ItemStructDecl;
class ItemTraitDecl;

class PatternStruct;
class PatternGroup;
class PatternIdentifier;
class PatternLiteral;
class PatternPath;
class PatternReference;
class PatternRest;
class PatternSlice;
class PatternTuple;
class PatternWildCard;

class StmtEmpty;
class StmtExpr;
class StmtItem;
class StmtLet;

class TypeArray;
class TypeRawptr;
class TypeReference;
class TypeSlice;
class TypeTuple;

class ASTNode;

class ASTVisitor{
public:
    ASTVisitor() = default;
    virtual ~ASTVisitor() = 0;

    virtual void visit(ASTNode &node) = 0;

    //Expression
    virtual void visit(ExprArray &node) = 0;
    virtual void visit(ExprBlock &node) = 0;
    virtual void visit(ExprBreak &node) = 0;
    virtual void visit(ExprCall &node) = 0;
    virtual void visit(ExprContinue &node) = 0;
    virtual void visit(ExprField &node) = 0;
    virtual void visit(ExprGroup &node) = 0;
    virtual void visit(ExprIf &node) = 0;
    virtual void visit(ExprIndex &node) = 0;
    virtual void visit(ExprLiteral &node) = 0;
    virtual void visit(ExprLoop &node) = 0;
    virtual void visit(ExprMatch &node) = 0;
    virtual void visit(ExprMethodcall &node) = 0;
    virtual void visit(ExprOpbinary &node) = 0;
    virtual void visit(ExprOpunary &node) = 0;
    virtual void visit(ExprPath &node) = 0;
    virtual void visit(ExprReturn &node) = 0;
    virtual void visit(ExprTuple &node) = 0;
    virtual void visit(ExprUnderscore &node) = 0;
    virtual void visit(ExprWhile &node) = 0;
    
    //Item 
    virtual void visit(ItemConstDecl &node) = 0;
    virtual void visit(ItemEnumDecl &node) = 0;
    virtual void visit(ItemFnDecl &node) = 0;
    virtual void visit(ItemImplDecl &node) = 0;
    virtual void visit(ItemModuleDecl &node) = 0;
    virtual void visit(ItemStructDecl &node) = 0;
    virtual void visit(ItemTraitDecl &node) = 0;

    //Pattern
    virtual void visit(PatternGroup &node) = 0;
    virtual void visit(PatternIdentifier &node) = 0;
    virtual void visit(PatternStruct &node) = 0;
    virtual void visit(PatternLiteral &node) = 0;
    virtual void visit(PatternPath &node) = 0;
    virtual void visit(PatternReference &node) = 0;
    virtual void visit(PatternRest &node) = 0;
    virtual void visit(PatternSlice &node) = 0;
    virtual void visit(PatternWildCard &node) = 0;
    virtual void visit(PatternTuple &node) = 0;

    //Statement
    virtual void visit(StmtEmpty &node) = 0;
    virtual void visit(StmtExpr &node) = 0;
    virtual void visit(StmtItem &node) = 0;
    virtual void visit(StmtLet &node) = 0;

    //Type
    virtual void visit(TypeArray &node) = 0;
    virtual void visit(TypeRawptr &node) = 0;
    virtual void visit(TypeReference &node) = 0;
    virtual void visit(TypeSlice &node) = 0;
    virtual void visit(TypeTuple &node) = 0;
};
}