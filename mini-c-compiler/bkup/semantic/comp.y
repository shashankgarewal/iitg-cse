%{
void yyerror(char *s);
extern int mylineno;
extern char *yytext;
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
FILE* fout;
int cur_scope = 0;

%}

%error-verbose
%start st

%token  EOI            
%token  SEMI
%token  MAIN                
%token  PLUS        
%token  TIMES       
%token  LP             
%token  RP             
%token  MINUS         
%token  DIV           
%token  NEQ           
%token  LE             
%token  LEQ            
%token  GR             
%token  GRQ            
%token  EQ             
%token  IF             
%token  OPEN_CURL      
%token  CLOSE_CURL     
%token  ELSE           
%token  WHILE          
%token  DO             
%token  EEQ            
%token  SWITCH         
%token  CASE            
%token  DEFAULT        
%token  FOR            
%token  BREAK          
%token  CONTINUE       
%token  LSQBRAC        
%token  RSQBRAC        
%token  DOT                
%token  COLON          
%token  COMMA   
%token  PLUSPLUS       
%token  MINUSMINUS     
%token  RETURN                        
%token  NOT                
%token  ID            
%token  INT
%token  FLOAT          
%token  STRING
%token  AMP
%token  INT_TYPE
%token  FLOAT_TYPE
%token  CHAR_TYPE
%token  CHAR
%token  AND_AND
%token  OR_OR

%code requires{

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
    
    int valid;          /* whether this entry is deleted or not*/
    int scope;
    
    struct node *next;
};
struct list_attr{
    struct node* list_var;
    int size;
};

struct func_node *func_table;
struct node cur_func;
struct node *symb_table;

void insert_symb_table(struct node* var);
void add_params_to_sym(struct node *param_list);
void check_distinct(struct node *attrs, int size);
struct func_node* get_func_entry(char *name);
void insert_func_entry(struct node type,struct node id,struct list_attr attrs);
struct node check_func_exists(char *name);
int match_node_list(struct node *list_var,int lsize,struct node *param_list,int psize);
int check_func_proto(struct node type,struct node id,struct list_attr attrs);
int check_param_match(struct node fn,struct list_attr attrs);
int match_node(struct node *n1,struct node *n2);
int exists_in_scope(struct node var);
void patch_type(struct node type,struct list_attr lis);
struct node get_sym(char* var_name,int size_used);
void delete_entries();
struct node print_comp_error(struct node exp1, struct node exp2);
struct node compatible(struct node exp1,struct node exp2);
struct node print_opt_error(struct node exp1,enum op_type op, struct node exp2);
struct node comp_binopt_type(struct node exp1,enum op_type op, struct node exp2);
struct node comp_opt_type(enum op_type op,struct node exp);
}

%union{   
    int list_num;
    struct node n1;
    struct list_attr lis_attr;
}

%type<list_num> ptr br_list 
%type<n1> id ide_id_decl type fis ide_id function_call s_dash expression
%type<n1> expression_and term factor arithmetic multdiv final
%type<lis_attr> decl_list list_params list_call_params


%%

epsilon : ;

decl : type decl_list {patch_type($1,$2);};

st      : decl SEMI st | proto;


decl_list : ide_id_decl { 
                $$.list_var = (struct node*)malloc(sizeof(struct node));
                $$.list_var[0] = $1; $$.size = 1;} 
            | ide_id_decl COMMA decl_list { 
                $$.size = 1 + $3.size;
                $$.list_var = (struct node*)malloc(sizeof(struct node)*$$.size);
                
                int iter = 0;
                for(iter = 0;iter < $3.size; ++iter) $$.list_var[iter] = $3.list_var[iter];
                $$.list_var[$3.size] = $1;
             }
            ;

id : ID {strcpy($$.name,strdup(yytext));};
proto_head : type id LP list_params RP {insert_func_entry($1,$2,$4);}
proto : proto_head SEMI proto 
        | st2
        ;

func_head :  type id LP list_params RP {
            if(check_func_proto($1,$2,$4) == 0){
                printf("Prototype mismatch/not declared\n");
            }
            cur_scope++;
            add_params_to_sym($4.list_var);
            cur_func = $1;
            }
        ;
int_head: INT_TYPE MAIN LP RP{cur_func.et = INT_T;cur_func.size = 0;cur_func.ptr_depth = 0;};
st2      : int_head OPEN_CURL s CLOSE_CURL {fprintf(fout,"st2 -> MAIN(){ s } \n");}
        | func_head func_body st2 
        ;
func_body: OPEN_CURL s CLOSE_CURL{
        delete_entries(cur_scope);
        cur_scope--;
};

ptr : TIMES {$$ = 1;}| TIMES ptr {$$ = $2 + 1;};


ide_id_decl : id {
        strcpy($$.name,$1.name);
        $$.size = 0;
    } 
    | id  br_list{
        strcpy($$.name,$1.name);
        $$.size = $2;
        };


br_list : LSQBRAC expression RSQBRAC { 
            if($2.et == INT_T && $2.ptr_depth == 0 && $2.size == 0){
                $$ = 1;
            }
            else{ 
                printf("index must be int\n");
                $$=1;
            }
        }
        | LSQBRAC expression RSQBRAC br_list { 
            /*$$.dim_ptr = (int*)malloc(sizeof(int)*($4.size+1));

            int iter = 0;
            for(iter = 0;iter < $4.size; ++iter) $$.dim_ptr[iter] = $4.dim_ptr[iter];
            */

            $$ = $4 + 1;

            if($2.et == INT_T && $2.ptr_depth == 0 && $2.size == 0){
                /*$$.dim_ptr[$4.size] = *((int *)$2.val[0]);
                $$.prod *= $2.prod;*/
            }
            else{ 
                printf("index must be int\n");
            }           
    }
    ;


type : INT_TYPE { $$.et = INT_T; $$.ptr_depth=0;}
                | FLOAT_TYPE { $$.et = FLOAT_T; $$.ptr_depth=0;}
                | CHAR_TYPE { $$.et = CHAR_T; $$.ptr_depth=0;}
                | INT_TYPE ptr { $$.et = INT_T; $$.ptr_depth=$2;}
                | FLOAT_TYPE ptr { $$.et = FLOAT_T; $$.ptr_depth=$2;}
                | CHAR_TYPE ptr { $$.et = CHAR_T; $$.ptr_depth=$2;}
                ;



list_params     : type ide_id_decl { 
                    $$.list_var = (struct node*)malloc(sizeof(struct node));
                    $2.et = $1.et;
                    $2.ptr_depth = $1.ptr_depth;
                    $$.list_var[0] = $2; $$.size = 1;
                    } 
                | type ide_id_decl COMMA list_params  
                { 
                    $$.size = 1 + $4.size;
                    $$.list_var = (struct node*)malloc(sizeof(struct node)*$$.size);
                    
                    int iter = 0;
                    for(iter = 0;iter < $4.size; ++iter) $$.list_var[iter] = $4.list_var[iter];
                    $2.et = $1.et;
                    $2.ptr_depth = $1.ptr_depth;
                    $$.list_var[$4.size] = $2;
                 }
                ;

fis     : INT   {$$.et = INT_T; $$.ptr_depth = 0; $$.size = 0;}
        | FLOAT  {$$.et = FLOAT_T; $$.ptr_depth = 0; $$.size = 0;}
        | CHAR   {$$.et = CHAR_T; $$.ptr_depth = 0; $$.size = 0;}
        ;

ide_id : id { $$ = get_sym($1.name,0);} | id br_list { $$ = get_sym($1.name,$2); };

list_call_params        : expression   {
                            $$.list_var = (struct node*)malloc(sizeof(struct node));
                            $$.list_var[0] = $1;
                            $$.size = 1;
                        }
                        | expression COMMA list_call_params {
                            $$.size = 1 + $3.size;
                            
                            $$.list_var = (struct node*)malloc(sizeof(struct node)*$$.size);
                            
                            int iter = 0;
                            for(iter = 0;iter < $3.size; ++iter) $$.list_var[iter] = $3.list_var[iter];
                            $$.list_var[$3.size] = $1;
                        }
                        ;

s       : epsilon {fprintf(fout,"s -> epsilon\n");}
        | uif s {fprintf(fout,"s -> uif s\n");}
        | mif s {fprintf(fout,"s -> mif s\n");}
        ;

function_call   : id LP list_call_params RP   {$$ = check_func_exists($1.name); if($$.valid == 1){
                            check_param_match($$,$3);
}}
                ;

s_dash  : EQ  expression  {$$ = $2;}
        ;

for_exp : FOR LP ide_id EQ expression SEMI expression SEMI expression RP
                {
                    compatible($3,$5);
                    if($7.et != BOOL || $7.size > 0 || $7.ptr_depth >0){
                        printf("Boolean required in expression\n");
                    }
                };

for_stmnt  :  for_exp single_or_block ;

while_exp : WHILE LP expression RP 
            {
                if($3.et != BOOL || $3.size > 0 || $3.ptr_depth >0)
                    printf("Boolean required in expression\n");
            };
while_stmnt  : while_exp single_or_block  {fprintf(fout,"while_stmnt -> while(expression) single_or_block\n");};

do_while_stmnt  : DO single_or_block WHILE LP expression RP  
                {
                    if($5.et != BOOL || $5.size > 0 || $5.ptr_depth >0)
                        printf("Boolean required in expression\n");
                };

switch_stmnt  : SWITCH LP ide_id LP OPEN_CURL case_stmnts DEFAULT COLON single_or_block CLOSE_CURL  
                {fprintf(fout," switch_stmnt -> SWITCH(ide_id) { case_stmnts DEFAULT: single_or_block } \n");};
case_stmnts  : CASE fis COLON single_or_block {fprintf(fout,"case_stmnts -> CASE fis : single_or_block\n");}
                 | CASE fis COLON single_or_block case_stmnts  {fprintf(fout,"case_stmnts -> CASE fis : single_or_block case_stmnts\n");};

single_or_block  :   mif | uif
                 ;

ifexp: IF LP expression RP
        {
            if($3.et != BOOL || $3.size > 0 || $3.ptr_depth >0){
                printf("Boolean expected\n");
            }
        };

mif  : ifexp mif ELSE mif 
        | other_than_if
        ;

uif  : ifexp mif  
        | ifexp uif  
       |  ifexp mif ELSE uif  
       ;

opc: OPEN_CURL {cur_scope++;};

other_than_if       : ide_id s_dash SEMI  { compatible($1,$2); }
                    | function_call SEMI  {fprintf(fout,"other_than_if -> function_call;\n");}
                    | CONTINUE SEMI  {fprintf(fout,"other_than_if-> CONTINUE;\n");}
                    | BREAK SEMI {fprintf(fout,"other_than_if-> BREAK;\n");}
                    | while_stmnt  {fprintf(fout,"other_than_if-> while_stmnt\n");}
                    | for_stmnt  {fprintf(fout,"other_than_if-> for_stmnt\n");}
                    | switch_stmnt  {fprintf(fout,"other_than_if-> switch_stmnt\n");}
                    | do_while_stmnt  {fprintf(fout,"other_than_if-> do_while_stmnt\n");}
                    | opc s CLOSE_CURL   { delete_entries(cur_scope); cur_scope--;}
                    | decl SEMI
                    | RETURN expression SEMI  { compatible(cur_func,$2);}
                    ;

expression      : expression_and AND_AND expression  { $$ = comp_binopt_type($1,AND_AND,$3);}
                | expression_and OR_OR expression  { $$ = comp_binopt_type($1,OR_OR,$3);}
                | expression_and {$$ = $1;}
                ;

expression_and      : term EEQ expression_and  { $$ = comp_binopt_type($1,EEQ,$3);}
                | term NEQ expression_and  { $$ = comp_binopt_type($1,NEQ,$3);}
                | term {$$ = $1;}
                ;

term            : factor  {$$ = $1;}
                | factor LEQ term  { $$ = comp_binopt_type($1,LEQ,$3);}
                | factor GRQ term  { $$ = comp_binopt_type($1,GRQ,$3);}
                | factor GR term  { $$ = comp_binopt_type($1,GR,$3);}
                | factor LE term { $$ = comp_binopt_type($1,LE,$3);}
                ;

factor          : arithmetic {$$ = $1;}
                | arithmetic MINUS factor { $$ = comp_binopt_type($1,MINUS,$3);}
                ;

arithmetic      : multdiv {$$ = $1;} 
                | multdiv PLUS arithmetic  {$$ = comp_binopt_type($1,PLUS,$3);} 
                ;

multdiv         : final {$$ = $1;}
                | final TIMES multdiv {$$ = comp_binopt_type($1,TIMES,$3);}
                | final DIV multdiv  {$$ = comp_binopt_type($1,DIV,$3);}

final :   ptr ide_id {
            if($1 > $2.ptr_depth + $2.size ){
                printf("Error dereferencing\n");
                $$.et = ERROR;
            }else{
                $$.size = $2.size;
                $$.ptr_depth = $2.ptr_depth - $1;
                if($$.ptr_depth < 0)
                {
                    $$.size += $$.ptr_depth;
                    $$.ptr_depth = 0;
                }
                 $$.et = $2.et;
   
            }
        }
        | AMP ide_id {
            $$.ptr_depth = $2.ptr_depth + 1;
            $$.size = $2.size;
            $$.et = $2.et;
        }
        | ptr LP expression RP {
            if($1 > $3.ptr_depth + $3.size ){
                printf("Error dereferencing\n");
                $$.et = ERROR;
            }else{
                $$.size = $3.size;

                $$.ptr_depth = $3.ptr_depth - $1;
                if($$.ptr_depth < 0)
                {
                    $$.size += $$.ptr_depth;
                    $$.ptr_depth = 0;
                }
                 $$.et = $3.et;
   
            }
        }
        | type LP expression RP {
            $$ = compatible($1,$3);
        }
        | ide_id  {
                $$ = $1;
            }
        | PLUSPLUS ide_id  {
                $$ = comp_opt_type(PLUS,$2);
        }
        | MINUSMINUS ide_id  {

           $$ = comp_opt_type(MINUS,$2);
        }
        | ide_id PLUSPLUS  {

            $$ = comp_opt_type(PLUS,$1);
        }
        | ide_id MINUSMINUS  {

            $$ = comp_opt_type(MINUS,$1);
        }
        | LP expression RP  {
                $$ = $2;
            
        }
        | NOT LP expression RP  {
            
            $$ = comp_opt_type(NOT,$3);
        }
        | fis  {
                $$ = $1;
            }
        | function_call  {
                $$ = $1;
        }
        | LP ide_id EQ expression RP
        {
            $$ = compatible($2,$4);
        }
        ;
%%

void insert_symb_table(struct node* var)
{
    if (var == NULL)
        return ;
    
    var->valid = 1;
    var->next = symb_table;
    symb_table = var;
}

void add_params_to_sym(struct node *param_list)
{
    while(param_list!=NULL)
    {
        param_list->scope = 1;

        if(exists_in_scope(*param_list)){
            printf("Parameter already defined\n");
        }else{
            insert_symb_table(param_list);
        }

        param_list = param_list->next;
    }
}

void check_distinct(struct node *attrs, int size)
{
    int i,j;
    for (i =0;i<size;i++)
    {
        for(j=i+1;j<size;j++){
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
        printf("%s is name of fn  \n",act_func->name);
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

    printf("Inserting %s\n",n->name);
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

int match_node_list(struct node *list_var,int lsize,struct node *param_list,int psize)
{
    
    if(lsize != psize)
    {
        printf("Number of var mismatch");
        return 0;
    }
    int i;
    
    for(i = 0;i<lsize;i++)
    {
        if(!match_node(&list_var[i],&param_list[i]))
        {
            printf("variable mismatch : %s %s\n",list_var[i].name,param_list[i].name);
            return 0;
        }
    }
    printf("EXIT\n");
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
        && match_node_list(attrs.list_var,attrs.size,act_func->param_list,act_func->num_params))
    {
        act_func->valid = 1;
        return 1;
    }

    return 0;
}

int check_param_match(struct node fn,struct list_attr attrs)
{
    printf("In check param\n\n");
    struct func_node *func = get_func_entry(fn.name);
    int ret_val = match_node_list(func->param_list,func->num_params,attrs.list_var,attrs.size);

    if(ret_val == 0)
        printf("Parameters mismatch for the Function %s\n",func->name);

    return ret_val;
}




int match_node(struct node *n1,struct node *n2)
{
    struct node ret = compatible(*n1,*n2);
    printf("%d return\n",ret.et);
    if(ret.et == ERROR)
        return 0;
    else
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
        if(exists_in_scope(lis.list_var[iter])){
            printf("%s variable already defined\n",lis.list_var[iter].name);
        }
        else{
            lis.list_var[iter].ptr_depth = type.ptr_depth;
            lis.list_var[iter].et = type.et;
            lis.list_var[iter].scope = cur_scope;
            insert_symb_table(lis.list_var+iter);
        }
    }
}

struct node get_sym(char* var_name,int size_used){
    struct node* temp = symb_table;
    struct node* node_found = NULL;
    int cur_max_scope = -1;

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
    if(node_found == NULL || node_found -> size < size_used){
        printf("variable not found %s\n",var_name);
        ret.et = ERROR;
        return ret;
    }
    ret.et = node_found->et;
    ret.ptr_depth = node_found->ptr_depth;
    ret.size = node_found -> size - size_used;
    return ret;
}

void delete_entries(){
    struct node* temp = symb_table;
    while(temp){
        if(temp->scope == cur_scope){
            temp->valid = 0;
        }
        temp = temp->next;
    }
}

struct node print_comp_error(struct node exp1, struct node exp2){
    struct node ret;
    ret.et = ERROR;
    printf("%d ptr: %d size: %d typecast not compatible with %d ptr: %d size: %d\n",exp1.et,exp1.ptr_depth,exp1.size,
     exp2.et,exp2.ptr_depth,exp2.size);

    return ret;
}
struct node compatible(struct node exp1,struct node exp2){
    if(exp1.et == ERROR || exp2.et == ERROR) return exp1;

    struct node ret;
    if(exp1.ptr_depth > 0){
        if(exp1.size != exp2.size || exp2.ptr_depth != exp1.ptr_depth) return print_comp_error(exp1,exp2);
        return exp1; 
    }
    if(exp1.size > 0){
        if(exp2.size + exp2.ptr_depth != exp1.size) return print_comp_error(exp1,exp2);
    }
    if(exp1.et == CHAR_T && exp2.et == FLOAT_T) return print_comp_error(exp1,exp2);
    if(exp1.et == BOOL && exp2.et == FLOAT_T) return print_comp_error(exp1,exp2);
    return exp1;
}

struct node print_opt_error(struct node exp1,enum op_type op, struct node exp2){
    struct node ret;
    ret.et = ERROR;
    printf("%d ptr: %d size: %d op: %d not compatible with %d ptr: %d size: %d\n",exp1.et,exp1.ptr_depth,exp1.size,
    op, exp2.et,exp2.ptr_depth,exp2.size);

    return ret;
}
struct node comp_binopt_type(struct node exp1,enum op_type op, struct node exp2){
    if(exp1.et == ERROR || exp2.et == ERROR) return exp1;

    struct node ret;
    if(op == _AND_AND || op == _OR_OR){
        if(exp1.size + exp1.ptr_depth > 0 || exp2.size + exp2.ptr_depth > 0){
            return print_opt_error(exp1,op,exp2);
        }
        ret.et = BOOL;
        ret.ptr_depth = ret.size = 0;
        return ret;
    }
    if(op == _EEQ || op == _NEQ || op == _GR || op == _LE || op == _GRQ || op == _LEQ){
        if(exp1.size > 0 || exp2.size > 0 || exp1.ptr_depth != exp2.ptr_depth || exp1.et != exp2.et){
            return print_opt_error(exp1,op,exp2);
        }
        ret.et = BOOL;
        ret.ptr_depth = exp1.ptr_depth;
        ret.size = 0;
        return ret;
    }
    if(exp1.size > 0 || exp2.size > 0) return print_opt_error(exp1,op,exp2);
    if(op == _PLUS || op == _MINUS){
        if(exp1.ptr_depth > 0 && exp2.ptr_depth > 0) return print_opt_error(exp1,op,exp2);
        if(exp2.ptr_depth > 0){
            struct node temp = exp1;
            exp1 = exp2;
            exp2 = temp;
        }

        if(exp1.ptr_depth > 0){
            if(exp2.et != FLOAT_T){
                ret.ptr_depth = exp1.ptr_depth;
                ret.et = exp1.et;
                ret.size = 0;
                return ret;
            }
            else return print_opt_error(exp1,op,exp2);
        }

        ret.size = ret.ptr_depth = 0;
        if(exp1.et == FLOAT_T || exp2.et == FLOAT_T) ret.et = FLOAT_T;
        else ret.et = INT_T;
        return ret; 
    }
    if(exp1.size + exp1.ptr_depth > 0 || exp2.size + exp2.ptr_depth > 0){
        return print_opt_error(exp1,op,exp2);
    }
    ret.size = ret.ptr_depth = 0;
    if(exp1.et == FLOAT_T || exp2.et == FLOAT_T) ret.et = FLOAT_T;
    else ret.et = INT_T;
    return ret;
}

struct node comp_opt_type(enum op_type op,struct node exp){
    if(exp.et == ERROR) return exp;

    struct node ret;
    if(exp.size > 0){
        ret.et = ERROR;
        printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
        return ret;
    }
    if(exp.ptr_depth > 0){
        if(op == _NOT){
            ret.et = ERROR;
            printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
            return ret;
        }
        ret.et = exp.et;
        ret.ptr_depth = exp.ptr_depth;
        ret.size = exp.size;
        return ret;
    }
    if(op == _NOT){
        if(exp.et == FLOAT_T){
            ret.et = ERROR;
            printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
            return ret;
        }
        ret.et = BOOL;
        ret.ptr_depth = exp.ptr_depth;
        ret.size = exp.size;
        return ret;
    }

    if(exp.et == BOOL){
        ret.et = ERROR;
        printf("%d op not compatible with %d ptr: %d size: %d type\n",op,exp.et,exp.ptr_depth,exp.size);
        return ret;
    }
    ret.et = exp.et;
    ret.ptr_depth = exp.ptr_depth;
    ret.size = exp.size;
    return ret;
}

int main (void) 
{
        fout = fopen("parser.txt","w");
        func_table = NULL;
        symb_table = NULL;
        cur_scope=0;
	return yyparse ();
}

void yyerror (char *s) {fprintf (stderr,  "LINE:%d %s \n",mylineno,s);} 
