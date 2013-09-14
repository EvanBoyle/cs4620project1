
%{
#include "symtab.h"
#include "token.h"
%}

%%

\/\/.*          ;
[[:space:]]     ;

FORWARD         return GO;
SWERVE          return TURN; 
ELEMENT         return VAR;
LEAP            return JUMP;
IF		return IF;
WHILE		return WHILE;
FOR             return FOR;
STEP            return STEP;
TO              return TO;
DO              return DO;
START           return COPEN;
FINISH          return CCLOSE;

sin             return SIN;
cosine          return COS;
sqareroot       return SQRT;

;               return SEMICOLON;
\+              return PLUS;
-               return MINUS;
\*              return TIMES;
\/              return DIV;
\(              return OPEN;
\)              return CLOSE;
=               return ASSIGN;

[a-z]+          { yylval.n = lookup(yytext); 
                  if (yylval.n==NULL)
		    yylval.n = insert(yytext);
                  return ID;
		}
    
[0-9]+\.[0-9]+  yylval.d = atof(yytext);  return FLOAT;
[0-9]+          yylval.i = atoi(yytext);  return NUMBER;


.               fprintf(stderr,"Unexpected character %c (%2X)\n",yytext[0],yytext[0]);

%%
