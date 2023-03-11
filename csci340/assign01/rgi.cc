/*  Gerald Ellsworth
    Z1885378
    CS340.1

    I certify that this is my own work and where appropriate an extension
    of the starter code provided for the assignment.
*/

#include "rgi.h"

const int SEED = 2021;                                               // Constants necessary for the functions.
const int LOW = 1;
const int HIGH = 999;
const int VEC_SIZE = 250;
const int NO_ITEMS = 10;
const int ITEM_W = 4;

//********************************************************
// Function designed to generate random numbers
// into the vector.
//
// @parameter 1: the vector being used.
// @parameter 2: the number of values put into the vector.
//********************************************************

void genRndNums(vector<int> &v, int num)
{
    std::srand(SEED);                                               // Using a seed value of 2021 to obtain the correct values.

    for (int i = 0; i < num; i++)                                   // For loop to push the values to the end of vector v.
        v.push_back(rand() % HIGH + LOW);                           // We use the function rand() with values between 1 and 999.
//      v[i] = rand() % (HIGH - LOW + 1) + LOW;
}

//******************************************************
// Function designed to print the contents of the vector.
//
// @parameter 1: the vector to be displayed.
//******************************************************

void printVec(const vector<int> &v)
{
    int i;

    for (i = 0; i < VEC_SIZE; i++)                                  // For loop intended to print the contents of vector v.
    {
        cout << std::setw(ITEM_W) << v[i];

        if ((i + 1) % NO_ITEMS == 0)                                // If we print 10 values, end the line and continue printing on the next line.
            cout << endl;
    }

    if (i % NO_ITEMS != 0)                                          // If there are less than 10 values to be printed, end the line and stop.
         cout << endl;

}

int main()
{
    vector<int> v;                                                  // Declaration of vector v.

    genRndNums(v, VEC_SIZE);                                        // Calls the function genRndNums with v as the vector and VEC_SIZE as the number of values to be used.	

    std::sort(v.begin(), v.end());                                  // Sorts the values of vector v starting with the first value and ending with the last in ascending order.
	
    printVec(v);                                                    // Calls the function printVec to print the contents of vector v.

        return 1;
}
