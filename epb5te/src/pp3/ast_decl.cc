/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "errors.h"
#include <typeinfo>
#include <string.h>
        
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}
  
void VarDecl::PrintChildren(int indentLevel) { 
   type->Print(indentLevel+1);
   id->Print(indentLevel+1);
}

void FnDecl::UndefCheck(){
	
	for(int i = 0; i<formals->NumElements();i++){
		
		Node* parentPtr = this->GetParent();
		bool exists = false;
		while(parentPtr){
			if(parentPtr->GetScope()->GetSymTab()->Lookup(formals->Nth(i)->GetType()->Name())){
				exists = true;
				break;
			}
		parentPtr = parentPtr->GetParent();	
		}
		if(!exists){
			NamedType * nt =  formals->Nth(i)->GetType();
			ReportError::IdentifierNotDeclared(nt->GetId(), 0);
		}
	}
	if(returnType->GetPrintNameForNode()=="NamedType"){
		Node* parentPtr = this->GetParent();
		bool exists = false;
		while(parentPtr){
			if(parentPtr->GetScope()->GetSymTab()->Lookup(returnType->Name())){
				exists = true;
				break;
			}
		parentPtr = parentPtr->GetParent();	
		}
		if(!exists){
			NamedType * nt =  returnType;
			ReportError::IdentifierNotDeclared(nt->GetId(), 0);
		}
	}
	
	if(body){
		printf("calling undef on f body \n");
		((StmtBlock*)body)->UndefCheck();
	}
	
	
}

void VarDecl::UndefCheck(){
	printf(GetType()->Name());
	if(strcmp(GetType()->GetPrintNameForNode(),"NamedType")==0){
		Node* parentPtr = this->GetParent();
		bool exists = false;
		while(parentPtr){
			if(parentPtr->GetScope()->GetSymTab()->Lookup(GetType()->Name())){
				exists = true;
				break;
			}
		parentPtr = parentPtr->GetParent();	
		}
		if(!exists){
			NamedType * nt =  GetType();
			ReportError::IdentifierNotDeclared(nt->GetId(), 0);
		}
	}
	
	if(strcmp(GetType()->GetPrintNameForNode(),"ArrayType")==0){
		Type * t = GetType();
		while(strcmp(t->GetPrintNameForNode(),"ArrayType")==0){
			t = t->GetType();
		}
		if(strcmp(t->GetPrintNameForNode(),"NamedType")==0){
		Node* parentPtr = this->GetParent();
		bool exists = false;
		while(parentPtr){
			if(parentPtr->GetScope()->GetSymTab()->Lookup(t->Name())){
				exists = true;
				break;
			}
		parentPtr = parentPtr->GetParent();	
		}
		if(!exists){
			NamedType * nt =  t;
			ReportError::IdentifierNotDeclared(nt->GetId(), 0);
		}
	}
	}
}

void ClassDecl::UndefCheck(){
	for(int i =0; i< implements->NumElements();i++){
		Node* parentPtr = this->GetParent();
		bool exists = false;
		while(parentPtr){
			if(parentPtr->GetScope()->GetSymTab()->Lookup(implements->Nth(i)->Name())){
				exists = true;
				break;
			}
		parentPtr = parentPtr->GetParent();	
		}
		if(!exists){
			ReportError::IdentifierNotDeclared(implements->Nth(i)->GetId(), 2);
		}
	}
	if(extends){
		Node* parentPtr = this->GetParent();
		bool exists = false;
		while(parentPtr){
			if(parentPtr->GetScope()->GetSymTab()->Lookup(extends->Name())){
				exists = true;
				break;
			}
		parentPtr = parentPtr->GetParent();	
		}
		if(!exists){
			ReportError::IdentifierNotDeclared(extends->GetId(), 1);
		}
	}
	
	
}



ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be g, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}
void ClassDecl::BuildSymTab(){
	this->SetScope(new Scope(this));
	for(int i = 0; i < members->NumElements(); i++){
		bool result = this->GetScope()->Insert(members->Nth(i)->Name(), members->Nth(i));
		members->Nth(i)->BuildSymTab();
		if(!result){
			//report error - duplicate decl
			Decl * prev_decl = (Node*)this->GetScope()->GetSymTab()->Lookup(members->Nth(i)->Name());
			ReportError::DeclConflict(members->Nth(i), prev_decl);
		}
	}
	
}
bool FnDecl::Equals(FnDecl * other){
	if(strcmp(this->Name(),other->Name())!=0|| this->GetFormals()->NumElements()!=other->GetFormals()->NumElements()|| strcmp(this->returnType->Name(), other->returnType->Name())!=0){
		
		
		return false;
	}
	for(int i = 0; i< this->GetFormals()->NumElements(); i++){
		if(!(this->GetFormals()->Nth(i)->Equals(other->GetFormals()->Nth(i)))){
			//printf("breaking there %d\n",i);
			return false;
			
		}
	}
	return true;
}

void ClassDecl::TraverseCheck(){
	//printf("class decl t check\n");
	//if impl or extends check all methods
	if(extends || implements->NumElements()>0){
		//printf("true!!\n");
		for(int i = 0; i < members->NumElements(); i++){
			//if the member is a fn decl
			/*printf(members->Nth(i)->Name());
			printf("\n");
			printf(members->Nth(i)->GetPrintNameForNode());
			printf("\n");*/
			if(members->Nth(i)->GetPrintNameForNode()=="FnDecl"){
				//do stuff
				FnDecl * curFn = ((FnDecl*)members->Nth(i)); 
				Node * parentPtr = this->GetParent();
				
				/*printf("%d \n",implements->NumElements());
				printf(parentPtr->GetPrintNameForNode());
				printf("here\n");*/
				//printf("%s\n", extends->Name());
				bool isNull = parentPtr==NULL;
				
				while(!isNull){
					//printf("past while\n");
					for(int k =0; k< implements->NumElements();k++){
						Node * tmp = parentPtr->GetScope()->GetSymTab()->Lookup(implements->Nth(k)->Name());
						if(tmp){
							
							Node * fnPtr = tmp->GetScope()->GetSymTab()->Lookup(members->Nth(i)->Name());
							if(fnPtr && fnPtr->GetPrintNameForNode()=="FnDecl"){
								//printf("found the implementation checking nodes\n");
								//check the formals
								FnDecl * fdecl = ((FnDecl*)fnPtr);
								if(fdecl->GetFormals()->NumElements()!=curFn->GetFormals()->NumElements()){
									//throw error
									ReportError::OverrideMismatch(curFn);
									
								}
								else{
									for(int j = 0; j< fdecl->GetFormals()->NumElements(); j++){
										if(!fdecl->Equals(curFn)){
											//must change this so equals is imp for FNDecl
											//throw error
											ReportError::OverrideMismatch(curFn);
											
										}
									}
								}
								
							}
						}
							
						
					}
					if(extends!=NULL){
						//printf("it does extend \n");
						Node * tmp = parentPtr->GetScope()->GetSymTab()->Lookup(extends->Name());
						if(tmp){
							printf(" ");
							Node * fnPtr = tmp->GetScope()->GetSymTab()->Lookup(members->Nth(i)->Name());
							if(fnPtr && fnPtr->GetPrintNameForNode()=="FnDecl"){
								//check the formals
								FnDecl * fdecl = ((FnDecl*)fnPtr);
								if(fdecl->GetFormals()->NumElements()!=curFn->GetFormals()->NumElements()){
									//throw error
									ReportError::OverrideMismatch(curFn);
								}
								else{
									for(int j = 0; j< fdecl->GetFormals()->NumElements(); j++){
										if(!fdecl->Equals(curFn)){
											//must change this so equals is imp for FNDecl
											//throw error
											ReportError::OverrideMismatch(curFn);
											//printf("extends error");
											break;
										}
									}
								}
								
							}
						}
						
					}
					
				parentPtr = parentPtr->GetParent();	
				isNull = parentPtr==NULL;
				}
			}
		}
	}
	
	
}

void ClassDecl::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
    if (extends) extends->Print(indentLevel+1, "(extends) ");
    implements->PrintAll(indentLevel+1, "(implements) ");
    members->PrintAll(indentLevel+1);
}


InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::BuildSymTab(){
	this->SetScope(new Scope(this));
	for(int i = 0; i < members->NumElements(); i++){
		bool result = this->GetScope()->Insert(members->Nth(i)->Name(), members->Nth(i));
		members->Nth(i)->BuildSymTab();
		if(!result){
			//report error - duplicate decl
			Decl * prev_decl = (Node*)this->GetScope()->GetSymTab()->Lookup(members->Nth(i)->Name());
			ReportError::DeclConflict(members->Nth(i), prev_decl);
		}
	}
	
}

void InterfaceDecl::PrintChildren(int indentLevel) {
    id->Print(indentLevel+1);
    members->PrintAll(indentLevel+1);
}

bool VarDecl::Equals(VarDecl * oDecl){
	bool nameB = true;
	if(strcmp(this->Name(),oDecl->Name())!=0){
		nameB=false;
	}
	
	bool typeB = true;
	if(strcmp(this->type->Name(),oDecl->type->Name())!=0){
		typeB=false;
	}
	
	return nameB&&typeB;
	
}
	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}


void FnDecl::BuildSymTab(){
	this->SetScope(new Scope(this));
	for(int i = 0; i < formals->NumElements(); i++){
		bool result = this->GetScope()->Insert(formals->Nth(i)->Name(), formals->Nth(i));
		formals->Nth(i)->BuildSymTab();
		if(!result){
			//report error - duplicate decl
			Decl * prev_decl = (Node*)this->GetScope()->GetSymTab()->Lookup(formals->Nth(i)->Name());
			ReportError::DeclConflict(formals->Nth(i), prev_decl);
		}
	}
	
	if(body){
		((StmtBlock*)body)->BuildSymTab();
	}
	
	
	
}






void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

void FnDecl::PrintChildren(int indentLevel) {
    returnType->Print(indentLevel+1, "(return type) ");
    id->Print(indentLevel+1);
    formals->PrintAll(indentLevel+1, "(formals) ");
    if (body) body->Print(indentLevel+1, "(body) ");
}


