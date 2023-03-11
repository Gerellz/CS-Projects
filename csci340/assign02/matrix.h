#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

using namespace std;

#ifndef H_MATRIX_MULTIPLY
#define H_MATRIX_MULTIPLY

// data files
constexpr char FILE1[] = "./matrix01.dat";
constexpr char FILE2[] = "./matrix02.dat";

#define ITEM_W 8 // no of spaces for each printed number

// to open two data files
void open_files(ifstream&, ifstream&);

// to read contents of two data files
void read_data(ifstream&, vector <vector <int> >&);

// to print contents of all matrices
void print_data(const vector <vector<int> >&);

// to generate a matrix by multiplying two input matrices
void gen_data(const vector <vector<int> >&,
    			const vector <vector<int> >&,
    			vector <vector<int> >&);

#endif
