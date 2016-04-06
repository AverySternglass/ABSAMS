//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Jun Wu & Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Box.hpp
// Interface of the class Box
//========================================================================  


#ifndef INCLUDED_Box_hpp
#define INCLUDED_Box_hpp

#include "Globals.h"
#include "Vector.hpp"
#include "List.hpp"
#include "Bricks.hpp"

	
//====================================================================
// class Box
// -------------------------------------------------------------------
// \brief
// The class \c Box describes a muscular hydrostat unit in the shape of Box
// 
//
// <b>Example Program:</b>
//
// \include Box.t.cpp
//========================================================================  


class Box : public Muscle
{
	friend class Node;
public:

// ---- Constructor and Destructor -----

	Box(int unitNumber, 
		double dimension1, 
		double dimension2, 
		double dimension3,
		double mass,
		double bulkModulus,
		double dimension1Stiffness,
		double dimension3Stiffness,
		double damping,
		Vector position,
		Vector orientation,
		Vector uAxis);	
		// Constructor

	Box(int unitNumber, 
		double dimension1, 
		double dimension2, 
		double dimension3,
		Vector position, 
		Vector orientation,
		Vector uAxis,
		double muscleDensity);
		// Constructor
	
	virtual void shapeChange(void);
		// Calculates change in dimensions of the Cylindrical 
		// Muscular Hydrostat Unit

	double getDimension1(void) const;
		// Provides access to the data member dimension1
		//  return		Dimension of the MHU along U-axis

	void setDimension1(double dimension1);
		// Provides access to the data member dimension1
		
	double getDimension2(void) const;
		// Provides access to the data member dimension2
		//  return		Dimension of the MHU along V-axis

	double getDimension3(void) const;
		// Provides access to the data member dimension3
		//  return		Dimension of the MHU along W-axis

	void setDimension3(double dimension1);
		// Provides access to the data member dimension3
	
	void setDimension1CommandForce(double command);
		// Set data member command force along dimension1
		// Its value must be between 0 and 1 

	void setDimension3CommandForce(double command);
		// Set data member command force along dimension2
		// Its value must be between 0 and 1 

	double getDimension1CommandForce(void) const;
		// Access to data member command force along dimension1

	double getDimension3CommandForce(void) const;
		// Access to data member command force along dimension3
	
	virtual void writeMHAFile(FILE *mhaFilePtr) const;
		// Writes to the file the specifics of this Box-type MHU

	virtual void writeLogFile(double logTime, FILE *mhaFilePtr) const;
		// Writes to the log file the position and dimensions of MHU

	virtual void updateInertiaTensor(void);
		// Updates the current Inertia matrix w.r.t the world frame 
		// using the current orientation of the MHU. 

	virtual double getInvIstar(Vector normal, Vector location);
		// Evaluates the equivalent inertia using
		// invIstar = 1/M + n.(invI* (r x n)) x r

	virtual Vector getInstantaneousVelocity(Vector location) const;
		// Calulates the instantaneous velocity at a particular
		// point on the MH Unit

	virtual void display(void) const;
		// Displays the MH Unit in OpenGL window. If OpenGL is 
		// not available, error is printed.

	virtual void display(double red, double green, double blue) const;
		// Displays the MH Unit in OpenGL window in the specified color.
		// If OpenGL is not available, error is printed.

	virtual void displayForce(void) const;
		// Displays the resultant force at the COM of the box 
		// in OpenGL window. If OpenGL is not available, error is printed.

	virtual void displayAxes(void) const;
		// Displays the u-v-w frame at the COM of the cylinder 
		// in OpenGL window. If OpenGL is not available, error is printed.

	virtual void displayForce(double red, double green, double blue) const;
		// Displays the resultant force at the COM of the box
		// in OpenGL window in the specified color. 
		// If OpenGL is not available, error is printed.

	friend ostream &operator<<(ostream &output, const Box &box);
		// This function overloads the ostream \c << operator
		// to output the essential quantities of the Box \a box 
 		// to the output stream separated by white spaces(e.g. spaces).
		// Example: \code cout << box; \endcode

private:
	 
	double d_dimension1;
		// The first dimension of the muscular hydrostat unit

	const double c_dimension2;
		// The second dimension of the muscular hydrostat unit
	
	double d_dimension3;
		// The third dimension of the muscular hydrostat unit

	const double c_dimension1MuscleStiffness;
		// The stiffness of the material of the MHU along the U-axis

	const double c_dimension3MuscleStiffness;
		// The stiffness of the material of the MHU along the W-axis

	const double c_restingDimension1;
		// The initial radius of the MHU. The unit attempts to get back 
		// to this radius after it is deformed
	 
	const double c_restingDimension3;
		// The initial height of the MHU. The unit attempts to get back 
		// to this height after it is deformed

	double d_dimension1CommandForce;
		// The internally commanded force that causes change in dimension1
		// By convention, a positive force causes dimension1 to increase

	double d_dimension3CommandForce;
		// The internally commanded force that causes change in dimension2
		// By convention, a positive force causes dimension2 to increase
	 
	double d_dimension1Velocity;
		// The rate of change of dimension1 of the MHU
	 
	double d_dimension3Velocity;
		// The rate of change of dimension2 of the MHU
	 
	double d_previousDimension1Velocity;
		// The rate of change of dimension1 of the MHU at the previous time step
	 
	double d_previousDimension3Velocity;
		// The rate of change of dimension2 of the MHU at the previous time step
	 
	double d_dimension1Acceleration;
		// The rate of change of dimension1 velocity of the MHU
	 
	double d_dimension3Acceleration;
		// The rate of change of dimension2 velocity of the MHU
	 
	double d_previousDimension1Acceleration;
		// The dimension1 acceleration of the MHU at the previous time step
	 
	double d_previousDimension3Acceleration;
		// The dimension2 acceleration of the MHU at the previous time

	double d_dimension1Load;
		// External load applied to the MHU along dimension1

	double d_dimension3Load;
		// External load applied to the MHU along dimension2
	
};

#endif // INCLUDED_Box_hpp