#ifndef MYSTACK_H
#define MYSTACK_H

//***************************************
// Written by Gerald Ellsworth (z1885378)
//**************************************/

#include <cstdlib>
#include <cctype>

class mystack
{
private:
	char* stk_array = nullptr;
	size_t stk_capacity = 0;
	size_t stk_size = 0;

public:
	mystack() = default;
	mystack(const mystack&);
	~mystack();
	mystack& operator=(const mystack&);

	size_t capacity() const;
	size_t size() const;

	bool empty() const;

	void clear();
	void reserve(size_t);
	void push(char);
	void pop();

	const char& top() const;
};

#endif /* MYSTACK_H */
