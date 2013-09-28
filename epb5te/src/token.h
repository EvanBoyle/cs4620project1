
/* Tokens.  */
#define GO 258
#define TURN 259
#define VAR 260
#define JUMP 261
#define FOR 262
#define STEP 263
#define TO 264
#define DO 265
#define COPEN 266
#define CCLOSE 267
#define SIN 268
#define COS 269
#define SQRT 270
#define FLOAT 271
#define ID 272
#define NUMBER 273
#define SEMICOLON 274
#define PLUS 275
#define MINUS 276
#define TIMES 277
#define DIV 278
#define OPEN 279
#define CLOSE 280
#define ASSIGN 281
#define IF 282
#define ELSE 283
#define EQUALS 284
#define NOTEQUALS 285
#define GREAT 286
#define GREATE 287
#define LESS 288
#define LESSE 289
#define OCBRACE 290
#define CCBRACE 291
#define	WHILE 292




typedef union YYSTYPE
{ int i; node *n; double d;}
        YYSTYPE;
extern YYSTYPE yylval;

