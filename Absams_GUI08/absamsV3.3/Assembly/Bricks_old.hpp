//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Jun Wu & Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Bricks.hpp
// Interface of the classes Cylinder, Spring and Node.
//========================================================================  


#ifndef INCLUDED_Bricks_hpp
#define INCLUDED_Bricks_hpp

#include "Globals.h"
#include "Vector.hpp"
#include "List.hpp"

	
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


class Cylinder
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
	
	int getID(void) const;
		// Provides access to the MH Unit ID
	
	void shapeChange(void);
		// Calculates change in dimensions of the Muscular Hydrostat Unit

	void updateCylinder(void);
		// Calculates change in position and orientation of the MH Unit 
		// without a change in it shape
	
	void setModel(int model);
		// Set model for simulation


	
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

	void setPosition(Vector position);
		// Set position of Muscular Hydrostat Unit

	void setOrientation(Vector orientation);
		// Set orientation of Muscular Hydrostat Unit

	void setUAxis(Vector uAxis);
		// Set U-Axis of Muscular Hydrostat Unit

	void attachNode(Node *node);
		// Attaches a node on the surface to the MH Unit

	void detachNode(Node *node);
		// Detaches a node from the MH Unit

	Node *createCollisionNode(Vector absPosition);
		// Creates and adds a node (upon collision) to the 
		// MH Unit to the list of collision nodes.
		// This is used to apply the collision forces on the MHU.
		//  return		pointer to the created node

	void removeCollisionNode(Node *node);
		// Deletes a node added due to collision from the List

	int getNumCollisionNodes(void) const;
		// Returns the number of collision nodes (points
		// of collision) on the cylinder.

	void setAnchor(void);
		// Sets the Cylinder as an anchor node

	bool isAnchor(void) const;
		// Provides access to the d_isAnchor variable
		//  return		true if the cylinder is anchored 
		//				false otherwise

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
	
	Vector getPosition(void) const;
		// Provides access to the data member position
		//  return		Position of the MHU

	Vector getOrientation(void) const;
		// Provides access to the data member orientation
		//  return		Orientation of the MHU

	Vector getUAxis(void) const;
		// Provides access to the data member U-Axis
		//  return		Orientation of the MHU

	void updateInertiaTensor(void);
		// Updates the current Inertia matrix w.r.t the world frame 
		// using the current orientation of the MHU. 

	void getUnitQuaternion(double *qw, double *qx, double *qy, double *qz) const;
		// Sets the quaternion [ qw,qx,qy,qz] to represent 
		// the orientation of the MHU. Note that it has to 
		// be a unit quaternion.

	void applyForceAt(Vector force, Vector location);
		// Adds the effect of the specified force to the 
		// total force and torque on the MHU
	
	Vector getInstantaneousVelocity(Vector location) const;
		// Calulates the instantaneous velocity at a particular
		// point on the cylinder
	
	double getInvIstar(Vector normal, Vector location);
		// Evaluates the equivalent inertia using
		// invIstar = 1/M + n.(invI* (r x n)) x r

	void display(void) const;
		// Displays the MH Unit in OpenGL window. If OpenGL is 
		// not available, error is printed.

	void display(double red, double green, double blue) const;
		// Displays the MH Unit in OpenGL window in the specified color.
		// If OpenGL is not available, error is printed.

	void displayForce(void) const;
		// Displays the resultant force at the COM of the cylinder 
		// in OpenGL window. If OpenGL is not available, error is printed.

	void displayAxes(void) const;
		// Displays the u-v-w frame at the COM of the cylinder 
		// in OpenGL window. If OpenGL is not available, error is printed.

	void displayForce(double red, double green, double blue) const;
		// Displays the resultant force at the COM of the cylinder
		// in OpenGL window in the specified color. 
		// If OpenGL is not available, error is printed.

	friend ostream &operator<<(ostream &output, const Cylinder &cylinder);
		// This function overloads the ostream \c << operator
		// to output the essential quantities of the Cylinder \a cylinder 
 		// to the output stream separated by white spaces(e.g. spaces).
		// Example: \code cout << cylinder; \endcode

private:
	 
	 int d_unitNumber;
		// Uniquely identifies the MH Unit

	 List<Node *> d_attachedNodes;
		// Nodes that are attached to the MH Unit

	List<Node *> d_collisionNodes;
		// Nodes that are formed at the point of collision

	 double d_radius;
		// The radius of the muscular hydrostat unit

	 double d_height;
		// The height(length) of the muscular hydrostat unit
	
	 int d_model;
		// Model type 1 = BCR 2 = Constrained dynamics

	 static double s_ambientPressure;
		// The pressure applied by the surrounding medium on the MHU

	 double d_pressureConstantVolume;
		// The pressure applied by the internal pressure

	 const double c_mass;
		// The total mass of the MHU

	 const double c_bulkModulus;
		// The bulk modulus of the material of the MHU

	 const double c_radialMuscleStiffness;
		// The stiffness of the material of the MHU in the radial direction

	 const double c_longitudinalMuscleStiffness;
		// The stiffness of the material of the MHU in the longitudinal direction

	 const double c_muscleDamping;
		// The structural damping of the material of the MHU
	 
	 const double c_restingRadius;
		// The initial radius of the MHU. The unit attempts to get back 
		// to this radius after it is deformed
	 
	 const double c_restingHeight;
		// The initial height of the MHU. The unit attempts to get back 
		// to this height after it is deformed


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
	 
	 bool d_isAnchor;
		// Is it a fixed cylinder w.r.t global frame of reference

	 Vector d_position;
	 	 // Position of the center of the MHU w.r.t the global frame

	 Vector d_linearVelocity;
		//  Linear velocity of the center of the MHU w.r.t the global frame

	 Vector d_previousLinearVelocity;
		//  Linear velocity of the center of the MHU w.r.t the global frame

	 Vector d_linearAcceleration;
		// Linear acceleration of the center of the MHU w.r.t the global frame
	 
	 Vector d_previousLinearAcceleration;
		// Linear acceleration of the center of the MHU w.r.t the global frame

	 Vector d_orientation;
		// Unit vector that represents the orientation of the MHU

	 Vector d_uAxis;
		// Unit vector that represents the U-axis of the UVW frame fixed to the MHU

	 Vector d_angularVelocity;
		//  Angular velocity of the center of the MHU w.r.t the global frame

	 Vector d_previousAngularVelocity;
		//  Angular velocity of the center of the MHU w.r.t the global frame

	 Vector d_angularMomentum;
		// Angular momentum of the center of the MHU w.r.t the global frame

	 Vector d_sigmaF;
		// Resultant force acting at the COM of the MH Unit which causes translation 
		// of the entire unit without causing a change in shape.

	 Vector d_sigmaTau;
		// Resultant torque acting at the COM of the MH Unit which causes rotation 
		// of the entire unit without causing a change in shape.

	 Vector d_previousSigmaTau;
		// Torque at previous time step

	 Vector d_inertiaInverse[3];
		// The Inertia tensor w.r.t the world frame and hence changes  
		// with time. 

};



//====================================================================
// class SpringBase
// -------------------------------------------------------------------
// \brief
// The class \c SpringBase is an abstract class that will be used to derive 
// types of springs to describe the material properties of the connective tissue
//
// 
// 
//
// The class \c SpringBase defines the data type \c SpringBase and provides methods 
// for operations such as ??, ?? and ??.
//
// <b>Example Program:</b>
//
// \include Spring.t.cpp
//========================================================================  


class SpringBase
{
	friend class Node;
	
public:
	
// ---- Constructor and Destructor -----

	SpringBase(int springNumber, Node *startNode, Node *endNode);
		// Copy Constructor. 

	SpringBase(int springNumber, Node *startNode, Node *endNode, double restingLength);
		// Copy Constructor.

	~SpringBase();
		// The default destructor.

// ---- Member Functions ----- 

	int getNumber(void) const;
		// This function provides access to the Spring number to help identify
		// the spring
		//  return		Unique identifier for the Spring (spring number)
	
	double getForce(void) const;
		// This function provides access to the data member d_force
		//  return		Force exerted by the spring

	virtual void updateSpring(void) ;
		// This function calculates the force exerted by the spring
		// on the nodes. 		
	
	double getCurrentLength(void);
		// This function provides access to the data memeber d_currentLength
		// It also updates the variable which is why it is not declared constant
		//  return		Current Length of the spring

	double getRestingLength(void) const;
		// This function provides access to the data memeber c_currentLength
		//  return		The resting length of the spring

	Node *getStartNode(void) const;
		// This function provides access to the data member d_StartNode
		// of the Spring
		//  return		Pointer to the Starting Node of the Spring
	
	Node *getEndNode(void) const;
		// This function provides access to the data member d_EndNode
		// of the Spring
		//  return		Pointer to the Ending Node of the Spring
	
	bool isStartNode(Node *node) const;
		// Checks if a node is the start node
		//  return		True if the node is the Start Node

	bool isEndNode(Node *node) const;
		// Checks if a node is the end node
		//  return		True if the node is the End Node
	
	friend ostream &operator<<(ostream &output, const SpringBase &springbase);
		// This function overloads the ostream \c << operator
		// to output the essential quantities of the Spring \a spring to the output stream
 		// separated by white spaces(e.g. spaces).
		// Example: \code cout << spring; \endcode
		
private:
	
	SpringBase();
		// The default constructor. Do not allow creation of a 
		// spring without assigning end nodes to it.
		
	
protected:
	
	int d_springNumber;
		// Uniquely identifies the spring

	double d_currentLength;
		// Current length of the spring

	double c_restingLength;
		// Length at which spring generates no force

	Node *d_startNode;
		// Node at one extremity of the spring

	Node *d_endNode;
		// Node at the other extremity of the spring

	double d_previousLength;
		// Length of the spring during the previous time sample

	double d_force;
		// Force generated by the spring. WLOG forces that push the 
		// nodes away will be considered positive. The force calculated
		// is a scalar and the directions are dealt with by each node


};




class Node 
{
	friend class Cylinder;
public:
	
// ---- Constructor and Destructor -----

	Node();
		// The default constructor.
	
	Node(int nodeNumber, Cylinder *mhUnitID, Vector relativePosition);
		// Constructor. relativePosition is the position w.r.t the MHU
		// frame of reference.

	~Node();
		// The default destructor.

	int getNumber(void) const;
		// This function provides access to the Node number to help identify
		// the node
		//  return		Unique identifier for the node (node number)
	
	void updateNode(void);
		// This function evaluates the dynamics of the node i.e., the 
		// acceleration, velocity and position vectors.
		
	void relocateNode(void);
		// This function repositions the node depanding on the 
		// shape change of the corresponding cylinder
	
	void setPosition(double xPosition, double yPosition, double zPosition);
		// Provides access to the position vector

	void setPosition(Vector position);
		// Provides access to the position vector

	Vector getRelativePosition(void) const;
		// Calculates position of the node in the world 
		// coordinates
		//   return		Vector describing the position of the node 
		//				in the world frame of reference

	Vector getAbsolutePosition(void) const;
		// Calculates position of the node in the MH Unit fixed 
		// coordinates
		//   return		Vector describing the position of the node 
		//				in the MH Unit frame of reference

	double distanceTo(Node *destination) const;
		// Calculates the distance to the destination node
		//  return		Distance to target node

	Vector directionOf(Node *destination) const;
		// Calculates the direction of the destination node
		//  return		Unit vector representing the direction of the destination

	void addSpring(SpringBase *spr);
		// Adds a spring to the list of springs by using the list functions


	Vector getResultantForce(void) const;
		// Provides access to the data member d_sigmaF

	Vector getVelocity(void) const;
		// Returns the instantaneous velocity of the node

	Cylinder *getMHUnitID(void) const;
		// Provides access to the data member d_mhUnitID
	
	void setExternalForce(Vector extForce);
		// Allows the addition of an additional external force on the node
		//  extForce		Applied external force
	
	void addCollisionForce(Vector collisionForce);
		// Applies a force due to collision on the node
		//  collisionForce		Force due to collision

	Vector getCollisionForce(void) const;
		// Provides access to the data member d_collisionForce
	
	void writeMHAFile(FILE *mhaFilePtr) const;
		// Writes relavant Node data to the specified file


	void display(void) const;
		// Displays the Node in OpenGL window. If OpenGL is 
		// not available, error is printed.

	void display(double red, double green, double blue) const;
		// Displays the Node in OpenGL window in the specified color.
		// If OpenGL is not available, error is printed.

	void displayForce(void) const;
		// Displays the resultant force on the Node in OpenGL window. 
		// If OpenGL is not available, error is printed.

	void displayForce(double red, double green, double blue) const;
		// Displays the resultant force on the Node in OpenGL window
		// in the specified color. If OpenGL is not available, error is printed.

	friend ostream &operator<<(ostream &output, const Node &node);
		// This function overloads the ostream \c << operator
		// to output the essential quantities of the Node \a node to the output stream
 		// separated by white spaces(e.g. spaces).
		// Example: \code cout << node; \endcode

private:
	
	int d_nodeNumber;
		// Uniquely identifies the node

	int d_numNeighbors;
		// Number of nodes connected DIRECTLY by connective tissue

	List< SpringBase *> d_connectedSprings;
		// List of spring-damper combinations that describe
		// the interaction of the node with its neighbors

	Vector d_absolutePosition;
		// Vector representing the position of the node in the 
		// global frame of reference

	Vector d_relativePosition;
		// Vector representing the position of the node in the 
		// MHU frame of reference

	const Vector c_relativePositionInit;
		// Vector representing the location of the node on the 
		// MH Unit. It is the initial position vector w.r.t a 
		// frame fixed to the center of the MH Unit.

	Vector d_velocity;
		// The vector describing the current velocity of the node

	Vector d_oldVelocity;
		// Velocity of the node in the previous time sample

	Vector d_acceleration;
		// Acceleration Vector of the node

	Vector d_oldAcceleration;
		// Acceleration of the node in the previous time sample

	Vector d_sigmaF;
		// Resultant force vector acting on the node 

	Vector d_externalForce;
		// External force vector acting on the node 

	Vector d_collisionForce;
		// External force vector acting on the node 

	Cylinder *d_mhUnitID;
		// The MH Unit that houses the node

};


#endif // INCLUDED_Bricks_hpp