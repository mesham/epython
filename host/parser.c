/* A Bison parser, made by GNU Bison 3.0.2.  */

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "epython.y" /* yacc.c:339  */

#include "byteassembler.h"
#include "memorymanager.h"
#include "stack.h"
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

#line 85 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
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
    REM = 265,
    DIM = 266,
    SDIM = 267,
    LET = 268,
    STOP = 269,
    ELSE = 270,
    COMMA = 271,
    WHILE = 272,
    FOR = 273,
    TO = 274,
    FROM = 275,
    NEXT = 276,
    INTO = 277,
    GOTO = 278,
    PRINT = 279,
    INPUT = 280,
    IF = 281,
    THEN = 282,
    COREID = 283,
    NUMCORES = 284,
    SEND = 285,
    RECV = 286,
    RANDOM = 287,
    SYNC = 288,
    BCAST = 289,
    REDUCE = 290,
    SUM = 291,
    MIN = 292,
    MAX = 293,
    PROD = 294,
    SENDRECV = 295,
    TOFROM = 296,
    ADD = 297,
    SUB = 298,
    ISHOST = 299,
    ISDEVICE = 300,
    COLON = 301,
    DEF = 302,
    RET = 303,
    MULT = 304,
    DIV = 305,
    MOD = 306,
    AND = 307,
    OR = 308,
    NEQ = 309,
    LEQ = 310,
    GEQ = 311,
    LT = 312,
    GT = 313,
    EQ = 314,
    NOT = 315,
    SQRT = 316,
    SIN = 317,
    COS = 318,
    TAN = 319,
    ASIN = 320,
    ACOS = 321,
    ATAN = 322,
    SINH = 323,
    COSH = 324,
    TANH = 325,
    FLOOR = 326,
    CEIL = 327,
    LOG = 328,
    LOG10 = 329,
    LPAREN = 330,
    RPAREN = 331,
    SLBRACE = 332,
    SRBRACE = 333,
    ASSGN = 334,
    POW = 335
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
#define REM 265
#define DIM 266
#define SDIM 267
#define LET 268
#define STOP 269
#define ELSE 270
#define COMMA 271
#define WHILE 272
#define FOR 273
#define TO 274
#define FROM 275
#define NEXT 276
#define INTO 277
#define GOTO 278
#define PRINT 279
#define INPUT 280
#define IF 281
#define THEN 282
#define COREID 283
#define NUMCORES 284
#define SEND 285
#define RECV 286
#define RANDOM 287
#define SYNC 288
#define BCAST 289
#define REDUCE 290
#define SUM 291
#define MIN 292
#define MAX 293
#define PROD 294
#define SENDRECV 295
#define TOFROM 296
#define ADD 297
#define SUB 298
#define ISHOST 299
#define ISDEVICE 300
#define COLON 301
#define DEF 302
#define RET 303
#define MULT 304
#define DIV 305
#define MOD 306
#define AND 307
#define OR 308
#define NEQ 309
#define LEQ 310
#define GEQ 311
#define LT 312
#define GT 313
#define EQ 314
#define NOT 315
#define SQRT 316
#define SIN 317
#define COS 318
#define TAN 319
#define ASIN 320
#define ACOS 321
#define ATAN 322
#define SINH 323
#define COSH 324
#define TANH 325
#define FLOOR 326
#define CEIL 327
#define LOG 328
#define LOG10 329
#define LPAREN 330
#define RPAREN 331
#define SLBRACE 332
#define SRBRACE 333
#define ASSGN 334
#define POW 335

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 20 "epython.y" /* yacc.c:355  */

	int integer;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 293 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 308 "parser.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
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
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  87
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   537

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  81
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  217

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   335

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      75,    76,    77,    78,    79,    80
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    58,    58,    61,    62,    66,    67,    68,    69,    73,
      74,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
      97,    98,    99,   100,   101,   102,   103,   104,   108,   109,
     110,   114,   115,   116,   120,   123,   126,   129,   130,   131,
     132,   136,   140,   144,   145,   149,   150,   153,   154,   158,
     159,   160,   161,   162,   166,   167,   168,   169,   170,   174,
     175,   176,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   202,   203,   204,   205,   209,   213,   214,   215,   216,
     217,   218,   219,   220,   224,   225
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "STRING",
  "IDENTIFIER", "NEWLINE", "INDENT", "OUTDENT", "REM", "DIM", "SDIM",
  "LET", "STOP", "ELSE", "COMMA", "WHILE", "FOR", "TO", "FROM", "NEXT",
  "INTO", "GOTO", "PRINT", "INPUT", "IF", "THEN", "COREID", "NUMCORES",
  "SEND", "RECV", "RANDOM", "SYNC", "BCAST", "REDUCE", "SUM", "MIN", "MAX",
  "PROD", "SENDRECV", "TOFROM", "ADD", "SUB", "ISHOST", "ISDEVICE",
  "COLON", "DEF", "RET", "MULT", "DIV", "MOD", "AND", "OR", "NEQ", "LEQ",
  "GEQ", "LT", "GT", "EQ", "NOT", "SQRT", "SIN", "COS", "TAN", "ASIN",
  "ACOS", "ATAN", "SINH", "COSH", "TANH", "FLOOR", "CEIL", "LOG", "LOG10",
  "LPAREN", "RPAREN", "SLBRACE", "SRBRACE", "ASSGN", "POW", "$accept",
  "program", "lines", "line", "statements", "statement", "fncallargs",
  "fndeclarationargs", "codeblock", "indent_rule", "outdent_rule",
  "reductionop", "declareident", "elseifblock", "expression",
  "logical_or_expression", "logical_and_expression", "equality_expression",
  "relational_expression", "additive_expression",
  "multiplicative_expression", "value", "ident", "constant",
  "unary_operator", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335
};
# endif

#define YYPACT_NINF -174

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-174)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     425,   489,  -174,  -174,  -174,     9,     9,     9,  -174,   177,
       9,    14,   177,    54,   177,   177,     9,  -174,   177,    65,
     177,     9,  -174,    23,   425,  -174,    18,   489,   -57,    28,
      -4,    -2,     8,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,   226,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    48,    48,    48,    48,   177,    24,
      19,    17,   -40,    59,   -10,    44,  -174,     1,  -174,    52,
      20,  -174,  -174,  -174,  -174,    68,    39,    69,   -16,    67,
    -174,  -174,  -174,  -174,   177,    51,    30,  -174,  -174,  -174,
    -174,   177,   177,   177,  -174,   177,   177,   177,    19,  -174,
    -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,  -174,
    -174,  -174,  -174,    13,    91,   226,   226,   274,   274,   274,
     274,   274,   274,   274,   274,    48,    48,    48,    48,   177,
    -174,  -174,   177,     9,   457,   177,   177,   177,   177,    77,
     177,     9,    -8,  -174,    32,  -174,    53,    57,  -174,  -174,
      98,  -174,    17,   -40,    59,    59,   -10,   -10,   -10,   -10,
      44,    44,  -174,  -174,  -174,  -174,    60,   103,  -174,  -174,
     114,  -174,  -174,    61,   108,     9,   110,    -5,  -174,   177,
    -174,    58,  -174,  -174,  -174,   425,  -174,   177,    94,    91,
     122,     9,  -174,     9,     9,    97,  -174,   177,   347,   425,
    -174,  -174,   177,  -174,    70,  -174,    91,  -174,  -174,  -174,
     386,  -174,   177,  -174,  -174,    66,  -174
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    95,     8,    33,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,     0,     0,    34,     0,     0,
       0,     0,    36,     0,     2,     3,     6,    10,     0,     0,
       0,     0,     0,    96,    97,   103,    98,    99,   100,   104,
     105,    62,    63,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,    55,    57,    59,    64,    69,    72,    93,    91,     0,
       0,    51,    22,    31,    26,     0,     0,     0,     0,     0,
      47,    48,    49,    50,     0,     0,     0,     1,     4,     5,
       9,    38,     0,     0,     7,     0,     0,     0,    54,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     101,   102,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,    39,     0,    29,     0,     0,    28,    92,
       0,    21,    56,    58,    61,    60,    67,    68,    66,    65,
      70,    71,    73,    74,    75,    76,     0,     0,    27,    25,
      23,    13,    11,     0,     0,     0,     0,     0,    42,     0,
      37,     0,    18,    19,    45,     0,    94,     0,     0,     0,
       0,     0,    17,     0,     0,     0,    40,     0,     0,     0,
      52,    24,     0,    16,    14,    43,     0,    30,    46,    44,
       0,    12,     0,    35,    20,     0,    15
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -174,  -174,  -173,   -22,     2,  -174,  -174,  -174,  -125,  -174,
    -174,  -174,  -174,  -174,    16,   106,    31,    34,   -55,     6,
     -58,    -7,     0,   142,  -174
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    23,    24,    25,    26,    27,   142,   177,   151,   185,
     209,    84,    70,   189,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      28,    28,    88,    29,   136,    30,    31,    32,   179,   170,
      71,   194,   198,    74,   117,     2,    78,    72,    91,   118,
      92,    86,    93,    87,    28,    89,   210,    28,    73,    90,
      76,    77,   123,   124,    79,    94,    85,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,    33,    34,    35,     2,   130,   131,    33,    34,    35,
       2,   137,   154,   155,   201,   160,   161,    97,   180,   116,
     114,   195,   115,    95,   113,    96,    36,    37,   129,   132,
      38,   213,    36,    37,   133,   134,    38,   138,   135,   149,
      39,    40,   140,   125,   126,   127,    39,    40,   150,   175,
     139,    80,    81,    82,    83,   141,   184,   143,   144,   145,
     181,   146,   147,   148,   119,   120,   121,   122,   162,   163,
     164,   165,   187,    58,   128,   156,   157,   158,   159,   188,
     191,   182,   193,   168,    28,   183,   169,   197,   186,   190,
     200,   178,   202,   206,   216,   166,   152,   212,   167,    98,
     153,   171,   172,   173,   174,    75,   176,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   192,    88,     0,     0,     0,
      33,    34,    35,     2,     0,    28,     0,     0,    88,     0,
       0,   203,     0,   204,   205,   196,     0,     0,    28,    28,
       0,     0,     0,   199,     0,    36,    37,     0,     0,    38,
      28,     0,     0,   207,     0,     0,     0,     0,   211,    39,
      40,    41,    42,     0,     0,     0,     0,     0,   215,    33,
      34,    35,     2,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,     0,    36,    37,     0,     0,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,    40,
      41,    42,     0,     0,     0,     0,     0,    33,    34,    35,
       2,     0,     0,     0,     0,     0,     0,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    36,    37,     0,     0,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    39,    40,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
       1,     0,     0,     2,     3,     0,   208,     4,     5,     6,
       7,     8,     0,     0,     9,    10,     0,     0,     0,     0,
      11,    12,    13,    14,     0,     0,     0,    15,    16,     0,
      17,    18,    19,     0,     0,     0,     0,    20,     0,     1,
       0,     0,     2,     3,    21,    22,     4,     5,     6,     7,
       8,     0,     0,     9,    10,     0,     0,   214,     0,    11,
      12,    13,    14,     0,     0,     0,    15,    16,     0,    17,
      18,    19,     0,     0,     0,     0,    20,     0,     1,     0,
       0,     2,     3,    21,    22,     4,     5,     6,     7,     8,
       0,     0,     9,    10,     0,     0,     0,     0,    11,    12,
      13,    14,     0,     0,     0,    15,    16,     0,    17,    18,
      19,     0,     0,     2,   150,    20,     0,     4,     5,     6,
       7,     8,    21,    22,     9,    10,     0,     0,     0,     0,
      11,    12,    13,    14,     0,     0,     0,    15,    16,     0,
      17,    18,    19,     0,     0,     2,     0,    20,     0,     4,
       5,     6,     7,     8,    21,    22,     9,    10,     0,     0,
       0,     0,    11,    12,    13,    14,     0,     0,     0,    15,
      16,     0,    17,    18,    19,     0,     0,     0,     0,    20,
       0,     0,     0,     0,     0,     0,    21,    22
};

static const yytype_int16 yycheck[] =
{
       0,     1,    24,     1,    20,     5,     6,     7,    16,   134,
      10,    16,   185,    13,    54,     6,    16,     3,    75,    59,
      77,    21,    79,     0,    24,     7,   199,    27,    12,    27,
      14,    15,    42,    43,    18,     7,    20,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,     3,     4,     5,     6,     3,     4,     3,     4,     5,
       6,    77,   117,   118,   189,   123,   124,    59,    76,    52,
      46,    76,    53,    77,    58,    77,    28,    29,    77,    59,
      32,   206,    28,    29,    16,    46,    32,    20,    19,    76,
      42,    43,    41,    49,    50,    51,    42,    43,     7,    22,
      84,    36,    37,    38,    39,    75,     8,    91,    92,    93,
      78,    95,    96,    97,    55,    56,    57,    58,   125,   126,
     127,   128,    19,    75,    80,   119,   120,   121,   122,    15,
      22,    78,    22,   133,   134,    78,   134,    79,    78,    78,
      46,   141,    20,    46,    78,   129,   115,    77,   132,    43,
     116,   135,   136,   137,   138,    13,   140,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   175,   198,    -1,    -1,    -1,
       3,     4,     5,     6,    -1,   185,    -1,    -1,   210,    -1,
      -1,   191,    -1,   193,   194,   179,    -1,    -1,   198,   199,
      -1,    -1,    -1,   187,    -1,    28,    29,    -1,    -1,    32,
     210,    -1,    -1,   197,    -1,    -1,    -1,    -1,   202,    42,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,   212,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    -1,    28,    29,    -1,    -1,    32,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    28,    29,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
       3,    -1,    -1,     6,     7,    -1,     9,    10,    11,    12,
      13,    14,    -1,    -1,    17,    18,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    -1,     3,
      -1,    -1,     6,     7,    47,    48,    10,    11,    12,    13,
      14,    -1,    -1,    17,    18,    -1,    -1,    21,    -1,    23,
      24,    25,    26,    -1,    -1,    -1,    30,    31,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    -1,     3,    -1,
      -1,     6,     7,    47,    48,    10,    11,    12,    13,    14,
      -1,    -1,    17,    18,    -1,    -1,    -1,    -1,    23,    24,
      25,    26,    -1,    -1,    -1,    30,    31,    -1,    33,    34,
      35,    -1,    -1,     6,     7,    40,    -1,    10,    11,    12,
      13,    14,    47,    48,    17,    18,    -1,    -1,    -1,    -1,
      23,    24,    25,    26,    -1,    -1,    -1,    30,    31,    -1,
      33,    34,    35,    -1,    -1,     6,    -1,    40,    -1,    10,
      11,    12,    13,    14,    47,    48,    17,    18,    -1,    -1,
      -1,    -1,    23,    24,    25,    26,    -1,    -1,    -1,    30,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      -1,    -1,    -1,    -1,    -1,    -1,    47,    48
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     6,     7,    10,    11,    12,    13,    14,    17,
      18,    23,    24,    25,    26,    30,    31,    33,    34,    35,
      40,    47,    48,    82,    83,    84,    85,    86,   103,    85,
     103,   103,   103,     3,     4,     5,    28,    29,    32,    42,
      43,    44,    45,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
      93,   103,     3,    95,   103,   104,    95,    95,   103,    95,
      36,    37,    38,    39,    92,    95,   103,     0,    84,     7,
      85,    75,    77,    79,     7,    77,    77,    59,    96,   102,
     102,   102,   102,   102,   102,   102,   102,   102,   102,   102,
     102,   102,   102,    95,    46,    53,    52,    54,    59,    55,
      56,    57,    58,    42,    43,    49,    50,    51,    80,    77,
       3,     4,    59,    16,    46,    19,    20,    77,    20,    95,
      41,    75,    87,    95,    95,    95,    95,    95,    95,    76,
       7,    89,    97,    98,    99,    99,   100,   100,   100,   100,
     101,   101,   102,   102,   102,   102,    95,    95,   103,    85,
      89,    95,    95,    95,    95,    22,    95,    88,   103,    16,
      76,    78,    78,    78,     8,    90,    78,    19,    15,    94,
      78,    22,   103,    22,    16,    76,    95,    79,    83,    95,
      46,    89,    20,   103,   103,   103,    46,    95,     9,    91,
      83,    95,    77,    89,    21,    95,    78
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    81,    82,    83,    83,    84,    84,    84,    84,    85,
      85,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    87,
      87,    88,    88,    88,    89,    90,    91,    92,    92,    92,
      92,    93,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    98,    98,    98,    99,    99,    99,    99,    99,   100,
     100,   100,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   102,   102,   102,   102,   103,   104,   104,   104,   104,
     104,   104,   104,   104,   105,   105
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     3,     1,     2,
       1,     4,     7,     4,     6,     9,     6,     5,     5,     5,
       8,     4,     2,     4,     6,     4,     2,     4,     4,     3,
       6,     2,     1,     1,     1,     7,     1,     4,     0,     1,
       3,     0,     1,     3,     4,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     2,     1,     3,     1,     3,     1,
       3,     3,     1,     1,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     1,     3,     1,     4,     1,     1,     1,     1,     1,
       1,     2,     2,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

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
      yychar = yylex ();
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
     '$$ = $1'.

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
#line 58 "epython.y" /* yacc.c:1646  */
    { compileMemory((yyvsp[0].data)); }
#line 1607 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 62 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1613 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 66 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[-1].data); }
#line 1619 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 67 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[0].data); }
#line 1625 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 68 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[-1].data); setLineNumber((yyval.data), (yyvsp[-2].integer)); }
#line 1631 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 69 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = NULL; }
#line 1637 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 73 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1643 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 78 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendRecvStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1649 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 79 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendRecvIntoArrayStatement((yyvsp[-5].string), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1655 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 80 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1661 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 81 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendRecvStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1667 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 82 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendRecvStatementIntoArray((yyvsp[-7].data), (yyvsp[-5].data), (yyvsp[-3].string), (yyvsp[-1].data)); }
#line 1673 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 83 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendBcastStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1679 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 84 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendReductionStatement((yyvsp[-3].integer), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1685 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 85 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareArray((yyvsp[-3].string), (yyvsp[-1].data)); }
#line 1691 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 86 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareSharedArray((yyvsp[-3].string), (yyvsp[-1].data)); }
#line 1697 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 87 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendForStatement((yyvsp[-6].string), (yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[-1].data)); leaveScope(); }
#line 1703 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 88 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendWhileStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1709 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 89 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendGotoStatement((yyvsp[0].integer)); }
#line 1715 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 90 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1721 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 91 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].data)); }
#line 1727 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 92 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1733 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 93 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendInputStatement((yyvsp[0].string)); }
#line 1739 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 94 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendInputStringStatement((yyvsp[-2].data), (yyvsp[0].string)); }
#line 1745 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 95 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1751 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 96 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1757 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 97 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendArraySetStatement((yyvsp[-5].string), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1763 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 98 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendPrintStatement((yyvsp[0].data)); }
#line 1769 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 99 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendStopStatement(); }
#line 1775 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 100 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = NULL; }
#line 1781 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 101 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSyncStatement(); }
#line 1787 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 102 "epython.y" /* yacc.c:1646  */
    { appendNewFunctionStatement((yyvsp[-5].string), (yyvsp[-3].stack), (yyvsp[0].data)); leaveScope(); (yyval.data) = NULL; }
#line 1793 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 103 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatement(); }
#line 1799 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 104 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 1805 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 108 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); }
#line 1811 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 109 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 1817 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 110 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-2].stack); }
#line 1823 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 114 "epython.y" /* yacc.c:1646  */
    { enterScope(); (yyval.stack)=getNewStack(); }
#line 1829 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 115 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifier((yyval.stack), (yyvsp[0].string)); appendArgument((yyvsp[0].string)); }
#line 1835 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 116 "epython.y" /* yacc.c:1646  */
    { pushIdentifier((yyvsp[-2].stack), (yyvsp[0].string)); (yyval.stack)=(yyvsp[-2].stack); appendArgument((yyvsp[0].string)); }
#line 1841 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 120 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 1847 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 123 "epython.y" /* yacc.c:1646  */
    { enterScope(); }
#line 1853 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 126 "epython.y" /* yacc.c:1646  */
    { leaveScope(); }
#line 1859 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 129 "epython.y" /* yacc.c:1646  */
    { (yyval.integer)=0; }
#line 1865 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 130 "epython.y" /* yacc.c:1646  */
    { (yyval.integer)=1; }
#line 1871 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 131 "epython.y" /* yacc.c:1646  */
    { (yyval.integer)=2; }
#line 1877 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 132 "epython.y" /* yacc.c:1646  */
    { (yyval.integer)=3; }
#line 1883 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 136 "epython.y" /* yacc.c:1646  */
    { (yyval.string)=(yyvsp[0].string); enterScope(); addVariableIfNeeded((yyvsp[0].string)); }
#line 1889 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 140 "epython.y" /* yacc.c:1646  */
    { leaveScope(); enterScope(); }
#line 1895 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 144 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1901 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 145 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1907 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 149 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1913 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 150 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createOrExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1919 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 153 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1925 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 154 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAndExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1931 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 158 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1937 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 159 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createEqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1943 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 160 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1949 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 161 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsHostExpression(); }
#line 1955 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 162 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsDeviceExpression(); }
#line 1961 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 166 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1967 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 167 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1973 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 168 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1979 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 169 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1985 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 170 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1991 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 174 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1997 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 175 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAddExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2003 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 176 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSubExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2009 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 180 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2015 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 181 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createMulExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2021 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 182 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2027 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 183 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createModExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2033 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 184 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createPowExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2039 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 185 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSqrtExpression((yyvsp[0].data)); }
#line 2045 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 186 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinExpression((yyvsp[0].data)); }
#line 2051 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 187 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosExpression((yyvsp[0].data)); }
#line 2057 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 188 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanExpression((yyvsp[0].data)); }
#line 2063 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 189 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createASinExpression((yyvsp[0].data)); }
#line 2069 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 190 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createACosExpression((yyvsp[0].data)); }
#line 2075 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 191 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createATanExpression((yyvsp[0].data)); }
#line 2081 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 192 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinHExpression((yyvsp[0].data)); }
#line 2087 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 193 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosHExpression((yyvsp[0].data)); }
#line 2093 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 194 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanHExpression((yyvsp[0].data)); }
#line 2099 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 195 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorExpression((yyvsp[0].data)); }
#line 2105 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 196 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCeilExpression((yyvsp[0].data)); }
#line 2111 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 197 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLogExpression((yyvsp[0].data)); }
#line 2117 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 198 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLog10Expression((yyvsp[0].data)); }
#line 2123 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 202 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2129 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 203 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2135 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 204 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierExpression((yyvsp[0].string)); }
#line 2141 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 205 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierArrayAccessExpression((yyvsp[-3].string), (yyvsp[-1].data)); }
#line 2147 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 209 "epython.y" /* yacc.c:1646  */
    { (yyval.string) = malloc(strlen((yyvsp[0].string))+1); strcpy((yyval.string), (yyvsp[0].string)); }
#line 2153 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 213 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[0].integer)); }
#line 2159 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 214 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[0].real)); }
#line 2165 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 215 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCoreIdExpression(); }
#line 2171 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 216 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNumCoresExpression(); }
#line 2177 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 217 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRandomExpression(); }
#line 2183 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 218 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[-1].integer) * (yyvsp[0].integer)); }
#line 2189 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 219 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[-1].integer) * (yyvsp[0].real)); }
#line 2195 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 220 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createStringExpression((yyvsp[0].string)); }
#line 2201 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 224 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2207 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 225 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = -1; }
#line 2213 "parser.c" /* yacc.c:1646  */
    break;


#line 2217 "parser.c" /* yacc.c:1646  */
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

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

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
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 228 "epython.y" /* yacc.c:1906  */

