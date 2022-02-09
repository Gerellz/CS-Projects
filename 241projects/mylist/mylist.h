#ifndef MYLIST_H
#define MYLIST_H

//***************************************
//
// mylist.h
//
// CSCI 241 Assignment 10
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include <iostream>
#include <stdexcept>

using std::underflow_error;

template <class T>
class mylist;

template <class T>
std::ostream& operator<<(std::ostream&, const mylist<T>&);

template <class T>
struct node
{
	T value;
	node<T>* prev;
	node<T>* next;

	node(const T& value = T(), node<T>* prev = nullptr, node<T>* next = nullptr)
        {
                this->value = value;
		this->prev = prev;
                this->next = next;
        }
};

template <class T>
class mylist
{
	friend std::ostream& operator<< <>(std::ostream&, const mylist<T>&);

private:
	node<T>* l_front;
	node<T>* l_back;
	size_t l_size;

public:
	mylist();
	~mylist();
	mylist(const mylist<T>& x);
	mylist<T>& operator=(const mylist<T>&);

	void clear();
	size_t size() const;
	bool empty() const;
	const T& front() const;
	T& front();
	const T& back() const;
	T& back();
	void push_front(const T& value);
	void push_back(const T& value);
	void pop_front();
	void pop_back();
	bool operator==(const mylist<T>& rhs) const;
	bool operator<(const mylist<T>& rhs) const;
	void clone(const mylist<T>&);
};

//*********************************
// initializer for the mylist class
//********************************/

template <class T>
mylist<T>::mylist()
{
	l_front = nullptr;
	l_back = nullptr;
	l_size = 0;
}

//********************************
// destructor for the mylist class
//*******************************/

template <class T>
mylist<T>::~mylist()
{
	clear();
}

//**********************************
// copy constructor that copies the
// list nodes.
//*********************************/

template <class T>
mylist<T>::mylist(const mylist<T>& x)
{
	l_front = nullptr;
	l_back = nullptr;
	l_size = 0;

/*	auto node = x.l_front;

	while (node != nullptr)
	{
		push_back(node->value);
		node = node->next;
	}
*/
	clone(x);
}

//*************************************************
// overloaded assignment operator.
// @return: a pointer to a mylist object 'this'.
//************************************************/

template <class T>
mylist<T>& mylist<T>::operator=(const mylist<T>& x)
{
	if (this != &x)
	{
		clear();
/*		auto node = x.l_front;

		while (node !=nullptr)
		{
			push_back(node->value);
			node = node->next;
		}*/
		clone(x);
	}
	return *this;
}

//**********************
// sets the link back
// to empty and deletes
// all nodes in the list
//*********************/

template <class T>
void mylist<T>::clear()
{
	while (!empty())
	{
		pop_back();
	}
}

//****************************
// returns the list size.
// @return: the list size.
//***************************/
template <class T>
size_t mylist<T>::size() const
{
return l_size;
}

//****************************
// checks if the list is empty
// @return1: true if the list
//	     is empty.
//
// @return2: false if the list
//	     is not empty.
//***************************/

template <class T>
bool mylist<T>::empty() const
{
	if (l_size == 0)
		return true;
	else
		return false;
}

//*******************************
// returns the value of the front
// node of the list.
// @return: the front of the list
//	    value.
//******************************/

template <class T>
const T& mylist<T>::front() const
{
	if (l_size == 0)
	{
		throw underflow_error("underflow exception on call to front()");
	}

	else
		return l_front->value;
}

//******************************
// returns the value of the front
// node of the list.
// @return: the front of the list
//	    value.
//*****************************/

template <class T>
T& mylist<T>::front()
{
	if (l_size == 0)
	{
		throw underflow_error("underflow exception on call to front()");
	}

	else
		return l_front->value;
}

//******************************
// returns the value of the back
// node of the list.
// @return: the back of the list
//	    value.
//*****************************/

template <class T>
const T& mylist<T>::back() const
{
	if (l_size == 0)
	{
		throw underflow_error("underflow exception on call to back()");
	}

	else
		return l_back->value;
}

//*****************************
// returns the value of the back
// node of the list.
// @return: the back of the list
//	    value.
//****************************/

template <class T>
T& mylist<T>::back()
{
	if (l_size == 0)
	{
		throw underflow_error("underflow exception on call to back()");
	}

	else
		return l_back->value;
}

//***************************************
// inserts an item at the front of the list.
//**************************************/

template <class T>
void mylist<T>::push_front(const T& value)
{
	node<T>* new_node = new node<T>(value);
/*	new_node->value = value;
	new_node->prev = nullptr;
	new_node->next = nullptr;
*/
	new_node->next = l_front;

	if (empty())
		l_back = new_node;

	else
		l_front->prev = new_node;

	l_front = new_node;

	l_size++;
}

//****************************************
// inserts an item at the back of the list
//***************************************/

template <class T>
void mylist<T>::push_back(const T& value)
{
	node<T>* new_node = new node<T>(value);
/*	new_node->value = value;
	new_node->prev = nullptr;
	new_node->next = nullptr;
*/
	new_node->prev = l_back;

	if (empty())
		l_front = new_node;

	else
		l_back->next = new_node;

	l_back = new_node;

	l_size++;
}

//*******************************
// removes the item at the front
// of the list.
//******************************/

template <class T>
void mylist<T>::pop_front()
{
	if (empty())
	{
		throw underflow_error("underflow exception on call to pop_front()");
	}

	node<T>* del_node = l_front;

	l_front = del_node->next;

	if (l_front == nullptr)
		l_back = nullptr;
	else
		l_front->prev = nullptr;

	delete del_node;

	--l_size;
}

//************************
// removes the item at the
// back of the list.
//***********************/

template <class T>
void mylist<T>::pop_back()
{
	if (empty())
	{
		throw underflow_error("underflow exception on call to pop_back()");
	}

	node<T>* del_node = l_back;

	l_back = del_node->prev;

	if (l_back == nullptr)
		l_front = nullptr;
	else
		l_back->next = nullptr;

	delete del_node;

	--l_size;
}

//****************************************************
// overloads the equality operator for a comparsion of
// two mylist objects.
// @return1: true if the two lists contain the same
//	    number of nodes and if the lists are equal
//	    in value.
// @return2: false if either of the above are false.
//***************************************************/

template <class T>
bool mylist<T>::operator==(const mylist<T>& rhs) const
{
	if (this->size() != rhs.size())
		return false;

	auto rnode = rhs.l_front;
	auto lnode = l_front;

	while (rnode->value == lnode->value)
	{
		if (rnode->next == nullptr)
			return true;

		rnode = rnode->next;
		lnode = lnode->next;
	}

	return false;
}

//***************************************************
// overloads the less than operator to compare two
// mylist objects.
// @return1: if all the value elements are equivalent
//	     returns false.
// @return2: returns true if .
//**************************************************/

template <class T>
bool mylist<T>::operator<(const mylist<T>& rhs) const
{
	if (rhs.empty())
		return false;

	if (empty())
		return true;

	auto lnode = l_front;
	auto rnode = rhs.l_front;

	while (lnode->value == rnode->value)
	{
		if (rnode->next == nullptr)
			return false;

		if (lnode->next == nullptr)
			return true;

		lnode = lnode->next;
		rnode = rnode->next;
	}

	return lnode->value < rnode->value;
}

//************************************************************
// overloads the stream insertion operator so a mylist object
// can be sent to standard output.
// @return: os.
//***********************************************************/

template <class T>
std::ostream&operator <<(std::ostream& os, const mylist<T>& obj)
{
	auto node = obj.l_front;

	while (node != nullptr)
	{
		std::cout << node->value << " ";
		node = node->next;
	}

return os;
}

template <class T>
void mylist<T>::clone(const mylist<T>& x)
{
	auto node = x.l_front;

	while (node != nullptr)
	{
		push_back(node->value);
		node = node->next;
	}
}

#endif /* MYLIST_H */
