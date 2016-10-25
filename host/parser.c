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
    IS = 325,
    NOT = 326,
    SQRT = 327,
    SIN = 328,
    COS = 329,
    TAN = 330,
    ASIN = 331,
    ACOS = 332,
    ATAN = 333,
    SINH = 334,
    COSH = 335,
    TANH = 336,
    FLOOR = 337,
    CEIL = 338,
    LOG = 339,
    LOG10 = 340,
    STR = 341,
    LPAREN = 342,
    RPAREN = 343,
    SLBRACE = 344,
    SRBRACE = 345,
    TRUE = 346,
    FALSE = 347,
    LEN = 348,
    ASSGN = 349,
    POW = 350
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
#define IS 325
#define NOT 326
#define SQRT 327
#define SIN 328
#define COS 329
#define TAN 330
#define ASIN 331
#define ACOS 332
#define ATAN 333
#define SINH 334
#define COSH 335
#define TANH 336
#define FLOOR 337
#define CEIL 338
#define LOG 339
#define LOG10 340
#define STR 341
#define LPAREN 342
#define RPAREN 343
#define SLBRACE 344
#define SRBRACE 345
#define TRUE 346
#define FALSE 347
#define LEN 348
#define ASSGN 349
#define POW 350

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

#line 325 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 340 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  88
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   645

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  96
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  130
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  284

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   350

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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    60,    60,    63,    64,    68,    69,    70,    74,    75,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   108,   109,   113,   114,
     115,   119,   120,   121,   122,   123,   127,   130,   133,   136,
     139,   140,   141,   142,   146,   147,   148,   149,   150,   151,
     152,   155,   159,   160,   161,   165,   166,   170,   171,   174,
     175,   179,   180,   181,   182,   183,   184,   188,   189,   190,
     191,   192,   196,   197,   198,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   215,   216,
     217,   218,   219,   220,   221,   222,   223,   224,   225,   229,
     230,   234,   235,   236,   237,   238,   242,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   255,   256,   257,   261,
     262
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
  "EPY_I_SEND", "EPY_I_RECV", "RANDOM", "EPY_I_SYNC", "EPY_I_BCAST",
  "EPY_I_REDUCE", "EPY_I_SUM", "EPY_I_MIN", "EPY_I_MAX", "EPY_I_PROD",
  "EPY_I_SENDRECV", "TOFROM", "ADD", "SUB", "EPY_I_ISHOST",
  "EPY_I_ISDEVICE", "COLON", "DEF", "RET", "NONE", "FILESTART", "IN",
  "ADDADD", "SUBSUB", "MULMUL", "DIVDIV", "MODMOD", "POWPOW",
  "FLOORDIVFLOORDIV", "FLOORDIV", "MULT", "DIV", "MOD", "AND", "OR", "NEQ",
  "LEQ", "GEQ", "LT", "GT", "EQ", "IS", "NOT", "SQRT", "SIN", "COS", "TAN",
  "ASIN", "ACOS", "ATAN", "SINH", "COSH", "TANH", "FLOOR", "CEIL", "LOG",
  "LOG10", "STR", "LPAREN", "RPAREN", "SLBRACE", "SRBRACE", "TRUE",
  "FALSE", "LEN", "ASSGN", "POW", "$accept", "program", "lines", "line",
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
     345,   346,   347,   348,   349,   350
};
# endif

#define YYPACT_NINF -144

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-144)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     522,  -144,  -144,     5,     5,   -67,   305,   305,     5,   305,
     305,   305,     5,  -144,   305,    65,   305,     5,   305,    23,
     522,  -144,    28,   598,   -46,   116,   -13,     2,    -9,  -144,
    -144,  -144,  -144,  -144,     1,  -144,  -144,  -144,  -144,  -144,
     396,    17,    19,    36,    38,    40,    49,    50,    51,    54,
      57,    63,    66,    67,    68,    71,   305,   305,  -144,  -144,
      74,    69,    89,   100,   -42,   -19,   -10,   -21,  -144,   -12,
    -144,   109,   119,   124,  -144,  -144,   121,   157,   158,   159,
    -144,  -144,  -144,  -144,   305,   136,  -144,  -144,  -144,  -144,
    -144,  -144,     5,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
     305,   305,   214,   -60,   305,   305,   305,  -144,    91,    89,
      39,    39,    39,    39,    39,    39,    39,    39,    39,    39,
      39,    39,    39,    39,    39,    92,  -144,    -1,   305,   175,
     396,   396,   115,   115,   115,   115,   115,   115,   115,   115,
     115,    39,    39,    39,    39,    39,   305,    94,  -144,  -144,
     175,   305,   560,   305,   305,   305,   163,   305,     4,   117,
       9,  -144,    95,   122,  -144,   305,   305,  -144,     0,     3,
    -144,   125,   128,   133,   134,   135,   137,   138,   139,   140,
     142,   144,   145,   146,   151,   152,  -144,   305,   153,   155,
     216,  -144,   100,   -42,   -19,   -19,   -19,   -10,   -10,   -10,
     -10,   -21,   -21,  -144,  -144,  -144,  -144,  -144,    11,  -144,
     199,  -144,    55,  -144,  -144,   227,     5,   228,     5,   205,
     305,   305,  -144,  -144,   232,   161,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,    39,  -144,  -144,   522,  -144,
     175,   207,   305,  -144,     5,  -144,     5,   160,   175,  -144,
    -144,  -144,   165,  -144,  -144,   484,  -144,   175,   219,  -144,
    -144,   305,  -144,  -144,  -144,  -144,  -144,   175,  -144,   103,
     221,  -144,   175,  -144
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   116,     7,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    31,     0,     0,     0,     0,    33,     0,
       2,     3,     6,     9,     0,     0,     0,     0,     0,   117,
     118,   125,   119,   120,   121,   129,   130,    75,    76,   128,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   126,   127,
       0,     0,    65,    67,    69,    71,    77,    82,    85,   113,
     111,     0,     0,     0,    61,    29,     0,     0,     0,     0,
      50,    51,    52,    53,     0,     0,    46,    34,     1,     4,
       5,     8,    41,    54,    55,    56,    57,    58,    59,    60,
      38,     0,     0,     0,     0,     0,     0,    30,     0,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,   114,   123,   124,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,    39,     0,     0,    26,     0,     0,    28,     0,     0,
     122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,     0,   107,     0,
       0,    23,    68,    70,    73,    72,    74,    80,    81,    79,
      78,    83,    84,    88,    86,    87,    89,    90,     0,    18,
       0,    22,    19,    11,    10,     0,     0,     0,     0,     0,
       0,     0,    35,    36,     0,     0,    27,    15,    16,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   104,   105,   103,   110,     0,   106,    48,     0,   115,
       0,     0,     0,    21,     0,    14,     0,    44,     0,    43,
      40,    24,     0,    37,   108,     0,    17,     0,     0,    13,
      12,     0,    32,    25,    49,    47,    20,     0,    45,    62,
       0,    64,     0,    63
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -144,  -144,    20,   -18,   -17,  -144,   201,   126,  -144,  -144,
    -143,  -144,  -144,  -144,  -144,  -144,    -8,    -6,   235,   147,
     148,   -61,   -27,   -11,    27,   -59,    13,    52,  -144
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    19,    20,    21,    22,    23,   103,   160,   158,    24,
     191,   248,   275,    84,   104,    73,   253,   126,    62,    63,
      64,    65,    66,    67,   127,    68,    69,    70,    71
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      61,    72,    89,    75,    76,    77,    91,   209,    79,   212,
      85,     1,    87,    25,   187,   187,    26,    27,   187,   218,
      28,    74,   132,    88,   221,    78,   221,   133,   134,   165,
      86,   139,   140,    25,   166,    90,    25,   141,   142,   143,
     144,    92,    29,    30,    31,     1,   135,   136,   137,   138,
     125,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   185,    32,    33,   251,   252,
      34,   194,   195,   196,   145,   146,   105,   101,   156,   107,
      35,    36,   203,   204,   205,   206,   207,    39,   108,   188,
     227,   106,   219,   228,   161,   162,   164,   222,   167,   249,
      80,    81,    82,    83,   110,   159,   111,   266,   197,   198,
     199,   200,   148,   149,   129,   272,   280,   252,    29,    30,
      31,     1,   189,   112,   276,   113,    56,   114,   201,   202,
      58,    59,   168,   169,   279,   211,   115,   116,   117,   283,
     161,   118,    32,    33,   119,   210,    34,   213,   214,   215,
     120,   217,   130,   121,   122,   123,    35,    36,   124,   225,
     226,   128,   131,    39,   150,    25,   152,    93,    94,    95,
      96,    97,    98,    99,   151,   153,   157,   154,   155,   170,
     186,   244,   190,   165,   216,   223,   264,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,   100,    57,   101,    58,    59,    60,   224,
     102,   220,   245,   229,   259,   260,   230,    29,    30,    31,
       1,   231,   232,   233,   247,   234,   235,   236,   237,   255,
     238,   257,   239,   240,   241,    29,    30,    31,   163,   242,
     243,    32,    33,   246,   250,    34,   268,    89,   254,   256,
     258,   263,   267,   273,   271,    35,    36,    37,    38,    32,
      33,    25,    39,    34,   277,   278,   282,   269,   265,   270,
     147,   281,   208,    35,    36,   109,   262,   192,    25,   193,
      39,     0,     0,     0,     0,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,     0,    57,     0,    58,    59,    60,    29,    30,
      31,     1,     0,     0,     0,     0,     0,     0,     0,     0,
     261,     0,     0,    58,    59,     0,     0,     0,     0,     0,
       0,     0,    32,    33,     0,     0,    34,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    35,    36,    37,    38,
       0,     0,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,     0,    57,     0,    58,    59,    60,    29,
      30,    31,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    32,    33,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    35,    36,    37,
      38,     0,     0,     0,    39,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,     0,    57,     0,    58,    59,    60,
       1,     2,     0,   274,     3,     4,     5,     0,     6,     0,
       7,     8,     0,     0,     0,     0,     0,     9,     0,    10,
       0,     0,     0,    11,    12,     0,    13,    14,    15,     0,
       0,     0,     0,    16,     0,     0,     0,     0,     1,     2,
      17,    18,     3,     4,     5,     0,     6,     0,     7,     8,
       0,     0,     0,     0,     0,     9,     0,    10,     0,     0,
       0,    11,    12,     0,    13,    14,    15,     0,     0,     0,
       0,    16,     0,     0,     0,     0,     1,   190,    17,    18,
       3,     4,     5,     0,     6,     0,     7,     8,     0,     0,
       0,     0,     0,     9,     0,    10,     0,     0,     0,    11,
      12,     0,    13,    14,    15,     0,     0,     0,     0,    16,
       0,     0,     0,     0,     1,     0,    17,    18,     3,     4,
       5,     0,     6,     0,     7,     8,     0,     0,     0,     0,
       0,     9,     0,    10,     0,     0,     0,    11,    12,     0,
      13,    14,    15,     0,     0,     0,     0,    16,     0,     0,
       0,     0,     0,     0,    17,    18
};

static const yytype_int16 yycheck[] =
{
       6,     7,    20,     9,    10,    11,    23,   150,    14,   152,
      16,     6,    18,     0,    15,    15,     3,     4,    15,    15,
      87,     8,    64,     0,    15,    12,    15,    69,    70,    89,
      17,    41,    42,    20,    94,     7,    23,    58,    59,    60,
      61,    87,     3,     4,     5,     6,    65,    66,    67,    68,
      56,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,    27,    28,    13,    14,
      31,   132,   133,   134,    95,    87,    89,    89,    84,    88,
      41,    42,   141,   142,   143,   144,   145,    48,    87,    90,
      90,    89,    88,    90,   100,   101,   102,    88,   104,    88,
      35,    36,    37,    38,    87,    92,    87,   250,   135,   136,
     137,   138,     3,     4,    45,   258,    13,    14,     3,     4,
       5,     6,   128,    87,   267,    87,    87,    87,   139,   140,
      91,    92,   105,   106,   277,   152,    87,    87,    87,   282,
     146,    87,    27,    28,    87,   151,    31,   153,   154,   155,
      87,   157,    63,    87,    87,    87,    41,    42,    87,   165,
     166,    87,    62,    48,    45,   152,    45,    51,    52,    53,
      54,    55,    56,    57,    50,    18,    40,    19,    19,    88,
      88,   187,     7,    89,    21,    90,   245,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    87,    89,    89,    91,    92,    93,    87,
      94,    94,    59,    88,   220,   221,    88,     3,     4,     5,
       6,    88,    88,    88,     8,    88,    88,    88,    88,   216,
      88,   218,    88,    88,    88,     3,     4,     5,    24,    88,
      88,    27,    28,    88,    45,    31,   252,   265,    21,    21,
      45,    90,    45,    88,    94,    41,    42,    43,    44,    27,
      28,   248,    48,    31,    45,   271,    45,   254,   248,   256,
      69,   279,   146,    41,    42,    40,   224,   130,   265,   131,
      48,    -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    -1,    89,    -1,    91,    92,    93,     3,     4,
       5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      88,    -1,    -1,    91,    92,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    28,    -1,    -1,    31,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,    44,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    -1,    89,    -1,    91,    92,    93,     3,
       4,     5,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    28,    -1,    -1,    31,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,    43,
      44,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    -1,    89,    -1,    91,    92,    93,
       6,     7,    -1,     9,    10,    11,    12,    -1,    14,    -1,
      16,    17,    -1,    -1,    -1,    -1,    -1,    23,    -1,    25,
      -1,    -1,    -1,    29,    30,    -1,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    -1,    -1,     6,     7,
      46,    47,    10,    11,    12,    -1,    14,    -1,    16,    17,
      -1,    -1,    -1,    -1,    -1,    23,    -1,    25,    -1,    -1,
      -1,    29,    30,    -1,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    -1,    -1,    -1,    -1,     6,     7,    46,    47,
      10,    11,    12,    -1,    14,    -1,    16,    17,    -1,    -1,
      -1,    -1,    -1,    23,    -1,    25,    -1,    -1,    -1,    29,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      -1,    -1,    -1,    -1,     6,    -1,    46,    47,    10,    11,
      12,    -1,    14,    -1,    16,    17,    -1,    -1,    -1,    -1,
      -1,    23,    -1,    25,    -1,    -1,    -1,    29,    30,    -1,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    47
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    10,    11,    12,    14,    16,    17,    23,
      25,    29,    30,    32,    33,    34,    39,    46,    47,    97,
      98,    99,   100,   101,   105,   122,   122,   122,    87,     3,
       4,     5,    27,    28,    31,    41,    42,    43,    44,    48,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    89,    91,    92,
      93,   113,   114,   115,   116,   117,   118,   119,   121,   122,
     123,   124,   113,   111,   122,   113,   113,   113,   122,   113,
      35,    36,    37,    38,   109,   113,   122,   113,     0,    99,
       7,   100,    87,    51,    52,    53,    54,    55,    56,    57,
      87,    89,    94,   102,   110,    89,    89,    88,    87,   114,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,   113,   113,   120,    87,    45,
      63,    62,    64,    69,    70,    65,    66,    67,    68,    41,
      42,    58,    59,    60,    61,    95,    87,   102,     3,     4,
      45,    50,    45,    18,    19,    19,   113,    40,   104,   122,
     103,   113,   113,    24,   113,    89,    94,   113,   120,   120,
      88,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,    88,    15,    90,   113,
       7,   106,   115,   116,   117,   117,   117,   118,   118,   118,
     118,   119,   119,   121,   121,   121,   121,   121,   103,   106,
     113,   100,   106,   113,   113,   113,    21,   113,    15,    88,
      94,    15,    88,    90,    87,   113,   113,    90,    90,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,   113,    59,    88,     8,   107,    88,
      45,    13,    14,   112,    21,   122,    21,   122,    45,   113,
     113,    88,   123,    90,   121,    98,   106,    45,   113,   122,
     122,    94,   106,    88,     9,   108,   106,    45,   113,   106,
      13,   112,    45,   106
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    96,    97,    98,    98,    99,    99,    99,   100,   100,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   102,   102,   103,   103,
     103,   104,   104,   104,   104,   104,   105,   106,   107,   108,
     109,   109,   109,   109,   110,   110,   110,   110,   110,   110,
     110,   111,   112,   112,   112,   113,   113,   114,   114,   115,
     115,   116,   116,   116,   116,   116,   116,   117,   117,   117,
     117,   117,   118,   118,   118,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   120,
     120,   121,   121,   121,   121,   121,   122,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   124,
     124
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     2,     1,
       4,     4,     6,     6,     5,     5,     5,     6,     4,     4,
       7,     5,     4,     4,     5,     6,     3,     4,     3,     2,
       3,     1,     6,     1,     2,     4,     3,     4,     0,     1,
       3,     0,     1,     3,     3,     5,     2,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     7,     5,     1,     2,     1,     3,     1,
       3,     1,     3,     3,     3,     1,     1,     1,     3,     3,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       3,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,     5,     1,
       3,     1,     3,     1,     2,     4,     1,     1,     1,     1,
       1,     1,     3,     2,     2,     1,     1,     1,     1,     1,
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
#line 1698 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 64 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1704 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 68 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[-1].data); }
#line 1710 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 69 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[0].data); }
#line 1716 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 70 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = NULL; }
#line 1722 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 74 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1728 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 79 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendRecvStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1734 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 80 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1740 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 81 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSendRecvStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1746 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 82 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendBcastStatement((yyvsp[-4].data), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1752 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendReductionStatement((yyvsp[-3].uchar), (yyvsp[-2].data), (yyvsp[0].string)); }
#line 1758 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 84 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareArray((yyvsp[-3].string), (yyvsp[-1].stack), 0); }
#line 1764 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 85 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendDeclareArray((yyvsp[-3].string), (yyvsp[-1].stack), 1); }
#line 1770 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 86 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendForStatement((yyvsp[-4].string), (yyvsp[-2].data), (yyvsp[0].data)); leaveScope(); }
#line 1776 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 87 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendWhileStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1782 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 88 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1788 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 89 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1794 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 90 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 1800 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 91 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1806 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 92 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1812 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 93 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendInputStatement((yyvsp[-4].string)); }
#line 1818 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 94 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendInputStringStatement((yyvsp[-1].data), (yyvsp[-5].string)); }
#line 1824 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 95 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1830 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 96 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendArraySetStatement((yyvsp[-3].string), (yyvsp[-2].stack), (yyvsp[0].data)); }
#line 1836 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 97 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetWithOperatorStatement((yyvsp[-2].string), (yyvsp[0].data), (yyvsp[-1].uchar)); }
#line 1842 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 98 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendPrintStatement((yyvsp[0].data)); }
#line 1848 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 99 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendStopStatement(); }
#line 1854 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 100 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSyncStatement(); }
#line 1860 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 101 "epython.y" /* yacc.c:1646  */
    { appendNewFunctionStatement((yyvsp[-5].string), (yyvsp[-3].stack), (yyvsp[0].data)); leaveScope(); (yyval.data) = NULL; }
#line 1866 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 102 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatement(); }
#line 1872 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 103 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatementWithExpression((yyvsp[0].data)); }
#line 1878 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 104 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 1884 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 108 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[-1].data)); }
#line 1890 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 109 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-3].stack), (yyvsp[-1].data)); }
#line 1896 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 113 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); }
#line 1902 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 114 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 1908 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 115 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-2].stack); }
#line 1914 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 119 "epython.y" /* yacc.c:1646  */
    { enterScope(); (yyval.stack)=getNewStack(); }
#line 1920 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 120 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifier((yyval.stack), (yyvsp[0].string)); appendArgument((yyvsp[0].string)); }
#line 1926 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 121 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifierAssgnExpression((yyval.stack), (yyvsp[-2].string), (yyvsp[0].data)); appendArgument((yyvsp[-2].string)); }
#line 1932 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 122 "epython.y" /* yacc.c:1646  */
    { pushIdentifier((yyvsp[-2].stack), (yyvsp[0].string)); (yyval.stack)=(yyvsp[-2].stack); appendArgument((yyvsp[0].string)); }
#line 1938 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 123 "epython.y" /* yacc.c:1646  */
    { pushIdentifierAssgnExpression((yyvsp[-4].stack), (yyvsp[-2].string), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-4].stack); appendArgument((yyvsp[-2].string)); }
#line 1944 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 127 "epython.y" /* yacc.c:1646  */
    { enterFunction((yyvsp[0].string)); (yyval.string)=(yyvsp[0].string); }
#line 1950 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 130 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 1956 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 133 "epython.y" /* yacc.c:1646  */
    { enterScope(); }
#line 1962 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 136 "epython.y" /* yacc.c:1646  */
    { leaveScope(); }
#line 1968 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 139 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=0; }
#line 1974 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 140 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=1; }
#line 1980 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 141 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=2; }
#line 1986 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 142 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=3; }
#line 1992 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 146 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=0; }
#line 1998 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 147 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=1; }
#line 2004 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 148 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=2; }
#line 2010 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 149 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=3; }
#line 2016 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 150 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=4; }
#line 2022 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 151 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=5; }
#line 2028 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 152 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=6; }
#line 2034 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 155 "epython.y" /* yacc.c:1646  */
    { (yyval.string)=(yyvsp[0].string); enterScope(); addVariableIfNeeded((yyvsp[0].string)); }
#line 2040 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 159 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2046 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 160 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 2052 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 161 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 2058 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 165 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2064 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 166 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNotExpression((yyvsp[0].data)); }
#line 2070 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 170 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2076 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 171 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createOrExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2082 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 174 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2088 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 175 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAndExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2094 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 179 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2100 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 180 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createEqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2106 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 181 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2112 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 182 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2118 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 183 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsHostExpression(); }
#line 2124 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 184 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsDeviceExpression(); }
#line 2130 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 188 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2136 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 189 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2142 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 190 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2148 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 191 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2154 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 192 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2160 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 196 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2166 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 197 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAddExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2172 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 198 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSubExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2178 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 202 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2184 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 203 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createMulExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2190 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 204 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2196 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 205 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2202 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 206 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createModExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2208 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 207 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createPowExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2214 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 208 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSqrtExpression((yyvsp[-1].data)); }
#line 2220 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 209 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinExpression((yyvsp[-1].data)); }
#line 2226 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 210 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosExpression((yyvsp[-1].data)); }
#line 2232 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 211 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanExpression((yyvsp[-1].data)); }
#line 2238 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 212 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createASinExpression((yyvsp[-1].data)); }
#line 2244 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 213 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createACosExpression((yyvsp[-1].data)); }
#line 2250 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 214 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createATanExpression((yyvsp[-1].data)); }
#line 2256 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 215 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSinHExpression((yyvsp[-1].data)); }
#line 2262 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 216 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCosHExpression((yyvsp[-1].data)); }
#line 2268 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 217 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createTanHExpression((yyvsp[-1].data)); }
#line 2274 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 218 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorExpression((yyvsp[-1].data)); }
#line 2280 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 219 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCeilExpression((yyvsp[-1].data)); }
#line 2286 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 220 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2292 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 221 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLogExpression((yyvsp[-1].data)); }
#line 2298 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 222 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLog10Expression((yyvsp[-1].data)); }
#line 2304 "parser.c" /* yacc.c:1646  */
    break;

  case 106:
#line 223 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLenExpression((yyvsp[-1].data)); }
#line 2310 "parser.c" /* yacc.c:1646  */
    break;

  case 107:
#line 224 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createArrayExpression((yyvsp[-1].stack), NULL); }
#line 2316 "parser.c" /* yacc.c:1646  */
    break;

  case 108:
#line 225 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createArrayExpression((yyvsp[-3].stack), (yyvsp[0].data)); }
#line 2322 "parser.c" /* yacc.c:1646  */
    break;

  case 109:
#line 229 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 2328 "parser.c" /* yacc.c:1646  */
    break;

  case 110:
#line 230 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); }
#line 2334 "parser.c" /* yacc.c:1646  */
    break;

  case 111:
#line 234 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2340 "parser.c" /* yacc.c:1646  */
    break;

  case 112:
#line 235 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2346 "parser.c" /* yacc.c:1646  */
    break;

  case 113:
#line 236 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierExpression((yyvsp[0].string)); }
#line 2352 "parser.c" /* yacc.c:1646  */
    break;

  case 114:
#line 237 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierArrayAccessExpression((yyvsp[-1].string), (yyvsp[0].stack)); }
#line 2358 "parser.c" /* yacc.c:1646  */
    break;

  case 115:
#line 238 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 2364 "parser.c" /* yacc.c:1646  */
    break;

  case 116:
#line 242 "epython.y" /* yacc.c:1646  */
    { (yyval.string) = malloc(strlen((yyvsp[0].string))+1); strcpy((yyval.string), (yyvsp[0].string)); }
#line 2370 "parser.c" /* yacc.c:1646  */
    break;

  case 117:
#line 246 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[0].integer)); }
#line 2376 "parser.c" /* yacc.c:1646  */
    break;

  case 118:
#line 247 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[0].real)); }
#line 2382 "parser.c" /* yacc.c:1646  */
    break;

  case 119:
#line 248 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createCoreIdExpression(); }
#line 2388 "parser.c" /* yacc.c:1646  */
    break;

  case 120:
#line 249 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNumCoresExpression(); }
#line 2394 "parser.c" /* yacc.c:1646  */
    break;

  case 121:
#line 250 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRandomExpression(); }
#line 2400 "parser.c" /* yacc.c:1646  */
    break;

  case 122:
#line 251 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRandomExpression(); }
#line 2406 "parser.c" /* yacc.c:1646  */
    break;

  case 123:
#line 252 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[-1].integer) * (yyvsp[0].integer)); }
#line 2412 "parser.c" /* yacc.c:1646  */
    break;

  case 124:
#line 253 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[-1].integer) * (yyvsp[0].real)); }
#line 2418 "parser.c" /* yacc.c:1646  */
    break;

  case 125:
#line 254 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createStringExpression((yyvsp[0].string)); }
#line 2424 "parser.c" /* yacc.c:1646  */
    break;

  case 126:
#line 255 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(1); }
#line 2430 "parser.c" /* yacc.c:1646  */
    break;

  case 127:
#line 256 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(0); }
#line 2436 "parser.c" /* yacc.c:1646  */
    break;

  case 128:
#line 257 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNoneExpression(); }
#line 2442 "parser.c" /* yacc.c:1646  */
    break;

  case 129:
#line 261 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2448 "parser.c" /* yacc.c:1646  */
    break;

  case 130:
#line 262 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = -1; }
#line 2454 "parser.c" /* yacc.c:1646  */
    break;


#line 2458 "parser.c" /* yacc.c:1646  */
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
#line 265 "epython.y" /* yacc.c:1906  */

