/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

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
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     REAL = 259,
     STRING = 260,
     IDENTIFIER = 261,
     NEWLINE = 262,
     REM = 263,
     DIM = 264,
     SDIM = 265,
     LET = 266,
     STOP = 267,
     ENDIF = 268,
     ELSE = 269,
     COMMA = 270,
     FOR = 271,
     TO = 272,
     FROM = 273,
     NEXT = 274,
     INTO = 275,
     GOTO = 276,
     PRINT = 277,
     INPUT = 278,
     IF = 279,
     THEN = 280,
     COREID = 281,
     SEND = 282,
     RECV = 283,
     RANDOM = 284,
     SYNC = 285,
     BCAST = 286,
     REDUCE = 287,
     SUM = 288,
     MIN = 289,
     MAX = 290,
     PROD = 291,
     ADD = 292,
     SUB = 293,
     MULT = 294,
     DIV = 295,
     MOD = 296,
     AND = 297,
     OR = 298,
     NEQ = 299,
     LEQ = 300,
     GEQ = 301,
     LT = 302,
     GT = 303,
     EQ = 304,
     NOT = 305,
     SQRT = 306,
     SIN = 307,
     COS = 308,
     TAN = 309,
     ASIN = 310,
     ACOS = 311,
     ATAN = 312,
     SINH = 313,
     COSH = 314,
     TANH = 315,
     FLOOR = 316,
     CEIL = 317,
     LOG = 318,
     LOG10 = 319,
     LPAREN = 320,
     RPAREN = 321,
     SLBRACE = 322,
     SRBRACE = 323,
     POW = 324
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define REAL 259
#define STRING 260
#define IDENTIFIER 261
#define NEWLINE 262
#define REM 263
#define DIM 264
#define SDIM 265
#define LET 266
#define STOP 267
#define ENDIF 268
#define ELSE 269
#define COMMA 270
#define FOR 271
#define TO 272
#define FROM 273
#define NEXT 274
#define INTO 275
#define GOTO 276
#define PRINT 277
#define INPUT 278
#define IF 279
#define THEN 280
#define COREID 281
#define SEND 282
#define RECV 283
#define RANDOM 284
#define SYNC 285
#define BCAST 286
#define REDUCE 287
#define SUM 288
#define MIN 289
#define MAX 290
#define PROD 291
#define ADD 292
#define SUB 293
#define MULT 294
#define DIV 295
#define MOD 296
#define AND 297
#define OR 298
#define NEQ 299
#define LEQ 300
#define GEQ 301
#define LT 302
#define GT 303
#define EQ 304
#define NOT 305
#define SQRT 306
#define SIN 307
#define COS 308
#define TAN 309
#define ASIN 310
#define ACOS 311
#define ATAN 312
#define SINH 313
#define COSH 314
#define TANH 315
#define FLOOR 316
#define CEIL 317
#define LOG 318
#define LOG10 319
#define LPAREN 320
#define RPAREN 321
#define SLBRACE 322
#define SRBRACE 323
#define POW 324



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2053 of yacc.c  */
#line 19 "ebasic.y"

	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;


/* Line 2053 of yacc.c  */
#line 203 "parser.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_PARSER_H_INCLUDED  */
