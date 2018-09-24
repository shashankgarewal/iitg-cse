/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 79 "comp.c" /* yacc.c:1909  */


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


#line 143 "y.tab.h" /* yacc.c:1909  */

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
#line 178 "comp.c" /* yacc.c:1909  */
   
    struct list_brac lb;


    int list_num;
    int label_num;
    struct node n1;

    struct list_attr lis_attr;

#line 270 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
