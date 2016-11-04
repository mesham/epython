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
    EPY_I_REDUCE = 285,
    EPY_I_SUM = 286,
    EPY_I_MIN = 287,
    EPY_I_MAX = 288,
    EPY_I_PROD = 289,
    TOFROM = 290,
    NATIVE = 291,
    ADD = 292,
    SUB = 293,
    COLON = 294,
    DEF = 295,
    RET = 296,
    NONE = 297,
    FILESTART = 298,
    IN = 299,
    ADDADD = 300,
    SUBSUB = 301,
    MULMUL = 302,
    DIVDIV = 303,
    MODMOD = 304,
    POWPOW = 305,
    FLOORDIVFLOORDIV = 306,
    FLOORDIV = 307,
    MULT = 308,
    DIV = 309,
    MOD = 310,
    AND = 311,
    OR = 312,
    NEQ = 313,
    LEQ = 314,
    GEQ = 315,
    LT = 316,
    GT = 317,
    EQ = 318,
    IS = 319,
    NOT = 320,
    SQRT = 321,
    SIN = 322,
    COS = 323,
    TAN = 324,
    ASIN = 325,
    ACOS = 326,
    ATAN = 327,
    SINH = 328,
    COSH = 329,
    TANH = 330,
    FLOOR = 331,
    CEIL = 332,
    LOG = 333,
    LOG10 = 334,
    STR = 335,
    LPAREN = 336,
    RPAREN = 337,
    SLBRACE = 338,
    SRBRACE = 339,
    TRUE = 340,
    FALSE = 341,
    LEN = 342,
    EPY_I_ISHOST = 343,
    EPY_I_ISDEVICE = 344,
    ASSGN = 345,
    POW = 346
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
#define EPY_I_REDUCE 285
#define EPY_I_SUM 286
#define EPY_I_MIN 287
#define EPY_I_MAX 288
#define EPY_I_PROD 289
#define TOFROM 290
#define NATIVE 291
#define ADD 292
#define SUB 293
#define COLON 294
#define DEF 295
#define RET 296
#define NONE 297
#define FILESTART 298
#define IN 299
#define ADDADD 300
#define SUBSUB 301
#define MULMUL 302
#define DIVDIV 303
#define MODMOD 304
#define POWPOW 305
#define FLOORDIVFLOORDIV 306
#define FLOORDIV 307
#define MULT 308
#define DIV 309
#define MOD 310
#define AND 311
#define OR 312
#define NEQ 313
#define LEQ 314
#define GEQ 315
#define LT 316
#define GT 317
#define EQ 318
#define IS 319
#define NOT 320
#define SQRT 321
#define SIN 322
#define COS 323
#define TAN 324
#define ASIN 325
#define ACOS 326
#define ATAN 327
#define SINH 328
#define COSH 329
#define TANH 330
#define FLOOR 331
#define CEIL 332
#define LOG 333
#define LOG10 334
#define STR 335
#define LPAREN 336
#define RPAREN 337
#define SLBRACE 338
#define SRBRACE 339
#define TRUE 340
#define FALSE 341
#define LEN 342
#define EPY_I_ISHOST 343
#define EPY_I_ISDEVICE 344
#define ASSGN 345
#define POW 346

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

#line 245 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
