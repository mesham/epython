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
    GOTO = 276,
    PRINT = 277,
    INPUT = 278,
    IF = 279,
    NATIVE = 280,
    ADD = 281,
    SUB = 282,
    COLON = 283,
    DEF = 284,
    RET = 285,
    NONE = 286,
    FILESTART = 287,
    IN = 288,
    ADDADD = 289,
    SUBSUB = 290,
    MULMUL = 291,
    DIVDIV = 292,
    MODMOD = 293,
    POWPOW = 294,
    FLOORDIVFLOORDIV = 295,
    FLOORDIV = 296,
    MULT = 297,
    DIV = 298,
    MOD = 299,
    AND = 300,
    OR = 301,
    NEQ = 302,
    LEQ = 303,
    GEQ = 304,
    LT = 305,
    GT = 306,
    EQ = 307,
    IS = 308,
    NOT = 309,
    STR = 310,
    LPAREN = 311,
    RPAREN = 312,
    SLBRACE = 313,
    SRBRACE = 314,
    TRUE = 315,
    FALSE = 316,
    ASSGN = 317,
    POW = 318
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
#define GOTO 276
#define PRINT 277
#define INPUT 278
#define IF 279
#define NATIVE 280
#define ADD 281
#define SUB 282
#define COLON 283
#define DEF 284
#define RET 285
#define NONE 286
#define FILESTART 287
#define IN 288
#define ADDADD 289
#define SUBSUB 290
#define MULMUL 291
#define DIVDIV 292
#define MODMOD 293
#define POWPOW 294
#define FLOORDIVFLOORDIV 295
#define FLOORDIV 296
#define MULT 297
#define DIV 298
#define MOD 299
#define AND 300
#define OR 301
#define NEQ 302
#define LEQ 303
#define GEQ 304
#define LT 305
#define GT 306
#define EQ 307
#define IS 308
#define NOT 309
#define STR 310
#define LPAREN 311
#define RPAREN 312
#define SLBRACE 313
#define SRBRACE 314
#define TRUE 315
#define FALSE 316
#define ASSGN 317
#define POW 318

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

#line 189 "parser.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
