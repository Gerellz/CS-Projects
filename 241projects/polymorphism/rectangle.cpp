//***************************************
//
// shape.cpp
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include "rectangle.h"
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;

//**************************************************
// Constructor for the rectangle class
//
// @param1: a constant string that is the color
// 	    of the rectangle.
// @param2: an integer, the height of the rectangle
// @param3: an integer, the width of the rectangle
//
// @note: initialized using a constructor
// 	  initialization list.
//*************************************************/

rectangle::rectangle(const string& color, int height, int width) : shape(color)
{
	set_height(height);
	set_width(width);
}

//******************************************
// Returns the height value of the rectangle
//
// @return: the height of the circle.
//*****************************************/

int rectangle::get_height() const
{
	return height;
}

//**************************************************
// Mutator function for the height of the rectangle.
// If the height of the rectangle is below 0, it is
// initialized to 0 instead.
//
// @param1: an integer, the height of the rectangle.
//*************************************************/

void rectangle::set_height(int height)
{
	this->height = (height < 0) ? 0 : height;
}

//*******************************************
// Returns the width value that is input in the
// main function.
//
// @return1: the width of the rectangle
//******************************************/

int rectangle::get_width() const
{
	return width;
}

//******************************************
// Mutator function for the width of the rectangle.
// If the width of the rectangle is below 0, it is
// initialized to 0 instead.
//*****************************************/

void rectangle::set_width(int width)
{
	this->width = (width < 0) ? 0 : width;
}

//**********************************
// Print function that overrides the
// shape class' print function.
//*********************************/

void rectangle::print() const
{
	shape::print();

	cout << " rectangle, height " << height << ", width " << width << ", area " << get_area() << endl;
}

//*********************************
// Function to return the area of a
// rectangle.
//
// @return: the area of a rectangle
// 	    (length * width).
//********************************/
double rectangle::get_area() const
{
	return height * width;
}
