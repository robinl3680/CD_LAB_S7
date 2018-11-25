%{
	#include<stdio.h>
	#include<iostream>
	#include<string>
	#include<string.h>
	#include<bits/stdc++.h>
	using namespace std;
	int yylex();
	void yyerror(const char *s);

	int offset = 0;

	vector<string> machine_code;

	struct sym_tab
	{
		char *name;
		int offset;
		sym_tab *next;
	};

	stack<int> post;



	sym_tab *head;
	sym_tab *get(char *name);
	void put(char *name);
	void display();
	void machine_code_print();
%}


%union{
	char *id;
	int val;
}

%token PROG INT BEG READ IF THEN ELSE EIF WHILE DO EWHILE WRITE END DOT COMMA SEMICOLON EQUAL NUM IDENTI
%type <val> expression NUM
%type <id> IDENTI
%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%left '<' '>'
%start Pro

%%

Pro : PROG declarations 				{machine_code.push_back("res " + to_string(offset));}
	  BEG command_sequence END
 										{machine_code.push_back("halt 0"); }
	|
	;

declarations : INT id_sequence IDENTI {cout << "\n$3 : " << yylval.id << endl; put($3);}
							   DOT 
	|
	;
id_sequence : id_sequence IDENTI {cout << "\n$2 : " << yylval.id << endl; put($2);}
							COMMA 
	|
	;
command_sequence : command_sequence command SEMICOLON
	|
	;
command : IDENTI EQUAL expression {machine_code.push_back("store " + to_string(get($1)->offset));}
	|
		IF expression THEN 	{
								machine_code.push_back("jmp_false ");
								post.push(machine_code.size()-1);

							}
	command_sequence ELSE {

								machine_code.push_back("goto ");
								int temp = post.top();
								post.pop();
								post.push(machine_code.size()-1);
								machine_code[temp].append(to_string(machine_code.size()+1));


							} 
	command_sequence EIF	
							{
								int temp = post.top();
								post.pop();
								machine_code[temp].append(to_string(machine_code.size()+1));
							}
	|
	WHILE
							{
								post.push(machine_code.size()-1);
							}
	 expression DO 
							{
							machine_code.push_back("jmp_false ");
							post.push(machine_code.size()-1);
							}
	command_sequence	
							{
							int temp1 = post.top();
							post.pop();
							int l1 = post.top();
							post.pop();
							machine_code.push_back("goto " + to_string(l1+1));
							machine_code[temp1].append(to_string(machine_code.size()+1));
							}
	EWHILE
	|
	READ IDENTI	{machine_code.push_back("read " + to_string(get($2)->offset));}
	|
	WRITE expression	{machine_code.push_back("write 0");}
	;
expression : NUM	{$$ = $1; machine_code.push_back("load_int " + to_string($1));}
	|
	IDENTI	{$$ = get($1)->offset; machine_code.push_back("load_var " + to_string(get($1)->offset));}
	|
	'(' expression ')'	{$$ = $2;}
	|
	expression '+' expression	{$$ = $1 + $3; machine_code.push_back("add 0");}
	|
	expression '-' expression	{$$ = $1 - $3; machine_code.push_back("sub 0");}
	|
	expression '*' expression	{$$ = $1 * $3; machine_code.push_back("mul 0");}
	|
	expression '<' expression	{$$ = $1 < $3; machine_code.push_back("lt 0");}
	|
	expression '/' expression	{$$ = $1 / $3; machine_code.push_back("div 0");}
	|
	expression '>' expression	{$$ = $1 > $3; machine_code.push_back("gt 0");}
	;

%%

sym_tab *get(char *name)
{
	sym_tab *temp = head;
	while(temp != NULL)
	{
		if(strcmp(temp -> name,name) == 0)
			return temp;
		temp = temp -> next;
	}
	if(temp == NULL)
	{

	}
	return NULL;
}

void put(char *name)
{
	sym_tab *temp = get(name);
	if(temp == NULL)
	{
		temp = new sym_tab;
		temp -> name = name;
		temp -> offset = offset;
		offset++;
		temp -> next = head;
		head = temp;

	}
	else
	{
		cout << "Already exists" << endl;
		return;
	}

}

void display()
{
	sym_tab *temp = head;
	while(temp != NULL)
	{
		if(strcmp(temp -> name,"end") != 0)
		{
			cout << "\nTemp Name : " << temp->name << "\nOffset : " << temp->offset << endl;
		}
		temp = temp -> next;
	}
}


void machine_code_print()
{
	for(auto it : machine_code)
		cout << it << endl;
}


int main()
{
	head = new sym_tab;
    head->name = "end";
    head->offset = -1;
    head->next = NULL;
	yyparse();
	cout << endl;
	cout << "Success parsed " << endl;
	display();
	machine_code_print();
	return 0;

}
void yyerror(const char *s)
{
	cout << "error is " << s << endl;
	exit(0);
}


