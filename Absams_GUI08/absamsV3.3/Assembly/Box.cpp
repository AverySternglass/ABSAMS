//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Jun Wu and Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Box.cpp
// Implementation of the class Box.
//========================================================================  

#include "Box.hpp"

//============================================================
// Box::Box
//============================================================

Box :: Box(int unitNumber,
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
		   Vector uAxis)
			: Muscle(2,mass, bulkModulus, damping, dimension1*dimension2*dimension3),
			  c_dimension2 (dimension2),
			  c_dimension1MuscleStiffness (dimension1Stiffness),
			  c_dimension3MuscleStiffness (dimension3Stiffness),
			  c_restingDimension1 (dimension1),
			  c_restingDimension3 (dimension3)
	// copy constructor
{
	Vector zero(0,0,0);
	d_unitNumber = unitNumber;
	d_dimension1 = dimension1;
	d_dimension3 = dimension3;
	d_dimension1CommandForce = 0;
	d_dimension3CommandForce = 0;
	d_dimension1Velocity = 0;
	d_dimension3Velocity = 0;
	d_previousDimension1Velocity = 0;
	d_previousDimension3Velocity = 0;
	d_dimension1Acceleration = 0;
	d_dimension3Acceleration = 0;
	d_previousDimension1Acceleration = 0;
	d_previousDimension3Acceleration = 0;
	d_dimension1Load = 0;
	d_dimension3Load = 0;
	d_pressureConstantVolume = 0;
	d_isAnchor = false;
	d_position = position;
	orientation = orientation.normalize();
	d_orientation = orientation;
	uAxis = uAxis.normalize();
	d_uAxis = uAxis;
	d_linearVelocity = zero;
	d_previousLinearVelocity = zero;
	d_linearAcceleration = zero;
	d_previousLinearAcceleration = zero;
	d_angularVelocity = zero;
	d_previousAngularVelocity = zero;
	d_angularMomentum = zero;
	d_sigmaF = zero;
	d_sigmaTau = zero;
	d_previousSigmaTau = zero;
	d_inertiaInverse[0] = Vector(1.0/((1.0/3.0)*c_mass*
								(c_dimension2*c_dimension2 + d_dimension3*d_dimension3)),0,0);
	d_inertiaInverse[1] = Vector(0,1.0/((1.0/3.0)*c_mass*
								(d_dimension1*d_dimension1 + d_dimension3*d_dimension3)),0);
	d_inertiaInverse[2] = Vector(0,0,1.0/((1.0/3.0)*c_mass*
								(d_dimension1*d_dimension1 + c_dimension2*c_dimension2)));


}

	
//============================================================
// Box::Box
//============================================================
Box :: Box(int unitNumber, 
					double dimension1, 
					double dimension2, 
					double dimension3,
					Vector position, 
					Vector orientation,
					Vector uAxis,
					double muscleDensity)	
		: Muscle(2,muscleDensity*dimension1*dimension2*dimension3, g_bulkModulus, 
			g_muscleDamping, dimension1*dimension2*dimension3),
		  c_dimension2 (dimension2),
		  c_dimension1MuscleStiffness (g_dimension1MuscleStiffness),
		  c_dimension3MuscleStiffness (g_dimension3MuscleStiffness),
		  c_restingDimension1 (dimension1),
		  c_restingDimension3 (dimension3)
	// copy constructor
{
	Vector zero(0,0,0);
	d_unitNumber = unitNumber;
	d_dimension1 = dimension1;
	d_dimension3 = dimension3;
	d_dimension1CommandForce = 0;
	d_dimension3CommandForce = 0;
	d_dimension1Velocity = 0;
	d_dimension3Velocity = 0;
	d_previousDimension1Velocity = 0;
	d_previousDimension3Velocity = 0;
	d_dimension1Acceleration = 0;
	d_dimension3Acceleration = 0;
	d_previousDimension1Acceleration = 0;
	d_previousDimension3Acceleration = 0;
	d_dimension1Load = 0;
	d_dimension3Load = 0;
	d_pressureConstantVolume = 0;
	d_isAnchor = false;
	d_position = position;
	orientation = orientation.normalize();
	d_orientation = orientation;
	uAxis = uAxis.normalize();
	d_uAxis = uAxis;
	d_linearVelocity = zero;
	d_previousLinearVelocity = zero;
	d_linearAcceleration = zero;
	d_previousLinearAcceleration = zero;
	d_angularVelocity = zero;
	d_previousAngularVelocity = zero;
	d_angularMomentum = zero;
	d_sigmaF = zero;
	d_sigmaTau = zero;
	d_previousSigmaTau = zero;
	d_inertiaInverse[0] = Vector(1.0/((1.0/3.0)*c_mass*
								(c_dimension2*c_dimension2 + d_dimension3*d_dimension3)),0,0);
	d_inertiaInverse[1] = Vector(0,1.0/((1.0/3.0)*c_mass*
								(d_dimension1*d_dimension1 + d_dimension3*d_dimension3)),0);
	d_inertiaInverse[2] = Vector(0,0,1.0/((1.0/3.0)*c_mass*
								(d_dimension1*d_dimension1 + c_dimension2*c_dimension2)));


	
}



//============================================================
// Box :: shapeChange
//============================================================
void Box :: shapeChange(void)
{
	const double initialVolume = d_dimension1*c_dimension2*d_dimension3;
	double Area1 = d_dimension3*c_dimension2;
	double Area3 = d_dimension1*c_dimension2;
	double dimension1Pressure = d_dimension1CommandForce/Area1;
	double dimension3Pressure = d_dimension3CommandForce/Area3;
	
	double currentVolume = d_dimension1*c_dimension2*d_dimension3;
	
	d_pressureConstantVolume = - c_bulkModulus * (currentVolume - initialVolume)/initialVolume;
	
	d_dimension1Acceleration = ((dimension1Pressure - s_ambientPressure + d_pressureConstantVolume)*Area1 
							- c_dimension1MuscleStiffness * (d_dimension1 - c_restingDimension1) 
							- c_muscleDamping * d_dimension1Velocity)/(c_mass);
	
	d_dimension3Acceleration = ((dimension3Pressure - s_ambientPressure + d_pressureConstantVolume)*Area3
								  - c_dimension3MuscleStiffness * (d_dimension3 - c_restingDimension3) 
								  - c_muscleDamping * d_dimension3Velocity)/(c_mass);

	d_dimension1Velocity += 0.5*(d_dimension1Acceleration + d_previousDimension1Acceleration)*g_stepSize;
	d_dimension3Velocity += 0.5*(d_dimension3Acceleration + d_previousDimension3Acceleration)*g_stepSize;
	
	d_dimension1 += 0.5*(d_dimension1Velocity + d_previousDimension1Velocity)*g_stepSize;
	d_dimension3 += 0.5*(d_dimension3Velocity + d_previousDimension3Velocity)*g_stepSize;

	d_previousDimension1Velocity = d_dimension1Velocity;
	d_previousDimension3Velocity = d_dimension3Velocity;

	d_previousDimension1Acceleration = d_dimension1Acceleration;
	d_previousDimension3Acceleration = d_dimension3Acceleration;

	// Now move the nodes to reflect the change in shape of the cylinder
	int numNodes = d_attachedNodes.getNumElements();
	for(int i=0; i< numNodes; i++)
	{
		Node *nodePtr = d_attachedNodes.getElement(i).getData();
		nodePtr->relocateNode();
	}
}

//============================================================
// Box :: updateInertiaTensor
//============================================================
void Box :: updateInertiaTensor(void)
{
	
	
	//         The inertia in the body fixed frame is constant and is first 
	//         initialized. Then based on the current MHU orientation and 
	//         direction of the U-axis, the rotation matrix R is initialized.
	//         Inertia in the world frame is then calculated using the formula
	//         Iworld = R * Ibody * transpose(R). However, we only need 
	//         inverse(Iworld) which is calculated using
	//         inverse(Iworld) = R * inverse(Ibody) * transpose(R)
	//         This is because R is an orthonormal matrix

	
	static const Vector iInvFirstRow(1.0/((1.0/3.0)*c_mass*
								(c_dimension2*c_dimension2 + d_dimension3*d_dimension3)),0,0);
	static const Vector iInvSecondRow(0,1.0/((1.0/3.0)*c_mass*
								(d_dimension1*d_dimension1 + d_dimension3*d_dimension3)),0);
	static const Vector iInvThirdRow(0,0,1.0/((1.0/3.0)*c_mass*
								(d_dimension1*d_dimension1 + c_dimension2*c_dimension2)));
	

	Vector rotationFirstRow (d_uAxis.getX(),(d_orientation.crossProduct(d_uAxis)).getX(), d_orientation.getX());
	Vector rotationSecondRow (d_uAxis.getY(),(d_orientation.crossProduct(d_uAxis)).getY(), d_orientation.getY());
	Vector rotationThirdRow (d_uAxis.getZ(),(d_orientation.crossProduct(d_uAxis)).getZ(), d_orientation.getZ());
	// This is the rotation matrix that represents the orientation of the u-v-w frame
	// w.r.t the x-y-z frame

	// Next we calculate  tempMatrix = inverse(Ibody) * transpose(R)
	
	Vector tempMatrixFirstColumn (iInvFirstRow.dotProduct(rotationFirstRow),
								  iInvSecondRow.dotProduct(rotationFirstRow),
								  iInvThirdRow.dotProduct(rotationFirstRow));
	Vector tempMatrixSecondColumn (iInvFirstRow.dotProduct(rotationSecondRow),
								   iInvSecondRow.dotProduct(rotationSecondRow),
								   iInvThirdRow.dotProduct(rotationSecondRow));
	Vector tempMatrixThirdColumn (iInvFirstRow.dotProduct(rotationThirdRow),
								  iInvSecondRow.dotProduct(rotationThirdRow),
								  iInvThirdRow.dotProduct(rotationThirdRow));
	
	// Next we calculate inverse(Iworld) = R * tempMatrix


	d_inertiaInverse[0] = Vector (rotationFirstRow.dotProduct(tempMatrixFirstColumn),
							  rotationFirstRow.dotProduct(tempMatrixSecondColumn),
							  rotationFirstRow.dotProduct(tempMatrixThirdColumn));

	d_inertiaInverse[1] = Vector (rotationSecondRow.dotProduct(tempMatrixFirstColumn),
							  rotationSecondRow.dotProduct(tempMatrixSecondColumn),
							  rotationSecondRow.dotProduct(tempMatrixThirdColumn));

	d_inertiaInverse[2] = Vector (rotationThirdRow.dotProduct(tempMatrixFirstColumn),
							  rotationThirdRow.dotProduct(tempMatrixSecondColumn),
							  rotationThirdRow.dotProduct(tempMatrixThirdColumn));
	
	d_selectTag = 0;
}


//============================================================
// Box::getInstantaneousVelocity
//============================================================

Vector Box::getInstantaneousVelocity(Vector location) const

{
	Vector invRotationFirstRow (d_uAxis.getX(),d_uAxis.getY(),d_uAxis.getZ());
	Vector invRotationSecondRow ((d_orientation.crossProduct(d_uAxis)).getX(),
		(d_orientation.crossProduct(d_uAxis)).getY(), (d_orientation.crossProduct(d_uAxis)).getZ());
	Vector invRotationThirdRow (d_orientation.getX(),d_orientation.getY(), d_orientation.getZ());
	// This is the rotation matrix that represents the orientation of the u-v-w frame
	// w.r.t the x-y-z frame. This, is the inverse(transpose) of the matrix.
	
	Vector relativeLocation = Vector (invRotationFirstRow.dotProduct(location - d_position),
							  invRotationSecondRow.dotProduct(location - d_position),
							  invRotationThirdRow.dotProduct(location - d_position));

	Vector relativeVelocity = Vector ((relativeLocation.getX()/d_dimension1)*d_dimension1Velocity,
									  0,(relativeLocation.getZ()/d_dimension3)*d_dimension3Velocity);

	Vector rotationFirstRow (d_uAxis.getX(),(d_orientation.crossProduct(d_uAxis)).getX(), d_orientation.getX());
	Vector rotationSecondRow (d_uAxis.getY(),(d_orientation.crossProduct(d_uAxis)).getY(), d_orientation.getY());
	Vector rotationThirdRow (d_uAxis.getZ(),(d_orientation.crossProduct(d_uAxis)).getZ(), d_orientation.getZ());

	Vector shapeChangeVelocity = Vector (rotationFirstRow.dotProduct(relativeVelocity),
							  rotationSecondRow.dotProduct(relativeVelocity),
							  rotationThirdRow.dotProduct(relativeVelocity));
	
	
	return d_angularVelocity.crossProduct(location - d_position) + d_linearVelocity + shapeChangeVelocity;
}



//============================================================
// Box::setDimension1CommandForce
//============================================================
void Box :: setDimension1CommandForce(double command)
{
	command = (command > 1.0) ? 1.0 : command;
	command = (command < 0.0) ? 0.0 : command;
		// A better check is required.. but this is a simple solution

	d_dimension1CommandForce = command * g_muscleForcePerArea * (c_dimension2*d_dimension3);
}



//============================================================
// Box::setDimension3CommandForce
//============================================================
void Box :: setDimension3CommandForce(double command)
{
	command = (command > 1.0) ? 1.0 : command;
	command = (command < 0.0) ? 0.0 : command;
		// A better check is required.. but this is a simple solution
	
	d_dimension3CommandForce = command * g_muscleForcePerArea * (c_dimension2*d_dimension1);
}



//============================================================
// Box::getDimension1CommandForce
//============================================================
double Box :: getDimension1CommandForce(void) const
{
	return d_dimension1CommandForce;
}



//============================================================
// Box::getDimension3CommandForce
//============================================================
double Box :: getDimension3CommandForce(void) const
{
	return d_dimension3CommandForce;
}


//============================================================
// Box::getDimension1
//============================================================
double Box :: getDimension1(void) const
{	
	return d_dimension1;
}


//============================================================
// Box::setDimension1
//============================================================
void Box :: setDimension1(double dimension1)
{	
	d_dimension1 = dimension1;
}


//============================================================
// Box::getDimension2
//============================================================
double Box :: getDimension2(void) const
{	
	return c_dimension2;
}


//============================================================
// Box::getDimension3
//============================================================
double Box :: getDimension3(void) const
{	
	return d_dimension3;
}	



//============================================================
// Box::setDimension3
//============================================================
void Box :: setDimension3(double dimension3)
{	
	d_dimension3 = dimension3;
}



//============================================================
// Box::getInvIstar
//============================================================
double Box :: getInvIstar(Vector normal, Vector location)
{
	// invIstar = 1/M + n.(invI* (r x n)) x r
	// where M - the mass of the unit
	//       n - normal at the point of collision
	//    invI - inverse Inertia matrix in the world frame (time varying)
	//		 r - relative position of the point of collision in the world frame
	//           ( i.e., the vector joining the centre of the MHU to the point
	//             as expressed in the world frame)

	this->updateInertiaTensor();

		Vector r (location - d_position);
		Vector rCrossN (r.crossProduct(normal));

		Vector tempMatrix (d_inertiaInverse[0].dotProduct(rCrossN),
						   d_inertiaInverse[1].dotProduct(rCrossN),
						   d_inertiaInverse[2].dotProduct(rCrossN));

		return ((1.0/c_mass) + normal.dotProduct(tempMatrix.crossProduct(r)));
}


//============================================================
// Box::writeMHAFile
//============================================================

void Box :: writeMHAFile(FILE *mhaFilePtr) const
{
	fprintf(mhaFilePtr,"%d\t", d_unitNumber);
	fprintf(mhaFilePtr,"2\t");
	fprintf(mhaFilePtr,"%d\t", d_isAnchor);
	fprintf(mhaFilePtr,"%lf\t%lf\t%lf\t", d_dimension1,	c_dimension2,d_dimension3);
	fprintf(mhaFilePtr,"%lf\t%lf\t%lf\t", d_position.getX(),
			d_position.getY(),d_position.getZ());
	fprintf(mhaFilePtr,"%lf\t%lf\t%lf\t", d_orientation.getX(),
			d_orientation.getY(),d_orientation.getZ());
	fprintf(mhaFilePtr,"%lf\t%lf\t%lf\n", d_uAxis.getX(),
			d_uAxis.getY(),d_uAxis.getZ());
}


//============================================================
// Box::writeLogFile
//============================================================

void Box :: writeLogFile(double logTime, FILE *logFilePtr) const
{
//	fprintf(logFilePtr,"%lf\t", logTime);
	fprintf(logFilePtr,"%d\t", d_unitNumber);
	fprintf(logFilePtr,"2\t");
	fprintf(logFilePtr,"%lf\t%lf\t%lf\t", d_dimension1,	c_dimension2,d_dimension3);
	fprintf(logFilePtr,"%lf\t%lf\t%lf\t", d_position.getX(),
			d_position.getY(),d_position.getZ());
	
}



//============================================================
// Box::display
//============================================================
void Box :: display(void) const
{
	if(d_dimension1CommandForce == 0 && d_dimension3CommandForce == 0)
	{
		switch(d_selectTag)
		{
			case 1: 
				display(1.0,0.0,0.0);
				break;
			case 2: 
				display(0.0,1.0,0.0);
				break;
			default:
				display(0.7,0.7,0.7);
				break;
		}
	}
	else
		display(0.7,0.3,0.3);		
}


//============================================================
// Box::displayForce
//============================================================
void Box :: displayForce(void) const
{
	displayForce(0,0,0);
}



#ifdef __glut_h__
//============================================================
// Box::display
//============================================================
void Box :: display(double red, double green, double blue) const
{
	
	glPushMatrix();
	glColor4f (red, green, blue, 1.0);
	Vector zAxis(0,0,1);
	Vector baseOrientation = this->d_orientation;

	glTranslatef(g_scaleFactor*d_position.getX(),
				 g_scaleFactor*d_position.getY(),
				 g_scaleFactor*d_position.getZ());
	Vector vAxis = d_orientation.crossProduct(d_uAxis);
	GLfloat rotMatrix[16] = { d_uAxis.getX(), d_uAxis.getY(),d_uAxis.getZ(),0,
								vAxis.getX(), vAxis.getY(),vAxis.getZ(),0,
								d_orientation.getX(), d_orientation.getY(),d_orientation.getZ(),0,
								0,0,0,1};
								
	glMultMatrixf(rotMatrix);

	glBegin(GL_QUADS);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);

		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);

		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);

		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);

		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);

	glEnd();
	glColor4f (0.0, 0.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);

		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);

		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);

		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);

		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);

		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(-0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,0.5*g_scaleFactor*d_dimension3);
		glVertex3f(0.5*g_scaleFactor*d_dimension1,-0.5*g_scaleFactor*c_dimension2,-0.5*g_scaleFactor*d_dimension3);
		
	glEnd();
	glPopMatrix();
}

//============================================================
// Box::displayForce
//============================================================
void Box :: displayForce(double red, double green, double blue) const
{
	glPushMatrix();
	glTranslatef(g_scaleFactor*d_position.getX(), 
		g_scaleFactor*d_position.getY(),
		g_scaleFactor*d_position.getZ());
	if(Vector(0,0,0) != d_sigmaF)
		d_sigmaF.display(red, green, blue);
	glPopMatrix();
}

//============================================================
// Box::displayAxes
//============================================================
void Box :: displayAxes(void) const
{
	Vector vAxis;
	glPushMatrix();
	glTranslatef(g_scaleFactor*d_position.getX(), 
		g_scaleFactor*d_position.getY(),
		g_scaleFactor*d_position.getZ());
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(-d_uAxis.getX()*g_scaleFactor*d_dimension1*0.25,
			-d_uAxis.getY()*g_scaleFactor*d_dimension1*0.25,
			-d_uAxis.getZ()*g_scaleFactor*d_dimension1*0.25);
		glVertex3f(d_uAxis.getX()*g_scaleFactor*d_dimension1*1.25,
			d_uAxis.getY()*g_scaleFactor*d_dimension1*1.25,
			d_uAxis.getZ()*g_scaleFactor*d_dimension1*1.25);
		glColor3f(0,1,0);
		vAxis = d_orientation.crossProduct(d_uAxis);
		glVertex3f(-vAxis.getX()*g_scaleFactor*d_dimension1*0.25,
			-vAxis.getY()*g_scaleFactor*d_dimension1*0.25,
			-vAxis.getZ()*g_scaleFactor*d_dimension1*0.25);
		glVertex3f(vAxis.getX()*g_scaleFactor*d_dimension1*1.25,
			vAxis.getY()*g_scaleFactor*d_dimension1*1.25,
			vAxis.getZ()*g_scaleFactor*d_dimension1*1.25);
		glColor3f(0,0,1);
		glVertex3f(-d_orientation.getX()*g_scaleFactor*d_dimension1*0.25,
			-d_orientation.getY()*g_scaleFactor*d_dimension1*0.25,
			-d_orientation.getZ()*g_scaleFactor*d_dimension1*0.25);
		glVertex3f(d_orientation.getX()*g_scaleFactor*d_dimension1*1.25,
			d_orientation.getY()*g_scaleFactor*d_dimension1*1.25,
			d_orientation.getZ()*g_scaleFactor*d_dimension1*1.25);
	glEnd();
	glPopMatrix();
}

#endif

#ifndef __glut_h__
//============================================================
// Box::display
//============================================================
void Box :: display(double red, double green, double blue) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

//============================================================
// Box::displayForce
//============================================================
void Box :: displayForce(double red, double green, double blue) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

//============================================================
// Box::displayAxes
//============================================================
void Box :: displayAxes(void) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

#endif


//============================================================
// operator<<
//============================================================

ostream &operator<<(ostream &output, const Box &box)
	// Overloading the << operator for easy display of Cylinder information on the screen.
{
	output << "MH Unit Number: " << box.d_unitNumber << "\n" 
		<< "Position: " << box.d_position << "\n" 
		<< "Velocity: " << box.d_orientation << "\n" 
		<< "Dimension1: " << box.d_dimension1 << "\n" 
		<< "Dimension2: " << box.c_dimension2 << "\n" 
		<< "Dimension3:"  << box.d_dimension3 << "\n" << endl;

	return output;
}