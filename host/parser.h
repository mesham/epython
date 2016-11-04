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
    TOFROM = 291,
    NATIVE = 292,
    ADD = 293,
    SUB = 294,
    COLON = 295,
    DEF = 296,
    RET = 297,
    NONE = 298,
    FILESTART = 299,
    IN = 300,
    ADDADD = 301,
    SUBSUB = 302,
    MULMUL = 303,
    DIVDIV = 304,
    MODMOD = 305,
    POWPOW = 306,
    FLOORDIVFLOORDIV = 307,
    FLOORDIV = 308,
    MULT = 309,
    DIV = 310,
    MOD = 311,
    AND = 312,
    OR = 313,
    NEQ = 314,
    LEQ = 315,
    GEQ = 316,
    LT = 317,
    GT = 318,
    EQ = 319,
    IS = 320,
    NOT = 321,
    SQRT = 322,
    SIN = 323,
    COS = 324,
    TAN = 325,
    ASIN = 326,
    ACOS = 327,
    ATAN = 328,
    SINH = 329,
    COSH = 330,
    TANH = 331,
    FLOOR = 332,
    CEIL = 333,
    LOG = 334,
    LOG10 = 335,
    STR = 336,
    LPAREN = 337,
    RPAREN = 338,
    SLBRACE = 339,
    SRBRACE = 340,
    TRUE = 341,
    FALSE = 342,
    LEN = 343,
    EPY_I_ISHOST = 344,
    EPY_I_ISDEVICE = 345,
    ASSGN = 346,
    POW = 347
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
#define TOFROM 291
#define NATIVE 292
#define ADD 293
#define SUB 294
#define COLON 295
#define DEF 296
#define RET 297
#define NONE 298
#define FILESTART 299
#define IN 300
#define ADDADD 301
#define SUBSUB 302
#define MULMUL 303
#define DIVDIV 304
#define MODMOD 305
#define POWPOW 306
#define FLOORDIVFLOORDIV 307
#define FLOORDIV 308
#define MULT 309
#define DIV 310
#define MOD 311
#define AND 312
#define OR 313
#define NEQ 314
#define LEQ 315
#define GEQ 316
#define LT 317
#define GT 318
#define EQ 319
#define IS 320
#define NOT 321
#define SQRT 322
#define SIN 323
#define COS 324
#define TAN 325
#define ASIN 326
#define ACOS 327
#define ATAN 328
#define SINH 329
#define COSH 330
#define TANH 331
#define FLOOR 332
#define CEIL 333
#define LOG 334
#define LOG10 335
#define STR 336
#define LPAREN 337
#define RPAREN 338
#define SLBRACE 339
#define SRBRACE 340
#define TRUE 341
#define FALSE 342
#define LEN 343
#define EPY_I_ISHOST 344
#define EPY_I_ISDEVICE 345
#define ASSGN 346
#define POW 347

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

#line 247 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
