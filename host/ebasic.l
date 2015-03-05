%{
#include "parser.h"
int line_num = 1;

void yyget_INTEGER(YYSTYPE*, char*, size_t);
void yyget_REAL (YYSTYPE*, char*, size_t);
void yyget_STRING(YYSTYPE*, char*, size_t);

#define yyget_IDENTIFIER yyget_STRING
#define SAVE_VALUE(type)					\
{						\
        yyget_##type(&yylval, yytext, yyleng);	\
        return  type;				\
}

void yyget_INTEGER(YYSTYPE *outval, char *text, size_t len) {
	outval->integer = atoi(text);
}

void yyget_REAL(YYSTYPE *outval, char *text, size_t len) {
	outval->real = atof(text);
}

void yyget_STRING(YYSTYPE *outval, char *text, size_t len) {
	outval->string = text;
}
%}

O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\n\f]

STRING_CHARS [[:print:]]{-}[\"]

%option noyywrap case-insensitive
%x COMMENTS
%x SINGLELINECOMMENT
%%

\/\*					{BEGIN(COMMENTS);}
<COMMENTS>\*\/			{BEGIN(INITIAL);}
<COMMENTS>\n            { ++line_num; }
<SINGLELINECOMMENT>\n	{ ++line_num;BEGIN(INITIAL); }
<COMMENTS,SINGLELINECOMMENT>.		;

\r\n|\n                                 { ++line_num; return NEWLINE; }
[ \t\n]                 				;
REM{WS}*[[:print:]]*                    return REM;
\"{STRING_CHARS}*\"                     SAVE_VALUE(STRING);

{HP}{H}+{IS}?							SAVE_VALUE(INTEGER); 
{NZ}{D}*{IS}?							SAVE_VALUE(INTEGER);
"0"{O}*{IS}?							SAVE_VALUE(INTEGER);
{CP}?"'"([^'\\\n]|{ES})+"'"				SAVE_VALUE(INTEGER);

{D}+{E}{FS}?							SAVE_VALUE(REAL); 
{D}*"."{D}+{E}?{FS}?					SAVE_VALUE(REAL);
{D}+"."{E}?{FS}?						SAVE_VALUE(REAL);
{HP}{H}+{P}{FS}?						SAVE_VALUE(REAL); 
{HP}{H}*"."{H}+{P}{FS}?					SAVE_VALUE(REAL);
{HP}{H}+"."{P}{FS}?						SAVE_VALUE(REAL);
      
AND                                     return AND;
OR                                      return OR;
NOT|"!"                                 return NOT;
"<>"|"!="                               return NEQ;
"<="                                    return LEQ;
">="                                    return GEQ;
"<"                                     return LT;
">"                                     return GT;
"="|"=="                                return EQ;
"^"|"**"                                return POW;
","										return COMMA;
"+"                                     return ADD;
"-"                                     return SUB;
"*"                                     return MULT;
"/"                                     return DIV;
"%"                                     return MOD;
"["										return SLBRACE;
"]"										return SRBRACE;
"("                                     return LPAREN;
")"                                     return RPAREN;
ELSE                                    return ELSE;
SEND									return SEND;
RECV									return RECV;
SYNC									return SYNC;
BCAST									return BCAST;
REDUCE									return REDUCE;
INTO									return INTO;
SUM										return SUM;
MIN										return MIN;
MAX										return MAX;
PROD									return PROD;
DIM                                     return DIM;
SDIM                                    return SDIM;
END{WS}IF								return ENDIF;
LET                                     return LET;
STOP                                    return STOP;
FOR                                     return FOR;
TO                                      return TO;
FROM									return FROM;
NEXT                                    return NEXT;
GOTO                                    return GOTO;
IF                                      return IF;
THEN                                    return THEN;
PRINT                                   return PRINT;
INPUT                                   return INPUT;
COREID									return COREID;
RANDOM									return RANDOM;
SQRT									return SQRT;
SIN										return SIN;
COS										return COS;
TAN										return TAN;
ASIN									return ASIN;
ACOS									return ACOS;
ATAN									return ATAN;
SINH									return SINH;
COSH									return COSH;
TANH									return TANH;
FLOOR									return FLOOR;
CEIL									return CEIL;
LOG										return LOG;
LOG10									return LOG10;
"//"									BEGIN(SINGLELINECOMMENT);

[:.;]                                  return yytext[0];

[a-zA-Z_][a-zA-Z0-9_]*           		SAVE_VALUE(IDENTIFIER);
%%
