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
    EPY_I_BCAST = 285,
    EPY_I_REDUCE = 286,
    EPY_I_SUM = 287,
    EPY_I_MIN = 288,
    EPY_I_MAX = 289,
    EPY_I_PROD = 290,
    TOFROM = 291,
    NATIVE = 292,
    ADD = 293,
    SUB = 294,
    COLON = 295,
    DEF = 296,
    RET = 297,
    NONE = 298,
    FILESTART = 299,
    IN = 300,
    ADDADD = 301,
    SUBSUB = 302,
    MULMUL = 303,
    DIVDIV = 304,
    MODMOD = 305,
    POWPOW = 306,
    FLOORDIVFLOORDIV = 307,
    FLOORDIV = 308,
    MULT = 309,
    DIV = 310,
    MOD = 311,
    AND = 312,
    OR = 313,
    NEQ = 314,
    LEQ = 315,
    GEQ = 316,
    LT = 317,
    GT = 318,
    EQ = 319,
    IS = 320,
    NOT = 321,
    SQRT = 322,
    SIN = 323,
    COS = 324,
    TAN = 325,
    ASIN = 326,
    ACOS = 327,
    ATAN = 328,
    SINH = 329,
    COSH = 330,
    TANH = 331,
    FLOOR = 332,
    CEIL = 333,
    LOG = 334,
    LOG10 = 335,
    STR = 336,
    LPAREN = 337,
    RPAREN = 338,
    SLBRACE = 339,
    SRBRACE = 340,
    TRUE = 341,
    FALSE = 342,
    LEN = 343,
    EPY_I_ISHOST = 344,
    EPY_I_ISDEVICE = 345,
    ASSGN = 346,
    POW = 347
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
#define EPY_I_BCAST 285
#define EPY_I_REDUCE 286
#define EPY_I_SUM 287
#define EPY_I_MIN 288
#define EPY_I_MAX 289
#define EPY_I_PROD 290
#define TOFROM 291
#define NATIVE 292
#define ADD 293
#define SUB 294
#define COLON 295
#define DEF 296
#define RET 297
#define NONE 298
#define FILESTART 299
#define IN 300
#define ADDADD 301
#define SUBSUB 302
#define MULMUL 303
#define DIVDIV 304
#define MODMOD 305
#define POWPOW 306
#define FLOORDIVFLOORDIV 307
#define FLOORDIV 308
#define MULT 309
#define DIV 310
#define MOD 311
#define AND 312
#define OR 313
#define NEQ 314
#define LEQ 315
#define GEQ 316
#define LT 317
#define GT 318
#define EQ 319
#define IS 320
#define NOT 321
#define SQRT 322
#define SIN 323
#define COS 324
#define TAN 325
#define ASIN 326
#define ACOS 327
#define ATAN 328
#define SINH 329
#define COSH 330
#define TANH 331
#define FLOOR 332
#define CEIL 333
#define LOG 334
#define LOG10 335
#define STR 336
#define LPAREN 337
#define RPAREN 338
#define SLBRACE 339
#define SRBRACE 340
#define TRUE 341
#define FALSE 342
#define LEN 343
#define EPY_I_ISHOST 344
#define EPY_I_ISDEVICE 345
#define ASSGN 346
#define POW 347

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

#line 319 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 334 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  83
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   560

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  93
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  126
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  277

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   347

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
      85,    86,    87,    88,    89,    90,    91,    92
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    63,    64,    68,    69,    70,    74,    75,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   103,   104,   108,   109,   110,   114,   115,   116,   117,
     118,   122,   125,   128,   131,   134,   135,   136,   137,   141,
     142,   143,   144,   145,   146,   147,   150,   154,   155,   156,
     160,   161,   165,   166,   169,   170,   174,   175,   176,   177,
     181,   182,   183,   184,   185,   189,   190,   191,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   224,   225,   229,   230,   231,   232,
     233,   234,   238,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   257,   258
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "STRING",
  "IDENTIFIER", "NEWLINE", "INDENT", "OUTDENT", "DIM", "SDIM", "EXIT",
  "ELSE", "ELIF", "COMMA", "WHILE", "FOR", "TO", "FROM", "NEXT", "INTO",
  "GOTO", "PRINT", "INPUT", "IF", "THEN", "EPY_I_COREID", "EPY_I_NUMCORES",
  "EPY_I_RANDOM", "EPY_I_BCAST", "EPY_I_REDUCE", "EPY_I_SUM", "EPY_I_MIN",
  "EPY_I_MAX", "EPY_I_PROD", "TOFROM", "NATIVE", "ADD", "SUB", "COLON",
  "DEF", "RET", "NONE", "FILESTART", "IN", "ADDADD", "SUBSUB", "MULMUL",
  "DIVDIV", "MODMOD", "POWPOW", "FLOORDIVFLOORDIV", "FLOORDIV", "MULT",
  "DIV", "MOD", "AND", "OR", "NEQ", "LEQ", "GEQ", "LT", "GT", "EQ", "IS",
  "NOT", "SQRT", "SIN", "COS", "TAN", "ASIN", "ACOS", "ATAN", "SINH",
  "COSH", "TANH", "FLOOR", "CEIL", "LOG", "LOG10", "STR", "LPAREN",
  "RPAREN", "SLBRACE", "SRBRACE", "TRUE", "FALSE", "LEN", "EPY_I_ISHOST",
  "EPY_I_ISDEVICE", "ASSGN", "POW", "$accept", "program", "lines", "line",
  "statements", "statement", "arrayaccessor", "fncallargs",
  "fndeclarationargs", "fn_entry", "codeblock", "indent_rule",
  "outdent_rule", "reductionop", "opassgn", "declareident", "elifblock",
  "expression", "logical_or_expression", "logical_and_expression",
  "equality_expression", "relational_expression", "additive_expression",
  "multiplicative_expression", "commaseparray", "value", "ident",
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
     345,   346,   347
};
# endif

#define YYPACT_NINF -138

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-138)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     474,  -138,  -138,     9,     9,   -73,   305,   305,     9,   305,
     305,   305,    48,     9,     9,   305,    19,   474,  -138,    56,
     518,    21,   104,    -6,    13,     2,  -138,  -138,  -138,    28,
    -138,  -138,    31,     9,  -138,  -138,  -138,   391,    46,    47,
      52,    53,    55,    57,    59,    60,    62,    63,    64,    75,
      76,    77,    78,   305,   305,  -138,  -138,    79,   122,   106,
     109,   -28,    45,    23,     4,  -138,   -50,  -138,    89,   127,
     123,  -138,  -138,   129,   151,  -138,  -138,  -138,  -138,   305,
      90,  -138,  -138,  -138,  -138,  -138,  -138,     9,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,   305,   305,   305,   -56,   305,
     305,   305,  -138,   219,    93,    95,   106,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,   305,    98,  -138,   -10,   305,   164,   391,   391,   391,
     391,   391,   391,   391,   391,   391,   391,   391,    61,    61,
      61,    61,    61,   305,    94,  -138,  -138,   164,   305,   496,
     305,   170,   305,    -4,   101,     1,  -138,   108,  -138,   305,
     305,  -138,    -9,    -8,  -138,   111,  -138,   305,   114,   117,
     118,   119,   124,   125,   126,   133,   134,   135,   136,   137,
     138,   143,   144,  -138,   305,   152,   145,   197,  -138,   109,
     -28,    45,    45,    45,    23,    23,    23,    23,     4,     4,
    -138,  -138,  -138,  -138,  -138,     3,  -138,   172,  -138,    88,
     208,     9,     8,     9,   192,   305,   305,  -138,  -138,   148,
    -138,  -138,  -138,  -138,    12,  -138,  -138,  -138,  -138,  -138,
    -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,  -138,
    -138,    61,  -138,  -138,   474,  -138,   164,   194,   305,  -138,
       9,  -138,  -138,   146,   164,  -138,  -138,  -138,  -138,  -138,
     173,  -138,   164,   195,  -138,   305,  -138,  -138,  -138,  -138,
     164,  -138,   110,   196,  -138,   164,  -138
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   112,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,     0,     2,     3,     6,
       9,     0,     0,     0,     0,     0,   113,   114,   121,     0,
     115,   116,   117,     0,   125,   126,   124,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   122,   123,     0,     0,    60,
      62,    64,    66,    70,    75,    78,   108,   106,     0,     0,
       0,    56,    24,     0,     0,    45,    46,    47,    48,     0,
       0,    41,    28,     1,     4,     5,     8,    36,    49,    50,
      51,    52,    53,    54,    55,    33,     0,     0,     0,     0,
       0,     0,    25,     0,     0,     0,    61,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,   109,   119,   120,     0,     0,     0,
       0,     0,    33,     0,    37,     0,    34,     0,    21,     0,
       0,    23,     0,     0,   102,     0,   118,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,     0,   100,     0,     0,    20,    63,
      65,    68,    67,    69,    73,    74,    72,    71,    76,    77,
      81,    79,    80,    82,    83,     0,    15,     0,    19,    16,
       0,     0,     0,     0,     0,     0,     0,    29,    31,     0,
      22,    12,    13,   103,     0,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    97,    98,    96,
     105,     0,    99,    43,     0,   110,     0,     0,     0,    18,
       0,    11,    30,    39,     0,    38,    35,    32,   111,   101,
       0,    14,     0,     0,    10,     0,    26,    44,    42,    17,
       0,    40,    57,     0,    59,     0,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -138,  -138,    -3,   -15,   -19,  -138,   174,  -114,  -138,  -138,
    -137,  -138,  -138,  -138,  -138,  -138,   -34,    15,   202,   115,
     121,   -75,   -13,    -5,    26,   -68,     0,  -138,  -138
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,    98,   155,   153,    21,
     188,   244,   268,    79,    99,    70,   249,   156,    59,    60,
      61,    62,    63,    64,   124,    65,    66,    67,    68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      22,    86,    84,    23,    24,   184,   184,   184,    71,    25,
     206,   213,   209,    80,    81,     1,   216,    22,   216,    83,
      22,    58,    69,   216,    72,    73,    74,   216,   159,   205,
      82,   129,   143,   105,    96,   160,   130,   131,   212,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   224,   191,   192,   193,   138,   139,   140,
     141,   136,   137,    85,    26,    27,    28,     1,   122,   123,
     200,   201,   202,   203,   204,   185,   221,   222,   100,   214,
      75,    76,    77,    78,   217,   102,   245,   154,    30,    31,
      32,   252,   145,   146,   151,   258,   142,   101,    33,    34,
      35,   247,   248,    87,    36,   132,   133,   134,   135,   261,
     103,   157,   158,   104,   161,   123,   123,   266,   165,   194,
     195,   196,   197,   273,   248,   269,   162,   163,   107,   108,
     208,   198,   199,   272,   109,   110,   182,   111,   276,   112,
     186,   113,   114,    53,   115,   116,   117,    55,    56,    22,
      88,    89,    90,    91,    92,    93,    94,   118,   119,   120,
     121,   125,   126,   207,   127,   210,   128,   147,   148,   149,
     150,   187,   152,   259,   219,   220,   166,   167,   159,     1,
       2,   183,   267,     3,     4,     5,    95,     6,    96,     7,
       8,   211,   215,   218,   223,    97,     9,   225,    10,   240,
     226,   227,   228,    11,    12,   243,   241,   229,   230,   231,
      13,   251,   246,   253,    14,    15,   232,   233,   234,   235,
     236,   237,    26,    27,    28,     1,   238,   239,   242,   250,
     255,   256,   254,   257,   262,   270,   275,   265,   274,   106,
     144,   260,   189,    29,    22,    84,    30,    31,    32,   190,
     264,     0,     0,     0,     0,     0,    33,    34,    35,     0,
      22,     0,    36,   263,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     271,     0,     0,     0,     0,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,   164,    54,     0,    55,    56,    57,    26,    27,
      28,     1,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    29,
       0,     0,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,    33,    34,    35,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,     0,    54,
       0,    55,    56,    57,    26,    27,    28,     1,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,    30,    31,
      32,     0,     0,     0,     0,     0,     0,     0,    33,    34,
      35,     0,     0,     0,    36,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,     0,    54,     0,    55,    56,    57,
       1,     2,     0,     0,     3,     4,     5,     0,     6,     0,
       7,     8,     0,     0,     0,     0,     0,     9,     0,    10,
       0,     0,     1,   187,    11,    12,     3,     4,     5,     0,
       6,    13,     7,     8,     0,    14,    15,     0,     0,     9,
       0,    10,     0,     0,     1,     0,    11,    12,     3,     4,
       5,     0,     6,    13,     7,     8,     0,    14,    15,     0,
       0,     9,     0,    10,     0,     0,     0,     0,    11,    12,
       0,     0,     0,     0,     0,    13,     0,     0,     0,    14,
      15
};

static const yytype_int16 yycheck[] =
{
       0,    20,    17,     3,     4,    15,    15,    15,     8,    82,
     147,    15,   149,    13,    14,     6,    15,    17,    15,     0,
      20,     6,     7,    15,     9,    10,    11,    15,    84,   143,
      15,    59,    82,    33,    84,    91,    64,    65,   152,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   167,   129,   130,   131,    53,    54,    55,
      56,    38,    39,     7,     3,     4,     5,     6,    53,    54,
     138,   139,   140,   141,   142,    85,    85,    85,    84,    83,
      32,    33,    34,    35,    83,    83,    83,    87,    27,    28,
      29,    83,     3,     4,    79,    83,    92,    84,    37,    38,
      39,    13,    14,    82,    43,    60,    61,    62,    63,   246,
      82,    96,    97,    82,    99,   100,   101,   254,   103,   132,
     133,   134,   135,    13,    14,   262,   100,   101,    82,    82,
     149,   136,   137,   270,    82,    82,   121,    82,   275,    82,
     125,    82,    82,    82,    82,    82,    82,    86,    87,   149,
      46,    47,    48,    49,    50,    51,    52,    82,    82,    82,
      82,    82,    40,   148,    58,   150,    57,    40,    45,    40,
      19,     7,    82,   241,   159,   160,    83,    82,    84,     6,
       7,    83,     9,    10,    11,    12,    82,    14,    84,    16,
      17,    21,    91,    85,    83,    91,    23,    83,    25,   184,
      83,    83,    83,    30,    31,     8,    54,    83,    83,    83,
      37,   211,    40,   213,    41,    42,    83,    83,    83,    83,
      83,    83,     3,     4,     5,     6,    83,    83,    83,    21,
     215,   216,    40,    85,    40,    40,    40,    91,   272,    37,
      66,   244,   127,    24,   244,   260,    27,    28,    29,   128,
     250,    -1,    -1,    -1,    -1,    -1,    37,    38,    39,    -1,
     260,    -1,    43,   248,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     265,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    -1,    86,    87,    88,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      -1,    -1,    27,    28,    29,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    38,    39,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    -1,    84,
      -1,    86,    87,    88,     3,     4,     5,     6,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,    28,
      29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,
      39,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    -1,    84,    -1,    86,    87,    88,
       6,     7,    -1,    -1,    10,    11,    12,    -1,    14,    -1,
      16,    17,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,
      -1,    -1,     6,     7,    30,    31,    10,    11,    12,    -1,
      14,    37,    16,    17,    -1,    41,    42,    -1,    -1,    23,
      -1,    25,    -1,    -1,     6,    -1,    30,    31,    10,    11,
      12,    -1,    14,    37,    16,    17,    -1,    41,    42,    -1,
      -1,    23,    -1,    25,    -1,    -1,    -1,    -1,    30,    31,
      -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,
      42
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    10,    11,    12,    14,    16,    17,    23,
      25,    30,    31,    37,    41,    42,    94,    95,    96,    97,
      98,   102,   119,   119,   119,    82,     3,     4,     5,    24,
      27,    28,    29,    37,    38,    39,    43,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,    84,    86,    87,    88,   110,   111,
     112,   113,   114,   115,   116,   118,   119,   120,   121,   110,
     108,   119,   110,   110,   110,    32,    33,    34,    35,   106,
     119,   119,   110,     0,    96,     7,    97,    82,    46,    47,
      48,    49,    50,    51,    52,    82,    84,    91,    99,   107,
      84,    84,    83,    82,    82,   119,   111,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,   110,   110,   117,    82,    40,    58,    57,    59,
      64,    65,    60,    61,    62,    63,    38,    39,    53,    54,
      55,    56,    92,    82,    99,     3,     4,    40,    45,    40,
      19,   110,    82,   101,   119,   100,   110,   110,   110,    84,
      91,   110,   117,   117,    83,   110,    83,    82,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   110,    83,    15,    85,   110,     7,   103,   112,
     113,   114,   114,   114,   115,   115,   115,   115,   116,   116,
     118,   118,   118,   118,   118,   100,   103,   110,    97,   103,
     110,    21,   100,    15,    83,    91,    15,    83,    85,   110,
     110,    85,    85,    83,   100,    83,    83,    83,    83,    83,
      83,    83,    83,    83,    83,    83,    83,    83,    83,    83,
     110,    54,    83,     8,   104,    83,    40,    13,    14,   109,
      21,   119,    83,   119,    40,   110,   110,    85,    83,   118,
      95,   103,    40,   110,   119,    91,   103,     9,   105,   103,
      40,   110,   103,    13,   109,    40,   103
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    93,    94,    95,    95,    96,    96,    96,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    99,    99,   100,   100,   100,   101,   101,   101,   101,
     101,   102,   103,   104,   105,   106,   106,   106,   106,   107,
     107,   107,   107,   107,   107,   107,   108,   109,   109,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   113,   113,
     114,   114,   114,   114,   114,   115,   115,   115,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   117,   117,   118,   118,   118,   118,
     118,   118,   119,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   121
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     2,     1,
       6,     5,     5,     5,     6,     4,     4,     7,     5,     4,
       4,     3,     4,     3,     2,     3,     6,     1,     2,     4,
       5,     3,     4,     0,     1,     3,     0,     1,     3,     3,
       5,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     7,     5,
       1,     2,     1,     3,     1,     3,     1,     3,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     3,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,     5,     3,     4,     1,     3,     1,     3,     1,     2,
       4,     5,     1,     1,     1,     1,     1,     1,     3,     2,
       2,     1,     1,     1,     1,     1,     1
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
#line 1668 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 64 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1674 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 68 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[-1].data); }
#line 1680 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 69 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[0].data); }
#line 1686 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 70 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = NULL; }
#line 1692 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 74 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1698 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendBcastStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1704 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendReductionStatement((yyvsp[-3].uchar), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1710 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 81 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareArray((yyvsp[-3].string), (yyvsp[-1].stack), 0); }
#line 1716 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 82 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareArray((yyvsp[-3].string), (yyvsp[-1].stack), 1); }
#line 1722 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendForStatement((yyvsp[-4].string), (yyvsp[-2].data), (yyvsp[0].data)); leaveScope(); }
#line 1728 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 84 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendWhileStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1734 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 85 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1740 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 86 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1746 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 87 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 1752 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 88 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1758 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 89 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1764 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 90 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1770 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 91 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendArraySetStatement((yyvsp[-3].string), (yyvsp[-2].stack), (yyvsp[0].data)); }
#line 1776 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 92 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetWithOperatorStatement((yyvsp[-2].string), (yyvsp[0].data), (yyvsp[-1].uchar)); }
#line 1782 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 93 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement("rtl_print", NULL, (yyvsp[0].data)); }
#line 1788 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 94 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendStopStatement(); }
#line 1794 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 95 "epython.y" /* yacc.c:1646  */
    { appendNewFunctionStatement((yyvsp[-5].string), (yyvsp[-3].stack), (yyvsp[0].data)); leaveScope(); (yyval.data) = NULL; }
#line 1800 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 96 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatement(); }
#line 1806 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 97 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatementWithExpression((yyvsp[0].data)); }
#line 1812 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 98 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 1818 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 99 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack), NULL); }
#line 1824 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 103 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[-1].data)); }
#line 1830 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 104 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-3].stack), (yyvsp[-1].data)); }
#line 1836 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 108 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); }
#line 1842 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 109 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 1848 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 110 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-2].stack); }
#line 1854 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 114 "epython.y" /* yacc.c:1646  */
    { enterScope(); (yyval.stack)=getNewStack(); }
#line 1860 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 115 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifier((yyval.stack), (yyvsp[0].string)); appendArgument((yyvsp[0].string)); }
#line 1866 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 116 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifierAssgnExpression((yyval.stack), (yyvsp[-2].string), (yyvsp[0].data)); appendArgument((yyvsp[-2].string)); }
#line 1872 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 117 "epython.y" /* yacc.c:1646  */
    { pushIdentifier((yyvsp[-2].stack), (yyvsp[0].string)); (yyval.stack)=(yyvsp[-2].stack); appendArgument((yyvsp[0].string)); }
#line 1878 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 118 "epython.y" /* yacc.c:1646  */
    { pushIdentifierAssgnExpression((yyvsp[-4].stack), (yyvsp[-2].string), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-4].stack); appendArgument((yyvsp[-2].string)); }
#line 1884 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 122 "epython.y" /* yacc.c:1646  */
    { enterFunction((yyvsp[0].string)); (yyval.string)=(yyvsp[0].string); }
#line 1890 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 125 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 1896 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 128 "epython.y" /* yacc.c:1646  */
    { enterScope(); }
#line 1902 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 131 "epython.y" /* yacc.c:1646  */
    { leaveScope(); }
#line 1908 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 134 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=0; }
#line 1914 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 135 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=1; }
#line 1920 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 136 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=2; }
#line 1926 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 137 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=3; }
#line 1932 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 141 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=0; }
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 142 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=1; }
#line 1944 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 143 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=2; }
#line 1950 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 144 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=3; }
#line 1956 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 145 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=4; }
#line 1962 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 146 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=5; }
#line 1968 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 147 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=6; }
#line 1974 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 150 "epython.y" /* yacc.c:1646  */
    { (yyval.string)=(yyvsp[0].string); enterScope(); addVariableIfNeeded((yyvsp[0].string)); }
#line 1980 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 154 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1986 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 155 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1992 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 156 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 1998 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 160 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2004 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 161 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNotExpression((yyvsp[0].data)); }
#line 2010 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 165 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2016 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 166 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createOrExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2022 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 169 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2028 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 170 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAndExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2034 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 174 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2040 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 175 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createEqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2046 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 176 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2052 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 177 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2058 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 181 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2064 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 182 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2070 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 183 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2076 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 184 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2082 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 185 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2088 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 189 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2094 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 190 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAddExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2100 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 191 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSubExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2106 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 195 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2112 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 196 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createMulExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2118 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 197 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2124 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 198 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2130 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 199 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createModExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2136 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 200 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createPowExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2142 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 201 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSqrtExpression((yyvsp[-1].data)); }
#line 2148 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 202 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinExpression((yyvsp[-1].data)); }
#line 2154 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 203 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosExpression((yyvsp[-1].data)); }
#line 2160 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 204 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanExpression((yyvsp[-1].data)); }
#line 2166 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 205 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createASinExpression((yyvsp[-1].data)); }
#line 2172 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 206 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createACosExpression((yyvsp[-1].data)); }
#line 2178 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 207 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createATanExpression((yyvsp[-1].data)); }
#line 2184 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 208 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinHExpression((yyvsp[-1].data)); }
#line 2190 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 209 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosHExpression((yyvsp[-1].data)); }
#line 2196 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 210 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanHExpression((yyvsp[-1].data)); }
#line 2202 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 211 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorExpression((yyvsp[-1].data)); }
#line 2208 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 212 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCeilExpression((yyvsp[-1].data)); }
#line 2214 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 213 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2220 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 214 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLogExpression((yyvsp[-1].data)); }
#line 2226 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 215 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLog10Expression((yyvsp[-1].data)); }
#line 2232 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 216 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLenExpression((yyvsp[-1].data)); }
#line 2238 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 217 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createArrayExpression((yyvsp[-1].stack), NULL); }
#line 2244 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 218 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createArrayExpression((yyvsp[-3].stack), (yyvsp[0].data)); }
#line 2250 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 219 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement("rtl_input", NULL, NULL); }
#line 2256 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 220 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement("rtl_inputprint", NULL, (yyvsp[-1].data)); }
#line 2262 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 224 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 2268 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 225 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); }
#line 2274 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 229 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2280 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 230 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2286 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 231 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierExpression((yyvsp[0].string)); }
#line 2292 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 232 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierArrayAccessExpression((yyvsp[-1].string), (yyvsp[0].stack)); }
#line 2298 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 233 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 2304 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 234 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack), NULL); }
#line 2310 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 238 "epython.y" /* yacc.c:1646  */
    { (yyval.string) = malloc(strlen((yyvsp[0].string))+1); strcpy((yyval.string), (yyvsp[0].string)); }
#line 2316 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 242 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[0].integer)); }
#line 2322 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 243 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[0].real)); }
#line 2328 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 244 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCoreIdExpression(); }
#line 2334 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 245 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNumCoresExpression(); }
#line 2340 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 246 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRandomExpression(); }
#line 2346 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 247 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRandomExpression(); }
#line 2352 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 248 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[-1].integer) * (yyvsp[0].integer)); }
#line 2358 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 249 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[-1].integer) * (yyvsp[0].real)); }
#line 2364 "parser.c" /* yacc.c:1646  */
    break;

  case 121:
#line 250 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createStringExpression((yyvsp[0].string)); }
#line 2370 "parser.c" /* yacc.c:1646  */
    break;

  case 122:
#line 251 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(1); }
#line 2376 "parser.c" /* yacc.c:1646  */
    break;

  case 123:
#line 252 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(0); }
#line 2382 "parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 253 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNoneExpression(); }
#line 2388 "parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 257 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2394 "parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 258 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = -1; }
#line 2400 "parser.c" /* yacc.c:1646  */
    break;


#line 2404 "parser.c" /* yacc.c:1646  */
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
#line 261 "epython.y" /* yacc.c:1906  */

