//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Vector.hpp
// Interface of the class Vector.
//========================================================================  
 

//====================================================================
// class Vector
// -------------------------------------------------------------------
// \brief
// The class \c Vector describes a simple vector of doubles in 3-D space
// 
//
// 
//
// The class \c Vector defines the data type \c Vector and provides methods 
// for operations such as ??, ?? and ??.
//
// <b>Example Program:</b>
//
// \include Vector.t.cpp
//========================================================================  

#ifndef INCLUDED_Vector_hpp
#define INCLUDED_Vector_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

//xg
using namespace std;

class Vector
{
public:
	
// ---- Constructor and Destructor -----

	Vector();
		// Default Constructor. 

	Vector(double initX, double initY, double initZ);
		// Copy Constructor. 

	~Vector();
		// The default destructor.

	double getX(void) const;
		// This function provides access to the X component of the vector.
		//  return		X component of the vector
		
	double getY(void) const;
		// This function provides access to the Y component of the vector.
		//  return		Y component of the vector
	
	double getZ(void) const;
		// This function provides access to the Z component of the vector.
		//  return		Z component of the vector

	void setX(double xComponent);
		// This function provides access to the X component of the vector.
		//  xComponent		X component of the vector
		
	void setY(double yComponent);
		// This function provides access to the Y component of the vector.
		//  yComponent		Y component of the vector
	
	void setZ(double zComponent);
		// This function provides access to the Z component of the vector.
		//  zComponent		Z component of the vector
	
	Vector operator=(const Vector &source);
		// This function overloads the assignment operator 
		// to assign one Vector to another.
		//  source		The source vector for the assignment.

	Vector operator+(const Vector &source);
		// This function overloads the addition operator 
		// to add one Vector to another.
		//  source		The source vector for the addition.

	Vector operator-(const Vector &source);
		// This function overloads the subtraction operator 
		// to subtract one Vector from another.
		//  source		The source vector for the subtraction.

	Vector operator*(const double &scalar);
		// Overloading binary multiplication operator to 
		// pre-multiply a vector with a scalar.
		//  scalar		The source scalar for scalar multiplication.

	Vector operator/(const double &scalar);
		// Overloading division operator to divide a a vector by a scalar.
		//  scalar		The source scalar for scalar division.

	Vector crossProduct(Vector vect) const;
		// Computes the cross product of the vector with another Vector
		// i.e., this vector X given vector
		//  returns		The cross product result

	double dotProduct(Vector vect) const;
		// Computes the dot product of the vector with another Vector
		// i.e., this vector . given vector
		//  returns		The dot product result

	Vector normalize(void) const;
		// Computes the unit vector corresponding to the direction 
		// of the vector by normalizing the vector
		//  returns		Unit vector in the direction of the vector


	void operator+=(const Vector &source);
		// Defining the += operator to mean addition followed by assignment
		// like in scalars.
		//  source		The source vector to be added.

	void operator-=(const Vector &source);
		// Defining the -= operator to mean subtraction followed by assignment
		// like in scalars.
		//  source		The source vector to be subtracted.

	bool operator==(const Vector &source);
		// Defining the == operator to mean comparison of vectors
		//  source		The source vector to be compared
		//  return		true if the vectors are the same
	
	bool operator!=(const Vector &source);
		// Defining the != operator to mean comparison of vectors
		//  source		The source vector to be compared
		//  return		false if the vectors are the same
	
	void display(void) const;
		// Displays the Vector in OpenGL window w.r.t the CURRENT
		// frame of reference. If OpenGL is not available, error is printed.

	void display(double red, double green, double blue) const;
		// Displays the Vector in OpenGL window in the specified color.
		// If OpenGL is not available, error is printed.

	friend ostream &operator<<(ostream &output, const Vector &vector);
		// This function overloads the ostream \c << operator
		// to output the elements of the Vector \a vector to the output stream
 		// separated by white spaces(e.g. spaces).
		// Example: \code cout << vector; \endcode


private:
	double magnitudeI;
		// The X component of the vector in the global frame of reference

	double magnitudeJ;
		// The Y component of the vector in the global frame of reference

	double magnitudeK;
		// The Z component of the vector in the global frame of reference
		
};


Vector operator*(const int &scalar, const Vector &vect);

Vector operator*(const double &scalar, const Vector &vect);

#endif // INCLUDED_Vector_hpp