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
    EXIT = 267,
    ELSE = 268,
    ELIF = 269,
    COMMA = 270,
    WHILE = 271,
    FOR = 272,
    TO = 273,
    FROM = 274,
    NEXT = 275,
    INTO = 276,
    GOTO = 277,
    PRINT = 278,
    INPUT = 279,
    IF = 280,
    THEN = 281,
    EPY_I_COREID = 282,
    EPY_I_NUMCORES = 283,
    EPY_I_SEND = 284,
    EPY_I_RECV = 285,
    RANDOM = 286,
    EPY_I_SYNC = 287,
    EPY_I_BCAST = 288,
    EPY_I_REDUCE = 289,
    EPY_I_SUM = 290,
    EPY_I_MIN = 291,
    EPY_I_MAX = 292,
    EPY_I_PROD = 293,
    EPY_I_SENDRECV = 294,
    TOFROM = 295,
    ADD = 296,
    SUB = 297,
    EPY_I_ISHOST = 298,
    EPY_I_ISDEVICE = 299,
    COLON = 300,
    DEF = 301,
    RET = 302,
    NONE = 303,
    FILESTART = 304,
    IN = 305,
    ADDADD = 306,
    SUBSUB = 307,
    MULMUL = 308,
    DIVDIV = 309,
    MODMOD = 310,
    POWPOW = 311,
    FLOORDIVFLOORDIV = 312,
    FLOORDIV = 313,
    MULT = 314,
    DIV = 315,
    MOD = 316,
    AND = 317,
    OR = 318,
    NEQ = 319,
    LEQ = 320,
    GEQ = 321,
    LT = 322,
    GT = 323,
    EQ = 324,
    IS = 325,
    NOT = 326,
    SQRT = 327,
    SIN = 328,
    COS = 329,
    TAN = 330,
    ASIN = 331,
    ACOS = 332,
    ATAN = 333,
    SINH = 334,
    COSH = 335,
    TANH = 336,
    FLOOR = 337,
    CEIL = 338,
    LOG = 339,
    LOG10 = 340,
    LPAREN = 341,
    RPAREN = 342,
    SLBRACE = 343,
    SRBRACE = 344,
    TRUE = 345,
    FALSE = 346,
    LEN = 347,
    ASSGN = 348,
    POW = 349
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
#define ELSE 268
#define ELIF 269
#define COMMA 270
#define WHILE 271
#define FOR 272
#define TO 273
#define FROM 274
#define NEXT 275
#define INTO 276
#define GOTO 277
#define PRINT 278
#define INPUT 279
#define IF 280
#define THEN 281
#define EPY_I_COREID 282
#define EPY_I_NUMCORES 283
#define EPY_I_SEND 284
#define EPY_I_RECV 285
#define RANDOM 286
#define EPY_I_SYNC 287
#define EPY_I_BCAST 288
#define EPY_I_REDUCE 289
#define EPY_I_SUM 290
#define EPY_I_MIN 291
#define EPY_I_MAX 292
#define EPY_I_PROD 293
#define EPY_I_SENDRECV 294
#define TOFROM 295
#define ADD 296
#define SUB 297
#define EPY_I_ISHOST 298
#define EPY_I_ISDEVICE 299
#define COLON 300
#define DEF 301
#define RET 302
#define NONE 303
#define FILESTART 304
#define IN 305
#define ADDADD 306
#define SUBSUB 307
#define MULMUL 308
#define DIVDIV 309
#define MODMOD 310
#define POWPOW 311
#define FLOORDIVFLOORDIV 312
#define FLOORDIV 313
#define MULT 314
#define DIV 315
#define MOD 316
#define AND 317
#define OR 318
#define NEQ 319
#define LEQ 320
#define GEQ 321
#define LT 322
#define GT 323
#define EQ 324
#define IS 325
#define NOT 326
#define SQRT 327
#define SIN 328
#define COS 329
#define TAN 330
#define ASIN 331
#define ACOS 332
#define ATAN 333
#define SINH 334
#define COSH 335
#define TANH 336
#define FLOOR 337
#define CEIL 338
#define LOG 339
#define LOG10 340
#define LPAREN 341
#define RPAREN 342
#define SLBRACE 343
#define SRBRACE 344
#define TRUE 345
#define FALSE 346
#define LEN 347
#define ASSGN 348
#define POW 349

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "epython.y" /* yacc.c:1909  */

	int integer;
	unsigned char uchar;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 251 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
