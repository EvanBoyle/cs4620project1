/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>

Location * IntConstant::Emit(CodeGenerator* generator){
	Location * loc = generator->GenLoadConstant(value);
	return loc;
	
}

Location* ReadLineExpr::Emit(CodeGenerator* generator){
	
	return generator->GenBuiltInCall(ReadLine);
	
	
}

Location* ArithmeticExpr::Emit(CodeGenerator * generator){
	Location * lloc;
	char * aop;
	if(strcmp(op->str(), "+")==0){
		aop = "+";
	}
	if(strcmp(op->str(), "-")==0){
		aop = "-";
	}
	if(strcmp(op->str(), "*")==0){
		aop = "*";
	}
	if(strcmp(op->str(), "/")==0){
		aop = "/";
	}
	if(strcmp(op->str(), "%")==0){
		aop = "%";
	}
	if(left!=NULL){
		lloc = left->Emit(generator);
	}
	Location * rloc = right->Emit(generator);
	if(left!=NULL){
		return generator->GenBinaryOp(aop, lloc, rloc);
		
			
		
	}
	else{
		Location *lloc=generator->GenLoadConstant(-1);
		return generator->GenBinaryOp("*", lloc, rloc);
		
	}
	return NULL;
	//generator->GenBinaryOp("+",  
	
}

Location* LogicalExpr::Emit(CodeGenerator * generator){
	Location * lloc;
	char * aop;
	if(strcmp(op->str(), "&&")==0){
		aop = "&&";
	}
	if(strcmp(op->str(), "||")==0){
		aop = "||";
	}
	if(strcmp(op->str(), "!")==0){
		aop = "!";
	}

	if(left!=NULL){
		lloc = left->Emit(generator);
	}
	Location * rloc = right->Emit(generator);
	if(left!=NULL){
		return generator->GenBinaryOp(aop, lloc, rloc);
		
			
		
	}
	else{
		Location *lloc=generator->GenLoadConstant(-1);
		Location * tmploc=generator->GenBinaryOp("*", lloc, rloc);
		Location *consloc=generator->GenLoadConstant(1);
		return generator->GenBinaryOp("+", tmploc, consloc);
		
	}
	return NULL;
	//generator->GenBinaryOp("+",  
	
}

Location* EqualityExpr::Emit(CodeGenerator * generator){
	Location * lloc=left->Emit(generator);
	Location * rloc = right->Emit(generator);
	char * aop;
	if(strcmp(op->str(), "==")==0){
		aop = "==";
		return generator->GenBinaryOp(aop, lloc, rloc);
	}
	if(strcmp(op->str(), "!=")==0){
		aop = "!=";
		Location* tmploc1 = generator->GenBinaryOp("==", lloc, rloc);
		Location *consloc1=generator->GenLoadConstant(-1);
		Location* tmploc2= generator->GenBinaryOp("*", tmploc1, consloc1);
		Location *consloc2=generator->GenLoadConstant(1);
		return generator->GenBinaryOp("+", tmploc2, consloc2);
		
	} 
	
}

Location* RelationalExpr::Emit(CodeGenerator * generator){
	Location * lloc=left->Emit(generator);
	Location * rloc = right->Emit(generator);
	char * aop;
	if(strcmp(op->str(), "<")==0){
		aop = "<";
		return generator->GenBinaryOp(aop, lloc, rloc);
	}
	if(strcmp(op->str(), ">")==0){
		aop = "<";
		return generator->GenBinaryOp(aop, rloc, lloc);
	}
	if(strcmp(op->str(), "<=")==0){
		aop = "<";
		Location * less= generator->GenBinaryOp(aop, lloc, rloc);
		Location *equal = generator->GenBinaryOp("==", rloc, lloc);
		return generator->GenBinaryOp("||", less, equal);
	}
	if(strcmp(op->str(), ">=")==0){
		aop = "<";
		Location *less = generator->GenBinaryOp(aop, rloc, lloc);
		Location *equal = generator->GenBinaryOp("==", rloc, lloc);
		return generator->GenBinaryOp("||", less, equal);
	}
	
	return NULL;
	
	
	
	
}

Location * Call::Emit(CodeGenerator* generator){
	
	Decl * dec = FindDecl(field);
	FnDecl * fdec = dynamic_cast<FnDecl*>(dec);
	if(fdec!=NULL){
		if(fdec->IsMethodDecl()==false){
			int paramBytes = 0;
			
			for(int i = 0; i< actuals->NumElements(); i++){
				generator->GenPushParam(actuals->Nth(i)->Emit(generator));
				paramBytes+=4;
			}
			std::string label = "_";
			label +=fdec->GetName();
			bool hasReturn = strcmp(fdec->returnType->typeName, "void")==0;
			
			Location * ret = generator->GenLCall(label.c_str(), !hasReturn);
			generator->GenPopParams(paramBytes);
			return ret;
		}
		else{
			//is a class call and we must figure out what to do
			
		}
	}
	return NULL;
	
}

Location* ReadIntegerExpr::Emit(CodeGenerator* generator){
	
	return generator->GenBuiltInCall(ReadInteger);
	
}



Location* BoolConstant::Emit(CodeGenerator * generator){
	Location * loc = generator->GenLoadConstant(value);
	return loc;
}

Location* FieldAccess::Emit(CodeGenerator* generator){
	Location * loc;
	if(base == NULL){
		if(generator->VarLocations->Lookup(field->GetName())==NULL){
			loc =new Location(fpRelative, generator->OffsetToNextLocal, field->GetName());
			generator->VarLocations->Enter(field->GetName(), loc);
			generator->OffsetToNextLocal -=4;
			generator->FnFrameSize+=4;
			return loc;
		}
		else{
			return generator->VarLocations->Lookup(field->GetName());
		}
		
	}
	return NULL;
	
}

Location* AssignExpr::Emit(CodeGenerator * generator){
	Location * lloc = left->Emit(generator);
	Location * rloc = right->Emit(generator);
	generator->GenAssign(lloc, rloc);
	return rloc;
	
}



IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
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
   
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}
 

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

       
