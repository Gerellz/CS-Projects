#ifndef CIRCLE_H
#define CIRCLE_H

//***************************************
//
// circle.h
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include "shape.h"

class circle : public shape
{
private:
	int radius = 0;
//	int get_radius() const;
//	void set_radius(int);

public:
	circle() = default;
	circle(const std::string&, int);

	int get_radius() const;
	void set_radius(int);

	virtual void print() const;
	virtual double get_area() const;
};


#endif
