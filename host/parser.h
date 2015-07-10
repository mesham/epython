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
    ENDIF = 270,
    ENDDO = 271,
    ELSE = 272,
    COMMA = 273,
    DO = 274,
    WHILE = 275,
    FOR = 276,
    TO = 277,
    FROM = 278,
    NEXT = 279,
    INTO = 280,
    GOTO = 281,
    PRINT = 282,
    INPUT = 283,
    IF = 284,
    THEN = 285,
    COREID = 286,
    NUMCORES = 287,
    SEND = 288,
    RECV = 289,
    RANDOM = 290,
    SYNC = 291,
    BCAST = 292,
    REDUCE = 293,
    SUM = 294,
    MIN = 295,
    MAX = 296,
    PROD = 297,
    SENDRECV = 298,
    TOFROM = 299,
    ADD = 300,
    SUB = 301,
    ISHOST = 302,
    ISDEVICE = 303,
    COLON = 304,
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
#define ENDIF 270
#define ENDDO 271
#define ELSE 272
#define COMMA 273
#define DO 274
#define WHILE 275
#define FOR 276
#define TO 277
#define FROM 278
#define NEXT 279
#define INTO 280
#define GOTO 281
#define PRINT 282
#define INPUT 283
#define IF 284
#define THEN 285
#define COREID 286
#define NUMCORES 287
#define SEND 288
#define RECV 289
#define RANDOM 290
#define SYNC 291
#define BCAST 292
#define REDUCE 293
#define SUM 294
#define MIN 295
#define MAX 296
#define PROD 297
#define SENDRECV 298
#define TOFROM 299
#define ADD 300
#define SUB 301
#define ISHOST 302
#define ISDEVICE 303
#define COLON 304
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
#line 19 "epython.y" /* yacc.c:1909  */

	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;

#line 223 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
