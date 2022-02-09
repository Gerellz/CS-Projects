#ifndef BOOK_H
#define BOOK_H

//****************************************
//
//  book.h
//
//  Assignment 5 CSCI 241
//
//  Written by Gerald Ellsworth (z1885378)
//
//****************************************/

class book
{
	private:

		char isbn[11] {"None"};
		char title[41] {"None"};

		double price = 0.0;

		int stock = 0;

	public:

		const char* get_isbn() const;
		double get_price();
		int fulfill_order(int);
		void print() const;
};

#endif /* BOOK_H */
