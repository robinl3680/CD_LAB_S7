#include<iostream>
#include<bits/stdc++.h>
using namespace std;
char prod[10][10];
char arr2[10];
int x=0;
string non;
vector<string> first_all;

void find_follow(char ch,int n);
void find_first2(char ch,int n);
void Array_Manipulation(char ch);

int find_id(char ch)
{
	for(int i=0;i<non.length();i++)
	{
		if(non[i]==ch)
			return i;
	}
	return -1;
}
void manipulate(char arr[],char ch)
{
	int i;
	for(i=0; arr[i]!='\0';i++)
	{
		if(arr[i]==ch)
			return;
	}
	arr[i]=ch;
	i+=1;
	arr[i]='\0';
}

void find_first(char *arr,char ch,int n)
{
	char temp[10];
	temp[0]='\0';
	arr[0]='\0';
	if(!isupper(ch))
	{
		manipulate(arr,ch);
		return;
	}
	else
	{
		for(int i=0;i<n;i++)
		{
			if(prod[i][0]==ch)
			{
				if(prod[i][2]=='$')
				{
					manipulate(arr,'$');
				}
				else
				{
					int j=2;
					while(prod[i][j]!='\0')
					{
						int x=0;
						find_first(temp,prod[i][j],n);
						for(int k=0; temp[k]!='\0'; k++)
						{
							manipulate(arr,temp[k]);
						}
						for(int k=0; temp[k]!='\0'; k++)
						{
							if(temp[k]=='$')
							{
								x=1;
								break;
							}
						}
						if(!x)
							break;
						j++;
					}
				}
			}
		}
	}
}

// string find_follow(char c,int n)
// {
// 	string st=" ";
// 	if(prod[0][0]=c)
// 		st+='$';
// 	string s=prod[0];
// 	int len=s.length();
// 	for(int i=0;i<n;i++)
// 	{
// 		for(int j=2;j<len;j++)
// 		{
// 			if(prod[i][j]==c)
// 				// cout<<prod[i][j]<<endl;
// 			{
// 				if(prod[i][j+1] !='\0')
// 				{
// 					int f = find_id(prod[i][j+1]);
// 					if(f>=0)
// 					{
// 						st+=first_all[f];
// 						// cout<<st<<" "<<endl;
// 						for(int k=0;k<first_all[f].size();k++)
// 						{
// 							if(first_all[f][k]=='$')
// 							{
// 								// st.pop_back();
// 								st+=find_follow(prod[i][0],n);
// 							}
// 						}
// 					}
// 					else
// 					{
// 						char arr[10];
// 						find_first(arr,c,n);
// 						st+=arr;
// 					}

// 				}
// 				if(prod[i][j+1]=='\0' && c!=prod[i][0])
// 					st+=find_follow(prod[i][0],n);
// 			}
// 		}
// 	}
// 	return st;
// }

int main()
{

	int n,noterm;
	ifstream in("inp.txt");
	
	char t='y';
	char arr[10];
	in>>n;
	in>>noterm;
	in>>non;
	for(int i=0;i<n;i++)
	{
		in>>prod[i];
	}
	for(int i=0;i<non.length();i++)
	{
		char tp[10];
		find_first(tp,non[i],n);
		first_all.push_back(tp);
	}

	// while(t=='y')
	// {

	// 	int ch;
	// 	cout<<"Enter choice 1-first 2-follow "<<endl;
	// 	cin>>ch;
	// 	switch(ch)
	// 	{
	// 		case 1:
	// 			{
	// 				char c;
	// 				cout<<"Enter symbol"<<endl;
	// 				cin>>c;
	// 				int fnd=find_id(c);
	// 				if(fnd>=0)
	// 					cout<<first_all[fnd]<<endl;
	// 				else
	// 					{
	// 						find_first(arr,c,n);
	// 								cout<<"{ ";
	// 								for(int i=0;arr[i]!='\0';i++)
	// 								{
	// 									cout<<arr[i]<<"";
	// 								}
	// 								cout<<" }"<<endl;
	// 					}
	// 				break;
	// 			}
	// 		case 2:
	// 		{
	// 		char c;
	// 		x = 0;
 //            cout<<"Enter symbol "<<endl;
 //            cin>>c;
 //            find_follow(c,n);
 //            cout<<"Follow "<<endl;
 //            for(int count = 0; count < x; count++)
	//             {
	//                   cout<<arr2[count];
	//             }
 //            cout<<endl;
	// 		}
	// 		default:break;
	// 	}
	// 	cout<<"Do you want to continue y or n"<<endl;
	// 	cin>>t;
	// }


	for(int i=0;i<non.size();i++)
	{
		cout<<non[i]<<" First "<<endl;
		find_first(arr,non[i],n);
		find_follow(non[i],n);
		for(int j=0;arr[j]!='\0';j++)
		{

			cout<<arr[j]<<" ";
		}	
		cout<<endl;
		cout<<non[i]<<" Follow "<<endl;
		for(int j=0;j<x;j++)
		{
			if(arr2[j]!=' ')
				cout<<arr2[j]<<" ";
		}	
		for(int k=0;k<10;k++)
		{
			arr2[k]=' ';
		}
		cout<<endl;

	}

}


void find_follow(char ch,int n)
{
      int i, j;
      // cout<<"hai "<<endl;
      string st=prod[0];
      int leng=st.length();

      if(prod[0][0] == ch)
      {
            Array_Manipulation('$');
            // cout<<"hai strt "<<endl;

      }
      for(i = 0; i < n; i++)
      {
            for(j = 2; j < leng; j++)
            {
                  if(prod[i][j] == ch)
                  {
                        if(prod[i][j + 1] != '\0')
                        {
                              find_first2(prod[i][j + 1],n);
                              // cout<<"hai "<<prod[i][j+1]<<endl;
                        }
                        if(prod[i][j + 1] == '\0' && ch != prod[i][0])
                        {     
                        	  // cout<<"hai "<<prod[i][0]<<endl;				
                              find_follow(prod[i][0],n);

                        }
                  }
            }
      }
}
 
void find_first2(char ch,int n)
{
      int i, k;
      if(!(isupper(ch)))
      {
            Array_Manipulation(ch);
      }
      for(k = 0; k < n; k++)
      {
            if(prod[k][0] == ch)
            {
                  if(prod[k][2] == '$') 
                  {
                        find_follow(prod[i][0],n);
                  }
                  else if(islower(prod[k][2]))
                  {
                        Array_Manipulation(prod[k][2]);
                  }
                  else 
                  {
                        find_first2(prod[k][2],n);
                  }
            }
      }
}
 
void Array_Manipulation(char ch)
{
      int count;
      for(count = 0; count <= x; count++)
      {
            if(arr2[count] == ch)
            {
                  return;
            }
      }
      arr2[x++] = ch;
}