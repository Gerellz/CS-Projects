#include <iostream>
#include "mystack.h"

using namespace std;

int main()
{

	char letters[] = "abcdefghijklmnopqrstuvwxyz";
	const mystack s1;

	cout << "Default constructor\n\n";


	cout << "Testing empty():          ";
	cout << ((s1.empty()) ? "SUCCESS\n" : "failure\n");
	cout << "Testing capacity():       ";
	cout << ((s1.capacity() == 0) ? "SUCCESS\n" : "failure\n");
	cout << "Testing size():           ";
	cout << ((s1.size() == 0) ? "SUCCESS\n" : "failure\n");

	cout << "\npush(), top(), and pop()\n\n";

	mystack s2;
	size_t i;

	bool correct = true;
	for (i = 0; i < 10; i++)
	{
		s2.push(letters[i]);
		if (letters[i] != s2.top())
			correct = false;
		if (s2.size() != i+1)
			correct = false;
	}

	cout << "Testing push() and top(): ";
	cout << ((correct) ? "SUCCESS\n" : "failure\n");
	cout << "Testing empty():          ";
	cout << ((!s2.empty()) ? "SUCCESS\n" : "failure\n");
	cout << "Testing capacity():       ";
	cout << ((s2.capacity() == 16) ? "SUCCESS\n" : "failure\n");
	cout << "Testing size():           ";
	cout << ((s2.size() == 10) ? "SUCCESS\n" : "failure\n");
	cout << "Testing top():            ";
	cout << ((s2.top()== letters[9]) ? "SUCCESS\n" : "failure\n");

	correct = true;
	for (i = 10; letters[i]; i++)
	{
		s2.push(letters[i]);
		if (letters[i] != s2.top())
			correct = false;
	}

	cout << "Testing push() and top(): ";
	cout << ((correct) ? "SUCCESS\n" : "failure\n");
	cout << "Testing empty():          ";
	cout << ((!s2.empty()) ? "SUCCESS\n" : "failure\n");
	cout << "Testing capacity():       ";
	cout << ((s2.capacity() == 32) ? "SUCCESS\n" : "failure\n");
	cout << "Testing size():           ";
	cout << ((s2.size() == 26) ? "SUCCESS\n" : "failure\n");
	cout << "Testing top():            ";
	cout << ((s2.top() == letters[25]) ? "SUCCESS\n" : "failure\n");


	mystack s3(s2);

	correct = true;
	for (i = 25; !s2.empty(); i--)
	{
		if (letters[i] != s2.top())
			correct = false;

		s2.pop();
	}

	cout << "Testing top() and pop():  ";
	cout << ((correct) ? "SUCCESS\n" : "failure\n");

	cout << "\nCopy Constructor\n\n";

	cout << "Testing empty():          ";
	cout << ((!s3.empty()) ? "SUCCESS\n" : "failure\n");
	cout << "Testing capacity():       ";
	cout << ((s3.capacity() == 32) ? "SUCCESS\n" : "failure\n");
	cout << "Testing size():           ";
	cout << ((s3.size() == 26) ? "SUCCESS\n" : "failure\n");
	cout << "Testing top():            ";
	cout << ((s3.top() == letters[25]) ? "SUCCESS\n" : "failure\n");
}
