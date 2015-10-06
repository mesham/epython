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
    EPY_I_COREID = 283,
    EPY_I_NUMCORES = 284,
    EPY_I_SEND = 285,
    EPY_I_RECV = 286,
    RANDOM = 287,
    EPY_I_SYNC = 288,
    EPY_I_BCAST = 289,
    EPY_I_REDUCE = 290,
    SUM = 291,
    MIN = 292,
    MAX = 293,
    PROD = 294,
    EPY_I_SENDRECV = 295,
    TOFROM = 296,
    ADD = 297,
    SUB = 298,
    ISHOST = 299,
    ISDEVICE = 300,
    COLON = 301,
    DEF = 302,
    RET = 303,
    NONE = 304,
    FILESTART = 305,
    MULT = 306,
    DIV = 307,
    MOD = 308,
    AND = 309,
    OR = 310,
    NEQ = 311,
    LEQ = 312,
    GEQ = 313,
    LT = 314,
    GT = 315,
    EQ = 316,
    NOT = 317,
    SQRT = 318,
    SIN = 319,
    COS = 320,
    TAN = 321,
    ASIN = 322,
    ACOS = 323,
    ATAN = 324,
    SINH = 325,
    COSH = 326,
    TANH = 327,
    FLOOR = 328,
    CEIL = 329,
    LOG = 330,
    LOG10 = 331,
    LPAREN = 332,
    RPAREN = 333,
    SLBRACE = 334,
    SRBRACE = 335,
    ASSGN = 336,
    POW = 337
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
#define EPY_I_COREID 283
#define EPY_I_NUMCORES 284
#define EPY_I_SEND 285
#define EPY_I_RECV 286
#define RANDOM 287
#define EPY_I_SYNC 288
#define EPY_I_BCAST 289
#define EPY_I_REDUCE 290
#define SUM 291
#define MIN 292
#define MAX 293
#define PROD 294
#define EPY_I_SENDRECV 295
#define TOFROM 296
#define ADD 297
#define SUB 298
#define ISHOST 299
#define ISDEVICE 300
#define COLON 301
#define DEF 302
#define RET 303
#define NONE 304
#define FILESTART 305
#define MULT 306
#define DIV 307
#define MOD 308
#define AND 309
#define OR 310
#define NEQ 311
#define LEQ 312
#define GEQ 313
#define LT 314
#define GT 315
#define EQ 316
#define NOT 317
#define SQRT 318
#define SIN 319
#define COS 320
#define TAN 321
#define ASIN 322
#define ACOS 323
#define ATAN 324
#define SINH 325
#define COSH 326
#define TANH 327
#define FLOOR 328
#define CEIL 329
#define LOG 330
#define LOG10 331
#define LPAREN 332
#define RPAREN 333
#define SLBRACE 334
#define SRBRACE 335
#define ASSGN 336
#define POW 337

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "epython.y" /* yacc.c:1909  */

	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 226 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
