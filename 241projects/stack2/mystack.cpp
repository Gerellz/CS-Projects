//****************************************
//
// mystack.cpp
//
// CSCI 241 Assignment 8
//
// Written by Gerald Ellsworth (z1885378)
//
//***************************************/

#include "mystack.h"

//************************************
// initializes a new object to the
// same values as the existing mystack
// object.
//
// @param: a constant object.
//************************************/

mystack::mystack(const mystack& other)
{
	stk_top = nullptr;
	stk_size = other.stk_size;
	clone(other);
}

//******************
// deletes the stack
//******************/

mystack::~mystack()
{
	clear();
}

//***********************************************
// overloads the = operator and assigns one
// mystack object to another.
//
// @param: a constant object.
//
// @return: this object.
//***********************************************/

mystack& mystack::operator=(const mystack& other)
{
	if (this != &other)
	{
		clear();
		stk_size = other.stk_size;
		clone(other);
	}
	return *this;
}

//**************************
// returns the stack size.
//
// @return: stk_size.
//**************************/

size_t mystack::size() const
{
	return stk_size;
}

//***************************
// boolean that checks if
// the stack is empty or not.
//
// @return: a boolean.
//***************************/

bool mystack::empty() const
{
	if (stk_size == 0)
		return true;
	else
		return false;
}

//*******************
// clears the stack.
//******************/

void mystack::clear()
{
	while (!empty())
		pop();
}

//******************************
// returns the top of the stack.
//
// @return: the top of the stack
//	    array.
//*****************************/

const int& mystack::top() const
{
	return stk_top->value;
}

//****************************
// pushes a value to the top
// of the stack.
//
// @param: a value to be put
//	   on the stack.
//***************************/

void mystack::push(int value)
{
	node* new_node = new node(value, stk_top);

	stk_top = new_node;
	stk_size = stk_size + 1;
}

//****************
// removes an item
// from the stack.
//***************/

void mystack::pop()
{
	node* delete_node = stk_top;
	stk_top = stk_top->next;

	delete delete_node;

	stk_size--;
}

//***************************************
// clones the linked list from stack
// other to a new stack.
//
// @param: a stack object other.
//**************************************/

void mystack::clone(const mystack& other)
{
	node* last = nullptr;
	node* ptr = other.stk_top;

	while (ptr != nullptr)
	{
		node* new_node = new node(ptr->value, nullptr);

		if (last == nullptr)
			stk_top = new_node;
		else
			last->next = new_node;

		last = new_node;
		ptr = ptr->next;
	}
}
