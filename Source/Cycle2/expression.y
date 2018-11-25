%{
	#include<stdio.h>
	#include<stdlib.h>
	int n=1;
	void yyerror();
%}
%start stmt
%token ID NUM
%left '+' '-'
%left '/' '*'
%%
stmt : expr
	| ID '=' expr
;
expr : expr '+' expr
	| expr '-' expr
	| expr '*' expr
	| expr '/' 
	| '(' expr ')'
	| ID
	| NUM
;
%%
void main()
{
	while(n)
	{
	printf("Enter Expression \n ");
	yyparse();
	printf("Valid expression\n");
	}
}
void yyerror()
{
	printf("Invalid expression\n");
	exit(0);
}
