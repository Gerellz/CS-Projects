//***************************************
//
// shape.cpp
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include "circle.h"
#include <iostream>
#include <string>
#include <math.h>

using std::cout;
using std::endl;
using std::string;

//*********************************
// Constructor for the circle class
//
// @param1: a constant string which
// 	    denotes the color of
//	    the shape.
// @param2: an integer which denotes
//	    the radius of the circle
//
// @note: initialized using a
//	  constructor initialization
//	  list.
//********************************/

circle::circle(const string& color, int radius) : shape(color)
{
	set_radius(radius);
}

//**********************************
// returns the radius that is input
// in the main function.
//
// @return: the radius of the circle
//*********************************/

int circle::get_radius() const
{
	return radius;
}

//***********************************
// Mutator function for the radius.
// If the radius of the circle is
// below 0, it is initialized to 0
// otherwise it is the given value.
//
// @param1: the radius of the circle.
//**********************************/

void circle::set_radius(int radius)
{
	this->radius = (radius < 0.0) ? 0.0 : radius;
}

//**********************************
// Print function that overrides the
// shape class' print function.
//*********************************/

void circle::print() const
{
	shape::print();
	cout << " circle" << ", radius " << radius << ", area " << get_area() << endl;
}

//*******************************
// Function to return the area
// of a circle.
//
// @return: the area of a circle
//	    (pi * radius squared)
//******************************/

double circle::get_area() const
{
	double pi = 3.14159265358979323846;

	return pi * (radius * radius);
}
