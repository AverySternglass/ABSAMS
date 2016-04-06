//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: SpringBase.cpp
// Implementation of the class SpringBase.
//========================================================================  


#include "Bricks.hpp"
#include "Globals.h"


//============================================================
// SpringBase::SpringBase
//============================================================

SpringBase::SpringBase(){}
	// Default Constructor



//============================================================
// SpringBase::SpringBase
//============================================================

SpringBase:: SpringBase(int springNumber, Node *startNode, Node *endNode)
	// Copy Constructor
{
	d_springNumber = springNumber;
	d_startNode = startNode;
	d_endNode = endNode;
	c_restingLength = startNode->distanceTo(endNode);
	d_currentLength = c_restingLength;
	d_previousLength = d_currentLength;
	d_force = g_pretension;
	startNode->addSpring(this);
	endNode->addSpring(this);
}

//============================================================
// SpringBase::SpringBase
//============================================================

SpringBase:: SpringBase(int springNumber, Node *startNode, Node *endNode, double restingLength)
	// Copy Constructor
{
	d_springNumber = springNumber;
	d_startNode = startNode;
	d_endNode = endNode;
	c_restingLength = restingLength;
	d_currentLength = c_restingLength;
	d_previousLength = d_currentLength;
	d_force = g_pretension;
	startNode->addSpring(this);
	endNode->addSpring(this);
}

//============================================================
// SpringBase::~SpringBase
//============================================================

SpringBase :: ~SpringBase(){}
	// Default Destructor



//============================================================
// SpringBase::getNumber
//============================================================
//xg
int SpringBase :: getNumber(void) const
	// Access function
{
	return(d_springNumber);
}



//============================================================
// SpringBase::getStartNode
//============================================================

Node *SpringBase :: getStartNode(void) const
	// Access function
{
	return(d_startNode);
}




//============================================================
// SpringBase::getEndNode
//============================================================

Node *SpringBase :: getEndNode(void) const
	// Access function
{
	return(d_endNode);
}



//============================================================
// SpringBase::getForce
//============================================================

double SpringBase:: getForce(void) const
{
	return d_force;
}



//============================================================
// SpringBase::getCurrentLength
//============================================================

double SpringBase:: getCurrentLength(void)
{
	d_currentLength = d_startNode->distanceTo(d_endNode);
	return d_currentLength;

}


//============================================================
// SpringBase::getRestingLength
//============================================================

double SpringBase:: getRestingLength(void) const
{
	return c_restingLength;

}


//============================================================
// SpringBase::isStartNode
//============================================================

bool SpringBase:: isStartNode(Node *node) const
{
	if(node->getNumber() == this->d_startNode->getNumber())
		return true;
	else return false;
}


//============================================================
// SpringBase::isEndNode
//============================================================

bool SpringBase:: isEndNode(Node *node) const
{
	if(node->getNumber() == this->d_endNode->getNumber())
		return true;
	else return false;
}



//============================================================
// operator<<
//============================================================

ostream &operator<<(ostream &output, const SpringBase &springbase)
	// Overloading the << operator for easy display of Spring information on the screen.
{
	output << "Spring Number: " << springbase.d_springNumber << "\n" 
		<< "Current Length: " << springbase.d_currentLength << "\n" 
		<< "Resting Length: " << springbase.c_restingLength << "\n" 
		<< "Force: " << springbase.d_force << "\n" 
		<< "Start Node: " << springbase.d_startNode->getNumber() << "\n" 
		<< "End Node: " << springbase.d_endNode->getNumber() << "\n" << endl;

	return output;
}


//============================================================
// Spring::updateSpring
//============================================================

void SpringBase:: updateSpring(void){}
// Trivial implementation
