#ifndef TRIANGLE_H
#define TRIANGLE_H

//***************************************
//
// triangle.h
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include "shape.h"
#include <string>

class triangle : public shape
{
private:
	int height = 0;
	int base = 0;

	int get_height() const;
	void set_height(int);

	int get_base() const;
	void set_base(int);

public:
	triangle() = default;
	triangle(const std::string&, int, int);

//	int get_height() const;
//	void set_height(int);

//	int get_base() const;
//	void set_base(int);

	virtual void print() const;
	virtual double get_area() const;
};

#endif
