// Author:  William Murmann
// Email:   wmurmann@gmail.com
// Course:  CPSC 240
// Assignment:  7
// Due date:   May 14th, 2015

// Name of this file:  c2.cpp

// GNU compiler:  g++ -c -m64 -Wall -l c1.lis -o c1.o c1.cpp 
//  Gnu linker:   g++ -m64 -o harmonic.out driver.o harmonic.o debug.o
// Purpose:  This is subprogram number 2 out of 6 designed for the purpose of investigating 
//            the role of the system stack in process of calling subprograms.

//===== Begin code area ===================================================================================================================================================

#include <stdio.h>
#include <stdint.h>
#include <ctime>
#include <cstring>
#include <iostream>

extern "C" long c2();

int main(){

  long int1 = 3;
  long int2 = 8;
  std:: cout << int1 << std::endl;
  std:: cout << int2 << std::endl;
  long c2_long = c2();
  std:: cout << int1 << std::endl;
  std:: cout << int2 << std::endl;

  std:: cout << c2_long << std::endl;
  
  return 0;

}//End of main
//=======1=========2=========3=========4=========5=========6=========7=========8=========9=========0=========1=========2=========3=========4=========5=========6=========7**

  //return_code = harmonic_calc ();