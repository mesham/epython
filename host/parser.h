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
    EPY_I_BCAST = 287,
    EPY_I_REDUCE = 288,
    EPY_I_SUM = 289,
    EPY_I_MIN = 290,
    EPY_I_MAX = 291,
    EPY_I_PROD = 292,
    EPY_I_SENDRECV = 293,
    TOFROM = 294,
    EPY_I_FREE = 295,
    NATIVE = 296,
    ADD = 297,
    SUB = 298,
    COLON = 299,
    DEF = 300,
    RET = 301,
    NONE = 302,
    FILESTART = 303,
    IN = 304,
    ADDADD = 305,
    SUBSUB = 306,
    MULMUL = 307,
    DIVDIV = 308,
    MODMOD = 309,
    POWPOW = 310,
    FLOORDIVFLOORDIV = 311,
    FLOORDIV = 312,
    MULT = 313,
    DIV = 314,
    MOD = 315,
    AND = 316,
    OR = 317,
    NEQ = 318,
    LEQ = 319,
    GEQ = 320,
    LT = 321,
    GT = 322,
    EQ = 323,
    IS = 324,
    NOT = 325,
    SQRT = 326,
    SIN = 327,
    COS = 328,
    TAN = 329,
    ASIN = 330,
    ACOS = 331,
    ATAN = 332,
    SINH = 333,
    COSH = 334,
    TANH = 335,
    FLOOR = 336,
    CEIL = 337,
    LOG = 338,
    LOG10 = 339,
    STR = 340,
    LPAREN = 341,
    RPAREN = 342,
    SLBRACE = 343,
    SRBRACE = 344,
    TRUE = 345,
    FALSE = 346,
    LEN = 347,
    EPY_I_ISHOST = 348,
    EPY_I_ISDEVICE = 349,
    ASSGN = 350,
    POW = 351
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
#define EPY_I_BCAST 287
#define EPY_I_REDUCE 288
#define EPY_I_SUM 289
#define EPY_I_MIN 290
#define EPY_I_MAX 291
#define EPY_I_PROD 292
#define EPY_I_SENDRECV 293
#define TOFROM 294
#define EPY_I_FREE 295
#define NATIVE 296
#define ADD 297
#define SUB 298
#define COLON 299
#define DEF 300
#define RET 301
#define NONE 302
#define FILESTART 303
#define IN 304
#define ADDADD 305
#define SUBSUB 306
#define MULMUL 307
#define DIVDIV 308
#define MODMOD 309
#define POWPOW 310
#define FLOORDIVFLOORDIV 311
#define FLOORDIV 312
#define MULT 313
#define DIV 314
#define MOD 315
#define AND 316
#define OR 317
#define NEQ 318
#define LEQ 319
#define GEQ 320
#define LT 321
#define GT 322
#define EQ 323
#define IS 324
#define NOT 325
#define SQRT 326
#define SIN 327
#define COS 328
#define TAN 329
#define ASIN 330
#define ACOS 331
#define ATAN 332
#define SINH 333
#define COSH 334
#define TANH 335
#define FLOOR 336
#define CEIL 337
#define LOG 338
#define LOG10 339
#define STR 340
#define LPAREN 341
#define RPAREN 342
#define SLBRACE 343
#define SRBRACE 344
#define TRUE 345
#define FALSE 346
#define LEN 347
#define EPY_I_ISHOST 348
#define EPY_I_ISDEVICE 349
#define ASSGN 350
#define POW 351

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

#line 255 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
