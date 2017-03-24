/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTEGER = 258,
    REAL = 259,
    STRING = 260,
    IDENTIFIER = 261,
    NEWLINE = 262,
    INDENT = 263,
    OUTDENT = 264,
    DIM = 265,
    SDIM = 266,
    EXIT = 267,
    QUIT = 268,
    ELSE = 269,
    ELIF = 270,
    COMMA = 271,
    WHILE = 272,
    PASS = 273,
    AT = 274,
    FOR = 275,
    TO = 276,
    FROM = 277,
    NEXT = 278,
    GOTO = 279,
    PRINT = 280,
    INPUT = 281,
    IF = 282,
    NATIVE = 283,
    ADD = 284,
    SUB = 285,
    COLON = 286,
    DEF = 287,
    RET = 288,
    NONE = 289,
    FILESTART = 290,
    IN = 291,
    ADDADD = 292,
    SUBSUB = 293,
    MULMUL = 294,
    DIVDIV = 295,
    MODMOD = 296,
    POWPOW = 297,
    FLOORDIVFLOORDIV = 298,
    FLOORDIV = 299,
    MULT = 300,
    DIV = 301,
    MOD = 302,
    AND = 303,
    OR = 304,
    NEQ = 305,
    LEQ = 306,
    GEQ = 307,
    LT = 308,
    GT = 309,
    EQ = 310,
    IS = 311,
    NOT = 312,
    STR = 313,
    ID = 314,
    SYMBOL = 315,
    ALIAS = 316,
    LPAREN = 317,
    RPAREN = 318,
    SLBRACE = 319,
    SRBRACE = 320,
    TRUE = 321,
    FALSE = 322,
    ASSGN = 323,
    POW = 324
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define REAL 259
#define STRING 260
#define IDENTIFIER 261
#define NEWLINE 262
#define INDENT 263
#define OUTDENT 264
#define DIM 265
#define SDIM 266
#define EXIT 267
#define QUIT 268
#define ELSE 269
#define ELIF 270
#define COMMA 271
#define WHILE 272
#define PASS 273
#define AT 274
#define FOR 275
#define TO 276
#define FROM 277
#define NEXT 278
#define GOTO 279
#define PRINT 280
#define INPUT 281
#define IF 282
#define NATIVE 283
#define ADD 284
#define SUB 285
#define COLON 286
#define DEF 287
#define RET 288
#define NONE 289
#define FILESTART 290
#define IN 291
#define ADDADD 292
#define SUBSUB 293
#define MULMUL 294
#define DIVDIV 295
#define MODMOD 296
#define POWPOW 297
#define FLOORDIVFLOORDIV 298
#define FLOORDIV 299
#define MULT 300
#define DIV 301
#define MOD 302
#define AND 303
#define OR 304
#define NEQ 305
#define LEQ 306
#define GEQ 307
#define LT 308
#define GT 309
#define EQ 310
#define IS 311
#define NOT 312
#define STR 313
#define ID 314
#define SYMBOL 315
#define ALIAS 316
#define LPAREN 317
#define RPAREN 318
#define SLBRACE 319
#define SRBRACE 320
#define TRUE 321
#define FALSE 322
#define ASSGN 323
#define POW 324

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "epython.y" /* yacc.c:1909  */

	int integer;
	unsigned char uchar;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 201 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
