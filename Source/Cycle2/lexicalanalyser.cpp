#include<iostream>
#include<string.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	ifstream input("input.txt");
	char c;
	vector<int> Numbers;
	vector<char> Special;
	vector<string> Op;
	vector<string> Key;
	vector<string> Id;
	vector<string> Lit;
	string str="";
	string str1="";

	while(input.get(c))
	{
		if(isdigit(c))
		{
			int n = c-48;
			input.get(c);
			while(isdigit(c))
			{
				n = n*10 + (c-48);
				input.get(c);
			}
			Numbers.push_back(n);
		}
		if(isalpha(c))
		{
			char st[10];
			int j = 0;
			st[j++] = c;
			input.get(c);
			while(c == '_' || c == '$' || isalpha(c) || isdigit(c))
			{
				st[j++] = c;
				input.get(c);
			}
			input.unget();
			st[j++] = '\0';
			if(strcmp("void",st) == 0 || strcmp("int",st) == 0 || strcmp("for",st) == 0)
				Key.push_back(st);
			else
				Id.push_back(st);
		}
		
		else if(c == '=' || c == '*' || c =='&')
		{
			str="";
			Op.push_back(str+c);
		}
		else if(c == '+')
		{
			str="";
			input.get(c);
			str+=c;
			if(c == '+')
			{
				str+=c;
				Op.push_back(str);
			}
			else
			{
				input.unget();
				Op.push_back(str);
			}
		}
		else if( c == '<')
		{
			str="";
			input.get(c);
			str+=c;
			if(c == '=')
			{
				str+=c;
				
			}
			else
			{
				input.unget();
			}
			Op.push_back(str);
		}

		else if(c == '"')
		{
			str1="";
			str1+=c;
			while(input.get(c))
			{
				str1+=c;
				if(c == '"')
					break;
			}
			Lit.push_back(str1);
			str1="";

		}
		else if(c == ' ' || c == '\t' || c == '\n')
		{
			continue;
		}
		else
			Special.push_back(c);
	}
	cout<<endl;
	cout<<"Numbers : "<<endl;
	for(int i=0; i<Numbers.size(); i++)
	{
		cout<<Numbers[i]<<endl;
	}
	cout<<endl<<"Keywords : "<<endl;
	for(int i=0; i<Key.size(); i++)
	{
		cout<<Key[i]<<endl;
	}
	cout<<endl<<"Literals : "<<endl;
	for(int i=0; i<Lit.size(); i++)
	{
		cout<<Lit[i]<<endl;
	}
	cout<<endl<<"Identifiers : "<<endl;
	for(int i=0; i<Id.size(); i++)
	{
		cout<<Id[i]<<endl;
	}
	cout<<endl<<"Special symbols : "<<endl;
	for(int i=0; i<Special.size(); i++)
	{
		cout<<Special[i]<<endl;
	}
	cout<<endl<<"Operators : "<<endl;
	for(int i=0; i<Op.size(); i++)
	{
		cout<<Op[i]<<endl;
	}
	return 0;
}