/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>
#include "errors.h"



void CompoundExpr::ThisCheck(){
	//printf(GetPrintNameForNode());
	if(left){
		left->ThisCheck();
	}
	if(right){
		right->ThisCheck();
	}
}

void This::ThisCheck(){
	//printf("this checking\n");
	Node * parentPtr = GetParent();
	bool valid = false;
	while(parentPtr!=NULL){
		if(strcmp(parentPtr->GetPrintNameForNode(),"ClassDecl")==0){
			valid = true;
			break;
		}
		parentPtr=parentPtr->GetParent();
		
	}
	if(!valid){
		ReportError::ThisOutsideClassScope(this);
	}
}


char* Call::CheckExpr(){
	//printf("checking field acc\n");
	Node* parentPtr = GetParent();
	while(parentPtr){
		FnDecl * decl=NULL;
		if(parentPtr->GetScope()){
			decl = parentPtr->GetScope()->GetSymTab()->Lookup(field->GetName());
		}
		
		if(decl){
			if(strcmp(decl->GetPrintNameForNode(),"FnDecl")==0){
				return decl->GetRT()->Name();
			}
		}
		
		parentPtr=parentPtr->GetParent();
	}
	return "UNDEFINED";
}


char* FieldAccess::CheckExpr(){
	//printf("checking field acc\n");
	Node* parentPtr = GetParent();
	while(parentPtr){
		VarDecl * decl=NULL;
		if(parentPtr->GetScope()){
			decl = parentPtr->GetScope()->GetSymTab()->Lookup(field->GetName());
		}
		
		if(decl){
			if(strcmp(decl->GetPrintNameForNode(),"VarDecl")==0){
				return decl->GetType()->Name();
			}
		}
		
		parentPtr=parentPtr->GetParent();
	}
	return "UNDEFINED";
}

char* CompoundExpr::CheckExpr(){
	
	if(left){
		//left->CheckExpr();
		printf(left->GetPrintNameForNode());
		//printf("\n");
	}
	if(right){
		//right->CheckExpr();
		printf(right->GetPrintNameForNode());
		//printf("\n");
	}
	return "UNDEFINED";
}

char* ArithmeticExpr::CheckExpr(){
	//printf("checking\n");
	if(left && right){
		char * ltype = left->CheckExpr();
		char * rtype = right->CheckExpr();
		if(!strcmp(ltype, rtype)==0){
			ReportError::IncompatibleOperands(GetOperator(), ltype, rtype); 
			return "UNDEFINED";
		}
		if(strcmp(ltype, "int")==0  || strcmp(ltype, "double")){
			return ltype;
		}
		
	}
	else{
		char * rtype = right->CheckExpr();
		if(strcmp(rtype, "int")==0  || strcmp(rtype, "double")){
			return rtype;
		}
		else{
			ReportError::IncompatibleOperand(GetOperator(), rtype); 
		}
	}
	return "UNDEFINED";
}

char* RelationalExpr::CheckExpr(){
	if(left && right){
		char * ltype = left->CheckExpr();
		char * rtype = right->CheckExpr();
		if(!strcmp(ltype, rtype)==0){
			ReportError::IncompatibleOperands(GetOperator(), ltype, rtype); 
			return "UNDEFINED";
		}
		if(strcmp(ltype, "int")==0||strcmp(ltype, "double")==0){
			return "bool";
		}
		
	}
	return "UNDEFINED";
	
}

char* AssignExpr::CheckExpr(){
	if(left && right){
		char * ltype = left->CheckExpr();
		char * rtype = right->CheckExpr();
		if(!strcmp(ltype, rtype)==0){
			ReportError::IncompatibleOperands(GetOperator(), ltype, rtype); 
			return "UNDEFINED";
		}
		return ltype;
		
		
	}
	return "UNDEFINED";

	
}

char* EqualityExpr::CheckExpr(){
	//anything just same
	if(left && right){
	
		char * ltype = left->CheckExpr();
		char * rtype = right->CheckExpr();
		if(!strcmp(ltype, rtype)==0){
			ReportError::IncompatibleOperands(GetOperator(), ltype, rtype); 
			return "UNDEFINED";
		}
		return ltype;
	}
	
	return "UNDEFINED";
}

char* LogicalExpr::CheckExpr(){
	printf("logical \n");
	if(left && right){
		char * ltype = left->CheckExpr();
		char * rtype = right->CheckExpr();
		if(!strcmp(ltype, rtype)==0){
			ReportError::IncompatibleOperands(GetOperator(), ltype, rtype); 
			return "UNDEFINED";
		}
		if(strcmp(ltype, "bool")==0 ){
			return ltype;
		}
			ReportError::IncompatibleOperands(GetOperator(), ltype, rtype); 
			return "UNDEFINED";
		
	}
	else{
		char * rtype = right->CheckExpr();
		printf("checking right expr \n");
		if(strcmp("bool", rtype)==0){
			return "bool";
		}
		else{
			ReportError::IncompatibleOperand(GetOperator(), rtype); 
		}
	}
	return "UNDEFINED";
}

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}
void IntConstant::PrintChildren(int indentLevel) { 
    printf("%d", value);
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}
void DoubleConstant::PrintChildren(int indentLevel) { 
    printf("%g", value);
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}
void BoolConstant::PrintChildren(int indentLevel) { 
    printf("%s", value ? "true" : "false");
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}
void StringConstant::PrintChildren(int indentLevel) { 
    printf("%s",value);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    
    
    strncpy(tokenString, tok, sizeof(tokenString));
}

void Operator::PrintChildren(int indentLevel) {
    printf("%s",tokenString);
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

void CompoundExpr::PrintChildren(int indentLevel) {
   if (left) left->Print(indentLevel+1);
   op->Print(indentLevel+1);
   right->Print(indentLevel+1);
}
   
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}

void ArrayAccess::PrintChildren(int indentLevel) {
    base->Print(indentLevel+1);
    subscript->Print(indentLevel+1, "(subscript) ");
  }
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


  void FieldAccess::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
  }

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

 void Call::PrintChildren(int indentLevel) {
    if (base) base->Print(indentLevel+1);
    field->Print(indentLevel+1);
    actuals->PrintAll(indentLevel+1, "(actuals) ");
  }
 

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

void NewExpr::PrintChildren(int indentLevel) {	
    cType->Print(indentLevel+1);
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

void NewArrayExpr::PrintChildren(int indentLevel) {
    size->Print(indentLevel+1);
    elemType->Print(indentLevel+1);
}

PostfixExpr::PostfixExpr(LValue *lv, Operator *o) : Expr(Join(lv->GetLocation(), o->GetLocation())) {
    Assert(lv != NULL && o != NULL);
    (lvalue=lv)->SetParent(this);
    (op=o)->SetParent(this);
}

void PostfixExpr::PrintChildren(int indentLevel) {
    lvalue->Print(indentLevel+1);
    op->Print(indentLevel+1);
}
       
