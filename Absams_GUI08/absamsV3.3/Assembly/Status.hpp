//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Status.hpp
// Interface of the class Status.
//========================================================================  
 

//====================================================================
// class Status
// -------------------------------------------------------------------
// \brief
// The class \c Status is used to check the Error Status of a program
// during its execution.
//
// 
//
// The class \c Status defines the data type \c ?? and provides methods 
// for operations such as chkStatus, ?? and ??.
//
// <b>Example Program:</b>
//
// \include Status.t.cpp
//========================================================================  

#ifndef INCLUDED_Status_hpp
#define INCLUDED_Status_hpp

#include <stdio.h>
//#include <iostream.h>
#include <iostream>
#include <stdlib.h>

class Status
{
public:
	
// ---- Constructor and Destructor -----

	Status();
		// Default Constructor. 

	Status(int errorCode);
		// Copy Constructor. 

	~Status();
		// The default destructor.

	int chkStatus(void) const;
		// This function checks to see if any error flags have 
		// been set, and displays appropriate error messages.
		
	void setStatus(int errorCode);
		// Sets the status to the appropriate error code

private:
	int errorNumber;
		// Uniquely identifies the error code
};

#endif // INCLUDED_Status_hpp