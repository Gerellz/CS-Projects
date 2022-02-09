//****************************************
//
//  mystack.cpp
//
//  CSCI 241 Assignment 7
//
//  Written by Gerald Ellsworth (z1885378)
//
//***************************************/

#include "mystack.h"

//************************************
// initializes a new object to the
// same values as the existing mystack
// object.
//
// @param: a constant object.
//************************************

mystack::mystack(const mystack& other)
{
	stk_size = other.stk_size;
	stk_capacity = other.stk_capacity;

	if (stk_capacity > 0)
		stk_array = new char[stk_capacity];

	else
		stk_array = nullptr;

	for (size_t i = 0; i < stk_size; i++)
		stk_array[i] = other.stk_array[i];
}

//*****************
//deletes the stack
//array.
//*****************

mystack::~mystack()
{
	delete[] stk_array;
}

//***********************************************
// overloads the = operator and assigns one
// mystack object to another.
//
// @param a constant object.
//
// @return this object.
//***********************************************

mystack& mystack::operator=(const mystack& other)
{
	if (this != &other)
	{
		delete[] stk_array;

		stk_capacity = other.stk_capacity;
		stk_size = other.stk_size;

		if (stk_capacity > 0)
			stk_array = new char[stk_capacity];
		else
			stk_array = nullptr;

		for (size_t i = 0; i < stk_size; i++)
			stk_array[i] = other.stk_array[i];
	}

	return *this;
}

//******************************
// returns the stack capacity.
//
// @return stk_capacity.
//******************************

size_t mystack::capacity() const
{
	return stk_capacity;
}

//**************************
// returns the stack size.
//
// @return stk_size.
//**************************

size_t mystack::size() const
{
 	return stk_size;
}

//***************************
// boolean that checks if
// the stack is empty or not.
//
// @return a boolean.
//***************************

bool mystack::empty() const
{
	if (stk_size == 0)
		return true;
	else
		return false;
}

//*******************
// clears the stack.
//*******************

void mystack::clear()
{
	stk_size = 0;
}

//******************************
// reserves additional storage
// for the array.
//
// @param: the amount of storage
//	   to reserve.
//******************************

void mystack::reserve(size_t n)
{
	if (n < stk_size || n == stk_capacity)
		return;

	stk_capacity = n;
	char* temp_array = new char[n];

	for (size_t i = 0; i < stk_size; i++)
		temp_array[i] = stk_array[i];

	delete[] stk_array;

	stk_array = temp_array;
}

//******************************
// returns the top of the stack.
//
// @return: the top of the stack
//	    array.
//******************************

const char& mystack::top() const
{
		return stk_array[stk_size - 1];
}

//****************************
// pushes a value to the top
// of the stack.
//
// @param: a value to be put
//	   on the stack.
//****************************

void mystack::push(char value)
{
	if (stk_size == stk_capacity)
	{
		if (stk_capacity == 0)
			reserve(1);
		else
			reserve(stk_capacity * 2);
	}
	stk_array[stk_size] = value;
	stk_size = stk_size +1;
}

//****************
// removes an item
// from the stack.
//****************

void mystack::pop()
{
	stk_size = stk_size - 1;
}
