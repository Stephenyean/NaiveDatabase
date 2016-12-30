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
    SQL_CHAR = 351,
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
    SQL_DATABASES = 378,
    SQL_CHECK = 379,
    SQL_USE = 380,
    SQL_READ = 381,
    SQL_QUIT = 382,
    SQL_MAX = 383,
    SQL_MIN = 384,
    SQL_AVG = 385,
    SQL_SUM = 386,
    SQL_EQUALS = 387,
    SQL_LESS = 388,
    SQL_GREATER = 389,
    SQL_NOTNULL = 390,
    SQL_UMINUS = 391
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
	hsql::CheckInDef* check_t;
	hsql::SelectStatement::SelectType select_type;

	hsql::SQLParserResult* stmt_list;

	std::vector<char*>* str_vec;
	std::vector<hsql::TableRef*>* table_vec;
	std::vector<hsql::ColumnDefinition*>* column_vec;
	std::vector<hsql::UpdateClause*>* update_vec;
	std::vector<hsql::Expr*>* expr_vec;
	std::vector<std::vector<hsql::Expr*>*>* literal_list_vec;

#line 360 "bison_parser.cpp" /* yacc.c:355  */
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

#line 388 "bison_parser.cpp" /* yacc.c:358  */

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
#define YYLAST   510

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  157
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  174
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  317

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   391

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   143,     2,     2,
     148,   149,   141,   139,   155,   140,   150,   142,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   152,   151,
     134,   132,   135,   156,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   146,     2,   147,   144,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   153,     2,   154,     2,     2,     2,     2,
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
     125,   126,   127,   128,   129,   130,   131,   133,   136,   137,
     138,   145
};

#if HSQL_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   240,   240,   247,   248,   252,   257,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   278,   282,   286,
     290,   293,   297,   301,   310,   315,   323,   327,   339,   347,
     351,   362,   368,   375,   383,   393,   401,   407,   408,   412,
     413,   417,   423,   426,   432,   435,   441,   442,   443,   444,
     445,   446,   456,   460,   472,   480,   492,   498,   508,   509,
     519,   528,   529,   533,   545,   546,   550,   551,   555,   560,
     572,   573,   574,   578,   587,   600,   601,   602,   603,   607,
     608,   612,   617,   622,   623,   627,   631,   638,   643,   647,
     648,   651,   652,   656,   657,   658,   663,   664,   665,   672,
     673,   677,   678,   682,   683,   687,   694,   695,   696,   697,
     698,   702,   703,   704,   708,   712,   713,   714,   715,   716,
     717,   718,   720,   721,   722,   723,   724,   729,   730,   731,
     732,   733,   734,   738,   742,   743,   747,   748,   749,   750,
     754,   759,   760,   764,   768,   772,   777,   788,   789,   799,
     800,   806,   811,   812,   817,   827,   834,   835,   840,   841,
     845,   846,   854,   866,   867,   868,   869,   870,   876,   882,
     886,   895,   896,   901,   902
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
  "LEFT", "LIKE", "LOAD", "NULL", "PART", "PLAN", "SHOW", "CHAR", "TIME",
  "VIEW", "WITH", "ADD", "ALL", "AND", "ASC", "CSV", "FOR", "INT", "KEY",
  "NOT", "OFF", "SET", "TBL", "TOP", "AS", "BY", "IF", "IN", "IS", "OF",
  "ON", "OR", "TO", "DATABASE", "DATABASES", "CHECK", "USE", "READ",
  "QUIT", "MAX", "MIN", "AVG", "SUM", "'='", "EQUALS", "'<'", "'>'",
  "LESS", "GREATER", "NOTNULL", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'",
  "UMINUS", "'['", "']'", "'('", "')'", "'.'", "';'", "':'", "'{'", "'}'",
  "','", "'?'", "$accept", "input", "statement_list", "statement",
  "preparable_statement", "single_statement", "prepare_statement",
  "execute_statement", "import_statement", "import_file_type", "file_path",
  "create_statement", "opt_check_def", "opt_primary_key_def",
  "opt_not_exists", "column_def_commalist", "column_def", "width",
  "null_type", "column_type", "drop_statement", "delete_statement",
  "truncate_statement", "insert_statement", "opt_column_list",
  "update_statement", "update_clause_commalist", "update_clause",
  "select_statement", "select_with_paren", "select_no_paren",
  "set_operator", "select_clause", "opt_select_method", "opt_distinct",
  "opt_select_list", "from_clause", "opt_where", "my_where_clause",
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
     385,   386,    61,   387,    60,    62,   388,   389,   390,    43,
      45,    42,    47,    37,    94,   391,    91,    93,    40,    41,
      46,    59,    58,   123,   125,    44,    63
};
# endif

#define YYPACT_NINF -221

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-221)))

#define YYTABLE_NINF -170

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-170)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     228,    29,    32,    86,    95,   -35,    31,    33,    48,    87,
      32,   -31,   -37,   124,    54,  -221,   -25,   137,   -12,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,    26,   143,    -1,  -221,     2,  -104,
      42,   155,    32,    60,    32,  -221,    21,    56,  -221,    32,
     164,   167,  -221,  -221,   170,    27,    36,  -221,   228,  -221,
    -221,  -221,    72,  -221,   135,   126,  -221,   198,    15,   282,
     228,    94,    32,  -221,   128,  -221,   121,    64,   -89,  -221,
    -221,  -221,  -221,    21,  -221,    21,  -221,   144,    65,  -221,
     171,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,   226,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,    21,   159,   225,  -221,  -221,  -105,  -221,  -221,
     -12,   191,    91,    21,  -221,   246,   250,    37,    87,   255,
      40,    55,     6,   128,     0,  -221,    21,    21,    21,    21,
     172,   257,    12,    21,    21,    21,    21,    21,    21,    21,
      21,    21,    21,  -221,  -221,   131,   -47,  -221,   248,   126,
     214,  -221,    15,   111,  -221,   265,   175,   350,   185,  -221,
    -221,   -55,   125,  -221,    21,  -221,  -221,   -25,  -221,   119,
     160,     4,  -221,   134,   216,  -221,  -221,  -221,  -221,    21,
    -221,   366,    74,    74,   366,    21,  -221,    21,   -86,   262,
     366,    74,    74,    40,    40,   138,   138,   138,  -221,    15,
     226,  -221,  -221,  -221,  -221,  -221,   225,  -221,  -221,   211,
     -50,  -221,    21,    32,  -221,   275,    15,   130,   102,   140,
       6,  -221,  -221,  -221,  -221,  -221,   195,   173,  -221,   334,
     366,   262,  -221,  -221,  -221,  -221,  -221,  -221,  -221,  -221,
    -221,   145,  -221,    19,   -43,   146,   350,  -221,  -221,   -34,
     148,  -221,     4,  -221,   139,     7,    21,   128,   291,   190,
     192,   152,  -221,  -221,   270,   169,  -221,  -221,    15,   259,
       6,   -25,  -221,   197,   -23,   216,   177,   212,  -221,   174,
     316,  -221,   -30,  -221,   178,    21,    21,    21,  -221,  -221,
    -221,  -221,   321,   217,  -221,     4,   350,  -221,   350,   187,
     186,  -221,  -221,    21,   -11,   188,  -221
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,    80,
       0,     0,     0,     0,     0,    23,     0,     0,   172,     3,
       6,    16,     5,    15,     8,     9,    14,    11,    12,    10,
      13,     7,    64,    65,    92,     0,   156,    55,    26,     0,
      38,     0,     0,     0,     0,    79,     0,     0,   155,     0,
       0,     0,    20,    19,     0,     0,     0,     1,   171,     2,
      71,    72,     0,    70,     0,    98,    53,     0,     0,     0,
       0,     0,     0,    17,    84,    29,     0,    59,   134,   140,
     141,   143,   144,     0,   145,     0,   146,     0,    81,    99,
     161,   107,   108,   109,   115,   110,   111,   113,   136,   137,
     142,   138,   112,   139,     0,    52,    18,    21,    22,    67,
      66,     4,     0,    92,     0,    68,   157,     0,   103,    24,
     172,     0,     0,     0,    54,     0,     0,     0,    80,     0,
     114,     0,     0,    84,     0,   159,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   160,   105,     0,    84,    61,    95,    98,
      96,    27,     0,     0,    37,     0,    83,    86,     0,    30,
     173,     0,     0,    57,     0,   135,   106,     0,    82,   147,
     149,   161,   151,   167,    88,    75,    76,    77,    78,     0,
     100,   128,   131,   132,   123,     0,   158,     0,   125,   122,
     127,   129,   130,   117,   116,   119,   118,   120,   121,     0,
       0,    60,    94,    93,    91,    69,     0,   104,    25,     0,
       0,    39,     0,     0,    58,     0,     0,    56,     0,     0,
       0,   154,   163,   164,   166,   165,     0,     0,    73,     0,
     124,   126,    63,    62,    97,    50,    47,    48,    51,    49,
      46,    43,    31,     0,     0,     0,    85,    28,   174,     0,
       0,   133,     0,   152,   148,     0,     0,    84,     0,    45,
       0,     0,    40,    34,     0,     0,    32,   101,     0,   150,
       0,     0,   169,     0,    90,    88,     0,     0,    41,     0,
       0,    33,     0,   153,     0,     0,     0,     0,    87,    74,
      42,    44,     0,     0,   102,     0,   170,   162,    89,     0,
       0,   168,    36,     0,     0,     0,    35
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -221,  -221,   269,   286,   276,  -221,  -221,  -221,  -221,  -221,
    -221,  -221,  -221,    92,  -221,  -221,    96,  -221,  -221,  -221,
    -221,  -221,  -221,  -221,  -221,  -221,  -221,   150,  -148,   345,
      -5,  -221,   298,  -221,   222,  -221,   127,  -120,  -221,    79,
    -221,   254,  -221,   210,  -220,  -221,  -193,  -132,   -71,  -221,
    -221,  -221,  -221,  -221,  -221,   -67,   247,  -221,   -82,  -221,
    -221,  -221,  -221,  -196,  -221,   106,  -221,    -2,  -217,   200,
    -221,  -221,   113,  -221,   264,  -221
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    76,
     168,    25,   254,   255,    72,   220,   221,   269,   288,   251,
      26,    27,    28,    29,   127,    30,   156,   157,    31,    32,
      33,    64,    34,   189,    46,    87,   133,   124,   166,   238,
     298,    65,   214,   115,    88,   227,   117,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   178,   179,   264,   180,    47,   181,   153,   154,
     182,   236,   183,   307,    59,   171
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,   118,   190,    78,    79,    80,    81,   135,    48,    36,
      36,    56,   130,   184,   131,    78,    79,    80,    81,    79,
      80,    81,   219,   296,    78,    79,    80,    81,     9,   229,
     123,  -170,   160,   259,   263,    36,   211,    51,    60,    40,
      74,   158,    77,    49,   161,   279,   284,   105,    69,    70,
     162,   270,   167,   147,   148,   149,   150,   151,   152,   128,
      35,   129,   136,   137,   138,   191,   192,   193,   194,    61,
     122,   198,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,  -170,  -170,   293,   292,    52,    41,   311,    38,
       9,    50,    82,   314,   224,   217,   172,    62,    39,   252,
     225,    63,    45,   228,    82,   253,   273,    82,   210,   136,
     137,   138,   274,    82,    42,   277,    43,   141,   239,   304,
     197,   162,   173,    16,   240,   162,   241,    53,   185,   186,
     187,   188,   297,   294,   244,    44,    54,    57,   315,    58,
      83,    84,   242,   271,   297,   139,    66,   285,    85,    67,
      68,   256,    83,    84,   177,   281,    86,    71,    73,   118,
      85,    83,    84,   140,    75,   190,   104,   106,    86,    85,
     107,    86,   142,   108,   135,   143,   109,    86,   136,   137,
     138,   149,   150,   151,   152,   110,   112,   144,     9,   145,
     146,   142,   139,   114,   147,   148,   149,   150,   151,   152,
     232,   116,   121,   125,   176,   123,   233,   234,  -170,  -170,
     140,   118,   126,   147,   148,   149,   150,   151,   152,   142,
     134,   257,   143,   235,   306,   308,  -169,   132,   245,   155,
      62,    81,  -169,  -169,   144,   164,   145,   146,     1,   165,
     246,   147,   148,   149,   150,   151,   152,     2,  -169,  -169,
      79,   261,   247,   170,     3,   136,   137,   138,   175,     4,
     196,   139,   195,   209,   216,   218,     5,     6,   219,   136,
     137,   138,   223,   226,   230,     7,     8,   222,   258,   140,
     237,     9,   152,   265,   141,   260,    10,   266,   142,   262,
     248,   143,     1,   268,   280,   276,   278,   286,   287,   289,
     290,     2,   270,   144,   301,   145,   146,   249,     3,    11,
     147,   148,   149,   150,   151,   152,   295,   250,   291,   303,
       5,     6,   302,    12,   309,  -168,   300,   305,   212,     7,
       8,  -168,  -168,   310,   313,     9,   312,   316,   139,   120,
      10,   136,   137,   138,   111,   119,   275,  -168,  -168,   272,
     174,   213,   139,    13,    14,    15,   140,   136,   137,   138,
     243,    55,   113,    11,   299,   142,   267,   159,   143,   215,
     140,   282,   169,   136,   137,   138,    16,    12,   283,   142,
     144,   231,   145,   146,   163,     0,     0,   147,   148,   149,
     150,   151,   152,     0,   144,     0,   145,   146,     0,     0,
       0,   147,   148,   149,   150,   151,   152,    13,    14,    15,
       0,     0,     0,     0,     0,     0,     0,   132,     0,     0,
       0,     0,     0,     0,   139,     0,     0,     0,     0,     0,
      16,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     139,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,   142,     0,     0,   143,     0,   139,     0,   140,     0,
       0,     0,     0,     0,     0,     0,   144,   142,   145,   146,
     143,     0,     0,   147,   148,   149,   150,   151,   152,     0,
       0,     0,   144,   142,   145,   146,     0,     0,     0,   147,
     148,   149,   150,   151,   152,     0,     0,     0,   144,     0,
     145,   146,     0,     0,     0,   147,   148,   149,   150,   151,
     152
};

static const yytype_int16 yycheck[] =
{
       2,    68,   134,     3,     4,     5,     6,     3,    10,     3,
       3,    16,    83,   133,    85,     3,     4,     5,     6,     4,
       5,     6,     3,    46,     3,     4,     5,     6,    53,   177,
      77,   117,   114,   226,   230,     3,   156,    74,    12,    74,
      42,   112,    44,    74,   149,   262,   266,    49,   152,   153,
     155,    32,   123,   139,   140,   141,   142,   143,   144,   148,
      31,   150,     7,     8,     9,   136,   137,   138,   139,    43,
      72,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,     8,     9,   280,   278,   123,   122,   305,     3,
      53,   122,    92,   313,   149,   162,    59,    71,     3,   149,
     155,    75,    15,   174,    92,   155,   149,    92,   155,     7,
       8,     9,   155,    92,    83,   149,    83,   113,   189,   149,
     108,   155,   127,   148,   195,   155,   197,     3,   128,   129,
     130,   131,   155,   281,   216,    87,    82,     0,   149,   151,
     140,   141,   209,   124,   155,    90,     3,   267,   148,   150,
     148,   222,   140,   141,   148,   148,   156,   115,     3,   226,
     148,   140,   141,   108,   104,   297,   110,     3,   156,   148,
       3,   156,   117,     3,     3,   120,   149,   156,     7,     8,
       9,   141,   142,   143,   144,   149,   114,   132,    53,   134,
     135,   117,    90,    67,   139,   140,   141,   142,   143,   144,
      66,     3,   108,    82,   149,    77,    72,    73,   134,   135,
     108,   278,   148,   139,   140,   141,   142,   143,   144,   117,
     155,   223,   120,    89,   295,   296,    66,    83,    17,     3,
      71,     6,    72,    73,   132,    44,   134,   135,    10,   148,
      29,   139,   140,   141,   142,   143,   144,    19,    88,    89,
       4,   149,    41,     3,    26,     7,     8,     9,     3,    31,
       3,    90,    90,   132,    50,   154,    38,    39,     3,     7,
       8,     9,    87,   148,   155,    47,    48,   102,     3,   108,
      64,    53,   144,    88,   113,   155,    58,   114,   117,   149,
      79,   120,    10,   148,   155,   149,   148,     6,   108,   107,
     148,    19,    32,   132,    92,   134,   135,    96,    26,    81,
     139,   140,   141,   142,   143,   144,   119,   106,   149,     3,
      38,    39,   148,    95,     3,    66,   149,   149,    80,    47,
      48,    72,    73,   116,   148,    53,   149,   149,    90,    70,
      58,     7,     8,     9,    58,    69,   254,    88,    89,   253,
     128,   103,    90,   125,   126,   127,   108,     7,     8,     9,
     210,    16,    64,    81,   285,   117,   239,   113,   120,   159,
     108,   265,   125,     7,     8,     9,   148,    95,   265,   117,
     132,   181,   134,   135,   120,    -1,    -1,   139,   140,   141,
     142,   143,   144,    -1,   132,    -1,   134,   135,    -1,    -1,
      -1,   139,   140,   141,   142,   143,   144,   125,   126,   127,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,    -1,    -1,
      -1,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,    -1,
     148,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      90,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   117,    -1,    -1,   120,    -1,    90,    -1,   108,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   132,   117,   134,   135,
     120,    -1,    -1,   139,   140,   141,   142,   143,   144,    -1,
      -1,    -1,   132,   117,   134,   135,    -1,    -1,    -1,   139,
     140,   141,   142,   143,   144,    -1,    -1,    -1,   132,    -1,
     134,   135,    -1,    -1,    -1,   139,   140,   141,   142,   143,
     144
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    19,    26,    31,    38,    39,    47,    48,    53,
      58,    81,    95,   125,   126,   127,   148,   158,   159,   160,
     161,   162,   163,   164,   165,   168,   177,   178,   179,   180,
     182,   185,   186,   187,   189,    31,     3,   224,     3,     3,
      74,   122,    83,    83,    87,    15,   191,   223,   224,    74,
     122,    74,   123,     3,    82,   186,   187,     0,   151,   231,
      12,    43,    71,    75,   188,   198,     3,   150,   148,   152,
     153,   115,   171,     3,   224,   104,   166,   224,     3,     4,
       5,     6,    92,   140,   141,   148,   156,   192,   201,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   110,   224,     3,     3,     3,   149,
     149,   160,   114,   189,    67,   200,     3,   203,   212,   161,
     159,   108,   224,    77,   194,    82,   148,   181,   148,   150,
     205,   205,    83,   193,   155,     3,     7,     8,     9,    90,
     108,   113,   117,   120,   132,   134,   135,   139,   140,   141,
     142,   143,   144,   225,   226,     3,   183,   184,   205,   198,
     215,   149,   155,   231,    44,   148,   195,   205,   167,   213,
       3,   232,    59,   187,   191,     3,   149,   148,   219,   220,
     222,   224,   227,   229,   194,   128,   129,   130,   131,   190,
     204,   205,   205,   205,   205,    90,     3,   108,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   132,
     155,   194,    80,   103,   199,   200,    50,   212,   154,     3,
     172,   173,   102,    87,   149,   155,   148,   202,   205,   185,
     155,   226,    66,    72,    73,    89,   228,    64,   196,   205,
     205,   205,   212,   184,   215,    17,    29,    41,    79,    96,
     106,   176,   149,   155,   169,   170,   205,   224,     3,   203,
     155,   149,   149,   220,   221,    88,   114,   193,   148,   174,
      32,   124,   173,   149,   155,   170,   149,   149,   148,   225,
     155,   148,   222,   229,   201,   194,     6,   108,   175,   107,
     148,   149,   203,   220,   185,   119,    46,   155,   197,   196,
     149,    92,   148,     3,   149,   149,   205,   230,   205,     3,
     116,   225,   149,   148,   201,   149,   149
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   157,   158,   159,   159,   160,   160,   161,   161,   161,
     161,   161,   161,   161,   161,   161,   161,   162,   162,   162,
     162,   162,   162,   162,   163,   163,   164,   164,   165,   166,
     167,   168,   168,   168,   168,   169,   170,   171,   171,   172,
     172,   173,   174,   174,   175,   175,   176,   176,   176,   176,
     176,   176,   177,   177,   178,   179,   180,   180,   181,   181,
     182,   183,   183,   184,   185,   185,   186,   186,   187,   187,
     188,   188,   188,   189,   189,   190,   190,   190,   190,   191,
     191,   192,   193,   194,   194,   195,   195,   196,   196,   197,
     197,   198,   198,   199,   199,   199,   200,   200,   200,   201,
     201,   202,   202,   203,   203,   204,   205,   205,   205,   205,
     205,   206,   206,   206,   207,   208,   208,   208,   208,   208,
     208,   208,   208,   208,   208,   208,   208,   209,   209,   209,
     209,   209,   209,   210,   211,   211,   212,   212,   212,   212,
     213,   214,   214,   215,   216,   217,   218,   219,   219,   220,
     220,   220,   221,   221,   222,   223,   224,   224,   225,   225,
     226,   226,   227,   228,   228,   228,   228,   228,   229,   229,
     230,   231,   231,   232,   232
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     3,     3,     1,     4,     6,     2,     5,     7,     1,
       1,     7,     8,     9,     8,     9,     6,     3,     0,     1,
       3,     4,     3,     0,     2,     0,     1,     1,     1,     1,
       1,     1,     3,     3,     4,     2,     6,     5,     3,     0,
       5,     1,     3,     3,     1,     1,     3,     3,     3,     5,
       1,     1,     1,     6,     9,     1,     1,     1,     1,     1,
       0,     1,     2,     2,     0,     3,     1,     4,     0,     2,
       0,     4,     0,     1,     1,     0,     2,     4,     0,     1,
       3,     3,     5,     1,     3,     2,     3,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     3,     4,     3,     3,     3,
       3,     3,     3,     5,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       4,     1,     1,     3,     2,     1,     1,     3,     2,     1,
       1,     0,     6,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     1,     3
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

#line 1691 "bison_parser.cpp" /* yacc.c:1429  */
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
#line 240 "bison_parser.y" /* yacc.c:1646  */
    {
			*result = (yyvsp[-1].stmt_list);
		}
#line 1882 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 247 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.stmt_list) = new SQLParserResult((yyvsp[0].statement)); }
#line 1888 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 248 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].stmt_list)->addStatement((yyvsp[0].statement)); (yyval.stmt_list) = (yyvsp[-2].stmt_list); }
#line 1894 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 252 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].prep_stmt)->setPlaceholders(yyloc.placeholder_list);
			yyloc.placeholder_list.clear();
			(yyval.statement) = (yyvsp[0].prep_stmt);
		}
#line 1904 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 262 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].select_stmt); }
#line 1910 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 263 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].import_stmt); }
#line 1916 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 264 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].create_stmt); }
#line 1922 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 265 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].insert_stmt); }
#line 1928 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 266 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1934 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 267 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].delete_stmt); }
#line 1940 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 268 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].update_stmt); }
#line 1946 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 269 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].drop_stmt); }
#line 1952 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 270 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].exec_stmt); }
#line 1958 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 271 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.statement) = (yyvsp[0].single_stmt); }
#line 1964 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 278 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kCreateDatabase);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 1973 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 282 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kDropDatabase);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 1982 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 286 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kUseDatabase);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 1991 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 290 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kShowDatabase);
         }
#line 1999 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 293 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kShowTable);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 2008 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 297 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.single_stmt) = new SingleStatement(SingleStatement::kReadFile);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
	}
#line 2017 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 301 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.single_stmt) = new SingleStatement(SingleStatement::kQuit);
	}
#line 2025 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 310 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-2].sval);
			(yyval.prep_stmt)->query = new SQLParserResult((yyvsp[0].statement));
		}
#line 2035 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 315 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-4].sval);
			(yyval.prep_stmt)->query = (yyvsp[-2].stmt_list);
		}
#line 2045 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 323 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[0].sval);
		}
#line 2054 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 327 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[-3].sval);
			(yyval.exec_stmt)->parameters = (yyvsp[-1].expr_vec);
		}
#line 2064 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 339 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.import_stmt) = new ImportStatement((ImportStatement::ImportType) (yyvsp[-4].uval));
			(yyval.import_stmt)->filePath = (yyvsp[-2].sval);
			(yyval.import_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2074 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 347 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ImportStatement::kImportCSV; }
#line 2080 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 351 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].expr)->name; }
#line 2086 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 362 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
            (yyval.create_stmt)->ifNotExists = (yyvsp[-4].bval);
            (yyval.create_stmt)->tableName = (yyvsp[-3].sval);
            (yyval.create_stmt)->columns = (yyvsp[-1].column_vec);
        }
#line 2097 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 368 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
            (yyval.create_stmt)->ifNotExists = (yyvsp[-5].bval);
            (yyval.create_stmt)->tableName = (yyvsp[-4].sval);
            (yyval.create_stmt)->columns = (yyvsp[-2].column_vec);
            (yyval.create_stmt)->primaryKey = (yyvsp[-1].sval);
        }
#line 2109 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 375 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
            (yyval.create_stmt)->ifNotExists = (yyvsp[-6].bval);
            (yyval.create_stmt)->tableName = (yyvsp[-5].sval);
            (yyval.create_stmt)->columns = (yyvsp[-3].column_vec);
			(yyval.create_stmt)->checkIn = (yyvsp[-2].check_t);
			(yyval.create_stmt)->primaryKey = (yyvsp[-1].sval);
        }
#line 2122 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 383 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
            (yyval.create_stmt)->ifNotExists = (yyvsp[-5].bval);
            (yyval.create_stmt)->tableName = (yyvsp[-4].sval);
            (yyval.create_stmt)->columns = (yyvsp[-2].column_vec);
			(yyval.create_stmt)->checkIn = (yyvsp[-1].check_t);
        }
#line 2134 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 393 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.check_t) = new CheckInDef();
			(yyval.check_t)->relName = (yyvsp[-5].sval);
			(yyval.check_t)->checkInVec = (yyvsp[-2].expr_vec);
		}
#line 2144 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 401 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.sval) = (yyvsp[-1].sval);
		}
#line 2152 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 407 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2158 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 408 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2164 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 412 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.column_vec) = new std::vector<ColumnDefinition*>(); (yyval.column_vec)->push_back((yyvsp[0].column_t)); }
#line 2170 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 413 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].column_vec)->push_back((yyvsp[0].column_t)); (yyval.column_vec) = (yyvsp[-2].column_vec); }
#line 2176 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 417 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.column_t) = new ColumnDefinition((yyvsp[-3].sval), (ColumnDefinition::DataType) (yyvsp[-2].uval), (yyvsp[-1].ival), (yyvsp[0].bval));
        }
#line 2184 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 423 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.ival) = (yyvsp[-1].ival);
        }
#line 2192 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 426 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.ival) = 0;
        }
#line 2200 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 432 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.bval) = true;
        }
#line 2208 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 435 "bison_parser.y" /* yacc.c:1646  */
    {
             (yyval.bval) = false;
         }
#line 2216 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 441 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DINT; }
#line 2222 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 442 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DINT; }
#line 2228 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 443 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DFLOAT; }
#line 2234 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 444 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::STRING; }
#line 2240 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 445 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::VARCHAR; }
#line 2246 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 446 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DDATE; }
#line 2252 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 456 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kTable);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2261 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 460 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kPreparedStatement);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2270 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 472 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[-1].sval);
			(yyval.delete_stmt)->whereClause = (yyvsp[0].expr_vec);
		}
#line 2280 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 480 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2289 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 492 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertValues);
			(yyval.insert_stmt)->tableName = (yyvsp[-3].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-2].str_vec);
			(yyval.insert_stmt)->values = (yyvsp[0].literal_list_vec);
		}
#line 2300 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 498 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertSelect);
			(yyval.insert_stmt)->tableName = (yyvsp[-2].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-1].str_vec);
			(yyval.insert_stmt)->select = (yyvsp[0].select_stmt);
		}
#line 2311 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 508 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = (yyvsp[-1].str_vec); }
#line 2317 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 509 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = NULL; }
#line 2323 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 519 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.update_stmt) = new UpdateStatement();
		(yyval.update_stmt)->table = (yyvsp[-3].table);
		(yyval.update_stmt)->updates = (yyvsp[-1].update_vec);
		(yyval.update_stmt)->whereClause = (yyvsp[0].expr_vec);
	}
#line 2334 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 528 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.update_vec) = new std::vector<UpdateClause*>(); (yyval.update_vec)->push_back((yyvsp[0].update_t)); }
#line 2340 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 529 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].update_vec)->push_back((yyvsp[0].update_t)); (yyval.update_vec) = (yyvsp[-2].update_vec); }
#line 2346 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 533 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.update_t) = new UpdateClause();
			(yyval.update_t)->column = (yyvsp[-2].sval);
			(yyval.update_t)->value = (yyvsp[0].expr);
		}
#line 2356 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 550 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2362 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 551 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2368 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 555 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2378 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 560 "bison_parser.y" /* yacc.c:1646  */
    {
			// TODO: allow multiple unions (through linked list)
			// TODO: capture type of set_operator
			// TODO: might overwrite order and limit of first select here
			(yyval.select_stmt) = (yyvsp[-4].select_stmt);
			(yyval.select_stmt)->unionSelect = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2392 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 578 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::NO_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-4].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-3].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2405 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 587 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement((yyvsp[-4].select_type));
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = new std::vector<Expr*>();
			(yyval.select_stmt)->selectList->push_back((*(yyvsp[-6].expr_vec))[0]);
			(yyval.select_stmt)->selectList->push_back((yyvsp[-3].expr));
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2420 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 600 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.select_type) = SelectStatement::MAX_OP;}
#line 2426 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 76:
#line 601 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.select_type) = SelectStatement::MIN_OP;}
#line 2432 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 602 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.select_type) = SelectStatement::AVG_OP;}
#line 2438 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 603 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.select_type) = SelectStatement::SUM_OP;}
#line 2444 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 607 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2450 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 608 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2456 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 617 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[0].table); }
#line 2462 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 622 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr_vec) = (yyvsp[0].expr_vec); }
#line 2468 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 623 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = NULL; }
#line 2474 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 627 "bison_parser.y" /* yacc.c:1646  */
    { 
			(yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); 
			(yyval.expr_vec) = (yyvsp[-2].expr_vec);
		}
#line 2483 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 631 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr_vec) = new std::vector<Expr*>(); 
			(yyval.expr_vec)->push_back((yyvsp[0].expr));
		}
#line 2492 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 638 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.group_t) = new GroupByDescription();
			(yyval.group_t)->columns = (yyvsp[-1].expr_vec);
			(yyval.group_t)->having = (yyvsp[0].expr);
		}
#line 2502 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 643 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.group_t) = NULL; }
#line 2508 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 647 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2514 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 648 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2520 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 651 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = new OrderDescription((yyvsp[0].order_type), (yyvsp[-1].expr)); }
#line 2526 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 652 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = NULL; }
#line 2532 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 656 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2538 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 657 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderDesc; }
#line 2544 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 658 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2550 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 663 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[0].expr)->ival, kNoOffset); delete (yyvsp[0].expr); }
#line 2556 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 664 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[-2].expr)->ival, (yyvsp[0].expr)->ival); delete (yyvsp[-2].expr); delete (yyvsp[0].expr); }
#line 2562 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 665 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = NULL; }
#line 2568 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 672 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2574 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 673 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2580 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 677 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.literal_list_vec) = new std::vector<std::vector<Expr*>*>; (yyval.literal_list_vec)->push_back((yyvsp[-1].expr_vec)); }
#line 2586 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 102:
#line 678 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-4].literal_list_vec)->push_back((yyvsp[-1].expr_vec)); (yyval.literal_list_vec) = (yyvsp[-4].literal_list_vec); }
#line 2592 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 103:
#line 682 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2598 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 104:
#line 683 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2604 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 105:
#line 687 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = (yyvsp[-1].expr);
			(yyval.expr)->alias = (yyvsp[0].sval);
		}
#line 2613 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 106:
#line 694 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2619 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 708 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::UMINUS, (yyvsp[0].expr)); }
#line 2625 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 713 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '-', (yyvsp[0].expr)); }
#line 2631 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 714 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '+', (yyvsp[0].expr)); }
#line 2637 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 715 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '/', (yyvsp[0].expr)); }
#line 2643 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 716 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '*', (yyvsp[0].expr)); }
#line 2649 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 717 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '%', (yyvsp[0].expr)); }
#line 2655 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 718 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '^', (yyvsp[0].expr)); }
#line 2661 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 720 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::OR, (yyvsp[0].expr)); }
#line 2667 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 721 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LIKE, (yyvsp[0].expr)); }
#line 2673 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 722 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), Expr::NOT_LIKE, (yyvsp[0].expr)); }
#line 2679 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 723 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), 'y', (yyvsp[0].expr));}
#line 2685 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 724 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), 'n', (yyvsp[0].expr));}
#line 2691 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 729 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '=', (yyvsp[0].expr)); }
#line 2697 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 730 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::NOT_EQUALS, (yyvsp[0].expr)); }
#line 2703 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 731 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '<', (yyvsp[0].expr)); }
#line 2709 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 732 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '>', (yyvsp[0].expr)); }
#line 2715 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 131:
#line 733 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LESS_EQ, (yyvsp[0].expr)); }
#line 2721 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 132:
#line 734 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::GREATER_EQ, (yyvsp[0].expr)); }
#line 2727 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 133:
#line 738 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeFunctionRef((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-2].bval)); }
#line 2733 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 134:
#line 742 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[0].sval)); }
#line 2739 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 743 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 2745 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 754 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].sval)); }
#line 2751 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 759 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].fval)); }
#line 2757 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 764 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].ival)); }
#line 2763 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 144:
#line 768 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteralNull();}
#line 2769 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 772 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr(kExprStar); }
#line 2775 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 146:
#line 777 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = Expr::makePlaceholder(yylloc.total_column);
			yyloc.placeholder_list.push_back((yyval.expr));
		}
#line 2784 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 789 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].table_vec)->push_back((yyvsp[-2].table));
			auto tbl = new TableRef(kTableCrossProduct);
			tbl->list = (yyvsp[0].table_vec);
			(yyval.table) = tbl;
		}
#line 2795 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 800 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2806 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 152:
#line 811 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table_vec) = new std::vector<TableRef*>(); (yyval.table_vec)->push_back((yyvsp[0].table)); }
#line 2812 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 812 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].table_vec)->push_back((yyvsp[0].table)); (yyval.table_vec) = (yyvsp[-2].table_vec); }
#line 2818 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 154:
#line 817 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableName);
			tbl->name = (yyvsp[-1].sval);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2829 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 155:
#line 827 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.table) = new TableRef(kTableName);
			(yyval.table)->name = (yyvsp[0].sval);
		}
#line 2838 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 840 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 2844 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 846 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2850 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 855 "bison_parser.y" /* yacc.c:1646  */
    { 
			(yyval.table) = new TableRef(kTableJoin);
			(yyval.table)->join = new JoinDefinition();
			(yyval.table)->join->type = (JoinType) (yyvsp[-4].uval);
			(yyval.table)->join->left = (yyvsp[-5].table);
			(yyval.table)->join->right = (yyvsp[-2].table);
			(yyval.table)->join->condition = (yyvsp[0].expr);
		}
#line 2863 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 866 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2869 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 164:
#line 867 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinOuter; }
#line 2875 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 165:
#line 868 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinLeft; }
#line 2881 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 166:
#line 869 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinRight; }
#line 2887 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 167:
#line 870 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2893 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 876 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2904 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 173:
#line 901 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = new std::vector<char*>(); (yyval.str_vec)->push_back((yyvsp[0].sval)); }
#line 2910 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 174:
#line 902 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].str_vec)->push_back((yyvsp[0].sval)); (yyval.str_vec) = (yyvsp[-2].str_vec); }
#line 2916 "bison_parser.cpp" /* yacc.c:1646  */
    break;


#line 2920 "bison_parser.cpp" /* yacc.c:1646  */
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
#line 905 "bison_parser.y" /* yacc.c:1906  */

/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

