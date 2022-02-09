//***************************************
//
// eval.cpp
//
// CSCI 241 Assignment 8
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "mystack.h"
#include "inpost.h"

using std::cout;
using std::string;
using std::stringstream;
using std::stoi;
using std::islower;
using std::isdigit;

//**********************************
// evaluates the postfix string
// and assigns the operation a
// value.
//
// @param: a string of integers,
//	   variables, and operators.
//
// @return: the value of the
//	    finished operation.
//**********************************

int evaluate(const string& postfix)
{
	mystack* eval_stack = new mystack();				//initializes a new stack
	string op;
	stringstream ss(postfix);					//stream of the postfix string

	while (ss >> op)						//while streaming the postfix into the op string:
	{
		if (islower(op[0]))					//if the value is a lowercase letter,
		{							//subtract the value of 'a' (0) from the
			int value = op[0] - 'a';			//value of the operand and push it onto the stack.
			eval_stack->push(value);
		}

		else if (isdigit(op[0]))				//if the value is a digit, convert
		{							//the string to an integer and
			int value = stoi(op);				//push the value onto the stack.
			eval_stack->push(value);
		}

		else if (op[0] == '~')					//if the operand is a negation, get
			{						//the value from the top of the stack,
				int value = eval_stack->top();		//pop the stack, multiply the value by -1,
				eval_stack->pop();			//and push the new value onto the stack.
				value = value * -1;
				eval_stack->push(value);
			}

		else							//if the value is none of the above, it must
		{							//be an operator and therefore we must use a
			int r_op = eval_stack->top();			//left and right operand to complete the equation.
			eval_stack->pop();				//we take the left and right operands from the top of
			int l_op = eval_stack->top();			//the stack and then pop the stack before calling for
			eval_stack->pop();				//the operator.

			if (op[0] == '+')
			{
				int value = l_op + r_op;
				eval_stack->push(value);
			}

			else if (op[0] == '-')
			{
				int value = l_op - r_op;
				eval_stack->push(value);
			}

			else if (op[0] == '^')				//if the operator is a '^', we have to check
			{						//if the exponent is 0. If it is, we either set
				if (r_op == 0)				//the value to -1 or to 1 depending on if the
				{					//left operand is positive or negative.
					if (l_op > 0)
						eval_stack->push(1);
					else
						eval_stack->push(-1);
				}

				else					//if the exponent is not a 0, we multiply
				{					//the left operand by itself a number of
					int exp = l_op;			//times equal to the value of the exponent.

					for (int i = 1; i < r_op; i++)
						l_op  = l_op * exp;
					int value = l_op;

					eval_stack->push(value);
				}
			}

			else if (op[0] == '/')
			{
				if (r_op == 0)					//if we try to divide by zero, bad things happen.
				{						//...So lets not do that...
					cout << "*** Division by 0 ***\n";
					eval_stack->push(0);
				}

				else
				{
					int value = l_op / r_op;
					eval_stack->push(value);
				}
			}

			else if (op[0] == '*')
			{
				int value = l_op * r_op;
				eval_stack->push(value);
			}
		}
	}

	int result = eval_stack->top();

	return result;
}
