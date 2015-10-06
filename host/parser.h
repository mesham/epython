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
    ELIF = 271,
    COMMA = 272,
    WHILE = 273,
    FOR = 274,
    TO = 275,
    FROM = 276,
    NEXT = 277,
    INTO = 278,
    GOTO = 279,
    PRINT = 280,
    INPUT = 281,
    IF = 282,
    THEN = 283,
    EPY_I_COREID = 284,
    EPY_I_NUMCORES = 285,
    EPY_I_SEND = 286,
    EPY_I_RECV = 287,
    RANDOM = 288,
    EPY_I_SYNC = 289,
    EPY_I_BCAST = 290,
    EPY_I_REDUCE = 291,
    SUM = 292,
    MIN = 293,
    MAX = 294,
    PROD = 295,
    EPY_I_SENDRECV = 296,
    TOFROM = 297,
    ADD = 298,
    SUB = 299,
    EPY_I_ISHOST = 300,
    EPY_I_ISDEVICE = 301,
    COLON = 302,
    DEF = 303,
    RET = 304,
    NONE = 305,
    FILESTART = 306,
    MULT = 307,
    DIV = 308,
    MOD = 309,
    AND = 310,
    OR = 311,
    NEQ = 312,
    LEQ = 313,
    GEQ = 314,
    LT = 315,
    GT = 316,
    EQ = 317,
    NOT = 318,
    SQRT = 319,
    SIN = 320,
    COS = 321,
    TAN = 322,
    ASIN = 323,
    ACOS = 324,
    ATAN = 325,
    SINH = 326,
    COSH = 327,
    TANH = 328,
    FLOOR = 329,
    CEIL = 330,
    LOG = 331,
    LOG10 = 332,
    LPAREN = 333,
    RPAREN = 334,
    SLBRACE = 335,
    SRBRACE = 336,
    TRUE = 337,
    FALSE = 338,
    ISHOST = 339,
    ISDEVICE = 340,
    ASSGN = 341,
    POW = 342
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
#define ELIF 271
#define COMMA 272
#define WHILE 273
#define FOR 274
#define TO 275
#define FROM 276
#define NEXT 277
#define INTO 278
#define GOTO 279
#define PRINT 280
#define INPUT 281
#define IF 282
#define THEN 283
#define EPY_I_COREID 284
#define EPY_I_NUMCORES 285
#define EPY_I_SEND 286
#define EPY_I_RECV 287
#define RANDOM 288
#define EPY_I_SYNC 289
#define EPY_I_BCAST 290
#define EPY_I_REDUCE 291
#define SUM 292
#define MIN 293
#define MAX 294
#define PROD 295
#define EPY_I_SENDRECV 296
#define TOFROM 297
#define ADD 298
#define SUB 299
#define EPY_I_ISHOST 300
#define EPY_I_ISDEVICE 301
#define COLON 302
#define DEF 303
#define RET 304
#define NONE 305
#define FILESTART 306
#define MULT 307
#define DIV 308
#define MOD 309
#define AND 310
#define OR 311
#define NEQ 312
#define LEQ 313
#define GEQ 314
#define LT 315
#define GT 316
#define EQ 317
#define NOT 318
#define SQRT 319
#define SIN 320
#define COS 321
#define TAN 322
#define ASIN 323
#define ACOS 324
#define ATAN 325
#define SINH 326
#define COSH 327
#define TANH 328
#define FLOOR 329
#define CEIL 330
#define LOG 331
#define LOG10 332
#define LPAREN 333
#define RPAREN 334
#define SLBRACE 335
#define SRBRACE 336
#define TRUE 337
#define FALSE 338
#define ISHOST 339
#define ISDEVICE 340
#define ASSGN 341
#define POW 342

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

#line 236 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
