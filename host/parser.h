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
    ADD = 297,
    SUB = 298,
    EPY_I_ISHOST = 299,
    EPY_I_DIMS = 300,
    EPY_I_DSIZE = 301,
    EPY_I_ISDEVICE = 302,
    COLON = 303,
    DEF = 304,
    RET = 305,
    NONE = 306,
    FILESTART = 307,
    IN = 308,
    ADDADD = 309,
    SUBSUB = 310,
    MULMUL = 311,
    DIVDIV = 312,
    MODMOD = 313,
    POWPOW = 314,
    FLOORDIVFLOORDIV = 315,
    FLOORDIV = 316,
    MULT = 317,
    DIV = 318,
    MOD = 319,
    AND = 320,
    OR = 321,
    NEQ = 322,
    LEQ = 323,
    GEQ = 324,
    LT = 325,
    GT = 326,
    EQ = 327,
    IS = 328,
    NOT = 329,
    SQRT = 330,
    SIN = 331,
    COS = 332,
    TAN = 333,
    ASIN = 334,
    ACOS = 335,
    ATAN = 336,
    SINH = 337,
    COSH = 338,
    TANH = 339,
    FLOOR = 340,
    CEIL = 341,
    LOG = 342,
    LOG10 = 343,
    STR = 344,
    LPAREN = 345,
    RPAREN = 346,
    SLBRACE = 347,
    SRBRACE = 348,
    TRUE = 349,
    FALSE = 350,
    LEN = 351,
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
#define ADD 297
#define SUB 298
#define EPY_I_ISHOST 299
#define EPY_I_DIMS 300
#define EPY_I_DSIZE 301
#define EPY_I_ISDEVICE 302
#define COLON 303
#define DEF 304
#define RET 305
#define NONE 306
#define FILESTART 307
#define IN 308
#define ADDADD 309
#define SUBSUB 310
#define MULMUL 311
#define DIVDIV 312
#define MODMOD 313
#define POWPOW 314
#define FLOORDIVFLOORDIV 315
#define FLOORDIV 316
#define MULT 317
#define DIV 318
#define MOD 319
#define AND 320
#define OR 321
#define NEQ 322
#define LEQ 323
#define GEQ 324
#define LT 325
#define GT 326
#define EQ 327
#define IS 328
#define NOT 329
#define SQRT 330
#define SIN 331
#define COS 332
#define TAN 333
#define ASIN 334
#define ACOS 335
#define ATAN 336
#define SINH 337
#define COSH 338
#define TANH 339
#define FLOOR 340
#define CEIL 341
#define LOG 342
#define LOG10 343
#define STR 344
#define LPAREN 345
#define RPAREN 346
#define SLBRACE 347
#define SRBRACE 348
#define TRUE 349
#define FALSE 350
#define LEN 351
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
