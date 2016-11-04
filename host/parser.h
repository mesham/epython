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
    EPY_I_RANDOM = 283,
    EPY_I_REDUCE = 284,
    EPY_I_SUM = 285,
    EPY_I_MIN = 286,
    EPY_I_MAX = 287,
    EPY_I_PROD = 288,
    TOFROM = 289,
    NATIVE = 290,
    ADD = 291,
    SUB = 292,
    COLON = 293,
    DEF = 294,
    RET = 295,
    NONE = 296,
    FILESTART = 297,
    IN = 298,
    ADDADD = 299,
    SUBSUB = 300,
    MULMUL = 301,
    DIVDIV = 302,
    MODMOD = 303,
    POWPOW = 304,
    FLOORDIVFLOORDIV = 305,
    FLOORDIV = 306,
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
    IS = 318,
    NOT = 319,
    SQRT = 320,
    SIN = 321,
    COS = 322,
    TAN = 323,
    ASIN = 324,
    ACOS = 325,
    ATAN = 326,
    SINH = 327,
    COSH = 328,
    TANH = 329,
    FLOOR = 330,
    CEIL = 331,
    LOG = 332,
    LOG10 = 333,
    STR = 334,
    LPAREN = 335,
    RPAREN = 336,
    SLBRACE = 337,
    SRBRACE = 338,
    TRUE = 339,
    FALSE = 340,
    LEN = 341,
    EPY_I_ISHOST = 342,
    EPY_I_ISDEVICE = 343,
    ASSGN = 344,
    POW = 345
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
#define EPY_I_RANDOM 283
#define EPY_I_REDUCE 284
#define EPY_I_SUM 285
#define EPY_I_MIN 286
#define EPY_I_MAX 287
#define EPY_I_PROD 288
#define TOFROM 289
#define NATIVE 290
#define ADD 291
#define SUB 292
#define COLON 293
#define DEF 294
#define RET 295
#define NONE 296
#define FILESTART 297
#define IN 298
#define ADDADD 299
#define SUBSUB 300
#define MULMUL 301
#define DIVDIV 302
#define MODMOD 303
#define POWPOW 304
#define FLOORDIVFLOORDIV 305
#define FLOORDIV 306
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
#define IS 318
#define NOT 319
#define SQRT 320
#define SIN 321
#define COS 322
#define TAN 323
#define ASIN 324
#define ACOS 325
#define ATAN 326
#define SINH 327
#define COSH 328
#define TANH 329
#define FLOOR 330
#define CEIL 331
#define LOG 332
#define LOG10 333
#define STR 334
#define LPAREN 335
#define RPAREN 336
#define SLBRACE 337
#define SRBRACE 338
#define TRUE 339
#define FALSE 340
#define LEN 341
#define EPY_I_ISHOST 342
#define EPY_I_ISDEVICE 343
#define ASSGN 344
#define POW 345

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

#line 243 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
