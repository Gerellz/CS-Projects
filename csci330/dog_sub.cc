/*
    Gerald Ellsworth
    z1885378
    CS 330-1
    Assignment 5
    Due Date: 2/12/2021
*/

#include "dog.h"

void caesar(char buffer[], int k)
{
	int value = 0;

	for (int i = 0; buffer[i] != '\0'; ++i)
	{
		value = buffer[i];
		if (value >= 'a' && value <= 'z')
		{
			value = value + k;
			if (value > 'z')
				value = value - 'z' + 'a' - 1;
			buffer[i] = value;
		}
		else if (value >= 'A' && value <= 'Z')
		{
			value = value + k;

			if (value > 'Z')
				value = value - 'Z' + 'A' - 1;

			buffer[i] = value;
		}
	}
}
