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
    DIM = 265,
    SDIM = 266,
    LET = 267,
    STOP = 268,
    ELSE = 269,
    ELIF = 270,
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
    EPY_I_ISHOST = 299,
    EPY_I_ISDEVICE = 300,
    COLON = 301,
    DEF = 302,
    RET = 303,
    NONE = 304,
    FILESTART = 305,
    IN = 306,
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
    LEN = 339,
    ISHOST = 340,
    ISDEVICE = 341,
    ASSGN = 342,
    POW = 343
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
#define LET 267
#define STOP 268
#define ELSE 269
#define ELIF 270
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
#define EPY_I_ISHOST 299
#define EPY_I_ISDEVICE 300
#define COLON 301
#define DEF 302
#define RET 303
#define NONE 304
#define FILESTART 305
#define IN 306
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
#define LEN 339
#define ISHOST 340
#define ISDEVICE 341
#define ASSGN 342
#define POW 343

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

#line 238 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
