
%{
#include <stdio.h>
#include "symtab.h"
%}

%union { int i; node *n; double d;}

%token GO TURN ELEMENT JUMP
%token WHILE
%token IF ELSE LESS GREAT LESSE GREATE EQUALS NOTEQUALS OCBRACE CCBRACE
%token FOR STEP TO DO
%token COPEN CCLOSE
%token SIN COS SQRT
%token <d> FLOAT
%token <n> ID               
%token <i> NUMBER       
%token SEMICOLON PLUS MINUS TIMES DIV OPEN CLOSE ASSIGN

%type <n> decl
%type <n> decllist

%%
program: head decllist stmtlist tail;

head: { printf("%%!PS Adobe\n"
               "\n"
	       "newpath 0 0 moveto\n"
	       );
      };

tail: { printf("stroke\n"); };

decllist: ;
decllist: decllist decl;

decl: ELEMENT ID SEMICOLON { printf("/tlt%s 0 def\n",$2->symbol);} ;


stmtlist: ;
stmtlist: stmtlist stmt ;

stmt: ID ASSIGN expr SEMICOLON {printf("/tlt%s exch store\n",$1->symbol);} ;
stmt: GO expr SEMICOLON {printf("0 rlineto\n");};
stmt: JUMP expr SEMICOLON {printf("0 rmoveto\n");};
stmt: TURN expr SEMICOLON {printf("rotate\n");};

stmt: FOR ID ASSIGN expr 
          STEP expr
	  TO expr
	  DO {printf("{ /tlt%s exch store\n",$2->symbol);} 
	     stmt {printf("} for\n");};

boolexpr: expr EQUALS expr {printf("eq");};
boolexpr: expr NOTEQUALS expr {printf("ne");};
boolexpr: expr LESS expr {printf("lt");};
boolexpr: expr LESSE expr {printf("le");};
boolexpr: expr GREATE expr {printf("ge");};
boolexpr: expr GREAT expr {printf("gt");};
boolexpr: expr EQUALS expr {printf("eq");};


stmnt: WHILE {printf("{");}OPEN boolexpr CLOSE  {printf("{} {exit} ifelse");}OCBRACE stmtlist CCBRACE 	{printf("}loop \n ");};

stmnt: IF OPEN boolexpr {printf("{");}CLOSE OCBRACE stmtlist CCBRACE {printf("}if");} ELSE {printf("{");}OCBRACE stmtlist {printf("}elseif");}CCBRACE;

stmnt: IF OPEN boolexpr {printf("{");}CLOSE OCBRACE stmtlist {printf("}if");}CCBRACE;

stmnt: COPEN stmtlist CCLOSE;	 

expr: expr PLUS term { printf("add ");};
expr: expr MINUS term { printf("sub ");};
expr: term;

term: term TIMES factor { printf("mul ");};
term: term DIV factor { printf("div ");};
term: factor;

factor: MINUS atomic { printf("neg ");};
factor: PLUS atomic;
factor: SIN factor { printf("sin ");};
factor: COS factor { printf("cos ");};
factor: SQRT factor { printf("sqrt ");};
factor: atomic;



atomic: OPEN expr CLOSE;
atomic: NUMBER {printf("%d ",$1);};
atomic: FLOAT {printf("%f ",$1);};
atomic: ID {printf("tlt%s ", $1->symbol);};


%%
int yyerror(char *msg)
{  fprintf(stderr,"Error: %s\n",msg);
   return 0;
}

int main(void)
{   yyparse();
    return 0;
}

