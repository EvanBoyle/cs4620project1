/* File: ast.h
 * ----------- 
 * This file defines the abstract base class Node and the concrete 
 * Identifier and Error node subclasses that are used through the tree as 
 * leaf nodes. A parse tree is a hierarchical collection of ast nodes (or, 
 * more correctly, of instances of concrete subclassses such as VarDecl,
 * ForStmt, and AssignExpr).
 * 
 * Location: Each node maintains its lexical location (line and columns in 
 * file), that location can be NULL for those nodes that don't care/use 
 * locations. The location is typcially set by the node constructor.  The 
 * location is used to provide the context when reporting semantic errors.
 *
 * Parent: Each node has a pointer to its parent. For a Program node, the 
 * parent is NULL, for all other nodes it is the pointer to the node one level
 * up in the parse tree.  The parent is not set in the constructor (during a 
 * bottom-up parse we don't know the parent at the time of construction) but 
 * instead we wait until assigning the children into the parent node and then 
 * set up links in both directions. The parent link is typically not used 
 * during parsing, but is more important in later phases.

 */

#ifndef _H_ast
#define _H_ast

#include <stdlib.h>   // for NULL
#include "location.h"
#include "hashtable.h"
#include <string.h>



class Scope;



class Node 
{
  protected:
    yyltype *location;
    Node *parent;
    Scope * scope;
    

  public:
    Node(yyltype loc);
    Node();
    
    
    yyltype *GetLocation()   { return location; }
    void SetParent(Node *p)  { parent = p; }
    Node *GetParent()        { return parent; }
    Scope *GetScope()		{return scope;}
    virtual void TraverseCheck();
    virtual void UndefCheck();
    void SetScope(Scope *s)	{scope = s;}

    virtual const char *GetPrintNameForNode() = 0;
    
    // Print() is deliberately _not_ virtual
    // subclasses should override PrintChildren() instead
    void Print(int indentLevel, const char *label = NULL);
    virtual void BuildSymTab(); 
    virtual void ImplCheck();
    virtual void PrintChildren(int indentLevel)  {}
    virtual void ThisCheck(){};
    virtual char* CheckExpr(){return NULL;};
    virtual void CallCheck(){};
};

class Scope
{
  protected: 
	Hashtable<Node*> *symtab;
	Node *treeNode;
	
  public:
	Scope(Node *ref);
	Node *GetTreeNode() {return treeNode;}
	Hashtable<Node*> *GetSymTab(){return symtab;}
	bool Insert(char * id, Node * treeRef);
		
	
};
   

class Identifier : public Node 
{
  protected:
    char *name;
    
  public:
    Identifier(yyltype loc, const char *name);
    const char *GetPrintNameForNode()   { return "Identifier"; }
    void PrintChildren(int indentLevel);
    char * GetName(){return name;}
};


// This node class is designed to represent a portion of the tree that 
// encountered syntax errors during parsing. The partial completed tree
// is discarded along with the states being popped, and an instance of
// the Error class can stand in as the placeholder in the parse tree
// when your parser can continue after an error.
class Error : public Node
{
  public:
    Error() : Node() {}
    const char *GetPrintNameForNode()   { return "Error"; }
};



#endif
