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
extern char * parsing_filename;
void yyerror(char const*);
int yylex(void);

void yyerror (char const *msg) {
	fprintf(stderr, "%s at line %d of file %s\n", msg, line_num, parsing_filename);
	exit(0);
}

#line 86 "parser.c" /* yacc.c:339  */

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
    DIM = 265,
    SDIM = 266,
    STOP = 267,
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
    EPY_I_SEND = 284,
    EPY_I_RECV = 285,
    RANDOM = 286,
    EPY_I_SYNC = 287,
    EPY_I_BCAST = 288,
    EPY_I_REDUCE = 289,
    EPY_I_SUM = 290,
    EPY_I_MIN = 291,
    EPY_I_MAX = 292,
    EPY_I_PROD = 293,
    EPY_I_SENDRECV = 294,
    TOFROM = 295,
    ADD = 296,
    SUB = 297,
    EPY_I_ISHOST = 298,
    EPY_I_ISDEVICE = 299,
    COLON = 300,
    DEF = 301,
    RET = 302,
    NONE = 303,
    FILESTART = 304,
    IN = 305,
    ADDADD = 306,
    SUBSUB = 307,
    MULMUL = 308,
    DIVDIV = 309,
    MODMOD = 310,
    POWPOW = 311,
    FLOORDIVFLOORDIV = 312,
    FLOORDIV = 313,
    MULT = 314,
    DIV = 315,
    MOD = 316,
    AND = 317,
    OR = 318,
    NEQ = 319,
    LEQ = 320,
    GEQ = 321,
    LT = 322,
    GT = 323,
    EQ = 324,
    NOT = 325,
    SQRT = 326,
    SIN = 327,
    COS = 328,
    TAN = 329,
    ASIN = 330,
    ACOS = 331,
    ATAN = 332,
    SINH = 333,
    COSH = 334,
    TANH = 335,
    FLOOR = 336,
    CEIL = 337,
    LOG = 338,
    LOG10 = 339,
    LPAREN = 340,
    RPAREN = 341,
    SLBRACE = 342,
    SRBRACE = 343,
    TRUE = 344,
    FALSE = 345,
    LEN = 346,
    ASSGN = 347,
    POW = 348
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
#define STOP 267
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
#define EPY_I_SEND 284
#define EPY_I_RECV 285
#define RANDOM 286
#define EPY_I_SYNC 287
#define EPY_I_BCAST 288
#define EPY_I_REDUCE 289
#define EPY_I_SUM 290
#define EPY_I_MIN 291
#define EPY_I_MAX 292
#define EPY_I_PROD 293
#define EPY_I_SENDRECV 294
#define TOFROM 295
#define ADD 296
#define SUB 297
#define EPY_I_ISHOST 298
#define EPY_I_ISDEVICE 299
#define COLON 300
#define DEF 301
#define RET 302
#define NONE 303
#define FILESTART 304
#define IN 305
#define ADDADD 306
#define SUBSUB 307
#define MULMUL 308
#define DIVDIV 309
#define MODMOD 310
#define POWPOW 311
#define FLOORDIVFLOORDIV 312
#define FLOORDIV 313
#define MULT 314
#define DIV 315
#define MOD 316
#define AND 317
#define OR 318
#define NEQ 319
#define LEQ 320
#define GEQ 321
#define LT 322
#define GT 323
#define EQ 324
#define NOT 325
#define SQRT 326
#define SIN 327
#define COS 328
#define TAN 329
#define ASIN 330
#define ACOS 331
#define ATAN 332
#define SINH 333
#define COSH 334
#define TANH 335
#define FLOOR 336
#define CEIL 337
#define LOG 338
#define LOG10 339
#define LPAREN 340
#define RPAREN 341
#define SLBRACE 342
#define SRBRACE 343
#define TRUE 344
#define FALSE 345
#define LEN 346
#define ASSGN 347
#define POW 348

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 21 "epython.y" /* yacc.c:355  */

	int integer;
	unsigned char uchar;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 321 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 336 "parser.c" /* yacc.c:358  */

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
#define YYLAST   574

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  94
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  120
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  267

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   348

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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    60,    60,    63,    64,    68,    69,    70,    74,    75,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   111,
     112,   113,   117,   118,   119,   123,   126,   129,   132,   133,
     134,   135,   139,   140,   141,   142,   143,   144,   145,   148,
     152,   153,   154,   158,   159,   163,   164,   167,   168,   172,
     173,   174,   175,   176,   180,   181,   182,   183,   184,   188,
     189,   190,   194,   195,   196,   197,   198,   199,   200,   201,
     202,   203,   204,   205,   206,   207,   208,   209,   210,   211,
     212,   213,   214,   218,   219,   220,   221,   222,   226,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   243,
     244
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "STRING",
  "IDENTIFIER", "NEWLINE", "INDENT", "OUTDENT", "DIM", "SDIM", "STOP",
  "ELSE", "ELIF", "COMMA", "WHILE", "FOR", "TO", "FROM", "NEXT", "INTO",
  "GOTO", "PRINT", "INPUT", "IF", "THEN", "EPY_I_COREID", "EPY_I_NUMCORES",
  "EPY_I_SEND", "EPY_I_RECV", "RANDOM", "EPY_I_SYNC", "EPY_I_BCAST",
  "EPY_I_REDUCE", "EPY_I_SUM", "EPY_I_MIN", "EPY_I_MAX", "EPY_I_PROD",
  "EPY_I_SENDRECV", "TOFROM", "ADD", "SUB", "EPY_I_ISHOST",
  "EPY_I_ISDEVICE", "COLON", "DEF", "RET", "NONE", "FILESTART", "IN",
  "ADDADD", "SUBSUB", "MULMUL", "DIVDIV", "MODMOD", "POWPOW",
  "FLOORDIVFLOORDIV", "FLOORDIV", "MULT", "DIV", "MOD", "AND", "OR", "NEQ",
  "LEQ", "GEQ", "LT", "GT", "EQ", "NOT", "SQRT", "SIN", "COS", "TAN",
  "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "FLOOR", "CEIL", "LOG",
  "LOG10", "LPAREN", "RPAREN", "SLBRACE", "SRBRACE", "TRUE", "FALSE",
  "LEN", "ASSGN", "POW", "$accept", "program", "lines", "line",
  "statements", "statement", "fncallargs", "fndeclarationargs",
  "codeblock", "indent_rule", "outdent_rule", "reductionop", "opassgn",
  "declareident", "elifblock", "expression", "logical_or_expression",
  "logical_and_expression", "equality_expression", "relational_expression",
  "additive_expression", "multiplicative_expression", "value", "ident",
  "constant", "unary_operator", YY_NULLPTR
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
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348
};
# endif

#define YYPACT_NINF -103

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-103)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     451,  -103,  -103,    17,    17,  -103,    28,    28,    17,    28,
     155,    28,    28,    17,  -103,    28,    13,    28,    17,   187,
      30,   451,  -103,    47,   527,   113,   -13,   -12,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,   276,   -17,
      -8,    -5,    -4,    -3,    -2,    -1,     6,    31,    35,    36,
      38,    40,    41,    28,  -103,  -103,    42,    34,    10,    23,
     -43,   -30,   -22,   -15,  -103,   -58,  -103,    37,    43,    65,
    -103,  -103,  -103,    75,    77,   106,     5,   109,  -103,  -103,
    -103,  -103,    28,    91,    48,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,    28,    28,
      28,    28,    28,    28,    10,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,    49,
      28,   127,   276,   276,   365,   365,   365,   365,   365,   365,
     365,   365,   294,   294,   294,   294,   294,    28,    28,  -103,
    -103,   127,    28,    17,   489,    28,    28,    28,    28,   116,
      28,    17,     0,  -103,    50,  -103,  -103,    57,    58,    64,
      66,    67,    70,    71,    76,    85,    86,    87,    88,    89,
      90,    92,    93,  -103,    94,   143,  -103,    23,   -43,   -30,
     -30,   -22,   -22,   -22,   -22,   -15,   -15,  -103,  -103,  -103,
    -103,  -103,     1,    96,  -103,   132,  -103,  -103,    39,  -103,
    -103,    97,   160,    17,   166,     3,  -103,    28,  -103,   102,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,   451,  -103,
    -103,   127,   144,    28,  -103,   169,    17,  -103,    17,    17,
     150,  -103,    28,   388,  -103,   127,   154,    28,  -103,   115,
    -103,   127,  -103,  -103,  -103,  -103,   127,  -103,    28,  -103,
      44,   118,   158,  -103,  -103,   127,  -103
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   108,     7,     0,     0,    32,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     0,     0,     0,     0,    35,
       0,     2,     3,     6,     9,     0,     0,     0,   109,   110,
     116,   111,   112,   113,   119,   120,    72,    73,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   117,   118,     0,     0,    63,    65,
      67,    69,    74,    79,    82,   105,   103,     0,     0,     0,
      59,    31,    26,     0,     0,     0,     0,     0,    48,    49,
      50,    51,     0,     0,     0,    36,    37,     1,     4,     5,
       8,    52,    53,    54,    55,    56,    57,    58,    39,     0,
       0,     0,     0,     0,    64,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,     0,   114,
     115,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,     0,    40,     0,    28,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,     0,     0,    25,    66,    68,    71,
      70,    77,    78,    76,    75,    80,    81,    85,    83,    84,
      86,    87,     0,     0,    20,     0,    27,    24,    21,    12,
      10,     0,     0,     0,     0,     0,    43,     0,    38,     0,
      17,    18,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,    46,     0,   107,
     106,     0,     0,     0,    23,     0,     0,    16,     0,     0,
       0,    41,     0,     0,    19,     0,     0,     0,    15,    13,
      44,     0,    29,    47,    45,    22,     0,    11,     0,    34,
      60,     0,     0,    62,    14,     0,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -103,  -103,   -24,   -19,   -14,  -103,    72,  -103,  -102,  -103,
    -103,  -103,  -103,  -103,   -52,    -6,   172,    95,    98,   -60,
     -66,   -64,   178,     4,   201,  -103
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    20,    21,    22,    23,    24,   152,   205,   176,   228,
     254,    82,   101,    69,   234,   153,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      57,    68,    88,    71,    25,    74,    75,    26,    27,    77,
      90,    83,    70,    86,    72,   207,   207,    76,   239,   130,
     131,   124,    84,     1,   146,    25,   125,   137,    25,   138,
      87,    28,    29,    30,     1,   126,   127,   128,   129,   194,
     139,   140,   198,   132,   133,   134,   135,   119,    78,    79,
      80,    81,   232,   233,    89,    31,    32,   262,   233,    33,
     181,   182,   183,   184,   179,   180,   185,   186,   105,    34,
      35,    36,    37,   122,   102,   103,   149,   106,   136,   121,
     107,   108,   109,   110,   111,   123,   208,   229,   141,   240,
     143,   112,   147,   154,   155,   156,   157,   158,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,   174,   142,   113,    54,    55,    56,
     114,   115,   144,   116,   145,   117,   118,   120,   148,   244,
     197,   150,   193,   151,   175,   173,   195,   203,   209,   199,
     200,   201,   202,   255,   204,   210,   211,   196,    25,   259,
     212,   227,   213,   214,   260,   206,   215,   216,    28,    29,
      30,     1,   217,   266,    91,    92,    93,    94,    95,    96,
      97,   218,   219,   220,   221,   222,   223,   231,   224,   225,
     226,   236,    31,    32,   230,   235,    33,   238,   247,   245,
      28,    29,    30,     1,   242,   251,    34,    35,    98,   256,
      99,   241,   258,   265,   243,   100,   264,   237,   263,   192,
     104,    73,     0,     0,    31,    32,     0,   177,    33,     0,
       0,   178,     0,     0,    88,     0,     0,   246,    34,    35,
      36,    37,    25,     0,     0,    85,   252,     0,     0,     0,
     248,   257,   249,   250,    54,    55,     0,    25,     0,     0,
       0,     0,   261,     0,     0,     0,     0,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,     0,     0,     0,    54,    55,    56,    28,
      29,    30,     1,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   170,   171,   172,    28,    29,    30,
       1,     0,     0,    31,    32,     0,     0,    33,     0,     0,
     187,   188,   189,   190,   191,     0,     0,    34,    35,    36,
      37,    31,    32,     0,     0,    33,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,     0,     0,     0,    54,    55,    56,    28,    29,
      30,     1,     0,     0,     0,     0,     0,     0,     0,    53,
       0,     0,     0,    54,    55,     0,     0,     0,     0,     0,
       0,     0,    31,    32,     1,     2,    33,   253,     3,     4,
       5,     0,     6,     0,     7,     8,    34,    35,     0,     0,
       0,     9,    10,    11,     0,     0,     0,    12,    13,     0,
      14,    15,    16,     0,     0,     0,     0,    17,     0,     0,
       0,     0,     0,     0,    18,    19,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,     0,     0,     0,    54,    55,    56,     1,     2,     0,
       0,     3,     4,     5,     0,     6,     0,     7,     8,     0,
       0,     0,     0,     0,     9,    10,    11,     0,     0,     0,
      12,    13,     0,    14,    15,    16,     0,     0,     0,     0,
      17,     0,     0,     0,     0,     1,   175,    18,    19,     3,
       4,     5,     0,     6,     0,     7,     8,     0,     0,     0,
       0,     0,     9,    10,    11,     0,     0,     0,    12,    13,
       0,    14,    15,    16,     0,     0,     0,     0,    17,     0,
       0,     0,     0,     1,     0,    18,    19,     3,     4,     5,
       0,     6,     0,     7,     8,     0,     0,     0,     0,     0,
       9,    10,    11,     0,     0,     0,    12,    13,     0,    14,
      15,    16,     0,     0,     0,     0,    17,     0,     0,     0,
       0,     0,     0,    18,    19
};

static const yytype_int16 yycheck[] =
{
       6,     7,    21,     9,     0,    11,    12,     3,     4,    15,
      24,    17,     8,    19,    10,    15,    15,    13,    15,    41,
      42,    64,    18,     6,    19,    21,    69,    85,    24,    87,
       0,     3,     4,     5,     6,    65,    66,    67,    68,   141,
       3,     4,   144,    58,    59,    60,    61,    53,    35,    36,
      37,    38,    13,    14,     7,    27,    28,    13,    14,    31,
     126,   127,   128,   129,   124,   125,   130,   131,    85,    41,
      42,    43,    44,    63,    87,    87,    82,    85,    93,    45,
      85,    85,    85,    85,    85,    62,    86,    86,    45,    86,
      15,    85,    87,    99,   100,   101,   102,   103,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,   120,    50,    85,    89,    90,    91,
      85,    85,    45,    85,    18,    85,    85,    85,    19,   231,
     144,    40,   138,    85,     7,    86,   142,    21,    88,   145,
     146,   147,   148,   245,   150,    88,    88,   143,   144,   251,
      86,     8,    86,    86,   256,   151,    86,    86,     3,     4,
       5,     6,    86,   265,    51,    52,    53,    54,    55,    56,
      57,    86,    86,    86,    86,    86,    86,    45,    86,    86,
      86,    21,    27,    28,    88,    88,    31,    21,    19,    45,
       3,     4,     5,     6,    92,    45,    41,    42,    85,    45,
      87,   207,    87,    45,   228,    92,    88,   203,   260,   137,
      38,    10,    -1,    -1,    27,    28,    -1,   122,    31,    -1,
      -1,   123,    -1,    -1,   243,    -1,    -1,   233,    41,    42,
      43,    44,   228,    -1,    -1,    48,   242,    -1,    -1,    -1,
     236,   247,   238,   239,    89,    90,    -1,   243,    -1,    -1,
      -1,    -1,   258,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    -1,    -1,    -1,    89,    90,    91,     3,
       4,     5,     6,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,     3,     4,     5,
       6,    -1,    -1,    27,    28,    -1,    -1,    31,    -1,    -1,
     132,   133,   134,   135,   136,    -1,    -1,    41,    42,    43,
      44,    27,    28,    -1,    -1,    31,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    -1,    -1,    -1,    89,    90,    91,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    85,
      -1,    -1,    -1,    89,    90,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,     6,     7,    31,     9,    10,    11,
      12,    -1,    14,    -1,    16,    17,    41,    42,    -1,    -1,
      -1,    23,    24,    25,    -1,    -1,    -1,    29,    30,    -1,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    -1,    -1,    -1,    89,    90,    91,     6,     7,    -1,
      -1,    10,    11,    12,    -1,    14,    -1,    16,    17,    -1,
      -1,    -1,    -1,    -1,    23,    24,    25,    -1,    -1,    -1,
      29,    30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    -1,    -1,    -1,    -1,     6,     7,    46,    47,    10,
      11,    12,    -1,    14,    -1,    16,    17,    -1,    -1,    -1,
      -1,    -1,    23,    24,    25,    -1,    -1,    -1,    29,    30,
      -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    -1,
      -1,    -1,    -1,     6,    -1,    46,    47,    10,    11,    12,
      -1,    14,    -1,    16,    17,    -1,    -1,    -1,    -1,    -1,
      23,    24,    25,    -1,    -1,    -1,    29,    30,    -1,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    10,    11,    12,    14,    16,    17,    23,
      24,    25,    29,    30,    32,    33,    34,    39,    46,    47,
      95,    96,    97,    98,    99,   117,   117,   117,     3,     4,
       5,    27,    28,    31,    41,    42,    43,    44,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    89,    90,    91,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   109,   107,
     117,   109,   117,   118,   109,   109,   117,   109,    35,    36,
      37,    38,   105,   109,   117,    48,   109,     0,    97,     7,
      98,    51,    52,    53,    54,    55,    56,    57,    85,    87,
      92,   106,    87,    87,   110,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,   109,
      85,    45,    63,    62,    64,    69,    65,    66,    67,    68,
      41,    42,    58,    59,    60,    61,    93,    85,    87,     3,
       4,    45,    50,    15,    45,    18,    19,    87,    19,   109,
      40,    85,   100,   109,   109,   109,   109,   109,   109,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,    86,   109,     7,   102,   111,   112,   113,
     113,   114,   114,   114,   114,   115,   115,   116,   116,   116,
     116,   116,   100,   109,   102,   109,   117,    98,   102,   109,
     109,   109,   109,    21,   109,   101,   117,    15,    86,    88,
      88,    88,    86,    86,    86,    86,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,     8,   103,    86,
      88,    45,    13,    14,   108,    88,    21,   117,    21,    15,
      86,   109,    92,    96,   102,    45,   109,    19,   117,   117,
     117,    45,   109,     9,   104,   102,    45,   109,    87,   102,
     102,   109,    13,   108,    88,    45,   102
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    94,    95,    96,    96,    97,    97,    97,    98,    98,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,    99,
      99,    99,    99,    99,    99,    99,    99,    99,    99,   100,
     100,   100,   101,   101,   101,   102,   103,   104,   105,   105,
     105,   105,   106,   106,   106,   106,   106,   106,   106,   107,
     108,   108,   108,   109,   109,   110,   110,   111,   111,   112,
     112,   112,   112,   112,   113,   113,   113,   113,   113,   114,
     114,   114,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   116,   116,   116,   116,   116,   117,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   119,
     119
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     2,     1,
       4,     7,     4,     6,     9,     6,     5,     5,     5,     6,
       4,     4,     7,     5,     4,     4,     2,     4,     3,     6,
       3,     2,     1,     1,     7,     1,     2,     2,     4,     0,
       1,     3,     0,     1,     3,     4,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       4,     7,     5,     1,     2,     1,     3,     1,     3,     1,
       3,     3,     1,     1,     1,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     3,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     1,     3,     1,     4,     4,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     1,     1,     1,
       1
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
#line 60 "epython.y" /* yacc.c:1646  */
    { compileMemory((yyvsp[0].data)); }
#line 1669 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 64 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1675 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 68 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[-1].data); }
#line 1681 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 69 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[0].data); }
#line 1687 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 70 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = NULL; }
#line 1693 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 74 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1699 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendRecvStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1705 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendRecvIntoArrayStatement((yyvsp[-5].string), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1711 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 81 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1717 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 82 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendRecvStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1723 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendRecvStatementIntoArray((yyvsp[-7].data), (yyvsp[-5].data), (yyvsp[-3].string), (yyvsp[-1].data)); }
#line 1729 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 84 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendBcastStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1735 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 85 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendReductionStatement((yyvsp[-3].uchar), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1741 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 86 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareArray((yyvsp[-3].string), (yyvsp[-1].data)); }
#line 1747 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 87 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareSharedArray((yyvsp[-3].string), (yyvsp[-1].data)); }
#line 1753 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 88 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendForStatement((yyvsp[-4].string), (yyvsp[-2].data), (yyvsp[0].data)); leaveScope(); }
#line 1759 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 89 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendWhileStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1765 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 90 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1771 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 91 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1777 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 92 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 1783 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 93 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1789 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 94 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1795 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 95 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendInputStatement((yyvsp[0].string)); }
#line 1801 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 96 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendInputStringStatement((yyvsp[-2].data), (yyvsp[0].string)); }
#line 1807 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 97 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1813 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 98 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendArraySetStatement((yyvsp[-5].string), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1819 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 99 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetWithOperatorStatement((yyvsp[-2].string), (yyvsp[0].data), (yyvsp[-1].uchar)); }
#line 1825 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 100 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendPrintStatement((yyvsp[0].data)); }
#line 1831 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 101 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendStopStatement(); }
#line 1837 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 102 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSyncStatement(); }
#line 1843 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 103 "epython.y" /* yacc.c:1646  */
    { appendNewFunctionStatement((yyvsp[-5].string), (yyvsp[-3].stack), (yyvsp[0].data)); leaveScope(); (yyval.data) = NULL; }
#line 1849 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 104 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatement(); }
#line 1855 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 105 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatement(); }
#line 1861 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 106 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatementWithExpression((yyvsp[0].data)); }
#line 1867 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 107 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 1873 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 111 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); }
#line 1879 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 112 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 1885 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 113 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-2].stack); }
#line 1891 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 117 "epython.y" /* yacc.c:1646  */
    { enterScope(); (yyval.stack)=getNewStack(); }
#line 1897 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 118 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifier((yyval.stack), (yyvsp[0].string)); appendArgument((yyvsp[0].string)); }
#line 1903 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 119 "epython.y" /* yacc.c:1646  */
    { pushIdentifier((yyvsp[-2].stack), (yyvsp[0].string)); (yyval.stack)=(yyvsp[-2].stack); appendArgument((yyvsp[0].string)); }
#line 1909 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 123 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 1915 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 126 "epython.y" /* yacc.c:1646  */
    { enterScope(); }
#line 1921 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 129 "epython.y" /* yacc.c:1646  */
    { leaveScope(); }
#line 1927 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 132 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=0; }
#line 1933 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 133 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=1; }
#line 1939 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 134 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=2; }
#line 1945 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 135 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=3; }
#line 1951 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 139 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=0; }
#line 1957 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 140 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=1; }
#line 1963 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 141 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=2; }
#line 1969 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 142 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=3; }
#line 1975 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 143 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=4; }
#line 1981 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 144 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=5; }
#line 1987 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 145 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=6; }
#line 1993 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 148 "epython.y" /* yacc.c:1646  */
    { (yyval.string)=(yyvsp[0].string); enterScope(); addVariableIfNeeded((yyvsp[0].string)); }
#line 1999 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 152 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2005 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 153 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 2011 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 154 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 2017 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 158 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2023 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 159 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2029 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 163 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2035 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 164 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createOrExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2041 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 167 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2047 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 168 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAndExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2053 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 172 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2059 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 173 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createEqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2065 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 174 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2071 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 175 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsHostExpression(); }
#line 2077 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 176 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsDeviceExpression(); }
#line 2083 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 180 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2089 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 181 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2095 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 182 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2101 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 183 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2107 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 184 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2113 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 188 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2119 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 189 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAddExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2125 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 190 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSubExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2131 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 194 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2137 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 195 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createMulExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2143 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 196 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2149 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 197 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2155 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 198 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createModExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2161 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 199 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createPowExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2167 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 200 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSqrtExpression((yyvsp[-1].data)); }
#line 2173 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 201 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinExpression((yyvsp[-1].data)); }
#line 2179 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 202 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosExpression((yyvsp[-1].data)); }
#line 2185 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 203 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanExpression((yyvsp[-1].data)); }
#line 2191 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 204 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createASinExpression((yyvsp[-1].data)); }
#line 2197 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 205 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createACosExpression((yyvsp[-1].data)); }
#line 2203 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 206 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createATanExpression((yyvsp[-1].data)); }
#line 2209 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 207 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinHExpression((yyvsp[-1].data)); }
#line 2215 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 208 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosHExpression((yyvsp[-1].data)); }
#line 2221 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 209 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanHExpression((yyvsp[-1].data)); }
#line 2227 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 210 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorExpression((yyvsp[-1].data)); }
#line 2233 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 211 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCeilExpression((yyvsp[-1].data)); }
#line 2239 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 212 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLogExpression((yyvsp[-1].data)); }
#line 2245 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 213 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLog10Expression((yyvsp[-1].data)); }
#line 2251 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 214 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLenExpression((yyvsp[-1].data)); }
#line 2257 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 218 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2263 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 219 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2269 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 220 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierExpression((yyvsp[0].string)); }
#line 2275 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 221 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierArrayAccessExpression((yyvsp[-3].string), (yyvsp[-1].data)); }
#line 2281 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 222 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 2287 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 226 "epython.y" /* yacc.c:1646  */
    { (yyval.string) = malloc(strlen((yyvsp[0].string))+1); strcpy((yyval.string), (yyvsp[0].string)); }
#line 2293 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 230 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[0].integer)); }
#line 2299 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 231 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[0].real)); }
#line 2305 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 232 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCoreIdExpression(); }
#line 2311 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 233 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNumCoresExpression(); }
#line 2317 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 234 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRandomExpression(); }
#line 2323 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 235 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[-1].integer) * (yyvsp[0].integer)); }
#line 2329 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 236 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[-1].integer) * (yyvsp[0].real)); }
#line 2335 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 237 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createStringExpression((yyvsp[0].string)); }
#line 2341 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 238 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(1); }
#line 2347 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 239 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(0); }
#line 2353 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 243 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2359 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 244 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = -1; }
#line 2365 "parser.c" /* yacc.c:1646  */
    break;


#line 2369 "parser.c" /* yacc.c:1646  */
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
#line 247 "epython.y" /* yacc.c:1906  */

