%{
#include "parser.h"
#include "stack.h"

static const unsigned int TAB_WIDTH = 4;

int line_num = 0, indent_caller;
char * parsing_filename=NULL;
int line_indent=0, fake_outdent_symbol=0;

extern struct stack_t indent_stack, filenameStack, lineNumberStack;

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

/* Python indentation handling based upon code at https://github.com/lucasb-eyer/flex-bison-indentation and 
http://www.benbarbour.com/implementing-python-style-indention-syntax-using-flex-bison-or-lexyacc */

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
%x INDENT_MODE
%%

\<\<\<.*\n						{ 
									if (parsing_filename != NULL) {
										pushIdentifier(&filenameStack, parsing_filename); 
										push(&lineNumberStack, line_num);
										free(parsing_filename);
									}
									parsing_filename=(char*) malloc(yyleng-3);
									strncpy(parsing_filename, &yytext[3], yyleng-4);
									parsing_filename[yyleng-4]='\0';									
									line_num=1; 
								}
\>\>\>.*\n						{
									if (getStackSize(&filenameStack) > 0) {
										parsing_filename=popIdentifier(&filenameStack);
										line_num=pop(&lineNumberStack);
									}									
								}

\/\*					{BEGIN(COMMENTS);}
<COMMENTS>\*\/			{BEGIN(INITIAL);}
<COMMENTS>\n            { ++line_num; }
<SINGLELINECOMMENT>\n	{ ++line_num;BEGIN(INITIAL); return NEWLINE; }
<COMMENTS,SINGLELINECOMMENT>.		;

<INDENT_MODE>" "     { line_indent++; }
<INDENT_MODE>\t      { line_indent+=TAB_WIDTH; }
<INDENT_MODE>\n      { line_indent=0; }
<INDENT_MODE><<EOF>> { 	if (peek(&indent_stack) > 0) {
						pop(&indent_stack);
						if (line_indent < peek(&indent_stack)) {
							int i;
                            unput('\n');
                            for (i=0;i<peek(&indent_stack);i++) unput(' ');                            
                        } else {											
							BEGIN(indent_caller);
						}
						return OUTDENT;						
					} else {
						yyterminate();
					}					 
				}
<INDENT_MODE>.		{
					if (!fake_outdent_symbol) unput(*yytext);					
					fake_outdent_symbol=0;
					if (line_indent > 0 && line_indent > peek(&indent_stack)) {
						push(&indent_stack, line_indent);						
						BEGIN(indent_caller);											
						return INDENT;
					} else if (line_indent < peek(&indent_stack)) {
						pop(&indent_stack);						
						if (peek(&indent_stack) != -1 && line_indent != peek(&indent_stack)) {
							int i;
							for(i=0;i<line_indent;i++) unput(' ');
                            unput('\n');                            
                            unput('.');                          
                            fake_outdent_symbol=1;
                            for(i=0;i<peek(&indent_stack);i++) unput(' ');
                            unput('\n');
						} else {
							BEGIN(indent_caller);
						}						
						return OUTDENT;
					} else {
						BEGIN(indent_caller);
					}
				}									

\r\n|\n                                 { ++line_num; line_indent=0; indent_caller = YY_START; BEGIN(INDENT_MODE); return NEWLINE; }
[ \t\n]                 				;
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
"="										return ASSGN;
"=="                                	return EQ;
"^"|"**"                                return POW;
","										return COMMA;
":"										return COLON;
"+"                                     return ADD;
"-"                                     return SUB;
"*"                                     return MULT;
"/"                                     return DIV;
"%"                                     return MOD;
"//"									return FLOORDIV;
"+="									return ADDADD;
"-="									return SUBSUB;
"*="									return MULMUL;
"/="									return DIVDIV;
"%="									return MODMOD;
"**="									return POWPOW;
"//="									return FLOORDIVFLOORDIV;
"["										return SLBRACE;
"]"										return SRBRACE;
"("                                     return LPAREN;
")"                                     return RPAREN;
TRUE									return TRUE;
FALSE									return FALSE;
DEF										return DEF;
RETURN									return RET;
NONE									return NONE;
ELSE                                    return ELSE;
ELIF									return ELIF;
IN										return IN;
IS										return IS;
DIM                                     return DIM;
SDIM                                    return SDIM;
WHILE									return WHILE;
EXIT                                    return EXIT;
FOR                                     return FOR;
TO                                      return TO;
FROM									return FROM;
NEXT                                    return NEXT;
GOTO                                    return GOTO;
IF                                      return IF;
PRINT                                   return PRINT;
INPUT                                   return INPUT;
NATIVE									return NATIVE;
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
STR										return STR;
"#"										BEGIN(SINGLELINECOMMENT);

[:.;]                                  return yytext[0];

[a-zA-Z_][a-zA-Z0-9_.]*           		SAVE_VALUE(IDENTIFIER);
%%
