%{
void yyerror(char *s);
extern int mylineno;
#include <stdio.h>     /* C declarations used in actions */
#include <stdlib.h>
#include <string.h>
FILE* fout;

enum ele_type {INT,FLOAT,CHAR};
enum ret_type {INT,FLOAT,CHAR,VOID};
enum type {SIMPLE,ARRAY};


int cur_scope = 0;

struct func_node{
    char name[50];
    enum ret_type return_type;

    int ptr_depth;
    int valid;
    struct node *param_list;
    int num_params;

    struct func_node *next;
};
struct func_node *func_table;


struct node
{
    char name[50];
    enum type t;        /* array / var*/
    enum ele_type et;
    int valid;          /* whether this entry is deleted or not*/
    int scope;
    int ptr_depth;
    struct node **points_to;
    int *dim_ptr;
    struct node *next;
    struct void **values;
};

struct node *symb_table;

%}

%union{
    struct type_attr{
        enum ele_type type;
        int ptr_depth; 
    }ty_attr;

    struct list_attr{
        struct node* list_var;
        struct int* list_val;
    }lis_attr;

}

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
%token  NAME           
%token  PROCESSOR      
%token  ISA            
%token  CLOCK_SPEED    
%token  L1_MEMORY      
%token  L2_MEMORY      
%token  IS_RUNNING     
%token  SUBMIT_JOBS      
%token  SUBMIT_CLUS_JOBS  
%token  GET_CLOCK_SPEED
%token  RUN            
%token  DISCARD_JOBS
%token  FLOPS_REQUIRED  
%token  LIST_ALGOS  
%token  SCH_ID   
%token  LINK           
%token  START_POINT    
%token  END_POINT      
%token  BANDWIDTH      
%token  CHANNEL_CAPACITY   
%token  MEMORY         
%token  MEMORY_TYPE    
%token  MEM_SIZE       
%token  GET_AVAILABLE_MEMORY   
%token  JOB            
%token  JOB_ID              
%token  DEADLINE       
%token  MEM_REQUIRED   
%token  AFFINITY 
%token  GET_MEMORY 
%token  WAIT       
%token  CLUSTER        
%token  PROCESSORS     
%token  TOPOLOGY       
%token  LINK_BANDWIDTH 
%token  LINK_CAPACITY  
%token  USE_SCHEDULER   
%token  USE_CLUS_SCHEDULER         
%token  USE_LIST_SCHEDULER            
%token  ADD_ALGORITHM            
%token  SCH_ALGO            
%token  LIST_SCH            
%token  CODE_PTR            
%token  START_SCHEDULER     
%token  START_CLUS_SCHEDULER             
%token  STOP_SCHEDULER             
%token  STOP_CLUS_SCHEDULER               
%token  NOT    	           
%token  ID            
%token	INT
%token  FLOAT 	       
%token  STRING
%token  AMP
%token	VOID
%token	INT_TYPE
%token	FLOAT_TYPE
%token	CHAR_TYPE
%token 	CHAR
%token PROCESSOR_TYPE 
%token LINK_TYPE 
%token MEM_TYPE 
%token JOB_TYPE 
%token CLUSTER_TYPE 
%token SCH_ALGO_TYPE 
%token LIST_SCH_TYPE

%type <ty_attr> type
%type <lis_attr> list_params,decl_list
%%

epsilon : ;

st      : decl SEMI st | proto;

proto : type ID LP list_params RP SEMI proto {insert_func_entry($1.type,$1.ptr_depth,$2,$4.list_var);}
        | VOID ID LP list_params RP OPEN_CURL proto {insert_func_entry(3,0,$2,$4.list_var);}
        | st2
        ;

func_head :  type ID LP list_params RP {
            if(check_func_proto($1.type,$1.ptr_depth,$2,$4.list_var) == 0){
                printf("Prototype mismatch/not declared\n");
            }
            cur_scope++;
            add_params_to_sym($4.list_var);
            }
            | VOID ID LP list_params RP{
            if(check_func_proto(3,0,$2,$4.list_var) == 0){
                printf("Prototype mismatch/not declared\n");
            }
            cur_scope++;
            add_params_to_sym($4.list_var);
            }
        ;
st2      : INT_TYPE MAIN LP RP OPEN_CURL s CLOSE_CURL {fprintf(fout,"st2 -> MAIN(){ s } \n");}
        | func_head func_body st2 
        ;
func_body: OPEN_CURL s CLOSE_CURL{
        delete_entries(cur_scope);
        cur_scope--;
};

ptr : TIMES {$$.depth = 1;}| TIMES ptr {$$.depth = $2.depth + 1};

ide_id : ID {$$.name = $1,$$.type=SIMPLE,$$.dim_ptr = NULL;} | ID br_list {$$.name = $1,$$.type=ARRAY,$$.dim_ptr= $2.dim_ptr};
br_list : LSQBRAC expression RSQBRAC { 
            if($2.type == INT){$$.dim_ptr = makelist($2.val);}
            else{ $$.type = ERROR; printf("index must be int");}
        }
        | LSQBRAC expression RSQBRAC br_list {            
            if($2.type == INT){$$.dim_ptr = append($2.val,$4.dim_ptr);}
            else{ $$.type = ERROR; printf("index must be int");}
        };

decl : type decl_list {patch_type($1.type,$1.ptr_depth,$2.list_var,$2.list_val);};

type : INT_TYPE { $$.type = INT; $$.ptr_depth=0;}
                | FLOAT_TYPE { $$.type = FLOAT; $$.ptr_depth=0;}
                | CHAR_TYPE { $$.type = CHAR; $$.ptr_depth=0;}
                | INT_TYPE ptr { $$.type = INT; $$.ptr_depth=$2.depth;}
                | FLOAT_TYPE ptr { $$.type = FLOAT; $$.ptr_depth=$2.depth;}
                | CHAR_TYPE ptr	{ $$.type = CHAR; $$.ptr_depth=$2.depth;}
                | PROCESSOR_TYPE { $$.type = INT; $$.ptr_depth=0;}
                | LINK_TYPE { $$.type = INT; $$.ptr_depth=0;}
                | MEM_TYPE { $$.type = INT; $$.ptr_depth=0;}
                | JOB_TYPE { $$.type = INT; $$.ptr_depth=0;}
                | CLUSTER_TYPE { $$.type = INT; $$.ptr_depth=0;}
                | SCH_ALGO_TYPE { $$.type = INT; $$.ptr_depth=0;}
                | LIST_SCH_TYPE	{ $$.type = INT; $$.ptr_depth=0;}
                | PROCESSOR_TYPE ptr { $$.type = INT; $$.ptr_depth=0;}
                | LINK_TYPE ptr { $$.type = INT; $$.ptr_depth=0;}
                | MEM_TYPE ptr { $$.type = INT; $$.ptr_depth=0;}
                | JOB_TYPE ptr { $$.type = INT; $$.ptr_depth=0;}
                | CLUSTER_TYPE ptr { $$.type = INT; $$.ptr_depth=0;}
                | SCH_ALGO_TYPE ptr { $$.type = INT; $$.ptr_depth=0;}
                | LIST_SCH_TYPE ptr;

decl_list : ide_id { $$.list_var = make_node_list($1.name,$1.type,$1.dim_ptr); } 
            | ide_id EQ expression
            | ide_id COMMA decl_list 
            | ide_id EQ expression COMMA decl_list; 

list_params     : type ide_id {fprintf(fout,"list_params -> ide_id \n");}
                | type ide_id COMMA list_params  {fprintf(fout,"list_params -> ide_id,list_params\n");}
                | def_list_ids {fprintf(fout,"list_params -> def_list_ids\n");}
                ;

def_list_ids    : epsilon  {fprintf(fout,"def_list_ids -> epsilon\n");}
                | type ide_id  EQ  expression  {fprintf(fout,"def_list_ids -> ide_id = expression\n");}
                | type ide_id  EQ  expression COMMA def_list_ids  {fprintf(fout,"def_list_ids -> ide_id = expression,def_list_ids\n");}
                 ;

fis     : INT 	{fprintf(fout," fis -> INT\n");}
		| FLOAT  {fprintf(fout," fis -> FLOAT\n");}
		| CHAR 	 {fprintf(fout," fis -> CHAR\n");}
        | STRING {fprintf(fout,"fis -> STRING\n");}
        | constructor
        | var_array
        ;


list_call_params        : expression COMMA list_call_params  {fprintf(fout," list_call_params -> expression,list_call_params\n");}
                        | expression {fprintf(fout,"list_call_params -> expression\n");}
                        ;

s       :epsilon {fprintf(fout,"s -> epsilon\n");}
        | uif s {fprintf(fout,"s -> uif s\n");}
        | mif s {fprintf(fout,"s -> mif s\n");}
        ;

function_call   : ID LP list_call_params RP   {fprintf(fout," function_call -> ID(list_call_params) \n");}
                ;

s_dash  : EQ  expression  {fprintf(fout," s_dash -> = expression\n");}
        | DOT recr {fprintf(fout,"s_dash -> .recr \n");}
        ;

var_array       : LSQBRAC list_call_params RSQBRAC {fprintf(fout,"var_array -> [list_call_params]\n");}
                ;


for_stmnt  : FOR LP ide_id EQ expression SEMI expression SEMI expression RP single_or_block  
                {fprintf(fout,"for_stmt -> for ( ide_id=expression;expression;expression) single_or_block\n");};

while_stmnt  : WHILE LP expression RP single_or_block  {fprintf(fout,"while_stmnt -> while(expression) single_or_block\n");};
do_while_stmnt  : DO single_or_block WHILE LP expression RP  {fprintf(fout," do_while_stmnt -> do single_or_block while (expression) \n");};

switch_stmnt  : SWITCH LP ide_id LP OPEN_CURL case_stmnts DEFAULT COLON single_or_block CLOSE_CURL  
                {fprintf(fout," switch_stmnt -> SWITCH(ide_id) { case_stmnts DEFAULT: single_or_block } \n");};
case_stmnts  : CASE fis COLON single_or_block {fprintf(fout,"case_stmnts -> CASE fis : single_or_block\n");}
                 | CASE fis COLON single_or_block case_stmnts  {fprintf(fout,"case_stmnts -> CASE fis : single_or_block case_stmnts\n");};

single_or_block  :   mif {fprintf(fout,"single_or_block -> mif\n");}
                    | uif  {fprintf(fout,"single_or_block -> uif\n");}
                 ;

mif  : IF LP expression RP mif  ELSE   mif  {fprintf(fout," mif -> if(expression) mif else mif \n");}
        | other_than_if  {fprintf(fout,"mif->other_than_if\n");};

uif  :  IF LP expression RP mif  {fprintf(fout,"uif-> if(expression) mif\n");}
        | IF LP expression RP uif   {fprintf(fout,"uif-> if(expression) uif\n");}
       |  IF LP expression RP mif ELSE uif  {fprintf(fout,"uif-> if(expression) mif else uif\n");};

 

other_than_if       : ide_id s_dash SEMI  {fprintf(fout,"other_than_if -> ide_id s_dash;\n");}
                    | function_call SEMI  {fprintf(fout,"other_than_if -> function_call;\n");}
                    | RUN LP list_call_params RP SEMI  {fprintf(fout,"other_than_if -> RUN(list_call_params);\n");}
                    | WAIT LP expression RP SEMI  {fprintf(fout,"other_than_if -> WAIT(expression);\n");}
                    | RETURN SEMI  {fprintf(fout,"other_than_if -> RETURN;\n");}
                    | RETURN expression SEMI  {fprintf(fout,"other_than_if -> RETURN expression;\n");}
                    | CONTINUE SEMI  {fprintf(fout,"other_than_if-> CONTINUE;\n");}
                    | BREAK SEMI {fprintf(fout,"other_than_if-> BREAK;\n");}
                    | while_stmnt  {fprintf(fout,"other_than_if-> while_stmnt\n");}
                    | for_stmnt  {fprintf(fout,"other_than_if-> for_stmnt\n");}
                    | switch_stmnt  {fprintf(fout,"other_than_if-> switch_stmnt\n");}
                    | do_while_stmnt  {fprintf(fout,"other_than_if-> do_while_stmnt\n");}
                    | OPEN_CURL s CLOSE_CURL   {fprintf(fout,"other_than_if->{s}\n");}
                    | decl SEMI
                    ;


expression      : term EEQ expression  {fprintf(fout," expression -> term == expression\n");}
                | term NEQ expression  {fprintf(fout," expression -> term != expression\n");}
                | term {fprintf(fout," expression -> term\n");}
                ;

term            : factor  {fprintf(fout," term -> factor\n");}
                | factor LEQ term  {fprintf(fout,"term -> factor <= term\n");}
                | factor GRQ term  {fprintf(fout,"term -> factor >= term\n");}
                | factor GR term  {fprintf(fout,"term -> factor > term\n");}
                | factor LE term {fprintf(fout,"term -> factor < term\n");}
                ;

factor          : arithmetic {fprintf(fout,"factor->arithmetic\n");}
                | arithmetic MINUS factor {fprintf(fout,"factor->arithmetic - factor \n");}
                ;

arithmetic      : multdiv {fprintf(fout,"arithmetic->multdiv\n");} 
                | multdiv PLUS arithmetic  {fprintf(fout,"arithmetic->multdiv + arithmetic\n");} ;

multdiv         : final {fprintf(fout,"multdiv->final\n");}
                 | final TIMES multdiv {fprintf(fout,"multdiv->final*multdiv\n");} 
                | final DIV multdiv  {fprintf(fout,"multdiv->final/multdiv\n");} ;

final :   ptr ide_id 
        | AMP ide_id
        | ptr LP expression RP
        | type LP expression RP
        | ide_id  {fprintf(fout,"final -> ide_id\n");}
        | PLUSPLUS ide_id  {fprintf(fout,"final -> ++ide_id \n");}
        | MINUSMINUS ide_id  {fprintf(fout,"final -> --ide_id \n");}
        | ide_id PLUSPLUS  {fprintf(fout,"final -> ide_id++ \n");}
        | ide_id MINUSMINUS  {fprintf(fout,"final -> ide_id--\n");}
        | LP expression RP  {fprintf(fout,"final -> (expression)\n");}
        | NOT LP expression RP  {fprintf(fout,"final -> !(expression)\n");}
        | ide_id DOT recr  {fprintf(fout,"final -> ide_id.recr\n");}
        | NOT ide_id DOT recr  {fprintf(fout,"final -> !ide_id.recr\n");}
        | fis  {fprintf(fout,"final -> fis\n");}
        | function_call  {fprintf(fout,"final -> function_call\n");}
        | LP ide_id EQ expression RP
        ;

recr : ide_id  {fprintf(fout,"recr -> ide_id\n");} 
        | member_function  {fprintf(fout,"recr -> fn_calls\n");} 
        | ide_id DOT recr  {fprintf(fout,"recr -> ide_id.recr\n");}
         ;



constructor : PROCESSOR proc_params  {fprintf(fout,"constructor -> PROCESSOR proc_params\n");}
        |  LINK link_params  {fprintf(fout,"constructor -> LINK link_params\n");}
        |  MEMORY mem_params  {fprintf(fout,"constructor ->  MEMORY mem_params \n");}
        |  JOB job_params  {fprintf(fout,"constructor -> JOB job_params\n");}
        | CLUSTER clus_params  {fprintf(fout,"constructor -> CLUSTER clus_params\n");}
        |  SCH_ALGO sch_algo_params  {fprintf(fout,"constructor -> SCH_ALGO sch_algo_params\n");}
        |  LIST_SCH list_sch_params {fprintf(fout,"constructor -> LIST_SCH list_sch_params\n");};

member_function : proc_func {fprintf(fout,"member_function -> proc_func\n");}
        | mem_func {fprintf(fout,"member_function -> mem_func\n");}
        | job_func {fprintf(fout,"member_function -> job_func\n");}
        | clus_func {fprintf(fout,"member_function -> clus_func\n");}
        | list_sch_func {fprintf(fout,"member_function -> list_sch_func\n");};





proc_params :   LP isa_eps expression  COMMA  clk_eps expression  COMMA  l1_eps expression proc_params_opt  RP  
            {fprintf(fout,"proc_params -> (isa_eps expression,clk_eps expression,l1_eps expression proc_params_opt)\n");};

proc_params_opt :   COMMA  l2_eps expression params_opt_aid_name 
                {fprintf(fout,"proc_params_opt -> ,l2_eps expression params_opt_aid_name\n");}
                | params_opt_aid_name {fprintf(fout,"proc_params_opt -> params_opt_aid_name\n");}; 

params_opt_aid_name :   COMMA  loc_sid_eps expression
                    {fprintf(fout,"params_opt_aid_name -> ,loc_sid_eps expression\n");}
                    |params_opt_name {fprintf(fout,"params_opt_aid_name -> params_opt_name\n");};

params_opt_name : epsilon {fprintf(fout,"params_opt_name -> epsilon\n");}
                |   COMMA  name_eps expression {fprintf(fout,"params_opt_name -> ,name_eps expression\n");}; 

isa_eps : ISA   EQ  {fprintf(fout,"isa_eps -> ISA =\n");} | epsilon
                ; 


clk_eps : CLOCK_SPEED   EQ  {fprintf(fout,"clk_eps -> CLOCK_SPEED =\n");} | epsilon
                ; 

l1_eps : L1_MEMORY   EQ  {fprintf(fout,"l1_eps -> L1_MEMORY =\n");} | epsilon
                ; 

l2_eps : L2_MEMORY   EQ  {fprintf(fout,"l2_eps -> L2_MEMORY =\n");}
                ;
 
name_eps : NAME   EQ  {fprintf(fout,"name_eps -> NAME =\n");}
                ;

loc_sid_eps : SCH_ID   EQ  {fprintf(fout,"loc_sid_eps -> SCH_ID =\n");}
                ;

proc_func : IS_RUNNING  LP   RP {fprintf(fout,"proc_func -> IS_RUNNING()\n");}
                |SUBMIT_JOBS  LP list_call_params  RP {fprintf(fout,"proc_func -> SUBMIT_JOBS(list_call_params) \n");}
                |GET_CLOCK_SPEED  LP   RP {fprintf(fout,"proc_func -> GET_CLOCK_SPEED()\n");}
                |DISCARD_JOBS  LP list_call_params  RP {fprintf(fout,"proc_func ->  DISCARD_JOBS  LP list_call_params  RP\n");}
                |START_SCHEDULER  LP   RP {fprintf(fout,"proc_func -> START_SCHEDULER  LP   RP\n");}
                |STOP_SCHEDULER  LP   RP {fprintf(fout,"proc_func -> STOP_SCHEDULER  LP   RP \n");}
                |USE_SCHEDULER  LP expression  RP  {fprintf(fout,"proc_func -> USE_SCHEDULER  LP expression  RP\n");}; 

link_params :   LP st_eps expression  COMMA  en_eps expression  COMMA  bw_eps expression  COMMA  ch_eps expression params_opt_name  RP  
                {fprintf(fout,"link_params -> (st_eps expression,en_eps expression,bw_eps expression,ch_eps expression params_opt_name)\n");}; 

st_eps : START_POINT   EQ  {fprintf(fout,"st_eps -> START_POINT =\n");} | epsilon
                ;
en_eps : END_POINT   EQ  {fprintf(fout,"en_eps -> END_POINT =\n");} | epsilon
                ;
bw_eps : BANDWIDTH   EQ  {fprintf(fout,"bw_eps -> BANDWIDTH = \n");} | epsilon
                ;
ch_eps : CHANNEL_CAPACITY   EQ  {fprintf(fout,"ch_eps -> CHANNEL_CAPACITY =\n");} | epsilon
                ;

mem_params :   LP mem_type_eps expression  COMMA  mem_size_eps expression params_opt_name  RP  
               {fprintf(fout,"mem_params -> (mem_type_eps expression,mem_size_eps expression params_opt_name)\n");}; 

mem_type_eps : MEMORY_TYPE   EQ  {fprintf(fout,"mem_type_eps -> MEMORY_TYPE =\n");} | epsilon
                ;
mem_size_eps : MEM_SIZE   EQ  {fprintf(fout,"mem_size_eps -> MEM_SIZE = \n");} | epsilon
                ;

mem_func : GET_AVAILABLE_MEMORY  LP   RP  {fprintf(fout,"mem_func -> GET_AVAILABLE_MEMORY()\n");}; 

job_params :   LP job_id_eps expression  COMMA  flps_eps expression  COMMA  dead_eps expression  COMMA  mem_reqd_eps expression  COMMA  aff_eps var_affinity  RP  
               {fprintf(fout,"job_params -> (job_id_eps expression,flps_eps expression,dead_eps expression,mem_reqd_eps expression,aff_eps var_affinity)\n");}; 

job_id_eps : JOB_ID   EQ  {fprintf(fout,"job_id_eps -> JOB_ID =\n");} | epsilon
                ;
flps_eps : FLOPS_REQUIRED   EQ  {fprintf(fout,"flps_eps -> FLOPS_REQUIRED = \n");}
                | epsilon;
dead_eps : DEADLINE   EQ  {fprintf(fout,"dead_eps -> DEADLINE =\n");}
                | epsilon;
mem_reqd_eps : MEM_REQUIRED   EQ  {fprintf(fout,"mem_reqd_eps -> MEM_REQUIRED =\n");}
                | epsilon;
aff_eps : AFFINITY   EQ  {fprintf(fout,"aff_eps -> AFFINITY =\n");}
                | epsilon;
var_affinity :   LSQBRAC  FLOAT  RSQBRAC  {fprintf(fout,"var_affinity -> [FLOAT]\n");}
                |  LSQBRAC  FLOAT  COMMA  FLOAT  RSQBRAC  {fprintf(fout,"var_affinity -> [FLOAT,FLOAT]\n");}
                |  LSQBRAC  FLOAT  COMMA  FLOAT  COMMA  FLOAT  RSQBRAC  {fprintf(fout,"var_affinity -> [FLOAT,FLOAT,FLOAT]\n");}
                |  LSQBRAC  FLOAT  COMMA  FLOAT  COMMA  FLOAT  COMMA  FLOAT  RSQBRAC   {fprintf(fout,"var_affinity -> [FLOAT,FLOAT,FLOAT,FLOAT]\n");}; 

job_func : GET_MEMORY  LP   RP  {fprintf(fout,"job_func -> GET_MEMORY()\n");}; 

clus_params :   LP proc_list_eps var_list_clus  COMMA  top_eps expression  COMMA  link_bw_eps expression  COMMA  link_cap_eps expression params_opt_aid_name  RP  
                {fprintf(fout,"clus_params -> (proc_list_eps var_list_clus,top_eps expression,link_bw_eps expression,link_cap_eps expression params_opt_aid_name)\n");}; 

clus_func : SUBMIT_CLUS_JOBS  LP list_call_params  RP {fprintf(fout,"clus_func -> SUBMIT_CLUS_JOBS(list_call_params)\n");}
                |START_CLUS_SCHEDULER  LP   RP {fprintf(fout,"clus_func -> START_CLUS_SCHEDULER()\n");}
                |STOP_CLUS_SCHEDULER  LP   RP {fprintf(fout,"clus_func -> STOP_CLUS_SCHEDULER()\n");}
                |USE_CLUS_SCHEDULER  LP expression  RP {fprintf(fout,"clus_func -> USE_CLUS_SCHEDULER(expression)\n");}
                |USE_LIST_SCHEDULER  LP expression  RP  {fprintf(fout,"clus_func -> USE_LIST_SCHEDULER(expression)\n");}; 

proc_list_eps : PROCESSORS   EQ  {fprintf(fout,"proc_list_eps -> PROCESSORS =\n");} | epsilon
                ;
top_eps : TOPOLOGY   EQ  {fprintf(fout,"top_eps -> TOPOLOGY = \n");}| epsilon
                ;
link_bw_eps : LINK_BANDWIDTH   EQ  {fprintf(fout,"link_bw_eps -> LINK_BANDWIDTH = \n");}
                | epsilon;
link_cap_eps : LINK_CAPACITY   EQ  {fprintf(fout,"link_cap_eps -> LINK_CAPACITY =\n");}
                | epsilon;
var_list_clus : LSQBRAC list_call_params RSQBRAC{fprintf(fout,"var_list_clus -> list_call_params\n");}
                | epsilon; 



sch_algo_params : LP code_ptr_eps expression COMMA aff_eps var_affinity COMMA params_opt_name RP 
            {fprintf(fout," sch_algo_params -> LP code_ptr_eps expression COMMA aff_eps var_affinity COMMA params_opt_name RP\n");} 
;

code_ptr_eps : CODE_PTR  {fprintf(fout,"code_ptr_eps -> CODE_PTR\n");} | epsilon
        ;

list_sch_params : LP algo_list_eps LSQBRAC list_call_params RSQBRAC params_opt_name RP  
    {fprintf(fout,"list_sch_params -> LP algo_list_eps list_call_params params_opt_name RP\n");} | epsilon
;

algo_list_eps : LIST_ALGOS EQ  {fprintf(fout,"algo_list_eps -> LIST_ALGOS EQ\n");} | epsilon
        ;

list_sch_func : ADD_ALGORITHM LP expression RP {fprintf(fout,"list_sch_func -> ADD_ALGORITHM LP expression RP\n");} 
;

%%


int main (void) 
{
        fout = fopen("parser.txt","w");
        func_table = NULL;
        symb_table = NULL;
        cur_scope=0;
	return yyparse ();
}

void yyerror (char *s) {fprintf (stderr,  "LINE:%d %s \n",mylineno,s);} 
