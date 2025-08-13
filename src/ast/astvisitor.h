# pragma once

namespace JaneZ {
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


class ASTNode;

class ASTVisitor{
public:
    ASTVisitor() = default;
    virtual ~ASTVisitor() = 0;

    virtual void visit(ASTNode &node) = 0;
    
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

};
}