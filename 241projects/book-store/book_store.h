#ifndef BOOK_STORE_H
#define BOOK_STORE_H

//****************************************
//
//  book_store.h
//
//  CSCI 241 Assignment 5
//
//  Written by Gerald Ellsworth (z1885378)
//
//****************************************/

#include <string>
#include "book.h"

class book_store
{
	private:
		book inventory[30];

		int book_data = 0;

		void sort_data();
		int binary_search(book [], int, const char*);

	public:
		void read_book_data(const std::string&);
		void process_orders(const std::string&);
		void print() const;
};

#endif /* BOOK_STORE_H */
