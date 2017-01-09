/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    PASS = 272,
    FOR = 273,
    TO = 274,
    FROM = 275,
    NEXT = 276,
    GOTO = 277,
    PRINT = 278,
    INPUT = 279,
    IF = 280,
    NATIVE = 281,
    ADD = 282,
    SUB = 283,
    COLON = 284,
    DEF = 285,
    RET = 286,
    NONE = 287,
    FILESTART = 288,
    IN = 289,
    ADDADD = 290,
    SUBSUB = 291,
    MULMUL = 292,
    DIVDIV = 293,
    MODMOD = 294,
    POWPOW = 295,
    FLOORDIVFLOORDIV = 296,
    FLOORDIV = 297,
    MULT = 298,
    DIV = 299,
    MOD = 300,
    AND = 301,
    OR = 302,
    NEQ = 303,
    LEQ = 304,
    GEQ = 305,
    LT = 306,
    GT = 307,
    EQ = 308,
    IS = 309,
    NOT = 310,
    STR = 311,
    ID = 312,
    LPAREN = 313,
    RPAREN = 314,
    SLBRACE = 315,
    SRBRACE = 316,
    TRUE = 317,
    FALSE = 318,
    ASSGN = 319,
    POW = 320
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
#define PASS 272
#define FOR 273
#define TO 274
#define FROM 275
#define NEXT 276
#define GOTO 277
#define PRINT 278
#define INPUT 279
#define IF 280
#define NATIVE 281
#define ADD 282
#define SUB 283
#define COLON 284
#define DEF 285
#define RET 286
#define NONE 287
#define FILESTART 288
#define IN 289
#define ADDADD 290
#define SUBSUB 291
#define MULMUL 292
#define DIVDIV 293
#define MODMOD 294
#define POWPOW 295
#define FLOORDIVFLOORDIV 296
#define FLOORDIV 297
#define MULT 298
#define DIV 299
#define MOD 300
#define AND 301
#define OR 302
#define NEQ 303
#define LEQ 304
#define GEQ 305
#define LT 306
#define GT 307
#define EQ 308
#define IS 309
#define NOT 310
#define STR 311
#define ID 312
#define LPAREN 313
#define RPAREN 314
#define SLBRACE 315
#define SRBRACE 316
#define TRUE 317
#define FALSE 318
#define ASSGN 319
#define POW 320

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 21 "epython.y" /* yacc.c:1909  */

	int integer;
	unsigned char uchar;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 193 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
