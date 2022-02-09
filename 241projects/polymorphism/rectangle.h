#ifndef RECTANGLE_H
#define RECTANGLE_H

//***************************************
//
// rectangle.h
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include "shape.h"
#include <string>

class rectangle : public shape
{
private:
	int height = 0;
	int width = 0;
	int get_height() const;
	void set_height(int);

	int get_width() const;
	void set_width(int);

public:
	rectangle() = default;
	rectangle(const std::string&, int, int);

//	int get_height() const;
//	void set_height();

//	int get_width() const;
//	void set_width(int);

	virtual void print() const;
	virtual double get_area() const;
};

#endif
