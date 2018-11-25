%{
	#include<stdio.h>
	#include<string.h>
	#include "y.tab.h"
	int outputline = 1;
	
%}


%%
[\n] {outputline++;}
"+"	{return '+';}
"-" {return '-';}
"*" {return '*';}
"/" {return '/';}
"<" {return '<';}
">" {return '>';}
"." {return DOT;}
","	{return COMMA;}
":=" {return EQUAL;}
";" {return SEMICOLON;}
"prog" {return PROG;}
"begin" {return BEG;}
"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"endif" {return EIF;}
"integer" {return INT;}
"while" {return WHILE;}
"do" {return DO;}
"endwhile" {return EWHILE;}
"write" {return WRITE;}
"read" {return READ;}
"end" {return END;}
[a-zA-Z][_a-zA-Z0-9]* {yylval.id = strdup(yytext); return IDENTI;}
[1-9][0-9]* {yylval.val = atoi(yytext); return NUM;}

[ \t .] {;}
%%

int yywrap(void)
{
	return 1;
}