//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Jun Wu & Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Cylinder.hpp
// Interface of the class Cylinder
//========================================================================  


#ifndef INCLUDED_Cylinder_hpp
#define INCLUDED_Cylinder_hpp

#include "Globals.h"
#include "Vector.hpp"
#include "List.hpp"
#include "Bricks.hpp"

	
//====================================================================
// class Cylinder
// -------------------------------------------------------------------
// \brief
// The class \c Cylinder describes a muscular hydrostat unit in the shape of Cylinder
// 
//
// <b>Example Program:</b>
//
// \include Cylinder.t.cpp
//========================================================================  


class Cylinder : public Muscle
{
	friend class Node;
public:

// ---- Constructor and Destructor -----

	Cylinder(int unitNumber, 
		double radius, 
		double height, 
		double mass,
		double bulkModulus,
		double radialStiffness,
		double longitudinalStiffness,
		double damping,
		Vector position,
		Vector orientation,
		Vector uAxis);	
		// Constructor

	Cylinder(int unitNumber, 
		double radius, 
		double height, 
		Vector position, 
		Vector orientation,
		Vector uAxis,
		double muscleDensity);
		// Constructor
	
	virtual void shapeChange(void);
		// Calculates change in dimensions of the Cylindrical 
		// Muscular Hydrostat Unit

	double getHeight(void) const;
		// Provides access to the data member height
		//  return		Height of the MHU

	void setHeight(double height);
		// Provides access to the data member height
		
	double getRadius(void) const;
		// Provides access to the data member radius
		//  return		Radius of the MHU

	void setRadius(double radius);
		// Provides access to the data member radius

	void setRadialCommandForce(double command);
		// Set data member command force along radius
		// Its value must be between 0 and 1 

	void setLongitudinalCommandForce(double command);
		// Set data member command force along height
		// Its value must be between 0 and 1 

	double getRadialCommandForce(void) const;
		// Access to data member command force along radius

	double getLongitudinalCommandForce(void) const;
		// Access to data member command force along height
	
	virtual void writeMHAFile(FILE *mhaFilePtr) const;
		// Writes an MHA file that represents this assembly

	virtual void writeLogFile(double logTime, FILE *mhaFilePtr) const;
		// Writes a line in the log file that represents this cylinder

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
		// Displays the resultant force at the COM of the cylinder 
		// in OpenGL window. If OpenGL is not available, error is printed.

	virtual void displayAxes(void) const;
		// Displays the u-v-w frame at the COM of the cylinder 
		// in OpenGL window. If OpenGL is not available, error is printed.

	virtual void displayForce(double red, double green, double blue) const;
		// Displays the resultant force at the COM of the cylinder
		// in OpenGL window in the specified color. 
		// If OpenGL is not available, error is printed.

	friend ostream &operator<<(ostream &output, const Cylinder &cylinder);
		// This function overloads the ostream \c << operator
		// to output the essential quantities of the Cylinder \a cylinder 
 		// to the output stream separated by white spaces(e.g. spaces).
		// Example: \code cout << cylinder; \endcode

	void presetRadialCommand(double command);
		//Set data member start time to apply force along radius

	double getRadialCommandPreset(void);
		//Get data member start time to apply force along radius
	
	void setRadialStartTime(double startTime);
		//Set data member start time to apply force along radius

	void setRadialStopTime(double stopTime);
		//Set data member stop time to apply force along radius

	void presetLongitudinalCommand(double command);
		//Set data member start time to apply force along radius
	
	void setLongitudinalStartTime(double startTime);
		//Set data member start time to apply force along height

	double getLongitudinalCommandPreset(void);
		//Get data member start time to apply force along radius

	void setLongitudinalStopTime(double stopTime);
		//Set data member stop time to apply force along height

	double getRadialStartTime(void);
		//Get data member start time to apply force along radius

	double getRadialStopTime(void);
		//Get data member stop time to apply force along radius

	double getLongitudinalStartTime(void);
		//Get data member start time to apply force along height

	double getLongitudinalStopTime(void);
		//Get data member stop time to apply force along height
private:
	 
	double d_radius;
		// The radius of the muscular hydrostat unit

	double d_height;
		// The height(length) of the muscular hydrostat unit
	
	const double c_radialMuscleStiffness;
		// The stiffness of the material of the MHU in the radial direction

	const double c_longitudinalMuscleStiffness;
		// The stiffness of the material of the MHU in the longitudinal direction

	const double c_restingRadius;
		// The initial radius of the MHU. The unit attempts to get back 
		// to this radius after it is deformed
	 
	const double c_restingHeight;
		// The initial height of the MHU. The unit attempts to get back 
		// to this height after it is deformed

	double d_radialCommandForce;
		// The internally commanded force that causes change in radius
		// By convention, a positive force causes the radius to increase

	double d_longitudinalCommandForce;
		// The internally commanded force that causes change in height
		// By convention, a positive force causes the height to increase
	 
	double d_radialVelocity;
		// The rate of change of radius of the MHU
	 
	double d_longitudinalVelocity;
		// The rate of change of height(length) of the MHU
	 
	double d_previousRadialVelocity;
		// The rate of change of radius of the MHU at the previous time step
	 
	double d_previousLongitudinalVelocity;
		// The rate of change of height(length) of the MHU at the previous time step
	 
	double d_radialAcceleration;
		// The rate of change of radial velocity of the MHU
	 
	double d_longitudinalAcceleration;
		// The rate of change of longitudinal velocity of the MHU
	 
	double d_previousRadialAcceleration;
		// The radial acceleration of the MHU at the previous time step
	 
	double d_previousLongitudinalAcceleration;
		// The longitudinal acceleration of the MHU at the previous time

	double d_radialLoad;
		// External load applied to the MHU along its radius

	double d_longitudinalLoad;
		// External load applied to the MHU along its height
	
	
	 double d_radialStartTime;
		//The start time to apply force along radius

	 double d_radialStopTime;
		//The stop time to apply force along radius

	 double d_radialForcePreset;
		//The stop time to apply force along radius
	 
	 double d_longitudinalStartTime;
		//The start time to apply force along height

	 double d_longitudinalStopTime;
		//The start time to apply force along height
	 
	 double d_longitudinalForcePreset;
		//The stop time to apply force along radius

};

#endif // INCLUDED_Cylinder_hpp