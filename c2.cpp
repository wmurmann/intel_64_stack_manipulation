// Author:  William Murmann
// Email:   wmurmann@gmail.com
// Course:  CPSC 240
// Assignment:  7
// Due date:   May 14th, 2015

// Name of this file:  c2.cpp

// GNU compiler:  g++ -c -m64 -Wall -l c2.lis -o c2.o c2.cpp

// Purpose:  This is subprogram number 2 out of 6 designed for the purpose of investigating the role of the system stack in process of calling subprograms.
#include <stdio.h>
#include <stdint.h>
#include <ctime>
#include <cstring>
#include <iostream>

extern "C" long c2();

extern "C" long c3(long  c2);

extern "C" long c2(){

	long int1 = -4;
	long ptr_val = -1;
	long * ptr = &ptr_val;
	long int2 = 7;

	std:: cout << int1 << std::endl;
	std:: cout << *ptr << std::endl;
	std:: cout << int2 << std::endl;

	long c3_long = c3(int1);

	std:: cout << int1 << std::endl;
	std:: cout << *ptr << std::endl;
	std:: cout << int2 << std::endl;

	std:: cout << c3_long << std::endl;

	return c3_long;

}