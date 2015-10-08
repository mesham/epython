%{
#include "byteassembler.h"
#include "memorymanager.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

extern int line_num;
extern char * parsing_filename;
void yyerror(char const*);
int yylex(void);

void yyerror (char const *msg) {
	fprintf(stderr, "%s at line %d of file %s\n", msg, line_num, parsing_filename);
	exit(0);
}
%}

%union {
	int integer;
	unsigned char uchar;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;
}

%token <integer> INTEGER
%token <real>    REAL
%token <string>  STRING IDENTIFIER

%token NEWLINE INDENT OUTDENT
%token DIM SDIM STOP ELSE ELIF COMMA WHILE
%token FOR TO FROM NEXT INTO GOTO PRINT INPUT
%token IF THEN EPY_I_COREID EPY_I_NUMCORES EPY_I_SEND EPY_I_RECV RANDOM EPY_I_SYNC EPY_I_BCAST EPY_I_REDUCE EPY_I_SUM EPY_I_MIN EPY_I_MAX EPY_I_PROD EPY_I_SENDRECV TOFROM

%token ADD SUB EPY_I_ISHOST EPY_I_ISDEVICE COLON DEF RET NONE FILESTART IN ADDADD SUBSUB MULMUL DIVDIV MODMOD POWPOW FLOORDIVFLOORDIV FLOORDIV
%token MULT DIV MOD AND OR NEQ LEQ GEQ LT GT EQ NOT SQRT SIN COS TAN ASIN ACOS ATAN SINH COSH TANH FLOOR CEIL LOG LOG10
%token LPAREN RPAREN SLBRACE SRBRACE TRUE FALSE

%left ADD SUB LEN ADDADD SUBSUB
%left MULT DIV MOD MULMUL DIVDIV MODMOD
%left AND OR
%left NEQ LEQ GEQ LT GT EQ EPY_I_ISHOST EPY_I_ISDEVICE ASSGN
%right NOT
%right POW POWPOW FLOORDIVFLOORDIV FLOORDIV

%type <string> ident declareident
%type <integer> unary_operator 
%type <uchar> reductionop opassgn
%type <data> constant expression logical_or_expression logical_and_expression equality_expression relational_expression additive_expression multiplicative_expression value statement statements line lines codeblock elifblock
%type <stack> fndeclarationargs fncallargs

%start program 

%%

program : lines { compileMemory($1); }

lines
        : line
        | lines line { $$=concatenateMemory($1, $2); }
;

line
        : statements NEWLINE { $$ = $1; }
        | statements { $$ = $1; }        
	    | NEWLINE { $$ = NULL; }
;

statements
	: statement statements { $$=concatenateMemory($1, $2); }
	| statement
;

statement	
	: EPY_I_RECV ident FROM expression { $$=appendRecvStatement($2, $4); }
	| EPY_I_RECV ident SLBRACE expression SRBRACE FROM expression { $$=appendRecvIntoArrayStatement($2, $4, $7); }
	| EPY_I_SEND expression TO expression { $$=appendSendStatement($2, $4); }
	| EPY_I_SENDRECV expression TOFROM expression INTO ident { $$=appendSendRecvStatement($2, $4, $6); }
	| EPY_I_SENDRECV expression TOFROM expression INTO ident SLBRACE expression SRBRACE { $$=appendSendRecvStatementIntoArray($2, $4, $6, $8); }
	| EPY_I_BCAST expression FROM expression INTO ident { $$=appendBcastStatement($2, $4, $6); }
	| EPY_I_REDUCE reductionop expression INTO ident { $$=appendReductionStatement($2, $3, $5); }
	| DIM ident SLBRACE expression SRBRACE { $$=appendDeclareArray($2, $4); }	
	| SDIM ident SLBRACE expression SRBRACE { $$=appendDeclareSharedArray($2, $4); }
	| FOR declareident IN expression COLON codeblock { $$=appendForStatement($2, $4, $6); leaveScope(); }
	| WHILE expression COLON codeblock { $$=appendWhileStatement($2, $4); }	
	| IF expression COLON codeblock { $$=appendIfStatement($2, $4); }
	| IF expression COLON codeblock ELSE COLON codeblock { $$=appendIfElseStatement($2, $4, $7); }
	| IF expression COLON codeblock elifblock { $$=appendIfElseStatement($2, $4, $5); }		
	| IF expression COLON statements { $$=appendIfStatement($2, $4); }
	| ELIF expression COLON codeblock { $$=appendIfStatement($2, $4); }	
	| INPUT ident { $$=appendInputStatement($2); }
	| INPUT constant COMMA ident { $$=appendInputStringStatement($2, $4); }
    | ident ASSGN expression { $$=appendLetStatement($1, $3); }
    | ident SLBRACE expression SRBRACE ASSGN expression { $$=appendArraySetStatement($1, $3, $6); }
    | ident opassgn expression { $$=appendLetWithOperatorStatement($1, $3, $2); }
	| PRINT expression { $$=appendPrintStatement($2); }	
	| STOP { $$=appendStopStatement(); }	
	| EPY_I_SYNC { $$=appendSyncStatement(); }
	| DEF ident LPAREN fndeclarationargs RPAREN COLON codeblock { appendNewFunctionStatement($2, $4, $7); leaveScope(); $$ = NULL; }
	| RET { $$ = appendReturnStatement(); }
	| RET NONE { $$ = appendReturnStatement(); }
	| RET expression { $$ = appendReturnStatementWithExpression($2); }
	| ident LPAREN fncallargs RPAREN { $$=appendCallFunctionStatement($1, $3); }
;

fncallargs
	: /*blank*/ { $$=getNewStack(); }	
	| expression { $$=getNewStack(); pushExpression($$, $1); }
	| fncallargs COMMA expression { pushExpression($1, $3); $$=$1; }
	;

fndeclarationargs
	: /*blank*/ { enterScope(); $$=getNewStack(); }
	| ident { $$=getNewStack(); enterScope(); pushIdentifier($$, $1); appendArgument($1); }
	| ident ASSGN expression { $$=getNewStack(); enterScope(); pushIdentifierAssgnExpression($$, $1, $3); appendArgument($1); }
	| fndeclarationargs COMMA ident { pushIdentifier($1, $3); $$=$1; appendArgument($3); }	
	| fndeclarationargs COMMA ident ASSGN expression { pushIdentifierAssgnExpression($1, $3, $5); $$=$1; appendArgument($3); }
	;

codeblock
	: NEWLINE indent_rule lines outdent_rule { $$=$3; }
	
indent_rule
	: INDENT { enterScope(); }
	
outdent_rule
	: OUTDENT { leaveScope(); }
	
reductionop
	: EPY_I_SUM { $$=0; }
	| EPY_I_MIN { $$=1; }
	| EPY_I_MAX { $$=2; }
	| EPY_I_PROD { $$=3; }
;

opassgn
	: ADDADD { $$=0; }
	| SUBSUB { $$=1; }
	| MULMUL { $$=2; }
	| DIVDIV { $$=3; }
	| MODMOD { $$=4; }
	| POWPOW { $$=5; }
	| FLOORDIVFLOORDIV { $$=6; }

declareident
	 : ident { $$=$1; enterScope(); addVariableIfNeeded($1); }
;

elifblock
	: ELIF expression COLON codeblock { $$=appendIfStatement($2, $4); }
	| ELIF expression COLON codeblock ELSE COLON codeblock { $$=appendIfElseStatement($2, $4, $7); }
	| ELIF expression COLON codeblock elifblock { $$=appendIfElseStatement($2, $4, $5); }
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
	| EPY_I_ISHOST { $$=createIsHostExpression(); }
	| EPY_I_ISDEVICE { $$=createIsDeviceExpression(); }
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
	| multiplicative_expression FLOORDIV value { $$=createFloorDivExpression($1, $3); }
	| multiplicative_expression MOD value { $$=createModExpression($1, $3); }
	| multiplicative_expression POW value { $$=createPowExpression($1, $3); }
	| SQRT LPAREN value RPAREN { $$=createSqrtExpression($3); }
	| SIN LPAREN value RPAREN { $$=createSinExpression($3); }
	| COS LPAREN value RPAREN { $$=createCosExpression($3); }
	| TAN LPAREN value RPAREN { $$=createTanExpression($3); }
	| ASIN LPAREN value RPAREN { $$=createASinExpression($3); }
	| ACOS LPAREN value RPAREN { $$=createACosExpression($3); }
	| ATAN LPAREN value RPAREN { $$=createATanExpression($3); }
	| SINH LPAREN value RPAREN { $$=createSinHExpression($3); }
	| COSH LPAREN value RPAREN { $$=createCosHExpression($3); }
	| TANH LPAREN value RPAREN { $$=createTanHExpression($3); }
	| FLOOR LPAREN value RPAREN { $$=createFloorExpression($3); }
	| CEIL LPAREN value RPAREN { $$=createCeilExpression($3); }
	| LOG LPAREN value RPAREN { $$=createLogExpression($3); }
	| LOG10 LPAREN value RPAREN { $$=createLog10Expression($3); }
	| LEN LPAREN expression RPAREN { $$=createLenExpression($3); }	
;

value
	: constant { $$=$1; }
	| LPAREN expression RPAREN { $$=$2; }
	| ident { $$=createIdentifierExpression($1); }
	| ident SLBRACE expression SRBRACE { $$=createIdentifierArrayAccessExpression($1, $3); }
	| ident LPAREN fncallargs RPAREN { $$=appendCallFunctionStatement($1, $3); }
;

ident
	: IDENTIFIER { $$ = malloc(strlen($1)+1); strcpy($$, $1); }
;

constant
        : INTEGER { $$=createIntegerExpression($1); }
        | REAL { $$=createRealExpression($1); }
        | EPY_I_COREID { $$=createCoreIdExpression(); }
        | EPY_I_NUMCORES { $$=createNumCoresExpression(); }
        | RANDOM { $$=createRandomExpression(); }
		| unary_operator INTEGER { $$=createIntegerExpression($1 * $2); }	
		| unary_operator REAL { $$=createRealExpression($1 * $2); }		
		| STRING { $$=createStringExpression($1); }	
		| TRUE { $$=createBooleanExpression(1); }
		| FALSE { $$=createBooleanExpression(0); }
;

unary_operator
	: ADD { $$ = 1; }
	| SUB { $$ = -1; }
;

%%
