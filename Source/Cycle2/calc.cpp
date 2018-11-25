#include<iostream>
#include "calc.h"
extern int yylex();
extern int yylineno;
extern char* yytext;
int main()
{
	int nt;
	nt = yylex();
	while(nt)
	{
		// printf("Token ID : %d value : %s \n", nt, yytext);
		if(nt==1)
				printf("Operator : %s \n",yytext);
		else if(nt==2)
				printf("Operator : %s \n",yytext);
		else if(nt==3)
				printf("Operator : %s \n", yytext);
		else if(nt==4)
				printf("Keyword : %s \n", yytext);
		else if(nt==5)
				printf("Operator : %s \n",yytext);
		else if(nt==6)
				printf("Special : %s \n", yytext);
		else if(nt==7)
				printf("Identifier : %s \n", yytext);
		else if(nt==8)
				printf("Number : %s \n", yytext);
		nt = yylex();
		printf("\n");
	}
	return 0;
}