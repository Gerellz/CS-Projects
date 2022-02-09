#ifndef MATRIX_H
#define MATRIX_H

//***************************************
//
// matrix.h
//
// CSCI 241 Assignment 6
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <iostream>

class matrix
{
	friend std::ostream& operator<<(std::ostream&, const matrix&);
	friend matrix operator*(int, const matrix&);

	private:

		int matrix_array[2][2] = {{1, 0}, {0, 1}};

	public:

		matrix();
		matrix(int[][2]);
		int determinant() const;
		matrix operator+(const matrix&) const;
		matrix operator*(int) const;
		matrix operator*(const matrix&) const;
		bool operator==(const matrix&) const;
		bool operator!=(const matrix&) const;
};

#endif /* MATRIX_H */
