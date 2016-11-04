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
    EPY_I_RANDOM = 286,
    EPY_I_SYNC = 287,
    EPY_I_BCAST = 288,
    EPY_I_REDUCE = 289,
    EPY_I_SUM = 290,
    EPY_I_MIN = 291,
    EPY_I_MAX = 292,
    EPY_I_PROD = 293,
    EPY_I_SENDRECV = 294,
    TOFROM = 295,
    EPY_I_FREE = 296,
    EPY_I_GC = 297,
    NATIVE = 298,
    ADD = 299,
    SUB = 300,
    COLON = 301,
    DEF = 302,
    RET = 303,
    NONE = 304,
    FILESTART = 305,
    IN = 306,
    ADDADD = 307,
    SUBSUB = 308,
    MULMUL = 309,
    DIVDIV = 310,
    MODMOD = 311,
    POWPOW = 312,
    FLOORDIVFLOORDIV = 313,
    FLOORDIV = 314,
    MULT = 315,
    DIV = 316,
    MOD = 317,
    AND = 318,
    OR = 319,
    NEQ = 320,
    LEQ = 321,
    GEQ = 322,
    LT = 323,
    GT = 324,
    EQ = 325,
    IS = 326,
    NOT = 327,
    SQRT = 328,
    SIN = 329,
    COS = 330,
    TAN = 331,
    ASIN = 332,
    ACOS = 333,
    ATAN = 334,
    SINH = 335,
    COSH = 336,
    TANH = 337,
    FLOOR = 338,
    CEIL = 339,
    LOG = 340,
    LOG10 = 341,
    STR = 342,
    LPAREN = 343,
    RPAREN = 344,
    SLBRACE = 345,
    SRBRACE = 346,
    TRUE = 347,
    FALSE = 348,
    LEN = 349,
    EPY_I_ISHOST = 350,
    EPY_I_ISDEVICE = 351,
    ASSGN = 352,
    POW = 353
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
#define EPY_I_RANDOM 286
#define EPY_I_SYNC 287
#define EPY_I_BCAST 288
#define EPY_I_REDUCE 289
#define EPY_I_SUM 290
#define EPY_I_MIN 291
#define EPY_I_MAX 292
#define EPY_I_PROD 293
#define EPY_I_SENDRECV 294
#define TOFROM 295
#define EPY_I_FREE 296
#define EPY_I_GC 297
#define NATIVE 298
#define ADD 299
#define SUB 300
#define COLON 301
#define DEF 302
#define RET 303
#define NONE 304
#define FILESTART 305
#define IN 306
#define ADDADD 307
#define SUBSUB 308
#define MULMUL 309
#define DIVDIV 310
#define MODMOD 311
#define POWPOW 312
#define FLOORDIVFLOORDIV 313
#define FLOORDIV 314
#define MULT 315
#define DIV 316
#define MOD 317
#define AND 318
#define OR 319
#define NEQ 320
#define LEQ 321
#define GEQ 322
#define LT 323
#define GT 324
#define EQ 325
#define IS 326
#define NOT 327
#define SQRT 328
#define SIN 329
#define COS 330
#define TAN 331
#define ASIN 332
#define ACOS 333
#define ATAN 334
#define SINH 335
#define COSH 336
#define TANH 337
#define FLOOR 338
#define CEIL 339
#define LOG 340
#define LOG10 341
#define STR 342
#define LPAREN 343
#define RPAREN 344
#define SLBRACE 345
#define SRBRACE 346
#define TRUE 347
#define FALSE 348
#define LEN 349
#define EPY_I_ISHOST 350
#define EPY_I_ISDEVICE 351
#define ASSGN 352
#define POW 353

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

#line 259 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
