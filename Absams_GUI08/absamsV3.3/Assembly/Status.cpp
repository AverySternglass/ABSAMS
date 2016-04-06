//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Status.cpp
// Implementation of the class Status.
//========================================================================  
 
#include "Status.hpp"
//xg
using namespace std;

//============================================================
// Status::Status
//============================================================

Status :: Status() {}
	// Default Constructor



//============================================================
// Status::Status
//============================================================

Status :: Status(int errorCode) 
	// Copy Constructor
{
	errorNumber = errorCode;
}
	



//============================================================
// Status::~Status
//============================================================

Status :: ~Status() {}
	// Default Destructor



//============================================================
// Status::setStatus
//============================================================

void Status :: setStatus(int errorCode)
{
	errorNumber = errorCode;
}

//============================================================
// Status::chkStatus
//============================================================

int Status :: chkStatus(void) const
{
	switch (errorNumber)
	{
		case 0: break;
			// No error condition

		case 1: 
			cout << "Error Allocating Memory" << endl;
			break;

		case 2: 
			cout << "Error: List Element not present" << endl;
			break;
		case 3: 
			cout << "Error: File open Failed" << endl;
			break;
	}
	return(errorNumber);
}
