//***************************************
//
// scc.cpp
//
// CSCI 241 Assignment 9
//
// Written by Gerald Ellsworth (z1885378)
//
//**************************************/

#include "sml.h"
#include "inpost.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>

using std::cin;
using std::istringstream;
using std::string;
using std::endl;
using std::cout;
using std::islower;
using std::isdigit;
using std::showpos;
using std::noshowpos;

//**
//*
//* Symbol table entry.
//*
//********************************************************************/

struct table_entry
{
    int symbol;
    char type;      // 'C' constant, 'L' Simple line number, 'V' variable
    int location;   // Simplesim address
};

//**
//*
//*
//*
//*******************************************/

class scc
{
public:
        static const int MEMORY_SIZE = 100;
        static const int SYMBOL_TABLE_SIZE = 1000;

        scc();
        void first_pass();
        void second_pass();
        void print_program() const;
        void data_check() const;
        void memory_check() const;

private:
        int memory[MEMORY_SIZE];
        int data[MEMORY_SIZE];
        int ndata = 0;

        table_entry symbol_table[SYMBOL_TABLE_SIZE];
        int flags[MEMORY_SIZE];

	int next_instruction_addr = 0;
	int next_const_or_var_addr = MEMORY_SIZE - 1;
	int next_symbol_table_idx = 0;

	void handle_end();
	void handle_data(istringstream&);
	void handle_input(istringstream&);
	void handle_print(istringstream&);
	int get_symbol_location(const string&);
	int search_symbol_table(int, char);
};

int main()
{
    scc compiler;

    compiler.first_pass();

    compiler.second_pass();

    compiler.print_program();

    return 0;
}

//**
//* Initializes memory and flags array.
//*
//********************************************************************/

scc::scc()
{
	for (int i = 0; i < MEMORY_SIZE; i++)
	{
		memory[i] = 7777;
		flags[i] = -1;
	}
}

//**
//* Performs first pass of compilation.
//*
//********************************************************************/

void scc::first_pass()
{
    string buffer1, buffer2, command;

    int line_number;

    while (getline(cin, buffer1))
    {
        buffer2 = buffer1;
        istringstream ss(buffer1);

        ss >> line_number;

        // Code to add line number to symbol table.
	symbol_table[next_symbol_table_idx].symbol = line_number;
	symbol_table[next_symbol_table_idx].type = 'L';
	symbol_table[next_symbol_table_idx].location = next_instruction_addr;
	next_symbol_table_idx++;

        // Extract the command from this statement.
        ss >> command;

        // Process the command.
        if (command == "input")
        {
		handle_input(ss);
        }
        else if (command == "data")
        {
		handle_data(ss);
        }
        else if (command == "let")
        {

        }
        else if (command == "if")
        {

        }
        else if (command == "goto")
        {

        }
        else if (command == "print")
        {
		handle_print(ss);
        }
        else if (command == "end")
        {
		handle_end();
        }
        else // if (command == "rem")
        {
            // Nothing to do for this instruction.
        }
    }
}

//**
//* Performs second pass of compilation.
//*
//********************************************************************/
void scc::second_pass()
{

}

//**
//* Prints memory and data for the compiled SML program.
//*
//********************************************************************/

void scc::print_program() const
{
	cout << showpos;
	// Print entire memory array followed by data array.
	for (int i = 0; i < MEMORY_SIZE; i++)
		cout << memory[i] << endl;

	//print end of instructions sentinel value.
	cout << -99999 << endl;

	cout << noshowpos;
	//print data values.
	for (int i = 0; i < ndata; i++)
		cout << data[i] << endl;
}

//**
//
//
//
//
//****************/

void scc::data_check() const
{
	if (ndata >= MEMORY_SIZE)
	{
		cout << "*** ERROR: Too many data lines ***\n";
		exit(1);
	}
}

//**
// checks memory array to add instruction.
//
//
//
//********************/

void scc::memory_check() const
{
	if(next_instruction_addr >= MEMORY_SIZE || next_instruction_addr > next_const_or_var_addr)
	{
		cout << "*** ERROR: ran out of Simplesim memory ***\n";
		exit(1);
	}
}

void scc::handle_end()
{
	memory_check();

	memory[next_instruction_addr] = HALT * 100;

	next_instruction_addr++;
}

void scc::handle_data(istringstream& ss)
{
	int token;

	ss >> token;
	data_check();
	data[ndata] = token;
	ndata++;
}

void scc::handle_input(istringstream& ss)
{
	string token;
	int location;

	ss >> token;

	location = get_symbol_location(token);

	memory_check();
	memory[next_instruction_addr] = READ * 100 + location;
	next_instruction_addr++;
}

void scc::handle_print(istringstream& ss)
{
	string token;
	int location;

	ss >> token;

	location = get_symbol_location(token);

	memory_check();
	memory[next_instruction_addr] = WRITE * 100 + location;
	next_instruction_addr++;
}

int scc::get_symbol_location(const string& token)
{
	int location, symbol;
	char type;

	if (islower(token[0]))
	{
		symbol = token[0];
		type = 'V'; //could be a constant
	}
	else
		type = 'C';

	int index = search_symbol_table(symbol, type);

	if (index == -1)
	{
		// TODO add this symbol to the symbol table
		symbol_table[next_symbol_table_idx].symbol = symbol; //set symbol_table[next_symbol_table_idx].symbol to the symbol.
		symbol_table[next_symbol_table_idx].type = type; // set symbol_table[next_symbol_table_idx].type to the symbol's type.
		symbol_table[next_symbol_table_idx].location = next_const_or_var_addr; // set symbol_table[next_symbol_table_idx].location to the next_const_or_var_addr.
		// save that location so it can be returned at the end of the function.
		next_symbol_table_idx++; // increment next_symbol_table_idx.

		memory[next_const_or_var_addr] = 0;//TODO - allocate memory for the variable and set memory[next_const_or_var_addr] to 0
		//else it is a constant, so set memory[next_const_or_var_addr] to that constant.
		//location of this symbol is next_const_or_var_addr
		next_const_or_var_addr--; //Decrement next_const_or_var_addr.
	}

	else
		return symbol_table[index].location;
}

int scc::search_symbol_table(int symbol, char type)
{
	for (int i = 0; i < next_symbol_table_idx; i++)
	{
		if (symbol == symbol_table[i].symbol && type == symbol_table[i].type)
			return i;
	}

	return -1;
}
