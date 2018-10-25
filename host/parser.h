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
    HEX = 259,
    REAL = 260,
    STRING = 261,
    IDENTIFIER = 262,
    NEWLINE = 263,
    INDENT = 264,
    OUTDENT = 265,
    DIM = 266,
    SDIM = 267,
    EXIT = 268,
    QUIT = 269,
    ELSE = 270,
    ELIF = 271,
    COMMA = 272,
    WHILE = 273,
    PASS = 274,
    AT = 275,
    FOR = 276,
    TO = 277,
    FROM = 278,
    NEXT = 279,
    GOTO = 280,
    PRINT = 281,
    INPUT = 282,
    IF = 283,
    NATIVE = 284,
    ADD = 285,
    SUB = 286,
    COLON = 287,
    DEF = 288,
    RET = 289,
    NONE = 290,
    FILESTART = 291,
    IN = 292,
    ADDADD = 293,
    SUBSUB = 294,
    MULMUL = 295,
    DIVDIV = 296,
    MODMOD = 297,
    POWPOW = 298,
    FLOORDIVFLOORDIV = 299,
    FLOORDIV = 300,
    MULT = 301,
    DIV = 302,
    MOD = 303,
    AND = 304,
    OR = 305,
    NEQ = 306,
    LEQ = 307,
    GEQ = 308,
    LT = 309,
    GT = 310,
    EQ = 311,
    IS = 312,
    NOT = 313,
    STR = 314,
    ID = 315,
    SYMBOL = 316,
    ALIAS = 317,
    LPAREN = 318,
    RPAREN = 319,
    SLBRACE = 320,
    SRBRACE = 321,
    TRUE = 322,
    FALSE = 323,
    ASSGN = 324,
    POW = 325
  };
#endif
/* Tokens.  */
#define INTEGER 258
#define HEX 259
#define REAL 260
#define STRING 261
#define IDENTIFIER 262
#define NEWLINE 263
#define INDENT 264
#define OUTDENT 265
#define DIM 266
#define SDIM 267
#define EXIT 268
#define QUIT 269
#define ELSE 270
#define ELIF 271
#define COMMA 272
#define WHILE 273
#define PASS 274
#define AT 275
#define FOR 276
#define TO 277
#define FROM 278
#define NEXT 279
#define GOTO 280
#define PRINT 281
#define INPUT 282
#define IF 283
#define NATIVE 284
#define ADD 285
#define SUB 286
#define COLON 287
#define DEF 288
#define RET 289
#define NONE 290
#define FILESTART 291
#define IN 292
#define ADDADD 293
#define SUBSUB 294
#define MULMUL 295
#define DIVDIV 296
#define MODMOD 297
#define POWPOW 298
#define FLOORDIVFLOORDIV 299
#define FLOORDIV 300
#define MULT 301
#define DIV 302
#define MOD 303
#define AND 304
#define OR 305
#define NEQ 306
#define LEQ 307
#define GEQ 308
#define LT 309
#define GT 310
#define EQ 311
#define IS 312
#define NOT 313
#define STR 314
#define ID 315
#define SYMBOL 316
#define ALIAS 317
#define LPAREN 318
#define RPAREN 319
#define SLBRACE 320
#define SRBRACE 321
#define TRUE 322
#define FALSE 323
#define ASSGN 324
#define POW 325

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

#line 203 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
