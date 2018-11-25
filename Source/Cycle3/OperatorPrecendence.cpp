#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	int nterm;
	ifstream in("input.txt");
	cout<<"Enter number of terminals including $"<<endl;
	in>>nterm;
	vector<vector<char> >precedence = vector<vector<char>>(nterm,vector<char>(nterm));
	string str;
	char c;
	cout<<"Enter your terminals appended with $"<<endl;
	in>>str;
	cout<<"Enter your precedence "<<endl;
	for(int i=0; i<str.length(); i++)
	{
		cout<<str[i]<<" ";
		for(int j=0; j<str.length(); j++)
		{
			cout<<str[j]<<" ";
			in>>c;
			precedence[i][j]=c;
		}
		cout<<endl;
	}
	cout<<"precedence are "<<endl;
	for(int i=0; i<str.length(); i++)
	{
		cout<<str[i]<<" ";
		for(int j=0; j<str.length(); j++)
		{
			cout<<str[j]<<" ";
			cout<<precedence[i][j]<<"\t";
		}
		cout<<endl;
	}
	char st[20]={' '};
	int top=0;
	st[top]='$';
	string rd;
	int row,col;
	cout<<"Enter input string "<<endl;
	cin>>rd;
	cout<<st<<"\t"<<rd<<"\t";
	for(int i=0; i<rd.length();)
	{
		for(int j=0; j<nterm; j++)
		{
			if(st[top] == str[j])
			{
				row = j;
				// cout<<rd[i]<<" row "<<j<<endl;
			}
			if(rd[i] == str[j])
			{
				col = j;
				// cout<<rd[i]<<" Col "<<j<<endl;
			}
		}
		if(st[top]=='$' && rd[i] == '$')
		{
			cout<<"String accepted"<<endl;
			break;
		}
		else if(precedence[row][col]=='<' || precedence[row][col]=='=')
		{
			st[++top] = precedence[row][col];
			st[++top] = rd[i];
			cout<<"Shift "<<rd[i]<<endl;
			rd[i]=' ';
			i++;
		}
		else
		{
			if(precedence[row][col] == '>')
			{
				while(st[top] != '<')
				{
					
					--top;
				}

				top = top-1;

				cout<<"Reduce "<<endl;
			}
			else
			{
				cout<<"String not accepted"<<endl;
				break;
			}
		}
		cout<<st<<"\t"<<rd<<"\t";
		if(rd[i]=='\0' && st[top] !='$')
			cout<<"Not accepted"<<endl;
	}
	// cout<<st<<"\t"<<rd<<"\t";
	cout<<endl;
	return 0;
}