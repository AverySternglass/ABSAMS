//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Tue Aug 2 2005
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: MuscleGroup.cpp
// Implementation of the class MuscleGroup.
//========================================================================  

#include "MuscleGroup.hpp"


//============================================================
// MuscleGroup::MuscleGroup
//============================================================

MuscleGroup :: MuscleGroup(const char *grpName)
{
	strcpy(d_groupName,grpName);
}


//============================================================
// MuscleGroup::~MuscleGroup
//============================================================

MuscleGroup :: ~MuscleGroup(){}
	// Default Destructor


//============================================================
// MuscleGroup :: getGroupName
//============================================================
const char * MuscleGroup :: getGroupName(void) const
{
	return d_groupName;
}


//============================================================
// MuscleGroup :: getNumMuscles
//============================================================
int MuscleGroup :: getNumMuscles(void) const
{
	return d_muscles.getNumElements();
}


//============================================================
// MuscleGroup :: getMuscleList
//============================================================
List<Muscle *> MuscleGroup :: getMuscleList(void) const
{
	return d_muscles;
}


//============================================================
// MuscleGroup :: getMuscle
//============================================================
Muscle *MuscleGroup :: getMuscle(int muscleNumber) const
{
	return d_muscles.getElement(muscleNumber).getData();
}


//============================================================
// MuscleGroup :: checkMembership
//============================================================
bool MuscleGroup :: checkMembership(Muscle *musclePtr) const
{
	for(int i=0; i<d_muscles.getNumElements(); i++)
		if(d_muscles.getElement(i).getData()->getID() == musclePtr->getID())
			return true;
	return false;
}


//============================================================
// MuscleGroup :: addMuscle
//============================================================
void MuscleGroup :: addMuscle(Muscle *musclePtr)
{
	d_muscles.addElement(musclePtr);
}

//============================================================
// MuscleGroup :: getVolume
//============================================================
double MuscleGroup :: getVolume(void)
{
	Muscle *musclePtr;
	Vector firstPointRelative, secondPointRelative,
		   firstPointAbsolute, secondPointAbsolute;
	int i, numPoints, dim, index;
	coordT *points;
	
	qh_initqhull_start (NULL, stdout, stderr);

	numPoints = 2.0*this->getNumMuscles(); // two points per MHU
	dim = 3;
	points = (coordT *)malloc(dim*numPoints*sizeof(coordT));
	for(i=0;i<this->getNumMuscles();i++)
	{
		musclePtr = d_muscles.getElement(i).getData();
		if(musclePtr->getShape() == 1) // Cylinder
		{
			Cylinder *cylinderPtr = (Cylinder *) musclePtr;
			firstPointRelative = Vector(0,0,-0.5*cylinderPtr->getHeight());
			secondPointRelative = Vector(0,0,0.5*cylinderPtr->getHeight());
		}
		if(musclePtr->getShape() == 2) // Box
		{
			cout << "volume for boxes not implemented" << endl;
			exit(0);
		}
		
		firstPointAbsolute = musclePtr->getAbsoluteCoords(firstPointRelative);
		secondPointAbsolute = musclePtr->getAbsoluteCoords(secondPointRelative);
		index = 6*i;
		*(points+index) = (coordT)firstPointAbsolute.getX();
		*(points+index+1) = (coordT)firstPointAbsolute.getY();
		*(points+index+2) = (coordT)firstPointAbsolute.getZ();
		*(points+index+3) = (coordT)secondPointAbsolute.getX();
		*(points+index+4) = (coordT)secondPointAbsolute.getY();
		*(points+index+5) = (coordT)secondPointAbsolute.getZ();
	}

    qh_init_B (points, numPoints, dim, True);
    qh_qhull();
    qh_getarea(qh facet_list);

	return qh totvol;
}

//============================================================
// MuscleGroup::writeMHAFile
//============================================================

void MuscleGroup :: writeMHAFile(FILE *mhaFilePtr) const
	// Write Surface Data to the specified file
{
	int j;
	fprintf(mhaFilePtr,"\n%s\t%d\t", d_groupName, this->getNumMuscles());
	for(j=0; j < this->getNumMuscles(); j++)
		fprintf(mhaFilePtr, "%d\t",(d_muscles.getElement(j).getData())->getID());
}