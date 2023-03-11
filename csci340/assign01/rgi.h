/*  Gerald Ellsworth
    Z1885378
    CS340.1

    I certify that this is my own work and where appropriate an extension
    of the starter code provided for the assignment.
*/

#ifndef H_RGI // should not be defined any place else 
#define H_RGI // same const value as for ifndef directive

#include <iostream> // Add minimal needed header files here ..
#include <iomanip>
#include <vector>
#include <algorithm>

using std::vector;
using std::cout;
using std::endl;

// You need to declare these two functions ...
void genRndNums(vector<int> &v, int num);                   // void genRndNums(vector<int> &v, int num);
void printVec(const vector<int> &v);                        // void printVec(const vector<int> &v);

#endif
