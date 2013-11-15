/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "errors.h"


Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void FnDecl::ThisCheck(){
	
	if(body){
		body->ThisCheck();
	}
}

void Program::Check() {
	//printf("check \n");
    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */
     this->BuildSymTab();
    // printf("sym tab built \n");
     this->TraverseCheck();
    // printf("class overides checked\n");
     this->UndefCheck();
     //printf("undeclared checked\n");
     this->ImplCheck();
    // printf("implement interface checked \n");
     this->ThisCheck();
     //printf("this checked\n");
     this->CheckExpr();
     //printf("exprs checked \n");
     this->CallCheck();
     //printf("calls checked \n");
}

char* BreakStmt::CheckExpr(){
	Node* parent = GetParent();
	//printf("checking break \n");
	while(parent){
		if(strcmp(parent->GetPrintNameForNode(),"ForStmt")==0||strcmp(parent->GetPrintNameForNode(),"WhileStmt")==0){
			return "";
			
		}
		parent=parent->GetParent();
	}
	ReportError::BreakOutsideLoop(this);
	return "";
}

void Program::ThisCheck(){
	for(int i = 0; i < decls->NumElements(); i++){
		decls->Nth(i)->ThisCheck();
		
	}
}

char* Program::CheckExpr(){
	for(int i = 0; i < decls->NumElements(); i++){
		decls->Nth(i)->CheckExpr();
		
	}
	return NULL;
}


void Program::BuildSymTab(){
	//printf("working \n");
	this->SetScope(new Scope(this));
	for(int i = 0; i < decls->NumElements(); i++){
		bool result = this->GetScope()->Insert(decls->Nth(i)->Name(), decls->Nth(i));
		decls->Nth(i)->BuildSymTab();
		if(!result){
			//printf("error: %s", decls->Nth(i)->Name());
			Decl * prev_decl = (Node*)this->GetScope()->GetSymTab()->Lookup(decls->Nth(i)->Name());
			ReportError::DeclConflict(decls->Nth(i), prev_decl); 
			//report error - duplicate decl
		}
	}
	
}
void ConditionalStmt::ThisCheck(){
	if(body){
		body->ThisCheck();
	}
}

void ConditionalStmt::TraverseCheck(){
	if(body){
		body->TraverseCheck();
	}
}

void Program::CallCheck(){
	for(int i = 0; i < decls->NumElements(); i++){
		decls->Nth(i)->CallCheck();
		
	}
}

void ConditionalStmt::CallCheck(){
	if(body){
		body->CallCheck();
	}
}

void IfStmt::CallCheck(){
	if(body){
		body->CallCheck();
	}
	if(body){
		test->CallCheck();
	}
	if(elseBody){
		elseBody->CallCheck();
	}
}
void StmtBlock::CallCheck(){
	for(int i = 0; i < decls->NumElements(); i++){
		
		decls->Nth(i)->CallCheck();
		
	}
	for(int i = 0; i < stmts->NumElements(); i++){
		
		stmts->Nth(i)->CallCheck();
		
	}
}




char* ConditionalStmt::CheckExpr(){
	if(body){
		body->CheckExpr();
	}
	if(test){
		if(strcmp(test->CheckExpr(),"bool")!=0){
			ReportError::TestNotBoolean(test);
		}
	}
	return "";
}

char* IfStmt::CheckExpr(){
	if(body){
		body->CheckExpr();
	}
	if(test){
		if(strcmp(test->CheckExpr(),"bool")!=0){
			ReportError::TestNotBoolean(test);
		}
	}
	if(elseBody){
		elseBody->CheckExpr();
	}
	return "";
}

char* ReturnStmt::CheckExpr(){
	//ReportError::ReturnMismatch(ReturnStmt *rStmt, Type *given, Type *expected)
	char * type = "";
	if(expr){
		type = expr->CheckExpr();
	}
	Node* parentPtr = GetParent();
	while(parentPtr){
		if(strcmp(parentPtr->GetPrintNameForNode(),"FnDecl")==0){
			FnDecl * fdecl = parentPtr;
			char* rt = fdecl->GetRT()->Name();
			if(strcmp(rt,type)!=0){
				ReportError::ReturnMismatch(this, type, rt);
				return "UNDEFINED";
			}
		}
		parentPtr= parentPtr->GetParent();	
	}
	return type;
	
}

void IfStmt::ThisCheck(){
	if(body){
		body->ThisCheck();
	}
	if(test){
		test->ThisCheck();
	}
	if(elseBody){
		elseBody->ThisCheck();
	}
	return "";
}

void IfStmt::UndefCheck(){
	if(body){
		body->UndefCheck();
	}
	if(test){
		test->UndefCheck();
	}
	if(elseBody){
		elseBody->UndefCheck();
	}
	return "";
}

void IfStmt::TraverseCheck(){
	if(body){
		body->TraverseCheck();
	}
	if(test){
		test->TraverseCheck();
	}
	if(elseBody){
		elseBody->TraverseCheck();
	}
	return "";
}


void IfStmt::BuildSymTab(){
	if(body){
		body->BuildSymTab();
	}
	
	if(elseBody){
		elseBody->BuildSymTab();
	}
	return "";
}



void Program::UndefCheck(){
	for(int i = 0; i < decls->NumElements(); i++){
		decls->Nth(i)->UndefCheck();
		
	}
	
}

void ConditionalStmt::BuildSymTab(){
	if(body){
		body->BuildSymTab();
	}
}

void Program::ImplCheck(){
	for(int i = 0; i < decls->NumElements(); i++){
		decls->Nth(i)->ImplCheck();
		
	}
}


void Program::TraverseCheck(){
	for(int i = 0; i < decls->NumElements(); i++){
		decls->Nth(i)->TraverseCheck();
		
	}
	
}

void Program::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    printf("\n");
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}
void StmtBlock::UndefCheck(){
	
	for(int i = 0; i < decls->NumElements(); i++){
		
		decls->Nth(i)->UndefCheck();
		
	}
	for(int i = 0; i < stmts->NumElements(); i++){
		
		stmts->Nth(i)->UndefCheck();
		
	}
	
}

char* StmtBlock::CheckExpr(){
	
	for(int i = 0; i < decls->NumElements(); i++){
		
		decls->Nth(i)->CheckExpr();
		
	}
	for(int i = 0; i < stmts->NumElements(); i++){
		
		stmts->Nth(i)->CheckExpr();
		
	}
	return NULL;
	
}

void StmtBlock::ThisCheck(){
	
	for(int i = 0; i < decls->NumElements(); i++){
		
		decls->Nth(i)->ThisCheck();
		
	}
	for(int i = 0; i < stmts->NumElements(); i++){
		
		stmts->Nth(i)->ThisCheck();
		
	}
}
void WhileStmt::UndefCheck(){
	if(body){
		(body)->UndefCheck();
	}
}
void ConditionalStmt::UndefCheck(){
	if(body){
		(body)->UndefCheck();
	}
}
void LoopStmt::UndefCheck(){
	if(body){
		
		(body)->UndefCheck();
	}
}

void StmtBlock::TraverseCheck(){
	for(int i = 0; i < decls->NumElements(); i++){
		decls->Nth(i)->TraverseCheck();
		
	}
	
}

void StmtBlock::BuildSymTab(){
	//printf("in stmt block \n");
	this->SetScope(new Scope(this));
	for(int i = 0; i < decls->NumElements(); i++){
		bool result = this->GetScope()->Insert(decls->Nth(i)->Name(), decls->Nth(i));
		decls->Nth(i)->BuildSymTab();
		if(!result){
			//printf("error: %s", decls->Nth(i)->Name());
			Decl * prev_decl = (Node*)this->GetScope()->GetSymTab()->Lookup(decls->Nth(i)->Name());
			ReportError::DeclConflict(decls->Nth(i), prev_decl);
			//report error - duplicate decl
		}
	}
	
	for(int i = 0; i < stmts->NumElements(); i++){
		/*if(strcmp(stmts->Nth(i)->GetPrintNameForNode(),"StmtBlock")==0){
			(stmts->Nth(i))->BuildSymTab();
		  }*/
		(stmts->Nth(i))->BuildSymTab();
		
	}
	
}

void StmtBlock::PrintChildren(int indentLevel) {
    decls->PrintAll(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

void ForStmt::PrintChildren(int indentLevel) {
    init->Print(indentLevel+1, "(init) ");
    test->Print(indentLevel+1, "(test) ");
    step->Print(indentLevel+1, "(step) ");
    body->Print(indentLevel+1, "(body) ");
}

void WhileStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(body) ");
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

void IfStmt::PrintChildren(int indentLevel) {
    test->Print(indentLevel+1, "(test) ");
    body->Print(indentLevel+1, "(then) ");
    if (elseBody) elseBody->Print(indentLevel+1, "(else) ");
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}

void ReturnStmt::PrintChildren(int indentLevel) {
    expr->Print(indentLevel+1);
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

void PrintStmt::PrintChildren(int indentLevel) {
    args->PrintAll(indentLevel+1, "(args) ");
}

Case::Case(IntConstant *v, List<Stmt*> *s) {
    Assert(s != NULL);
    value = v;
    if (value) value->SetParent(this);
    (stmts=s)->SetParentAll(this);
}

void Case::PrintChildren(int indentLevel) {
    if (value) value->Print(indentLevel+1);
    stmts->PrintAll(indentLevel+1);
}

SwitchStmt::SwitchStmt(Expr *e, List<Case*> *c) {
    Assert(e != NULL && c != NULL);
    (expr=e)->SetParent(this);
    (cases=c)->SetParentAll(this);
}
      
void SwitchStmt::PrintChildren(int indentLevel) {
    expr->Print(indentLevel+1);
    cases->PrintAll(indentLevel+1);
}


