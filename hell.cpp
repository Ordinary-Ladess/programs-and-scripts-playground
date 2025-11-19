#include <stdio.h>

//This weird program compiles fine with:
//gcc version 4.7.2 (Debian 4.7.2-5) 
//
//Though, there's a segfault upon exit because
//the call to main isn't a function.
//if main were called as a function despite 
//being an object, then the program would run twice

class PROGRAM
{
 public:
   PROGRAM()
     {

	//int myfavvar[255];
	printf("\nInsert an int number here:");
	//fgets(myfavvar,254,stdin);
	gets(myfavvar);
	printf("%s",myfavvar);
	printf("\nAnother?:");
	//fgets(myfavvar,254,stdin);
	gets(myfavvar);
	printf("%s",myfavvar);
	printf("\nThis Actually Worked!\n");
     }
   
   ~PROGRAM()
     {
	//we never make it here!!
     }
   
 private:
   char myfavvar[255];
};
//maybe  -std=c++11 -g -O0 -fverbose-asm is needed?
PROGRAM main;