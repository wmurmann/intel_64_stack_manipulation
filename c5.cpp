// Author:  William Murmann
// Email:   wmurmann@gmail.com
// Course:  CPSC 240
// Assignment:  7
// Due date:   May 14th, 2015

// Name of this file:  c2.cpp

// GNU compiler:  g++ -c -m64 -Wall -l c2.lis -o c2.o c2.cpp

// Purpose:  This is subprogram number 5 out of 6 designed for the purpose of investigating the role of the system stack in process of calling subprograms.
#include <stdio.h>
#include <stdint.h>
#include <ctime>
#include <cstring>
#include <iostream>

//extern "C" double findframe();
extern "C" long findframe();

extern "C" long c5(long c4);

extern "C" long c5(long c4){
	
	findframe();
	//Calls findframe and passes nothing to findframe.
	//Receives a long from findframe.
	long findframe_temp = 1.0;
	std:: cout << c4 << std::endl;
	return c4 + findframe_temp;
}