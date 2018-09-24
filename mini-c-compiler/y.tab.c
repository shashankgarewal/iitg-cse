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
#line 1 "comp.c" /* yacc.c:339  */

void yyerror(char *s);
extern int mylineno;
extern int yylineno;
extern char *yytext;
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
#include <assert.h>
FILE* fout;
FILE* asmout;
int cur_scope = 0;
int cur_off = 0;
int not_label = 0;
int text_printed = 0;
int tot_func = 0;
int label_cnt = 0;

int is_for[100];
int loop_no[100];
int loop_cnt = 0;


#line 90 "y.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 79 "comp.c" /* yacc.c:355  */


#define NUM_REG 18

enum ele_type {INT_T,FLOAT_T,CHAR_T,BOOL,ERROR};
enum op_type {_NOT,_PLUS,_MINUS,_AND_AND,_OR_OR,_EEQ,_NEQ,_LEQ,_GRQ,_LE,_GR,_TIMES,_DIV}; 


struct func_node{
    char name[50];
    
    enum ele_type et;
    int ptr_depth;

    int valid;

    struct node *param_list;
    int num_params;

    struct func_node *next;
};    
struct node
{
    char name[50];
    
    enum ele_type et;
    int ptr_depth;

    int size;
    int* dim_list;
    int st_off;
    int typeSize;
    int prod;
    char* reg_off;
    int valid_off;

    
    int valid;          /* whether this entry is deleted or not*/
    int scope;

    int expr_val; //init to -1000000


    int num_func;

    char* reg_name;
    
    struct node *next;
};
struct list_attr{
    struct node* list_var;
    int size;
};
struct list_brac{
        int size;
        int* dim_list;
        char** reg_name;
};



char  Names[NUM_REG][4];
int used[NUM_REG];


struct func_node *func_table;
struct node cur_func;
struct node *symb_table;

void insert_symb_table(struct node* var);
void add_params_to_sym(struct list_attr lis);
void check_distinct(struct node *attrs, int size);
struct func_node* get_func_entry(char *name);
void insert_func_entry(struct node type,struct node id,struct list_attr attrs);
struct node check_func_exists(char *name);
int match_node_list(struct node *list_var,int lsize,struct node *param_list,int psize,int isProto);
int check_func_proto(struct node type,struct node id,struct list_attr attrs);
int check_param_match(struct node fn,struct list_attr attrs);
int match_node(struct node *n1,struct node *n2);
int exists_in_scope(struct node var);
void patch_type(struct node type,struct list_attr lis);
struct node get_sym(char* var_name,struct list_brac* lsb);
void delete_entries();
void delete_entries_on_ret();
struct node print_comp_error(struct node exp1, struct node exp2);
struct node compatible(struct node exp1,struct node exp2);
struct node print_opt_error(struct node exp1,enum op_type op, struct node exp2);
struct node comp_binopt_type(struct node exp1,enum op_type op, struct node exp2);
struct node comp_opt_type(enum op_type op,struct node exp);
int match_node_exact(struct node n1,struct node n2);
int add(int a,int b);
int mul(int a,int b);
int sub(int a,int b);
int _div(int a,int b);
void freename(char *s);
char *newname();


#line 219 "y.tab.c" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    EOI = 258,
    SEMI = 259,
    MAIN = 260,
    PLUS = 261,
    TIMES = 262,
    LP = 263,
    RP = 264,
    MINUS = 265,
    DIV = 266,
    NEQ = 267,
    LE = 268,
    LEQ = 269,
    GR = 270,
    GRQ = 271,
    EQ = 272,
    IF = 273,
    OPEN_CURL = 274,
    CLOSE_CURL = 275,
    ELSE = 276,
    WHILE = 277,
    DO = 278,
    EEQ = 279,
    SWITCH = 280,
    CASE = 281,
    DEFAULT = 282,
    FOR = 283,
    BREAK = 284,
    CONTINUE = 285,
    LSQBRAC = 286,
    RSQBRAC = 287,
    DOT = 288,
    COLON = 289,
    COMMA = 290,
    PLUSPLUS = 291,
    MINUSMINUS = 292,
    RETURN = 293,
    NOT = 294,
    ID = 295,
    INT = 296,
    FLOAT = 297,
    STRING = 298,
    AMP = 299,
    INT_TYPE = 300,
    FLOAT_TYPE = 301,
    CHAR_TYPE = 302,
    CHAR = 303,
    AND_AND = 304,
    OR_OR = 305,
    PRINT = 306,
    ENDL = 307
  };
#endif
/* Tokens.  */
#define EOI 258
#define SEMI 259
#define MAIN 260
#define PLUS 261
#define TIMES 262
#define LP 263
#define RP 264
#define MINUS 265
#define DIV 266
#define NEQ 267
#define LE 268
#define LEQ 269
#define GR 270
#define GRQ 271
#define EQ 272
#define IF 273
#define OPEN_CURL 274
#define CLOSE_CURL 275
#define ELSE 276
#define WHILE 277
#define DO 278
#define EEQ 279
#define SWITCH 280
#define CASE 281
#define DEFAULT 282
#define FOR 283
#define BREAK 284
#define CONTINUE 285
#define LSQBRAC 286
#define RSQBRAC 287
#define DOT 288
#define COLON 289
#define COMMA 290
#define PLUSPLUS 291
#define MINUSMINUS 292
#define RETURN 293
#define NOT 294
#define ID 295
#define INT 296
#define FLOAT 297
#define STRING 298
#define AMP 299
#define INT_TYPE 300
#define FLOAT_TYPE 301
#define CHAR_TYPE 302
#define CHAR 303
#define AND_AND 304
#define OR_OR 305
#define PRINT 306
#define ENDL 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 178 "comp.c" /* yacc.c:355  */
   
    struct list_brac lb;


    int list_num;
    int label_num;
    struct node n1;

    struct list_attr lis_attr;

#line 346 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 363 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  17
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   262

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  46
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  219

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   198,   198,   198,   199,   201,   207,   208,   209,   210,
     211,   212,   214,   214,   216,   219,   229,   232,   237,   244,
     259,   262,   278,   279,   280,   283,   307,   320,   329,   331,
     343,   364,   392,   402,   403,   411,   418,   427,   430,   447,
     470,   489,   500,   507,   527,   548,   553,   564,   565,   566,
     569,   602,   638,   652,   659,   669,   679,   691,   700,   713,
     719,   723,   729,   731,   767,   797,   806,   811,   812,   814,
     815,   816,   820,   834,   839,   864,   865,   866,   869,   870,
     871,   874,   875,   876,   877,   878,   881,   882,   885,   886,
     889,   890,   891,   893,   949,   964,  1023,  1029,  1033,  1047,
    1061,  1082,  1103,  1112,  1116,  1119
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EOI", "SEMI", "MAIN", "PLUS", "TIMES",
  "LP", "RP", "MINUS", "DIV", "NEQ", "LE", "LEQ", "GR", "GRQ", "EQ", "IF",
  "OPEN_CURL", "CLOSE_CURL", "ELSE", "WHILE", "DO", "EEQ", "SWITCH",
  "CASE", "DEFAULT", "FOR", "BREAK", "CONTINUE", "LSQBRAC", "RSQBRAC",
  "DOT", "COLON", "COMMA", "PLUSPLUS", "MINUSMINUS", "RETURN", "NOT", "ID",
  "INT", "FLOAT", "STRING", "AMP", "INT_TYPE", "FLOAT_TYPE", "CHAR_TYPE",
  "CHAR", "AND_AND", "OR_OR", "PRINT", "ENDL", "$accept", "st", "epsilon",
  "decl", "type", "ptr", "decl_list", "id", "ide_id_decl", "arr_index",
  "br_list", "proto_head", "proto", "func_head", "int_head", "st2",
  "func_body", "list_params", "fis", "arr_index_dyn", "br_list_dyn",
  "ide_id", "ide_id_amp", "ide_id_lhs", "list_call_params", "s",
  "function_call", "for_head", "for_cond", "for_exp", "for_stmnt",
  "while_head", "while_exp", "while_stmnt", "ifexp", "iftrue", "mif",
  "opc", "other_than_if", "expression", "expression_and", "term", "factor",
  "arithmetic", "multdiv", "final", YY_NULLPTR
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
     305,   306,   307
};
# endif

#define YYPACT_NINF -93

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-93)))

#define YYTABLE_NINF -45

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     121,    -1,    15,    15,    63,     3,    37,    61,   -93,    75,
      79,   -93,    97,    15,   -93,   -93,   -93,   -93,   121,   -93,
     -93,    -3,    72,   121,   163,   121,   163,   107,   -93,   -93,
     143,   205,    83,   -93,    37,    37,   -93,   205,    77,   118,
     -93,   123,   126,   125,   132,    37,    37,   205,   130,   -93,
     -93,    37,    15,   -93,   105,   -93,   139,     4,     8,    56,
     -93,   -93,    25,   134,   -93,   205,   205,   136,   -93,   205,
     136,   -93,   136,   148,   163,   163,   163,   168,   -36,    48,
     145,   164,   170,    47,    37,   -93,   157,   -93,    37,   174,
     171,     8,    20,   154,   -93,   -93,    83,   188,   189,   -93,
     205,   -93,    37,   -93,   -93,   166,   -93,   -93,   202,   205,
     166,   -93,   212,   213,   -93,   205,   205,   -16,   -93,   201,
     205,   205,   166,    49,   205,   -93,   -93,   -93,   215,   211,
     163,   214,   163,   163,   136,   -93,   204,   -93,   -93,   205,
     205,   205,   205,   205,   205,   205,   205,   205,   205,   205,
     205,   217,   -93,   186,   203,   166,   -93,   -93,   218,   209,
     -93,   -93,   219,   -93,   -93,   -93,   220,   221,   205,   222,
     197,   206,   -93,   229,   -93,   -93,   216,   -93,   223,   228,
     163,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   143,   143,   -93,   -93,   205,   -93,
     -93,   -93,   230,   -93,   205,   -93,   -93,   -93,   -93,   -93,
     234,   226,   -93,   233,   -93,   -93,   -93,   -93,   -93
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     6,     7,     8,     0,     0,     0,     0,     3,     0,
       0,    24,     0,    12,     9,    10,    11,     1,     0,    16,
       5,    17,    14,     0,     4,     0,     4,     0,    13,     2,
       0,     0,    20,    18,     0,     0,    23,     0,     0,     0,
      62,     0,     0,     0,     0,     0,     0,     0,     0,    32,
      33,     0,     6,    34,     0,    47,     0,     0,     0,    39,
     104,    97,     0,     0,   105,     0,     0,     0,    68,     0,
       0,    67,     0,    61,     4,     4,     4,     0,    77,    80,
      81,    86,    88,    90,     0,    28,     0,    26,     0,     0,
       0,     0,     0,     0,    21,    15,    17,     0,     0,    35,
       0,    55,     0,    66,    65,    43,    98,    99,     0,     0,
      41,    94,     0,     0,    70,     0,     0,    39,    93,     0,
       0,     0,    37,    40,     0,   100,   101,    29,     0,     0,
       4,     0,     4,     4,     0,    49,     0,    48,    71,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    27,    30,    22,    39,    19,   103,     0,     0,
      44,    74,     0,    42,    73,    72,     0,     0,     0,     0,
      45,     0,    38,     0,    52,    53,     0,    56,     0,     0,
       4,    69,    75,    76,    79,    78,    85,    82,    84,    83,
      87,    89,    91,    92,     0,     0,    40,    58,     0,   102,
      96,    95,     0,    50,     0,    36,    64,    54,    57,    59,
       0,     0,    31,     0,    63,    46,    60,    25,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -93,   237,   -93,    29,     0,     7,   224,    33,   151,   -93,
     208,   -93,   236,   -93,   -93,   231,   -93,   -92,   -93,   -93,
     -67,   -55,   -93,    -5,    53,   -24,   -93,   -93,   -93,   -93,
     -93,   -93,   -93,   -93,   -93,   -93,   -93,   -35,   -93,   -20,
     -31,    19,   113,   114,   -27,   -93
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     4,    55,    56,    90,    91,    20,    59,    22,    32,
      33,     7,     8,     9,    10,    11,    25,    89,    60,   122,
     123,    61,   111,    92,   169,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       6,   -43,    86,   118,    12,    30,    13,    18,    14,    15,
      16,    93,   115,   139,   140,   121,   116,    98,     6,    62,
      28,    62,    13,    35,    57,    84,    57,   108,    31,     5,
      88,    58,   130,    58,   113,   132,   118,   133,   160,    21,
     106,   107,   124,   163,    19,   128,   129,     5,    19,   131,
     135,   136,   137,   119,   149,   172,   125,   126,   150,    14,
     141,   125,   126,    17,   120,    23,   -44,    96,    97,    62,
      62,    62,   142,   -43,    57,    57,    57,    19,   105,   105,
     158,    58,    58,    58,   110,   -44,   -44,   121,   196,   162,
      96,   117,   -43,   -43,    24,   166,   167,   159,    26,   180,
     170,   171,   211,   212,   173,    27,   176,    34,   178,   179,
     184,   185,    13,    37,    31,    38,    87,   151,    99,   182,
     183,    96,   192,   193,   155,    62,   100,    62,    62,   103,
      57,   101,    57,    57,   102,   105,   104,    58,   109,    58,
      58,    45,    46,   114,    48,    19,    49,    50,   202,    51,
      52,     2,     3,    53,   127,    40,   210,   112,   143,   144,
     145,   146,   186,   187,   188,   189,     1,     2,     3,   134,
      13,    37,   138,    38,   147,    62,   148,   152,   213,   115,
      57,    39,    40,   154,   170,    41,   156,    58,    52,     2,
       3,    42,    43,    44,    88,    88,    30,   121,   157,    45,
      46,    47,    48,    19,    49,    50,   161,    51,    52,     2,
       3,    53,    13,    37,    54,    38,   164,   165,   168,   174,
     175,   195,   -25,   177,   181,   194,   198,   197,   199,   200,
     201,   203,   204,   206,   214,   217,   207,   218,   205,   153,
      94,    45,    46,   208,    48,    19,    49,    50,   209,    51,
      52,     2,     3,    53,   216,    29,    85,   215,    95,    36,
     190,     0,   191
};

static const yytype_int16 yycheck[] =
{
       0,    17,    26,    58,     5,     8,     7,     4,     1,     2,
       3,    31,     8,    49,    50,    31,     8,    37,    18,    24,
      13,    26,     7,    23,    24,    25,    26,    47,    31,     0,
      30,    24,    67,    26,    54,    70,    91,    72,   105,     6,
      45,    46,    17,   110,    40,    65,    66,    18,    40,    69,
      74,    75,    76,    58,     7,   122,    36,    37,    11,    52,
      12,    36,    37,     0,     8,     4,    17,    34,    35,    74,
      75,    76,    24,    17,    74,    75,    76,    40,    45,    46,
     100,    74,    75,    76,    51,    36,    37,    31,   155,   109,
      57,    58,    36,    37,    19,   115,   116,   102,    19,   134,
     120,   121,   194,   195,   124,     8,   130,    35,   132,   133,
     141,   142,     7,     8,    31,    10,     9,    84,    41,   139,
     140,    88,   149,   150,    91,   130,     8,   132,   133,     4,
     130,     8,   132,   133,     8,   102,     4,   130,     8,   132,
     133,    36,    37,     4,    39,    40,    41,    42,   168,    44,
      45,    46,    47,    48,    20,    19,   180,    52,    13,    14,
      15,    16,   143,   144,   145,   146,    45,    46,    47,    21,
       7,     8,     4,    10,    10,   180,     6,    20,   198,     8,
     180,    18,    19,     9,   204,    22,    32,   180,    45,    46,
      47,    28,    29,    30,   194,   195,     8,    31,     9,    36,
      37,    38,    39,    40,    41,    42,     4,    44,    45,    46,
      47,    48,     7,     8,    51,    10,     4,     4,    17,     4,
       9,    35,    19,     9,    20,     8,    17,     9,     9,     9,
       9,     9,    35,     4,     4,     9,    20,     4,    32,    88,
      32,    36,    37,    20,    39,    40,    41,    42,    20,    44,
      45,    46,    47,    48,    20,    18,    25,   204,    34,    23,
     147,    -1,   148
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    45,    46,    47,    54,    56,    57,    64,    65,    66,
      67,    68,     5,     7,    58,    58,    58,     0,     4,    40,
      59,    60,    61,     4,    19,    69,    19,     8,    58,    54,
       8,    31,    62,    63,    35,    57,    65,     8,    10,    18,
      19,    22,    28,    29,    30,    36,    37,    38,    39,    41,
      42,    44,    45,    48,    51,    55,    56,    57,    58,    60,
      71,    74,    76,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    57,    68,    78,     9,    57,    70,
      57,    58,    76,    92,    63,    59,    60,    60,    92,    41,
       8,     8,     8,     4,     4,    60,    76,    76,    92,     8,
      60,    75,    52,    92,     4,     8,     8,    60,    74,    76,
       8,    31,    72,    73,    17,    36,    37,    20,    92,    92,
      90,    92,    90,    90,    21,    78,    78,    78,     4,    49,
      50,    12,    24,    13,    14,    15,    16,    10,     6,     7,
      11,    60,    20,    61,     9,    60,    32,     9,    92,    76,
      73,     4,    92,    73,     4,     4,    92,    92,    17,    77,
      92,    92,    73,    92,     4,     9,    78,     9,    78,    78,
      90,    20,    92,    92,    93,    93,    94,    94,    94,    94,
      95,    96,    97,    97,     8,    35,    73,     9,    17,     9,
       9,     9,    92,     9,    35,    32,     4,    20,    20,    20,
      78,    70,    70,    92,     4,    77,    20,     9,     4
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    55,    56,    57,    57,    57,    57,
      57,    57,    58,    58,    59,    59,    60,    61,    61,    62,
      63,    63,    64,    65,    65,    66,    67,    68,    68,    69,
      70,    70,    71,    71,    71,    71,    72,    73,    73,    74,
      74,    75,    75,    76,    76,    77,    77,    78,    78,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    89,    90,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    92,    92,    92,    93,    93,
      93,    94,    94,    94,    94,    94,    95,    95,    96,    96,
      97,    97,    97,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     1,     0,     2,     1,     1,     1,     2,
       2,     2,     1,     2,     1,     3,     1,     1,     2,     3,
       1,     2,     5,     3,     1,     5,     4,     4,     3,     3,
       2,     4,     1,     1,     1,     2,     3,     1,     2,     1,
       2,     1,     2,     1,     2,     1,     3,     1,     2,     2,
       4,     6,     3,     3,     4,     2,     3,     4,     4,     4,
       5,     1,     1,     5,     4,     2,     2,     1,     1,     3,
       2,     2,     3,     3,     3,     3,     3,     1,     3,     3,
       1,     1,     3,     3,     3,     3,     1,     3,     1,     3,
       1,     3,     3,     2,     2,     4,     4,     1,     2,     2,
       2,     2,     4,     3,     1,     1
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
        case 5:
#line 201 "comp.c" /* yacc.c:1646  */
    {
    patch_type((yyvsp[-1].n1),(yyvsp[0].lis_attr));
}
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 207 "comp.c" /* yacc.c:1646  */
    { (yyval.n1).et = INT_T; (yyval.n1).ptr_depth=0; (yyval.n1).size = 0;}
#line 1612 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 208 "comp.c" /* yacc.c:1646  */
    { (yyval.n1).et = FLOAT_T; (yyval.n1).ptr_depth=0;  (yyval.n1).size = 0;}
#line 1618 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 209 "comp.c" /* yacc.c:1646  */
    { (yyval.n1).et = CHAR_T; (yyval.n1).ptr_depth=0;  (yyval.n1).size = 0;}
#line 1624 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 210 "comp.c" /* yacc.c:1646  */
    { (yyval.n1).et = INT_T; (yyval.n1).ptr_depth=(yyvsp[0].list_num);  (yyval.n1).size = 0;}
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 211 "comp.c" /* yacc.c:1646  */
    { (yyval.n1).et = FLOAT_T; (yyval.n1).ptr_depth=(yyvsp[0].list_num);  (yyval.n1).size = 0;}
#line 1636 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 212 "comp.c" /* yacc.c:1646  */
    { (yyval.n1).et = CHAR_T; (yyval.n1).ptr_depth=(yyvsp[0].list_num);  (yyval.n1).size = 0;}
#line 1642 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 214 "comp.c" /* yacc.c:1646  */
    {(yyval.list_num) = 1;}
#line 1648 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 214 "comp.c" /* yacc.c:1646  */
    {(yyval.list_num) = (yyvsp[0].list_num) + 1;}
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 216 "comp.c" /* yacc.c:1646  */
    { 
                (yyval.lis_attr).list_var = (struct node*)malloc(sizeof(struct node));
                (yyval.lis_attr).list_var[0] = (yyvsp[0].n1); (yyval.lis_attr).size = 1;}
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 219 "comp.c" /* yacc.c:1646  */
    { 
                (yyval.lis_attr).size = 1 + (yyvsp[0].lis_attr).size;
                (yyval.lis_attr).list_var = (struct node*)malloc(sizeof(struct node)*(yyval.lis_attr).size);
                
                int iter = 0;
                for(iter = 0;iter < (yyvsp[0].lis_attr).size; ++iter) (yyval.lis_attr).list_var[iter] = (yyvsp[0].lis_attr).list_var[iter];
                (yyval.lis_attr).list_var[(yyvsp[0].lis_attr).size] = (yyvsp[-2].n1);
             }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 229 "comp.c" /* yacc.c:1646  */
    {strcpy((yyval.n1).name,strdup(yytext));}
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 232 "comp.c" /* yacc.c:1646  */
    {
        strcpy((yyval.n1).name,(yyvsp[0].n1).name);
        (yyval.n1).size = 0;
        (yyval.n1).dim_list = NULL;
    }
#line 1691 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 237 "comp.c" /* yacc.c:1646  */
    {
        strcpy((yyval.n1).name,(yyvsp[-1].n1).name);
        (yyval.n1).size = (yyvsp[0].lb).size;
        (yyval.n1).dim_list = (yyvsp[0].lb).dim_list;
    }
#line 1701 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 244 "comp.c" /* yacc.c:1646  */
    {
    if((yyvsp[-1].n1).et == INT_T && (yyvsp[-1].n1).ptr_depth == 0 && (yyvsp[-1].n1).size == 0 && (yyvsp[-1].n1).expr_val > 0){
        (yyval.lb).size = 1;
        (yyval.lb).dim_list = (int*)malloc(sizeof(int));
        (yyval.lb).dim_list[0] = (yyvsp[-1].n1).expr_val;
    }
    else{ 
        printf("index must be int and +ve constant\n");
        (yyval.lb).size = 1;
        (yyval.lb).dim_list = (int*)malloc(sizeof(int));
        (yyval.lb).dim_list[0] = 1;
    }
    freename((yyvsp[-1].n1).reg_name);
    freename((yyvsp[-1].n1).reg_off);
}
#line 1721 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 259 "comp.c" /* yacc.c:1646  */
    { 
            (yyval.lb) = (yyvsp[0].lb);
        }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 262 "comp.c" /* yacc.c:1646  */
    { 
            (yyval.lb).dim_list = (int*)malloc(sizeof(int)*((yyvsp[0].lb).size+1));

            int iter = 0;
            for(iter = 0;iter < (yyvsp[0].lb).size; ++iter) (yyval.lb).dim_list[iter] = (yyvsp[0].lb).dim_list[iter];
            
            (yyval.lb).size = (yyvsp[0].lb).size + 1;
            (yyval.lb).dim_list[(yyvsp[0].lb).size] = (yyvsp[-1].lb).dim_list[0];
                      
    }
#line 1744 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 278 "comp.c" /* yacc.c:1646  */
    {insert_func_entry((yyvsp[-4].n1),(yyvsp[-3].n1),(yyvsp[-1].lis_attr));}
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 283 "comp.c" /* yacc.c:1646  */
    {
            if(check_func_proto((yyvsp[-4].n1),(yyvsp[-3].n1),(yyvsp[-1].lis_attr)) == 0){
                printf("Prototype mismatch/not declared\n");
            }
            cur_scope++;

            if(!text_printed){
                text_printed = 1;
                fprintf(asmout, ".text\n.globl main\n" );
            }
            fprintf(asmout, "%s: \n",(yyvsp[-3].n1).name );

            int iter = 0;
            for(;iter < (yyvsp[-1].lis_attr).size;++iter){
                (yyvsp[-1].lis_attr).list_var[iter].st_off = cur_off;
                // printf("parameter name is %s for func %s\n",$4.list_var[iter].name,$2.name );
                cur_off += (yyvsp[-1].lis_attr).list_var[iter].prod*(yyvsp[-1].lis_attr).list_var[iter].typeSize;
            }

            add_params_to_sym((yyvsp[-1].lis_attr));
            cur_func = (yyvsp[-4].n1);
            cur_func.num_func = ++tot_func;
            }
#line 1778 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 307 "comp.c" /* yacc.c:1646  */
    {
        cur_func.et = INT_T;cur_func.size = 0;cur_func.ptr_depth = 0;
        cur_scope++;
        cur_func.num_func = ++tot_func;

        if(!text_printed){
            text_printed = 1;
            fprintf(asmout, ".text\n" );
        }
        fprintf(asmout, "main: \n" );        
        fprintf(asmout, "move $fp,$sp\n" );
    }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 320 "comp.c" /* yacc.c:1646  */
    {
                                delete_entries();
                                cur_scope--;
                                    
                                    assert(cur_scope == 0 && cur_off == 0);

                                    fprintf(asmout, "li $v0,10\nsyscall\n");
                                }
#line 1808 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 331 "comp.c" /* yacc.c:1646  */
    {
    delete_entries();
    cur_scope--;
    assert(cur_scope == 0 && cur_off == 0);
    fprintf(asmout, "li $v1,0\n");
    fprintf(asmout, "jr $ra\n");
}
#line 1820 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 343 "comp.c" /* yacc.c:1646  */
    { 
                    (yyval.lis_attr).list_var = (struct node*)malloc(sizeof(struct node));
                    (yyvsp[0].n1).et = (yyvsp[-1].n1).et;
                    (yyvsp[0].n1).ptr_depth = (yyvsp[-1].n1).ptr_depth;

                    if((yyvsp[0].n1).size){
                        (yyvsp[0].n1).prod = 1;
                        int i = 0;
                        for(;i < (yyvsp[0].n1).size;++i) (yyvsp[0].n1).prod *= (yyvsp[0].n1).dim_list[i];
                    }
                    else (yyvsp[0].n1).prod = 1;
                
                    int cprod = (yyvsp[0].n1).prod;

                    if(1){
                        (yyvsp[0].n1).typeSize = 4; /// MIPS pointer size
                    }
                    (yyval.lis_attr).list_var[0] = (yyvsp[0].n1); 
                    (yyval.lis_attr).size = 1;

                }
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 365 "comp.c" /* yacc.c:1646  */
    { 
                    (yyval.lis_attr).size = 1 + (yyvsp[0].lis_attr).size;
                    (yyval.lis_attr).list_var = (struct node*)malloc(sizeof(struct node)*(yyval.lis_attr).size);
                    
                    int iter = 0;
                    for(iter = 0;iter < (yyvsp[0].lis_attr).size; ++iter) (yyval.lis_attr).list_var[iter] = (yyvsp[0].lis_attr).list_var[iter];
                    
                    (yyvsp[-2].n1).et = (yyvsp[-3].n1).et;
                    (yyvsp[-2].n1).ptr_depth = (yyvsp[-3].n1).ptr_depth;

                    if((yyvsp[-2].n1).size){
                        (yyvsp[-2].n1).prod = 1;
                        int i = 0;
                        for(;i < (yyvsp[-2].n1).size;++i) (yyvsp[-2].n1).prod *= (yyvsp[-2].n1).dim_list[i];
                    }
                    else (yyvsp[-2].n1).prod = 1;
                
                    int cprod = (yyvsp[-2].n1).prod;

                    if(1){
                        (yyvsp[-2].n1).typeSize = 4; /// MIPS pointer size
                    }

                    (yyval.lis_attr).list_var[(yyvsp[0].lis_attr).size] = (yyvsp[-2].n1);
                }
#line 1876 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 392 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1).et = INT_T; (yyval.n1).ptr_depth = 0; 
            (yyval.n1).size = 0; 
            (yyval.n1).dim_list = NULL; 
            (yyval.n1).expr_val = atoi(strdup(yytext));

            (yyval.n1).reg_name = newname();
            fprintf(asmout, "li %s,%d\n",(yyval.n1).reg_name,(yyval.n1).expr_val );

        }
#line 1891 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 402 "comp.c" /* yacc.c:1646  */
    {(yyval.n1).et = FLOAT_T; (yyval.n1).ptr_depth = 0; (yyval.n1).size = 0;(yyval.n1).dim_list = NULL; (yyval.n1).expr_val = -1000000;}
#line 1897 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 403 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1).et = CHAR_T; (yyval.n1).ptr_depth = 0; (yyval.n1).size = 0;(yyval.n1).dim_list = NULL; (yyval.n1).expr_val = yytext[1];

            (yyval.n1).reg_name = newname();
            fprintf(asmout, "li %s,%d\n",(yyval.n1).reg_name,(yyval.n1).expr_val );

                //printf("CHAR VALUE IS %d %s\n",$$.expr_val,yytext);
        }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 411 "comp.c" /* yacc.c:1646  */
    {(yyval.n1).et = INT_T; (yyval.n1).ptr_depth = 0; (yyval.n1).size = 0; (yyval.n1).dim_list = NULL; (yyval.n1).expr_val = -atoi(strdup(yytext));

                (yyval.n1).reg_name = newname();
                fprintf(asmout, "li %s,%d\n",(yyval.n1).reg_name,(yyval.n1).expr_val );
            }
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 418 "comp.c" /* yacc.c:1646  */
    {
    if(!((yyvsp[-1].n1).et == INT_T && (yyvsp[-1].n1).ptr_depth == 0 && (yyvsp[-1].n1).size == 0)){
        printf("index must be int type\n");
    }   
    (yyval.lb).size = 1;            
    (yyval.lb).reg_name = (char**)malloc(sizeof(char*)*(1));
    (yyval.lb).reg_name[0] = (char*)malloc(4);
    strcpy((yyval.lb).reg_name[0],(yyvsp[-1].n1).reg_name);
}
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 427 "comp.c" /* yacc.c:1646  */
    { 
            (yyval.lb) = (yyvsp[0].lb);
        }
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 430 "comp.c" /* yacc.c:1646  */
    { 
            (yyval.lb).reg_name = (char**)malloc(sizeof(char*)*((yyvsp[0].lb).size+1));

            int iter = 0;
            for(iter = 0;iter < (yyvsp[0].lb).size; ++iter) {
                (yyval.lb).reg_name[iter] = (char*)malloc(4);
                strcpy((yyval.lb).reg_name[iter],(yyvsp[0].lb).reg_name[iter]);
            }
            
            (yyval.lb).size = (yyvsp[0].lb).size + 1;
            (yyval.lb).reg_name[(yyvsp[0].lb).size] = (char*)malloc(4);
            strcpy((yyval.lb).reg_name[(yyvsp[0].lb).size],(yyvsp[-1].lb).reg_name[0]);
    }
#line 1960 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 447 "comp.c" /* yacc.c:1646  */
    { 
    ///global vars sepeate access


    ///dynamic access a[i][j]


        (yyval.n1) = get_sym((yyvsp[0].n1).name,NULL); 
        (yyval.n1).expr_val = -1000000;
        if((yyval.n1).size == 0){
            char* reg_name = (char*)malloc(sizeof(char)*4);
            strcpy(reg_name,"$a0");
            fprintf(asmout, "addi %s,$fp,-%d\n",reg_name,(yyval.n1).st_off + (yyval.n1).typeSize );
            fprintf(asmout, "sub %s,%s,%s\n",reg_name,reg_name,(yyval.n1).reg_off );
            freename((yyval.n1).reg_off);
            (yyval.n1).valid_off = 0;

            (yyval.n1).reg_name = newname();
            if((yyval.n1).typeSize == 4) fprintf(asmout, "lw %s,(%s)\n",(yyval.n1).reg_name,reg_name );
            else fprintf(asmout, "lw %s,(%s)\n",(yyval.n1).reg_name,reg_name );
            
        }

        }
#line 1989 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 470 "comp.c" /* yacc.c:1646  */
    { 
            (yyval.n1) = get_sym((yyvsp[-1].n1).name,&((yyvsp[0].lb))); 
            (yyval.n1).expr_val = -1000000;
            if((yyval.n1).size == 0){
                char* reg_name = (char*)malloc(sizeof(char)*4);
                strcpy(reg_name,"$a0");
                fprintf(asmout, "addi %s,$fp,-%d\n",reg_name,(yyval.n1).st_off + (yyval.n1).typeSize );
                fprintf(asmout, "sub %s,%s,%s\n",reg_name,reg_name,(yyval.n1).reg_off );
                freename((yyval.n1).reg_off);
                (yyval.n1).valid_off = 0;

                (yyval.n1).reg_name = newname();
                if((yyval.n1).typeSize == 4) fprintf(asmout, "lw %s,(%s)\n",(yyval.n1).reg_name,reg_name );
                else fprintf(asmout, "lw %s,(%s)\n",(yyval.n1).reg_name,reg_name );
                
            }
        }
#line 2011 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 489 "comp.c" /* yacc.c:1646  */
    { 
    ///global vars sepeate access


    ///dynamic access a[i][j]


        (yyval.n1) = get_sym((yyvsp[0].n1).name,NULL); 
        (yyval.n1).expr_val = -1000000;
        

        }
#line 2028 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 500 "comp.c" /* yacc.c:1646  */
    { 
            (yyval.n1) = get_sym((yyvsp[-1].n1).name,&((yyvsp[0].lb))); 
            (yyval.n1).expr_val = -1000000;
            
        }
#line 2038 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 507 "comp.c" /* yacc.c:1646  */
    { 

        (yyval.n1) = get_sym((yyvsp[0].n1).name,NULL); 
        (yyval.n1).expr_val = -1000000;
        // printf("reached here \n");
        if((yyval.n1).size == 0){
            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
            fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off );
            //freename($$.reg_off);
            //$$.valid_off = 0;

            (yyval.n1).reg_name = newname();
            if((yyval.n1).typeSize == 4) fprintf(asmout, "lw %s,($a0)\n",(yyval.n1).reg_name );
            else fprintf(asmout, "lw %s,($a0)\n",(yyval.n1).reg_name );
            // printf("reached here 2\n");
        }
        else{
            printf("id cant be array in this case\n");
        }

        }
#line 2064 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 527 "comp.c" /* yacc.c:1646  */
    { 
            (yyval.n1) = get_sym((yyvsp[-1].n1).name,&((yyvsp[0].lb))); 
            (yyval.n1).expr_val = -1000000;
            if((yyval.n1).size == 0){
                char* reg_name = (char*)malloc(sizeof(char)*4);
                strcpy(reg_name,"$a0");
                fprintf(asmout, "addi %s,$fp,-%d\n",reg_name,(yyval.n1).st_off + (yyval.n1).typeSize );
                fprintf(asmout, "sub %s,%s,%s\n",reg_name,reg_name,(yyval.n1).reg_off );
                //freename($$.reg_off);
                //$$.valid_off = 0;

                (yyval.n1).reg_name = newname();
                if((yyval.n1).typeSize == 4) fprintf(asmout, "lw %s,(%s)\n",(yyval.n1).reg_name,reg_name );
                else fprintf(asmout, "lw %s,(%s)\n",(yyval.n1).reg_name,reg_name );
                
            }
            else{
                printf("id cant be array in this case\n");
            }
        }
#line 2089 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 548 "comp.c" /* yacc.c:1646  */
    {
                            (yyval.lis_attr).list_var = (struct node*)malloc(sizeof(struct node));
                            (yyval.lis_attr).list_var[0] = (yyvsp[0].n1);
                            (yyval.lis_attr).size = 1;
                        }
#line 2099 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 553 "comp.c" /* yacc.c:1646  */
    {
                            (yyval.lis_attr).size = 1 + (yyvsp[0].lis_attr).size;
                            
                            (yyval.lis_attr).list_var = (struct node*)malloc(sizeof(struct node)*(yyval.lis_attr).size);
                            
                            int iter = 0;
                            for(iter = 0;iter < (yyvsp[0].lis_attr).size; ++iter) (yyval.lis_attr).list_var[iter] = (yyvsp[0].lis_attr).list_var[iter];
                            (yyval.lis_attr).list_var[(yyvsp[0].lis_attr).size] = (yyvsp[-2].n1);
                        }
#line 2113 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 564 "comp.c" /* yacc.c:1646  */
    {fprintf(fout,"s -> epsilon\n");}
#line 2119 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 565 "comp.c" /* yacc.c:1646  */
    {fprintf(fout,"s -> uif s\n");}
#line 2125 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 566 "comp.c" /* yacc.c:1646  */
    {fprintf(fout,"s -> mif s\n");}
#line 2131 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 569 "comp.c" /* yacc.c:1646  */
    {
    (yyval.n1) = check_func_exists((yyvsp[-3].n1).name); 
    if((yyval.n1).valid == 1){
         int i=0;
        for(;i<NUM_REG;++i){
            fprintf(asmout, "addi $sp,$sp,-4\n" );
            fprintf(asmout, "sw %s,($sp)\n",Names[i]);
        }
        fprintf(asmout, "addi $sp,$sp,-4\n" );
        fprintf(asmout, "sw $fp,($sp)\n");
        fprintf(asmout, "addi $sp,$sp,-4\n" );
        fprintf(asmout, "sw $ra,($sp)\n");

        fprintf(asmout, "move $a0,$fp\n" );
        fprintf(asmout, "move $fp,$sp\n" );

        check_param_match((yyval.n1),(yyvsp[-1].lis_attr));

        fprintf(asmout, "jal %s\n",(yyvsp[-3].n1).name );

        fprintf(asmout, "lw $ra,($sp)\n");
        fprintf(asmout, "addi $sp,$sp,4\n" );
        fprintf(asmout, "lw $fp,($sp)\n");
        fprintf(asmout, "addi $sp,$sp,4\n" );

        for(i=NUM_REG-1;i>=0;i--){
            fprintf(asmout, "lw %s,($sp)\n",Names[i]);
            fprintf(asmout, "addi $sp,$sp,4\n" );
        }

    }
}
#line 2168 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 602 "comp.c" /* yacc.c:1646  */
    {
    if((yyvsp[-1].n1).size){
        fprintf(asmout, "addi $a0,$fp,-%d\n",(yyvsp[-1].n1).st_off + (yyvsp[-1].n1).typeSize );
        fprintf(asmout, "sub $a0,$a0,%s\n",(yyvsp[-1].n1).reg_off);
        freename((yyvsp[-1].n1).reg_off);
        (yyvsp[-1].n1).valid_off = 0;

        (yyvsp[-1].n1).reg_name = newname();
        (yyvsp[-1].n1).ptr_depth += (yyvsp[-1].n1).size;
        (yyvsp[-1].n1).size = 0;
        fprintf(asmout, "move %s,$a0\n",(yyvsp[-1].n1).reg_name );
        (yyvsp[-1].n1).expr_val = -1000000;
    }
    compatible((yyvsp[-3].n1),(yyvsp[-1].n1));

    fprintf(asmout, "addi $a0,$fp,-%d\n",(yyvsp[-3].n1).st_off + (yyvsp[-3].n1).typeSize);
    fprintf(asmout, "sub $a0,$a0,%s\n",(yyvsp[-3].n1).reg_off );

    if((yyvsp[-3].n1).typeSize == 1) {
        fprintf(asmout, "sw %s,($a0)\n",(yyvsp[-1].n1).reg_name );
    }
    else {
        fprintf(asmout, "sw %s,($a0)\n",(yyvsp[-1].n1).reg_name );
    }

    freename((yyvsp[-3].n1).reg_off);freename((yyvsp[-1].n1).reg_off);
    freename((yyvsp[-3].n1).reg_name);freename((yyvsp[-1].n1).reg_name);

    (yyval.label_num) = ++label_cnt;

    loop_cnt++;
    is_for[loop_cnt] = 1;
    loop_no[loop_cnt] = (yyval.label_num);
    
    fprintf(asmout, "START_LABEL%d:\n",(yyval.label_num) );
}
#line 2209 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 638 "comp.c" /* yacc.c:1646  */
    {
    (yyval.label_num) = (yyvsp[-2].label_num);

    if( (yyvsp[-1].n1).size > 0 || (yyvsp[-1].n1).ptr_depth >0)
        printf("Boolean required in expression\n");
    else{
        fprintf(asmout, "beq %s,$zero,LABEL%d\n",(yyvsp[-1].n1).reg_name,(yyval.label_num) );

    } 
    freename((yyvsp[-1].n1).reg_name);
    freename((yyvsp[-1].n1).reg_off);
    fprintf(asmout, "j FOR_START%d\n",(yyval.label_num) );
    fprintf(asmout, "FOR_INC%d:\n",(yyval.label_num) );
}
#line 2228 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 653 "comp.c" /* yacc.c:1646  */
    {
                    (yyval.label_num)=(yyvsp[-2].label_num);
                    fprintf(asmout, "j START_LABEL%d\n",(yyval.label_num) );
                    fprintf(asmout, "FOR_START%d:\n",(yyval.label_num) );
                }
#line 2238 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 659 "comp.c" /* yacc.c:1646  */
    {
    (yyval.label_num) = (yyvsp[-3].label_num);
    fprintf(asmout, "j FOR_INC%d\n",(yyval.label_num) );
    fprintf(asmout, "LABEL%d:\n",(yyvsp[-3].label_num) );
     delete_entries(); cur_scope--;

    loop_cnt--;

}
#line 2252 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 669 "comp.c" /* yacc.c:1646  */
    {
    (yyval.label_num) = ++label_cnt;

    loop_cnt++;
    is_for[loop_cnt] = 0;
    loop_no[loop_cnt] = (yyval.label_num);
    
    fprintf(asmout, "START_LABEL%d:\n",(yyval.label_num) );

}
#line 2267 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 680 "comp.c" /* yacc.c:1646  */
    {
                (yyval.label_num) = (yyvsp[-2].label_num);
                if((yyvsp[-1].n1).size > 0 || (yyvsp[-1].n1).ptr_depth >0)
                    printf("Boolean required in expression\n");
                else{
                    fprintf(asmout, "beq %s,$zero,LABEL%d\n",(yyvsp[-1].n1).reg_name,(yyval.label_num) );

                } 
                freename((yyvsp[-1].n1).reg_name);
                freename((yyvsp[-1].n1).reg_off);
            }
#line 2283 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 691 "comp.c" /* yacc.c:1646  */
    {
    fprintf(asmout, "j START_LABEL%d\n",(yyvsp[-3].label_num) );
    fprintf(asmout, "LABEL%d:\n",(yyvsp[-3].label_num) );
     delete_entries(); cur_scope--;

    loop_cnt--;
}
#line 2295 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 701 "comp.c" /* yacc.c:1646  */
    {
            if((yyvsp[-1].n1).size > 0 || (yyvsp[-1].n1).ptr_depth >0){
                printf("Boolean expected\n");
            }
            else{
                (yyval.label_num) = ++label_cnt;
                fprintf(asmout, "beq %s,$zero,LABEL%d\n",(yyvsp[-1].n1).reg_name,(yyval.label_num) );
            }

            freename((yyvsp[-1].n1).reg_name);
            freename((yyvsp[-1].n1).reg_off);
        }
#line 2312 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 713 "comp.c" /* yacc.c:1646  */
    {
        fprintf(asmout, "j END_LABEL%d\n",(yyvsp[-3].label_num) );
        fprintf(asmout, "LABEL%d:\n",(yyvsp[-3].label_num) );
        (yyval.label_num) = (yyvsp[-3].label_num);
         delete_entries(); cur_scope--;
}
#line 2323 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 719 "comp.c" /* yacc.c:1646  */
    {
          fprintf(asmout, "END_LABEL%d:\n",(yyvsp[-4].label_num) );
           delete_entries(); cur_scope--;
        }
#line 2332 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 723 "comp.c" /* yacc.c:1646  */
    {
            fprintf(asmout, "END_LABEL%d:\n",(yyvsp[0].label_num) );
        }
#line 2340 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 729 "comp.c" /* yacc.c:1646  */
    {cur_scope++;}
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 731 "comp.c" /* yacc.c:1646  */
    {
                             if((yyvsp[-1].n1).size){
                                fprintf(asmout, "addi $a0,$fp,-%d\n",(yyvsp[-1].n1).st_off + (yyvsp[-1].n1).typeSize );
                                fprintf(asmout, "sub $a0,$a0,%s\n",(yyvsp[-1].n1).reg_off);
                                freename((yyvsp[-1].n1).reg_off);
                                (yyvsp[-1].n1).valid_off = 0;

                                (yyvsp[-1].n1).reg_name = newname();
                                (yyvsp[-1].n1).ptr_depth += (yyvsp[-1].n1).size;
                                (yyvsp[-1].n1).size = 0;
                                fprintf(asmout, "move %s,$a0\n",(yyvsp[-1].n1).reg_name );
                                (yyvsp[-1].n1).expr_val = -1000000;
                            }
                            if((yyvsp[-4].list_num) > (yyvsp[-3].n1).ptr_depth){
                                printf("Error dereferencing\n");
                            }
                            else{
                                int ctr=0;
                                fprintf(asmout, "move $a1,%s\n",(yyvsp[-3].n1).reg_name );
                                for(;ctr < (yyvsp[-4].list_num)-1;++ctr){
                                    fprintf(asmout, "lw $a2,($a1)\n" );
                                    fprintf(asmout, "move $a1,$a2\n" );
                                }

                                (yyvsp[-3].n1).ptr_depth -= (yyvsp[-4].list_num);
                                compatible((yyvsp[-3].n1),(yyvsp[-1].n1));

                                fprintf(asmout, "sw %s,($a1)\n",(yyvsp[-1].n1).reg_name);
                            }
                            freename((yyvsp[-3].n1).reg_name);
                            freename((yyvsp[-3].n1).reg_off);
                            freename((yyvsp[-1].n1).reg_name);
                            freename((yyvsp[-1].n1).reg_off);
                        }
#line 2385 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 767 "comp.c" /* yacc.c:1646  */
    { 
                        if((yyvsp[-1].n1).size){
                            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyvsp[-1].n1).st_off + (yyvsp[-1].n1).typeSize );
                            fprintf(asmout, "sub $a0,$a0,%s\n",(yyvsp[-1].n1).reg_off);
                            freename((yyvsp[-1].n1).reg_off);
                            (yyvsp[-1].n1).valid_off = 0;

                            (yyvsp[-1].n1).reg_name = newname();
                            (yyvsp[-1].n1).ptr_depth += (yyvsp[-1].n1).size;
                            (yyvsp[-1].n1).size = 0;
                            fprintf(asmout, "move %s,$a0\n",(yyvsp[-1].n1).reg_name );
                            (yyvsp[-1].n1).expr_val = -1000000;
                        }
                        compatible((yyvsp[-3].n1),(yyvsp[-1].n1));

                        fprintf(asmout, "addi $a0,$fp,-%d\n",(yyvsp[-3].n1).st_off + (yyvsp[-3].n1).typeSize);
                        fprintf(asmout, "sub $a0,$a0,%s\n",(yyvsp[-3].n1).reg_off );

                        if((yyvsp[-3].n1).typeSize == 1) {
                            fprintf(asmout, "sw %s,($a0)\n",(yyvsp[-1].n1).reg_name );
                        }
                        else {
                            fprintf(asmout, "sw %s,($a0)\n",(yyvsp[-1].n1).reg_name );
                        }

                        freename((yyvsp[-3].n1).reg_off);freename((yyvsp[-1].n1).reg_off);
                        freename((yyvsp[-3].n1).reg_name);freename((yyvsp[-1].n1).reg_name);
                    }
#line 2418 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 797 "comp.c" /* yacc.c:1646  */
    {
                        if(!loop_cnt) printf("continue without loop\n");
                        if(is_for[loop_cnt]){
                            fprintf(asmout, "j FOR_INC%d\n",loop_no[loop_cnt] );
                        }
                        else{
                            fprintf(asmout, "j START_LABEL%d\n",loop_no[loop_cnt]);
                        }
                    }
#line 2432 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 806 "comp.c" /* yacc.c:1646  */
    {
                        if(!loop_cnt) printf("break without loop\n");
                        fprintf(asmout, "j LABEL%d\n",loop_no[loop_cnt] );
                    }
#line 2441 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 811 "comp.c" /* yacc.c:1646  */
    {fprintf(fout,"other_than_if-> while_stmnt\n");}
#line 2447 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 812 "comp.c" /* yacc.c:1646  */
    {fprintf(fout,"other_than_if-> for_stmnt\n");}
#line 2453 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 814 "comp.c" /* yacc.c:1646  */
    { delete_entries(); cur_scope--;}
#line 2459 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 816 "comp.c" /* yacc.c:1646  */
    {
                        freename((yyvsp[-1].n1).reg_name);
                        freename((yyvsp[-1].n1).reg_off);
                    }
#line 2468 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 820 "comp.c" /* yacc.c:1646  */
    {
                        if((yyvsp[-1].n1).size > 0){
                            printf("cannot print array expression\n");
                        }
                        else{
                            if((yyvsp[-1].n1).et == CHAR_T && (yyvsp[-1].n1).ptr_depth == 0) fprintf(asmout, "li $v0,11\n" );
                            else fprintf(asmout, "li $v0,1\n" );
                            
                            fprintf(asmout,"move $a0,%s\n",(yyvsp[-1].n1).reg_name);
                            fprintf(asmout, "syscall\n" );
                        }
                        freename((yyvsp[-1].n1).reg_name);
                        freename((yyvsp[-1].n1).reg_off);
                    }
#line 2487 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 834 "comp.c" /* yacc.c:1646  */
    {
                        fprintf(asmout, "li $v0,11\n" );            
                        fprintf(asmout,"li $a0,10\n");
                        fprintf(asmout, "syscall\n" );
                    }
#line 2497 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 839 "comp.c" /* yacc.c:1646  */
    {
                        if((yyvsp[-1].n1).size){
                            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyvsp[-1].n1).st_off + (yyvsp[-1].n1).typeSize );
                            fprintf(asmout, "sub $a0,$a0,%s\n",(yyvsp[-1].n1).reg_off);
                            freename((yyvsp[-1].n1).reg_off);
                            (yyvsp[-1].n1).valid_off = 0;

                            (yyvsp[-1].n1).reg_name = newname();
                            (yyvsp[-1].n1).ptr_depth += (yyvsp[-1].n1).size;
                            (yyvsp[-1].n1).size = 0;
                            fprintf(asmout, "move %s,$a0\n",(yyvsp[-1].n1).reg_name );
                            (yyvsp[-1].n1).expr_val = -1000000;
                        }

                        compatible(cur_func,(yyvsp[-1].n1));

                        fprintf(asmout, "move $v1,%s\n",(yyvsp[-1].n1).reg_name );
                        delete_entries_on_ret();
                        fprintf(asmout, "jr $ra\n" );
                        freename((yyvsp[-1].n1).reg_name);
                        freename((yyvsp[-1].n1).reg_off);
                    }
#line 2524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 864 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_AND_AND,(yyvsp[0].n1));}
#line 2530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 865 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_OR_OR,(yyvsp[0].n1));}
#line 2536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 866 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = (yyvsp[0].n1);}
#line 2542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 869 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_EEQ,(yyvsp[0].n1));}
#line 2548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 870 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_NEQ,(yyvsp[0].n1));}
#line 2554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 871 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = (yyvsp[0].n1);}
#line 2560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 874 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = (yyvsp[0].n1);}
#line 2566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 875 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_LEQ,(yyvsp[0].n1));}
#line 2572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 876 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_GRQ,(yyvsp[0].n1));}
#line 2578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 877 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_GR,(yyvsp[0].n1));}
#line 2584 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 878 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_LE,(yyvsp[0].n1));}
#line 2590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 881 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = (yyvsp[0].n1);}
#line 2596 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 882 "comp.c" /* yacc.c:1646  */
    { (yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_MINUS,(yyvsp[0].n1));}
#line 2602 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 885 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = (yyvsp[0].n1);}
#line 2608 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 886 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_PLUS,(yyvsp[0].n1));}
#line 2614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 889 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = (yyvsp[0].n1);}
#line 2620 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 890 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_TIMES,(yyvsp[0].n1));}
#line 2626 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 891 "comp.c" /* yacc.c:1646  */
    {(yyval.n1) = comp_binopt_type((yyvsp[-2].n1),_DIV,(yyvsp[0].n1));}
#line 2632 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 893 "comp.c" /* yacc.c:1646  */
    {
            // printf("accessing pointer of %d %d\n",$2.ptr_depth,$2.size);
            if((yyvsp[-1].list_num) > (yyvsp[0].n1).ptr_depth + (yyvsp[0].n1).size ){
                printf("Error dereferencing\n");
                (yyval.n1).et = ERROR;
                (yyval.n1).reg_name = (char*)malloc(1);
                (yyval.n1).reg_off = (char*)malloc(1);
            }else{
                (yyval.n1) = (yyvsp[0].n1);
                if((yyval.n1).size == 0){
                    int ctr=0;
                    fprintf(asmout, "move $a1,%s\n",(yyval.n1).reg_name );
                    for(;ctr < (yyvsp[-1].list_num)-1;++ctr){
                        fprintf(asmout, "lw $a2,($a1)\n" );
                        fprintf(asmout, "move $a1,$a2\n" );
                    }
                    int sz = 4;
                    if((yyval.n1).et == CHAR_T && (yyval.n1).ptr_depth == (yyvsp[-1].list_num)) sz = 4;   
                    
                    if(sz == 4) fprintf(asmout, "lw $a2,($a1)\n");
                    else fprintf(asmout, "lw $a2,($a1)\n");

                    fprintf(asmout, "move %s,$a2\n",(yyval.n1).reg_name );
                    (yyval.n1).ptr_depth -= (yyvsp[-1].list_num);
                    if((yyval.n1).ptr_depth == 0 && (yyval.n1).et == CHAR_T) (yyval.n1).typeSize = 4;       
                }
                else{
                    fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
                    fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off);
                    freename((yyval.n1).reg_off);
                    (yyval.n1).valid_off = 0;

                    (yyval.n1).reg_name = newname();
                    (yyval.n1).ptr_depth += (yyval.n1).size;
                    (yyval.n1).size = 0;

                    int ctr=0;
                    fprintf(asmout, "move $a1,$a0\n" );
                    for(;ctr < (yyvsp[-1].list_num)-1;++ctr){
                        fprintf(asmout, "lw $a2,($a1)\n" );
                        fprintf(asmout, "move $a1,$a2\n" );
                    }
                    int sz = 4;
                    if((yyval.n1).et == CHAR_T && (yyval.n1).ptr_depth == (yyvsp[-1].list_num)) sz = 4;   
                    
                    if(sz == 4) fprintf(asmout, "lw $a2,($a1)\n");
                    else fprintf(asmout, "lw $a2,($a1)\n");

                    fprintf(asmout, "move %s,$a2\n",(yyval.n1).reg_name );
                    (yyval.n1).ptr_depth -= (yyvsp[-1].list_num);
                    if((yyval.n1).ptr_depth == 0 && (yyval.n1).et == CHAR_T) (yyval.n1).typeSize = 4;

                }
            }
            (yyval.n1).expr_val = -1000000;
        }
#line 2693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 949 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1) = (yyvsp[0].n1);
            
            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
            fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off);
            freename((yyval.n1).reg_off);
            (yyval.n1).valid_off = 0;

            (yyval.n1).reg_name = newname();
            (yyval.n1).ptr_depth += (yyval.n1).size;
            (yyval.n1).size = 0;
            fprintf(asmout, "move %s,$a0\n",(yyval.n1).reg_name );
            (yyval.n1).expr_val = -1000000;
            (yyval.n1).ptr_depth++;
        }
#line 2713 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 964 "comp.c" /* yacc.c:1646  */
    {
            if((yyvsp[-3].list_num) > (yyvsp[-1].n1).ptr_depth + (yyvsp[-1].n1).size ){
                printf("Error dereferencing\n");
                (yyval.n1).et = ERROR;
                (yyval.n1).reg_name = (char*)malloc(1);
                (yyval.n1).reg_off = (char*)malloc(1);
            }else{
                (yyval.n1) = (yyvsp[-1].n1);
                if((yyval.n1).size == 0){
                    int ctr=0;
                    fprintf(asmout, "move $a1,%s\n",(yyval.n1).reg_name );
                    for(;ctr < (yyvsp[-3].list_num)-1;++ctr){
                        fprintf(asmout, "lw $a2,($a1)\n" );
                        fprintf(asmout, "move $a1,$a2\n" );
                    }
                    int sz = 4;
                    if((yyval.n1).et == CHAR_T && (yyval.n1).ptr_depth == (yyvsp[-3].list_num)) sz = 4;   
                    
                    if(sz == 4) fprintf(asmout, "lw $a2,($a1)\n");
                    else fprintf(asmout, "lw $a2,($a1)\n");

                    fprintf(asmout, "move %s,$a2\n",(yyval.n1).reg_name );
                    (yyval.n1).ptr_depth -= (yyvsp[-3].list_num);
                    if((yyval.n1).ptr_depth == 0 && (yyval.n1).et == CHAR_T) (yyval.n1).typeSize = 4;       
                }
                else{
                    fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
                    fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off);
                    freename((yyval.n1).reg_off);
                    (yyval.n1).valid_off = 0;

                    (yyval.n1).reg_name = newname();
                    (yyval.n1).ptr_depth += (yyval.n1).size;
                    (yyval.n1).size = 0;

                    int ctr=0;
                    fprintf(asmout, "move $a1,$a0\n" );
                    for(;ctr < (yyvsp[-3].list_num)-1;++ctr){
                        fprintf(asmout, "lw $a2,($a1)\n" );
                        fprintf(asmout, "move $a1,$a2\n" );
                    }
                    int sz = 4;
                    if((yyval.n1).et == CHAR_T && (yyval.n1).ptr_depth == (yyvsp[-3].list_num)) sz = 4;   
                    
                    if(sz == 4) fprintf(asmout, "lw $a2,($a1)\n");
                    else fprintf(asmout, "lw $a2,($a1)\n");

                    fprintf(asmout, "move %s,$a2\n",(yyval.n1).reg_name );
                    (yyval.n1).ptr_depth -= (yyvsp[-3].list_num);
                    if((yyval.n1).ptr_depth == 0 && (yyval.n1).et == CHAR_T) (yyval.n1).typeSize = 4;

                }
   
            }

            (yyval.n1).expr_val = -1000000;
        }
#line 2775 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1023 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1) = (yyvsp[-1].n1);
            (yyvsp[-3].n1) = compatible((yyvsp[-3].n1),(yyvsp[-1].n1));
            (yyval.n1).et = (yyvsp[-3].n1).et;
            (yyval.n1).expr_val = (yyvsp[-3].n1).expr_val;
        }
#line 2786 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1029 "comp.c" /* yacc.c:1646  */
    {
                (yyval.n1) = (yyvsp[0].n1);
                (yyval.n1).expr_val = -1000000;
            }
#line 2795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1033 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1) = comp_opt_type(_PLUS,(yyvsp[0].n1));
            if((yyval.n1).ptr_depth == 0){
                fprintf(asmout, "addi %s,%s,1\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
            else{    
                fprintf(asmout, "addi %s,%s,4\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }

            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
            fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off );

            fprintf(asmout, "sw %s,($a0)\n",(yyval.n1).reg_name);
        }
#line 2814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1047 "comp.c" /* yacc.c:1646  */
    {
           (yyval.n1) = comp_opt_type(_MINUS,(yyvsp[0].n1));
           if((yyval.n1).ptr_depth == 0){
                fprintf(asmout, "addi %s,%s,-1\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
            else{    
                fprintf(asmout, "addi %s,%s,-4\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }

            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
            fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off );

            fprintf(asmout, "sw %s,($a0)\n",(yyval.n1).reg_name);
        }
#line 2833 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1061 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1) = comp_opt_type(_PLUS,(yyvsp[-1].n1));
            if((yyval.n1).ptr_depth == 0){
                fprintf(asmout, "addi %s,%s,1\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
            else{    
                fprintf(asmout, "addi %s,%s,4\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }

            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
            fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off );

            fprintf(asmout, "sw %s,($a0)\n",(yyval.n1).reg_name);

            if((yyval.n1).ptr_depth == 0){
                fprintf(asmout, "addi %s,%s,-1\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
            else{    
                fprintf(asmout, "addi %s,%s,-4\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
        }
#line 2859 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 1082 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1) = comp_opt_type(_MINUS,(yyvsp[-1].n1));
            if((yyval.n1).ptr_depth == 0 ){
                fprintf(asmout, "addi %s,%s,-1\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
            else{    
                fprintf(asmout, "addi %s,%s,-4\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }

            fprintf(asmout, "addi $a0,$fp,-%d\n",(yyval.n1).st_off + (yyval.n1).typeSize );
            fprintf(asmout, "sub $a0,$a0,%s\n",(yyval.n1).reg_off );

            fprintf(asmout, "sw %s,($a0)\n",(yyval.n1).reg_name);

            if((yyval.n1).ptr_depth == 0 ){
                fprintf(asmout, "addi %s,%s,1\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
            else{    
                fprintf(asmout, "addi %s,%s,4\n",(yyval.n1).reg_name,(yyval.n1).reg_name );
            }
        }
#line 2885 "y.tab.c" /* yacc.c:1646  */
    break;

  case 102:
#line 1103 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1) = comp_opt_type(_NOT,(yyvsp[-1].n1));
            fprintf(asmout, "bne %s,$zero,NOT_LABEL%d\n",(yyval.n1).reg_name,not_label );
            fprintf(asmout, "li %s,1\n",(yyval.n1).reg_name );       
            fprintf(asmout, "j NOT_LABEL_END%d\n",not_label );
            fprintf(asmout, "NOT_LABEL%d:\n li %s,0\n",not_label,(yyval.n1).reg_name );
            fprintf(asmout, "NOT_LABEL_END%d:\n",not_label );
            not_label++; 
        }
#line 2899 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 1112 "comp.c" /* yacc.c:1646  */
    {
                (yyval.n1) = (yyvsp[-1].n1);
            
        }
#line 2908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1116 "comp.c" /* yacc.c:1646  */
    {
                (yyval.n1) = (yyvsp[0].n1);
            }
#line 2916 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1119 "comp.c" /* yacc.c:1646  */
    {
            (yyval.n1) = (yyvsp[0].n1);
            (yyval.n1).reg_name = newname();
            fprintf(asmout, "move %s,$v1\n",(yyval.n1).reg_name );
            (yyval.n1).expr_val = -1000000;
        }
#line 2927 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2931 "y.tab.c" /* yacc.c:1646  */
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
#line 1126 "comp.c" /* yacc.c:1906  */


void insert_symb_table(struct node* var)
{
    if (var == NULL)
        return ;
    
    var->valid = 1;
    var->next = symb_table;
    symb_table = var;
}

void add_params_to_sym(struct list_attr lis)
{
    int i=0;
    while(i < lis.size)
    {
        struct node* param_list = &lis.list_var[i];
        param_list->scope = 1;

        if(exists_in_scope(*param_list)){
            printf("Parameter already defined %s\n",param_list->name);
        }else{
            // printf("insertiing %s\n",param_list->name);
            insert_symb_table(param_list);
        }

        i++;
    }
}

void check_distinct(struct node *attrs, int size)
{
    int i,j;
    for (i =0;i<size;i++)
    {
        for(j=i+1;j<size;j++){
            // if(attrs[i].name == NULL) attrs[i].name = (char*)malloc(1);
            if(strcmp(attrs[i].name,attrs[j].name) == 0)
            {
                printf("Same variables names not allowed %s \n",attrs[i].name);
            }
        }
    }
}

struct func_node* get_func_entry(char *name)
{
    struct func_node *act_func = func_table;

    while(act_func!=NULL)
    {
        // printf("%s is name of fn  \n",act_func->name);
        if(name == NULL) name = (char*)malloc(1);
        if(strcmp(act_func->name,name)==0)
            return act_func;
        act_func = act_func->next;
    }

    return NULL; 
}

void insert_func_entry(struct node type,struct node id,struct list_attr attrs)
{
    if(get_func_entry(id.name) != NULL)
    {
        printf("Function already declared\n");
        return;
    }

    struct func_node *n = (struct func_node *)malloc(sizeof(struct func_node));
    strcpy(n->name, id.name);
    n->et = type.et;
    n->ptr_depth = type.ptr_depth;
    n->valid = 0;

    check_distinct(attrs.list_var,attrs.size);
    n->param_list = attrs.list_var;
    n->num_params = attrs.size;

    // printf("Inserting %s\n",n->name);
    n->next = func_table;
    func_table = n;
}

struct node check_func_exists(char *name)
{
    struct node ret_node;

    struct func_node *tmp = get_func_entry(name);
    
    strcpy(ret_node.name,name);

    if(tmp == NULL){
        ret_node.et = ERROR;
        ret_node.valid = 0;
    }
    else{
        ret_node.ptr_depth = tmp->ptr_depth;
        ret_node.size = 0;
        ret_node.et = tmp->et;
        ret_node.valid = 1;
    }

    return ret_node;
}   

int match_node_list(struct node *list_var,int lsize,struct node *param_list,int psize,int isProto)
{
    
    if(lsize != psize)
    {
        printf("Number of var mismatch\n");
        return 0;
    }
    int i;
    
    for(i = 0;i<lsize;i++)
    {
        int check;
        if(isProto) check = !match_node_exact(list_var[i],param_list[i]);
        else check = !match_node(&list_var[i],&param_list[i]);
        if(check)
        {
            printf("variable mismatch : %s\n",list_var[i].name);
            return 0;
        }
    }
    printf("\n");
       return 1;
}


int check_func_proto(struct node type,struct node id,struct list_attr attrs)
{
    struct func_node *act_func = get_func_entry(id.name);

    if(act_func == NULL){
        printf("Function prototype not declared\n");        
        return 0;
    }

    if(act_func->et == type.et 
        && act_func->ptr_depth == type.ptr_depth 
        && match_node_list(attrs.list_var,attrs.size,act_func->param_list,act_func->num_params,1))
    {
        if(act_func->valid == 1) return 0;
        act_func->valid = 1;
        return 1;
    }

    return 0;
}

int check_param_match(struct node fn,struct list_attr attrs)
{
   // printf("In check param\n");
    struct func_node *func = get_func_entry(fn.name);
    
    int ret_val = match_node_list(func->param_list,func->num_params,attrs.list_var,attrs.size,0);
    

    if(ret_val == 0)
        printf("Parameters mismatch for the Function %s\n",func->name);

    return ret_val;
}


int match_node_exact(struct node n1,struct node n2)
{
    if(n1.et == ERROR || n2.et == ERROR)
        return 0;

    if(strcmp(n1.name,n2.name)) return 0;

    if(n1.et != n2.et || n1.ptr_depth != n2.ptr_depth) return 0;
    if(n1.size != n2.size) return 0;
    int i = 0;
    for(;i<n1.size;++i ) if(n1.dim_list[i] != n2.dim_list[i]) return 0;
    return 1;
}


int match_node(struct node *n1,struct node *n2)
{
   // printf("comparing nodes %s %s %d\n",(*n1).name,(*n2).name,(*n2).et );
    struct node ret = compatible(*n1,*n2);


    if(ret.et == ERROR)
            return 0;
    struct node t1 = *n1,t2 = *n2;


    
    if(t1.ptr_depth || t2.ptr_depth == 0){
        int i=0;
        
        for(;i<t1.size;++i) {
            // printf("****%d %d *****\n", t1.dim_list[i],t2.dim_list[i]);
            if(t1.dim_list[i] != t2.dim_list[i]) return 0;
        }


        if(t2.size == 0){
            if(t1.et != CHAR_T || t1.ptr_depth > 0){
                fprintf(asmout, "addi $sp,$sp,-4\n" );
                fprintf(asmout, "sw %s,($sp)\n",t2.reg_name);
            }
            else{
                fprintf(asmout, "addi $sp,$sp,-4\n" );
                fprintf(asmout, "sw %s,($sp)\n",t2.reg_name);
            }
            freename(t2.reg_name);
        }
        else{
            int off;
            for(off = t2.st_off;off < t2.st_off + t2.prod * t2.typeSize; off += t2.typeSize){
                fprintf(asmout, "addi $a1,$a0,-%d\n",off + t2.typeSize );

                assert(t2.valid_off == 1);
                fprintf(asmout, "sub $a1,$a1,%s\n",t2.reg_off );

                if(t2.et != CHAR_T || t2.ptr_depth > 0) fprintf(asmout, "lw $a2,($a1)\n");
                else fprintf(asmout, "lw $a2,($a1)\n");

                if(t1.et != CHAR_T || t1.ptr_depth > 0){
                fprintf(asmout, "addi $sp,$sp,-4\n" );
                fprintf(asmout, "sw $a2,($sp)\n");
                }
                else{
                    fprintf(asmout, "addi $sp,$sp,-4\n" );
                    fprintf(asmout, "sw $a2,($sp)\n");
                }
            }
            t2.valid_off = 0;
            freename(t2.reg_off);
        }


    }
    else{
        int ctr=0;
        fprintf(asmout, "move $a1,%s\n",t2.reg_name );
        for(;ctr < t2.ptr_depth -1;++ctr){
            fprintf(asmout, "lw $a2,($a1)\n" );
            fprintf(asmout, "move $a1,$a2\n" );
        }

        int off = 0;
        int sz = 4;
        if(t2.et == CHAR_T) sz = 4;

        for(;off < t1.prod * sz; off += sz){

            if(sz == 4) fprintf(asmout, "lw $a2,($a1)\n");
            else fprintf(asmout, "lw $a2,($a1)\n");

            if(t1.et != CHAR_T || t1.ptr_depth > 0){
                fprintf(asmout, "addi $sp,$sp,-4\n" );
                fprintf(asmout, "sw $a2,($sp)\n");
            }

            else{
                fprintf(asmout, "addi $sp,$sp,-4\n" );
                fprintf(asmout, "sw $a2,($sp)\n");
            }

            fprintf(asmout, "addi $a1,$a1,%d\n",sz);
        }
        freename(t2.reg_name);
    }
    
    return 1;
    
}



int exists_in_scope(struct node var){
    struct node* temp = symb_table;
    while(temp){

        if(temp->scope == cur_scope && temp->valid == 1 && strcmp(temp->name,var.name) == 0){
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

void patch_type(struct node type,struct list_attr lis){
    int iter=0;
    for(iter = 0;iter < lis.size; ++iter){
        //printf("name of var %s %d\n",lis.list_var[iter].name,cur_scope );
        if(exists_in_scope(lis.list_var[iter])){
            printf("%s variable already defined\n",lis.list_var[iter].name);
        }
        else{
            lis.list_var[iter].ptr_depth = type.ptr_depth;
            lis.list_var[iter].et = type.et;
            lis.list_var[iter].scope = cur_scope;

            if(lis.list_var[iter].size){
                lis.list_var[iter].prod = 1;
                int i = 0;
                for(;i < lis.list_var[iter].size;++i) lis.list_var[iter].prod *= lis.list_var[iter].dim_list[i];
            }
            else lis.list_var[iter].prod = 1;
        
            int cprod = lis.list_var[iter].prod;
            lis.list_var[iter].st_off = cur_off;

            if(1){
                lis.list_var[iter].typeSize = 4; /// MIPS pointer size
                if(cur_scope){
                    fprintf(asmout, "addi $sp,$sp,-%d\n",4*cprod );
                    cur_off += 4*cprod;
                }   
                else{
                        fprintf(asmout, "%s .space %d\n", lis.list_var[iter].name,4*cprod);
                }
            }
            
            insert_symb_table(lis.list_var+iter);
        }
    }
}

struct node get_sym(char* var_name,struct list_brac* lsb){
    struct node* temp = symb_table;
    struct node* node_found = NULL;
    int cur_max_scope = -1000000;

    while(temp){
        if(temp->scope <= cur_scope && temp->valid == 1 && strcmp(temp->name,var_name) == 0){
            if(temp->scope > cur_max_scope){
                cur_max_scope = temp->scope;
                node_found = temp;
            }
        }
        temp = temp->next;
    }
    
    struct node ret;
    
    int size_used = 0;
    if(lsb) size_used = lsb->size;

    if(node_found == NULL || node_found -> size < size_used){
        printf("variable not found or too many boxes %s\n",var_name);
        ret.et = ERROR;

        ret.reg_name = (char*)malloc(1);
        ret.reg_off = (char*)malloc(1);
        return ret;
    }

    //ret.et = node_found->et;
    //ret.ptr_depth = node_found->ptr_depth;
    
    ret = *node_found;
    ret.reg_off = newname();
    fprintf(asmout, "li %s,0\n",ret.reg_off );
    ret.valid_off = 1;

    //int addoff = 0;
    if(lsb){
        int i=0;
        for(;i<size_used;++i){
            char cur_reg[4];
            strcpy(cur_reg,lsb->reg_name[i]);

            fprintf(asmout, "move $a0,%s\n",cur_reg );

            int j = 0;
            for(;j < node_found->size - size_used + i;++j) {
                fprintf(asmout, "li %s,%d\n",cur_reg,node_found->dim_list[j]);
                fprintf(asmout, "mult $a0,%s\n",cur_reg );
                fprintf(asmout, "mflo $a0\n");   
            }
            freename(cur_reg);

            fprintf(asmout, "add %s,%s,$a0\n",ret.reg_off,ret.reg_off );
        }
    }
    //ret.st_off += addoff*ret.typeSize;
    fprintf(asmout, "li $a0,%d\n",ret.typeSize);
    fprintf(asmout, "mult $a0,%s\n",ret.reg_off );
    fprintf(asmout, "mflo %s\n",ret.reg_off);   


    ret.size = node_found -> size - size_used;

    ret.prod = 1;

    ret.dim_list = (int*) malloc(sizeof(int)*ret.size);
    int i = 0;
    for(;i<node_found->size - size_used;++i) {
        ret.dim_list[i] = node_found->dim_list[i];
        ret.prod *= ret.dim_list[i];
    }

    return ret;
}

void delete_entries_on_ret(){
    struct node* temp = symb_table;
    while(temp){

        if(temp->scope <= cur_scope && temp -> valid == 1){
            assert(cur_scope>0);
            fprintf(asmout, "addi $sp,$sp,%d\n", temp->prod * temp->typeSize);
        }
        temp = temp->next;
    }
}
void delete_entries(){
    struct node* temp = symb_table;
    while(temp){

        if(temp->scope == cur_scope && temp -> valid == 1){
            assert(cur_scope>0);

            temp->valid = 0;
            cur_off -= temp->prod * temp->typeSize;

            fprintf(asmout, "addi $sp,$sp,%d\n", temp->prod * temp->typeSize);
        }
        temp = temp->next;
    }
}

struct node print_comp_error(struct node exp1, struct node exp2){
    struct node ret;
    ret.et = ERROR;

    ret.reg_name = (char*)malloc(1);
    ret.reg_off = (char*)malloc(1);
    printf("%d ptr: %d size: %d typecast not compatible with %d ptr: %d size: %d\n",exp1.et,exp1.ptr_depth,exp1.size,
     exp2.et,exp2.ptr_depth,exp2.size);

    /*freename(exp1.reg_name);
    freename(exp1.reg_off);

    freename(exp2.reg_name);
    freename(exp2.reg_off);*/

    return ret;
}
struct node compatible(struct node exp1,struct node exp2){
    if(exp1.et == ERROR || exp2.et == ERROR) {
        exp1.et = ERROR;
        /*freename(exp1.reg_name);
        freename(exp1.reg_off);

        freename(exp2.reg_name);
        freename(exp2.reg_off);*/
        exp1.reg_name = (char*)malloc(1);
        exp1.reg_off = (char*)malloc(1);
    
        return exp1;
    }

    if(exp1.ptr_depth > 0){
        if(exp1.size != exp2.size || exp2.ptr_depth != exp1.ptr_depth) return print_comp_error(exp1,exp2);
        exp1.expr_val = -1000000;
        return exp1; 
    }
    if(exp1.size > 0){
        if(exp2.size && exp2.ptr_depth) return print_comp_error(exp1,exp2);
        if(exp2.size + exp2.ptr_depth != exp1.size) return print_comp_error(exp1,exp2);
        
        if(exp1.et != FLOAT_T && exp2.et == FLOAT_T) return print_comp_error(exp1,exp2);
        exp1.expr_val = -1000000;
        return exp1;
    }
    if(exp2.ptr_depth > 0 || exp2.size > 0 ) return print_comp_error(exp1,exp2);
    if(exp1.et != FLOAT_T && exp2.et == FLOAT_T) return print_comp_error(exp1,exp2);
    exp1.expr_val = -1000000;
    return exp1;
}

struct node print_opt_error(struct node exp1,enum op_type op, struct node exp2){
    struct node ret;
    ret.et = ERROR;


    ret.reg_name = (char*)malloc(1);
    ret.reg_off = (char*)malloc(1);

    printf("%d ptr: %d size: %d op: %d not compatible with %d ptr: %d size: %d\n",exp1.et,exp1.ptr_depth,exp1.size,
    op, exp2.et,exp2.ptr_depth,exp2.size);

    /*freename(exp1.reg_name);
    freename(exp1.reg_off);

    freename(exp2.reg_name);
    freename(exp2.reg_off);*/

    return ret;
}
struct node comp_binopt_type(struct node exp1,enum op_type op, struct node exp2){
    if(exp1.et == ERROR || exp2.et == ERROR) {
        exp1.et = ERROR;

        exp1.reg_name = (char*)malloc(1);
        exp1.reg_off = (char*)malloc(1);
        return exp1;
    }

    struct node ret;
    if(op == _AND_AND || op == _OR_OR){
        if(exp1.size + exp1.ptr_depth > 0 || exp2.size + exp2.ptr_depth > 0){
            return print_opt_error(exp1,op,exp2);
        }
        ret.expr_val = -1000000;
        ret.et = BOOL;
        ret.ptr_depth = ret.size = 0;
        ret.typeSize = 4;

        if(op == _AND_AND){
            fprintf(asmout, "beq %s,$zero,NOT_LABEL%d\n",exp1.reg_name,not_label );
            fprintf(asmout, "beq %s,$zero,NOT_LABEL%d\n",exp2.reg_name,not_label );

            fprintf(asmout, "li %s,1\n",exp1.reg_name );       
            fprintf(asmout, "j NOT_LABEL_END%d\n",not_label );
            fprintf(asmout, "NOT_LABEL%d:\n li %s,0\n",not_label,exp1.reg_name );
            fprintf(asmout, "NOT_LABEL_END%d:\n",not_label );
            not_label++; 
            ret.reg_name = exp1.reg_name;
            freename(exp2.reg_name);
        }
        else{
            fprintf(asmout, "or %s,%s,%s\n",exp1.reg_name,exp1.reg_name,exp2.reg_name );
            freename(exp2.reg_name);
            
            fprintf(asmout, "bne %s,$zero,NOT_LABEL%d\n",exp1.reg_name,not_label );
            fprintf(asmout, "li %s,0\n",exp1.reg_name );       
            fprintf(asmout, "j NOT_LABEL_END%d\n",not_label );
            fprintf(asmout, "NOT_LABEL%d:\n li %s,1\n",not_label,exp1.reg_name );
            fprintf(asmout, "NOT_LABEL_END%d:\n",not_label );
            not_label++;
            ret.reg_name = exp1.reg_name;
        }
        
        return ret;
    }
    if(op == _EEQ || op == _NEQ || op == _GR || op == _LE || op == _GRQ || op == _LEQ){
        if(exp1.size > 0 || exp2.size > 0 || exp1.ptr_depth != exp2.ptr_depth || exp1.et != exp2.et){
            return print_opt_error(exp1,op,exp2);
        }
        ret.expr_val = -1000000;
        ret.et = BOOL;
        ret.ptr_depth = ret.size = 0;
        ret.typeSize = 4;

        if(op == _EEQ) fprintf(asmout, "beq %s,%s,NOT_LABEL%d\n",exp1.reg_name,exp2.reg_name,not_label );
        else if(op == _NEQ) fprintf(asmout, "bne %s,%s,NOT_LABEL%d\n",exp1.reg_name,exp2.reg_name,not_label );    
        else if(op == _GR) fprintf(asmout, "bgt %s,%s,NOT_LABEL%d\n",exp1.reg_name,exp2.reg_name,not_label );    
        else if(op == _GRQ) fprintf(asmout, "bge %s,%s,NOT_LABEL%d\n",exp1.reg_name,exp2.reg_name,not_label );    
        else if(op == _LE) fprintf(asmout, "blt %s,%s,NOT_LABEL%d\n",exp1.reg_name,exp2.reg_name,not_label );    
        else if(op == _LEQ) fprintf(asmout, "ble %s,%s,NOT_LABEL%d\n",exp1.reg_name,exp2.reg_name,not_label );    
        
        fprintf(asmout, "li %s,0\n",exp1.reg_name );
        fprintf(asmout, "j NOT_LABEL_END%d\n",not_label );
        fprintf(asmout, "NOT_LABEL%d:\n li %s,1\n",not_label,exp1.reg_name );
        fprintf(asmout, "NOT_LABEL_END%d:\n",not_label );
        not_label++;
        ret.reg_name = exp1.reg_name;
        freename(exp2.reg_name);

        return ret;
    }
    

    

    
    if(op == _PLUS || op == _MINUS){
        if(exp1.ptr_depth + exp1.size > 0 && exp2.ptr_depth + exp2.size > 0) return print_opt_error(exp1,op,exp2);
        if(exp2.size + exp2.ptr_depth > 0){
            struct node temp = exp1;
            exp1 = exp2;
            exp2 = temp;

        }

        

        if(exp1.ptr_depth + exp1.size > 0){
            if(exp2.et != FLOAT_T){
                
                if(exp1.size > 0){
                    fprintf(asmout, "addi $a0,$fp,-%d\n",exp1.st_off + exp1.typeSize );
                    fprintf(asmout, "sub $a0,$a0,%s\n",exp1.reg_off);
                    freename(exp1.reg_off);
                    exp1.valid_off = 0;

                    exp1.reg_name = newname();
                    exp1.ptr_depth += exp1.size;
                    exp1.size = 0;
                    fprintf(asmout, "move %s,$a0\n",exp1.reg_name );
                }
                if(1/*!(exp1.ptr_depth == 1 && exp1.et == CHAR_T)*/){
                    fprintf(asmout, "li $a0,4\n" );
                    fprintf(asmout, "mult $a0,%s\n",exp2.reg_name );
                    fprintf(asmout, "mflo %s\n",exp2.reg_name );    
                }
                fprintf(asmout, "sub %s,%s,%s\n",exp1.reg_name,exp1.reg_name,exp2.reg_name );
                freename(exp2.reg_name);

                ret.ptr_depth = exp1.ptr_depth;
                ret.et = exp1.et;
                ret.size = 0;
                ret.expr_val = -1000000;
                ret.reg_name = exp1.reg_name;
                ret.typeSize = 4;

                return ret;
            }
            else return print_opt_error(exp1,op,exp2);
        }

        ret.size = ret.ptr_depth = 0;
        ret.typeSize = 4;
        //if(exp1.typeSize == 1 && exp2.typeSize == 1) ret.typeSize = 4;

        if(op == _PLUS){
            ret.expr_val = add(exp2.expr_val,exp1.expr_val);
            fprintf(asmout, "add %s,%s,%s\n",exp1.reg_name,exp1.reg_name,exp2.reg_name );
        }
        else {
            ret.expr_val = sub(exp1.expr_val,exp2.expr_val);
            fprintf(asmout, "sub %s,%s,%s\n",exp1.reg_name,exp1.reg_name,exp2.reg_name );
        }
        freename(exp2.reg_name);
        ret.reg_name = exp1.reg_name;

        if(exp1.et == FLOAT_T || exp2.et == FLOAT_T) ret.et = FLOAT_T;
        else {
            if((exp1.et == CHAR_T && exp2.et == INT_T) || (exp2.et == CHAR_T && exp1.et == INT_T)) ret.et = CHAR_T;
            else ret.et = INT_T;
        }
        return ret; 
    }

    if(exp1.size + exp1.ptr_depth > 0 || exp2.size + exp2.ptr_depth > 0){
        return print_opt_error(exp1,op,exp2);
    }
    ret.size = ret.ptr_depth = 0;
    ret.typeSize = 4;
    // if(exp1.typeSize == 1 && exp2.typeSize == 1) ret.typeSize = 4;

    if(exp1.et == FLOAT_T || exp2.et == FLOAT_T) ret.et = FLOAT_T;
    else ret.et = INT_T;

    if(op == _TIMES){
        ret.expr_val = mul(exp2.expr_val,exp1.expr_val);
        fprintf(asmout, "mult %s,%s\n",exp1.reg_name,exp2.reg_name );
        fprintf(asmout, "mflo %s\n",exp1.reg_name );
    }
    else {
        ret.expr_val = _div(exp1.expr_val,exp2.expr_val);
        fprintf(asmout, "div %s,%s\n",exp1.reg_name,exp2.reg_name );
        fprintf(asmout, "mflo %s\n",exp1.reg_name );
    }
    freename(exp2.reg_name);
    ret.reg_name = exp1.reg_name;

    return ret;
}

int add(int a,int b)
{
    if(a!=-1000000 && b!=-1000000)
        return a+b;

    return -1000000;
}

int mul(int a,int b){
    if(a!=-1000000 && b!=-1000000)
        return a*b;

    return -1000000;
}

int sub(int a,int b){
    if(a!=-1000000 && b!=-1000000)
        return a-b;

    return -1000000;
}

int _div(int a,int b){
    if(a!=-1000000 && b!=-1000000){
        if(b==0){
            printf("Cannot divide by 0\n");
            return -1000000;
        }

        return a/b;
    }

    return -1000000;
}

struct node comp_opt_type(enum op_type op,struct node exp){
    if(exp.et == ERROR) {
        /*freename(exp.reg_name);
        freename(exp.reg_off);*/

        exp.reg_name = (char*)malloc(1);
        exp.reg_off = (char*)malloc(1);
        return exp;
    }

    struct node ret;
    ret.expr_val = -1000000;
    if(exp.size > 0){
        ret.et = ERROR;

        ret.reg_name = (char*)malloc(1);
        ret.reg_off = (char*)malloc(1);
        printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
        /*freename(exp.reg_name);
        freename(exp.reg_off);*/
        return ret;
    }
    if(exp.ptr_depth > 0){
        if(op == _NOT){
            ret.et = ERROR;

        ret.reg_name = (char*)malloc(1);
        ret.reg_off = (char*)malloc(1);
            /*freename(exp.reg_name);
            freename(exp.reg_off);*/
            printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
            return ret;
        }
        ret = exp;
        return ret;
    }
    if(op == _NOT){
        if(exp.et == FLOAT_T){
            ret.et = ERROR;

        ret.reg_name = (char*)malloc(1);
        ret.reg_off = (char*)malloc(1);
            /*freename(exp.reg_name);
            freename(exp.reg_off);*/
            printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
            return ret;
        }
        ret = exp;
        ret.et = BOOL;
        return ret;
    }

    if(exp.et == BOOL){
        ret.et = ERROR;

        ret.reg_name = (char*)malloc(1);
        ret.reg_off = (char*)malloc(1);
        /*freename(exp.reg_name);
        freename(exp.reg_off);*/
        printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
        return ret;
    }
    ret = exp;
    return ret;
}


char *newname()
{
    int i=0;
    for(;i<NUM_REG;++i) if(!used[i]){
        char *c = (char *)malloc(sizeof(char)*4);
        c = Names[i];
        used[i]=1;
        return c;
    }


    fprintf( stderr,": Expression too complex\n" );
    exit(1);
}

void freename(char *s)
{
    if(s == NULL) return;

    int i=0;
    for(;i<NUM_REG;++i) if(strcmp(Names[i],s) == 0){
        //assert(used[i] == 1);
        used[i]=0;
        return;
    }
}

int main (void) 
{
        fout = fopen("parser.txt","w");
        asmout= fopen("asm.s","w");
        fprintf(asmout, ".data\n");

        func_table = NULL;
        symb_table = NULL;
        cur_scope=0;
        not_label = 0;

        int i=0;
        for(;i<NUM_REG;++i) {
            char temp[4];
            if(i <= 9){
                sprintf(temp,"$t%d",i);
                strcpy(Names[i],temp);
            }
            else{
                sprintf(temp,"$s%d",i-10);
                strcpy(Names[i],temp);
            }
            used[i] = 0;
        }

    //printf("dfnaksjdnkjasndkjans\n");
   // n1.reg_off = (char*)malloc(1);

	return yyparse ();
}

void yyerror (char *s) {fprintf (stderr,  "LINE:%d %s \n",mylineno,s);} 
