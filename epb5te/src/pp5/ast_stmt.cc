/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "scope.h"
#include "errors.h"





Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();
}

Location * ReturnStmt::Emit(CodeGenerator* generator){
	if(expr!=NULL){
		Location * returnLoc = expr->Emit(generator);
		generator->GenReturn(returnLoc);
		
	}
	else{
		//generator->GenReturn();
	}
	return NULL;
	
	
}

Location *  Program::Emit(CodeGenerator * generator){
	//printf("at the program \n");
	if(nodeScope->LookupName("main")==NULL){
		ReportError::NoMainFound();
		return NULL;
	}
	
	CodeGenerator * gen = new CodeGenerator;
	for(int i=0; i<decls->NumElements(); i++){
		//printf("checking decl");
		decls->Nth(i)->Emit(gen);
	}
	
	gen->DoFinalCodeGen();
	return NULL;
	
	
}

Location* IfStmt::Emit(CodeGenerator* generator){
	if(elseBody!=NULL){
		char * l0 = generator->NewLabel();
		char * l1 = generator->NewLabel();
		Location * testLoc = test->Emit(generator);
		generator->GenIfZ(testLoc, l0);
		body->Emit(generator);
		generator->GenGoto(l1);
		generator->GenLabel(l0);
		elseBody->Emit(generator);
		generator->GenLabel(l1);
		
	}
	else{
		char * l0 = generator->NewLabel();
		Location * testLoc = test->Emit(generator);
		generator->GenIfZ(testLoc, l0);
		body->Emit(generator);
		generator->GenLabel(l0);
	}
	return NULL;
	
}

Location* WhileStmt::Emit(CodeGenerator* generator){
	//save old label, create start and break labels, set break label
	char * previousBreak = generator->BreakLabel;
	char* startLabel = generator->NewLabel();
	char* newBreak = generator->NewLabel();
	generator->BreakLabel = newBreak;
	//emit start label
	generator->GenLabel(startLabel);
	Location * testLoc = test->Emit(generator);
	generator->GenIfZ(testLoc, newBreak);
	body->Emit(generator);
	generator->GenGoto(startLabel);
	generator->GenLabel(newBreak);
	
	
	//restore previous break label
	generator->BreakLabel= previousBreak;
	
	return NULL;
	
	
}

Location* ForStmt::Emit(CodeGenerator* generator){
	//save old label, create start and break labels, set break label
	char * previousBreak = generator->BreakLabel;
	char* startLabel = generator->NewLabel();
	char* newBreak = generator->NewLabel();
	generator->BreakLabel = newBreak;
	//emit start label
	init->Emit(generator);
	generator->GenLabel(startLabel);
	Location * testLoc = test->Emit(generator);
	generator->GenIfZ(testLoc, newBreak);
	body->Emit(generator);
	step->Emit(generator);
	generator->GenGoto(startLabel);
	generator->GenLabel(newBreak);
	
	
	//restore previous break label
	generator->BreakLabel= previousBreak;
	
	return NULL;
	
	
}

Location* BreakStmt::Emit(CodeGenerator* generator){
	generator->GenGoto(generator->BreakLabel);
	return NULL;
	
}


StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}
void StmtBlock::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();
    stmts->CheckAll();
}

Location * StmtBlock::Emit(CodeGenerator* generator){
	if(decls){
		for(int i = 0; i<decls->NumElements(); i++){
			decls->Nth(i)->Emit(generator);
		}
	}
	if(stmts){
		for(int i = 0; i<stmts->NumElements(); i++){
			stmts->Nth(i)->Emit(generator);
		}
	}
	
	return NULL;
	
	
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

void ConditionalStmt::Check() {
    body->Check();
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}
void IfStmt::Check() {
    ConditionalStmt::Check();
    if (elseBody) elseBody->Check();
}


ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}

Location* PrintStmt::Emit(CodeGenerator * generator){
	for(int i =0; i< args->NumElements();i++){
		Location* loc = args->Nth(i)->Emit(generator);
		FieldAccess * fa = dynamic_cast<FieldAccess*>(args->Nth(i));
		IntConstant * ic = dynamic_cast<IntConstant*>(args->Nth(i));
		BoolConstant * bc = dynamic_cast<BoolConstant*>(args->Nth(i));
		
		if(bc){
			generator->GenBuiltInCall(PrintBool, loc);
		}
		
		else if(ic){
			generator->GenBuiltInCall(PrintInt, loc);
		}
		
		else if(fa){
			Decl * dec = fa->FindDecl(fa->field);
			VarDecl * vdec = dynamic_cast<VarDecl *>(dec);
			if(vdec){
				Type * t = vdec->GetDeclaredType();
				if(strcmp(t->typeName,"int")==0){
					generator->GenBuiltInCall(PrintInt, loc);
				}
				if(strcmp(t->typeName,"bool")==0){
					generator->GenBuiltInCall(PrintBool, loc);
				}
			}
		}
		
		else{
			generator->GenBuiltInCall(PrintInt, loc);
		}
		
		/*FindDecl(args->Nth()->
		Type t = args->Nth(i)->GetType();
		if(t == Type::intType){
			generator->GenBuiltInCall(PrintInt, loc);
		}
		if(t == Type::boolType){
			generator->GenBuiltInCall(PrintBool, loc);
		}*/
		//generator->GenBuiltInCall(PrintInt, loc);
		
	}
	return NULL;
}


