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
    SQL_USE = 379,
    SQL_READ = 380,
    SQL_QUIT = 381,
    SQL_MAX = 382,
    SQL_MIN = 383,
    SQL_AVG = 384,
    SQL_SUM = 385,
    SQL_EQUALS = 386,
    SQL_LESS = 387,
    SQL_GREATER = 388,
    SQL_NOTNULL = 389,
    SQL_UMINUS = 390
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

#line 357 "bison_parser.cpp" /* yacc.c:355  */
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

#line 385 "bison_parser.cpp" /* yacc.c:358  */

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
#define YYLAST   502

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  156
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  74
/* YYNRULES -- Number of rules.  */
#define YYNRULES  169
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  321

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   390

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,   142,     2,     2,
     147,   148,   140,   138,   154,   139,   149,   141,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   151,   150,
     133,   131,   134,   155,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   145,     2,   146,   143,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   152,     2,   153,     2,     2,     2,     2,
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
     125,   126,   127,   128,   129,   130,   132,   135,   136,   137,
     144
};

#if HSQL_DEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   236,   236,   243,   244,   248,   253,   258,   259,   260,
     261,   262,   263,   264,   265,   266,   267,   274,   278,   282,
     286,   289,   293,   297,   306,   311,   319,   323,   335,   343,
     347,   357,   363,   373,   374,   378,   379,   383,   389,   392,
     397,   400,   405,   411,   412,   413,   414,   415,   425,   429,
     441,   449,   461,   467,   477,   478,   488,   497,   498,   502,
     514,   515,   519,   520,   524,   529,   541,   542,   543,   547,
     555,   563,   571,   579,   590,   591,   595,   600,   605,   606,
     610,   614,   621,   626,   630,   631,   634,   635,   639,   640,
     641,   646,   647,   648,   655,   656,   660,   661,   665,   666,
     670,   677,   678,   679,   680,   681,   685,   686,   687,   691,
     695,   696,   697,   698,   699,   700,   701,   703,   704,   705,
     706,   707,   712,   713,   714,   715,   716,   717,   721,   725,
     726,   730,   731,   732,   733,   737,   742,   743,   747,   751,
     755,   760,   771,   772,   782,   783,   789,   794,   795,   800,
     810,   817,   818,   823,   824,   828,   829,   837,   849,   850,
     851,   852,   853,   859,   865,   869,   878,   879,   884,   885
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
  "ON", "OR", "TO", "DATABASE", "DATABASES", "USE", "READ", "QUIT", "MAX",
  "MIN", "AVG", "SUM", "'='", "EQUALS", "'<'", "'>'", "LESS", "GREATER",
  "NOTNULL", "'+'", "'-'", "'*'", "'/'", "'%'", "'^'", "UMINUS", "'['",
  "']'", "'('", "')'", "'.'", "';'", "':'", "'{'", "'}'", "','", "'?'",
  "$accept", "input", "statement_list", "statement",
  "preparable_statement", "single_statement", "prepare_statement",
  "execute_statement", "import_statement", "import_file_type", "file_path",
  "create_statement", "opt_not_exists", "column_def_commalist",
  "column_def", "width", "null_type", "primary_key_def", "column_type",
  "drop_statement", "delete_statement", "truncate_statement",
  "insert_statement", "opt_column_list", "update_statement",
  "update_clause_commalist", "update_clause", "select_statement",
  "select_with_paren", "select_no_paren", "set_operator", "select_clause",
  "opt_distinct", "select_list", "from_clause", "opt_where",
  "my_where_clause", "opt_group", "opt_having", "opt_order",
  "opt_order_type", "opt_limit", "expr_list", "literal_lists",
  "literal_list", "expr_alias", "expr", "scalar_expr", "unary_expr",
  "binary_expr", "comp_expr", "function_expr", "column_name", "literal",
  "string_literal", "num_literal", "int_literal", "nul_literal",
  "star_expr", "placeholder_expr", "table_ref", "table_ref_atomic",
  "table_ref_commalist", "table_ref_name", "table_ref_name_no_alias",
  "table_name", "alias", "opt_alias", "join_clause", "opt_join_type",
  "join_table", "join_condition", "opt_semicolon", "ident_commalist", YY_NULL
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
     385,    61,   386,    60,    62,   387,   388,   389,    43,    45,
      42,    47,    37,    94,   390,    91,    93,    40,    41,    46,
      59,    58,   123,   125,    44,    63
};
# endif

#define YYPACT_NINF -228

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-228)))

#define YYTABLE_NINF -165

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-165)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     265,     1,    60,    61,    95,   -33,   -46,   -27,    21,    84,
      60,   -29,   -38,   108,    30,  -228,   -28,   113,   -13,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,    15,   120,   -11,  -228,    -6,  -100,
      27,   141,    60,    41,    60,  -228,     0,    38,  -228,    60,
     147,   155,  -228,  -228,   156,    19,    26,  -228,   265,  -228,
    -228,  -228,    48,  -228,   112,   102,  -228,   175,     8,   305,
     265,    71,    60,  -228,   103,  -228,   100,    36,   -53,  -228,
    -228,  -228,  -228,    42,    43,    51,    52,    17,  -228,    17,
    -228,   105,    31,  -228,   168,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,   197,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,    17,   137,   203,  -228,
    -228,  -119,  -228,  -228,   -13,   166,    85,    17,  -228,   214,
     228,    -5,    84,   230,    17,    17,    17,    17,    80,    53,
      -1,   103,    17,  -228,    17,    17,    17,    17,   145,   233,
      13,    17,    17,    17,    17,    17,    17,    17,    17,    17,
      17,  -228,  -228,   106,   -47,  -228,   285,   102,   189,  -228,
       8,    91,  -228,   258,   172,   325,   193,  -228,  -228,  -104,
     130,  -228,    17,  -228,   134,   135,   138,   139,  -228,   -28,
    -228,   136,    29,    12,  -228,   153,   225,  -228,   359,   340,
     340,   359,    17,  -228,    17,    64,   126,   359,   340,   340,
      80,    80,   152,   152,   152,  -228,     8,   197,  -228,  -228,
    -228,  -228,  -228,   203,  -228,  -228,    14,   -95,  -228,    17,
      60,  -228,   294,     8,   144,   107,   105,   105,   105,   105,
     157,    -1,  -228,  -228,  -228,  -228,  -228,   212,   200,  -228,
     359,   126,  -228,  -228,  -228,  -228,  -228,  -228,  -228,  -228,
     169,  -228,    25,   325,  -228,  -228,   -83,   170,  -228,   103,
     103,   103,   103,    12,  -228,   165,     7,    17,   314,   213,
     215,  -228,   181,  -228,     8,   225,   225,   225,   225,   190,
      -1,   -28,  -228,   211,   -22,   187,   244,  -228,   191,  -228,
     -57,  -228,  -228,  -228,  -228,  -228,   192,    17,    17,  -228,
    -228,  -228,   334,  -228,    12,   325,  -228,   325,   194,  -228,
    -228
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
       0,     0,    20,    19,     0,     0,     0,     1,   166,     2,
      67,    68,     0,    66,     0,    93,    49,     0,     0,     0,
       0,     0,     0,    17,    79,    29,     0,    55,   129,   135,
     136,   138,   139,     0,     0,     0,     0,     0,   140,     0,
     141,     0,    76,    94,   156,   102,   103,   104,   110,   105,
     106,   108,   131,   132,   137,   133,   107,   134,     0,    48,
      18,    21,    22,    63,    62,     4,     0,    87,     0,    64,
     152,     0,    98,    24,   167,     0,     0,     0,    50,     0,
       0,     0,    75,     0,     0,     0,     0,     0,   109,     0,
       0,    79,     0,   154,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,   100,     0,    79,    57,    90,    93,    91,    27,
       0,     0,    33,     0,    78,    81,     0,    30,   168,     0,
       0,    53,     0,   130,     0,     0,     0,     0,   101,     0,
      77,   142,   144,   156,   146,   162,    83,    95,   123,   126,
     127,   118,     0,   153,     0,   120,   117,   122,   124,   125,
     112,   111,   114,   113,   115,   116,     0,     0,    56,    89,
      88,    86,    65,     0,    99,    25,     0,     0,    35,     0,
       0,    54,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,   149,   158,   159,   161,   160,     0,     0,    69,
     119,   121,    59,    58,    92,    47,    44,    45,    46,    43,
      39,    31,     0,    80,    28,   169,     0,     0,   128,    79,
      79,    79,    79,     0,   147,   143,     0,     0,     0,    41,
       0,    36,     0,    96,     0,    83,    83,    83,    83,   145,
       0,     0,   164,     0,    85,     0,     0,    37,     0,    32,
       0,    72,    73,    71,    70,   148,     0,     0,     0,    82,
      38,    40,     0,    97,     0,   165,   157,    84,     0,   163,
      42
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -228,  -228,   269,   283,   276,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,    88,  -228,  -228,  -228,  -228,  -228,
    -228,  -228,  -228,  -228,  -228,  -228,   140,  -155,   331,    -9,
    -228,   287,   222,   117,    34,   -58,  -228,    40,  -228,   238,
    -228,   195,    79,  -228,  -200,   217,   -78,  -228,  -228,  -228,
    -228,  -228,  -228,   -67,   232,  -228,   -92,  -228,  -228,  -228,
    -228,  -202,  -228,    93,  -228,    -2,  -227,   171,  -228,  -228,
      94,  -228,   247,  -228
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    17,    18,    19,    20,    21,    22,    23,    24,    76,
     176,    25,    72,   227,   228,   279,   297,   282,   260,    26,
      27,    28,    29,   131,    30,   164,   165,    31,    32,    33,
      64,    34,    46,    91,   141,   128,   174,   249,   309,    65,
     221,   119,    92,   234,   121,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     190,   191,   275,   192,    47,   193,   161,   162,   194,   247,
     195,   316,    59,   179
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      37,   122,    36,    78,    79,    80,    81,    56,    48,   138,
      36,   139,    79,    80,    81,   143,    78,    79,    80,    81,
      78,    79,    80,    81,   308,     9,   168,    60,   226,   169,
     127,   255,    35,   266,   240,   170,    51,    42,   166,   274,
      74,    40,    77,   256,   231,    49,   289,   109,     9,   175,
     232,    69,    70,   261,   180,   257,    43,   280,    61,   262,
     144,   145,   146,    36,    38,   283,   198,   199,   200,   201,
     126,   170,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   215,   196,   300,    52,    62,   319,   305,    41,
      63,   313,    82,    50,   132,  -164,   133,   170,    39,    45,
      82,  -164,  -164,   224,   235,    82,   218,   217,    44,    82,
     258,    53,    54,    57,   144,   145,   146,  -164,  -164,    16,
     259,   204,   181,    66,   250,   149,   251,    83,    84,    85,
      86,   254,   142,   144,   145,   146,   306,    58,    67,    87,
      88,    68,    71,   147,    73,    75,   189,    89,   108,   252,
     110,   263,    87,    88,   291,    90,    87,    88,   111,   112,
      89,   148,   116,    90,    89,     9,   122,   113,    90,   118,
     150,   143,    90,   151,   114,   144,   145,   146,   120,   125,
     127,  -165,   129,   130,   152,   142,   153,   154,   140,   134,
     135,   155,   156,   157,   158,   159,   160,   147,   136,   137,
     163,   188,   155,   156,   157,   158,   159,   160,    62,    81,
     172,   285,   286,   287,   288,   148,   147,   122,    79,   243,
     157,   158,   159,   160,   150,   244,   245,   151,   264,   315,
     317,   178,   173,   183,   148,   202,   203,   216,   152,   223,
     153,   154,   246,   150,   225,   155,   156,   157,   158,   159,
     160,   184,   185,   186,   187,   268,  -163,   152,   147,   153,
     154,   226,  -163,  -163,   155,   156,   157,   158,   159,   160,
     269,   270,   271,   272,   229,     1,   148,   233,  -163,  -163,
     230,   149,   236,   237,     2,   150,   238,   239,   151,   248,
     241,     3,   144,   145,   146,   160,     4,   265,   267,   152,
     276,   153,   154,     5,     6,   273,   155,   156,   157,   158,
     159,   160,     7,     8,   277,     1,   278,   284,     9,   290,
     295,   296,   298,    10,     2,   301,   302,   303,   304,   299,
     307,     3,   144,   145,   146,   310,   311,   318,   312,   124,
     314,   115,   320,     5,     6,   123,    11,    55,  -165,  -165,
     281,   117,     7,     8,   182,   167,   294,   253,     9,   197,
      12,   177,   222,    10,   242,   219,   144,   145,   146,   292,
     293,   171,     0,     0,     0,   147,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,     0,   220,    13,
      14,    15,     0,   148,     0,     0,     0,     0,     0,     0,
      12,     0,   150,     0,     0,   151,     0,     0,     0,     0,
       0,     0,    16,     0,     0,   147,   152,     0,   153,   154,
       0,     0,     0,   155,   156,   157,   158,   159,   160,    13,
      14,    15,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,   150,     0,     0,   151,     0,     0,     0,   147,
       0,     0,    16,     0,     0,     0,   152,   150,   153,   154,
       0,     0,     0,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,  -165,  -165,     0,   150,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,     0,     0,
     152,     0,   153,   154,     0,     0,     0,   155,   156,   157,
     158,   159,   160
};

static const yytype_int16 yycheck[] =
{
       2,    68,     3,     3,     4,     5,     6,    16,    10,    87,
       3,    89,     4,     5,     6,     3,     3,     4,     5,     6,
       3,     4,     5,     6,    46,    53,   118,    12,     3,   148,
      77,    17,    31,   233,   189,   154,    74,    83,   116,   241,
      42,    74,    44,    29,   148,    74,   273,    49,    53,   127,
     154,   151,   152,   148,    59,    41,    83,    32,    43,   154,
       7,     8,     9,     3,     3,   148,   144,   145,   146,   147,
      72,   154,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   141,   284,   123,    71,   314,   290,   122,
      75,   148,    92,   122,   147,    66,   149,   154,     3,    15,
      92,    72,    73,   170,   182,    92,   164,   154,    87,    92,
      96,     3,    82,     0,     7,     8,     9,    88,    89,   147,
     106,   108,   131,     3,   202,   113,   204,   127,   128,   129,
     130,   223,   154,     7,     8,     9,   291,   150,   149,   139,
     140,   147,   115,    90,     3,   104,   147,   147,   110,   216,
       3,   229,   139,   140,   147,   155,   139,   140,     3,     3,
     147,   108,   114,   155,   147,    53,   233,   148,   155,    67,
     117,     3,   155,   120,   148,     7,     8,     9,     3,   108,
      77,   117,    82,   147,   131,   154,   133,   134,    83,   147,
     147,   138,   139,   140,   141,   142,   143,    90,   147,   147,
       3,   148,   138,   139,   140,   141,   142,   143,    71,     6,
      44,   269,   270,   271,   272,   108,    90,   284,     4,    66,
     140,   141,   142,   143,   117,    72,    73,   120,   230,   307,
     308,     3,   147,     3,   108,    90,     3,   131,   131,    50,
     133,   134,    89,   117,   153,   138,   139,   140,   141,   142,
     143,   134,   135,   136,   137,   148,    66,   131,    90,   133,
     134,     3,    72,    73,   138,   139,   140,   141,   142,   143,
     236,   237,   238,   239,   102,    10,   108,   147,    88,    89,
      87,   113,   148,   148,    19,   117,   148,   148,   120,    64,
     154,    26,     7,     8,     9,   143,    31,     3,   154,   131,
      88,   133,   134,    38,    39,   148,   138,   139,   140,   141,
     142,   143,    47,    48,   114,    10,   147,   147,    53,   154,
       6,   108,   107,    58,    19,   285,   286,   287,   288,   148,
     119,    26,     7,     8,     9,   148,    92,     3,   147,    70,
     148,    58,   148,    38,    39,    69,    81,    16,     8,     9,
     262,    64,    47,    48,   132,   117,   277,   217,    53,   142,
      95,   129,   167,    58,   193,    80,     7,     8,     9,   276,
     276,   124,    -1,    -1,    -1,    90,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,   103,   124,
     125,   126,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      95,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,    -1,
      -1,    -1,   147,    -1,    -1,    90,   131,    -1,   133,   134,
      -1,    -1,    -1,   138,   139,   140,   141,   142,   143,   124,
     125,   126,    -1,   108,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   117,    -1,    -1,   120,    -1,    -1,    -1,    90,
      -1,    -1,   147,    -1,    -1,    -1,   131,   117,   133,   134,
      -1,    -1,    -1,   138,   139,   140,   141,   142,   143,    -1,
      -1,    -1,    -1,   133,   134,    -1,   117,    -1,   138,   139,
     140,   141,   142,   143,    -1,    -1,    -1,    -1,    -1,    -1,
     131,    -1,   133,   134,    -1,    -1,    -1,   138,   139,   140,
     141,   142,   143
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    10,    19,    26,    31,    38,    39,    47,    48,    53,
      58,    81,    95,   124,   125,   126,   147,   157,   158,   159,
     160,   161,   162,   163,   164,   167,   175,   176,   177,   178,
     180,   183,   184,   185,   187,    31,     3,   221,     3,     3,
      74,   122,    83,    83,    87,    15,   188,   220,   221,    74,
     122,    74,   123,     3,    82,   184,   185,     0,   150,   228,
      12,    43,    71,    75,   186,   195,     3,   149,   147,   151,
     152,   115,   168,     3,   221,   104,   165,   221,     3,     4,
       5,     6,    92,   127,   128,   129,   130,   139,   140,   147,
     155,   189,   198,   201,   202,   203,   204,   205,   206,   207,
     208,   209,   210,   211,   212,   213,   214,   215,   110,   221,
       3,     3,     3,   148,   148,   159,   114,   187,    67,   197,
       3,   200,   209,   160,   158,   108,   221,    77,   191,    82,
     147,   179,   147,   149,   147,   147,   147,   147,   202,   202,
      83,   190,   154,     3,     7,     8,     9,    90,   108,   113,
     117,   120,   131,   133,   134,   138,   139,   140,   141,   142,
     143,   222,   223,     3,   181,   182,   202,   195,   212,   148,
     154,   228,    44,   147,   192,   202,   166,   210,     3,   229,
      59,   185,   188,     3,   189,   189,   189,   189,   148,   147,
     216,   217,   219,   221,   224,   226,   191,   201,   202,   202,
     202,   202,    90,     3,   108,   202,   202,   202,   202,   202,
     202,   202,   202,   202,   202,   202,   131,   154,   191,    80,
     103,   196,   197,    50,   209,   153,     3,   169,   170,   102,
      87,   148,   154,   147,   199,   202,   148,   148,   148,   148,
     183,   154,   223,    66,    72,    73,    89,   225,    64,   193,
     202,   202,   209,   182,   212,    17,    29,    41,    96,   106,
     174,   148,   154,   202,   221,     3,   200,   154,   148,   190,
     190,   190,   190,   148,   217,   218,    88,   114,   147,   171,
      32,   170,   173,   148,   147,   191,   191,   191,   191,   222,
     154,   147,   219,   226,   198,     6,   108,   172,   107,   148,
     200,   193,   193,   193,   193,   217,   183,   119,    46,   194,
     148,    92,   147,   148,   148,   202,   227,   202,     3,   222,
     148
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   156,   157,   158,   158,   159,   159,   160,   160,   160,
     160,   160,   160,   160,   160,   160,   160,   161,   161,   161,
     161,   161,   161,   161,   162,   162,   163,   163,   164,   165,
     166,   167,   167,   168,   168,   169,   169,   170,   171,   171,
     172,   172,   173,   174,   174,   174,   174,   174,   175,   175,
     176,   177,   178,   178,   179,   179,   180,   181,   181,   182,
     183,   183,   184,   184,   185,   185,   186,   186,   186,   187,
     187,   187,   187,   187,   188,   188,   189,   190,   191,   191,
     192,   192,   193,   193,   194,   194,   195,   195,   196,   196,
     196,   197,   197,   197,   198,   198,   199,   199,   200,   200,
     201,   202,   202,   202,   202,   202,   203,   203,   203,   204,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   205,   206,   206,   206,   206,   206,   206,   207,   208,
     208,   209,   209,   209,   209,   210,   211,   211,   212,   213,
     214,   215,   216,   216,   217,   217,   217,   218,   218,   219,
     220,   221,   221,   222,   222,   223,   223,   224,   225,   225,
     225,   225,   225,   226,   226,   227,   228,   228,   229,   229
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     3,     3,     1,     4,     6,     2,     5,     7,     1,
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
         }
#line 1993 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 289 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.single_stmt) = new SingleStatement(SingleStatement::kShowTable);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
         }
#line 2002 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 293 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.single_stmt) = new SingleStatement(SingleStatement::kReadFile);
			(yyval.single_stmt)->name = (yyvsp[0].sval);
	}
#line 2011 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 297 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.single_stmt) = new SingleStatement(SingleStatement::kQuit);
	}
#line 2019 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 306 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-2].sval);
			(yyval.prep_stmt)->query = new SQLParserResult((yyvsp[0].statement));
		}
#line 2029 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 311 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.prep_stmt) = new PrepareStatement();
			(yyval.prep_stmt)->name = (yyvsp[-4].sval);
			(yyval.prep_stmt)->query = (yyvsp[-2].stmt_list);
		}
#line 2039 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 319 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[0].sval);
		}
#line 2048 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 323 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.exec_stmt) = new ExecuteStatement();
			(yyval.exec_stmt)->name = (yyvsp[-3].sval);
			(yyval.exec_stmt)->parameters = (yyvsp[-1].expr_vec);
		}
#line 2058 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 335 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.import_stmt) = new ImportStatement((ImportStatement::ImportType) (yyvsp[-4].uval));
			(yyval.import_stmt)->filePath = (yyvsp[-2].sval);
			(yyval.import_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2068 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 343 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ImportStatement::kImportCSV; }
#line 2074 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 347 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].expr)->name; }
#line 2080 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 357 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
			(yyval.create_stmt)->ifNotExists = (yyvsp[-4].bval);
			(yyval.create_stmt)->tableName = (yyvsp[-3].sval);
			(yyval.create_stmt)->columns = (yyvsp[-1].column_vec);
		}
#line 2091 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 363 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.create_stmt) = new CreateStatement(CreateStatement::kTable);
            (yyval.create_stmt)->ifNotExists = (yyvsp[-6].bval);
            (yyval.create_stmt)->tableName = (yyvsp[-5].sval);
            (yyval.create_stmt)->columns = (yyvsp[-3].column_vec);
            (yyval.create_stmt)->primaryKey = (yyvsp[-1].sval);
        }
#line 2103 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 373 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2109 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 374 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2115 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 378 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.column_vec) = new std::vector<ColumnDefinition*>(); (yyval.column_vec)->push_back((yyvsp[0].column_t)); }
#line 2121 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 379 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].column_vec)->push_back((yyvsp[0].column_t)); (yyval.column_vec) = (yyvsp[-2].column_vec); }
#line 2127 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 383 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.column_t) = new ColumnDefinition((yyvsp[-3].sval), (ColumnDefinition::DataType) (yyvsp[-2].uval), (yyvsp[-1].ival), (yyvsp[0].bval));
        }
#line 2135 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 389 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.ival) = (yyvsp[-1].ival);
        }
#line 2143 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 392 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.ival) = 0;
        }
#line 2151 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 397 "bison_parser.y" /* yacc.c:1646  */
    {
            (yyval.bval) = true;
        }
#line 2159 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 400 "bison_parser.y" /* yacc.c:1646  */
    {
             (yyval.bval) = false;
         }
#line 2167 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 405 "bison_parser.y" /* yacc.c:1646  */
    {
           (yyval.sval) = (yyvsp[-1].sval);
        }
#line 2175 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 411 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DINT; }
#line 2181 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 412 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DINT; }
#line 2187 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 413 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::DFLOAT; }
#line 2193 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 414 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::STRING; }
#line 2199 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 415 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = ColumnDefinition::VARCHAR; }
#line 2205 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 425 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kTable);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2214 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 429 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.drop_stmt) = new DropStatement(DropStatement::kPreparedStatement);
			(yyval.drop_stmt)->name = (yyvsp[0].sval);
		}
#line 2223 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 441 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[-1].sval);
			(yyval.delete_stmt)->whereClause = (yyvsp[0].expr_vec);
		}
#line 2233 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 449 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.delete_stmt) = new DeleteStatement();
			(yyval.delete_stmt)->tableName = (yyvsp[0].sval);
		}
#line 2242 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 461 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertValues);
			(yyval.insert_stmt)->tableName = (yyvsp[-3].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-2].str_vec);
			(yyval.insert_stmt)->values = (yyvsp[0].literal_list_vec);
		}
#line 2253 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 467 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.insert_stmt) = new InsertStatement(InsertStatement::kInsertSelect);
			(yyval.insert_stmt)->tableName = (yyvsp[-2].sval);
			(yyval.insert_stmt)->columns = (yyvsp[-1].str_vec);
			(yyval.insert_stmt)->select = (yyvsp[0].select_stmt);
		}
#line 2264 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 477 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = (yyvsp[-1].str_vec); }
#line 2270 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 478 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = NULL; }
#line 2276 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 488 "bison_parser.y" /* yacc.c:1646  */
    {
		(yyval.update_stmt) = new UpdateStatement();
		(yyval.update_stmt)->table = (yyvsp[-3].table);
		(yyval.update_stmt)->updates = (yyvsp[-1].update_vec);
		(yyval.update_stmt)->whereClause = (yyvsp[0].expr_vec);
	}
#line 2287 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 497 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.update_vec) = new std::vector<UpdateClause*>(); (yyval.update_vec)->push_back((yyvsp[0].update_t)); }
#line 2293 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 498 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].update_vec)->push_back((yyvsp[0].update_t)); (yyval.update_vec) = (yyvsp[-2].update_vec); }
#line 2299 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 502 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.update_t) = new UpdateClause();
			(yyval.update_t)->column = (yyvsp[-2].sval);
			(yyval.update_t)->value = (yyvsp[0].expr);
		}
#line 2309 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 519 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2315 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 520 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.select_stmt) = (yyvsp[-1].select_stmt); }
#line 2321 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 524 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2331 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 529 "bison_parser.y" /* yacc.c:1646  */
    {
			// TODO: allow multiple unions (through linked list)
			// TODO: capture type of set_operator
			// TODO: might overwrite order and limit of first select here
			(yyval.select_stmt) = (yyvsp[-4].select_stmt);
			(yyval.select_stmt)->unionSelect = (yyvsp[-2].select_stmt);
			(yyval.select_stmt)->order = (yyvsp[-1].order);
			(yyval.select_stmt)->limit = (yyvsp[0].limit);
		}
#line 2345 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 547 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::NO_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-4].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-3].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2358 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 555 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::SUM_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2371 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 563 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::AVG_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2384 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 571 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::MAX_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2397 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 579 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.select_stmt) = new SelectStatement(SelectStatement::MIN_OP);
			(yyval.select_stmt)->selectDistinct = (yyvsp[-7].bval);
			(yyval.select_stmt)->selectList = (yyvsp[-4].expr_vec);
			(yyval.select_stmt)->fromTable = (yyvsp[-2].table);
			(yyval.select_stmt)->whereClause = (yyvsp[-1].expr_vec);
			(yyval.select_stmt)->groupBy = (yyvsp[0].group_t);
		}
#line 2410 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 590 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = true; }
#line 2416 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 75:
#line 591 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.bval) = false; }
#line 2422 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 77:
#line 600 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table) = (yyvsp[0].table); }
#line 2428 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 78:
#line 605 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr_vec) = (yyvsp[0].expr_vec); }
#line 2434 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 79:
#line 606 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = NULL; }
#line 2440 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 80:
#line 610 "bison_parser.y" /* yacc.c:1646  */
    { 
			(yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); 
			(yyval.expr_vec) = (yyvsp[-2].expr_vec);
		}
#line 2449 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 81:
#line 614 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr_vec) = new std::vector<Expr*>(); 
			(yyval.expr_vec)->push_back((yyvsp[0].expr));
		}
#line 2458 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 82:
#line 621 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.group_t) = new GroupByDescription();
			(yyval.group_t)->columns = (yyvsp[-1].expr_vec);
			(yyval.group_t)->having = (yyvsp[0].expr);
		}
#line 2468 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 83:
#line 626 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.group_t) = NULL; }
#line 2474 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 84:
#line 630 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[0].expr); }
#line 2480 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 85:
#line 631 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = NULL; }
#line 2486 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 86:
#line 634 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = new OrderDescription((yyvsp[0].order_type), (yyvsp[-1].expr)); }
#line 2492 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 87:
#line 635 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order) = NULL; }
#line 2498 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 88:
#line 639 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2504 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 89:
#line 640 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderDesc; }
#line 2510 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 90:
#line 641 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.order_type) = kOrderAsc; }
#line 2516 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 91:
#line 646 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[0].expr)->ival, kNoOffset); delete (yyvsp[0].expr); }
#line 2522 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 92:
#line 647 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = new LimitDescription((yyvsp[-2].expr)->ival, (yyvsp[0].expr)->ival); delete (yyvsp[-2].expr); delete (yyvsp[0].expr); }
#line 2528 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 93:
#line 648 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.limit) = NULL; }
#line 2534 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 94:
#line 655 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2540 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 95:
#line 656 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2546 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 96:
#line 660 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.literal_list_vec) = new std::vector<std::vector<Expr*>*>; (yyval.literal_list_vec)->push_back((yyvsp[-1].expr_vec)); }
#line 2552 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 97:
#line 661 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-4].literal_list_vec)->push_back((yyvsp[-1].expr_vec)); (yyval.literal_list_vec) = (yyvsp[-4].literal_list_vec); }
#line 2558 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 98:
#line 665 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr_vec) = new std::vector<Expr*>(); (yyval.expr_vec)->push_back((yyvsp[0].expr)); }
#line 2564 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 99:
#line 666 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].expr_vec)->push_back((yyvsp[0].expr)); (yyval.expr_vec) = (yyvsp[-2].expr_vec); }
#line 2570 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 100:
#line 670 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = (yyvsp[-1].expr);
			(yyval.expr)->alias = (yyvsp[0].sval);
		}
#line 2579 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 101:
#line 677 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = (yyvsp[-1].expr); }
#line 2585 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 109:
#line 691 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpUnary(Expr::UMINUS, (yyvsp[0].expr)); }
#line 2591 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 111:
#line 696 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '-', (yyvsp[0].expr)); }
#line 2597 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 112:
#line 697 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '+', (yyvsp[0].expr)); }
#line 2603 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 113:
#line 698 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '/', (yyvsp[0].expr)); }
#line 2609 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 114:
#line 699 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '*', (yyvsp[0].expr)); }
#line 2615 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 115:
#line 700 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '%', (yyvsp[0].expr)); }
#line 2621 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 116:
#line 701 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '^', (yyvsp[0].expr)); }
#line 2627 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 117:
#line 703 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::OR, (yyvsp[0].expr)); }
#line 2633 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 118:
#line 704 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LIKE, (yyvsp[0].expr)); }
#line 2639 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 119:
#line 705 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), Expr::NOT_LIKE, (yyvsp[0].expr)); }
#line 2645 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 120:
#line 706 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), 'y', (yyvsp[0].expr));}
#line 2651 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 121:
#line 707 "bison_parser.y" /* yacc.c:1646  */
    {(yyval.expr) = Expr::makeOpBinary((yyvsp[-3].expr), 'n', (yyvsp[0].expr));}
#line 2657 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 122:
#line 712 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '=', (yyvsp[0].expr)); }
#line 2663 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 123:
#line 713 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::NOT_EQUALS, (yyvsp[0].expr)); }
#line 2669 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 124:
#line 714 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '<', (yyvsp[0].expr)); }
#line 2675 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 125:
#line 715 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), '>', (yyvsp[0].expr)); }
#line 2681 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 126:
#line 716 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::LESS_EQ, (yyvsp[0].expr)); }
#line 2687 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 127:
#line 717 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeOpBinary((yyvsp[-2].expr), Expr::GREATER_EQ, (yyvsp[0].expr)); }
#line 2693 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 128:
#line 721 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeFunctionRef((yyvsp[-4].sval), (yyvsp[-1].expr), (yyvsp[-2].bval)); }
#line 2699 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 129:
#line 725 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[0].sval)); }
#line 2705 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 130:
#line 726 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeColumnRef((yyvsp[-2].sval), (yyvsp[0].sval)); }
#line 2711 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 135:
#line 737 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].sval)); }
#line 2717 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 136:
#line 742 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].fval)); }
#line 2723 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 138:
#line 747 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteral((yyvsp[0].ival)); }
#line 2729 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 139:
#line 751 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = Expr::makeLiteralNull();}
#line 2735 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 140:
#line 755 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.expr) = new Expr(kExprStar); }
#line 2741 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 141:
#line 760 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.expr) = Expr::makePlaceholder(yylloc.total_column);
			yyloc.placeholder_list.push_back((yyval.expr));
		}
#line 2750 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 143:
#line 772 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyvsp[0].table_vec)->push_back((yyvsp[-2].table));
			auto tbl = new TableRef(kTableCrossProduct);
			tbl->list = (yyvsp[0].table_vec);
			(yyval.table) = tbl;
		}
#line 2761 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 145:
#line 783 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2772 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 147:
#line 794 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.table_vec) = new std::vector<TableRef*>(); (yyval.table_vec)->push_back((yyvsp[0].table)); }
#line 2778 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 148:
#line 795 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].table_vec)->push_back((yyvsp[0].table)); (yyval.table_vec) = (yyvsp[-2].table_vec); }
#line 2784 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 149:
#line 800 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableName);
			tbl->name = (yyvsp[-1].sval);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2795 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 150:
#line 810 "bison_parser.y" /* yacc.c:1646  */
    {
			(yyval.table) = new TableRef(kTableName);
			(yyval.table)->name = (yyvsp[0].sval);
		}
#line 2804 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 153:
#line 823 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); }
#line 2810 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 156:
#line 829 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2816 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 157:
#line 838 "bison_parser.y" /* yacc.c:1646  */
    { 
			(yyval.table) = new TableRef(kTableJoin);
			(yyval.table)->join = new JoinDefinition();
			(yyval.table)->join->type = (JoinType) (yyvsp[-4].uval);
			(yyval.table)->join->left = (yyvsp[-5].table);
			(yyval.table)->join->right = (yyvsp[-2].table);
			(yyval.table)->join->condition = (yyvsp[0].expr);
		}
#line 2829 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 158:
#line 849 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2835 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 159:
#line 850 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinOuter; }
#line 2841 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 160:
#line 851 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinLeft; }
#line 2847 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 161:
#line 852 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinRight; }
#line 2853 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 162:
#line 853 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.uval) = kJoinInner; }
#line 2859 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 163:
#line 859 "bison_parser.y" /* yacc.c:1646  */
    {
			auto tbl = new TableRef(kTableSelect);
			tbl->select = (yyvsp[-2].select_stmt);
			tbl->alias = (yyvsp[0].sval);
			(yyval.table) = tbl;
		}
#line 2870 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 168:
#line 884 "bison_parser.y" /* yacc.c:1646  */
    { (yyval.str_vec) = new std::vector<char*>(); (yyval.str_vec)->push_back((yyvsp[0].sval)); }
#line 2876 "bison_parser.cpp" /* yacc.c:1646  */
    break;

  case 169:
#line 885 "bison_parser.y" /* yacc.c:1646  */
    { (yyvsp[-2].str_vec)->push_back((yyvsp[0].sval)); (yyval.str_vec) = (yyvsp[-2].str_vec); }
#line 2882 "bison_parser.cpp" /* yacc.c:1646  */
    break;


#line 2886 "bison_parser.cpp" /* yacc.c:1646  */
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
#line 888 "bison_parser.y" /* yacc.c:1906  */

/*********************************
 ** Section 4: Additional C code
 *********************************/

/* empty */

