//****************************************
//
//  inpost.cpp
//
//  CSCI 241 Assignemnt 7
//
//  Written by Gerald Ellsworth (z1885378)
//
//***************************************/

#include <string>
#include <cctype>
#include <cstdlib>
#include "inpost.h"
#include "mystack.h"

using std::string;

//*********************************
// converts the infix expression
// into a postfix expression.
//
// @return the postfix expression.
//*********************************/

string convert(const string& infix)
{
	mystack* s = new mystack();					//initializes a new object
	string postfix;
	size_t index = 0;

	while (index < infix.length())					//cycles through the whole infix string
	{
		if (islower(infix[index]))				//checks if the character is a lowercase letter
		{							//if it is, append it to the postfix string
			postfix += infix[index];			//and move to the next index in the array.
			index++;
			postfix += ' ';
		}

		else if (isdigit(infix[index]))				//checks if the character is a digit
		{
			while (isdigit(infix[index]))
			{
				postfix += infix[index];
				index++;
			}

			postfix += ' ';					//appending a space is added outside of the while loop
		}							//to make sure its not done multiple times for a single
									//larger number. (ie 243 instead of 2 4 3).
		else if (isspace(infix[index]))
		{
			index++;					//this else if checks if there is a space.
		}

		else if (infix[index] == '(')				//checks if the character is a left parenthesis.
		{							//if it is, push it onto the top of the stack.
			s->push(infix[index]);
			index++;
		}

		else if (infix[index] == ')')				//checks if the character is a right parenthesis.
		{							//if it is and while the stack is not empty AND
			while (!s->empty() && s->top() != '(')		//the top of the stack is not a left parenthesis,
			{						//append the top of the stack to the postfix string
				postfix += s->top();			//and pop the stack.
				s->pop();
				postfix += ' ';
			}

			if (!s->empty())				//if the stack is not empty, pop the stack
			{
				s->pop();
			}

			index++;
		}

		else										//if the character is an operator, check
		{										//the precedence of the operator versus
			while (!s->empty() && precedence(infix[index]) <= precedence(s->top()))	//the top of the stack. if it is higher
			{									//push the operator onto the stack. if it
				postfix += s->top();						//is lower, append the top of the stack.
				s->pop();							//and then pop the stack.
				postfix += ' ';
			}

			s->push(infix[index]);
			index++;
		}

	}

	while (!s->empty())						//while the stack is not empty
	{								//append the top of the stack
		postfix += s->top();					//to the postfix string and
		s->pop();						//pop the stack.
		postfix += ' ';
	}

	return postfix;
}

//******************************
// finds the precedence of the
// operator and sets them to a
// value to be compared.
//
// @param: a character.
//
// @return: the precedence value
//          of the operator.
//******************************

int precedence (char op)
{

	if (op == '~' || op == '^')
		return 3;
	else if (op == '*' || op == '/')
		return 2;
	else if (op == '+' || op == '-')
		return 1;
	else
		return 0;
}
