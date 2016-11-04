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
    EPY_I_RANDOM = 284,
    EPY_I_BCAST = 285,
    EPY_I_REDUCE = 286,
    EPY_I_SUM = 287,
    EPY_I_MIN = 288,
    EPY_I_MAX = 289,
    EPY_I_PROD = 290,
    EPY_I_SENDRECV = 291,
    TOFROM = 292,
    EPY_I_FREE = 293,
    NATIVE = 294,
    ADD = 295,
    SUB = 296,
    COLON = 297,
    DEF = 298,
    RET = 299,
    NONE = 300,
    FILESTART = 301,
    IN = 302,
    ADDADD = 303,
    SUBSUB = 304,
    MULMUL = 305,
    DIVDIV = 306,
    MODMOD = 307,
    POWPOW = 308,
    FLOORDIVFLOORDIV = 309,
    FLOORDIV = 310,
    MULT = 311,
    DIV = 312,
    MOD = 313,
    AND = 314,
    OR = 315,
    NEQ = 316,
    LEQ = 317,
    GEQ = 318,
    LT = 319,
    GT = 320,
    EQ = 321,
    IS = 322,
    NOT = 323,
    SQRT = 324,
    SIN = 325,
    COS = 326,
    TAN = 327,
    ASIN = 328,
    ACOS = 329,
    ATAN = 330,
    SINH = 331,
    COSH = 332,
    TANH = 333,
    FLOOR = 334,
    CEIL = 335,
    LOG = 336,
    LOG10 = 337,
    STR = 338,
    LPAREN = 339,
    RPAREN = 340,
    SLBRACE = 341,
    SRBRACE = 342,
    TRUE = 343,
    FALSE = 344,
    LEN = 345,
    EPY_I_ISHOST = 346,
    EPY_I_ISDEVICE = 347,
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
#define EPY_I_RANDOM 284
#define EPY_I_BCAST 285
#define EPY_I_REDUCE 286
#define EPY_I_SUM 287
#define EPY_I_MIN 288
#define EPY_I_MAX 289
#define EPY_I_PROD 290
#define EPY_I_SENDRECV 291
#define TOFROM 292
#define EPY_I_FREE 293
#define NATIVE 294
#define ADD 295
#define SUB 296
#define COLON 297
#define DEF 298
#define RET 299
#define NONE 300
#define FILESTART 301
#define IN 302
#define ADDADD 303
#define SUBSUB 304
#define MULMUL 305
#define DIVDIV 306
#define MODMOD 307
#define POWPOW 308
#define FLOORDIVFLOORDIV 309
#define FLOORDIV 310
#define MULT 311
#define DIV 312
#define MOD 313
#define AND 314
#define OR 315
#define NEQ 316
#define LEQ 317
#define GEQ 318
#define LT 319
#define GT 320
#define EQ 321
#define IS 322
#define NOT 323
#define SQRT 324
#define SIN 325
#define COS 326
#define TAN 327
#define ASIN 328
#define ACOS 329
#define ATAN 330
#define SINH 331
#define COSH 332
#define TANH 333
#define FLOOR 334
#define CEIL 335
#define LOG 336
#define LOG10 337
#define STR 338
#define LPAREN 339
#define RPAREN 340
#define SLBRACE 341
#define SRBRACE 342
#define TRUE 343
#define FALSE 344
#define LEN 345
#define EPY_I_ISHOST 346
#define EPY_I_ISDEVICE 347
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
