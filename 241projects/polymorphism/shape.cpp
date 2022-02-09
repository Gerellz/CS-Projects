//***************************************
//
// shape.cpp
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <iostream>
#include "shape.h"

using std::cout;
using std::endl;
using std::string;

//********************************
// constructor for the shape class
//
// @param1: a constant string, the
//    	    color of a shape.
//*******************************/

shape::shape(const string& color)
{
	this->color = color;
}

//***********************************
// Destructor for the shape class.
//
// @note: this is empty because
// 	  there is no need to
// 	  delete any dynamic storage.
//**********************************/

shape::~shape()
{
}

//************************************
// Returns the color of the shape.
//
// @return: the color of a shape.
//***********************************/

const string& shape::get_color() const
{
	return color;
}

//***********************************
// Print function to print the color
// of a shape.
//**********************************/

void shape::print() const
{
	cout << color;
}
