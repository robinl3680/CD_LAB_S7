%{
	#include<stdio.h>
	#include<stdlib.h>
	void yyerror();
	int sym[52];
	int valu(char c);
	void upda(char s,int val);

%}
%union{int n; char id;}
%start stmt
%token print
%token end
%token <n> num
%token <id> identifier
%type <n> stmt exp term
%type <idnt> assign
%%
stmt : assign ';' {;}
	| end ';' {exit(EXIT_SUCCESS);}
	| print exp ';' {printf("Value is : %d\n",$2);}
	| stmt assign ';' {;}
	| stmt print exp ';' {printf("Value is : %d\n",$3);}
	| stmt end ';' {exit(EXIT_SUCCESS);};
assign : identifier '=' exp {upda($1,$3);}
;
exp	: term	{$$=$1;}
	| exp '+' term	{$$=$1+$3;}
	| exp '-' term	{$$=$1-$3;}
	| exp '*' term	{$$=$1*$3;}
	| exp '/' term	{$$=$1/$3;};
term : identifier {$$=valu($1);}
	| num	{$$=$1;};
%%

int idx(char s)
{
	int i=-1;
	if(islower(s))
	{
	i=s-'a' + 26;
	}
	else if(isupper(s))
	{
	i=s-'A';
	}
	return i;
}
int valu(char s)
{
	int i=idx(s);
	return sym[i];
}
void upda(char s,int val)
{
	int i=idx(s);
	sym[i]=val;
}
int main(void)
{
	int j;
	for(j=0;j<52;j++)
		sym[j]=0;
	return yyparse();	
}
void yyerror()
{
	
}