yacc -dtv comp.c
flex comp_ass2.l
gcc -w y.tab.c lex.yy.c
