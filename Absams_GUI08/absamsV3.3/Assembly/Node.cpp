//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Node.cpp
// Implementation of the class Node.
//========================================================================  


#include "Bricks.hpp"
#include "Spring.hpp"
#include "Cylinder.hpp"
#include "Box.hpp"
#include<math.h>

//============================================================
// Node::Node
//============================================================

Node::Node(){}
	// Default Constructor


//============================================================
// Node::Node
//============================================================

Node :: Node(int nodeNumber, Muscle *mhUnitID, Vector relativePosition)
	:c_relativePositionInit(relativePosition)
	// Copy Constructor
{
	Vector zero(0,0,0);
	d_nodeNumber = nodeNumber;
	d_mhUnitID = mhUnitID;
	d_relativePosition = relativePosition;
	d_absolutePosition = this->getAbsolutePosition();
	d_velocity = zero;
	d_acceleration = zero;
	d_oldAcceleration = zero;
	d_oldVelocity = zero;
	d_externalForce = zero;
	d_sigmaF = zero;
	d_collisionForce = zero;
	mhUnitID->attachNode(this);
	d_selectTag = 0;
	
}

//============================================================
// Node::~Node
//============================================================

Node :: ~Node(){}
	// Default Destructor



//============================================================
// Node::getNumber
//============================================================

int Node :: getNumber(void) const
	// Access function
{
	return(d_nodeNumber);
}



//============================================================
// Node::relocateNode
//============================================================

void Node::relocateNode(void)
{
	// The procedure is:
	// 1. Calculate the position of the node w.r.t the MHU frame (based 
	//    on the shape of the MHU).
	// 2. Set the absolute position by transformation

	// Step 1: Calculate the position of the node w.r.t the MHU frame (based 
	//         on the shape of the MHU). Since the initial position of the 
	//         node is w.r.t MHU frame, its current position w.r.t MHU frame
	//         is calculated by calculating the ratio of change in dimensions.
	//         For e.g. The w component of the node position w.r.t the MHU 
	//          frame is calculated as h/h0 * Winit where W init is the 
	//          w component of the initial position w.r.t MHU frame.

	Vector currentDimensionVector, restingDimensions;
	if(d_mhUnitID->getShape() == 1)
	{
		Cylinder *tempCylPtr = (Cylinder *) d_mhUnitID;
		currentDimensionVector = Vector(tempCylPtr->d_radius,
			tempCylPtr->d_radius,tempCylPtr->d_height);
		restingDimensions = Vector(tempCylPtr->c_restingRadius,
			tempCylPtr->c_restingRadius,tempCylPtr->c_restingHeight);
	}
	else if (d_mhUnitID->getShape() == 2)
	{
	
		Box *tempBoxPtr = (Box *) d_mhUnitID;
		currentDimensionVector = Vector(tempBoxPtr->d_dimension1,
			tempBoxPtr->c_dimension2,tempBoxPtr->d_dimension3);
		restingDimensions = Vector(tempBoxPtr->c_restingDimension1,
			tempBoxPtr->c_dimension2,tempBoxPtr->c_restingDimension3);
	}
	//Vector dimensionChange(currentDimensionVector - restingDimensions);
	
		
	d_relativePosition = Vector(c_relativePositionInit.getX() * currentDimensionVector.getX()/restingDimensions.getX(),
		c_relativePositionInit.getY() * currentDimensionVector.getY()/restingDimensions.getY(),
		c_relativePositionInit.getZ() * currentDimensionVector.getZ()/restingDimensions.getZ());
		
	// Step 2: Use function to assign the absolute position
	d_absolutePosition = this->getAbsolutePosition();
	
}

//============================================================
// Node::updateNode
//============================================================

void Node::updateNode(void)
{
	d_sigmaF = d_externalForce + d_collisionForce;
	SpringBase *springPtr;
	Vector direction;
	int numSprings = d_connectedSprings.getNumElements();
	for(int i=0; i< numSprings; i++)
	{
		springPtr = d_connectedSprings.getElement(i).getData();
		double magnitude = springPtr->getForce();
		if(springPtr->isStartNode(this))
			direction = this->directionOf(springPtr->d_endNode);
		else if(springPtr->isEndNode(this))
			direction = this->directionOf(springPtr->d_startNode);
		d_sigmaF += magnitude * direction;
	}
	
}



//============================================================
// Node::distanceTo
//============================================================

double Node::distanceTo(Node *target) const
{
	double distance = sqrt(pow((target->d_absolutePosition.getX() - this->d_absolutePosition.getX()),2)
						 + pow((target->d_absolutePosition.getY() - this->d_absolutePosition.getY()),2)
						 + pow((target->d_absolutePosition.getZ() - this->d_absolutePosition.getZ()),2));
	return(distance);
}


//============================================================
// Node::directionOf
//============================================================

Vector Node::directionOf(Node *target) const
{
	Vector direction;
	if(this ->distanceTo(target)!=0) 
	direction = (target->d_absolutePosition - this->d_absolutePosition)/this->distanceTo(target);
	else( direction = Vector(0,0,0));
	return(direction);
}



//============================================================
// Node::setPosition
//============================================================

void Node::setPosition(double xPosition, double yPosition, double zPosition)

{
	setPosition(Vector(xPosition, yPosition, zPosition));
}



//============================================================
// Node::setPosition
//============================================================

void Node::setPosition(Vector position)

{
	d_absolutePosition = position;
	Vector temp = d_absolutePosition - this->d_mhUnitID->d_position;
	Vector invRotationFirstRow = this->d_mhUnitID->d_uAxis;
	Vector invRotationSecondRow = this->d_mhUnitID->d_orientation.crossProduct(this->d_mhUnitID->d_uAxis);
	Vector invRotationThirdRow = this->d_mhUnitID->d_orientation;
	d_relativePosition = Vector(invRotationFirstRow.dotProduct(temp),
								invRotationSecondRow.dotProduct(temp),
								invRotationThirdRow.dotProduct(temp));

}

//============================================================
// Node::setRelativePosition
//============================================================

void Node::setRelativePosition(Vector relativePosition)

{
	d_relativePosition = relativePosition;
	d_absolutePosition = this->getAbsolutePosition();

}

//============================================================
// Node::getVelocity
//============================================================

Vector Node::getVelocity(void) const

{
	return d_mhUnitID->d_linearVelocity 
		+ d_mhUnitID->d_angularVelocity.crossProduct(d_relativePosition);
}

//============================================================
// Node::getRelativePosition
//============================================================

Vector Node::getRelativePosition(void) const

{
	return d_relativePosition;
}


//============================================================
// Node::getAbsolutePosition
//============================================================

Vector Node::getAbsolutePosition(void) const

{
	// This is done in the following steps:
	// 1. Rotate the MHU frame to be parallel to the world frame
	// 2. Calculate Pworld = Cworld + R * P0
	//    where: Pworld - Node position in world frame
	//           Cworld - MHU centre in world frame
	//           R      - Rotation matrix
	//           P0     - Node position w.r.t MHU frame

	// Step 1: Rotate the MHU frame to be parallel to the world frame.
	//         First use the orientation of the MHU (the Z axis of the MHU) and 
	//         the world frame Z-axis to find the vector about which the MHU frame
	//         must be rotated to be aligned with the world frame (using the 
	//         cross product). Next, use the dot product to calculate the angle 
	//         to be rotated about this axis to align the two frames. Then 
	//         calculate the corresponding rotation matrix.

/*	Vector zAxis(0,0,1); 
		// The world frame Z-axis 

	double angleOfRotation;
		// Rotation angle about the axis of rotation

	Vector axisOfRotation((zAxis.crossProduct(this->d_mhUnitID->d_orientation)).normalize());
		// The MHU frame W-axis is the orientation of the MHU
	Vector currentAbsolutePosition;
	Vector firstRow, secondRow, thirdRow;
	double cosTheta, sinTheta;

	if(axisOfRotation != Vector(0,0,0))
		// Check if Z-axis is parallel to the W-axis
	{

		angleOfRotation = acos(zAxis.dotProduct(this->d_mhUnitID->d_orientation));

		double u, v, w, tempVar;
		

		cosTheta = cos(angleOfRotation);
		sinTheta = sin(angleOfRotation);
		
		u = axisOfRotation.getX();
		v = axisOfRotation.getY();
		w = axisOfRotation.getZ();
		tempVar = 1-cosTheta;

		
		firstRow = Vector(u*u+(v*v+w*w)*cosTheta, 
			u*v*tempVar-w*sinTheta, u*w*tempVar+v*sinTheta);
		secondRow = Vector(u*v*tempVar+w*sinTheta, 
			v*v+(u*u+w*w)*cosTheta, v*w*tempVar-u*sinTheta);
		thirdRow = Vector(u*w*tempVar-v*sinTheta, 
			v*w*tempVar+u*sinTheta, w*w+(u*u+v*v)*cosTheta);
		
		//See maple derivation of the rotation matrices -- this needs detail

		currentAbsolutePosition = this->d_mhUnitID->d_position 
			+ Vector(firstRow.dotProduct(d_relativePosition),
			         secondRow.dotProduct(d_relativePosition),
					 thirdRow.dotProduct(d_relativePosition));
	}
	
	else
		// The axis of rotation is the Z-axis(or W-axis)
	{
		Vector xAxis(1,0,0);
			// World frame X-axis
		
		angleOfRotation = acos(xAxis.dotProduct(this->d_mhUnitID->d_uAxis));
		
		cosTheta = cos(angleOfRotation);
		sinTheta = sin(angleOfRotation);

		firstRow = Vector(cosTheta, -sinTheta,0);
		secondRow = Vector(sinTheta,cosTheta, 0);
		thirdRow = Vector(0,0,1);
		
		currentAbsolutePosition = this->d_mhUnitID->d_position 
			+ Vector(firstRow.dotProduct(d_relativePosition),
			         secondRow.dotProduct(d_relativePosition),
					 thirdRow.dotProduct(d_relativePosition));
	}
*/
	
	Vector rotationFirstRow (this->d_mhUnitID->d_uAxis.getX(),
		                     (this->d_mhUnitID->d_orientation.crossProduct(this->d_mhUnitID->d_uAxis)).getX(),
							 this->d_mhUnitID->d_orientation.getX());
	Vector rotationSecondRow (this->d_mhUnitID->d_uAxis.getY(),
		                      (this->d_mhUnitID->d_orientation.crossProduct(this->d_mhUnitID->d_uAxis)).getY(),
							  this->d_mhUnitID->d_orientation.getY());
	Vector rotationThirdRow (this->d_mhUnitID->d_uAxis.getZ(),
		                     (this->d_mhUnitID->d_orientation.crossProduct(this->d_mhUnitID->d_uAxis)).getZ(),
							 this->d_mhUnitID->d_orientation.getZ());
	
	Vector currentAbsolutePosition (rotationFirstRow.dotProduct(d_relativePosition),
									rotationSecondRow.dotProduct(d_relativePosition),
									rotationThirdRow.dotProduct(d_relativePosition));
	currentAbsolutePosition += this->d_mhUnitID->d_position;
	return currentAbsolutePosition;

}



//============================================================
// Node::getResultantForce
//============================================================

Vector Node::getResultantForce(void) const

{
	return d_sigmaF;
}



//============================================================
// Node::getMHUnitID
//============================================================

Muscle *Node::getMHUnitID(void) const

{
	return d_mhUnitID;
}



//============================================================
// Node::setExternalForce
//============================================================

void Node::setExternalForce(Vector extForce)

{
	d_externalForce = extForce;
}



//============================================================
// Node::addCollisionForce
//============================================================

void Node::addCollisionForce(Vector collisionForce)

{
	d_collisionForce += collisionForce;
}



//============================================================
// Node::getCollisionForce
//============================================================

Vector Node::getCollisionForce(void) const

{
	return d_collisionForce;
}



//============================================================
// Node::addSpring
//============================================================
	
void Node::addSpring(SpringBase *spr)

{
	d_connectedSprings.addElement(spr);
}


//============================================================
// Node :: getSelectionTag
//============================================================
int Node :: getSelectionTag(void) const
{
	return d_selectTag;
}

//============================================================
// Node :: setSelectionTag
//============================================================
void Node :: setSelectionTag(int tag)
{
	d_selectTag = tag;
}


//============================================================
// Node::writeMHAFile
//============================================================

void Node :: writeMHAFile(FILE *mhaFilePtr) const
	// Write Node Data to the specified file
{
	fprintf(mhaFilePtr,"%d\t", d_nodeNumber);
	fprintf(mhaFilePtr,"%d\t", d_mhUnitID->getID());
	fprintf(mhaFilePtr,"%lf\t%lf\t%lf\n", d_relativePosition.getX(),
			d_relativePosition.getY(),d_relativePosition.getZ());
}
	
	
	
	
//============================================================
// Node::display
//============================================================
void Node :: display(void) const
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
				display(0.3,0.3,0.3);
				break;
		}
}


//============================================================
// Node::displayForce
//============================================================
void Node :: displayForce(void) const
{
	displayForce(0,0,0);
}


#ifdef __glut_h__
//============================================================
// Node::display
//============================================================
void Node :: display(double red, double green, double blue) const
{
	glPushMatrix();
	glColor4f (red, green, blue, 1.0);
	glPointSize(10);
	glBegin(GL_POINTS);
	glVertex3f(g_scaleFactor*d_absolutePosition.getX(), 
		g_scaleFactor*d_absolutePosition.getY(),
		g_scaleFactor*d_absolutePosition.getZ());
	glEnd();
	glPopMatrix();
}


//============================================================
// Node::displayForce
//============================================================
void Node :: displayForce(double red, double green, double blue) const
{
	glPushMatrix();
	glTranslatef(g_scaleFactor*d_absolutePosition.getX(), 
		g_scaleFactor*d_absolutePosition.getY(),
		g_scaleFactor*d_absolutePosition.getZ());
	if(Vector(0,0,0) != d_sigmaF)
		d_sigmaF.display(red, green, blue);
	glPopMatrix();
}


#endif

#ifndef __glut_h__
//============================================================
// Node::display
//============================================================
void Node :: display(double red, double green, double blue) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}


//============================================================
// Node::displayForce
//============================================================
void Node :: displayForce(double red, double green, double blue) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

#endif


//============================================================
// operator<<
//============================================================

ostream &operator<<(ostream &output, const Node &node)
	// Overloading the << operator for easy display of Node information on the screen.
{
	output << "Node Number: " << node.d_nodeNumber << "\n" 
		<< "Absolute Position: " << node.d_absolutePosition << "\n" 
		<< "Velocity: " << node.d_velocity << "\n" 
		<< "Acceleration: " << node.d_acceleration << "\n" 
		<< "Resultant Force: " << node.d_sigmaF << "\n" 
		<< "Connected Springs:" ;
		for(int i=0; i < node.d_connectedSprings.getNumElements(); i++)
			output << node.d_connectedSprings.getElement(i).getData()->getNumber() << " ";
		output << endl;

	return output;
}
