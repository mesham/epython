/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
    REM = 265,
    DIM = 266,
    SDIM = 267,
    LET = 268,
    STOP = 269,
    ELSE = 270,
    COMMA = 271,
    WHILE = 272,
    FOR = 273,
    TO = 274,
    FROM = 275,
    NEXT = 276,
    INTO = 277,
    GOTO = 278,
    PRINT = 279,
    INPUT = 280,
    IF = 281,
    THEN = 282,
    COREID = 283,
    NUMCORES = 284,
    SEND = 285,
    RECV = 286,
    RANDOM = 287,
    SYNC = 288,
    BCAST = 289,
    REDUCE = 290,
    SUM = 291,
    MIN = 292,
    MAX = 293,
    PROD = 294,
    SENDRECV = 295,
    TOFROM = 296,
    ADD = 297,
    SUB = 298,
    ISHOST = 299,
    ISDEVICE = 300,
    COLON = 301,
    DEF = 302,
    RET = 303,
    NONE = 304,
    MULT = 305,
    DIV = 306,
    MOD = 307,
    AND = 308,
    OR = 309,
    NEQ = 310,
    LEQ = 311,
    GEQ = 312,
    LT = 313,
    GT = 314,
    EQ = 315,
    NOT = 316,
    SQRT = 317,
    SIN = 318,
    COS = 319,
    TAN = 320,
    ASIN = 321,
    ACOS = 322,
    ATAN = 323,
    SINH = 324,
    COSH = 325,
    TANH = 326,
    FLOOR = 327,
    CEIL = 328,
    LOG = 329,
    LOG10 = 330,
    LPAREN = 331,
    RPAREN = 332,
    SLBRACE = 333,
    SRBRACE = 334,
    ASSGN = 335,
    POW = 336
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
#define REM 265
#define DIM 266
#define SDIM 267
#define LET 268
#define STOP 269
#define ELSE 270
#define COMMA 271
#define WHILE 272
#define FOR 273
#define TO 274
#define FROM 275
#define NEXT 276
#define INTO 277
#define GOTO 278
#define PRINT 279
#define INPUT 280
#define IF 281
#define THEN 282
#define COREID 283
#define NUMCORES 284
#define SEND 285
#define RECV 286
#define RANDOM 287
#define SYNC 288
#define BCAST 289
#define REDUCE 290
#define SUM 291
#define MIN 292
#define MAX 293
#define PROD 294
#define SENDRECV 295
#define TOFROM 296
#define ADD 297
#define SUB 298
#define ISHOST 299
#define ISDEVICE 300
#define COLON 301
#define DEF 302
#define RET 303
#define NONE 304
#define MULT 305
#define DIV 306
#define MOD 307
#define AND 308
#define OR 309
#define NEQ 310
#define LEQ 311
#define GEQ 312
#define LT 313
#define GT 314
#define EQ 315
#define NOT 316
#define SQRT 317
#define SIN 318
#define COS 319
#define TAN 320
#define ASIN 321
#define ACOS 322
#define ATAN 323
#define SINH 324
#define COSH 325
#define TANH 326
#define FLOOR 327
#define CEIL 328
#define LOG 329
#define LOG10 330
#define LPAREN 331
#define RPAREN 332
#define SLBRACE 333
#define SRBRACE 334
#define ASSGN 335
#define POW 336

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 20 "epython.y" /* yacc.c:1909  */

	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 224 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
