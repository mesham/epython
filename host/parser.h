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
    MULT = 302,
    DIV = 303,
    MOD = 304,
    AND = 305,
    OR = 306,
    NEQ = 307,
    LEQ = 308,
    GEQ = 309,
    LT = 310,
    GT = 311,
    EQ = 312,
    NOT = 313,
    SQRT = 314,
    SIN = 315,
    COS = 316,
    TAN = 317,
    ASIN = 318,
    ACOS = 319,
    ATAN = 320,
    SINH = 321,
    COSH = 322,
    TANH = 323,
    FLOOR = 324,
    CEIL = 325,
    LOG = 326,
    LOG10 = 327,
    LPAREN = 328,
    RPAREN = 329,
    SLBRACE = 330,
    SRBRACE = 331,
    ASSGN = 332,
    POW = 333
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
#define MULT 302
#define DIV 303
#define MOD 304
#define AND 305
#define OR 306
#define NEQ 307
#define LEQ 308
#define GEQ 309
#define LT 310
#define GT 311
#define EQ 312
#define NOT 313
#define SQRT 314
#define SIN 315
#define COS 316
#define TAN 317
#define ASIN 318
#define ACOS 319
#define ATAN 320
#define SINH 321
#define COSH 322
#define TANH 323
#define FLOOR 324
#define CEIL 325
#define LOG 326
#define LOG10 327
#define LPAREN 328
#define RPAREN 329
#define SLBRACE 330
#define SRBRACE 331
#define ASSGN 332
#define POW 333

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 19 "epython.y" /* yacc.c:1909  */

	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;

#line 217 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
