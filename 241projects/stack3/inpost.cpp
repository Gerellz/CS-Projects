//***************************************
//
// inpost.cpp
//
// CSCI 241 Assignment 8
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <string>
#include <cctype>
#include <cstdlib>
#include "mystack.h"
#include "inpost.h"

using std::string;

//************************************
// converts the infix expression into
// a postfix expression.
//
// @return: the new postfix expression
//***********************************/

string convert(const string& infix)
{
	mystack* s = new mystack();
	string postfix;
	size_t index = 0;

	while (index < infix.length())
	{
		if (islower(infix[index]))
		{
			postfix += infix[index];
			index++;
			postfix += ' ';
		}

		else if (isdigit(infix[index]))
		{
			while (isdigit (infix[index]))
			{
				postfix += infix[index];
				index++;
			}

			postfix += ' ';
		}

		else if (isspace(infix[index]))
		{
			index++;
		}

		else if (infix[index] == '(')
		{
			s->push(infix[index]);
			index++;
		}

		else if (infix[index] == ')')
		{
			while (!s->empty() && s->top() != '(')
			{
				postfix += s->top();
				s->pop();
				postfix += ' ';
			}

			if (!s->empty())
			{
				s->pop();
			}

			index++;
		}

		else
		{
			while (!s->empty() && precedence(infix[index]) <= precedence(s->top()))
			{
				postfix += s->top();
				s->pop();
				postfix += ' ';
			}

			s->push(infix[index]);
			index++;
		}
	}

	while (!s->empty())
	{
		postfix += s->top();
		s->pop();
		postfix += ' ';
	}

	return postfix;
}

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
