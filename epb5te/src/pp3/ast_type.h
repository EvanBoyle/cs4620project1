/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"


class Type : public Node 
{
  protected:
    char *typeName;

  public :
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
    
    const char *GetPrintNameForNode() { return "Type"; }
    void PrintChildren(int indentLevel);
    virtual char * Name(){return typeName;}
    virtual Type * GetType(){return this;}
    
};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    
  public:
    NamedType(Identifier *i);
    
    const char *GetPrintNameForNode() { return "NamedType"; }
    void PrintChildren(int indentLevel);
    char * Name(){return id->GetName();}
    Identifier * GetId(){return id;}
    
};

class ArrayType : public Type 
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    
    const char *GetPrintNameForNode() { return "ArrayType"; }
    void PrintChildren(int indentLevel);
    Type * GetType() {return elemType;}
};

 
#endif
