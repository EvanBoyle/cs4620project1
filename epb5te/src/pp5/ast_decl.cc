/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "scope.h"
#include "errors.h"
#include <string.h>
        
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this); 
}

bool Decl::ConflictsWithPrevious(Decl *prev) {
    ReportError::DeclConflict(this, prev);
    return true;
}

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

Location* VarDecl::Emit(CodeGenerator* generator){
	Node* dec = GetParent();
	
	Program * prog = dynamic_cast<Program *>(dec);
	if(prog!=NULL){
		generator->seg = gpRelative;
		Location * glob = new Location(generator->seg, generator->OffsetToNextGlobal, GetName());
		generator->OffsetToNextGlobal+=generator->VarSize;
		generator->GlobalVars->Enter(GetName(), glob);
		generator->seg=fpRelative;
	}
	return NULL;
	
}
  
void VarDecl::Check() { type->Check(); }

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
    cType = new NamedType(n);
    cType->SetParent(this);
    convImp = NULL;
}

void ClassDecl::Check() {

    if (extends && !extends->IsClass()) {
        ReportError::IdentifierNotDeclared(extends->GetId(), LookingForClass);
        extends = NULL;
    }
    for (int i = 0; i < implements->NumElements(); i++) {
        NamedType *in = implements->Nth(i);
        if (!in->IsInterface()) {
            ReportError::IdentifierNotDeclared(in->GetId(), LookingForInterface);
            implements->RemoveAt(i--);
        }
    }
    PrepareScope();
    members->CheckAll();
}

Location * ClassDecl::Emit(CodeGenerator* generator){
	generator->Classes->Enter(GetName(), new Hashtable<int>);
	Hashtable<int> *cTable = generator->Classes->Lookup(GetName());
	int byteOffset = 4;
	List<const char *> *vTable = new List<const char *>;
	if(extends != NULL){
		Decl * dec = FindDecl(extends->GetId());
		ClassDecl * cdec = dynamic_cast<ClassDecl*>(dec);
		if(cdec!=NULL){
			for(int i = 0; i<cdec->members->NumElements(); i++){
				VarDecl * vdec = dynamic_cast<VarDecl*>(cdec->members->Nth(i));
				FnDecl * fdec =  dynamic_cast<FnDecl*>(cdec->members->Nth(i));
				if(vdec!=NULL){
					cTable->Enter(vdec->GetName(), byteOffset);
					byteOffset+=4;
					
				}
				if(fdec!=NULL){
					bool add = true;
					for(int j = 0; j < members->NumElements();j++){
						if(strcmp( members->Nth(j)->GetName(), cdec->members->Nth(i)->GetName())==0){
							add = false;
						}
						
					}
					if(add){
						std::string label= cdec->GetName();
						label+="_";
						label += fdec->GetName();
						vTable->Append(strdup(label.c_str()));
						
					}
					
					
				}
			}
			
		}
		
	}
	
	for(int i = 0; i<members->NumElements(); i++){
		members->Nth(i)->Emit(generator);
		VarDecl * vdec = dynamic_cast<VarDecl*>(members->Nth(i));
		FnDecl * fdec =  dynamic_cast<FnDecl*>(members->Nth(i));
		if(vdec!=NULL){
			cTable->Enter(vdec->GetName(), byteOffset);
			byteOffset+=4;
			
		}
		if(fdec!=NULL){
			std::string label= GetName();
			label+="_";
			label += fdec->GetName();
			vTable->Append(strdup(label.c_str()));
		}
	}
	
	cTable->Enter("*size*", byteOffset);
	
	generator->GenVTable(GetName(), vTable);
	return NULL;
	
}




// This is not done very cleanly. I should sit down and sort this out. Right now
// I was using the copy-in strategy from the old compiler, but I think the link to
// parent may be the better way now.
Scope *ClassDecl::PrepareScope()
{
    if (nodeScope) return nodeScope;
    nodeScope = new Scope();  
    if (extends) {
        ClassDecl *ext = dynamic_cast<ClassDecl*>(parent->FindDecl(extends->GetId())); 
        if (ext) nodeScope->CopyFromScope(ext->PrepareScope(), this);
    }
    convImp = new List<InterfaceDecl*>;
    for (int i = 0; i < implements->NumElements(); i++) {
        NamedType *in = implements->Nth(i);
        InterfaceDecl *id = dynamic_cast<InterfaceDecl*>(in->FindDecl(in->GetId()));
        if (id) {
		nodeScope->CopyFromScope(id->PrepareScope(), NULL);
            convImp->Append(id);
	  }
    }
    members->DeclareAll(nodeScope);
    return nodeScope;
}



InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

void InterfaceDecl::Check() {
    PrepareScope();
    members->CheckAll();
}
  
Scope *InterfaceDecl::PrepareScope() {
    if (nodeScope) return nodeScope;
    nodeScope = new Scope();  
    members->DeclareAll(nodeScope);
    return nodeScope;
}
	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

Location* FnDecl::Emit(CodeGenerator * generator){
	//generator->VarLocations = new Hashtable<Location*>;
	//printf("found a function \n");
	
	generator->FnFrameSize = 0;
	std::string label;
	if(strcmp(GetName(),"main")==0){
		label = "main";
	}
	else if(IsMethodDecl()==false){
		//printf("inside the good stuff");
		
		char* prefix = "_";
		label +="_";
		label +=GetName();
		
		int offset = 0;
		for(int i = 0; i< formals->NumElements(); i++){
			offset = (i+1)*4;
			Location* param = new Location(fpRelative, offset, formals->Nth(i)->GetName());
			//printf(formals->Nth(i)->GetId()->GetName());
			generator->VarLocations->Enter(formals->Nth(i)->GetName(), param);
		}
		
	}
	else{
		ClassDecl * parent = dynamic_cast<ClassDecl*>(GetParent());
		if(parent!=NULL){
			label += parent->GetName();
			label += "_";
			label += GetName();
		}
	}
	generator->seg = fpRelative;
	generator->GenLabel(label.c_str());
	BeginFunc *beginning = generator->GenBeginFunc();
	if(body){
		body->Emit(generator);
	
	}
	
	
	beginning->SetFrameSize(generator->FnFrameSize);
	
	generator->GenEndFunc();
	//generator->seg = gpRelative;
	
	return NULL;
	
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

void FnDecl::Check() {
    returnType->Check();
    if (body) {
        nodeScope = new Scope();
        formals->DeclareAll(nodeScope);
        formals->CheckAll();
	body->Check();
    }
}

bool FnDecl::ConflictsWithPrevious(Decl *prev) {
 // special case error for method override
    if (IsMethodDecl() && prev->IsMethodDecl() && parent != prev->GetParent()) { 
        if (!MatchesPrototype(dynamic_cast<FnDecl*>(prev))) {
            ReportError::OverrideMismatch(this);
            return true;
        }
        return false;
    }
    ReportError::DeclConflict(this, prev);
    return true;
}

bool FnDecl::IsMethodDecl() 
  { return dynamic_cast<ClassDecl*>(parent) != NULL || dynamic_cast<InterfaceDecl*>(parent) != NULL; }

bool FnDecl::MatchesPrototype(FnDecl *other) {
    if (!returnType->IsEquivalentTo(other->returnType)) return false;
    if (formals->NumElements() != other->formals->NumElements())
        return false;
    for (int i = 0; i < formals->NumElements(); i++)
        if (!formals->Nth(i)->GetDeclaredType()->IsEquivalentTo(other->formals->Nth(i)->GetDeclaredType()))
            return false;
    return true;
}



