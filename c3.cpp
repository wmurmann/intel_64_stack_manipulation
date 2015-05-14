// Author:  William Murmann
// Email:   wmurmann@gmail.com
// Course:  CPSC 240
// Assignment:  7
// Due date:   May 14th, 2015

// Name of this file:  c2.cpp

// GNU compiler:  g++ -c -m64 -Wall -l c2.lis -o c2.o c2.cpp

// Purpose:  This is subprogram number 3 out of 6 designed for the 
//           purpose of investigating the role of the system stack in process of calling subprograms.
#include <stdio.h>
#include <stdint.h>
#include <ctime>
#include <cstring>
#include <iostream>


extern "C" long c3(long c2);

extern "C" long c4(long  c3);

extern "C" long c3(long  c2){
	
	long int1 =  -16;
	long int3 = c2 + int1;
	long c4_long = c4(int3);
	
	std:: cout << int1 << std::endl;
	std:: cout << c2 << std::endl;
	std:: cout << int3 << std::endl;
	std:: cout << c4_long << std::endl;

	return c4_long;
}