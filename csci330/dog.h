/*
    Gerald Ellsworth
    z1885378
    CS 330-1
    Assignment 5
    Due Date: 2/12/2021
*/

#ifndef DOG_H
#define DOG_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string.h>

using std::endl;
using std::cerr;

void caesar(char[], int);
void binRotate(char[], int);
void binary(char[], int);
void hex(char[], int);

#endif
