//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Surface.cpp
// Implementation of the class Surface.
//========================================================================  


#include "Cement.hpp"
using namespace std;

//============================================================
// Surface::Surface
//============================================================

Surface::Surface(){}
	// Default Constructor


//============================================================
// Surface::Surface
//============================================================

Surface::Surface(int surfaceNumber, Assembly *assemblyName, FILE *mhaFilePtr)
	// Copy Constructor
{
	char header[15];
	int nodeNumber, springNumber;
	Muscle *mhUnitID;
	int mhUnitNumber;
	double upos,vpos,wpos;
	Node *nodePtr;
	Spring *springPtr;
	int endNode, startNode;
	double restingLength, stiffness, damping;
	
	int i;

	d_surfaceNumber = surfaceNumber;
	d_parentAssembly = assemblyName;

	for(i = 0; i < 3; i++)
		readIfNotComment(mhaFilePtr, header);
	readIfNotComment(mhaFilePtr, &d_numNodes);
	cout << "Number of Nodes in Surface "<< d_surfaceNumber << ": " << d_numNodes << endl;
	readIfNotComment(mhaFilePtr, header);
	readIfNotComment(mhaFilePtr, &d_numSprings);
	cout << "Number of Springs in Surface "<< d_surfaceNumber << ": " << d_numSprings << endl;

	while(1)
	{
		readIfNotComment(mhaFilePtr, header);
		if(strcmp(header,"W") == 0)
			break;
	}
	for(i = 0;i < d_numNodes; i++)
	{
		readIfNotComment(mhaFilePtr, &nodeNumber);
		readIfNotComment(mhaFilePtr, &mhUnitNumber);
		readIfNotComment(mhaFilePtr, &upos);
		readIfNotComment(mhaFilePtr, &vpos);
		readIfNotComment(mhaFilePtr, &wpos);

		mhUnitID = d_parentAssembly->getMHUnit(mhUnitNumber);
		nodePtr = new Node(nodeNumber, mhUnitID, Vector(g_sizeRatio*upos,g_sizeRatio*vpos,g_sizeRatio*wpos));
		this->addNode(nodePtr);
	}
	cout << "Done Creating Nodes" << endl;
	
	if(d_numSprings == 0)
	{
		cout << "Done Creating Springs" << endl;
		return;
	}

	
	while(1)
	{
		readIfNotComment(mhaFilePtr, header);
		if(strcmp(header,"Damping") == 0)
			break;
	}
	for(i = 0;i < d_numSprings; i++)
	{
		readIfNotComment(mhaFilePtr, &springNumber);
		readIfNotComment(mhaFilePtr, &startNode);
		readIfNotComment(mhaFilePtr, &endNode);
		readIfNotComment(mhaFilePtr, &restingLength);
		readIfNotComment(mhaFilePtr, &stiffness);
		
		
		if(stiffness == -1) stiffness = g_collagenStiffness;
		readIfNotComment(mhaFilePtr, &damping);
		if(damping == -1) damping = g_collagenDamping;
		if(restingLength == -1)
			// Use global values if these values are not specified : This must go when
			// we use the Young's modulus to specify stiffness



			springPtr = new Spring(springNumber,
							   getNode(startNode), getNode(endNode),
							   stiffness,damping);
		else
			springPtr = new Spring(springNumber,
							   getNode(startNode), getNode(endNode),
							   stiffness, damping, restingLength);

		this->d_memberSprings.addElement(springPtr);
//		getNode(startNode)->addSpring(springPtr);
//		getNode(endNode)->addSpring(springPtr);
	}
	cout << "Done Creating Springs" << endl;
}

//============================================================
// Surface::~Surface
//============================================================

Surface :: ~Surface(){}
	// Default Destructor



//============================================================
// Surface::getNumber
//============================================================
//xg
int Surface :: getNumber(void) const
	// Access function
{
	return(d_surfaceNumber);
}

//============================================================
// Surface::getNumNodes
//============================================================
//xg
int Surface :: getNumNodes(void) const
	// Access function
{
	return(d_numNodes);
}


//============================================================
// Surface::getNumSprings
//============================================================
//xg
int Surface :: getNumSprings(void) const
	// Access function
{
	return(d_numSprings);
}


//============================================================
// Surface::addNode
//============================================================

void Surface :: addNode(Node *node)
{
	d_memberNodes.addElement(node);
}


//============================================================
// Surface::isMemberOf
//============================================================

bool Surface :: isMemberOf(Node *node) const
	// Checks if a node is a part of a surface
{
	cout << " Not implemented" << endl;
	return true;
}



//============================================================
// Surface::getNode
//============================================================

Node * Surface :: getNode(int nodeNumber) const
	// Access function to nodes
{
	int i;
	for(i=0; i< d_numNodes; i++)
		if((d_memberNodes.getElement(i).getData())->getNumber() == nodeNumber)
			break;
	return d_memberNodes.getElement(i).getData();
}



//============================================================
// Surface::getSpring
//============================================================

SpringBase * Surface :: getSpring(int springNumber) const
	// Access function to nodes
{
	int i;
	for(i=0; i< d_numSprings; i++)
		if((d_memberSprings.getElement(i).getData())->getNumber() == springNumber)
			break;
	return d_memberSprings.getElement(i).getData();
}



//============================================================
// Surface::updateSurface
//============================================================

void Surface :: updateSurface(void)
	// Updates all nodes
{
	int i;
	for(i=0; i< d_numNodes; i++)
		(d_memberNodes.getElement(i).getData())->updateNode();
	for(i=0; i< d_numSprings; i++)
		(d_memberSprings.getElement(i).getData())->updateSpring();

}



//============================================================
// Surface::writeMHAFile
//============================================================

void Surface :: writeMHAFile(FILE *mhaFilePtr) const
	// Write Surface Data to the specified file
{
	int j;
	fprintf(mhaFilePtr,"\nSurface\t%d\n", d_surfaceNumber);
	fprintf(mhaFilePtr,"Nodes\t%d\n", d_numNodes);
	fprintf(mhaFilePtr,"Springs\t%d\n", d_numSprings);
			
	fprintf(mhaFilePtr,"\nNode\tMHUnit\tU\tV\tW\n");
	for(j=0; j < d_numNodes; j++)
		(d_memberNodes.getElement(j).getData())->writeMHAFile(mhaFilePtr);

	fprintf(mhaFilePtr,"\nSpring\tStart\tEnd\tRestL\tSiff\tDamping\n");
	for(j=0; j < d_numSprings; j++)
		(d_memberSprings.getElement(j).getData())->writeMHAFile(mhaFilePtr);
}
	


#ifdef __glut_h__
//============================================================
// Surface::display
//============================================================
void Surface :: display(void) const
{
	int i;
	for(i = 0; i < d_numNodes; i++)
	{
		this->getNode(i)->display();
	}
	for(i = 0; i < d_numSprings; i++)
	{
		this->getSpring(i)->display();
	}
}

#endif

#ifndef __glut_h__
//============================================================
// Surface::display
//============================================================
void Surface :: display(void) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

#endif


//============================================================
// operator<<
//============================================================

ostream &operator<<(ostream &output, const Surface &surface)
	// Overloading the << operator for easy display of Surface information on the screen.
{
	output << "Surface Number: " << surface.getNumber() << endl;
	for(int i=0; i < surface.getNumNodes(); i++)
	{
		output <<  *(surface.getNode(i));
		getchar();
	}
	output << endl;
	return output;
}


