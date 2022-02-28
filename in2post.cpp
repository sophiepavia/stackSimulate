#include <iostream>
#include <sstream>
//#include <cctype>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

string infix2Postfix(string s);
int precendance(char c);
bool isNumber(string num);
bool isOperand(string op);
char toChar(string s);
int evaluate(string s);

int main() 
{
	while(!cin.eof())
	{
		string pf;
		cout << "Enter infix expression (\"exit\" to quit): ";
		
		getline(cin, pf);
		
		if(pf == "exit")
			break;
		
		string p = infix2Postfix(pf);
		
		if(p != " ")
		{
			cout << "Postfix evaluation: " <<  p  <<  " = ";
			if(evaluate(p) == 0)
				cout << p << endl;
		}
		
	}	
}
string infix2Postfix(string s)
{
	//creates stack of chars (to push 
	Stack<char> stack;
	//will store postfix string
	string pf;
	//spilts string by spaces
	istringstream ss(s);
	//transverse till end of string
	string previous = "+";
	do
	{
		string token;
		ss >> token;
	
		//checking if it is an operand (digit or variable)
		if(isOperand(token))
		{
			if(isOperand(previous) && token != "")
			{
				cout << "\nError: Missing operators in the expression\n";
				return " ";
			}
				
			pf = pf + token + ' ';
		}
		//if not an operand, but a left parenthesis
		else if(token == "(")
		{
			if(isOperand(previous) && token != "")
			{
				cout << "\nError: Missing operators in the expression\n";
				return " ";
			}
			stack.push('(');
		}
			
		//if closing parenthesis is read in
		else if(token  == ")")
		{	
			if(!isOperand(previous))
			{
				if(previous == ")")
				{
					cout << "\nError: Infix expression has mismatched parens!\n";
					return " ";
				}
				cout << "\nError: Missing operands in expression\n";
				return " ";
			}
			//pop the stack till opening (, writing operators
			while(stack.top() != '(' && !stack.empty())
			{
				char c = stack.top();
				stack.pop();
				pf = pf + c + ' ';
				if(stack.top() != '(')
				{
					cout << "\nError: Infix expression has mismatched parens!\n";
					return " ";
				}	
			}
			if(stack.top() == '(')
			{	//when we get to ( pop it but don't write
				char c = stack.top();
				stack.pop();
			}		
		}
		//if it is an operator
		else
		{	//convert token to char
			char op = toChar(token);
			//pop only if token has less precendance than top of stack
			while(!stack.empty() && (precendance(op) <= precendance(stack.top())))
			{	
				char c = stack.top(); 
				stack.pop(); 
				pf = pf + c + ' ';
			}
			stack.push(op);		//push operand on stack 
		}
	previous = token;
	}while(ss);
	//now pop char remain in stack
	while(!stack.empty())
	{
		char c = stack.top(); 
		stack.pop();
		if(c != '(') 
			pf = pf + c + ' '; 
		else
		{
			cout << "\nError: Infix expression has mismatched parens!\n";
			return " ";
		}
			
	}
	cout << "\nPostfix expression: " << pf << "\n";
	
	return pf;
}
int evaluate(string s)
{
	//creates stack of chars (to push 
	Stack<float> stack;

	//will store postfix string
	string pf;
	//spilts string by spaces
	istringstream ss(s);
	
	do
	{
		string token;
		ss >> token;
		
		if((token >= "a" && token <= "z") || (token >= "A" && token <= "Z"))
			return 0;
	

		if(token != "+" && token != "-" && token != "/" && token != "*")
		{
			
			stringstream floatVal(token);
			float num = 0;
			floatVal >> num;
			stack.push(num);

		}
		else 
		{
			//the stack has exactly one operand in it, print that as the final result, or 0 if the stack is empty.
			
			if(stack.size() < 2)
			{
				cout << "\nError: Missing operand in postfix string. Unable to evluate postfix string!\n";
				return -1;
			}
			
			float val1 = stack.top();
			stack.pop();  
			float val2 = stack.top(); 
			stack.pop();
			
			if(token == "*")
			{
				stack.push(val2 * val1); 
			
			}	
				
			else if(token == "/")
			{
				stack.push(val2 / val1); 
				
			}
			
			else if(token == "+")
			{
				stack.push(val2 + val1); 
				
			}
			
			else if(token == "-")
			{
				stack.push(val2 - val1); 
		
			}
				
		}
		
	}while(ss);
	
	stack.pop();
	if(stack.size() == 1)
		cout << stack.top() << endl;
	if(stack.empty())
		cout << 0;

	return 1;
}

int precendance(char c)
{
	if(c == '*' || c == '/') 
		return 2; 
	else if(c == '+' || c == '-') 
		return 1; 
	return 0; 
	
}
bool isNumber(string num)
{
	for(int i = 0; i < num.length(); i++)
	{
		if(!isdigit(num[i]) && num[i] != '.')
			return false;
	}
	return true;
}
char toChar(string s)
{
	if(s == "+")
		return '+';
	else if(s == "-")
		return '-';
	else if(s == "/")
		return '/';
	else if(s == "*")
		return '*';
	return 0;
}
bool isOperand(string op)
{
	if((op >= "a" && op <= "z") || (op >= "A" && op <= "Z")  || isNumber(op))
		return true;
	return false;
}
