//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Jun Wu and Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Cylinder.cpp
// Implementation of the class Cylinder.
//========================================================================  

#include "Bricks.hpp"

double Cylinder :: s_ambientPressure = g_ambientPressure;

//============================================================
// Cylinder::Cylinder
//============================================================

Cylinder :: Cylinder(int unitNumber,
				   double radius,
				   double height,
				   double mass,
				   double bulkModulus,
				   double radialStiffness,
				   double longitudinalStiffness,
				   double damping,
				   Vector position,
				   Vector orientation,
				   Vector uAxis)
		: c_mass (mass),
		  c_bulkModulus (bulkModulus),
		  c_radialMuscleStiffness (radialStiffness),
		  c_longitudinalMuscleStiffness (longitudinalStiffness),
		  c_muscleDamping (damping),
		  c_restingRadius (radius),
		  c_restingHeight (height)
	// copy constructor
{
	Vector zero(0,0,0);
	d_unitNumber = unitNumber;
	d_radius = radius;
	d_height = height;
	d_model = 1;
	d_radialCommandForce = 0;
	d_longitudinalCommandForce = 0;
	d_radialVelocity = 0;
	d_longitudinalVelocity = 0;
	d_previousRadialVelocity = 0;
	d_previousLongitudinalVelocity = 0;
	d_radialAcceleration = 0;
	d_longitudinalAcceleration = 0;
	d_previousRadialAcceleration = 0;
	d_previousLongitudinalAcceleration = 0;
	d_radialLoad = 0;
	d_longitudinalLoad = 0;
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
	d_inertiaInverse[0] = Vector(1.0/((1.0/12.0)*c_mass*d_height*d_height 
											+ (1.0/4.0)*c_mass*d_radius*d_radius),0,0);
	d_inertiaInverse[1] = Vector(0,1.0/((1.0/12.0)*c_mass*d_height*d_height 
											+ (1.0/4.0)*c_mass*d_radius*d_radius),0);
	d_inertiaInverse[2] = Vector(0,0,1.0/((1.0/2.0)*c_mass*d_radius*d_radius));

	d_radialStartTime = 0;
	d_radialStopTime = 0; 
	d_longitudinalStartTime = 0;
	d_longitudinalStopTime = 0;
	
}

	
//============================================================
// Cylinder::Cylinder
//============================================================
Cylinder :: Cylinder(int unitNumber, 
					 double radius, 
					 double height, 
					 Vector position, 
					 Vector orientation,
					 Vector uAxis,
					 double muscleDensity)	
		: c_mass (muscleDensity*PI*radius*radius*height),
		  c_bulkModulus (g_bulkModulus),
		  c_radialMuscleStiffness (g_radialMuscleStiffness),
		  c_longitudinalMuscleStiffness (g_longitudinalMuscleStiffness),
		  c_muscleDamping (g_muscleDamping),
		  c_restingRadius (radius),
		  c_restingHeight (height)
	// copy constructor
{
	Vector zero(0,0,0);
	d_unitNumber = unitNumber;
	d_radius = radius;
	d_height = height;
	d_model = 1;
	d_radialCommandForce = 0;
	d_longitudinalCommandForce = 0;
	d_radialVelocity = 0;
	d_longitudinalVelocity = 0;
	d_previousRadialVelocity = 0;
	d_previousLongitudinalVelocity = 0;
	d_radialAcceleration = 0;
	d_longitudinalAcceleration = 0;
	d_previousRadialAcceleration = 0;
	d_previousLongitudinalAcceleration = 0;
	d_radialLoad = 0;
	d_longitudinalLoad = 0;
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
	d_inertiaInverse[0] = Vector(1.0/((1.0/12.0)*c_mass*d_height*d_height 
											+ (1.0/4.0)*c_mass*d_radius*d_radius),0,0);
	d_inertiaInverse[1] = Vector(0,1.0/((1.0/12.0)*c_mass*d_height*d_height 
											+ (1.0/4.0)*c_mass*d_radius*d_radius),0);
	d_inertiaInverse[2] = Vector(0,0,1.0/((1.0/2.0)*c_mass*d_radius*d_radius));

	d_radialStartTime = 0;
	d_radialStopTime = 0; 
	d_longitudinalStartTime = 0;
	d_longitudinalStopTime = 0;
	
}



//============================================================
// Cylinder :: getID
//============================================================
int Cylinder :: getID(void) const
{
	return d_unitNumber;
}



//============================================================
// Cylinder :: shapeChange
//============================================================
void Cylinder :: shapeChange(void)
{
	const double initialVolume = PI * c_restingRadius * c_restingRadius * c_restingHeight;
	double curvedArea = 2.0*PI*d_radius*d_height;
	double capArea = 2.0*PI*d_radius*d_radius;
	double radialPressure = d_radialCommandForce/curvedArea;
	double longitudinalPressure = d_longitudinalCommandForce/capArea;
	
	double currentVolume = PI * d_radius * d_radius * d_height;
	double rateOfVolumeChange = 2*PI*d_radius*d_height*d_radialVelocity
								+PI*d_radius*d_radius*d_longitudinalVelocity;

	//cout << currentVolume << " " << rateOfVolumeChange <<endl;
	if( d_model == 1)
		d_pressureConstantVolume = - c_bulkModulus * (currentVolume - initialVolume)/initialVolume;
	
	else
		d_pressureConstantVolume = (1.0/(2.0*PI*d_radius*d_radius*d_height*d_height 
										+ 2.0*PI*d_radius*d_radius*d_radius*d_radius))*
								((c_mass)*(-4.0*d_radius*d_radialVelocity*d_longitudinalVelocity
									-2.0*d_radialVelocity*d_radialVelocity*d_height)
									-(d_radius*d_height)*((radialPressure - s_ambientPressure)*curvedArea 
										- c_radialMuscleStiffness * (d_radius - c_restingRadius) 
										- c_muscleDamping * d_radialVelocity)
									-(d_radius*d_radius)*((longitudinalPressure - s_ambientPressure)*capArea
										- c_longitudinalMuscleStiffness * (d_height - c_restingHeight) 
										- c_muscleDamping * d_longitudinalVelocity));
	

	
	d_radialAcceleration = ((radialPressure - s_ambientPressure + d_pressureConstantVolume)*curvedArea 
							- c_radialMuscleStiffness * (d_radius - c_restingRadius) 
							- c_muscleDamping * d_radialVelocity)/(c_mass);
	
	d_longitudinalAcceleration = ((longitudinalPressure - s_ambientPressure + d_pressureConstantVolume)*capArea
								  - c_longitudinalMuscleStiffness * (d_height - c_restingHeight) 
								  - c_muscleDamping * d_longitudinalVelocity)/(c_mass);

	d_radialVelocity += 0.5*(d_radialAcceleration + d_previousRadialAcceleration)*g_stepSize;
	d_longitudinalVelocity += 0.5*(d_longitudinalAcceleration + d_previousLongitudinalAcceleration)*g_stepSize;
	if(d_model != 1)
		d_longitudinalVelocity = -2.0*d_height*d_radialVelocity/(d_radius);
	d_radius += 2*0.5*(d_radialVelocity + d_previousRadialVelocity)*g_stepSize;
	d_height += 2*0.5*(d_longitudinalVelocity + d_previousLongitudinalVelocity)*g_stepSize;

	d_previousRadialVelocity = d_radialVelocity;
	d_previousLongitudinalVelocity = d_longitudinalVelocity;

	d_previousRadialAcceleration = d_radialAcceleration;
	d_previousLongitudinalAcceleration = d_longitudinalAcceleration;

	// Now move the nodes to reflect the change in shape of the cylinder
	int numNodes = d_attachedNodes.getNumElements();
	for(int i=0; i< numNodes; i++)
	{
		Node *nodePtr = d_attachedNodes.getElement(i).getData();
		nodePtr->relocateNode();
	}
}

//============================================================
// Cylinder :: updateInertiaTensor
//============================================================
void Cylinder :: updateInertiaTensor(void)
{
	
	
	//         The inertia in the body fixed frame is constant and is first 
	//         initialized. Then based on the current MHU orientation and 
	//         direction of the U-axis, the rotation matrix R is initialized.
	//         Inertia in the world frame is then calculated using the formula
	//         Iworld = R * Ibody * transpose(R). However, we only need 
	//         inverse(Iworld) which is calculated using
	//         inverse(Iworld) = R * inverse(Ibody) * transpose(R)
	//         This is because R is an orthonormal matrix

	
	static const Vector iInvFirstRow(1.0/((1.0/12.0)*c_mass*d_height*d_height 
											+ (1.0/4.0)*c_mass*d_radius*d_radius),0,0);
	static const Vector iInvSecondRow(0,1.0/((1.0/12.0)*c_mass*d_height*d_height 
											+ (1.0/4.0)*c_mass*d_radius*d_radius),0);
	static const Vector iInvThirdRow(0,0,1.0/((1.0/2.0)*c_mass*d_radius*d_radius));
	

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

}


//============================================================
// Cylinder :: applyForceAt
//============================================================
void Cylinder :: applyForceAt(Vector force, Vector location)
{
	Vector direction = location - d_position;
	d_sigmaF += force;
	d_sigmaTau += direction.crossProduct(force);		
}


//============================================================
// Node::getInstantaneousVelocity
//============================================================

Vector Cylinder::getInstantaneousVelocity(Vector location) const

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

	Vector relativeVelocity = Vector ((relativeLocation.getX()/d_radius)*d_radialVelocity,
									  (relativeLocation.getY()/d_radius)*d_radialVelocity,
									  (relativeLocation.getZ()/d_height)*d_longitudinalVelocity);

	Vector rotationFirstRow (d_uAxis.getX(),(d_orientation.crossProduct(d_uAxis)).getX(), d_orientation.getX());
	Vector rotationSecondRow (d_uAxis.getY(),(d_orientation.crossProduct(d_uAxis)).getY(), d_orientation.getY());
	Vector rotationThirdRow (d_uAxis.getZ(),(d_orientation.crossProduct(d_uAxis)).getZ(), d_orientation.getZ());

	Vector shapeChangeVelocity = Vector (rotationFirstRow.dotProduct(relativeVelocity),
							  rotationSecondRow.dotProduct(relativeVelocity),
							  rotationThirdRow.dotProduct(relativeVelocity));
	
	
	return d_angularVelocity.crossProduct(location - d_position) + d_linearVelocity + shapeChangeVelocity;
}


//============================================================
// Cylinder :: updateCylinder
//============================================================
void Cylinder :: updateCylinder(void)
{
	// This is done in the following steps:
	// 1. Find the total force and torque acting on the MHU
	// 2. Calculate temporary variables required (Intertia and rotation)
	// 3. Calculate translational and rotational dynamics.
	
	// Step 1: Calculate the total force and torque on the MHU
	//		   Initialize the total force and torque to zero and then
	//		   loop over all the nodes. For each node, calculate the 
	//         effect of its force on the MHU.

	Node *nodePtr;
	Vector direction,temp1, temp2;
	int numNodes = d_attachedNodes.getNumElements();
	for(int i=0; i< numNodes; i++)
	{
		nodePtr = d_attachedNodes.getElement(i).getData();
		this->applyForceAt(nodePtr->getResultantForce(),nodePtr->getAbsolutePosition());
	}

	// Step 2: Update current Inertia Matrix;

	this->updateInertiaTensor();
	
	d_angularMomentum += 0.5*(d_sigmaTau + d_previousSigmaTau) * g_stepSize;


		
	d_angularVelocity = Vector(d_inertiaInverse[0].dotProduct(d_angularMomentum),
					     d_inertiaInverse[1].dotProduct(d_angularMomentum),
						 d_inertiaInverse[2].dotProduct(d_angularMomentum));
	
	// Now we can calculate the Rotation matrix at the new time step (which
	// will determine the orientation of the u-v-w axis w.r.t the x-y-z axis).
	// However, we only need to calculate the u and w axes 
	// to completely define the cylinder rotation. For this, we use
	// r_dot = omega X r where
	// r_dot - rate of change of the vector
	// omega - angular velocity vector
	// r     - current value of the vector.

	
	d_uAxis += 0.5*(d_angularVelocity.crossProduct(d_uAxis)
							+ d_previousAngularVelocity.crossProduct(d_uAxis))*g_stepSize;
	d_uAxis = d_uAxis.normalize();

	d_orientation += 0.5*(d_angularVelocity.crossProduct(d_orientation)
							+ d_previousAngularVelocity.crossProduct(d_orientation))*g_stepSize;
	d_orientation = d_orientation.normalize();

	d_previousSigmaTau = d_sigmaTau;
	d_previousAngularVelocity = d_angularVelocity;
	 
	d_linearAcceleration = (1/c_mass)*d_sigmaF;
	d_linearVelocity += 0.5*(d_linearAcceleration + d_previousLinearAcceleration)*g_stepSize;
	d_position += 0.5*(d_linearVelocity + d_previousLinearVelocity)*g_stepSize;

	//cout << d_sigmaTau<< endl;

	d_previousLinearAcceleration = d_linearAcceleration;
	d_previousLinearVelocity = d_linearVelocity;

	// Now move the nodes to reflect the change in position/orientation of the cylinder
	numNodes = d_attachedNodes.getNumElements();
	for(i=0; i< numNodes; i++)
	{
		nodePtr = d_attachedNodes.getElement(i).getData();
		nodePtr->relocateNode();
	}
	
	// Reset the force and torque for next iteration

	d_sigmaF = Vector(0,0,0);
	d_sigmaTau = Vector(0,0,0);
	
}


//============================================================
// Cylinder::setModel
//============================================================
void Cylinder :: setModel(int model)
{
	d_model = model;
}


//============================================================
// Cylinder::setAnchor
//============================================================

void Cylinder::setAnchor(void)

{
	d_isAnchor = true;
}

//============================================================
// Cylinder::isAnchor
//============================================================

bool Cylinder::isAnchor(void) const

{
	return(d_isAnchor);
}





//============================================================
// Cylinder::setRadialStartTime
//============================================================
void Cylinder :: setRadialStartTime(double startTime)
{
	d_radialStartTime = startTime;
}

//============================================================
// Cylinder::setRadialStopTime
//============================================================
void Cylinder :: setRadialStopTime(double stopTime)
{
	d_radialStopTime = stopTime;
}

//============================================================
// Cylinder::setLongitudinalStartTime
//============================================================
void Cylinder :: setLongitudinalStartTime(double startTime)
{
	d_longitudinalStartTime = startTime;
}

//============================================================
// Cylinder::setLongitudinalStopTime
//============================================================
void Cylinder :: setLongitudinalStopTime(double stopTime)
{
	d_longitudinalStopTime = stopTime;
}

//============================================================
// Cylinder::getRadialStartTime
//============================================================
double Cylinder ::getRadialStartTime(void)
{
	return d_radialStartTime;
}

//============================================================
// Cylinder::getRadialStopTime
//============================================================
double Cylinder ::getRadialStopTime(void)
{
	return d_radialStopTime;
}

//============================================================
// Cylinder::getLongitudinalStartTime
//============================================================
double Cylinder ::getLongitudinalStartTime(void)
{
	return d_longitudinalStartTime;
}

//============================================================
// Cylinder::getLongitudinalStopTime
//============================================================
double Cylinder :: getLongitudinalStopTime(void)
{
	return d_longitudinalStopTime;
}

//============================================================
// Cylinder::presetRadialCommand
//============================================================
void Cylinder :: presetRadialCommand(double command)
{
	d_radialForcePreset = command;
}

//============================================================
// Cylinder::presetLongitudinalCommand
//============================================================
void Cylinder :: presetLongitudinalCommand(double command)
{
	d_longitudinalForcePreset = command;
}


//============================================================
// Cylinder::getLongitudinalCommandPreset
//============================================================
double Cylinder :: getLongitudinalCommandPreset(void)
{
	return d_longitudinalForcePreset;
}

//============================================================
// Cylinder::getRadialCommandPreset
//============================================================
double Cylinder :: getRadialCommandPreset(void)
{
	return d_radialForcePreset;
}



//============================================================
// Cylinder::setRadialCommandForce
//============================================================
void Cylinder :: setRadialCommandForce(double command)
{
	command = (command > 1.0) ? 1.0 : command;
	command = (command < 0.0) ? 0.0 : command;
		// A better check is required.. but this is a simple solution

	d_radialCommandForce = command * g_muscleForcePerArea * (PI * d_radius * d_height);
}



//============================================================
// Cylinder::setLongitudinalCommandForce
//============================================================
void Cylinder :: setLongitudinalCommandForce(double command)
{
	command = (command > 1.0) ? 1.0 : command;
	command = (command < 0.0) ? 0.0 : command;
		// A better check is required.. but this is a simple solution
	
	d_longitudinalCommandForce = command * g_muscleForcePerArea * (PI * d_radius * d_radius);
}



//============================================================
// Cylinder::getRadialCommandForce
//============================================================
double Cylinder :: getRadialCommandForce(void) const
{
	return d_radialCommandForce;
}



//============================================================
// Cylinder::getLongitudinalCommandForce
//============================================================
double Cylinder :: getLongitudinalCommandForce(void) const
{
	return d_longitudinalCommandForce;
}


//============================================================
// Cylinder::setPosition
//============================================================
void Cylinder :: setPosition(Vector position)
{
	d_position = position;
}


//============================================================
// Cylinder::setOrientation
//============================================================
void Cylinder :: setOrientation(Vector orientation)
{
	d_orientation = orientation.normalize(); // Need to ensure it is a unit vector????
}

//============================================================
// Cylinder::setUAxis
//============================================================
void Cylinder :: setUAxis(Vector uAxis)
{
	d_uAxis = uAxis.normalize(); // Need to ensure it is a unit vector????
}


//============================================================
// Cylinder::createCollisionNode
//============================================================
Node *Cylinder :: createCollisionNode(Vector absPosition)
{
	Node *newNode;
	newNode = new Node((1000 + d_collisionNodes.getNumElements()),this, Vector(0,0,0));
	// the 1000 is an arbitrary number that signifies that the node is a collision
	// node (assuming that there will be fewer that 1000 nodes in the assembly

	this->detachNode(newNode); // remove form the list of attached nodes
	newNode->setPosition(absPosition);
	d_collisionNodes.addElement(newNode);
	return newNode;
}



//============================================================
// Cylinder::removeCollisionNode
//============================================================
void Cylinder :: removeCollisionNode(Node *node)
{
	int i;
	for(i=0; ; i++)
		if((d_collisionNodes.getElement(i).getData())->getNumber() == node->getNumber())
			break;
		d_collisionNodes.deleteElement(i);
}


//============================================================
// Cylinder::getNumCollisionNodes
//============================================================
int Cylinder :: getNumCollisionNodes(void) const
{
	return d_collisionNodes.getNumElements();
}


	
//============================================================
// Cylinder::attachNode
//============================================================
void Cylinder :: attachNode(Node *node)
{
	d_attachedNodes.addElement(node);
}


//============================================================
// Cylinder::detachNode
//============================================================
void Cylinder :: detachNode(Node *node)
{
	int i;
	for(i=0; ; i++)
	{
		if((d_attachedNodes.getElement(i).getData())->getNumber() == node->getNumber())
		{
			d_attachedNodes.deleteElement(i);
			return;
		}
	}
		
}



//============================================================
// Cylinder::getRadius
//============================================================
double Cylinder :: getRadius(void) const
{	
	return d_radius;
}


//============================================================
// Cylinder::setRadius
//============================================================
void Cylinder :: setRadius(double radius)
{	
	d_radius = radius;
}


//============================================================
// Cylinder::getHeight
//============================================================
double Cylinder :: getHeight(void) const
{	
	return d_height;
}	



//============================================================
// Cylinder::setHeight
//============================================================
void Cylinder :: setHeight(double height)
{	
	d_height = height;
}



//============================================================
// Cylinder::getPosition
//============================================================
Vector Cylinder :: getPosition(void) const
{
	return d_position;
}


//============================================================
// Cylinder::getOrientation
//============================================================
Vector Cylinder :: getOrientation(void) const
{
	return d_orientation;
}

//============================================================
// Cylinder::getUAxis
//============================================================
Vector Cylinder :: getUAxis(void) const
{
	return d_uAxis;
}


//============================================================
// Cylinder::getUnitQuaternion
//============================================================
void Cylinder :: getUnitQuaternion(double *qw, double *qx, double *qy, double *qz) const
{
	double m00 = d_uAxis.getX(),
		   m01 = d_uAxis.getY(),
		   m02 = d_uAxis.getZ();

	double m10 = (d_orientation.crossProduct(d_uAxis)).getX(),
		   m11 = (d_orientation.crossProduct(d_uAxis)).getY(),
		   m12 = (d_orientation.crossProduct(d_uAxis)).getZ();

	double m20 = d_orientation.getX(),
		   m21 = d_orientation.getY(),
		   m22 = d_orientation.getZ();
	
	*qw = sqrt(1 + m00 + m11 + m22)/2;
	*qx = (m21 - m12)/(4*(*qw));
	*qy = (m02 - m20)/(4*(*qw));
	*qz = (m10 - m01)/(4*(*qw));
	
}



//============================================================
// Cylinder::getInvIstar
//============================================================
double Cylinder :: getInvIstar(Vector normal, Vector location)
{
	// invIstar = 1/M + n.(invI* (r x n)) x r
	// where M - the mass of the unit
	//       n - normal at the point of collision
	//    invI - inverse Inertia matrix in the world frame (time varying)
	//		 r - relative position of the point of collision in the world frame
	//           ( i.e., the vector joining the centre of the MHU to the point
	//             as expressed in the world frame)

/*	if(d_isAnchor)
		return (1.0/g_infiniteMass);
	else
	{
		this->updateInertiaTensor();

		Vector r (location - d_position);
		Vector rCrossN (r.crossProduct(normal));

		Vector tempMatrix (d_inertiaInverse[0].dotProduct(rCrossN),
						   d_inertiaInverse[1].dotProduct(rCrossN),
						   d_inertiaInverse[2].dotProduct(rCrossN));

		return ((1.0/c_mass) + normal.dotProduct(tempMatrix.crossProduct(r)));
	}
*/

	this->updateInertiaTensor();

		Vector r (location - d_position);
		Vector rCrossN (r.crossProduct(normal));

		Vector tempMatrix (d_inertiaInverse[0].dotProduct(rCrossN),
						   d_inertiaInverse[1].dotProduct(rCrossN),
						   d_inertiaInverse[2].dotProduct(rCrossN));

		return ((1.0/c_mass) + normal.dotProduct(tempMatrix.crossProduct(r)));
}


//============================================================
// Cylinder::display
//============================================================
void Cylinder :: display(void) const
{
	if(d_longitudinalCommandForce != 0 || d_radialCommandForce != 0)
		display(0.7,0.3,0.3);
	else
		display(0.7,0.7,0.7);
}


//============================================================
// Cylinder::displayForce
//============================================================
void Cylinder :: displayForce(void) const
{
	displayForce(0,0,0);
}



#ifdef __glut_h__
//============================================================
// Cylinder::display
//============================================================
void Cylinder :: display(double red, double green, double blue) const
{
	
	glPushMatrix();
	glColor4f (red, green, blue, 1.0);
	Vector zAxis(0,0,1);
	Vector baseOrientation = this->d_orientation;
	GLUquadricObj *cylinderObject1,*cylinderObject2;
	glTranslatef(g_scaleFactor*d_position.getX(),
				 g_scaleFactor*d_position.getY(),
				 g_scaleFactor*d_position.getZ());

	Vector normal = zAxis.crossProduct(d_orientation).normalize();
	double rotationAngle = 180*acos(zAxis.dotProduct(baseOrientation))/PI;
	if(normal != Vector(0,0,0))
		glRotated(rotationAngle, normal.getX(),normal.getY(),normal.getZ());
	glTranslatef(0,0,-g_scaleFactor*(d_height)/2.0);
	cylinderObject1 = gluNewQuadric();
	cylinderObject2 = gluNewQuadric();
	gluQuadricDrawStyle(cylinderObject2, GLU_FILL);
	gluCylinder(cylinderObject2, g_scaleFactor*d_radius,	
		g_scaleFactor*d_radius, g_scaleFactor*d_height, 50, 50);
	glColor4f (0, 0, 0, 1.0);
	gluQuadricDrawStyle(cylinderObject1, GLU_SILHOUETTE);
	gluCylinder(cylinderObject1, g_scaleFactor*d_radius,	
		g_scaleFactor*d_radius, g_scaleFactor*d_height, 50, 50);
	glPopMatrix();
	glPushMatrix();
	int numNodes = d_collisionNodes.getNumElements();
	Node *nodePtr;
	for(int i=0; i< numNodes; i++)
	{
		nodePtr = d_collisionNodes.getElement(i).getData();
		nodePtr->display(1,0,0);
		nodePtr->displayForce();
	}
	glPopMatrix();
}

//============================================================
// Cylinder::displayForce
//============================================================
void Cylinder :: displayForce(double red, double green, double blue) const
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
// Cylinder::displayAxes
//============================================================
void Cylinder :: displayAxes(void) const
{
	Vector vAxis;
	glPushMatrix();
	glTranslatef(g_scaleFactor*d_position.getX(), 
		g_scaleFactor*d_position.getY(),
		g_scaleFactor*d_position.getZ());
	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(-d_uAxis.getX()*g_scaleFactor*d_radius*0.25,
			-d_uAxis.getY()*g_scaleFactor*d_radius*0.25,
			-d_uAxis.getZ()*g_scaleFactor*d_radius*0.25);
		glVertex3f(d_uAxis.getX()*g_scaleFactor*d_radius*1.25,
			d_uAxis.getY()*g_scaleFactor*d_radius*1.25,
			d_uAxis.getZ()*g_scaleFactor*d_radius*1.25);
		glColor3f(0,1,0);
		vAxis = d_orientation.crossProduct(d_uAxis);
		glVertex3f(-vAxis.getX()*g_scaleFactor*d_radius*0.25,
			-vAxis.getY()*g_scaleFactor*d_radius*0.25,
			-vAxis.getZ()*g_scaleFactor*d_radius*0.25);
		glVertex3f(vAxis.getX()*g_scaleFactor*d_radius*1.25,
			vAxis.getY()*g_scaleFactor*d_radius*1.25,
			vAxis.getZ()*g_scaleFactor*d_radius*1.25);
		glColor3f(0,0,1);
		glVertex3f(-d_orientation.getX()*g_scaleFactor*d_radius*0.25,
			-d_orientation.getY()*g_scaleFactor*d_radius*0.25,
			-d_orientation.getZ()*g_scaleFactor*d_radius*0.25);
		glVertex3f(d_orientation.getX()*g_scaleFactor*d_radius*1.25,
			d_orientation.getY()*g_scaleFactor*d_radius*1.25,
			d_orientation.getZ()*g_scaleFactor*d_radius*1.25);
	glEnd();
	glPopMatrix();
}

#endif

#ifndef __glut_h__
//============================================================
// Cylinder::display
//============================================================
void Cylinder :: display(double red, double green, double blue) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

//============================================================
// Cylinder::displayForce
//============================================================
void Cylinder :: displayForce(double red, double green, double blue) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

//============================================================
// Cylinder::displayAxes
//============================================================
void Cylinder :: displayAxes(void) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

#endif


//============================================================
// operator<<
//============================================================

ostream &operator<<(ostream &output, const Cylinder &cylinder)
	// Overloading the << operator for easy display of Cylinder information on the screen.
{
	output << "MH Unit Number: " << cylinder.d_unitNumber << "\n" 
		<< "Position: " << cylinder.d_position << "\n" 
		<< "Velocity: " << cylinder.d_orientation << "\n" 
		<< "Radius: " << cylinder.d_radius << "\n" 
		<< "Height:"  << cylinder.d_height << "\n" << endl;

	return output;
}