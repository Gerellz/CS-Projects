//***************************************
//
// assign12.cpp
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

#include "shape.h"
#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fixed;
using std::setprecision;

int main()
{
	vector<shape*> shapes;					//initializes a vector of pointers to the shape class.

	shapes.push_back(new circle("green", 10));
	shapes.push_back(new rectangle("red", 8, 6));
	shapes.push_back(new triangle("yellow", 8, 4));
	shapes.push_back(new triangle("black", 4, 10));
	shapes.push_back(new circle("orange", 5));
	shapes.push_back(new rectangle("blue", 3, 7));

	cout << "Printing all shapes...\n" << endl;

	for (size_t i = 0; i < shapes.size(); i++)		//loops through all the shapes and prints each (circle, rectangle, triangle)
	{
		shapes[i]->print();
	}

	cout << "\nPrinting only circles...\n" << endl;

	for (size_t i = 0; i < shapes.size(); i++)		//loops through only the circles listed and prints them.
	{
		circle* p = dynamic_cast<circle*>(shapes[i]);

		if (p != nullptr)
		{
			shapes[i]->print();
		}
	}

	for (size_t i = 0; i < shapes.size(); i++)		//deletes all the shapes in the shapes.
	{
		delete shapes[i];
	}

	return 0;
}
