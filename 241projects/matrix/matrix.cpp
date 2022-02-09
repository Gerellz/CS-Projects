//****************************************
//
//  matrix.cpp
//
//  CSCI 241 Assignment 6
//
//  Written by Gerald Ellsworth (z1885378)
//
//***************************************/

#include <iostream>
#include "matrix.h"

using std::ostream;

//*********************************
//  sets the elements of the array
//  to a proper identity matrix.
//
//*********************************

matrix::matrix()
{
	matrix_array[0][0] = 1;
	matrix_array[0][1] = 0;
	matrix_array[1][0] = 0;
	matrix_array[1][1] = 1;
}

//*******************************
//  initializes the elements in
//  matrix_array to the elements
//  of the given array.
//
//  @param: an array of integers
//*******************************

matrix::matrix(int array[][2])
{
	matrix_array[0][0] = array[0][0];
	matrix_array[0][1] = array[0][1];
	matrix_array[1][0] = array[1][0];
	matrix_array[1][1] = array[1][1];
}

//***************************************
//  function that multiplies and
//  subtracts given elements in
//  the matrix.
//
//  @return the result of multiplication
//   and then subtraction between array
//   elements.
//***************************************

int matrix::determinant() const
{
	return matrix_array[0][0] * matrix_array[1][1] - matrix_array[0][1] * matrix_array[1][0];
}

//*************************************
//  arithmetic function that adds
//  elements of one array to another.
//
//  @param: a reference to a constant
//   matrix object
//
//  @return: the result of the addition
//   between the two arrays.
//*************************************

matrix matrix::operator+(const matrix& rhs) const
{
	matrix result;

	result.matrix_array[0][0] = matrix_array[0][0] + rhs.matrix_array[0][0];			//Fun fact: I messed this up a few times because
	result.matrix_array[0][1] = matrix_array[0][1] + rhs.matrix_array[0][1];			//I added the wrong elements to each other over
	result.matrix_array[1][0] = matrix_array[1][0] + rhs.matrix_array[1][0];			//and over again. I promise I can do addition :)
	result.matrix_array[1][1] = matrix_array[1][1] + rhs.matrix_array[1][1];

	return result;
}

//*************************************
//  function that multiplies a matrix
//  by an integer.
//
//  @param: an integer
//
//  @return: the result of the
//   multiplication between matrix and
//   the integer.
//*************************************

matrix matrix::operator*(int rhs) const
{
	matrix result;

		result.matrix_array[0][0] = matrix_array[0][0] * rhs;					//this function has a friend found below that
		result.matrix_array[0][1] = matrix_array[0][1] * rhs;					//deals with the other array used in this program.
		result.matrix_array[1][0] = matrix_array[1][0] * rhs;					//It's nice to have friends :)
		result.matrix_array[1][1] = matrix_array[1][1] * rhs;

	return result;
}

//***********************************************
//  function that performs multiplication between
//  two matrices.
//
//  @param: a reference to a constant matrix
//   object.
//
//  @return: the result of matrix multiplication.
//***********************************************

matrix matrix::operator*(const matrix& rhs) const
{
	matrix result;

	result.matrix_array[0][0] = matrix_array[0][0] * rhs.matrix_array[0][0] + matrix_array[0][1] * rhs.matrix_array[1][0];		//thanks to order
	result.matrix_array[0][1] = matrix_array[0][0] * rhs.matrix_array[0][1] + matrix_array[0][1] * rhs.matrix_array[1][1];		//of operations,
	result.matrix_array[1][0] = matrix_array[1][0] * rhs.matrix_array[0][0] + matrix_array[1][1] * rhs.matrix_array[1][0];		//this resolves
	result.matrix_array[1][1] = matrix_array[1][0] * rhs.matrix_array[0][1] + matrix_array[1][1] * rhs.matrix_array[1][1];		//properly. Yay!

	return result;
}

//**********************************************
//  function that checks if elements in one
//  array are equal to the elements in another.
//
//  @param: a reference to a constant matrix
//   object.
//
//  @return: a boolean value. True if elements
//   are equal, false if they are not.
//**********************************************

bool matrix::operator==(const matrix& rhs) const
{
	if (this->matrix_array[0][0] == rhs.matrix_array[0][0] &&
	this->matrix_array[0][1] == rhs.matrix_array[0][1] &&
	this->matrix_array[1][0] == rhs.matrix_array[1][0] &&
	this->matrix_array[1][1] == rhs.matrix_array[1][1])
		return true;

	else
		return false;
}

//**********************************************
//  function that checks if elements in one
//  array are equal to the elements in another.
//
//  @param: a reference to a constant matrix
//   object.
//
//  @return: a boolean value. False if elements
//   are equal, true if they are not.
//**********************************************

bool matrix::operator!=(const matrix& rhs) const
{
	if (this->matrix_array[0][0] == rhs.matrix_array[0][0] &&
	this->matrix_array[0][1] == rhs.matrix_array[0][1] &&
	this->matrix_array[1][0] == rhs.matrix_array[0][1] &&
	this->matrix_array[1][1] == rhs.matrix_array[1][1])
		return false;

	else
		return true;
}

//***********************************************************
//  function that prints the elements of a matrix object.
//
//  @param1: a reference to an ostream object.
//
//  @param2: a reference to a constant matrix object.
//
//  @return: a reference to an ostream object.
//***********************************************************

std::ostream& operator<<(std::ostream& os, const matrix& rhs)
{
	std::cout<<"[["<<rhs.matrix_array[0][0]<<", "<<rhs.matrix_array[0][1]<<"], ["<<rhs.matrix_array[1][0]<<", "<<rhs.matrix_array[1][1]<<"]]";

	return os;
}

//*******************************************
//  friend function to the operator*
//  function used above. multiplies an
//  integer by the element of an array.
//
//  @param1: an integer
//
//  @param2: a reference to a constant matrix
//   object.
//
//  @return: the result of multiplication
//   between an integer and the element of
//   an array.
//*******************************************

matrix operator*(int lhs, const matrix& rhs)
{
	matrix result;

	result.matrix_array[0][0] = lhs * rhs.matrix_array[0][0];			//when the operator function is called
	result.matrix_array[0][1] = lhs * rhs.matrix_array[0][1];			//this function will multiply the array
	result.matrix_array[1][0] = lhs * rhs.matrix_array[1][0];			//by an integer on the left-hand side.
	result.matrix_array[1][1] = lhs * rhs.matrix_array[1][1];			//in this program, that number is 4.

	return result;
}
