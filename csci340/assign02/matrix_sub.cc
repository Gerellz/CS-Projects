/* 	Gerald Ellsworth
	Z1885378
	CS 340.1
	
	I certify that this is my own work and where appropriate an extension 
	of the starter code provided for the assignment.
*/

#include "matrix.h"

void open_files(ifstream &is1, ifstream &is2)
{
    is1.open(FILE1);                                            // Opening the files using the assigned variable for the path.
    is2.open(FILE2);

    if (!is1.is_open())                                         // If either is NOT open after we call to open, we print an error
    {                                                           // and exit the program.
        cerr << "Error Opening File 1." << endl;
        exit(1);
    }

    if (!is2.is_open())
    {
        cerr << "Error Opening File 2." << endl;
        exit(2);
    }
}

void read_data(ifstream &is, vector<vector<int>> &m)
{
    vector <int> v1;                                            // Added a bunch of variables to fix bug issues.
    int tmp;                                                    
    int row = 0;                                                // When row and col were not initialized, the matrices
    int col = 0;                                                // Would bug out and fill with 0's.
    int r = m.size() - 1;
    int c = m[0].size() - 1;

    while(is >> tmp)                                            // While loop continuing while the file is being read into the variable tmp
    {                                                            
        if (row > r)                                            // If the row number is greater than the size of the vector m
            return;                                             // We return and end because that would mean we're exceeding the size given.

        m[row][col] = tmp;                                      // Starting at the first index [0][0] we input the first file integer.
        ++col;                                                  // Increment to the next column and continue to input tmp.

        if (col > c)                                            // If the column that we're on is greater than the size of the vector
        {                                                       // Increment the row and continue on the first column of the new row.
            ++row;
            col = 0;
        }
    }
}

void print_data(const vector<vector<int>> &m)
{
    vector<int>::size_type row_size = m.size();                                             // Set these variables to vector<int>::size_type to avoid warnings
    vector<int>::size_type col_size = m[0].size();                                          // when comparing against vectors.

    cout << row_size << " x " << col_size << endl                                           // Print the Matrix row size by the column size.
    << "----------------------------------------------------------------------" << endl;

    for (vector<int>::size_type i = 0; i < row_size; i++)                                   // Loop to print both the rows and the columns of
    {                                                                                       // the matrices.
        for (vector<int>::size_type j = 0; j < m[i].size(); j++)
        {
            cout << setw(ITEM_W) << m[i][j];
        }
        cout << endl;
    }
}

void gen_data(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C)
{
    for (vector<int>::size_type i = 0; i < A.size(); i++)                                           // Longer loop that takes the integers
    {                                                                                               // from the rows and columns of matrices A & B
        for (vector<int>::size_type j = 0; j < B[i].size(); j++)                                    // so they can be multiplied into matrix C.
        {
            for (vector<int>::size_type k = 0; k < A[i].size(); k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}
