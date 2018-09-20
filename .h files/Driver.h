/* Eric Ngo
 * May 22, 2018
 * File Name: Driver.h
 * File Description: Driver.h is the driver to run and test the Tree.c
 *					 file and it also contains the UCSDStudent class. The
 *					 functionality of the Tree structure is tested and when
 *					 ^D is entered the program ends.
 
 */
#ifndef DRIVER_H
#define DRIVER_H

#include <string.h>
#include <iostream>
#include <cstdlib>
using namespace std;


/*============================================================================
 * class UCSDStudent
 *
 * Description: Implements the UCSDStudent that will be used to represent
 *				the elements being input into the tree structure. Each
 *				UCSDStudent entered in has a name and a value assigned to
 *				it.
 * 
 * Data Fields: char name - the name of the UCSDStudent
 *				long studentnum - the value assigned with the UCSDStudent
 *
 * Public Functions: ostream & operator << - writes out the data fields of the
 *									         UCSDStudent to the stream
 *					 const char * - operator overload to return the name of 
 *								    the UCSDStudent
 *					 == - operator overload to do equality check of 2 
 *						  UCSDStudents
 *					 > - operator overload to check which of 2
 *						 UCSDStudents are greater
 ===========================================================================*/
class UCSDStudent {
	//operator to print to ostream
    friend ostream & operator << (ostream &, const UCSDStudent &);

	//name of UCSDStudent
    char name[20];

	//value of UCSDStudent
    long studentnum;

public:

/***************************************************************************
% Routine Name : UCSDStudent (public)
% File :         Driver.c
% 
% Description :  Constructor to create a new UCSDStudent
%
%
% name               description
% --------------------------------------------------------------------------
% nm				the name of the UCSDStudent
% val				the value assigned to the UCSDStudent
% <return>			nothing
***************************************************************************/
	UCSDStudent (char * nm, long val = 0) : studentnum (val) {
		strcpy (name, nm);
	}


/***************************************************************************
% Routine Name : const char * (public)
% File :         Driver.c
% 
% Description :  overloads the char * cast to return the name of the 
%				 UCSDStudent
***************************************************************************/
	operator const char * (void) const {
		return name;
	}


/***************************************************************************
% Routine Name : == (public)
% File :         Driver.c
% 
% Description :  overloads the == operator to do an equality check on one 
%				 base and another				
***************************************************************************/
	long operator == (const UCSDStudent & stu) const {
		return ! strcmp (name, stu.name);
	}


/***************************************************************************
% Routine Name : > (public)
% File :         Driver.c
% 
% Description :  overloads the > operator to compare if one base is greater
%				 than another base
***************************************************************************/
	long operator > (const UCSDStudent & stu) const {
		return (strcmp (name , stu.name) > 0 ) ? 1 : 0;
	}	
};

#endif
