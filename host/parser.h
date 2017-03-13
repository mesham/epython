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
    AT = 273,
    FOR = 274,
    TO = 275,
    FROM = 276,
    NEXT = 277,
    GOTO = 278,
    PRINT = 279,
    INPUT = 280,
    IF = 281,
    NATIVE = 282,
    ADD = 283,
    SUB = 284,
    COLON = 285,
    DEF = 286,
    RET = 287,
    NONE = 288,
    FILESTART = 289,
    IN = 290,
    ADDADD = 291,
    SUBSUB = 292,
    MULMUL = 293,
    DIVDIV = 294,
    MODMOD = 295,
    POWPOW = 296,
    FLOORDIVFLOORDIV = 297,
    FLOORDIV = 298,
    MULT = 299,
    DIV = 300,
    MOD = 301,
    AND = 302,
    OR = 303,
    NEQ = 304,
    LEQ = 305,
    GEQ = 306,
    LT = 307,
    GT = 308,
    EQ = 309,
    IS = 310,
    NOT = 311,
    STR = 312,
    ID = 313,
    LPAREN = 314,
    RPAREN = 315,
    SLBRACE = 316,
    SRBRACE = 317,
    TRUE = 318,
    FALSE = 319,
    ASSGN = 320,
    POW = 321
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
#define AT 273
#define FOR 274
#define TO 275
#define FROM 276
#define NEXT 277
#define GOTO 278
#define PRINT 279
#define INPUT 280
#define IF 281
#define NATIVE 282
#define ADD 283
#define SUB 284
#define COLON 285
#define DEF 286
#define RET 287
#define NONE 288
#define FILESTART 289
#define IN 290
#define ADDADD 291
#define SUBSUB 292
#define MULMUL 293
#define DIVDIV 294
#define MODMOD 295
#define POWPOW 296
#define FLOORDIVFLOORDIV 297
#define FLOORDIV 298
#define MULT 299
#define DIV 300
#define MOD 301
#define AND 302
#define OR 303
#define NEQ 304
#define LEQ 305
#define GEQ 306
#define LT 307
#define GT 308
#define EQ 309
#define IS 310
#define NOT 311
#define STR 312
#define ID 313
#define LPAREN 314
#define RPAREN 315
#define SLBRACE 316
#define SRBRACE 317
#define TRUE 318
#define FALSE 319
#define ASSGN 320
#define POW 321

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "epython.y" /* yacc.c:1909  */

	int integer;
	unsigned char uchar;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 195 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
