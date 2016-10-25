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
    ADD = 296,
    SUB = 297,
    EPY_I_ISHOST = 298,
    EPY_I_DIMS = 299,
    EPY_I_DSIZE = 300,
    EPY_I_ISDEVICE = 301,
    COLON = 302,
    DEF = 303,
    RET = 304,
    NONE = 305,
    FILESTART = 306,
    IN = 307,
    ADDADD = 308,
    SUBSUB = 309,
    MULMUL = 310,
    DIVDIV = 311,
    MODMOD = 312,
    POWPOW = 313,
    FLOORDIVFLOORDIV = 314,
    FLOORDIV = 315,
    MULT = 316,
    DIV = 317,
    MOD = 318,
    AND = 319,
    OR = 320,
    NEQ = 321,
    LEQ = 322,
    GEQ = 323,
    LT = 324,
    GT = 325,
    EQ = 326,
    IS = 327,
    NOT = 328,
    SQRT = 329,
    SIN = 330,
    COS = 331,
    TAN = 332,
    ASIN = 333,
    ACOS = 334,
    ATAN = 335,
    SINH = 336,
    COSH = 337,
    TANH = 338,
    FLOOR = 339,
    CEIL = 340,
    LOG = 341,
    LOG10 = 342,
    STR = 343,
    LPAREN = 344,
    RPAREN = 345,
    SLBRACE = 346,
    SRBRACE = 347,
    TRUE = 348,
    FALSE = 349,
    LEN = 350,
    ASSGN = 351,
    POW = 352
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
#define ADD 296
#define SUB 297
#define EPY_I_ISHOST 298
#define EPY_I_DIMS 299
#define EPY_I_DSIZE 300
#define EPY_I_ISDEVICE 301
#define COLON 302
#define DEF 303
#define RET 304
#define NONE 305
#define FILESTART 306
#define IN 307
#define ADDADD 308
#define SUBSUB 309
#define MULMUL 310
#define DIVDIV 311
#define MODMOD 312
#define POWPOW 313
#define FLOORDIVFLOORDIV 314
#define FLOORDIV 315
#define MULT 316
#define DIV 317
#define MOD 318
#define AND 319
#define OR 320
#define NEQ 321
#define LEQ 322
#define GEQ 323
#define LT 324
#define GT 325
#define EQ 326
#define IS 327
#define NOT 328
#define SQRT 329
#define SIN 330
#define COS 331
#define TAN 332
#define ASIN 333
#define ACOS 334
#define ATAN 335
#define SINH 336
#define COSH 337
#define TANH 338
#define FLOOR 339
#define CEIL 340
#define LOG 341
#define LOG10 342
#define STR 343
#define LPAREN 344
#define RPAREN 345
#define SLBRACE 346
#define SRBRACE 347
#define TRUE 348
#define FALSE 349
#define LEN 350
#define ASSGN 351
#define POW 352

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

#line 257 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
