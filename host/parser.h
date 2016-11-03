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
    ADD = 298,
    SUB = 299,
    EPY_I_ISHOST = 300,
    EPY_I_DIMS = 301,
    EPY_I_DSIZE = 302,
    EPY_I_ISDEVICE = 303,
    COLON = 304,
    DEF = 305,
    RET = 306,
    NONE = 307,
    FILESTART = 308,
    IN = 309,
    ADDADD = 310,
    SUBSUB = 311,
    MULMUL = 312,
    DIVDIV = 313,
    MODMOD = 314,
    POWPOW = 315,
    FLOORDIVFLOORDIV = 316,
    FLOORDIV = 317,
    MULT = 318,
    DIV = 319,
    MOD = 320,
    AND = 321,
    OR = 322,
    NEQ = 323,
    LEQ = 324,
    GEQ = 325,
    LT = 326,
    GT = 327,
    EQ = 328,
    IS = 329,
    NOT = 330,
    SQRT = 331,
    SIN = 332,
    COS = 333,
    TAN = 334,
    ASIN = 335,
    ACOS = 336,
    ATAN = 337,
    SINH = 338,
    COSH = 339,
    TANH = 340,
    FLOOR = 341,
    CEIL = 342,
    LOG = 343,
    LOG10 = 344,
    STR = 345,
    LPAREN = 346,
    RPAREN = 347,
    SLBRACE = 348,
    SRBRACE = 349,
    TRUE = 350,
    FALSE = 351,
    LEN = 352,
    ASSGN = 353,
    POW = 354
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
#define ADD 298
#define SUB 299
#define EPY_I_ISHOST 300
#define EPY_I_DIMS 301
#define EPY_I_DSIZE 302
#define EPY_I_ISDEVICE 303
#define COLON 304
#define DEF 305
#define RET 306
#define NONE 307
#define FILESTART 308
#define IN 309
#define ADDADD 310
#define SUBSUB 311
#define MULMUL 312
#define DIVDIV 313
#define MODMOD 314
#define POWPOW 315
#define FLOORDIVFLOORDIV 316
#define FLOORDIV 317
#define MULT 318
#define DIV 319
#define MOD 320
#define AND 321
#define OR 322
#define NEQ 323
#define LEQ 324
#define GEQ 325
#define LT 326
#define GT 327
#define EQ 328
#define IS 329
#define NOT 330
#define SQRT 331
#define SIN 332
#define COS 333
#define TAN 334
#define ASIN 335
#define ACOS 336
#define ATAN 337
#define SINH 338
#define COSH 339
#define TANH 340
#define FLOOR 341
#define CEIL 342
#define LOG 343
#define LOG10 344
#define STR 345
#define LPAREN 346
#define RPAREN 347
#define SLBRACE 348
#define SRBRACE 349
#define TRUE 350
#define FALSE 351
#define LEN 352
#define ASSGN 353
#define POW 354

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

#line 261 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
