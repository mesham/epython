/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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
#define YYBISON_VERSION "3.0.4"

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
extern char * fn_decorator;
void yyerror(char const*);
int yylex(void);

void yyerror (char const *msg) {
	fprintf(stderr, "%s at line %d of file %s\n", msg, line_num, parsing_filename);
	exit(0);
}

#line 87 "parser.c" /* yacc.c:339  */

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
    QUIT = 268,
    ELSE = 269,
    ELIF = 270,
    COMMA = 271,
    WHILE = 272,
    PASS = 273,
    AT = 274,
    FOR = 275,
    TO = 276,
    FROM = 277,
    NEXT = 278,
    GOTO = 279,
    PRINT = 280,
    INPUT = 281,
    IF = 282,
    NATIVE = 283,
    ADD = 284,
    SUB = 285,
    COLON = 286,
    DEF = 287,
    RET = 288,
    NONE = 289,
    FILESTART = 290,
    IN = 291,
    ADDADD = 292,
    SUBSUB = 293,
    MULMUL = 294,
    DIVDIV = 295,
    MODMOD = 296,
    POWPOW = 297,
    FLOORDIVFLOORDIV = 298,
    FLOORDIV = 299,
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
    IS = 311,
    NOT = 312,
    STR = 313,
    ID = 314,
    SYMBOL = 315,
    ALIAS = 316,
    LPAREN = 317,
    RPAREN = 318,
    SLBRACE = 319,
    SRBRACE = 320,
    TRUE = 321,
    FALSE = 322,
    ASSGN = 323,
    POW = 324
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
#define QUIT 268
#define ELSE 269
#define ELIF 270
#define COMMA 271
#define WHILE 272
#define PASS 273
#define AT 274
#define FOR 275
#define TO 276
#define FROM 277
#define NEXT 278
#define GOTO 279
#define PRINT 280
#define INPUT 281
#define IF 282
#define NATIVE 283
#define ADD 284
#define SUB 285
#define COLON 286
#define DEF 287
#define RET 288
#define NONE 289
#define FILESTART 290
#define IN 291
#define ADDADD 292
#define SUBSUB 293
#define MULMUL 294
#define DIVDIV 295
#define MODMOD 296
#define POWPOW 297
#define FLOORDIVFLOORDIV 298
#define FLOORDIV 299
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
#define IS 311
#define NOT 312
#define STR 313
#define ID 314
#define SYMBOL 315
#define ALIAS 316
#define LPAREN 317
#define RPAREN 318
#define SLBRACE 319
#define SRBRACE 320
#define TRUE 321
#define FALSE 322
#define ASSGN 323
#define POW 324

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 22 "epython.y" /* yacc.c:355  */

	int integer;
	unsigned char uchar;
	float real;	
	struct memorycontainer * data;
	char *string;
	struct stack_t * stack;

#line 274 "parser.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 291 "parser.c" /* yacc.c:358  */

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
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   378

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  70
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  207

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   324

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
      65,    66,    67,    68,    69
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    61,    61,    64,    65,    69,    70,    71,    75,    76,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   104,   105,   109,   110,   111,   115,   116,   117,   118,
     119,   123,   127,   130,   133,   136,   137,   138,   139,   140,
     141,   142,   145,   149,   150,   151,   155,   156,   160,   161,
     164,   165,   169,   170,   171,   172,   176,   177,   178,   179,
     180,   184,   185,   186,   190,   191,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   204,   205,   209,   210,   211,
     212,   213,   214,   215,   216,   220,   224,   225,   226,   227,
     228,   229,   230,   231,   235,   236
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INTEGER", "REAL", "STRING",
  "IDENTIFIER", "NEWLINE", "INDENT", "OUTDENT", "DIM", "SDIM", "EXIT",
  "QUIT", "ELSE", "ELIF", "COMMA", "WHILE", "PASS", "AT", "FOR", "TO",
  "FROM", "NEXT", "GOTO", "PRINT", "INPUT", "IF", "NATIVE", "ADD", "SUB",
  "COLON", "DEF", "RET", "NONE", "FILESTART", "IN", "ADDADD", "SUBSUB",
  "MULMUL", "DIVDIV", "MODMOD", "POWPOW", "FLOORDIVFLOORDIV", "FLOORDIV",
  "MULT", "DIV", "MOD", "AND", "OR", "NEQ", "LEQ", "GEQ", "LT", "GT", "EQ",
  "IS", "NOT", "STR", "ID", "SYMBOL", "ALIAS", "LPAREN", "RPAREN",
  "SLBRACE", "SRBRACE", "TRUE", "FALSE", "ASSGN", "POW", "$accept",
  "program", "lines", "line", "statements", "statement", "arrayaccessor",
  "fncallargs", "fndeclarationargs", "fn_entry", "codeblock",
  "indent_rule", "outdent_rule", "opassgn", "declareident", "elifblock",
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
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324
};
# endif

#define YYPACT_NINF -96

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-96)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     118,   -96,   -96,   -41,     7,   178,   178,   -96,    52,    52,
     178,   178,    52,    52,   178,    13,    72,   118,   -96,    70,
     317,    33,   179,    35,    36,   -96,   -96,   -96,    34,    52,
     -96,   -96,   -96,   220,    44,    47,    54,   178,   178,   -96,
     -96,    90,    73,    75,   -16,    50,    -1,    39,   -96,   -19,
     -96,    48,    95,   -96,    92,   -96,   -96,    98,    82,   -96,
     -96,    52,   -96,   -96,   -96,   -96,    52,   -96,   -96,   -96,
     -96,   -96,   -96,   -96,   178,   178,   178,    10,   178,   -96,
     -96,   136,    85,    73,   178,    52,    52,    69,   -96,   -12,
     127,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   260,   260,   260,   260,   260,   178,    84,   -96,
     -96,   127,   178,   285,   178,   133,    -8,    86,    -4,   -96,
      87,   -96,   178,   178,   -96,   -96,    96,   178,    97,   100,
     104,   -96,   178,   110,   150,   -96,    75,   -16,    50,    50,
      50,    -1,    -1,    -1,    -1,    39,    39,   -96,   -96,   -96,
     -96,   -96,    -3,   -96,   137,   -96,    51,     1,   178,    52,
     138,   178,   178,   -96,   -96,   106,   -96,   -96,     4,   -96,
     -96,   -96,   -96,   260,   -96,   118,   -96,   127,   141,   178,
     -96,   -96,   112,   105,   127,   -96,   -96,   -96,   -96,   -96,
      29,   -96,   127,   147,   -96,   178,   -96,   -96,   -96,   -96,
     127,   -96,    66,   149,   -96,   127,   -96
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    95,     7,     0,     0,     0,     0,    28,     0,     0,
       0,     0,     0,     0,    24,     0,     0,     2,     3,     6,
       9,     0,     0,     0,     0,    96,    97,   100,     0,     0,
     104,   105,   103,     0,     0,     0,     0,     0,     0,   101,
     102,     0,    56,    58,    60,    62,    66,    71,    74,    89,
      87,     0,     0,    29,     0,    52,    20,     0,     0,    41,
      25,     0,     1,     4,     5,     8,    36,    45,    46,    47,
      48,    49,    50,    51,    33,     0,     0,     0,     0,    21,
      22,     0,     0,    57,     0,     0,     0,     0,    85,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,    90,    98,
      99,     0,     0,     0,    33,     0,     0,    37,     0,    34,
       0,    17,     0,     0,    19,    83,     0,    33,     0,     0,
       0,    88,     0,    81,     0,    16,    59,    61,    64,    63,
      65,    69,    70,    68,    67,    72,    73,    77,    75,    76,
      78,    79,     0,    11,     0,    15,    12,     0,     0,     0,
       0,     0,     0,    26,    31,     0,    18,    84,     0,    80,
      93,    94,    86,     0,    43,     0,    91,     0,     0,     0,
      14,    27,     0,    39,     0,    38,    35,    32,    92,    82,
       0,    10,     0,     0,    30,     0,    23,    44,    42,    13,
       0,    40,    53,     0,    55,     0,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -96,   -96,    11,   -14,   -13,   -96,   139,   -77,   -96,   -96,
     -95,   -96,   -96,   -96,   -96,   -17,    -5,   154,   114,    99,
      -2,    15,    19,   -96,   -79,     2,   -96,   -96
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,    17,    18,    19,    20,    77,   118,   116,    21,
     135,   175,   198,    78,    54,   180,   119,    42,    43,    44,
      45,    46,    47,    89,    48,    49,    50,    51
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    52,    22,    63,   132,    56,    57,    65,   159,    60,
      53,    55,   162,   162,    58,    59,   153,   162,   156,    22,
     162,    23,    22,   147,   148,   149,   150,   151,   100,   101,
     152,    82,    87,    88,    93,     1,     2,   157,   197,    94,
      95,     3,     4,   107,     5,    75,     6,     7,     8,     9,
     168,   109,   110,   133,    10,   160,    11,    12,     1,   163,
     176,    13,    14,   115,   181,   178,   179,   188,   117,    24,
     120,   121,    62,   124,   122,    61,   126,    64,   123,   128,
     203,   179,   191,   102,   103,   104,   105,   129,   130,   196,
      15,   138,   139,   140,   189,    66,    81,   199,    79,    80,
     155,    96,    97,    98,    99,   202,    84,   154,   106,    85,
     206,   141,   142,   143,   144,    22,    86,   165,   166,   145,
     146,    90,    91,    92,     1,     2,   111,   172,   112,   113,
       3,     4,   131,     5,   134,     6,     7,     8,     9,    25,
      26,    27,     1,    10,   114,    11,    12,   127,   122,   158,
      13,    14,   164,   182,   161,   173,   185,   186,   174,   167,
     169,   183,    28,   170,    29,    30,    31,   171,   177,   184,
      32,   187,   192,   195,   193,   194,    63,    22,   200,    15,
     205,    25,    26,    27,     1,   204,   190,    83,   108,     0,
     201,   137,    22,    33,    34,    35,    36,     0,    37,   125,
      38,     0,    39,    40,    28,   136,    29,    30,    31,     0,
       0,     0,    32,     0,     0,     0,    67,    68,    69,    70,
      71,    72,    73,    25,    26,    27,     1,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    34,    35,    36,     0,
      37,    74,    38,    75,    39,    40,    28,    76,    29,    30,
      31,     0,     0,     0,    32,     0,     0,     0,     0,     0,
       0,     0,     0,    25,    26,    27,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,     0,    37,     0,    38,     0,    39,    40,    29,    30,
      31,     1,   134,     0,    32,     0,     0,     3,     4,     0,
       5,     0,     6,     7,     8,     9,     0,     0,     0,     0,
      10,     0,    11,    12,     0,     0,     0,    13,    14,    35,
      36,     0,    37,     1,     0,     0,    39,    40,     0,     3,
       4,     0,     5,     0,     6,     7,     8,     9,     0,     0,
       0,     0,    10,     0,    11,    12,    15,     0,     0,    13,
      14,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    15
};

static const yytype_int16 yycheck[] =
{
       5,     6,     0,    17,    16,    10,    11,    20,    16,    14,
       8,     9,    16,    16,    12,    13,   111,    16,   113,    17,
      16,    62,    20,   102,   103,   104,   105,   106,    29,    30,
     107,    29,    37,    38,    50,     6,     7,   114,     9,    55,
      56,    12,    13,    62,    15,    64,    17,    18,    19,    20,
     127,     3,     4,    65,    25,    63,    27,    28,     6,    63,
      63,    32,    33,    61,    63,    14,    15,    63,    66,    62,
      75,    76,     0,    78,    64,    62,    81,     7,    68,    84,
      14,    15,   177,    44,    45,    46,    47,    85,    86,   184,
      61,    93,    94,    95,   173,    62,    62,   192,    63,    63,
     113,    51,    52,    53,    54,   200,    62,   112,    69,    62,
     205,    96,    97,    98,    99,   113,    62,   122,   123,   100,
     101,    31,    49,    48,     6,     7,    31,   132,    36,    31,
      12,    13,    63,    15,     7,    17,    18,    19,    20,     3,
       4,     5,     6,    25,    62,    27,    28,    62,    64,    16,
      32,    33,    65,   158,    68,    45,   161,   162,     8,    63,
      63,   159,    26,    63,    28,    29,    30,    63,    31,    31,
      34,    65,    31,    68,   179,    63,   190,   175,    31,    61,
      31,     3,     4,     5,     6,   202,   175,    33,    49,    -1,
     195,    92,   190,    57,    58,    59,    60,    -1,    62,    63,
      64,    -1,    66,    67,    26,    91,    28,    29,    30,    -1,
      -1,    -1,    34,    -1,    -1,    -1,    37,    38,    39,    40,
      41,    42,    43,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    57,    58,    59,    60,    -1,
      62,    62,    64,    64,    66,    67,    26,    68,    28,    29,
      30,    -1,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    -1,    62,    -1,    64,    -1,    66,    67,    28,    29,
      30,     6,     7,    -1,    34,    -1,    -1,    12,    13,    -1,
      15,    -1,    17,    18,    19,    20,    -1,    -1,    -1,    -1,
      25,    -1,    27,    28,    -1,    -1,    -1,    32,    33,    59,
      60,    -1,    62,     6,    -1,    -1,    66,    67,    -1,    12,
      13,    -1,    15,    -1,    17,    18,    19,    20,    -1,    -1,
      -1,    -1,    25,    -1,    27,    28,    61,    -1,    -1,    32,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     7,    12,    13,    15,    17,    18,    19,    20,
      25,    27,    28,    32,    33,    61,    71,    72,    73,    74,
      75,    79,    95,    62,    62,     3,     4,     5,    26,    28,
      29,    30,    34,    57,    58,    59,    60,    62,    64,    66,
      67,    86,    87,    88,    89,    90,    91,    92,    94,    95,
      96,    97,    86,    95,    84,    95,    86,    86,    95,    95,
      86,    62,     0,    73,     7,    74,    62,    37,    38,    39,
      40,    41,    42,    43,    62,    64,    68,    76,    83,    63,
      63,    62,    95,    87,    62,    62,    62,    86,    86,    93,
      31,    49,    48,    50,    55,    56,    51,    52,    53,    54,
      29,    30,    44,    45,    46,    47,    69,    62,    76,     3,
       4,    31,    36,    31,    62,    95,    78,    95,    77,    86,
      86,    86,    64,    68,    86,    63,    86,    62,    86,    95,
      95,    63,    16,    65,     7,    80,    88,    89,    90,    90,
      90,    91,    91,    91,    91,    92,    92,    94,    94,    94,
      94,    94,    77,    80,    86,    74,    80,    77,    16,    16,
      63,    68,    16,    63,    65,    86,    86,    63,    77,    63,
      63,    63,    86,    45,     8,    81,    63,    31,    14,    15,
      85,    63,    86,    95,    31,    86,    86,    65,    63,    94,
      72,    80,    31,    86,    63,    68,    80,     9,    82,    80,
      31,    86,    80,    14,    85,    31,    80
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    70,    71,    72,    72,    73,    73,    73,    74,    74,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    75,    75,    75,    75,    75,    75,
      75,    76,    76,    77,    77,    77,    78,    78,    78,    78,
      78,    79,    80,    81,    82,    83,    83,    83,    83,    83,
      83,    83,    84,    85,    85,    85,    86,    86,    87,    87,
      88,    88,    89,    89,    89,    89,    90,    90,    90,    90,
      90,    91,    91,    91,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    95,    96,    96,    96,    96,
      96,    96,    96,    96,    97,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     1,     2,     1,
       6,     4,     4,     7,     5,     4,     4,     3,     4,     3,
       2,     3,     3,     6,     1,     2,     4,     5,     1,     2,
       6,     3,     4,     0,     1,     3,     0,     1,     3,     3,
       5,     2,     4,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     7,     5,     1,     2,     1,     3,
       1,     3,     1,     3,     3,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     3,     3,     3,     3,
       4,     3,     5,     3,     4,     1,     3,     1,     3,     1,
       2,     4,     5,     4,     4,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1
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
#line 61 "epython.y" /* yacc.c:1646  */
    { compileMemory((yyvsp[0].data)); }
#line 1551 "parser.c" /* yacc.c:1646  */
    break;

  case 4:
#line 65 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1557 "parser.c" /* yacc.c:1646  */
    break;

  case 5:
#line 69 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[-1].data); }
#line 1563 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 70 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = (yyvsp[0].data); }
#line 1569 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 71 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = NULL; }
#line 1575 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 75 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=concatenateMemory((yyvsp[-1].data), (yyvsp[0].data)); }
#line 1581 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 80 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendForStatement((yyvsp[-4].string), (yyvsp[-2].data), (yyvsp[0].data)); leaveScope(); }
#line 1587 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 81 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendWhileStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1593 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 82 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1599 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 83 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1605 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 84 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 1611 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 85 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1617 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 86 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1623 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 87 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetStatement((yyvsp[-2].string), (yyvsp[0].data)); }
#line 1629 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 88 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendArraySetStatement((yyvsp[-3].string), (yyvsp[-2].stack), (yyvsp[0].data)); }
#line 1635 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 89 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendLetWithOperatorStatement((yyvsp[-2].string), (yyvsp[0].data), (yyvsp[-1].uchar)); }
#line 1641 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 90 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement("rtl_print", NULL, (yyvsp[0].data)); }
#line 1647 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 91 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendStopStatement(); }
#line 1653 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 92 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendStopStatement(); }
#line 1659 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 93 "epython.y" /* yacc.c:1646  */
    { appendNewFunctionStatement((yyvsp[-5].string), (yyvsp[-3].stack), (yyvsp[0].data)); leaveScope(); (yyval.data) = NULL; }
#line 1665 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 94 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatement(); }
#line 1671 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 95 "epython.y" /* yacc.c:1646  */
    { (yyval.data) = appendReturnStatementWithExpression((yyvsp[0].data)); }
#line 1677 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 96 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 1683 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 97 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack), NULL); }
#line 1689 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 98 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendPassStatement(); }
#line 1695 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 99 "epython.y" /* yacc.c:1646  */
    {  fn_decorator=(char*) malloc(strlen((yyvsp[0].string))+1); strcpy(fn_decorator, (yyvsp[0].string)); (yyval.data) = NULL; }
#line 1701 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 100 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendAliasStatement((yyvsp[-3].string), (yyvsp[-1].data)); }
#line 1707 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 104 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[-1].data)); }
#line 1713 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 105 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-3].stack), (yyvsp[-1].data)); }
#line 1719 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 109 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); }
#line 1725 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 110 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 1731 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 111 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-2].stack); }
#line 1737 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 115 "epython.y" /* yacc.c:1646  */
    { enterScope(); (yyval.stack)=getNewStack(); }
#line 1743 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 116 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifier((yyval.stack), (yyvsp[0].string)); appendArgument((yyvsp[0].string)); }
#line 1749 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 117 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); enterScope(); pushIdentifierAssgnExpression((yyval.stack), (yyvsp[-2].string), (yyvsp[0].data)); appendArgument((yyvsp[-2].string)); }
#line 1755 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 118 "epython.y" /* yacc.c:1646  */
    { pushIdentifier((yyvsp[-2].stack), (yyvsp[0].string)); (yyval.stack)=(yyvsp[-2].stack); appendArgument((yyvsp[0].string)); }
#line 1761 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 119 "epython.y" /* yacc.c:1646  */
    { pushIdentifierAssgnExpression((yyvsp[-4].stack), (yyvsp[-2].string), (yyvsp[0].data)); (yyval.stack)=(yyvsp[-4].stack); appendArgument((yyvsp[-2].string)); }
#line 1767 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 123 "epython.y" /* yacc.c:1646  */
    { enterFunction((yyvsp[0].string)); (yyval.string)=(yyvsp[0].string); }
#line 1773 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 127 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 1779 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 130 "epython.y" /* yacc.c:1646  */
    { enterScope(); }
#line 1785 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 133 "epython.y" /* yacc.c:1646  */
    { leaveScope(); }
#line 1791 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 136 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=0; }
#line 1797 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 137 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=1; }
#line 1803 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 138 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=2; }
#line 1809 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 139 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=3; }
#line 1815 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 140 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=4; }
#line 1821 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 141 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=5; }
#line 1827 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 142 "epython.y" /* yacc.c:1646  */
    { (yyval.uchar)=6; }
#line 1833 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 145 "epython.y" /* yacc.c:1646  */
    { (yyval.string)=(yyvsp[0].string); enterScope(); addVariableIfNeeded((yyvsp[0].string)); }
#line 1839 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 149 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfStatement((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1845 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 150 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-5].data), (yyvsp[-3].data), (yyvsp[0].data)); }
#line 1851 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 151 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendIfElseStatement((yyvsp[-3].data), (yyvsp[-1].data), (yyvsp[0].data)); }
#line 1857 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 155 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1863 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 156 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNotExpression((yyvsp[0].data)); }
#line 1869 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 160 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1875 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 161 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createOrExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1881 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 164 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1887 "parser.c" /* yacc.c:1646  */
    break;

  case 61:
#line 165 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAndExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1893 "parser.c" /* yacc.c:1646  */
    break;

  case 62:
#line 169 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1899 "parser.c" /* yacc.c:1646  */
    break;

  case 63:
#line 170 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createEqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1905 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 171 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1911 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 172 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIsExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1917 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 176 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1923 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 177 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1929 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 178 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLtExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1935 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 179 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createLeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1941 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 180 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createGeqExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1947 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 184 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1953 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 185 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createAddExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1959 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 186 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createSubExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1965 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 190 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 1971 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 191 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createMulExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1977 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 192 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1983 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 193 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createFloorDivExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1989 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 194 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createModExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 1995 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 195 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createPowExpression((yyvsp[-2].data), (yyvsp[0].data)); }
#line 2001 "parser.c" /* yacc.c:1646  */
    break;

  case 80:
#line 196 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2007 "parser.c" /* yacc.c:1646  */
    break;

  case 81:
#line 197 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createArrayExpression((yyvsp[-1].stack), NULL); }
#line 2013 "parser.c" /* yacc.c:1646  */
    break;

  case 82:
#line 198 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createArrayExpression((yyvsp[-3].stack), (yyvsp[0].data)); }
#line 2019 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 199 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement("rtl_input", NULL, NULL); }
#line 2025 "parser.c" /* yacc.c:1646  */
    break;

  case 84:
#line 200 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement("rtl_inputprint", NULL, (yyvsp[-1].data)); }
#line 2031 "parser.c" /* yacc.c:1646  */
    break;

  case 85:
#line 204 "epython.y" /* yacc.c:1646  */
    { (yyval.stack)=getNewStack(); pushExpression((yyval.stack), (yyvsp[0].data)); }
#line 2037 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 205 "epython.y" /* yacc.c:1646  */
    { pushExpression((yyvsp[-2].stack), (yyvsp[0].data)); }
#line 2043 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 209 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[0].data); }
#line 2049 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 210 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=(yyvsp[-1].data); }
#line 2055 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 211 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierExpression((yyvsp[0].string)); }
#line 2061 "parser.c" /* yacc.c:1646  */
    break;

  case 90:
#line 212 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIdentifierArrayAccessExpression((yyvsp[-1].string), (yyvsp[0].stack)); }
#line 2067 "parser.c" /* yacc.c:1646  */
    break;

  case 91:
#line 213 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack)); }
#line 2073 "parser.c" /* yacc.c:1646  */
    break;

  case 92:
#line 214 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendNativeCallFunctionStatement((yyvsp[-3].string), (yyvsp[-1].stack), NULL); }
#line 2079 "parser.c" /* yacc.c:1646  */
    break;

  case 93:
#line 215 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendReferenceStatement((yyvsp[-1].string)); }
#line 2085 "parser.c" /* yacc.c:1646  */
    break;

  case 94:
#line 216 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=appendSymbolStatement((yyvsp[-1].string)); }
#line 2091 "parser.c" /* yacc.c:1646  */
    break;

  case 95:
#line 220 "epython.y" /* yacc.c:1646  */
    { (yyval.string) = malloc(strlen((yyvsp[0].string))+1); strcpy((yyval.string), (yyvsp[0].string)); }
#line 2097 "parser.c" /* yacc.c:1646  */
    break;

  case 96:
#line 224 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[0].integer)); }
#line 2103 "parser.c" /* yacc.c:1646  */
    break;

  case 97:
#line 225 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[0].real)); }
#line 2109 "parser.c" /* yacc.c:1646  */
    break;

  case 98:
#line 226 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createIntegerExpression((yyvsp[-1].integer) * (yyvsp[0].integer)); }
#line 2115 "parser.c" /* yacc.c:1646  */
    break;

  case 99:
#line 227 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createRealExpression((yyvsp[-1].integer) * (yyvsp[0].real)); }
#line 2121 "parser.c" /* yacc.c:1646  */
    break;

  case 100:
#line 228 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createStringExpression((yyvsp[0].string)); }
#line 2127 "parser.c" /* yacc.c:1646  */
    break;

  case 101:
#line 229 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(1); }
#line 2133 "parser.c" /* yacc.c:1646  */
    break;

  case 102:
#line 230 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createBooleanExpression(0); }
#line 2139 "parser.c" /* yacc.c:1646  */
    break;

  case 103:
#line 231 "epython.y" /* yacc.c:1646  */
    { (yyval.data)=createNoneExpression(); }
#line 2145 "parser.c" /* yacc.c:1646  */
    break;

  case 104:
#line 235 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = 1; }
#line 2151 "parser.c" /* yacc.c:1646  */
    break;

  case 105:
#line 236 "epython.y" /* yacc.c:1646  */
    { (yyval.integer) = -1; }
#line 2157 "parser.c" /* yacc.c:1646  */
    break;


#line 2161 "parser.c" /* yacc.c:1646  */
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
#line 239 "epython.y" /* yacc.c:1906  */

