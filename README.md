# CD_LAB_S7
Now just incuding the files for an interpreter that we made for a given input grammar.
The grammar is


Pro : PROG declarations
	  BEG command_sequence END

	|
	;

declarations : INT id_sequence IDENTI
							   DOT 
	|
	;
id_sequence : id_sequence IDENTI 
							COMMA 
	|
	;
command_sequence : command_sequence command SEMICOLON
	|
	;
command : IDENTI EQUAL expression 
	|
		IF expression THEN 
	command_sequence ELSE 
	command_sequence EIF	
	|
	WHILE
							
	 expression DO 
							
	command_sequence	
							
	EWHILE
	|
	READ IDENTI	
	|
	WRITE expression	
	;
expression : NUM	
  |
	IDENTI
	|
	'(' expression ')'
	|
	expression '+' expression	
	|
	expression '-' expression	
	|
	expression '*' expression	
	|
	expression '<' expression	
	|
	expression '/' expression	
	|
	expression '>' expression	
	;
  
  
  where Terminals are represented by capital letters and non terminals are represented by small letters.
