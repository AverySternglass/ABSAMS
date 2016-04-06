//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Vector.cpp
// Implementation of the class Vector.
//========================================================================  
 

#include "Vector.hpp"
#include "Globals.h"

//xg
using namespace std;

//============================================================
// Vector::Vector
//============================================================

Vector :: Vector() {}
	// Default Constructor


//============================================================
// Vector::Vector
//============================================================

Vector ::Vector(double initX, double initY, double initZ)
	// Copy Constructor. 
{
	magnitudeI = initX;
	magnitudeJ = initY;
	magnitudeK = initZ;
}
	

//============================================================
// Vector::~Vector
//============================================================

Vector :: ~Vector() {}
	// Default Destructor


//============================================================
// Vector::getX
//============================================================

double Vector::getX(void) const
	// gets the X component of the vector
{
	return magnitudeI;
}


//============================================================
// Vector::getY
//============================================================

double Vector::getY(void) const
	// gets the Y component of the vector
{
	return magnitudeJ;
}


//============================================================
// Vector::getZ
//============================================================

double Vector::getZ(void) const
	// gets the Z component of the vector
{
	return magnitudeK;
}


//============================================================
// Vector::setX
//============================================================

void Vector::setX(double xComponent)
	// sets the X component of the vector
{
	magnitudeI = xComponent;
}


//============================================================
// Vector::setY
//============================================================

void Vector::setY(double yComponent)
	// sets the Y component of the vector
{
	magnitudeJ = yComponent;
}


//============================================================
// Vector::setZ
//============================================================

void Vector::setZ(double zComponent)
	// sets the Z component of the vector
{
	magnitudeK = zComponent;
}


//============================================================
// Vector::operator=
//============================================================

Vector Vector ::operator=(const Vector &source)
	// Overloading the = operator to assign a Vector to another
{
	magnitudeI = source.magnitudeI;
	magnitudeJ = source.magnitudeJ;
	magnitudeK = source.magnitudeK;
	
	return *this;	
}


//============================================================
// Vector::operator+
//============================================================

Vector Vector ::operator+(const Vector &source)
	// Overloading the + operator to add one Vector to another
{
	Vector result;
	result.setX(magnitudeI + source.magnitudeI);
	result.setY(magnitudeJ + source.magnitudeJ);
	result.setZ(magnitudeK + source.magnitudeK);
	
	return result;	
}


//============================================================
// Vector::operator-
//============================================================

Vector Vector ::operator-(const Vector &source)
	// Overloading the - operator to subtract one Vector from another
{
	Vector result;
	result.setX(magnitudeI - source.magnitudeI);
	result.setY(magnitudeJ - source.magnitudeJ);
	result.setZ(magnitudeK - source.magnitudeK);
	
	return result;
}


//============================================================
// Vector::operator+=
//============================================================

void Vector ::operator+=(const Vector &source)
	// Overloading the += operator to mean addition folowed by assignment
{
	this->setX(magnitudeI + source.magnitudeI);
	this->setY(magnitudeJ + source.magnitudeJ);
	this->setZ(magnitudeK + source.magnitudeK);
}



//============================================================
// Vector::operator-=
//============================================================

void Vector ::operator-=(const Vector &source)
	// Overloading the -= operator to mean subtraction followed by assignment
{
	this->setX(magnitudeI - source.magnitudeI);
	this->setY(magnitudeJ - source.magnitudeJ);
	this->setZ(magnitudeK - source.magnitudeK);
}



//============================================================
// Vector::operator==
//============================================================

bool Vector ::operator==(const Vector &source)
	// Overloading the == operator for comparison
{
	if(magnitudeI == source.getX() &&
		magnitudeJ == source.getY() &&
		magnitudeK == source.getZ()) return true;
	else return false;
}




//============================================================
// Vector::operator!=
//============================================================

bool Vector ::operator!=(const Vector &source)
	// Overloading the != operator for comparison
{
	if(magnitudeI == source.getX() &&
		magnitudeJ == source.getY() &&
		magnitudeK == source.getZ()) return false;
	else return true;
}



//======================================================================== 
// Vector::operator*
//========================================================================  


Vector Vector::operator*(const double &scalar)
	// Overloading the * operator for post-multiplication of a Vector with a scalar.
{
	Vector scalarProduct;
	
	scalarProduct.setX(magnitudeI*scalar);
	scalarProduct.setY(magnitudeJ*scalar); 
	scalarProduct.setZ(magnitudeK*scalar); 
 	
	return scalarProduct;
}

//======================================================================== 
// Vector::operator/
//========================================================================  


Vector Vector::operator/(const double &scalar)
	// Overloading the / operator for division of a Vector by a scalar.
{
	Vector result;
	
	result.setX(magnitudeI/scalar);
	result.setY(magnitudeJ/scalar); 
	result.setZ(magnitudeK/scalar); 
 	
	return result;
}


//======================================================================== 
// Vector::crossProduct
//========================================================================  


Vector Vector::crossProduct(Vector vect) const
	// Computes the cross product
{
	Vector result;
	
	result.setX(magnitudeJ * vect.getZ() - magnitudeK * vect.getY());
	result.setY(-magnitudeI * vect.getZ() + magnitudeK * vect.getX()); 
	result.setZ(magnitudeI * vect.getY() - magnitudeJ * vect.getX()); 
 	
	return result;
}


//======================================================================== 
// Vector::dotProduct
//========================================================================  


double Vector::dotProduct(Vector vect) const
	// Computes the dot product
{
	return (magnitudeI * vect.getX() + magnitudeJ * vect.getY() + magnitudeK * vect.getZ());
}



//======================================================================== 
// Vector::normalize
//========================================================================  


Vector Vector::normalize(void) const
	// Computes the normalized vector
{
	Vector result;
	double magnitude;

	magnitude = sqrt(magnitudeI * magnitudeI + magnitudeJ * magnitudeJ
					+ magnitudeK * magnitudeK);
	
	if(magnitude == 0) result = Vector(0,0,0);
	else
	{
		result.setX(magnitudeI/magnitude);
		result.setY(magnitudeJ/magnitude); 
		result.setZ(magnitudeK/magnitude); 
	}
 	
	return result;
}


//============================================================
// Vector::display
//============================================================
void Vector :: display(void) const
{
	display(0,0,0);
}

#ifdef __glut_h__

//============================================================
// Vector::display
//============================================================
void Vector :: display(double red, double green, double blue) const
{
	glPushMatrix();
	GLUquadricObj *arrowHead;
	Vector zAxis(0,0,1);
	glColor4f (red, green, blue, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0,0,0);
	glVertex3f(g_scaleFactor*magnitudeI, g_scaleFactor*magnitudeJ,g_scaleFactor*magnitudeK);
	glEnd();
	glTranslatef(g_scaleFactor*magnitudeI, g_scaleFactor*magnitudeJ, g_scaleFactor*magnitudeK);
	Vector normal = zAxis.crossProduct(*this).normalize();
	double rotationAngle = 180*acos(zAxis.dotProduct(this->normalize()))/PI;
	if(normal != Vector(0,0,0))
		glRotated(rotationAngle, normal.getX(),normal.getY(),normal.getZ());
	arrowHead = gluNewQuadric();
	gluCylinder(arrowHead, g_scaleFactor*0.0003,0, g_scaleFactor*0.0007, 50, 50);
	glPopMatrix();
}

#endif

#ifndef __glut_h__
//============================================================
// Vector::display
//============================================================
void Vector :: display(double red, double green, double blue) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

#endif


ostream &operator<<(ostream &output, const Vector &vector)
	// Overloading the << operator for easy display of a Vector on the screen.
{
	output << "[ " << vector.getX() << " " << vector.getY() << " " << vector.getZ() << " ]";
	return output;
}


Vector operator*(const int &scalar, const Vector &vect)
// Overloading binary multiplication operator (*) for 
// pre-multiplication of a Vector with scalar of type integer.
{
	Vector scalarProduct;
	
	scalarProduct.setX(vect.getX()*scalar);
	scalarProduct.setY(vect.getY()*scalar); 
	scalarProduct.setZ(vect.getZ()*scalar); 

	return scalarProduct;
}


Vector operator*(const double &scalar, const Vector &vect)
// Overloading binary multiplication operator (*) for 
// pre-multiplication of a Vector with scalar of type double.
{
	Vector scalarProduct;
	
	scalarProduct.setX(vect.getX()*scalar);
	scalarProduct.setY(vect.getY()*scalar); 
	scalarProduct.setZ(vect.getZ()*scalar); 

	return scalarProduct;
}