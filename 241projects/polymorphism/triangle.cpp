//***************************************
//
// shape.cpp
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include "triangle.h"
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

//************************************
// Constructor for the triangle class
//
// @param1: a constant string which
// 	    denotes the color of the
// 	    triangle.
// @param2: an integer which denotes
// 	    the height of the triangle
// @param3: an integer which denotes
// 	    the base of the triangle
//************************************/

triangle::triangle(const string& color, int height, int base) : shape(color)
{
	set_height(height);
	set_base(base);
}

//************************************
// returns the height that is input
// in the main function.
//
// @return: the height of the triangle
//***********************************/

int triangle::get_height() const
{
	return height;
}

//************************************
// Mutator function for the height.
// If the height of the triangle is
// below 0, it is initialized to 0
// otherwise it is the given value.
//
// @param1: the height of the triangle.
//************************************/

void triangle::set_height(int height)
{
	this->height = (height < 0) ? 0 : height;
}

//**********************************
// returns the base that is input
//
// @return: the base of the triangle
//*********************************/

int triangle::get_base() const
{
	return base;
}

//***********************************
// Mutator function for the triangle.
// If the base of the triangle is
// below 0, it is initialized to 0
// otherwise it is the given value.
//
// @param1: the base of the triangle.
//**********************************/

void triangle::set_base(int base)
{
	this->base = (base < 0) ? 0 : base;
}

//**********************************
// Print function that overrides the
// shape class' print function.
//*********************************/

void triangle::print() const
{
	shape::print();
	cout << " triangle, height " << height << ", base " << base << ", area " << get_area() << endl;
}

//********************************
// Function to return the area
// of a triangle.
//
// @return: the area of a triangle
//          ((base * height)/2)
//*******************************/

double triangle::get_area() const
{
	return (base * height)/2;
}
