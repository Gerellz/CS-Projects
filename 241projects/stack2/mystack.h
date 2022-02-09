#ifndef MYSTACK_H
#define MYSTACK_H

//***************************************
//
// mystack.h
//
// CSCI 241 Assignment 8
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <cstdlib>

struct node
{
	int value;
	node* next;

	node(int value, node* next = nullptr)
	{
		this->value = value;
		this->next = next;
	}
};

class mystack
{
	private:

	node* stk_top = nullptr;
	size_t stk_size = 0;

	public:

	mystack() = default;
	mystack(const mystack&);
	~mystack();
	mystack& operator=(const mystack&);
	size_t size() const;
	bool empty() const;
	void clear();
	void reserve(size_t);
	const int& top() const;
	void push(int);
	void pop();
	void clone(const mystack&);
};

#endif /* MYSTACK_H */
