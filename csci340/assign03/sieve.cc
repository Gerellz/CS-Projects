/*	Gerald Ellsworth
	z1885378
	CS340.1
	2/7/2021
	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment.
*/

#include <iostream>
#include <iomanip>
#include <set>

using std::set;											// Included a few usings just to clean up code
using std::cout;
using std::endl;

#define NO_ITEMS 12										// Created some defines for constants
#define ITEM_W 5										// that will be used for printing.


//**********************************************
// Function that creates a set container
// and fills it with all numbers from 2-5000.
//
// Parameter 1: A reference to the set container
//		to be filled.
// Parameter 2: the number of values to be
//		stored in the set.
//**********************************************

void sieve(set<int>& s, int n)
{
	std::cin >> n;
 	int m = 2;

	for (int m = 2; m < n; ++m)							// For loop that inserts values from 2 to 5000
	{													// into the set container.
		s.insert(m);
	}

	while (m * m <= n)									// While the square of m is less than 5000
	{													// we multiply m to erase any value that
		for (int k = 2; k < n; ++k)						// we get (because if we find a number,
		{												// that means it is not a prime number)!
			int np = m * k;
			s.erase(np);
		}
		++m;
	}
}

//**********************************************
// Function that prints the prime numbers
// with correct spacing and numbers per line.
//
// Parameter 1: A reference to the set container
//		that we created.
//**********************************************

void print_primes(const set<int>& s)
{
	int j = 0;
	cout << "\n";

	for (auto i : s)									// Range based loop that travels through
	{													// all values i in the set s.
		cout << std::setw(ITEM_W) << i;

		if ((j + 1) % NO_ITEMS == 0)					// We move to a new line every time j
			cout << endl;								// hits a value divisible by 12.
		++j;											// Increment j each time the for loop
	}													// completes, essentially assigning
	if ((j + 1) % NO_ITEMS != 0)						// every i value to its own j value.
		cout << endl;
}

int
main()
{
	set<int> s;
	int n;
	cout << "Upper limit for the set of primes: ";
	sieve(s, n);
	print_primes(s);
	return 0;
}
