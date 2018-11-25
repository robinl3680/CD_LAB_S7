%{ 
#include "calc.h"
%}
%%
; 	return SEMICOL;
"+"	return ADD;
"*"	return MUL;
-	return SUB;
=	return EQU;
"print"	return PRINT;
[a-zA-Z][_a-zA-Z0-9]*	return ID;
[1-9][0-9]*	return DIG;
[ \t\n]	;
%%
int yywrap(void)
{
return 1;
}
