#include<bits/stdc++.h>
#include<fstream>
using namespace std;

#define RES 1
#define READ 2
#define WRITE 3
#define LOAD_VAR 4
#define LOAD_INT 5
#define LT 6
#define GT 7
#define EQ 8
#define JMP_FALSE 9
#define GOTO 10
#define  STORE 11
#define ADD 12
#define MUL 13
#define SUB 14
#define DIV 15
#define HALT 16

int get_type(string s);



struct file_dup
{
	string opcode;
	int operand;
};

int main()
{
	ifstream input("machine_code.txt");
	vector<file_dup> info;
	string s;
	stack<int> calc;
	vector<int> data_segment;

	while(1)
	{
		file_dup f;
		input >> f.opcode >> f.operand;
		// cout << f.opcode << " " << f.operand << endl;
		info.push_back(f);
		if(f.opcode == "halt")
			break;

	}

	int line = 0;
	while(line < info.size())
	{
		file_dup instruction = info[line];
		// cout << instruction.opcode << " " << instruction.operand << endl;
		int type = get_type(instruction.opcode);
		switch(type)
		{
			case RES:
				data_segment = vector<int> (instruction.operand);
				break;
			case READ: 
			{
				int x;
				cin >> x;
				data_segment[instruction.operand] = x;

				break;
			}
			case WRITE:
			{
				int x = calc.top();
				calc.pop();
				cout << x << endl;
				break;
			}
			case LOAD_VAR:
			{
				int x = data_segment[instruction.operand];
				calc.push(x);
				break;
			}
			case LOAD_INT:
			{
				calc.push(instruction.operand);
				break;
			}
			case LT:
			{
				int b = calc.top();
				calc.pop();
				int a = calc.top();
				calc.pop();
				if(a < b)
					calc.push(1);
				else
					calc.push(0);
				break;
			}
			case GT:
			{
				int b = calc.top();
				calc.pop();
				int a = calc.top();
				calc.pop();
				if(a > b)
					calc.push(1);
				else
					calc.push(0);
				break;
			}
				
			case EQ:
				{
				int b = calc.top();
				calc.pop();
				int a = calc.top();
				calc.pop();
				if(a == b)
					calc.push(1);
				else
					calc.push(0);
				break;
				}
			case JMP_FALSE:
			{
				int x = calc.top();
				calc.pop();
				if(x == 0)
					line = instruction.operand - 2;
				break;
			}
			case GOTO:
				line = instruction.operand - 2;
				break;
			case ADD:
				{
				int b = calc.top();
				calc.pop();
				int a = calc.top();
				calc.pop();
				calc.push(a+b);
				break;
			}
			case SUB:
				{
				int b = calc.top();
				calc.pop();
				int a = calc.top();
				calc.pop();
				calc.push(a-b);
				break;
			}
			case MUL:
				{
				int b = calc.top();
				calc.pop();
				int a = calc.top();
				calc.pop();
				calc.push(a*b);
				break;
			}
			case DIV:
				{
				int b = calc.top();
				calc.pop();
				int a = calc.top();
				calc.pop();
				calc.push(a/b);
				break;
			}
			case STORE:
			{
				int x = calc.top();
				calc.pop();
				data_segment[instruction.operand] = x;
				break;
			}

			case HALT:
				break;



		}
		line++;
	}


	return 0;
}

int get_type(string s)
{
	if(s == "res")
		return RES;
	else if(s == "read")
		return READ;
	else if(s == "read")
		return READ;
	else if(s == "write")
		return WRITE;
	else if(s == "load_var")
		return LOAD_VAR;
	else if(s == "load_int")
		return LOAD_INT;
	else if(s == "lt")
		return LT;
	else if(s == "gt")
		return GT;
	else if(s == "eq")
		return EQ;
	else if(s == "jmp_false")
		return JMP_FALSE;
	else if(s == "goto")
		return GOTO;
	else if(s == "store")
		return STORE;
	else if(s == "add")
		return ADD;
	else if(s == "mul")
		return MUL;
	else if(s == "sub")
		return SUB;
	else if(s == "div")
		return DIV;
	else if(s == "store")
		return STORE;
	else if(s == "halt")
		return HALT;
	else
		return -1;

}