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
     ENDDO = 269,
     ELSE = 270,
     COMMA = 271,
     DO = 272,
     WHILE = 273,
     FOR = 274,
     TO = 275,
     FROM = 276,
     NEXT = 277,
     INTO = 278,
     GOTO = 279,
     PRINT = 280,
     INPUT = 281,
     IF = 282,
     THEN = 283,
     COREID = 284,
     NUMCORES = 285,
     SEND = 286,
     RECV = 287,
     RANDOM = 288,
     SYNC = 289,
     BCAST = 290,
     REDUCE = 291,
     SUM = 292,
     MIN = 293,
     MAX = 294,
     PROD = 295,
     SENDRECV = 296,
     TOFROM = 297,
     ADD = 298,
     SUB = 299,
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
     NOT = 311,
     SQRT = 312,
     SIN = 313,
     COS = 314,
     TAN = 315,
     ASIN = 316,
     ACOS = 317,
     ATAN = 318,
     SINH = 319,
     COSH = 320,
     TANH = 321,
     FLOOR = 322,
     CEIL = 323,
     LOG = 324,
     LOG10 = 325,
     LPAREN = 326,
     RPAREN = 327,
     SLBRACE = 328,
     SRBRACE = 329,
     POW = 330
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
#define ENDDO 269
#define ELSE 270
#define COMMA 271
#define DO 272
#define WHILE 273
#define FOR 274
#define TO 275
#define FROM 276
#define NEXT 277
#define INTO 278
#define GOTO 279
#define PRINT 280
#define INPUT 281
#define IF 282
#define THEN 283
#define COREID 284
#define NUMCORES 285
#define SEND 286
#define RECV 287
#define RANDOM 288
#define SYNC 289
#define BCAST 290
#define REDUCE 291
#define SUM 292
#define MIN 293
#define MAX 294
#define PROD 295
#define SENDRECV 296
#define TOFROM 297
#define ADD 298
#define SUB 299
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
#define NOT 311
#define SQRT 312
#define SIN 313
#define COS 314
#define TAN 315
#define ASIN 316
#define ACOS 317
#define ATAN 318
#define SINH 319
#define COSH 320
#define TANH 321
#define FLOOR 322
#define CEIL 323
#define LOG 324
#define LOG10 325
#define LPAREN 326
#define RPAREN 327
#define SLBRACE 328
#define SRBRACE 329
#define POW 330



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
#line 215 "parser.h"
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
