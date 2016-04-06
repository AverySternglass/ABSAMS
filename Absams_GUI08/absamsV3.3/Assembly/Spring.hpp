//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// ----------------------------------------------------------------------  
// File: Spring.hpp
// Interface of the class Spring.
//========================================================================  
 

#ifndef INCLUDED_Spring_hpp
#define INCLUDED_Spring_hpp

#include "Bricks.hpp"
//====================================================================
// class Spring
// -------------------------------------------------------------------
// \brief
// The class \c Spring is derived from the SpringBase class to describe 
// the connective tissue in the MH Unit. It presently describes a linear 
// spring.
// 
// 
//
// The class \c Spring defines the data type \c Spring and provides methods 
// for operations such as ??, ?? and ??.
//
// <b>Example Program:</b>
//
// \include Spring.t.cpp
//========================================================================  


class Spring : public SpringBase
{
	
public:
	
// ---- Constructor and Destructor -----

	Spring(int springNumber, Node *startNode, Node *endNode);
		// Copy Constructor. 

	Spring(int springNumber, Node *startNode, Node *endNode, 
		double stiffness, double damping);
		// Copy Constructor. 

	Spring(int springNumber, Node *startNode, Node *endNode, 
		double stiffness, double damping, double restingLength);
		// Copy Constructor. 

// ---- Member Functions ----- 

	virtual void updateSpring(void) ;
		// This function calculates the force exerted by the spring
		// on the nodes. 
	
	virtual void writeMHAFile(FILE *mhaFilePtr) const;
		// Writes relavant Spring data to the specified file
	
	
	virtual void display(void) const;
		// Displays the Spring in OpenGL window. If OpenGL is 
		// not available, error is printed.

	virtual void display(double red, double green, double blue) const;
		// Displays the Spring in OpenGL window in the specified color.
		// If OpenGL is not available, error is printed.
		
private:
	
	const double c_stiffness;
		// Linear spring constant describing the poition-force 
		// relationship
	
	const double c_damping;
		// Damping factor of the inherent damping in the spring 

};



#endif // INCLUDED_Spring_hpp