#ifndef SHAPE_H
#define SHAPE_H

//***************************************
//
// shape.h
//
// CSCI 241 Assignment 12
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <string>

class shape
{
private:
	std::string color;

public:
	shape() = default;
	shape(const std::string&);
	virtual ~shape();

	const std::string& get_color() const;

	virtual void print() const;
	virtual double get_area() const = 0;
};

#endif
