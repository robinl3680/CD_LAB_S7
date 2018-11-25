#include<iostream>
#include<bits/stdc++.h>
using namespace std;
char l;
int err=0;
int i=0;
string in;
void E();
void F()
{
	if(in[i]=='(')
	{
		i++;
		E();
		if(in[i]==')')
			i++;
	}
	else if(isalpha(in[i]))
	{
		i++;
		while(isalpha(in[i]) || in[i]=='_')
			i++;
	}
	else
		err=1;
}

void Td()
{
	if(in[i]=='*')
	{
		i++;
		F();
		Td();	
	}
	else
		return;
}
void T()
{
	F();
	Td();
}
void Ed()
{
	if(in[i]=='+')
	{
		i++;
		T();
		Ed();
	}
	else
		return;
}


int main()

{
	cout<<"Enter string to parsed append with $"<<endl;
	cin>>in;
	E();
	if(in.length()==i && err==0)
	{
		cout<<"Accepted"<<endl;
	}
	else
	{
		cout<<"Rejected"<<endl;
	}
}
void E()
{
	T();
	Ed();
}
