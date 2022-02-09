#ifndef BSTREE_H
#define BSTREE_H

//***************************************
// bstree.h
//
// CSCI 241 Assignment 11
//
// Written by Gerald Ellsworth (z1885378)
//**************************************/

#include <iostream>

using std::cout;
using std::endl;

template <class K, class V>
class bstree;

template <class K, class V>
struct node
{
	K key;
	V value;
	node<K, V>* left;
	node<K, V>* right;

	node(const K& key = K(), const V& value = V(), node<K, V>* left = nullptr, node<K, V>* right = nullptr)
	{
		this->key = key;
		this->value = value;
		this->left = left;
		this->right = right;
	}
};

template <class K, class V>
class bstree
{
private:
	node<K, V>* root;
	size_t tree_size;

	const K& maximum(const K&, const K&) const;
	const K& height_check(node<K, V>*) const;
	void preorder_traversal(node<K, V>*) const;
	void inorder_traversal(node<K, V>*) const;
	void postorder_traversal(node<K, V>*) const;
public:
	bstree();
	~bstree();
	bstree(const bstree<K, V>&);
	bstree<K, V>& operator=(const bstree<K, V>&);

	void clear();
	void destroy(const node<K, V>*);
	size_t size() const;
	size_t height() const;
	bool empty() const;
	const K& min() const;
	const K& max() const;
	bool insert(const K&, const V&);
	bool remove(const K&);
	const node<K, V>* find(const K&) const;
	void preorder() const;
	void inorder() const;
	void postorder() const;
	void level_order() const;
	node<K, V>* clone(const node<K, V>*);
};

//*************************
// default constructor for
// the bstree class. sets
// the root node to nullptr
// and the tree size to 0.
//************************/

template <class K, class V>
bstree<K, V>::bstree()
{
	root = nullptr;
	tree_size = 0;
}

//*************************
// destructor method for
// the bstree class.
//************************/

template <class K, class V>
bstree<K, V>::~bstree()
{
	clear();
}

//*************************
// copy constructor for the
// bstree class.
//
// @param: a constant node
//	   to copy to.
//************************/

template <class K, class V>
bstree<K, V>::bstree(const bstree<K, V>& x)
{
	tree_size = x.tree_size;
	root = clone(x.root);
}

//*************************
// overloaded  assignment
// operator.
//
// @param: a constant node
//	   to copy to.
//************************/

template <class K, class V>
bstree<K, V>& bstree<K, V>::operator=(const bstree<K, V>& x)
{
	if (this!= &x)
	{
		clear();
		tree_size = x.tree_size;
		root = clone(x.root);
	}

	return *this;
}

//*************************
// sets the tree back to
// empty and deletes the
// nodes.
//************************/

template <class K, class V>
void bstree<K, V>::clear()
{
	destroy(root);
	root = nullptr;
	tree_size= 0;
}

//*************************
// destroy function made to
// delete a node.
//
// @param: a pointer to a node
//	   to be deleted.
//************************/

template <class K, class V>
void bstree<K, V>::destroy(const node<K, V>* p)
{
	if (p != nullptr)
	{
		destroy(p->left);
		destroy(p->right);
		delete p;
	}
}


//*******************************
// returns the size of the tree
//
// @return: the size of the tree.
//******************************/

template <class K, class V>
size_t bstree<K, V>::size() const
{
	return tree_size;
}

//*******************************
// height function made to determine
// the height of the tree.
//******************************/

template <class K, class V>
size_t bstree<K, V>::height() const
{
/*
	node<K, V>* p = root;

	if (empty())
		return 0;

	else
		return height();
*/
	if (empty())
		return 0;
	else if (tree_size == 1)
		return 1;
	else
		return tree_size;
}


//*************************
// function to check the
// height of the tree
//
// @return: the highest key
//	    on the tree.
//************************/

template <class K, class V>
const K& bstree<K, V>::height_check(node<K, V>* p) const
{
	K left_height, right_height;

	if (p != nullptr)
	{
		left_height = height_check(p->left);
		right_height = height_check(p->right);
		return maximum(left_height, right_height);
	}

	else
		return maximum(left_height, right_height);
}

//*************************
// finds the higher between
// two values.
//
// @return: the higher of
//	    two values.
//************************/

template <class K, class V>
const K& bstree<K, V>::maximum(const K& a, const K& b) const
{
	return (a<b)?b:a;
}

//*************************
// checks if the tree is
// empty.
//
// @return1: true if the tree
//	     is empty.
// @return2: false if the tree
//	     is not empty.
//************************/

template <class K, class V>
bool bstree<K, V>::empty() const
{
	if (tree_size == 0)
		return true;
	else
		return false;
}

//*************************
// finds the minimum key in
// the tree.
//
// @return: the minimum key
//	    in the tree.
//************************/

template <class K, class V>
const K& bstree<K, V>::min() const
{
	node<K, V>* current_node = new node<K, V>;

	current_node = root;

	while (current_node->left != nullptr)
		current_node = current_node->left;

	return current_node->key;
}

//*************************
// finds the maximum key in
// the tree.
//
// @return: the maximum key
//	    in the tree.
//************************/

template <class K, class V>
const K& bstree<K, V>::max() const
{
	node<K, V>* current_node = new node<K, V>;

	current_node = root;

	while (current_node->right != nullptr)
		current_node = current_node->right;

	return current_node->key;

}

//*************************
// inserts a node into the
// tree.
//
// @param1: a constant K
//	    value.
// @param2: a constant V
//	    value.
// @return1: false if the
//	     root node is
//	     nullptr.
// @return2: true if able
//	     to insert a
//	     node.
//************************/

template <class K, class V>
bool bstree<K, V>::insert(const K& key, const V& value)
{
	node<K, V>* p = root;
	node<K, V>* parent = nullptr;

	while (p != nullptr && key != p->key)
	{
		parent = p;
		if (key < p->key)
			p = p->left;
		else
			p = p->right;
	}

	if (p != nullptr)
		return false;

	node<K, V>* new_node = new node<K, V>;
	new_node->key = key;
	new_node->value = value;

	if (parent == nullptr)
		root = new_node;
	else
	{
		if (new_node->key < parent->key)
			parent->left = new_node;
		else
			parent->right = new_node;
	}

	tree_size++;
	return true;
}

//*************************
// removes a node from the
// tree.
//
// @param: a const K& value
// @return1: false if the
//	     list is empty.
// @return2: true if a node
//	     can be removed.
//************************/

template <class K, class V>
bool bstree<K, V>::remove(const K& key)
{
	node<K, V>* p = root;
	node<K, V>* parent = nullptr;

	while (p != nullptr && key != p->key)
	{
		parent = p;
		if (key < p->key)
			p = p->left;
		else
			p = p->right;
	}

	if (p == nullptr)
		return false;

	node<K, V>* replace = new node<K, V>;
	node<K, V>* replace_parent = new node<K, V>;

	if (p->left == nullptr)
		replace = p->right;

	else if (p->right == nullptr)
		replace = p->left;

	else
	{
		replace_parent = p;
		replace = p->left;

		while (replace->right != nullptr)
		{
			replace_parent = replace;
			replace = replace->right;
		}

		if (replace_parent != p)
		{
			replace_parent->right = replace->left;
			replace->left = p->left;
		}

		replace->right = p->right;
	}

	if (parent == nullptr)
		root = replace;

	else
	{
		if (p->key < parent->key)
			parent->left = replace;
		else
			parent->right = replace;
	}

	delete p;
	tree_size--;
	return true;
}

//*************************
// finds a key in the list
//
// @param: a const K& value
//
// @return: the node p.
//************************/
template <class K, class V>
const node<K, V>* bstree<K, V>::find(const K& key) const
{
	node<K, V>* p = root;

	while (p != nullptr && key != p->key)
	{
		if (key < p->key)
			p = p->left;
		else
			p = p->right;
	}

	return p;
}

//*************************
// calls the preorder_traversal
// function to print a preordered
// binary tree.
//************************/

template <class K, class V>
void bstree<K, V>::preorder() const
{
	preorder_traversal(root);
}

//*************************
// traverses the tree in a
// preorder method and prints
// the list.
//
// @param: a pointer to a node
//	   to start the list.
//************************/

template <class K, class V>
void bstree<K, V>::preorder_traversal(node<K, V>* p) const
{
	if (p != nullptr)
	{
		cout << p->key << ": " << p->value << endl;
		preorder_traversal(p->left);
		preorder_traversal(p->right);
	}
}

//*************************
// calls the inorder_traversal
// function to be used in main.
//************************/

template <class K, class V>
void bstree<K, V>::inorder() const
{
	inorder_traversal(root);
}

//*************************
// traverses the tree in an
// inorder fashion and prints
// the key and value of each
// node.
//
// @param: a pointer to a node.
//************************/

template <class K, class V>
void bstree<K, V>::inorder_traversal(node<K, V>* p) const
{
	if (p != nullptr)
	{
		inorder_traversal(p->left);
		cout << p->key << ": " << p->value << endl;
		inorder_traversal(p->right);
	}
}

//*************************
// calls the postorder_traversal
// function to be used in main.
//************************/

template <class K, class V>
void bstree<K, V>::postorder() const
{
	postorder_traversal(root);
}

//*************************
// traverses the tree in a
// post order fashion and
// prints the values of the
// list.
//
// @param: a pointer to a node
//************************/

template <class K, class V>
void bstree<K, V>::postorder_traversal(node<K, V>* p) const
{
	if (p != nullptr)
	{
		postorder_traversal(p->left);
		postorder_traversal(p->right);
		cout << p->key << ": " << p->value << endl;
	}
}

//*************************
// traverses the tree in
// a level ordered fashion.
//************************/

template <class K, class V>
void bstree<K, V>::level_order() const
{
/*
	node<K, V>* root = new node<K, V>;
	node<K, V>* p = new node<K, V>;
	node<K, V>* q = new node<K, V>;

	if (root == nullptr)
		return;

	q.push(root)

	while (!q.empty())
	{
		p = q.front()
		q.pop();

		if (p->left != nullptr)
			q.push(p->left)

		if (p->right != nullptr)
			q.push(p->right)
	}
*/
}
/*
template <class K, class V>
void bstree<K, V>::level_order(node<K, V>* p) const
{

	if (root == nullptr)
		return;

	q.push(root);

	while (!q.empty())
	{
		p = q.front();
		q.pop();
		cout << p->key << ": " << p->value << endl;

		if (p->left != nullptr)
			q.push(p->left);

		if (p->right != nullptr)
			q.push(p->right);
	}

}

template <class K, class V>
void bstree<K, V>::pop()
{
	node<K, V>* del_node = left;

	left = del_node->left;


}

template <class K, class V>
void bstree<K, V>::push(const K& key)
{
	node<K, V>* new_node = new node<K, V>;

	new_node->
}
*/

//*************************
// a clone function used
// to copy nodes.
//
// @param: a const node
//	   pointer.
//************************/

template <class K, class V>
node<K, V>* bstree<K, V>::clone(const node<K, V>* p)
{
//	p = root;

	if (p != nullptr)
	{
		node<K, V>* new_node = new node<K, V>;
/*		new_node->value = this->value;
		new_node->key = this->key;
		new_node->left = this->left;
		new_node->right = this->right;
*/
		new_node->key = p->key;
		new_node->value = p->value;

		new_node->left = clone(p->left);
		new_node->right = clone(p->right);

		return new_node;
	}

	else
		return nullptr;
}
#endif /* BSTREE_H */
