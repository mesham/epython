/* A Bison parser, made by GNU Bison 2.7.12-4996.  */

/* Bison implementation for Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7.12-4996"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "ebasic.y"

#include "byteassembler.h"
#include "memorymanager.h"
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

extern int line_num;
void yyerror(char const*);
int yylex(void);

void yyerror (char const *msg) {
	fprintf(stderr, "%s at line %d\n", msg, line_num);
	exit(0);
}

/* Line 371 of yacc.c  */
#line 86 "parser.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
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
/* Line 387 of yacc.c  */
#line 19 "ebasic.y"

	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;


/* Line 387 of yacc.c  */
#line 287 "parser.c"
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

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 315 "parser.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif


/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   494

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  77
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  24
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNRULES -- Number of states.  */
#define YYNSTATES  199

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   330

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    76,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    13,    17,    19,    23,
      25,    30,    38,    43,    50,    60,    67,    73,    79,    85,
      94,   100,   103,   109,   117,   122,   125,   130,   135,   139,
     146,   149,   151,   153,   155,   157,   159,   161,   163,   165,
     167,   169,   171,   173,   175,   177,   180,   182,   186,   188,
     192,   194,   198,   202,   204,   208,   212,   216,   220,   222,
     226,   230,   232,   236,   240,   244,   248,   251,   254,   257,
     260,   263,   266,   269,   272,   275,   278,   281,   284,   287,
     290,   292,   296,   298,   303,   305,   307,   309,   311,   313,
     315,   318,   321,   323,   325
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      78,     0,    -1,    79,    -1,    80,    -1,    79,    80,    -1,
      81,     7,    -1,     3,    81,     7,    -1,     7,    -1,    82,
      76,    81,    -1,    82,    -1,    32,    98,    21,    90,    -1,
      32,    98,    73,    90,    74,    21,    90,    -1,    31,    90,
      20,    90,    -1,    41,    90,    42,    90,    23,    98,    -1,
      41,    90,    42,    90,    23,    98,    73,    90,    74,    -1,
      35,    90,    21,    90,    23,    98,    -1,    36,    83,    90,
      23,    98,    -1,     9,    98,    73,    90,    74,    -1,    10,
      98,    73,    90,    74,    -1,    19,    84,    55,    90,    20,
      90,    79,    22,    -1,    17,    87,    90,    79,    88,    -1,
      24,     3,    -1,    27,    90,    85,    79,    89,    -1,    27,
      90,    85,    79,    86,    79,    89,    -1,    27,    90,    28,
      81,    -1,    26,    98,    -1,    26,    99,    16,    98,    -1,
      11,    98,    55,    90,    -1,    98,    55,    90,    -1,    98,
      73,    90,    74,    55,    90,    -1,    25,    90,    -1,    12,
      -1,     8,    -1,    34,    -1,    37,    -1,    38,    -1,    39,
      -1,    40,    -1,    98,    -1,    28,    -1,    15,    -1,    18,
      -1,    14,    -1,    13,    -1,    91,    -1,    56,    91,    -1,
      92,    -1,    91,    49,    92,    -1,    93,    -1,    92,    48,
      93,    -1,    94,    -1,    93,    55,    94,    -1,    93,    50,
      94,    -1,    95,    -1,    94,    54,    95,    -1,    94,    53,
      95,    -1,    94,    51,    95,    -1,    94,    52,    95,    -1,
      96,    -1,    95,    43,    96,    -1,    95,    44,    96,    -1,
      97,    -1,    96,    45,    97,    -1,    96,    46,    97,    -1,
      96,    47,    97,    -1,    96,    75,    97,    -1,    57,    97,
      -1,    58,    97,    -1,    59,    97,    -1,    60,    97,    -1,
      61,    97,    -1,    62,    97,    -1,    63,    97,    -1,    64,
      97,    -1,    65,    97,    -1,    66,    97,    -1,    67,    97,
      -1,    68,    97,    -1,    69,    97,    -1,    70,    97,    -1,
      99,    -1,    71,    90,    72,    -1,    98,    -1,    98,    73,
      90,    74,    -1,     6,    -1,     3,    -1,     4,    -1,    29,
      -1,    30,    -1,    33,    -1,   100,     3,    -1,   100,     4,
      -1,     5,    -1,    43,    -1,    44,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    55,    55,    58,    59,    63,    64,    65,    69,    70,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,   101,   102,   103,   104,   108,   112,
     116,   120,   124,   127,   131,   132,   136,   137,   140,   141,
     145,   146,   147,   151,   152,   153,   154,   155,   159,   160,
     161,   165,   166,   167,   168,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     187,   188,   189,   190,   194,   198,   199,   200,   201,   202,
     203,   204,   205,   209,   210
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "STRING",
  "IDENTIFIER", "NEWLINE", "REM", "DIM", "SDIM", "LET", "STOP", "ENDIF",
  "ENDDO", "ELSE", "COMMA", "DO", "WHILE", "FOR", "TO", "FROM", "NEXT",
  "INTO", "GOTO", "PRINT", "INPUT", "IF", "THEN", "COREID", "NUMCORES",
  "SEND", "RECV", "RANDOM", "SYNC", "BCAST", "REDUCE", "SUM", "MIN", "MAX",
  "PROD", "SENDRECV", "TOFROM", "ADD", "SUB", "MULT", "DIV", "MOD", "AND",
  "OR", "NEQ", "LEQ", "GEQ", "LT", "GT", "EQ", "NOT", "SQRT", "SIN", "COS",
  "TAN", "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "FLOOR", "CEIL",
  "LOG", "LOG10", "LPAREN", "RPAREN", "SLBRACE", "SRBRACE", "POW", "':'",
  "$accept", "program", "lines", "line", "statements", "statement",
  "reductionop", "declareident", "openifblock", "elseifblock",
  "openwhileblock", "closedoblock", "closeifblock", "expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "value", "ident", "constant",
  "unary_operator", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,    58
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    77,    78,    79,    79,    80,    80,    80,    81,    81,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    83,    83,    83,    83,    84,    85,
      86,    87,    88,    89,    90,    90,    91,    91,    92,    92,
      93,    93,    93,    94,    94,    94,    94,    94,    95,    95,
      95,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    96,    96,
      97,    97,    97,    97,    98,    99,    99,    99,    99,    99,
      99,    99,    99,   100,   100
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     3,     1,     3,     1,
       4,     7,     4,     6,     9,     6,     5,     5,     5,     8,
       5,     2,     5,     7,     4,     2,     4,     4,     3,     6,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     3,     1,     3,
       1,     3,     3,     1,     3,     3,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       1,     3,     1,     4,     1,     1,     1,     1,     1,     1,
       2,     2,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    84,     7,    32,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,     0,     2,     3,     0,     9,     0,     0,     0,     0,
       0,    41,     0,     0,    38,    21,    85,    86,    92,    87,
      88,    89,    93,    94,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    44,    46,    48,    50,    53,    58,    61,    82,    80,
       0,    25,     0,     0,     0,     0,     0,    34,    35,    36,
      37,     0,     0,     1,     4,     5,     0,     0,     0,     6,
       0,     0,     0,     0,     0,    45,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    90,    91,     0,    39,
       0,     0,     0,     0,     0,     0,     0,     8,    28,     0,
       0,     0,    27,     0,     0,    81,    47,    49,    52,    51,
      56,    57,    55,    54,    59,    60,    62,    63,    64,    65,
       0,    26,    24,     0,    12,    10,     0,     0,     0,     0,
       0,    17,    18,    42,    20,     0,    83,    43,    40,     0,
      22,     0,     0,    16,     0,     0,     0,     0,     0,    15,
      13,    29,     0,    23,    11,     0,    19,     0,    14
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    21,    22,    23,    24,    25,    81,    33,   130,   179,
      32,   174,   180,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -90
static const yytype_int16 yypact[] =
{
     419,   453,   -90,   -90,   -90,     9,     9,     9,   -90,     3,
       9,    29,   161,   107,   161,   161,     9,   -90,   161,   -14,
     161,    40,   419,   -90,    35,   -33,   -53,    37,   -10,    -8,
       7,   -90,   161,    12,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   206,    31,    31,    31,    31,    31,
      31,    31,    31,    31,    31,    31,    31,    31,    31,   161,
     -90,    22,    36,   -38,    25,   -25,    23,   -90,    14,   -90,
       5,   -90,    57,    61,    65,    -7,    70,   -90,   -90,   -90,
     -90,   161,    50,   -90,   -90,   -90,   453,   161,   161,   -90,
     161,   161,   161,   419,   161,    22,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
      24,   206,   206,   206,   206,   206,   206,   206,   206,   206,
     206,    31,    31,    31,    31,   161,   -90,   -90,     9,   453,
     419,   161,   161,   161,   161,    72,   161,   -90,   -90,    32,
      34,    41,   -90,   311,    79,   -90,    36,   -38,    25,    25,
     -25,   -25,   -25,   -25,    23,    23,   -90,   -90,   -90,   -90,
      42,   -90,   -90,   275,   -90,   -90,    43,    86,     9,    91,
      63,   -90,   -90,   -90,   -90,   161,   -90,   -90,   -90,   419,
     -90,    98,     9,   -90,     9,   161,   419,   347,   161,   -90,
      47,   -90,   383,   -90,   -90,   161,   -90,    52,   -90
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -90,   -90,   -89,   -11,     2,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -66,    13,    83,    28,    21,   -84,   -35,   -81,
       1,     0,   121,   -90
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      26,    26,    87,    27,   143,    28,    29,    30,   126,   127,
      34,    84,   113,    71,   132,     2,    75,   114,   119,   120,
      88,    31,    26,    77,    78,    79,    80,    73,    74,   148,
     149,    76,    35,    82,    36,    37,    38,     2,   154,   155,
      83,   163,    85,    86,    89,    93,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
      39,    40,    92,    90,    41,    91,   133,    94,   121,   122,
     123,   111,   110,   128,    42,    43,   115,   116,   117,   118,
     150,   151,   152,   153,   112,   131,    26,   125,   137,   129,
     187,   134,   136,    26,   135,   168,   145,   192,   124,   175,
     138,   139,    59,   140,   141,   142,   170,   144,   171,   182,
      36,    37,    38,     2,   184,   172,   176,   181,   185,   188,
     195,   193,   156,   157,   158,   159,   198,    95,   161,    26,
      26,   162,    84,   147,    72,     0,    39,    40,   160,   146,
      41,     0,     0,    26,   164,   165,   166,   167,     0,   169,
      42,    43,    84,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    26,    36,    37,    38,     2,   183,     0,
       0,     0,     0,     0,     0,     0,    84,     0,     0,    26,
       0,    84,   189,     0,   190,     0,    26,    26,   186,     0,
      39,    40,    26,     0,    41,     0,     0,     0,   191,     0,
       0,   194,     0,     0,    42,    43,     0,     0,   197,    36,
      37,    38,     2,     0,     0,     0,     0,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,     0,     0,    39,    40,     0,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      43,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,     1,     0,
       0,     2,     3,     4,     5,     6,     7,     8,   177,     0,
     178,     0,     9,     0,    10,     0,     0,     0,     0,    11,
      12,    13,    14,     0,     0,     0,    15,    16,     0,    17,
      18,    19,     0,     0,     1,     0,    20,     2,     3,     4,
       5,     6,     7,     8,     0,   173,     0,     0,     9,     0,
      10,     0,     0,     0,     0,    11,    12,    13,    14,     0,
       0,     0,    15,    16,     0,    17,    18,    19,     0,     0,
       1,     0,    20,     2,     3,     4,     5,     6,     7,     8,
     177,     0,     0,     0,     9,     0,    10,     0,     0,     0,
       0,    11,    12,    13,    14,     0,     0,     0,    15,    16,
       0,    17,    18,    19,     0,     0,     1,     0,    20,     2,
       3,     4,     5,     6,     7,     8,     0,     0,     0,     0,
       9,     0,    10,     0,     0,   196,     0,    11,    12,    13,
      14,     0,     0,     0,    15,    16,     0,    17,    18,    19,
       0,     0,     1,     0,    20,     2,     3,     4,     5,     6,
       7,     8,     0,     0,     0,     0,     9,     0,    10,     0,
       0,     0,     0,    11,    12,    13,    14,     0,     0,     0,
      15,    16,     0,    17,    18,    19,     0,     0,     0,     2,
      20,     4,     5,     6,     7,     8,     0,     0,     0,     0,
       9,     0,    10,     0,     0,     0,     0,    11,    12,    13,
      14,     0,     0,     0,    15,    16,     0,    17,    18,    19,
       0,     0,     0,     0,    20
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-90)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
       0,     1,    55,     1,    93,     5,     6,     7,     3,     4,
      10,    22,    50,    13,    21,     6,    16,    55,    43,    44,
      73,    18,    22,    37,    38,    39,    40,    14,    15,   113,
     114,    18,     3,    20,     3,     4,     5,     6,   119,   120,
       0,   130,     7,    76,     7,    32,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      29,    30,    55,    73,    33,    73,    73,    55,    45,    46,
      47,    49,    59,    16,    43,    44,    51,    52,    53,    54,
     115,   116,   117,   118,    48,    20,    86,    73,    86,    28,
     179,    21,    42,    93,    81,    23,    72,   186,    75,    20,
      87,    88,    71,    90,    91,    92,    74,    94,    74,    23,
       3,     4,     5,     6,    23,    74,    74,    74,    55,    21,
      73,   187,   121,   122,   123,   124,    74,    44,   128,   129,
     130,   129,   143,   112,    13,    -1,    29,    30,   125,   111,
      33,    -1,    -1,   143,   131,   132,   133,   134,    -1,   136,
      43,    44,   163,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   163,     3,     4,     5,     6,   168,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   187,    -1,    -1,   179,
      -1,   192,   182,    -1,   184,    -1,   186,   187,   175,    -1,
      29,    30,   192,    -1,    33,    -1,    -1,    -1,   185,    -1,
      -1,   188,    -1,    -1,    43,    44,    -1,    -1,   195,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,    -1,    -1,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,     3,    -1,
      -1,     6,     7,     8,     9,    10,    11,    12,    13,    -1,
      15,    -1,    17,    -1,    19,    -1,    -1,    -1,    -1,    24,
      25,    26,    27,    -1,    -1,    -1,    31,    32,    -1,    34,
      35,    36,    -1,    -1,     3,    -1,    41,     6,     7,     8,
       9,    10,    11,    12,    -1,    14,    -1,    -1,    17,    -1,
      19,    -1,    -1,    -1,    -1,    24,    25,    26,    27,    -1,
      -1,    -1,    31,    32,    -1,    34,    35,    36,    -1,    -1,
       3,    -1,    41,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    -1,    17,    -1,    19,    -1,    -1,    -1,
      -1,    24,    25,    26,    27,    -1,    -1,    -1,    31,    32,
      -1,    34,    35,    36,    -1,    -1,     3,    -1,    41,     6,
       7,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      17,    -1,    19,    -1,    -1,    22,    -1,    24,    25,    26,
      27,    -1,    -1,    -1,    31,    32,    -1,    34,    35,    36,
      -1,    -1,     3,    -1,    41,     6,     7,     8,     9,    10,
      11,    12,    -1,    -1,    -1,    -1,    17,    -1,    19,    -1,
      -1,    -1,    -1,    24,    25,    26,    27,    -1,    -1,    -1,
      31,    32,    -1,    34,    35,    36,    -1,    -1,    -1,     6,
      41,     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,
      17,    -1,    19,    -1,    -1,    -1,    -1,    24,    25,    26,
      27,    -1,    -1,    -1,    31,    32,    -1,    34,    35,    36,
      -1,    -1,    -1,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     7,     8,     9,    10,    11,    12,    17,
      19,    24,    25,    26,    27,    31,    32,    34,    35,    36,
      41,    78,    79,    80,    81,    82,    98,    81,    98,    98,
      98,    18,    87,    84,    98,     3,     3,     4,     5,    29,
      30,    33,    43,    44,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,    98,    99,    90,    90,    98,    90,    37,    38,    39,
      40,    83,    90,     0,    80,     7,    76,    55,    73,     7,
      73,    73,    55,    90,    55,    91,    97,    97,    97,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      90,    49,    48,    50,    55,    51,    52,    53,    54,    43,
      44,    45,    46,    47,    75,    73,     3,     4,    16,    28,
      85,    20,    21,    73,    21,    90,    42,    81,    90,    90,
      90,    90,    90,    79,    90,    72,    92,    93,    94,    94,
      95,    95,    95,    95,    96,    96,    97,    97,    97,    97,
      90,    98,    81,    79,    90,    90,    90,    90,    23,    90,
      74,    74,    74,    14,    88,    20,    74,    13,    15,    86,
      89,    74,    23,    98,    23,    55,    90,    79,    21,    98,
      98,    90,    79,    89,    90,    73,    22,    90,    74
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YYUSE (yytype);
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1787 of yacc.c  */
#line 55 "ebasic.y"
    { compileMemory((yyvsp[(1) - (1)].data)); }
    break;

  case 4:
/* Line 1787 of yacc.c  */
#line 59 "ebasic.y"
    { (yyval.data)=concatenateMemory((yyvsp[(1) - (2)].data), (yyvsp[(2) - (2)].data)); }
    break;

  case 5:
/* Line 1787 of yacc.c  */
#line 63 "ebasic.y"
    { (yyval.data) = (yyvsp[(1) - (2)].data); }
    break;

  case 6:
/* Line 1787 of yacc.c  */
#line 64 "ebasic.y"
    { (yyval.data) = (yyvsp[(2) - (3)].data); setLineNumber((yyval.data), (yyvsp[(1) - (3)].integer)); }
    break;

  case 7:
/* Line 1787 of yacc.c  */
#line 65 "ebasic.y"
    { (yyval.data) = NULL; }
    break;

  case 10:
/* Line 1787 of yacc.c  */
#line 74 "ebasic.y"
    { (yyval.data)=appendRecvStatement((yyvsp[(2) - (4)].string), (yyvsp[(4) - (4)].data)); }
    break;

  case 11:
/* Line 1787 of yacc.c  */
#line 75 "ebasic.y"
    { (yyval.data)=appendRecvIntoArrayStatement((yyvsp[(2) - (7)].string), (yyvsp[(4) - (7)].data), (yyvsp[(7) - (7)].data)); }
    break;

  case 12:
/* Line 1787 of yacc.c  */
#line 76 "ebasic.y"
    { (yyval.data)=appendSendStatement((yyvsp[(2) - (4)].data), (yyvsp[(4) - (4)].data)); }
    break;

  case 13:
/* Line 1787 of yacc.c  */
#line 77 "ebasic.y"
    { (yyval.data)=appendSendRecvStatement((yyvsp[(2) - (6)].data), (yyvsp[(4) - (6)].data), (yyvsp[(6) - (6)].string)); }
    break;

  case 14:
/* Line 1787 of yacc.c  */
#line 78 "ebasic.y"
    { (yyval.data)=appendSendRecvStatementIntoArray((yyvsp[(2) - (9)].data), (yyvsp[(4) - (9)].data), (yyvsp[(6) - (9)].string), (yyvsp[(8) - (9)].data)); }
    break;

  case 15:
/* Line 1787 of yacc.c  */
#line 79 "ebasic.y"
    { (yyval.data)=appendBcastStatement((yyvsp[(2) - (6)].data), (yyvsp[(4) - (6)].data), (yyvsp[(6) - (6)].string)); }
    break;

  case 16:
/* Line 1787 of yacc.c  */
#line 80 "ebasic.y"
    { (yyval.data)=appendReductionStatement((yyvsp[(2) - (5)].integer), (yyvsp[(3) - (5)].data), (yyvsp[(5) - (5)].string)); }
    break;

  case 17:
/* Line 1787 of yacc.c  */
#line 81 "ebasic.y"
    { (yyval.data)=appendDeclareArray((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].data)); }
    break;

  case 18:
/* Line 1787 of yacc.c  */
#line 82 "ebasic.y"
    { (yyval.data)=appendDeclareSharedArray((yyvsp[(2) - (5)].string), (yyvsp[(4) - (5)].data)); }
    break;

  case 19:
/* Line 1787 of yacc.c  */
#line 83 "ebasic.y"
    { (yyval.data)=appendForStatement((yyvsp[(2) - (8)].string), (yyvsp[(4) - (8)].data), (yyvsp[(6) - (8)].data), (yyvsp[(7) - (8)].data)); leaveScope(); }
    break;

  case 20:
/* Line 1787 of yacc.c  */
#line 84 "ebasic.y"
    { (yyval.data)=appendDoWhileStatement((yyvsp[(3) - (5)].data), (yyvsp[(4) - (5)].data)); }
    break;

  case 21:
/* Line 1787 of yacc.c  */
#line 85 "ebasic.y"
    { (yyval.data)=appendGotoStatement((yyvsp[(2) - (2)].integer)); }
    break;

  case 22:
/* Line 1787 of yacc.c  */
#line 86 "ebasic.y"
    { (yyval.data)=appendIfStatement((yyvsp[(2) - (5)].data), (yyvsp[(4) - (5)].data)); }
    break;

  case 23:
/* Line 1787 of yacc.c  */
#line 87 "ebasic.y"
    { (yyval.data)=appendIfElseStatement((yyvsp[(2) - (7)].data), (yyvsp[(4) - (7)].data), (yyvsp[(6) - (7)].data)); }
    break;

  case 24:
/* Line 1787 of yacc.c  */
#line 88 "ebasic.y"
    { (yyval.data)=appendIfStatement((yyvsp[(2) - (4)].data), (yyvsp[(4) - (4)].data)); }
    break;

  case 25:
/* Line 1787 of yacc.c  */
#line 89 "ebasic.y"
    { (yyval.data)=appendInputStatement((yyvsp[(2) - (2)].string)); }
    break;

  case 26:
/* Line 1787 of yacc.c  */
#line 90 "ebasic.y"
    { (yyval.data)=appendInputStringStatement((yyvsp[(2) - (4)].data), (yyvsp[(4) - (4)].string)); }
    break;

  case 27:
/* Line 1787 of yacc.c  */
#line 91 "ebasic.y"
    { (yyval.data)=appendLetStatement((yyvsp[(2) - (4)].string), (yyvsp[(4) - (4)].data)); }
    break;

  case 28:
/* Line 1787 of yacc.c  */
#line 92 "ebasic.y"
    { (yyval.data)=appendLetStatement((yyvsp[(1) - (3)].string), (yyvsp[(3) - (3)].data)); }
    break;

  case 29:
/* Line 1787 of yacc.c  */
#line 93 "ebasic.y"
    { (yyval.data)=appendArraySetStatement((yyvsp[(1) - (6)].string), (yyvsp[(3) - (6)].data), (yyvsp[(6) - (6)].data)); }
    break;

  case 30:
/* Line 1787 of yacc.c  */
#line 94 "ebasic.y"
    { (yyval.data)=appendPrintStatement((yyvsp[(2) - (2)].data)); }
    break;

  case 31:
/* Line 1787 of yacc.c  */
#line 95 "ebasic.y"
    { (yyval.data)=appendStopStatement(); }
    break;

  case 32:
/* Line 1787 of yacc.c  */
#line 96 "ebasic.y"
    { (yyval.data) = NULL; }
    break;

  case 33:
/* Line 1787 of yacc.c  */
#line 97 "ebasic.y"
    { (yyval.data)=appendSyncStatement(); }
    break;

  case 34:
/* Line 1787 of yacc.c  */
#line 101 "ebasic.y"
    { (yyval.integer)=0; }
    break;

  case 35:
/* Line 1787 of yacc.c  */
#line 102 "ebasic.y"
    { (yyval.integer)=1; }
    break;

  case 36:
/* Line 1787 of yacc.c  */
#line 103 "ebasic.y"
    { (yyval.integer)=2; }
    break;

  case 37:
/* Line 1787 of yacc.c  */
#line 104 "ebasic.y"
    { (yyval.integer)=3; }
    break;

  case 38:
/* Line 1787 of yacc.c  */
#line 108 "ebasic.y"
    { (yyval.string)=(yyvsp[(1) - (1)].string); enterScope(); addVariableIfNeeded((yyvsp[(1) - (1)].string)); }
    break;

  case 39:
/* Line 1787 of yacc.c  */
#line 112 "ebasic.y"
    { enterScope(); }
    break;

  case 40:
/* Line 1787 of yacc.c  */
#line 116 "ebasic.y"
    { leaveScope(); enterScope(); }
    break;

  case 41:
/* Line 1787 of yacc.c  */
#line 120 "ebasic.y"
    { enterScope(); }
    break;

  case 42:
/* Line 1787 of yacc.c  */
#line 124 "ebasic.y"
    { leaveScope(); }
    break;

  case 43:
/* Line 1787 of yacc.c  */
#line 127 "ebasic.y"
    { leaveScope(); }
    break;

  case 44:
/* Line 1787 of yacc.c  */
#line 131 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 45:
/* Line 1787 of yacc.c  */
#line 132 "ebasic.y"
    { (yyval.data)=(yyvsp[(2) - (2)].data); }
    break;

  case 46:
/* Line 1787 of yacc.c  */
#line 136 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 47:
/* Line 1787 of yacc.c  */
#line 137 "ebasic.y"
    { (yyval.data)=createOrExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 48:
/* Line 1787 of yacc.c  */
#line 140 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 49:
/* Line 1787 of yacc.c  */
#line 141 "ebasic.y"
    { (yyval.data)=createAndExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 50:
/* Line 1787 of yacc.c  */
#line 145 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 51:
/* Line 1787 of yacc.c  */
#line 146 "ebasic.y"
    { (yyval.data)=createEqExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 52:
/* Line 1787 of yacc.c  */
#line 147 "ebasic.y"
    { (yyval.data)=createNeqExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 53:
/* Line 1787 of yacc.c  */
#line 151 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 54:
/* Line 1787 of yacc.c  */
#line 152 "ebasic.y"
    { (yyval.data)=createGtExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 55:
/* Line 1787 of yacc.c  */
#line 153 "ebasic.y"
    { (yyval.data)=createLtExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 56:
/* Line 1787 of yacc.c  */
#line 154 "ebasic.y"
    { (yyval.data)=createLeqExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 57:
/* Line 1787 of yacc.c  */
#line 155 "ebasic.y"
    { (yyval.data)=createGeqExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 58:
/* Line 1787 of yacc.c  */
#line 159 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 59:
/* Line 1787 of yacc.c  */
#line 160 "ebasic.y"
    { (yyval.data)=createAddExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 60:
/* Line 1787 of yacc.c  */
#line 161 "ebasic.y"
    { (yyval.data)=createSubExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 61:
/* Line 1787 of yacc.c  */
#line 165 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 62:
/* Line 1787 of yacc.c  */
#line 166 "ebasic.y"
    { (yyval.data)=createMulExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 63:
/* Line 1787 of yacc.c  */
#line 167 "ebasic.y"
    { (yyval.data)=createDivExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 64:
/* Line 1787 of yacc.c  */
#line 168 "ebasic.y"
    { (yyval.data)=createModExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 65:
/* Line 1787 of yacc.c  */
#line 169 "ebasic.y"
    { (yyval.data)=createPowExpression((yyvsp[(1) - (3)].data), (yyvsp[(3) - (3)].data)); }
    break;

  case 66:
/* Line 1787 of yacc.c  */
#line 170 "ebasic.y"
    { (yyval.data)=createSqrtExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 67:
/* Line 1787 of yacc.c  */
#line 171 "ebasic.y"
    { (yyval.data)=createSinExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 68:
/* Line 1787 of yacc.c  */
#line 172 "ebasic.y"
    { (yyval.data)=createCosExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 69:
/* Line 1787 of yacc.c  */
#line 173 "ebasic.y"
    { (yyval.data)=createTanExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 70:
/* Line 1787 of yacc.c  */
#line 174 "ebasic.y"
    { (yyval.data)=createASinExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 71:
/* Line 1787 of yacc.c  */
#line 175 "ebasic.y"
    { (yyval.data)=createACosExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 72:
/* Line 1787 of yacc.c  */
#line 176 "ebasic.y"
    { (yyval.data)=createATanExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 73:
/* Line 1787 of yacc.c  */
#line 177 "ebasic.y"
    { (yyval.data)=createSinHExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 74:
/* Line 1787 of yacc.c  */
#line 178 "ebasic.y"
    { (yyval.data)=createCosHExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 75:
/* Line 1787 of yacc.c  */
#line 179 "ebasic.y"
    { (yyval.data)=createTanHExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 76:
/* Line 1787 of yacc.c  */
#line 180 "ebasic.y"
    { (yyval.data)=createFloorExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 77:
/* Line 1787 of yacc.c  */
#line 181 "ebasic.y"
    { (yyval.data)=createCeilExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 78:
/* Line 1787 of yacc.c  */
#line 182 "ebasic.y"
    { (yyval.data)=createLogExpression((yyvsp[(2) - (2)].data)); }
    break;

  case 79:
/* Line 1787 of yacc.c  */
#line 183 "ebasic.y"
    { (yyval.data)=createLog10Expression((yyvsp[(2) - (2)].data)); }
    break;

  case 80:
/* Line 1787 of yacc.c  */
#line 187 "ebasic.y"
    { (yyval.data)=(yyvsp[(1) - (1)].data); }
    break;

  case 81:
/* Line 1787 of yacc.c  */
#line 188 "ebasic.y"
    { (yyval.data)=(yyvsp[(2) - (3)].data); }
    break;

  case 82:
/* Line 1787 of yacc.c  */
#line 189 "ebasic.y"
    { (yyval.data)=createIdentifierExpression((yyvsp[(1) - (1)].string)); }
    break;

  case 83:
/* Line 1787 of yacc.c  */
#line 190 "ebasic.y"
    { (yyval.data)=createIdentifierArrayAccessExpression((yyvsp[(1) - (4)].string), (yyvsp[(3) - (4)].data)); }
    break;

  case 84:
/* Line 1787 of yacc.c  */
#line 194 "ebasic.y"
    { (yyval.string) = malloc(strlen((yyvsp[(1) - (1)].string))+1); strcpy((yyval.string), (yyvsp[(1) - (1)].string)); }
    break;

  case 85:
/* Line 1787 of yacc.c  */
#line 198 "ebasic.y"
    { (yyval.data)=createIntegerExpression((yyvsp[(1) - (1)].integer)); }
    break;

  case 86:
/* Line 1787 of yacc.c  */
#line 199 "ebasic.y"
    { (yyval.data)=createRealExpression((yyvsp[(1) - (1)].real)); }
    break;

  case 87:
/* Line 1787 of yacc.c  */
#line 200 "ebasic.y"
    { (yyval.data)=createCoreIdExpression(); }
    break;

  case 88:
/* Line 1787 of yacc.c  */
#line 201 "ebasic.y"
    { (yyval.data)=createNumCoresExpression(); }
    break;

  case 89:
/* Line 1787 of yacc.c  */
#line 202 "ebasic.y"
    { (yyval.data)=createRandomExpression(); }
    break;

  case 90:
/* Line 1787 of yacc.c  */
#line 203 "ebasic.y"
    { (yyval.data)=createIntegerExpression((yyvsp[(1) - (2)].integer) * (yyvsp[(2) - (2)].integer)); }
    break;

  case 91:
/* Line 1787 of yacc.c  */
#line 204 "ebasic.y"
    { (yyval.data)=createRealExpression((yyvsp[(1) - (2)].integer) * (yyvsp[(2) - (2)].real)); }
    break;

  case 92:
/* Line 1787 of yacc.c  */
#line 205 "ebasic.y"
    { (yyval.data)=createStringExpression((yyvsp[(1) - (1)].string)); }
    break;

  case 93:
/* Line 1787 of yacc.c  */
#line 209 "ebasic.y"
    { (yyval.integer) = 1; }
    break;

  case 94:
/* Line 1787 of yacc.c  */
#line 210 "ebasic.y"
    { (yyval.integer) = -1; }
    break;


/* Line 1787 of yacc.c  */
#line 2286 "parser.c"
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2050 of yacc.c  */
#line 213 "ebasic.y"

