%{
#include "byteassembler.h"
#include "memorymanager.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

extern int line_num;
void yyerror(char const*);
int yylex(void);

void yyerror (char const *msg) {
	fprintf(stderr, "%s at line %d\n", msg, line_num);
	exit(0);
}
%}

%union {
	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;
}

%token <integer> INTEGER
%token <real>    REAL
%token <string>  STRING IDENTIFIER

%token NEWLINE
%token REM
%token DIM SDIM LET STOP ENDIF ENDDO ELSE COMMA DO WHILE
%token FOR TO FROM NEXT INTO GOTO PRINT INPUT
%token IF THEN COREID NUMCORES SEND RECV RANDOM SYNC BCAST REDUCE SUM MIN MAX PROD SENDRECV TOFROM

%token ADD SUB
%token MULT DIV MOD AND OR NEQ LEQ GEQ LT GT EQ NOT SQRT SIN COS TAN ASIN ACOS ATAN SINH COSH TANH FLOOR CEIL LOG LOG10
%token LPAREN RPAREN SLBRACE SRBRACE

%left ADD SUB
%left MULT DIV MOD
%left AND OR
%left NEQ LEQ GEQ LT GT EQ
%right NOT
%right POW

%type <string> ident declareident
%type <integer> unary_operator reductionop
%type <data> constant expression logical_or_expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression value statement statements line lines

%start program 

%%

program : lines { compileMemory($1); }

lines
        : line
        | lines line { $$=appendMemory($1, $2); }
;

line
        : statements NEWLINE { $$ = $1; }
        | INTEGER statements NEWLINE { $$ = $2; setLineNumber($$, $1); }
	    | NEWLINE { $$ = NULL; }
;

statements
	: statement ':' statements
	| statement
;

statement	
	: RECV ident FROM expression { $$=appendRecvStatement($2, $4); }
	| RECV ident SLBRACE expression SRBRACE FROM expression { $$=appendRecvIntoArrayStatement($2, $4, $7); }
	| SEND expression TO expression { $$=appendSendStatement($2, $4); }
	| SENDRECV expression TOFROM expression INTO ident { $$=appendSendRecvStatement($2, $4, $6); }
	| SENDRECV expression TOFROM expression INTO ident SLBRACE expression SRBRACE { $$=appendSendRecvStatementIntoArray($2, $4, $6, $8); }
	| BCAST expression FROM expression INTO ident { $$=appendBcastStatement($2, $4, $6); }
	| REDUCE reductionop expression INTO ident { $$=appendReductionStatement($2, $3, $5); }
	| DIM ident SLBRACE expression SRBRACE { $$=appendDeclareArray($2, $4); }	
	| SDIM ident SLBRACE expression SRBRACE { $$=appendDeclareSharedArray($2, $4); }
	| FOR declareident EQ expression TO expression lines NEXT { $$=appendForStatement($2, $4, $6, $7); leaveScope(); }
	| DO openwhileblock expression lines closedoblock { $$=appendDoWhileStatement($3, $4); } 
	| GOTO INTEGER { $$=appendGotoStatement($2); }
	| IF expression openifblock lines closeifblock { $$=appendIfStatement($2, $4); }
	| IF expression openifblock lines elseifblock lines closeifblock { $$=appendIfElseStatement($2, $4, $6); }
	| IF expression THEN statements { $$=appendIfStatement($2, $4); }
	| INPUT ident { $$=appendInputStatement($2); }
	| INPUT constant COMMA ident { $$=appendInputStringStatement($2, $4); }
	| LET ident EQ expression { $$=appendLetStatement($2, $4); }
    | ident EQ expression { $$=appendLetStatement($1, $3); }
    | ident SLBRACE expression SRBRACE EQ expression { $$=appendArraySetStatement($1, $3, $6); }
	| PRINT expression { $$=appendPrintStatement($2); }	
	| STOP { $$=appendStopStatement(); }
	| REM { $$ = NULL; }
	| SYNC { $$=appendSyncStatement(); }
;

reductionop
	: SUM { $$=0; }
	| MIN { $$=1; }
	| MAX { $$=2; }
	| PROD { $$=3; }
;

declareident
	 : ident { $$=$1; enterScope(); addVariableIfNeeded($1); }
;

openifblock
	: THEN { enterScope(); }
;

elseifblock
	: ELSE { leaveScope(); enterScope(); }
;

openwhileblock
	: WHILE { enterScope(); }
;

closedoblock
	: ENDDO { leaveScope(); }

closeifblock
	: ENDIF { leaveScope(); }
;

expression
	: logical_or_expression { $$=$1; }
	| NOT logical_or_expression { $$=$2; }
;

logical_or_expression
	: logical_and_expression { $$=$1; }
	| logical_or_expression OR logical_and_expression { $$=createOrExpression($1, $3); }

logical_and_expression
	: equality_expression { $$=$1; }
	| logical_and_expression AND equality_expression { $$=createAndExpression($1, $3); }
;

equality_expression
	: relational_expression { $$=$1; }
	| equality_expression EQ relational_expression { $$=createEqExpression($1, $3); }
	| equality_expression NEQ relational_expression { $$=createNeqExpression($1, $3); }
;

relational_expression
	: additive_expression { $$=$1; }
	| relational_expression GT additive_expression { $$=createGtExpression($1, $3); }
	| relational_expression LT additive_expression { $$=createLtExpression($1, $3); }
	| relational_expression LEQ additive_expression { $$=createLeqExpression($1, $3); }
	| relational_expression GEQ additive_expression { $$=createGeqExpression($1, $3); }
;

additive_expression
	: multiplicative_expression { $$=$1; }
	| additive_expression ADD multiplicative_expression { $$=createAddExpression($1, $3); }
	| additive_expression SUB multiplicative_expression { $$=createSubExpression($1, $3); }
;

multiplicative_expression
	: value { $$=$1; }
	| multiplicative_expression MULT value { $$=createMulExpression($1, $3); }
	| multiplicative_expression DIV value { $$=createDivExpression($1, $3); }
	| multiplicative_expression MOD value { $$=createModExpression($1, $3); }
	| multiplicative_expression POW value { $$=createPowExpression($1, $3); }
	| SQRT value { $$=createSqrtExpression($2); }
	| SIN value { $$=createSinExpression($2); }
	| COS value { $$=createCosExpression($2); }
	| TAN value { $$=createTanExpression($2); }
	| ASIN value { $$=createASinExpression($2); }
	| ACOS value { $$=createACosExpression($2); }
	| ATAN value { $$=createATanExpression($2); }
	| SINH value { $$=createSinHExpression($2); }
	| COSH value { $$=createCosHExpression($2); }
	| TANH value { $$=createTanHExpression($2); }
	| FLOOR value { $$=createFloorExpression($2); }
	| CEIL value { $$=createCeilExpression($2); }
	| LOG value { $$=createLogExpression($2); }
	| LOG10 value { $$=createLog10Expression($2); }
;

value
	: constant { $$=$1; }
	| LPAREN expression RPAREN { $$=$2; }
	| ident { $$=createIdentifierExpression($1); }
	| ident SLBRACE expression SRBRACE { $$=createIdentifierArrayAccessExpression($1, $3); }
;

ident
	: IDENTIFIER { $$ = malloc(strlen($1)+1); strcpy($$, $1); }
;

constant
        : INTEGER { $$=createIntegerExpression($1); }
        | REAL { $$=createRealExpression($1); }
        | COREID { $$=createCoreIdExpression(); }
        | NUMCORES { $$=createNumCoresExpression(); }
        | RANDOM { $$=createRandomExpression(); }
		| unary_operator INTEGER { $$=createIntegerExpression($1 * $2); }	
		| unary_operator REAL { $$=createRealExpression($1 * $2); }
		| STRING { $$=createStringExpression($1); }	
;

unary_operator
	: ADD { $$ = 1; }
	| SUB { $$ = -1; }
;

%%
