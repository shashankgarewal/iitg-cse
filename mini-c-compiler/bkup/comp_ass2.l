%{
    #include <stdio.h>
    #include "y.tab.h"
    int mylineno = 1;
%}

%%
[\n]                {mylineno++;}
[ \t]             {;}
,               {return COMMA;}
\;            {printf("Cur token %0.*s\n",yyleng,yytext);return SEMI;}
\+\+            {printf("Cur token %0.*s\n",yyleng,yytext);return PLUSPLUS       ;}
\+            {printf("Cur token %0.*s\n",yyleng,yytext);return PLUS;}
\*            {printf("Cur token %0.*s\n",yyleng,yytext);return TIMES;}
\(            {printf("Cur token %0.*s\n",yyleng,yytext);return LP	   ;}
\)            {printf("Cur token %0.*s\n",yyleng,yytext);return RP  		   ;}
--            {printf("Cur token %0.*s\n",yyleng,yytext);return MINUSMINUS     ;}
-            {printf("Cur token %0.*s\n",yyleng,yytext);return MINUS ;}
\/            {printf("Cur token %0.*s\n",yyleng,yytext);return DIV   ;}
!=            {printf("Cur token %0.*s\n",yyleng,yytext);return NEQ   ;}
!            {printf("Cur token %0.*s\n",yyleng,yytext);return NOT   ;}
\<=            {printf("Cur token %0.*s\n",yyleng,yytext);return LEQ    ;}
\<            {printf("Cur token %0.*s\n",yyleng,yytext);return LE     ;}
\>=            {printf("Cur token %0.*s\n",yyleng,yytext);return GRQ    ;}
\>            {printf("Cur token %0.*s\n",yyleng,yytext);return GR     ;}
==            {printf("Cur token %0.*s\n",yyleng,yytext);return EEQ    ;}
=            {printf("Cur token %0.*s\n",yyleng,yytext);return EQ     ;}
if            {printf("Cur token %0.*s\n",yyleng,yytext);return IF     ;}
\{            {printf("Cur token %0.*s\n",yyleng,yytext);return OPEN_CURL      ;}
\}            {printf("Cur token %0.*s\n",yyleng,yytext);return CLOSE_CURL     ;}
int				{return INT_TYPE;}
float 			{return FLOAT_TYPE;}
char  			{return CHAR_TYPE;}


PROCESSOR_TYPE {return PROCESSOR_TYPE;}
LINK_TYPE {return LINK_TYPE;} 
MEM_TYPE  {return MEM_TYPE;}
JOB_TYPE  {return JOB_TYPE;}
CLUSTER_TYPE  {return CLUSTER_TYPE;}
SCH_ALGO_TYPE  {return SCH_ALGO_TYPE;}
LIST_SCH_TYPE {return LIST_SCH_TYPE;}


else            {printf("Cur token %0.*s\n",yyleng,yytext);return ELSE   ;}
main            {printf("Cur token %0.*s\n",yyleng,yytext);return MAIN   ;}
while            {printf("Cur token %0.*s\n",yyleng,yytext);return WHILE  ;}
do            {printf("Cur token %0.*s\n",yyleng,yytext);return DO     ;}
switch            {printf("Cur token %0.*s\n",yyleng,yytext);return SWITCH ;}
case            {printf("Cur token %0.*s\n",yyleng,yytext);return CASE    ;}
default            {printf("Cur token %0.*s\n",yyleng,yytext);return DEFAULT;}
for            {printf("Cur token %0.*s\n",yyleng,yytext);return FOR    ;}
break            {printf("Cur token %0.*s\n",yyleng,yytext);return BREAK  ;}
continue            {printf("Cur token %0.*s\n",yyleng,yytext);return CONTINUE       ;}
\]            {printf("Cur token %0.*s\n",yyleng,yytext);return RSQBRAC;}
\[            {printf("Cur token %0.*s\n",yyleng,yytext);return LSQBRAC;}
\.            {printf("Cur token %0.*s\n",yyleng,yytext);return DOT;}
:            {printf("Cur token %0.*s\n",yyleng,yytext);return COLON  ;}
return            {printf("Cur token %0.*s\n",yyleng,yytext);return printf("Cur token %0.*s\n",yyleng,yytext);RETURN;}
wait            {return WAIT;}
name            {printf("Cur token %0.*s\n",yyleng,yytext);return NAME;}
Processor            {printf("Cur token %0.*s\n",yyleng,yytext);return PROCESSOR      ;}
isa            {printf("Cur token %0.*s\n",yyleng,yytext);return ISA    ;}
clock_speed            {printf("Cur token %0.*s\n",yyleng,yytext);return CLOCK_SPEED    ;}
l1_memory            {printf("Cur token %0.*s\n",yyleng,yytext);return L1_MEMORY      ;}
l2_memory            {printf("Cur token %0.*s\n",yyleng,yytext);return L2_MEMORY      ;}
is_running            {printf("Cur token %0.*s\n",yyleng,yytext);return IS_RUNNING     ;}
submit_jobs           {printf("Cur token %0.*s\n",yyleng,yytext);return SUBMIT_JOBS    ;}
submit_clus_jobs           {printf("Cur token %0.*s\n",yyleng,yytext);return SUBMIT_CLUS_JOBS    ;}
get_clock_speed            {printf("Cur token %0.*s\n",yyleng,yytext);return GET_CLOCK_SPEED;}
run            {printf("Cur token %0.*s\n",yyleng,yytext);return RUN    ;}
discard_jobs            {printf("Cur token %0.*s\n",yyleng,yytext);return DISCARD_JOBS    ;}
Link            {printf("Cur token %0.*s\n",yyleng,yytext);return LINK   ;}
start_point           {printf("Cur token %0.*s\n",yyleng,yytext);return START_POINT    ;}
end_point            {printf("Cur token %0.*s\n",yyleng,yytext);return END_POINT      ;}
bandwidth            {printf("Cur token %0.*s\n",yyleng,yytext);return BANDWIDTH      ;}
channel_capacity            {printf("Cur token %0.*s\n",yyleng,yytext);return CHANNEL_CAPACITY   ;}
Memory            {printf("Cur token %0.*s\n",yyleng,yytext);return MEMORY ;}
memory_type            {printf("Cur token %0.*s\n",yyleng,yytext);return MEMORY_TYPE    ;}
memory_size            {printf("Cur token %0.*s\n",yyleng,yytext);return MEM_SIZE       ;}
get_available_memory            {printf("Cur token %0.*s\n",yyleng,yytext);return GET_AVAILABLE_MEMORY   ;}
flops_required            {printf("Cur token %0.*s\n",yyleng,yytext);return FLOPS_REQUIRED   ;}
list_algos            {printf("Cur token %0.*s\n",yyleng,yytext);return LIST_ALGOS   ;}
sch_id            {printf("Cur token %0.*s\n",yyleng,yytext);return SCH_ID   ;}
Job            {printf("Cur token %0.*s\n",yyleng,yytext);return JOB    ;}
job_id            {printf("Cur token %0.*s\n",yyleng,yytext);return JOB_ID ;}
deadline            {printf("Cur token %0.*s\n",yyleng,yytext);return DEADLINE       ;}
mem_required            {printf("Cur token %0.*s\n",yyleng,yytext);return MEM_REQUIRED   ;}
get_memory            {printf("Cur token %0.*s\n",yyleng,yytext);return GET_MEMORY   ;}
affinity            {printf("Cur token %0.*s\n",yyleng,yytext);return AFFINITY       ;}
Cluster            {printf("Cur token %0.*s\n",yyleng,yytext);return CLUSTER;}
processors            {printf("Cur token %0.*s\n",yyleng,yytext);return PROCESSORS     ;}
topology            {printf("Cur token %0.*s\n",yyleng,yytext);return TOPOLOGY       ;}
link_bandwidth            {printf("Cur token %0.*s\n",yyleng,yytext);return LINK_BANDWIDTH ;}
link_capacity            {printf("Cur token %0.*s\n",yyleng,yytext);return LINK_CAPACITY  ;}
use_scheduler            {printf("Cur token %0.*s\n",yyleng,yytext);return USE_SCHEDULER  ;}
use_clus_scheduler            {printf("Cur token %0.*s\n",yyleng,yytext);return USE_CLUS_SCHEDULER  ;}
use_list_scheduler            {printf("Cur token %0.*s\n",yyleng,yytext);return USE_LIST_SCHEDULER    ;}
add_algorithm            {printf("Cur token %0.*s\n",yyleng,yytext);return ADD_ALGORITHM    ;}
Sch_algo            {printf("Cur token %0.*s\n",yyleng,yytext);return SCH_ALGO    ;}
List_sch            {printf("Cur token %0.*s\n",yyleng,yytext);return LIST_SCH    ;}
code_ptr            {printf("Cur token %0.*s\n",yyleng,yytext);return CODE_PTR    ;}
start_scheduler            {printf("Cur token %0.*s\n",yyleng,yytext);return START_SCHEDULER    ;}
start_clus_scheduler            {printf("Cur token %0.*s\n",yyleng,yytext);return START_CLUS_SCHEDULER    ;}
stop_scheduler            {printf("Cur token %0.*s\n",yyleng,yytext);return STOP_SCHEDULER    ;}
stop_clus_scheduler            {printf("Cur token %0.*s\n",yyleng,yytext);return STOP_CLUS_SCHEDULER    ;}
[_a-zA-Z][0-9a-zA-Z_]*     {printf("id Cur token %0.*s\n",yyleng,yytext);return ID;}
[0-9]+(\.[0-9]+) 		{printf("float Cur token %0.*s\n",yyleng,yytext);return FLOAT;}
[0-9]+ 					{printf("int Cur token %0.*s\n",yyleng,yytext);return INT;}
\'[^\']\'				{return CHAR;}
\"[^\"]*\"              {printf("string Cur token %0.*s\n",yyleng,yytext);return STRING; }
\&					{return AMP;}
.                   {printf("Unexpected Cur token %0.*s ",yyleng,yytext);}
%%

int yywrap (void) {return 1;}