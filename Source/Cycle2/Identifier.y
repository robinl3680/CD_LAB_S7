%{
	#include<stdlib.h>
	#include<stdio.h>
	void yyerror();
	int n=1;
%}
%start stmt
%token ID
%%
stmt : expr
;
expr : ID
;
%%
void main()
{
	while(n)
	{
	printf("Enter identifier\n");
	yyparse();
	printf("Valid\n");
	}
}
void yyerror()
{
	printf("Invalid\n");
	exit(0);
}