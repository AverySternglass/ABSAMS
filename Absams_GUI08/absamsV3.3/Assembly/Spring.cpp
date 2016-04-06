//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Spring.cpp
// Implementation of the class Spring.
//========================================================================  


#include "Spring.hpp"
#include "Globals.h"


//============================================================
// Spring::Spring
//============================================================

Spring:: Spring(int springNumber, Node *startNode, Node *endNode)
	: SpringBase(springNumber, startNode, endNode),
	c_stiffness (g_collagenStiffness),
	c_damping (g_collagenDamping)
	// Copy Constructor
{
	
	d_currentLength = g_pretension/c_stiffness + c_restingLength;
	
}



//============================================================
// Spring::Spring
//============================================================

Spring:: Spring(int springNumber, Node *startNode, Node *endNode,  
				double stiffness, double damping)
	: SpringBase(springNumber, startNode, endNode),
	c_stiffness (stiffness),
	c_damping (damping)
	// Copy Constructor
{
	
	d_currentLength = g_pretension/c_stiffness + c_restingLength;
	
}


//============================================================
// Spring::Spring
//============================================================

Spring:: Spring(int springNumber, Node *startNode, Node *endNode,  
				double stiffness, double damping, double restingLength)
	: SpringBase(springNumber, startNode, endNode, restingLength),
	c_stiffness (stiffness),
	c_damping (damping)
	// Copy Constructor
{
	
	d_currentLength = g_pretension/c_stiffness + c_restingLength;
	
}


//============================================================
// Spring::updateSpring
//============================================================

void Spring:: updateSpring(void)
{
//	if(d_springNumber == 3)
//		cout << "here";
	d_currentLength = d_startNode->distanceTo(d_endNode);
	double rateOfLengthChange = (d_currentLength - d_previousLength)/g_stepSize;
	if(d_currentLength > c_restingLength)
		d_force = c_stiffness * (d_currentLength - c_restingLength)
				+ c_damping * rateOfLengthChange;
	else d_force = 0.0;
	d_previousLength = d_currentLength;
}


//============================================================
// Spring::writeMHAFile
//============================================================

void Spring :: writeMHAFile(FILE *mhaFilePtr) const
	// Write Spring Data to the specified file
{
	fprintf(mhaFilePtr,"%d\t", d_springNumber);
	fprintf(mhaFilePtr,"%d\t", d_startNode->getNumber());
	fprintf(mhaFilePtr,"%d\t", d_endNode->getNumber());
	fprintf(mhaFilePtr,"%lf\t", c_restingLength);
	fprintf(mhaFilePtr,"%lf\t", c_stiffness);
	fprintf(mhaFilePtr,"%lf\n", c_damping);
}



//============================================================
// Spring::display
//============================================================
void Spring :: display(void) const
{
	display(0.3,0.3,0.3);
}


#ifdef __glut_h__
//============================================================
// Spring::display
//============================================================
void Spring :: display(double red, double green, double blue) const
{
	glPushMatrix();
	glColor4f (red, green, blue, 1.0);
	glPointSize(10);
	glBegin(GL_LINES);
	glVertex3f(g_scaleFactor*(this->getStartNode()->getAbsolutePosition()).getX(), 
			g_scaleFactor*(this->getStartNode()->getAbsolutePosition()).getY(),
			g_scaleFactor*(this->getStartNode()->getAbsolutePosition()).getZ());
		glVertex3f(g_scaleFactor*(this->getEndNode()->getAbsolutePosition()).getX(), 
			g_scaleFactor*(this->getEndNode()->getAbsolutePosition()).getY(),
			g_scaleFactor*(this->getEndNode()->getAbsolutePosition()).getZ());
	glEnd();
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

#endif