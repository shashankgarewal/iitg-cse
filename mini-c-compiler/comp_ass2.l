%{
    #include <stdio.h>
    #include "y.tab.h"
    int mylineno = 1;
%}

%%
[\n]                {mylineno++;}
[ \t]             {;}
,               {return COMMA;}
\;            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return SEMI;}
\+\+            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return PLUSPLUS       ;}
\+            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return PLUS;}
\*            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return TIMES;}
\(            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return LP	   ;}
\)            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return RP  		   ;}
--            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return MINUSMINUS     ;}
-            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return MINUS ;}
\/            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return DIV   ;}
!=            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return NEQ   ;}
!            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return NOT   ;}
\<=            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return LEQ    ;}
\<            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return LE     ;}
\>=            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return GRQ    ;}
\>            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return GR     ;}
==            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return EEQ    ;}
=            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return EQ     ;}
if            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return IF     ;}
\{            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return OPEN_CURL      ;}
\}            {    /*printf("Cur token %0.*s\n",yyleng,yytext);  */  return CLOSE_CURL     ;}
int				{return INT_TYPE;}
print 			{return PRINT;}
endl 			{return ENDL;}
float 			{return FLOAT_TYPE;}
char  			{return CHAR_TYPE;}
else            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return ELSE   ;}
main            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return MAIN   ;}
while            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return WHILE  ;}
do            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return DO     ;}
switch            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return SWITCH ;}
case            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return CASE    ;}
default            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return DEFAULT;}
for            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return FOR    ;}
break            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return BREAK  ;}
continue            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return CONTINUE       ;}
\]            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return RSQBRAC;}
\[            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return LSQBRAC;}
\.            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return DOT;}
:            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return COLON  ;}
return            {    /*printf("Cur token %0.*s\n",yyleng,yytext);      */      return RETURN;}
[_a-zA-Z][0-9a-zA-Z_]*     {return ID;}
[0-9]+(\.[0-9]+) 		{   return FLOAT;}
[0-9]+ 					{  return INT;}
\'[^\']\'				{ return CHAR;}
\"[^\"]*\"              { return STRING; }
\&\&					{return AND_AND;}
\&					{return AMP;}
\|\|					{return OR_OR;}
.                   {/*printf("Unexpected Cur token %0.*s ",yyleng,yytext);*/}
%%

int yywrap (void) {return 1;}