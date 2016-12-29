/* A Bison parser, made by GNU Bison 3.0.4.  */

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Substitute the type names.  */
#define YYSTYPE         HSQL_STYPE
#define YYLTYPE         HSQL_LTYPE
/* Substitute the variable and function names.  */
#define yyparse         hsql_parse
#define yylex           hsql_lex
#define yyerror         hsql_error
#define yydebug         hsql_debug
#define yynerrs         hsql_nerrs


/* Copy the first part of user declarations.  */
#line 1 "bison_parser.y" /* yacc.c:339  */

/**
 * bison_parser.y
 * defines bison_parser.h
 * outputs bison_parser.c
 * 
 * Grammar File Spec: http://dinosaur.compilertools.net/bison/bison_6.html
 *
 */
/*********************************
 ** Section 1: C Declarations
 *********************************/

#include "bison_parser.h"
#include "flex_lexer.h"

#include <stdio.h>

using namespace hsql;

int yyerror(YYLTYPE* llocp, SQLParserResult** result, yyscan_t scanner, const char *msg) {

	SQLParserResult* list = new SQLParserResult();
	list->isValid = false;
	list->errorMsg = strdup(msg);
	list->errorLine = llocp->first_line;
	list->errorColumn = llocp->first_column;

	*result = list;
	return 0;
}




#line 110 "bison_parser.cpp" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison_parser.h".  */
#ifndef YY_HSQL_BISON_PARSER_H_INCLUDED
# define YY_HSQL_BISON_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef HSQL_DEBUG
# if defined YYDEBUG
#if YYDEBUG
#   define HSQL_DEBUG 1
#  else
#   define HSQL_DEBUG 0
#  endif
# else /* ! defined YYDEBUG */
#  define HSQL_DEBUG 0
# endif /* ! defined YYDEBUG */
#endif  /* ! defined HSQL_DEBUG */
#if HSQL_DEBUG
extern int hsql_debug;
#endif
/* "%code requires" blocks.  */
#line 42 "bison_parser.y" /* yacc.c:355  */

// %code requires block	

#include "../sql/statements.h"
#include "../SQLParserResult.h"
#include "parser_typedef.h"

// Auto update column and line number
#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line; \
    yylloc->first_column = yylloc->last_column; \
    for(int i = 0; yytext[i] != '\0'; i++) { \
    	yylloc->total_column++; \
        if(yytext[i] == '\n') { \
            yylloc->last_line++; \
            yylloc->last_column = 0; \
        } \
        else { \
            yylloc->last_column++; \
        } \
    }

#line 171 "bison_parser.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef HSQL_TOKENTYPE
# define HSQL_TOKENTYPE
  enum hsql_tokentype
  {
    SQL_IDENTIFIER = 258,
    SQL_STRING = 259,
    SQL_DFLOATVAL = 260,
    SQL_INTVAL = 261,
    SQL_NOTEQUALS = 262,
    SQL_LESSEQ = 263,
    SQL_GREATEREQ = 264,
    SQL_DEALLOCATE = 265,
    SQL_PARAMETERS = 266,
    SQL_INTERSECT = 267,
    SQL_TEMPORARY = 268,
    SQL_TIMESTAMP = 269,
    SQL_DISTINCT = 270,
    SQL_NVARCHAR = 271,
    SQL_VARCHAR = 272,
    SQL_RESTRICT = 273,
    SQL_TRUNCATE = 274,
    SQL_ANALYZE = 275,
    SQL_BETWEEN = 276,
    SQL_CASCADE = 277,
    SQL_COLUMNS = 278,
    SQL_CONTROL = 279,
    SQL_DEFAULT = 280,
    SQL_EXECUTE = 281,
    SQL_EXPLAIN = 282,
    SQL_HISTORY = 283,
    SQL_INTEGER = 284,
    SQL_NATURAL = 285,
    SQL_PREPARE = 286,
    SQL_PRIMARY = 287,
    SQL_SCHEMAS = 288,
    SQL_SPATIAL = 289,
    SQL_VIRTUAL = 290,
    SQL_BEFORE = 291,
    SQL_COLUMN = 292,
    SQL_CREATE = 293,
    SQL_DELETE = 294,
    SQL_DIRECT = 295,
    SQL_DOUBLE = 296,
    SQL_ESCAPE = 297,
    SQL_EXCEPT = 298,
    SQL_EXISTS = 299,
    SQL_GLOBAL = 300,
    SQL_HAVING = 301,
    SQL_IMPORT = 302,
    SQL_INSERT = 303,
    SQL_ISNULL = 304,
    SQL_OFFSET = 305,
    SQL_RENAME = 306,
    SQL_SCHEMA = 307,
    SQL_SELECT = 308,
    SQL_SORTED = 309,
    SQL_TABLES = 310,
    SQL_UNIQUE = 311,
    SQL_UNLOAD = 312,
    SQL_UPDATE = 313,
    SQL_VALUES = 314,
    SQL_AFTER = 315,
    SQL_ALTER = 316,
    SQL_CROSS = 317,
    SQL_DELTA = 318,
    SQL_GROUP = 319,
    SQL_INDEX = 320,
    SQL_INNER = 321,
    SQL_LIMIT = 322,
    SQL_LOCAL = 323,
    SQL_MERGE = 324,
    SQL_MINUS = 325,
    SQL_ORDER = 326,
    SQL_OUTER = 327,
    SQL_RIGHT = 328,
    SQL_TABLE = 329,
    SQL_UNION = 330,
    SQL_USING = 331,
    SQL_WHERE = 332,
    SQL_CALL = 333,
    SQL_DATE = 334,
    SQL_DESC = 335,
    SQL_DROP = 336,
    SQL_FILE = 337,
    SQL_FROM = 338,
    SQL_FULL = 339,
    SQL_HASH = 340,
    SQL_HINT = 341,
    SQL_INTO = 342,
    SQL_JOIN = 343,
    SQL_LEFT = 344,
    SQL_LIKE = 345,
    SQL_LOAD = 346,
    SQL_NULL = 347,
    SQL_PART = 348,
    SQL_PLAN = 349,
    SQL_SHOW = 350,
    SQL_TEXT = 351,
    SQL_TIME = 352,
    SQL_VIEW = 353,
    SQL_WITH = 354,
    SQL_ADD = 355,
    SQL_ALL = 356,
    SQL_AND = 357,
    SQL_ASC = 358,
    SQL_CSV = 359,
    SQL_FOR = 360,
    SQL_INT = 361,
    SQL_KEY = 362,
    SQL_NOT = 363,
    SQL_OFF = 364,
    SQL_SET = 365,
    SQL_TBL = 366,
    SQL_TOP = 367,
    SQL_AS = 368,
    SQL_BY = 369,
    SQL_IF = 370,
    SQL_IN = 371,
    SQL_IS = 372,
    SQL_OF = 373,
    SQL_ON = 374,
    SQL_OR = 375,
    SQL_TO = 376,
    SQL_DATABASE = 377,
    SQL_USE = 378,
    SQL_READ = 379,
    SQL_QUIT = 380,
    SQL_MAX = 381,
    SQL_MIN = 382,
    SQL_AVG = 383,
    SQL_SUM = 384,
    SQL_EQUALS = 385,
    SQL_LESS = 386,
    SQL_GREATER = 387,
    SQL_NOTNULL = 388,
    SQL_UMINUS = 389
  };
#endif

/* Value type.  */
#if ! defined HSQL_STYPE && ! defined HSQL_STYPE_IS_DECLARED
typedef union HSQL_STYPE HSQL_STYPE;
union HSQL_STYPE
{
#line 101 "bison_parser.y" /* yacc.c:355  */

	double fval;
	int64_t ival;
	char* sval;
	uintmax_t uval;
	bool bval;

	hsql::SQLStatement* statement;
	hsql::SelectStatement* 	select_stmt;
	hsql::ImportStatement* 	import_stmt;
	hsql::CreateStatement* 	create_stmt;
	hsql::SingleStatement*  single_stmt;
	hsql::InsertStatement* 	insert_stmt;
	hsql::DeleteStatement* 	delete_stmt;
	hsql::UpdateStatement* 	update_stmt;
	hsql::DropStatement*   	drop_stmt;
	hsql::PrepareStatement* prep_stmt;
	hsql::ExecuteStatement* exec_stmt;

	hsql::TableRef* table;
	hsql::Expr* expr;
	hsql::OrderDescription* order;
	hsql::OrderType order_type;
	hsql::LimitDescription* limit;
	hsql::ColumnDefinition* column_t;
	hsql::GroupByDescription* group_t;
	hsql::UpdateClause* update_t;

	hsql::SQLParserResult* stmt_list;

	std::vector<char*>* str_vec;
	std::vector<hsql::TableRef*>* table_vec;
	std::vector<hsql::ColumnDefinition*>* column_vec;
	std::vector<hsql::UpdateClause*>* update_vec;
	std::vector<hsql::Expr*>* expr_vec;
	std::vector<std::vector<hsql::Expr*>*>* literal_list_vec;

#line 356 "bison_parser.cpp" /* yacc.c:355  */
};
# define HSQL_STYPE_IS_TRIVIAL 1
# define HSQL_STYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined HSQL_LTYPE && ! defined HSQL_LTYPE_IS_DECLARED
typedef struct HSQL_LTYPE HSQL_LTYPE;
struct HSQL_LTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define HSQL_LTYPE_IS_DECLARED 1
# define HSQL_LTYPE_IS_TRIVIAL 1
#endif



int hsql_parse (hsql::SQLParserResult** result, yyscan_t scanner);

#endif /* !YY_HSQL_BISON_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 384 "bison_parser.cpp" /* yacc.c:358  */

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
         || (defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL \
             && defined HSQL_STYPE_IS_TRIVIAL && HSQL_STYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  57
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   518

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  155
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  322

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   389

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   141,     2,     2,
     146,   147,   139,   137,   153,   138,   148,   140,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   150,   149,
     132,   130,   133,   154,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   144,     2,   145,   142,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   151,     2,   152,     2,     2,     2,     2,
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
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   131,   134,   135,   136,   143
};

#if HSQL_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   236,   236,   243,   244,   248,   253,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   274,   278,   282,
     286,   290,   294,   298,   307,   312,   320,   324,   336,   344,
     348,   358,   364,   374,   375,   379,   380,   384,   390,   393,
     398,   401,   406,   412,   413,   414,   415,   416,   426,   430,
     442,   450,   462,   468,   478,   479,   489,   498,   499,   503,
     515,   516,   520,   521,   525,   530,   542,   543,   544,   548,
     556,   564,   572,   580,   591,   592,   596,   601,   606,   607,
     611,   615,   622,   627,   631,   632,   635,   636,   640,   641,
     642,   647,   648,   649,   656,   657,   661,   662,   666,   667,
     671,   678,   679,   680,   681,   682,   686,   687,   688,   692,
     696,   697,   698,   699,   700,   701,   702,   704,   705,   706,
     707,   708,   713,   714,   715,   716,   717,   718,   722,   726,
     727,   731,   732,   733,   734,   738,   743,   744,   748,   752,
     756,   761,   772,   773,   783,   784,   790,   795,   796,   801,
     811,   818,   819,   824,   825,   829,   830,   838,   850,   851,
     852,   853,   854,   860,   866,   870,   879,   880,   885,   886
};
#endif

#if HSQL_DEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING", "DFLOATVAL",
  "INTVAL", "NOTEQUALS", "LESSEQ", "GREATEREQ", "DEALLOCATE", "PARAMETERS",
  "INTERSECT", "TEMPORARY", "TIMESTAMP", "DISTINCT", "NVARCHAR", "VARCHAR",
  "RESTRICT", "TRUNCATE", "ANALYZE", "BETWEEN", "CASCADE", "COLUMNS",
  "CONTROL", "DEFAULT", "EXECUTE", "EXPLAIN", "HISTORY", "INTEGER",
  "NATURAL", "PREPARE", "PRIMARY", "SCHEMAS", "SPATIAL", "VIRTUAL",
  "BEFORE", "COLUMN", "CREATE", "DELETE", "DIRECT", "DOUBLE", "ESCAPE",
  "EXCEPT", "EXISTS", "GLOBAL", "HAVING", "IMPORT", "INSERT", "ISNULL",
  "OFFSET", "RENAME", "SCHEMA", "SELECT", "SORTED", "TABLES", "UNIQUE",
  "UNLOAD", "UPDATE", "VALUES", "AFTER", "ALTER", "CROSS", "DELTA",
  "GROUP", "INDEX", "INNER", "LIMIT", "LOCAL", "MERGE", "MINUS", "ORDER",
  "OUTER", "RIGHT", "TABLE", "UNION", "USING", "WHERE", "CALL", "DATE",
  "DESC", "DROP", "FILE", "FROM", "FULL", "HASH", "HINT", "INTO", "JOIN",
  "LEFT", "LIKE", "LOAD", "NULL", "PART", "PLAN", "SHOW", "TEXT", "TIME",
  "VIEW", "WITH", "ADD", "ALL", "AND", "ASC", "CSV", "FOR", "INT", "KEY",
  "NOT", "OFF", "SET", "TBL", "TOP", "AS", "BY", "IF", "IN", "IS", "OF",
  "ON", "OR", "TO", "DATABASE", "USE", "READ", "QUIT", "MAX", "MIN", "AVG",
  "SUM", "'='", "EQUALS", "'<'", "'>'", "LESS", "GREATER", "NOTNULL",
  "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "UMINUS", "'['", "']'", "'('",
  "')'", "'.'", "';'", "':'", "'{'", "'}'", "','", "'?'", "$accept",
  "input", "statement_list", "statement", "preparable_statement",
  "single_statement", "prepare_statement", "execute_statement",
  "import_statement", "import_file_type", "file_path", "create_statement",
  "opt_not_exists", "column_def_commalist", "column_def", "width",
  "null_type", "primary_key_def", "column_type", "drop_statement",
  "delete_statement", "truncate_statement", "insert_statement",
  "opt_column_list", "update_statement", "update_clause_commalist",
  "update_clause", "select_statement", "select_with_paren",
  "select_no_paren", "set_operator", "select_clause", "opt_distinct",
  "select_list", "from_clause", "opt_where", "my_where_clause",
  "opt_group", "opt_having", "opt_order", "opt_order_type", "opt_limit",
  "expr_list", "literal_lists", "literal_list", "expr_alias", "expr",
  "scalar_expr", "unary_expr", "binary_expr", "comp_expr", "function_expr",
  "column_name", "literal", "string_literal", "num_literal", "int_literal",
  "nul_literal", "star_expr", "placeholder_expr", "table_ref",
  "table_ref_atomic", "table_ref_commalist", "table_ref_name",
  "table_ref_name_no_alias", "table_name", "alias", "opt_alias",
  "join_clause", "opt_join_type", "join_table", "join_condition",
  "opt_semicolon", "ident_commalist", YY_NULL
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
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
      61,   385,    60,    62,   386,   387,   388,    43,    45,    42,
      47,    37,    94,   389,    91,    93,    40,    41,    46,    59,
      58,   123,   125,    44,    63
};
# endif

#define YYPACT_NINF -248

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-248)))

#define YYTABLE_NINF -165

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-165)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     235,    13,    50,    55,    58,   -29,   -21,   -14,    15,    88,
      50,   -26,   -25,   104,    32,  -248,   -36,   117,   -27,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,    24,   133,    -4,  -248,     1,  -116,
      33,   148,    50,    48,    50,  -248,    -1,    51,  -248,    50,
     160,   162,   166,  -248,   168,    25,    30,  -248,   235,  -248,
    -248,  -248,    68,  -248,   130,   118,  -248,   184,     6,   280,
     235,    83,    50,  -248,   115,  -248,   120,    70,  -115,  -248,
    -248,  -248,  -248,    71,    84,    86,    90,    20,  -248,    20,
    -248,   154,    85,  -248,   172,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,   239,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,    20,   175,   241,
    -248,  -248,  -101,  -248,  -248,   -27,   213,   113,    20,  -248,
     256,   262,    -3,    88,   269,    20,    20,    20,    20,    -7,
      56,     3,   115,    20,  -248,    20,    20,    20,    20,   173,
     276,    16,    20,    20,    20,    20,    20,    20,    20,    20,
      20,    20,  -248,  -248,   151,   -59,  -248,   260,   118,   234,
    -248,     6,   139,  -248,   291,   193,   316,   209,  -248,  -248,
     -96,   152,  -248,    20,  -248,   150,   153,   156,   161,  -248,
     -36,  -248,   164,   167,    26,  -248,   -34,   237,  -248,   376,
      67,    67,   376,    20,  -248,    20,    73,   335,   376,    67,
      67,    -7,    -7,   165,   165,   165,  -248,     6,   239,  -248,
    -248,  -248,  -248,  -248,   241,  -248,  -248,    72,   -87,  -248,
      20,    50,  -248,   312,     6,   169,   111,   154,   154,   154,
     154,   174,     3,  -248,  -248,  -248,  -248,  -248,   232,   212,
    -248,   376,   335,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,   183,  -248,    27,   316,  -248,  -248,   -47,   185,  -248,
     115,   115,   115,   115,    26,  -248,   179,    11,    20,   328,
     227,   229,  -248,   190,  -248,     6,   237,   237,   237,   237,
     198,     3,   -36,  -248,   220,   -37,   194,   253,  -248,   200,
    -248,   -42,  -248,  -248,  -248,  -248,  -248,   201,    20,    20,
    -248,  -248,  -248,   344,  -248,    26,   316,  -248,   316,   202,
    -248,  -248
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    75,
       0,     0,     0,     0,     0,    23,     0,     0,   167,     3,
       6,    16,     5,    15,     8,     9,    14,    11,    12,    10,
      13,     7,    60,    61,    87,     0,   151,    51,    26,     0,
      34,     0,     0,     0,     0,    74,     0,     0,   150,     0,
       0,     0,     0,    19,     0,     0,     0,     1,   166,     2,
      67,    68,     0,    66,     0,    93,    49,     0,     0,     0,
       0,     0,     0,    17,    79,    29,     0,    55,   129,   135,
     136,   138,   139,     0,     0,     0,     0,     0,   140,     0,
     141,     0,    76,    94,   156,   102,   103,   104,   110,   105,
     106,   108,   131,   132,   137,   133,   107,   134,     0,    48,
      18,    21,    20,    22,    63,    62,     4,     0,    87,     0,
      64,   152,     0,    98,    24,   167,     0,     0,     0,    50,
       0,     0,     0,    75,     0,     0,     0,     0,     0,   109,
       0,     0,    79,     0,   154,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   155,   100,     0,    79,    57,    90,    93,    91,
      27,     0,     0,    33,     0,    78,    81,     0,    30,   168,
       0,     0,    53,     0,   130,     0,     0,     0,     0,   101,
       0,    77,   142,   144,   156,   146,   162,    83,    95,   123,
     126,   127,   118,     0,   153,     0,   120,   117,   122,   124,
     125,   112,   111,   114,   113,   115,   116,     0,     0,    56,
      89,    88,    86,    65,     0,    99,    25,     0,     0,    35,
       0,     0,    54,     0,     0,    52,     0,     0,     0,     0,
       0,     0,     0,   149,   158,   159,   161,   160,     0,     0,
      69,   119,   121,    59,    58,    92,    47,    44,    45,    46,
      43,    39,    31,     0,    80,    28,   169,     0,     0,   128,
      79,    79,    79,    79,     0,   147,   143,     0,     0,     0,
      41,     0,    36,     0,    96,     0,    83,    83,    83,    83,
     145,     0,     0,   164,     0,    85,     0,     0,    37,     0,
      32,     0,    72,    73,    71,    70,   148,     0,     0,     0,
      82,    38,    40,     0,    97,     0,   165,   157,    84,     0,
     163,    42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,   281,   294,   284,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,    91,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,   137,  -162,   340,    -9,
    -248,   293,   231,     5,   -13,   -50,  -248,   -11,  -248,   244,
    -248,   197,    89,  -248,  -197,   223,   -74,  -248,  -248,  -248,
    -248,  -248,  -248,   -67,   240,  -248,  -103,  -248,  -248,  -248,
    -248,  -201,  -248,    92,  -248,    -2,  -247,   177,  -248,  -248,
      95,  -248,   248,  -248
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    76,
     177,    25,    72,   228,   229,   280,   298,   283,   261,    26,
      27,    28,    29,   132,    30,   165,   166,    31,    32,    33,
      64,    34,    46,    91,   142,   129,   175,   250,   310,    65,
     222,   120,    92,   235,   122,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     191,   192,   276,   193,    47,   194,   162,   163,   195,   248,
     196,   317,    59,   180
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,   123,    78,    79,    80,    81,    36,    56,    48,   309,
      79,    80,    81,   139,    36,   140,   169,     9,   128,    78,
      79,    80,    81,    78,    79,    80,    81,   290,   241,   144,
     227,   133,   244,   134,    69,    70,    60,   267,   245,   246,
      74,   275,    77,   167,    35,    40,   170,   109,    49,    51,
       9,   232,   171,    36,   176,   247,   181,   233,    38,   281,
     262,    39,    42,   145,   146,   147,   263,    61,   320,    43,
     127,   199,   200,   201,   202,  -165,  -165,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   216,   301,   256,
     306,    82,   197,    41,   218,    62,    50,    52,    82,    63,
     284,   257,    44,    45,   225,   314,   171,    53,    82,   236,
      16,   171,    82,   258,    54,   219,   143,    57,   145,   146,
     147,   255,    58,   182,   205,    83,    84,    85,    86,   251,
     307,   252,   158,   159,   160,   161,    66,    87,    88,   150,
     185,   186,   187,   188,    67,    89,   148,    68,    71,   190,
     253,    73,    75,    90,    87,    88,   264,   292,    87,    88,
      90,   108,    89,   110,   149,   111,    89,   123,   259,   112,
      90,   113,   114,   151,    90,   144,   152,   115,   260,   145,
     146,   147,   117,     9,   151,   119,   153,   121,   154,   155,
    -165,   126,   128,   156,   157,   158,   159,   160,   161,  -165,
    -165,   148,   130,   189,   156,   157,   158,   159,   160,   161,
     156,   157,   158,   159,   160,   161,   131,   135,   123,   149,
     286,   287,   288,   289,   270,   271,   272,   273,   151,   265,
     136,   152,   137,  -164,   316,   318,   138,   141,   143,  -164,
    -164,   153,   164,   154,   155,     1,    62,    81,   156,   157,
     158,   159,   160,   161,     2,  -164,  -164,   173,   269,   174,
      79,     3,   148,   203,  -163,   179,     4,   145,   146,   147,
    -163,  -163,   184,     5,     6,   302,   303,   304,   305,   204,
     149,   217,     7,     8,   224,   150,  -163,  -163,     9,   151,
       1,   226,   152,    10,   227,   230,   231,   237,   234,     2,
     238,   249,   153,   239,   154,   155,     3,   161,   240,   156,
     157,   158,   159,   160,   161,   266,    11,   242,     5,     6,
     277,   274,   268,   145,   146,   147,   278,     7,     8,   279,
      12,   285,   291,     9,   296,   297,   299,   300,    10,   308,
     220,   311,   145,   146,   147,   312,   313,   319,   315,   321,
     148,   125,   116,   124,   282,   254,    55,   118,    13,    14,
      15,    11,   168,   221,   183,   223,   198,   295,   149,   293,
     178,   243,   294,   172,     0,    12,     0,   151,     0,     0,
     152,    16,     0,   145,   146,   147,     0,     0,     0,     0,
     153,     0,   154,   155,     0,     0,     0,   156,   157,   158,
     159,   160,   161,    13,    14,    15,   148,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   149,   148,    16,     0,     0,     0,
       0,     0,     0,   151,     0,     0,   152,     0,     0,     0,
       0,     0,     0,   149,     0,     0,   153,     0,   154,   155,
       0,     0,   151,   156,   157,   158,   159,   160,   161,     0,
       0,     0,     0,     0,     0,   153,   148,   154,   155,     0,
       0,     0,   156,   157,   158,   159,   160,   161,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   151,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   153,     0,   154,   155,
       0,     0,     0,   156,   157,   158,   159,   160,   161
};

static const yytype_int16 yycheck[] =
{
       2,    68,     3,     4,     5,     6,     3,    16,    10,    46,
       4,     5,     6,    87,     3,    89,   119,    53,    77,     3,
       4,     5,     6,     3,     4,     5,     6,   274,   190,     3,
       3,   146,    66,   148,   150,   151,    12,   234,    72,    73,
      42,   242,    44,   117,    31,    74,   147,    49,    74,    74,
      53,   147,   153,     3,   128,    89,    59,   153,     3,    32,
     147,     3,    83,     7,     8,     9,   153,    43,   315,    83,
      72,   145,   146,   147,   148,     8,     9,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   285,    17,
     291,    92,   142,   122,   153,    71,   122,   122,    92,    75,
     147,    29,    87,    15,   171,   147,   153,     3,    92,   183,
     146,   153,    92,    41,    82,   165,   153,     0,     7,     8,
       9,   224,   149,   132,   108,   126,   127,   128,   129,   203,
     292,   205,   139,   140,   141,   142,     3,   138,   139,   113,
     135,   136,   137,   138,   148,   146,    90,   146,   115,   146,
     217,     3,   104,   154,   138,   139,   230,   146,   138,   139,
     154,   110,   146,     3,   108,     3,   146,   234,    96,     3,
     154,     3,   147,   117,   154,     3,   120,   147,   106,     7,
       8,     9,   114,    53,   117,    67,   130,     3,   132,   133,
     117,   108,    77,   137,   138,   139,   140,   141,   142,   132,
     133,    90,    82,   147,   137,   138,   139,   140,   141,   142,
     137,   138,   139,   140,   141,   142,   146,   146,   285,   108,
     270,   271,   272,   273,   237,   238,   239,   240,   117,   231,
     146,   120,   146,    66,   308,   309,   146,    83,   153,    72,
      73,   130,     3,   132,   133,    10,    71,     6,   137,   138,
     139,   140,   141,   142,    19,    88,    89,    44,   147,   146,
       4,    26,    90,    90,    66,     3,    31,     7,     8,     9,
      72,    73,     3,    38,    39,   286,   287,   288,   289,     3,
     108,   130,    47,    48,    50,   113,    88,    89,    53,   117,
      10,   152,   120,    58,     3,   102,    87,   147,   146,    19,
     147,    64,   130,   147,   132,   133,    26,   142,   147,   137,
     138,   139,   140,   141,   142,     3,    81,   153,    38,    39,
      88,   147,   153,     7,     8,     9,   114,    47,    48,   146,
      95,   146,   153,    53,     6,   108,   107,   147,    58,   119,
      80,   147,     7,     8,     9,    92,   146,     3,   147,   147,
      90,    70,    58,    69,   263,   218,    16,    64,   123,   124,
     125,    81,   118,   103,   133,   168,   143,   278,   108,   277,
     130,   194,   277,   125,    -1,    95,    -1,   117,    -1,    -1,
     120,   146,    -1,     7,     8,     9,    -1,    -1,    -1,    -1,
     130,    -1,   132,   133,    -1,    -1,    -1,   137,   138,   139,
     140,   141,   142,   123,   124,   125,    90,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   108,    90,   146,    -1,    -1,    -1,
      -1,    -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,
      -1,    -1,    -1,   108,    -1,    -1,   130,    -1,   132,   133,
      -1,    -1,   117,   137,   138,   139,   140,   141,   142,    -1,
      -1,    -1,    -1,    -1,    -1,   130,    90,   132,   133,    -1,
      -1,    -1,   137,   138,   139,   140,   141,   142,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   130,    -1,   132,   133,
      -1,    -1,    -1,   137,   138,   139,   140,   141,   142
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    19,    26,    31,    38,    39,    47,    48,    53,
      58,    81,    95,   123,   124,   125,   146,   156,   157,   158,
     159,   160,   161,   162,   163,   166,   174,   175,   176,   177,
     179,   182,   183,   184,   186,    31,     3,   220,     3,     3,
      74,   122,    83,    83,    87,    15,   187,   219,   220,    74,
     122,    74,   122,     3,    82,   183,   184,     0,   149,   227,
      12,    43,    71,    75,   185,   194,     3,   148,   146,   150,
     151,   115,   167,     3,   220,   104,   164,   220,     3,     4,
       5,     6,    92,   126,   127,   128,   129,   138,   139,   146,
     154,   188,   197,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   110,   220,
       3,     3,     3,     3,   147,   147,   158,   114,   186,    67,
     196,     3,   199,   208,   159,   157,   108,   220,    77,   190,
      82,   146,   178,   146,   148,   146,   146,   146,   146,   201,
     201,    83,   189,   153,     3,     7,     8,     9,    90,   108,
     113,   117,   120,   130,   132,   133,   137,   138,   139,   140,
     141,   142,   221,   222,     3,   180,   181,   201,   194,   211,
     147,   153,   227,    44,   146,   191,   201,   165,   209,     3,
     228,    59,   184,   187,     3,   188,   188,   188,   188,   147,
     146,   215,   216,   218,   220,   223,   225,   190,   200,   201,
     201,   201,   201,    90,     3,   108,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   130,   153,   190,
      80,   103,   195,   196,    50,   208,   152,     3,   168,   169,
     102,    87,   147,   153,   146,   198,   201,   147,   147,   147,
     147,   182,   153,   222,    66,    72,    73,    89,   224,    64,
     192,   201,   201,   208,   181,   211,    17,    29,    41,    96,
     106,   173,   147,   153,   201,   220,     3,   199,   153,   147,
     189,   189,   189,   189,   147,   216,   217,    88,   114,   146,
     170,    32,   169,   172,   147,   146,   190,   190,   190,   190,
     221,   153,   146,   218,   225,   197,     6,   108,   171,   107,
     147,   199,   192,   192,   192,   192,   216,   182,   119,    46,
     193,   147,    92,   146,   147,   147,   201,   226,   201,     3,
     221,   147
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   155,   156,   157,   157,   158,   158,   159,   159,   159,
     159,   159,   159,   159,   159,   159,   159,   160,   160,   160,
     160,   160,   160,   160,   161,   161,   162,   162,   163,   164,
     165,   166,   166,   167,   167,   168,   168,   169,   170,   170,
     171,   171,   172,   173,   173,   173,   173,   173,   174,   174,
     175,   176,   177,   177,   178,   178,   179,   180,   180,   181,
     182,   182,   183,   183,   184,   184,   185,   185,   185,   186,
     186,   186,   186,   186,   187,   187,   188,   189,   190,   190,
     191,   191,   192,   192,   193,   193,   194,   194,   195,   195,
     195,   196,   196,   196,   197,   197,   198,   198,   199,   199,
     200,   201,   201,   201,   201,   201,   202,   202,   202,   203,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   205,   205,   205,   205,   205,   205,   206,   207,
     207,   208,   208,   208,   208,   209,   210,   210,   211,   212,
     213,   214,   215,   215,   216,   216,   216,   217,   217,   218,
     219,   220,   220,   221,   221,   222,   222,   223,   224,   224,
     224,   224,   224,   225,   225,   226,   227,   227,   228,   228
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       3,     3,     3,     1,     4,     6,     2,     5,     7,     1,
       1,     7,     9,     3,     0,     1,     3,     4,     3,     0,
       2,     0,     5,     1,     1,     1,     1,     1,     3,     3,
       4,     2,     6,     5,     3,     0,     5,     1,     3,     3,
       1,     1,     3,     3,     3,     5,     1,     1,     1,     6,
       9,     9,     9,     9,     1,     0,     1,     2,     2,     0,
       3,     1,     4,     0,     2,     0,     4,     0,     1,     1,
       0,     2,     4,     0,     1,     3,     3,     5,     1,     3,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     4,
       3,     4,     3,     3,     3,     3,     3,     3,     5,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     4,     1,     1,     3,     2,
       1,     1,     3,     2,     1,     1,     0,     6,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     0,     1,     3
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
      yyerror (&yylloc, result, scanner, YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if HSQL_DEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

__attribute__((__unused__))
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location, result, scanner); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, hsql::SQLParserResult** result, yyscan_t scanner)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp, hsql::SQLParserResult** result, yyscan_t scanner)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp, result, scanner);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule, hsql::SQLParserResult** result, yyscan_t scanner)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       , result, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule, result, scanner); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !HSQL_DEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !HSQL_DEBUG */


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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp, hsql::SQLParserResult** result, yyscan_t scanner)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  YYUSE (result);
  YYUSE (scanner);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (hsql::SQLParserResult** result, yyscan_t scanner)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined HSQL_LTYPE_IS_TRIVIAL && HSQL_LTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 79 "bison_parser.y" /* yacc.c:1429  */
{
	// Initialize
	yylloc.first_column = 0;
	yylloc.last_column = 0;
	yylloc.first_line = 0;
	yylloc.last_line = 0;
	yylloc.total_column = 0;
	yylloc.placeholder_id = 0;
}

#line 1685 "bison_parser.cpp" /* yacc.c:1429  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc, scanner);
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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 236 "bison_parser.y" /* yacc.c:1646  */
    {
			*result = (yyvsp[-1].stmt_list);
		}
#line 1876 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 243 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.stmt_list) = new SQLParserResult((yyvsp[0].statement)); }
#line 1882 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 244 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].stmt_list)->addStatement((yyvsp[0].statement)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1888 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 248 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].prep_stmt)->setPlaceholders(yyloc.placeholder_list);
			yyloc.placeholder_list.clear();
			(yyval.statement) = (yyvsp[0].prep_stmt);
		}
#line 1898 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 258 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].select_stmt); }
#line 1904 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 259 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].import_stmt); }
#line 1910 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 260 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].create_stmt); }
#line 1916 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 261 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].insert_stmt); }
#line 1922 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 262 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1928 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 263 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1934 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 264 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].update_stmt); }
#line 1940 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 265 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].drop_stmt); }
#line 1946 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 266 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].exec_stmt); }
#line 1952 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 267 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].single_stmt); }
#line 1958 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 274 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kCreateDatabase);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 1967 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 278 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kDropDatabase);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 1976 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 282 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kUseDatabase);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 1985 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 286 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kShowDatabase);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 1994 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 290 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kShowTable);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 2003 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 294 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.single_stmt) = new SingleStatement(SingleStatement::kReadFile);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
	}
#line 2012 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 298 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.single_stmt) = new SingleStatement(SingleStatement::kQuit);
	}
#line 2020 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 307 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-2].sval);
			(yyval.prep_stmt)->query = new SQLParserResult((yyvsp[0].statement));
		}
#line 2030 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 312 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-4].sval);
			(yyval.prep_stmt)->query = (yyvsp[-2].stmt_list);
		}
#line 2040 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 320 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[0].sval);
		}
#line 2049 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 324 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[-3].sval);
			(yyval.exec_stmt)->parameters = (yyvsp[-1].expr_vec);
		}
#line 2059 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 336 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.import_stmt) = new ImportStatement((ImportStatement::ImportType) (yyvsp[-4].uval));
			(yyval.import_stmt)->filePath = (yyvsp[-2].sval);
			(yyval.import_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2069 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 344 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ImportStatement::kImportCSV; }
#line 2075 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 348 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].expr)->name; }
#line 2081 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 358 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
			(yyval.create_stmt)->ifNotExists = (yyvsp[-4].bval);
			(yyval.create_stmt)->tableName = (yyvsp[-3].sval);
			(yyval.create_stmt)->columns = (yyvsp[-1].column_vec);
		}
#line 2092 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 364 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
            (yyval.create_stmt)->ifNotExists = (yyvsp[-6].bval);
            (yyval.create_stmt)->tableName = (yyvsp[-5].sval);
            (yyval.create_stmt)->columns = (yyvsp[-3].column_vec);
            (yyval.create_stmt)->primaryKey = (yyvsp[-1].sval);
        }
#line 2104 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 374 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2110 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 375 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2116 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 379 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.column_vec) = new std::vector<ColumnDefinition*>(); (yyval.column_vec)->push_back((yyvsp[0].column_t)); }
#line 2122 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 380 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].column_vec)->push_back((yyvsp[0].column_t)); (yyval.column_vec) = (yyvsp[-2].column_vec); }
#line 2128 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 384 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.column_t) = new ColumnDefinition((yyvsp[-3].sval), (ColumnDefinition::DataType) (yyvsp[-2].uval), (yyvsp[-1].ival), (yyvsp[0].bval));
        }
#line 2136 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 390 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.ival) = (yyvsp[-1].ival);
        }
#line 2144 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 393 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.ival) = 0;
        }
#line 2152 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 398 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.bval) = false;
        }
#line 2160 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 401 "bison_parser.y" /* yacc.c:1646  */
    {
             (yyval.bval) = true;
         }
#line 2168 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 406 "bison_parser.y" /* yacc.c:1646  */
    {
           (yyval.sval) = (yyvsp[-1].sval);
        }
#line 2176 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 412 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DINT; }
#line 2182 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 413 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DINT; }
#line 2188 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 414 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DFLOAT; }
#line 2194 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 415 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::STRING; }
#line 2200 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 416 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::VARCHAR; }
#line 2206 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 426 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kTable);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2215 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 430 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kPreparedStatement);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2224 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 442 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[-1].sval);
			(yyval.delete_stmt)->whereClause = (yyvsp[0].expr_vec);
		}
#line 2234 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 450 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2243 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 462 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertValues);
			(yyval.insert_stmt)->tableName = (yyvsp[-3].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-2].str_vec);
			(yyval.insert_stmt)->values = (yyvsp[0].literal_list_vec);
		}
#line 2254 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 468 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertSelect);
			(yyval.insert_stmt)->tableName = (yyvsp[-2].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-1].str_vec);
			(yyval.insert_stmt)->select = (yyvsp[0].select_stmt);
		}
#line 2265 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 478 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = (yyvsp[-1].str_vec); }
#line 2271 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 479 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = NULL; }
#line 2277 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 489 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.update_stmt) = new UpdateStatement();
		(yyval.update_stmt)->table = (yyvsp[-3].table);
		(yyval.update_stmt)->updates = (yyvsp[-1].update_vec);
		(yyval.update_stmt)->whereClause = (yyvsp[0].expr_vec);
	}
#line 2288 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 498 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.update_vec) = new std::vector<UpdateClause*>(); (yyval.update_vec)->push_back((yyvsp[0].update_t)); }
#line 2294 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 499 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].update_vec)->push_back((yyvsp[0].update_t)); (yyval.update_vec) = (yyvsp[-2].update_vec); }
#line 2300 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 503 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.update_t) = new UpdateClause();
			(yyval.update_t)->column = (yyvsp[-2].sval);
			(yyval.update_t)->value = (yyvsp[0].expr);
		}
#line 2310 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 520 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2316 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 521 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2322 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 525 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2332 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 530 "bison_parser.y" /* yacc.c:1646  */
    {
			// TODO: allow multiple unions (through linked list)
			// TODO: capture type of set_operator
			// TODO: might overwrite order and limit of first select here
			(yyval.select_stmt) = (yyvsp[-4].select_stmt);
			(yyval.select_stmt)->unionSelect = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2346 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 548 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::NO_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-4].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-3].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2359 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 556 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::SUM_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2372 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 564 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::AVG_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2385 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 572 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::MAX_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2398 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 580 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::MIN_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2411 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 591 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2417 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 592 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2423 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 601 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[0].table); }
#line 2429 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 606 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr_vec) = (yyvsp[0].expr_vec); }
#line 2435 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 607 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = NULL; }
#line 2441 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 611 "bison_parser.y" /* yacc.c:1646  */
    { 
			(yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); 
			(yyval.expr_vec) = (yyvsp[-2].expr_vec);
		}
#line 2450 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 615 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr_vec) = new std::vector<Expr*>(); 
			(yyval.expr_vec)->push_back((yyvsp[0].expr));
		}
#line 2459 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 622 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.group_t) = new GroupByDescription();
			(yyval.group_t)->columns = (yyvsp[-1].expr_vec);
			(yyval.group_t)->having = (yyvsp[0].expr);
		}
#line 2469 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 627 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.group_t) = NULL; }
#line 2475 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 631 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2481 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 632 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2487 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 635 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = new OrderDescription((yyvsp[0].order_type), (yyvsp[-1].expr)); }
#line 2493 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 636 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = NULL; }
#line 2499 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 640 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2505 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 641 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderDesc; }
#line 2511 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 642 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2517 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 647 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[0].expr)->ival, kNoOffset); delete (yyvsp[0].expr); }
#line 2523 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 648 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[-2].expr)->ival, (yyvsp[0].expr)->ival); delete (yyvsp[-2].expr); delete (yyvsp[0].expr); }
#line 2529 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 649 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = NULL; }
#line 2535 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 656 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2541 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 657 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2547 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 661 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.literal_list_vec) = new std::vector<std::vector<Expr*>*>; (yyval.literal_list_vec)->push_back((yyvsp[-1].expr_vec)); }
#line 2553 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 662 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-4].literal_list_vec)->push_back((yyvsp[-1].expr_vec)); (yyval.literal_list_vec) = (yyvsp[-4].literal_list_vec); }
#line 2559 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 666 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2565 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 667 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2571 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 671 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = (yyvsp[-1].expr);
			(yyval.expr)->alias = (yyvsp[0].sval);
		}
#line 2580 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 678 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2586 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 692 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::UMINUS, (yyvsp[0].expr)); }
#line 2592 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 697 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '-', (yyvsp[0].expr)); }
#line 2598 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 698 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '+', (yyvsp[0].expr)); }
#line 2604 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 699 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '/', (yyvsp[0].expr)); }
#line 2610 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 700 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '*', (yyvsp[0].expr)); }
#line 2616 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 701 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '%', (yyvsp[0].expr)); }
#line 2622 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 702 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '^', (yyvsp[0].expr)); }
#line 2628 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 704 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::OR, (yyvsp[0].expr)); }
#line 2634 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 705 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LIKE, (yyvsp[0].expr)); }
#line 2640 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 706 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), Expr::NOT_LIKE, (yyvsp[0].expr)); }
#line 2646 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 707 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), 'y', (yyvsp[0].expr));}
#line 2652 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 708 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), 'n', (yyvsp[0].expr));}
#line 2658 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 713 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '=', (yyvsp[0].expr)); }
#line 2664 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 714 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::NOT_EQUALS, (yyvsp[0].expr)); }
#line 2670 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 715 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '<', (yyvsp[0].expr)); }
#line 2676 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 716 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '>', (yyvsp[0].expr)); }
#line 2682 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 717 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LESS_EQ, (yyvsp[0].expr)); }
#line 2688 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 718 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::GREATER_EQ, (yyvsp[0].expr)); }
#line 2694 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 722 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeFunctionRef((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-2].bval)); }
#line 2700 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 726 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[0].sval)); }
#line 2706 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 727 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 2712 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 738 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].sval)); }
#line 2718 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 743 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].fval)); }
#line 2724 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 748 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].ival)); }
#line 2730 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 752 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteralNull();}
#line 2736 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 756 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr(kExprStar); }
#line 2742 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 761 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = Expr::makePlaceholder(yylloc.total_column);
			yyloc.placeholder_list.push_back((yyval.expr));
		}
#line 2751 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 773 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].table_vec)->push_back((yyvsp[-2].table));
			auto tbl = new TableRef(kTableCrossProduct);
			tbl->list = (yyvsp[0].table_vec);
			(yyval.table) = tbl;
		}
#line 2762 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 784 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2773 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 795 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table_vec) = new std::vector<TableRef*>(); (yyval.table_vec)->push_back((yyvsp[0].table)); }
#line 2779 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 796 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].table_vec)->push_back((yyvsp[0].table)); (yyval.table_vec) = (yyvsp[-2].table_vec); }
#line 2785 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 801 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableName);
			tbl->name = (yyvsp[-1].sval);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2796 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 811 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.table) = new TableRef(kTableName);
			(yyval.table)->name = (yyvsp[0].sval);
		}
#line 2805 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 824 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 2811 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 830 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2817 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 839 "bison_parser.y" /* yacc.c:1646  */
    { 
			(yyval.table) = new TableRef(kTableJoin);
			(yyval.table)->join = new JoinDefinition();
			(yyval.table)->join->type = (JoinType) (yyvsp[-4].uval);
			(yyval.table)->join->left = (yyvsp[-5].table);
			(yyval.table)->join->right = (yyvsp[-2].table);
			(yyval.table)->join->condition = (yyvsp[0].expr);
		}
#line 2830 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 850 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2836 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 851 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinOuter; }
#line 2842 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 852 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinLeft; }
#line 2848 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 853 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinRight; }
#line 2854 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 854 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2860 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 860 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2871 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 885 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = new std::vector<char*>(); (yyval.str_vec)->push_back((yyvsp[0].sval)); }
#line 2877 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 886 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].str_vec)->push_back((yyvsp[0].sval)); (yyval.str_vec) = (yyvsp[-2].str_vec); }
#line 2883 "bison_parser.cpp" /* yacc.c:1646  */
    break;


#line 2887 "bison_parser.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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
      yyerror (&yylloc, result, scanner, YY_("syntax error"));
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
        yyerror (&yylloc, result, scanner, yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc, result, scanner);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp, result, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
  yyerror (&yylloc, result, scanner, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc, result, scanner);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp, result, scanner);
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
#line 889 "bison_parser.y" /* yacc.c:1906  */

/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

