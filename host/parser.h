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
    TOFROM = 282,
    NATIVE = 283,
    ADD = 284,
    SUB = 285,
    COLON = 286,
    DEF = 287,
    RET = 288,
    NONE = 289,
    FILESTART = 290,
    IN = 291,
    ADDADD = 292,
    SUBSUB = 293,
    MULMUL = 294,
    DIVDIV = 295,
    MODMOD = 296,
    POWPOW = 297,
    FLOORDIVFLOORDIV = 298,
    FLOORDIV = 299,
    MULT = 300,
    DIV = 301,
    MOD = 302,
    AND = 303,
    OR = 304,
    NEQ = 305,
    LEQ = 306,
    GEQ = 307,
    LT = 308,
    GT = 309,
    EQ = 310,
    IS = 311,
    NOT = 312,
    SQRT = 313,
    SIN = 314,
    COS = 315,
    TAN = 316,
    ASIN = 317,
    ACOS = 318,
    ATAN = 319,
    SINH = 320,
    COSH = 321,
    TANH = 322,
    FLOOR = 323,
    CEIL = 324,
    LOG = 325,
    LOG10 = 326,
    STR = 327,
    LPAREN = 328,
    RPAREN = 329,
    SLBRACE = 330,
    SRBRACE = 331,
    TRUE = 332,
    FALSE = 333,
    LEN = 334,
    EPY_I_ISHOST = 335,
    EPY_I_ISDEVICE = 336,
    ASSGN = 337,
    POW = 338
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
#define TOFROM 282
#define NATIVE 283
#define ADD 284
#define SUB 285
#define COLON 286
#define DEF 287
#define RET 288
#define NONE 289
#define FILESTART 290
#define IN 291
#define ADDADD 292
#define SUBSUB 293
#define MULMUL 294
#define DIVDIV 295
#define MODMOD 296
#define POWPOW 297
#define FLOORDIVFLOORDIV 298
#define FLOORDIV 299
#define MULT 300
#define DIV 301
#define MOD 302
#define AND 303
#define OR 304
#define NEQ 305
#define LEQ 306
#define GEQ 307
#define LT 308
#define GT 309
#define EQ 310
#define IS 311
#define NOT 312
#define SQRT 313
#define SIN 314
#define COS 315
#define TAN 316
#define ASIN 317
#define ACOS 318
#define ATAN 319
#define SINH 320
#define COSH 321
#define TANH 322
#define FLOOR 323
#define CEIL 324
#define LOG 325
#define LOG10 326
#define STR 327
#define LPAREN 328
#define RPAREN 329
#define SLBRACE 330
#define SRBRACE 331
#define TRUE 332
#define FALSE 333
#define LEN 334
#define EPY_I_ISHOST 335
#define EPY_I_ISDEVICE 336
#define ASSGN 337
#define POW 338

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

#line 229 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
