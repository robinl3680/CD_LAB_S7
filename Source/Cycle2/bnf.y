%{
	#include<stdio.h>
	#include<stdlib.h>
	int n=1;
	node *x;
	void yyerror();
	struct node* getnode();
	extern char* yytext;
	int yylex();
%}
%start stmt
%token ID NUM
%left '+' '-'
%left '/' '*'
%%
stmt : expr {x=getnode(); x->dt=$1; x->left=NULL; x->right=NULL; $$=x;}
	| ID '=' expr {x=getnode(); x->dt='='; x->left=$1; x->right=$3; $$=x};
;
expr : expr '+' expr {x=getnode(); x->dt='+'; x->left=$1; x->right=$3; $$=x;}
	| expr '-' expr {x=getnode(); x->dt='-'; x->left=$1; x->right=$3; $$=x;}
	| expr '*' expr {x=getnode(); x->dt='*'; x->left=$1; x->right=$3; $$=x;}
	| expr '/' expr {x=getnode(); x->dt='/'; x->left=$1; x->right=$3; $$=x;}
	| ID {x=getnode(); x->dt=yytext; x->left=NULL; x->right=NULL; $$=x;}
	| NUM {x=getnode(); x->dt=yytext; x->left=NULL; x->right=NULL; $$=x;}
;
%%
struct node
	{
	char dt;
	struct node *right;
	struct node *left;
	};
node *getnode()
{
	node *d=(struct node*)malloc(sizeof(struct node));
	d->dt='c';
	d->left=NULL;
	d->right=NULL;
	return d;

}
void inorder(node *x)
{
	inorder(x->left);
	printf("%c ",x->dt);
	inorder(x->right);
}
void main()
{
	while(n)
	{
	printf("Enter Expression \n ");
	yyparse();
	inorder(x);
	printf("Valid expression\n");
	}
}
void yyerror()
{
	printf("Invalid expression\n");
	exit(0);
}
