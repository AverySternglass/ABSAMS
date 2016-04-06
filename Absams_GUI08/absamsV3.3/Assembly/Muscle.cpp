//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Jun Wu and Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Muscle.cpp
// Implementation of the class Muscle.
//========================================================================  

#include "Bricks.hpp"

double Muscle :: s_ambientPressure = g_ambientPressure;

//============================================================
// Muscle::Muscle
//============================================================

Muscle :: Muscle(int shape, double mass, double bulkModulus, 
				 double muscleDamping, double volume)
			:c_muscleShape(shape),
			 c_mass (mass),
			 c_bulkModulus (bulkModulus),
			 c_muscleDamping (muscleDamping),
			 c_volume (volume)
{
	d_ignoreCollision = false;
	d_musclesInContact.clearList();
	d_selectTag = 0;
}


//============================================================
// Muscle::~Muscle
//============================================================

Muscle :: ~Muscle(){}
	// Default Destructor


//============================================================
// Muscle :: getID
//============================================================
int Muscle :: getID(void) const
{
	return d_unitNumber;
}



//============================================================
// Muscle :: getShape
//============================================================
int Muscle :: getShape(void) const
{
	return c_muscleShape;
}


//============================================================
// Muscle :: applyForceAt
//============================================================
void Muscle :: applyForceAt(Vector force, Vector location)
{
	Vector direction = location - d_position;
	d_sigmaF += force;
	d_sigmaTau += direction.crossProduct(force);		
}

//============================================================
// Muscle :: getSelectionTag
//============================================================
int Muscle :: getSelectionTag(void) const
{
	return d_selectTag;
}

//============================================================
// Muscle :: setSelectionTag
//============================================================
void Muscle :: setSelectionTag(int tag)
{
	d_selectTag = tag;
}

//============================================================
// Muscle :: getIgnoreCollision
//============================================================
bool Muscle :: getIgnoreCollision(void) const
{
	return d_ignoreCollision;
}

//============================================================
// Muscle :: setIgnoreCollision
//============================================================
void Muscle :: setIgnoreCollision(bool ignoreValue)
{
	d_ignoreCollision = ignoreValue;
}

//============================================================
// Muscle :: getContactList
//============================================================
List <Muscle *> *Muscle :: getContactList(void)
{
	return &d_musclesInContact;
}


//============================================================
// Muscle :: updateMuscle
//============================================================
void Muscle :: updateMuscle(void)
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
	
	// Add gravitational force
	this->applyForceAt(Vector(0,0,g_gravity)*this->c_mass, this->getPosition());

	// If in water include buoyant force
	if(medium == WATER)
		this->applyForceAt(Vector(0,0,-(this->c_volume*g_waterDensity)),this->getPosition());

	// Step 2: Update current Inertia Matrix;

	this->updateInertiaTensor();
	
	d_angularMomentum += 0.5*(d_sigmaTau + d_previousSigmaTau) * g_stepSize;


		
	d_angularVelocity = Vector(d_inertiaInverse[0].dotProduct(d_angularMomentum),
					     d_inertiaInverse[1].dotProduct(d_angularMomentum),
						 d_inertiaInverse[2].dotProduct(d_angularMomentum));
	
	// Now we can calculate the Rotation matrix at the new time step (which
	// will determine the orientation of the u-v-w axis w.r.t the x-y-z axis).
	// However, we only need to calculate the u and w axes 
	// to completely define the Muscle rotation. For this, we use
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

	// Now move the nodes to reflect the change in position/orientation of the Muscle
	numNodes = d_attachedNodes.getNumElements();
	//xg
	int i;
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
// Muscle::setAnchor
//============================================================

void Muscle::setAnchor(void)

{
	d_isAnchor = true;
}

//============================================================
// Muscle::isAnchor
//============================================================

bool Muscle::isAnchor(void) const

{
	return(d_isAnchor);
}


//============================================================
// Muscle::setPosition
//============================================================
void Muscle :: setPosition(Vector position)
{
	d_position = position;
}


//============================================================
// Muscle::setOrientation
//============================================================
void Muscle :: setOrientation(Vector orientation)
{
	d_orientation = orientation.normalize(); // Need to ensure it is a unit vector????
}

//============================================================
// Muscle::setUAxis
//============================================================
void Muscle :: setUAxis(Vector uAxis)
{
	d_uAxis = uAxis.normalize(); // Need to ensure it is a unit vector????
}


	
//============================================================
// Muscle::attachNode
//============================================================
void Muscle :: attachNode(Node *node)
{
	d_attachedNodes.addElement(node);
}


//============================================================
// Muscle::detachNode
//============================================================
void Muscle :: detachNode(Node *node)
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
// Muscle::getPosition
//============================================================
Vector Muscle :: getPosition(void) const
{
	return d_position;
}


//============================================================
// Muscle::getAbsoluteCoords
//============================================================

Vector Muscle::getAbsoluteCoords(Vector relativeCoords) const

{
	
	Vector rotationFirstRow (this->d_uAxis.getX(),
		                     (this->d_orientation.crossProduct(this->d_uAxis)).getX(),
							 this->d_orientation.getX());
	Vector rotationSecondRow (this->d_uAxis.getY(),
		                      (this->d_orientation.crossProduct(this->d_uAxis)).getY(),
							  this->d_orientation.getY());
	Vector rotationThirdRow (this->d_uAxis.getZ(),
		                     (this->d_orientation.crossProduct(this->d_uAxis)).getZ(),
							 this->d_orientation.getZ());
	
	Vector currentAbsolutePosition (rotationFirstRow.dotProduct(relativeCoords),
									rotationSecondRow.dotProduct(relativeCoords),
									rotationThirdRow.dotProduct(relativeCoords));
	currentAbsolutePosition += this->d_position;
	return currentAbsolutePosition;

}

//============================================================
// Muscle::getOrientation
//============================================================
Vector Muscle :: getOrientation(void) const
{
	return d_orientation;
}

//============================================================
// Muscle::getUAxis
//============================================================
Vector Muscle :: getUAxis(void) const
{
	return d_uAxis;
}


//============================================================
// Muscle::getUnitQuaternion
//============================================================
void Muscle :: getUnitQuaternion(double *qw, double *qx, double *qy, double *qz) const
{
/*	double m00 = d_uAxis.getX(),
		   m10 = d_uAxis.getY(),
		   m20 = d_uAxis.getZ();

	double m01 = (d_orientation.crossProduct(d_uAxis)).getX(),
		   m11 = (d_orientation.crossProduct(d_uAxis)).getY(),
		   m21 = (d_orientation.crossProduct(d_uAxis)).getZ();

	double m02 = d_orientation.getX(),
		   m12 = d_orientation.getY(),
		   m22 = d_orientation.getZ();

*/	double m02 = d_uAxis.getX(),
		   m12 = d_uAxis.getY(),
		   m22 = d_uAxis.getZ();

	double m00 = (d_orientation.crossProduct(d_uAxis)).getX(),
		   m10 = (d_orientation.crossProduct(d_uAxis)).getY(),
		   m20 = (d_orientation.crossProduct(d_uAxis)).getZ();

	double m01 = d_orientation.getX(),
		   m11 = d_orientation.getY(),
		   m21 = d_orientation.getZ();
	
	
	double T = 1 + m00 + m11 + m22;
	double S;

	if(T > 1e-6) // Avoid divide by zero
	{
		S = sqrt(T) * 2;
		*qw = 0.25 * S;
		*qx = (m21 - m12)/S;
		*qy = (m02 - m20)/S;
		*qz = (m10 - m01)/S;
	}
	else
	{
		if ( m00 > m11 && m00 > m22 )
		{
			S  = sqrt( 1.0 + m00 - m11 - m22 ) * 2;
			*qx = 0.25 * S;
			*qy = (m10 + m01)/S;
			*qz = (m02 + m20)/S;
			*qw = (m21 - m12)/S;
		} 
		else if ( m11 > m22 ) 
		{
			S  = sqrt(1.0 + m11 - m00 - m22) * 2;
			*qx = (m10 + m01)/S;
			*qy = 0.25 * S;
			*qz = (m21 + m12)/S;
			*qw = (m02 - m20)/S;
		}
		else
		{
			S  = sqrt( 1.0 + m22 - m00 - m11 ) * 2;
			*qx = (m02 + m20)/S;
			*qy = (m21 + m12)/S;
			*qz = 0.25 * S;
			*qw = (m10 - m01)/S;
		}
	}


	
}


//============================================================
// operator<<
//============================================================

ostream &operator<<(ostream &output, const Muscle &muscle)
	// Overloading the << operator for easy display of Cylinder information on the screen.
{
	output << "MH Unit Number: " << muscle.d_unitNumber << "\n" 
		<< "Position: " << muscle.d_position << "\n" 
		<< "Velocity: " << muscle.d_orientation << "\n" << endl;

	return output;
}