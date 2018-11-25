#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class enfa
{
public:
	int num_states,num_alphabets;
	vector<int > final;
	vector<vector<vector<int>>> table;

	enfa(int n_s,int n_a)
	{
		num_states = n_s;
		num_alphabets = n_a;
		table = vector<vector<vector<int>>>(n_s,vector<vector<int>>(n_a+1));
	}

};
class nfa
{
public:
	int num_states,num_alphabets;
	vector<int> final;
	vector<vector<vector<int>>> table;

	nfa(int n_s,int n_a)
	{
		num_states=n_s;
		num_alphabets=n_a;
		table = vector<vector<vector<int>>>(n_s,vector<vector<int>>(n_a+1));
	}
};


bool check(int d,vector<int> &v)
{
	int f=1;
	for(int i=0;i<v.size();i++)
	{
		if(d==v[i])
		{
			return true;
		}
	}
	return false;
}

void printout(vector<int> v)
{
	for(int i=0;i<v.size();i++)
	{
		cout<<v[i]<<" ";
	}
}

vector<int> Find(vector<vector<vector<int>>> table,int k,int n_s)
{
	vector<int> v;
	v.push_back(k);
	for(int j=0;j<v.size();j++)
	{
		int k1=v[j];
			for(int i=0;i<table[k1][0].size();i++)
			{
				int t2=table[k1][0][i];
				if(!check(t2,v))
				{
					v.push_back(t2);
				}
			}
	}

	return v;
}

nfa convert(enfa a)
{
	int n_s=a.num_states;
	int n_a=a.num_alphabets;
	nfa obj(n_s,n_a);
	for(int i=0;i<a.num_states;i++)
	{
		cout<<"final strt"<<endl;
		vector<int> v=Find(a.table,i,a.num_states);
		for(int k=0;k<v.size();k++)
		{
			for(int j=0;j<a.final.size();j++)
			{
				if(v[k]==a.final[j])
				{
					obj.final.push_back(i);
					break;
				}
			}
		}
	}



	for(int i=0;i<a.num_states;i++)
	{
		vector<int > l=Find(a.table,i,a.num_states); //Get e closure
		for(int j=1;j<=a.num_alphabets;j++)
		{
			vector<int > f;
			for(int k=0;k<l.size();k++)
			{
				int st=l[k];
				// for(int m=0;m<a.table[st][j].size();m++)
				// {
				// 	int data=a.table[st][j][m];
				// 	f.push_back(data);
				// }
				vector<int> kk=a.table[st][j];
				f.insert(f.end(),kk.begin(),kk.end());

			}
			sort(f.begin(),f.end());
			unique(f.begin(),f.end());
			vector<int> temp;
			for(int p=0;p<f.size();p++)
			{
				int tempo=f[p];
				vector<int> nx = Find(a.table,tempo,a.num_states);
				temp.insert(temp.end(), nx.begin(), nx.end());
			}

			sort(temp.begin(), temp.end());
			unique(temp.begin(), temp.end());
			obj.table[i][j]=temp;

		}
	}
	return obj;
}

class dfa
{
public:
	int num_states, num_alphabets;
	vector<int> final;
	vector< vector<int> > table;
};


dfa nfatodfa(nfa a)
{
	cout << a.num_states << " " << a.num_alphabets << endl;
	dfa t;
	vector<set<int>> newstates;
	vector<bool> isfinal;
	set<int> st1={0};
	newstates.push_back(st1);
	t.table.push_back(vector<int>(a.num_alphabets+1,-1));
	if(check(0,a.final)){
		isfinal.push_back(1);
		t.final.push_back(0);
	}

	else
		isfinal.push_back(0);

	

	for(int i=0;i<newstates.size();i++)
	{	


		for(int j = 1 ; j <= a.num_alphabets ; j++){

			set<int> next;

			for(auto it : newstates[i])
				next.insert(a.table[it][j].begin(),a.table[it][j].end());

			int nextIndex = -1;

			for(int k = 0 ; k < newstates.size() ; k++){

				if(next == newstates[k]){
					nextIndex = k;
					break;
				}
			}

			if(nextIndex == -1){
				nextIndex = newstates.size();
				newstates.push_back(next);

				//to check whether new state is a final state
				bool flag = false;

				// cout << nextIndex << " : ";

				for(auto it : next){
					if(check(it,a.final)){
						flag = true;
						break;
					}
				}
				if(flag){
					isfinal.push_back(1);
					t.final.push_back(nextIndex);
				}
				else
				 	isfinal.push_back(0);

				t.table.push_back(vector<int>(a.num_alphabets+1,-1));

			}

			t.table[i][j] = nextIndex;

		}

	}


	t.num_states = t.table.size();
	t.num_alphabets = a.num_alphabets;


	return t;

}

    int fnd(vector<int> &p, int x, vector<int> &path)
        {
            path.push_back(x);
            if(x != p[x])
            {
                return fnd(p,p[x],path);
            }
            else 
            {
                return x;
            }
        }

          int pfind(int x,vector<int> &p)
        {
            if(x == p[x])
            {
                return x;
            }
            else
            {
                p[x] = pfind(p[x],p);
                return p[x];
            }
        }

dfa minimize(dfa d)
{
	vector<int> f = d.final;
	vector<vector<int> > lst = vector<vector<int> >(2);
	lst[0]=f;
	vector<int> nonfinal;
	for(int i=0;i<d.num_states;i++)
	{
		bool f=check(i,d.final);
		if(f==false)
		{
			nonfinal.push_back(i);
		}
	}
	lst[1]=nonfinal;


	// for(int i=0;i<lst.size();i++)
	// {
	// 	for(int j=0;j<lst[i].size();j++)
	// 	{
	// 		cout<<lst[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }

	int a[d.num_states][d.num_states];
	for(int i=0;i<d.num_states;i++)
	{
		for(int j=0;j<d.num_states;j++)
		{
			a[i][j]=0;
		}
	}

	int fl=1;

	for(int i=0;i<d.num_states;i++)
	{
		for(int j=i+1;j<d.num_states;j++)
		{
			if(check(i,d.final)&&!check(j,d.final) || check(j,d.final)&&!check(i,d.final))
			{
				a[i][j]=1;
			}
		}
	}
	while(fl==1)
	{
		fl=0;
		for(int i=0;i<d.num_states-2;i++)
		{
			for(int j=i+1;j<d.num_states-1;j++)
			{
				for(int k=1;k<=d.num_alphabets;k++)
				{ 
					int t1 = d.table[i][k];
					int t2 = d.table[j][k];
					if(t1 > t2)
					{
						int temp = t1;
						t1 = t2;
						t2 = temp;
					}
					if(a[i][j] == 0 && a[t1][t2] == 1)
					{
						a[i][j] = 1;
						fl=1;
						break;
					}
				}
			}
		}
	}


	// for(int i=0;i<d.num_states;i++)
	// {
	// 	for(int j=0;j<d.num_states;j++)
	// 	{
	// 		cout<<a[i][j]<<" ";	
	// 	}
	// 	cout<<endl;
	// }

	// vector<vector<int> > equi(d.num_states);
	// for(int i=0;i<d.num_states;i++)
	// {
	// 	equi[i].push_back(i);
	// }
	// for(int i=0;i<d.num_states;i++)
	// {
	// 	for(int j=i+1;j<d.num_states;j++)
	// 	{
	// 		if(a[i][j]==0)
	// 		{
	// 			equi[i].push_back(j);
	// 		}
	// 	}
	// }
	// for(int i=0;i<equi.size();i++)
	// {
	// 	cout<<i<<"-->";
	// 	for(int j=0;j<equi[i].size();j++)
	// 	{
	// 		cout<<equi[i][j]<<" ";
	// 	}
	// 	cout<<endl;
	// }


            vector<int> p(d.num_states);
            for(int i = 0; i < d.num_states; i++)
            {
                p[i] = i;
            }

            for(int i = 0; i < d.num_states; i++)
            {
                for(int j = i+1 ; j < d.num_states; j++)
                {
                    if(a[i][j] == 0)
                    {
                        p[j] = i;
                    }
                }
            }
            
            map<int, vector<int> > mapp;

            for(int i = 0; i < d.num_states; i++)
            {
                vector<int> path;
                int x = fnd(p,i,path);
                mapp[x] = path;
            }

            for(auto it : mapp)
            {
                cout << it.first << " : ";
                for(auto it1 : it.second)
                    cout << it1 << " ";
                cout << endl;
            }
            dfa min;

            min.num_states = mapp.size();
            min.table = vector<vector<int>>(min.num_states,vector<int>(d.num_alphabets));

            map<int,int> nmap;
            int index = 0;

            for(auto it : mapp)
            {
                nmap[it.first] = index++;
            }

            for(auto it : mapp)
            {
                for(int j = 1; j <= d.num_alphabets; j++)
                {
                    int start = *(it.second.begin());
                    int end = d.table[start][j];
                    int p_e = pfind(end,p);

                    min.table[nmap[it.first]][j] = nmap[p_e];
 
                }
            }

            for(auto it : d.final)
            {
                min.final.push_back(nmap[pfind(it,p)]);
            }
                        
            return min;



}

int main()
{
	ifstream input("input.txt");
	ofstream output("out.txt");


	int n_s,n_a;
	int fstate;
	input>> n_s >> n_a;
	input>>fstate;

	enfa obj(n_s,n_a);
	nfa obj1(n_s,n_a);
	
	for(int i=0;i<fstate;i++)
	{
		int data;
		input>>data;
		obj.final.push_back(data);
	}
	 while (!input.eof())
    {
        int x,y,z;
        input>>x>>y>>z;
        obj.table[x][y].push_back(z);
    }

	cout<<"Printing epsilon transitions and curresponding states"<<endl;
	for(int i=0;i<obj.num_states;i++)
	{
		cout<<i<<"->";
		for(int j=0;j<obj.table[i][0].size();j++)
			cout<<obj.table[i][0][j]<<" ";
		cout<<endl;
	}
	cout<<"Printing transitions and curresponding states"<<endl;
	for(int i=0;i<obj.num_states;i++)
	{
		cout<<i<<" -- ";
		for(int j=1;j<=obj.num_alphabets;j++)
		{
			cout<<j<<" -> ";
			for(int k=0;k<obj.table[i][j].size();k++)
				cout<<obj.table[i][j][k]<<" ";
			cout<<endl;
		}
		cout<<endl;
	}
	int t=1;
	dfa DFA1;
	while(t)
	{
		cout<<"Enter choice 1-Find Closure 2-Eliminate closure 3-nfa to dfa"<<endl;
		int ch;
		cin>>ch;
		switch(ch)
		{
			case 1:
			{
				int k;
				// cout<<"Enter state"<<endl;
				// cin>>k;
				vector<int> v;
				for(int i=0;i<obj.num_states;i++)
				{
				v=Find(obj.table,i,n_s);
				for(int j=0;j<v.size();j++)
				{
					int d=v[j];
					cout<<d<<" ";
				}

				cout<<endl;
			}

				break;
			}
			case 2:{
				obj1=convert(obj);
				cout<<"Final states "<<endl;
				for(int i=0;i<obj1.final.size();i++)
					cout<<obj1.final[i]<<" "<<endl;
				cout<<"Printing transitions and curresponding states"<<endl;
				for(int i=0;i<obj1.num_states;i++)
				{
					cout<<i<<" -- ";
					output<<i<<" ";
					for(int j=1;j<=obj1.num_alphabets;j++)
					{
						output<<"--"<<j<<" ";
						cout<<j<<" -> ";
						for(int k=0;k<obj1.table[i][j].size();k++)
						{
							cout<<obj1.table[i][j][k]<<" ";
							output<<obj1.table[i][j][k]<<" ";
						}
						cout<<endl;
						output<<endl;
					}
					cout<<endl;
					output<<endl;
				}
				cout<<obj1.num_alphabets;
				break;
			}
			case 3: 
			{
				DFA1 = nfatodfa(obj1);

				cout << "START\n";

				cout  << DFA1.num_states << " " << DFA1.num_alphabets << endl;

				for(int i=0;i<DFA1.num_states;i++)
				{
					cout<<i<<" ";
					for(int j=1;j<=DFA1.num_alphabets;j++)
					{
						cout<<j<<" ";
						cout<<DFA1.table[i][j]<<"  ";
					}

					cout << endl;
				}
				cout<<"Printing final states "<<endl;
				for(int i=0;i<DFA1.final.size();i++)
				{
					cout<<DFA1.final[i]<<" "<<endl;
				}


				dfa d=minimize(DFA1);
				cout<<"Optimized is "<<endl;
				cout  << d.num_states << " " << d.num_alphabets << endl;

				for(int i=0;i<d.num_states;i++)
				{
					cout<<i<<" ";
					for(int j=1;j<=d.num_alphabets;j++)
					{
						cout<<j<<" ";
						cout<<d.table[i][j]<<"  ";
					}

					cout << endl;
				}
				cout<<"Printing final states "<<endl;
				sort(d.final.begin(),d.final.end());
				unique(d.final.begin(),d.final.end());
				for(int i=0;i<d.final.size();i++)
				{
					if(d.final[i] != d.final[i-1])
						cout<<d.final[i]<<" "<<endl;
				}

				break;
			}

			default:t=0;
			break;
		}
	}
	return 0;
}
