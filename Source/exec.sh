#!/bin/bash
yacc -d mysample.y
lex mysample.l
g++ lex.yy.c y.tab.c
./a.out < inp.i >machine_code.txt
