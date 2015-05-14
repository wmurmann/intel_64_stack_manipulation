// Author:  William Murmann
// Email:   wmurmann@gmail.com
// Course:  CPSC 240
// Assignment:  7
// Due date:   May 14th, 2015

// Name of this file:  c2.cpp

// GNU compiler:  g++ -c -m64 -Wall -l c2.lis -o c2.o c2.cpp

// Purpose:  This is subprogram number 4 out of 6 designed for the 
//			 purpose of investigating the role of the system stack in process of calling subprograms.
#include <stdio.h>
#include <stdint.h>
#include <ctime>
#include <cstring>
#include <iostream>

extern "C" long c4(long c3);

extern "C" long c5(long  c4);

extern "C" long c4(long  c3){
	
	long int1 = 13;
	long int3 = c3 - int1;
	long c5_long = c5(int3);
	std:: cout << c3 << std::endl;
	std:: cout << int1 << std::endl;
	std:: cout << int3 << std::endl;
	std:: cout << c5_long << std::endl;

	return c5_long;
}