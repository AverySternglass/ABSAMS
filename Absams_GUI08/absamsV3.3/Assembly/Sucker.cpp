//======================================================================== 
// Package			: The Sucker
// Authors			: Pradeep Setlur
// Start Date		: Mon Aug 1 2005
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Sucker.cpp
// Implementation of the class Sucker.
//========================================================================  


#include "Sucker.hpp"


//============================================================
// Sucker::Sucker
//============================================================

Sucker::Sucker(int SuckerNumber, const char *mhaFile)
		: Assembly(SuckerNumber, mhaFile)
	// Constructor
{
	// Perform checks to verify if the the MHA file satisfies the properties of a sucker
	if (this->getNumMuscleGroups() != 6)
	{
		printf(" MHA file does not describe a sucker: Not enough muscle groups\n");
		exit(0);
	}
	if(strcmp(this->getMuscleGroup(0)->getGroupName(), "AcetabulumCap") != 0)
	{
		printf(" First Muscle group must be named \"AcetabulumCap\"\n");
		exit(0);
	}
	if(strcmp(this->getMuscleGroup(1)->getGroupName(), "Acetabulum") != 0)
	{
		printf(" Second Muscle group must be named \"Acetabulum\"\n");
		exit(0);
	}
	if(strcmp(this->getMuscleGroup(2)->getGroupName(), "Sphincter") != 0)
	{
		printf(" Third Muscle group must be named \"Sphincter\"\n");
		exit(0);
	}
	if(strcmp(this->getMuscleGroup(3)->getGroupName(), "Infundibulum") != 0)
	{
		printf(" Fourth Muscle group must be named \"Infundibulum\"\n");
		exit(0);
	}
	if(strcmp(this->getMuscleGroup(4)->getGroupName(), "ExtrinsicMuscles") != 0)
	{
		printf(" Fifth Muscle group must be named \"ExtrinsicMuscles\"\n");
		exit(0);
	}
	if(strcmp(this->getMuscleGroup(5)->getGroupName(), "SuckerRim") != 0)
	{
		printf(" Sixth Muscle group must be named \"SuckerRim\"\n");
		exit(0);
	}
	d_sealFormed = false;

}

//============================================================
// Sucker::getAcetabulumCap
//============================================================

MuscleGroup *Sucker::getAcetabulumCap(void) const
	// Access function
{
	return this->getMuscleGroup(0);
}


//============================================================
// Sucker::getAcetabulum
//============================================================

MuscleGroup *Sucker::getAcetabulum(void) const
	// Access function
{
	return this->getMuscleGroup(1);
}


//============================================================
// Sucker::getSphincter
//============================================================

MuscleGroup *Sucker::getSphincter(void) const
	// Access function
{
	return this->getMuscleGroup(2);
}

//============================================================
// Sucker::getInfundibulum
//============================================================

MuscleGroup *Sucker::getInfundibulum(void) const
	// Access function
{
	return this->getMuscleGroup(3);
}

//============================================================
// Sucker::getExtrinsicMuscles
//============================================================

MuscleGroup *Sucker::getExtrinsicMuscles(void) const
	// Access function
{
	return this->getMuscleGroup(4);
}


//============================================================
// Sucker::getRimMuscles
//============================================================

MuscleGroup *Sucker::getRimMuscles(void) const
	// Access function
{
	return this->getMuscleGroup(5);
}


//============================================================
// Sucker::getInternalVoulmeOf
//============================================================

double Sucker::getInternalVolumeOf(void)
	// Access function
{
	this->d_acetabulumVolume = this->getAcetabulum()->getVolume();
	this->d_infundibulumVolume = this->getInfundibulum()->getVolume();

	return (d_acetabulumVolume + d_infundibulumVolume);
}


//============================================================
// Sucker::isSealed
//============================================================

bool Sucker::isSealed(Muscle *objectMuscle)
	// Access function
{
	Muscle *tempMusclePtr;
	for(int i = 0; i < this->getRimMuscles()->getNumMuscles(); i++)
	{
		bool foundInList = false;
		tempMusclePtr = this->getRimMuscles()->getMuscle(i);
		for(int j=0;j< tempMusclePtr->getContactList()->getNumElements();j++)
			if(tempMusclePtr->getContactList()->getElement(j).getData()->getID()
												== objectMuscle->getID()) foundInList = true;
		if(!foundInList) 
		{
			d_sealFormed = false;
			return d_sealFormed;
		}
	}

	if(d_sealFormed == false)
		d_initialSealedVolume = this->getInternalVolumeOf();
	d_sealFormed = true;
	return d_sealFormed;
}

//============================================================
// Sucker::getAreaOfRimContact
//============================================================

double Sucker::getAreaOfRimContact(void) const
	// Calculate area of rim contact
	// Mod by FG 10/8/05
{

	//-----------------------Temp ----------------------
//	FILE *fp;
//	fp = fopen("area_log.txt","a");
	//-----------------------Temp ----------------------

	double totalHeight = 0, area = 0;
	Cylinder *cylPtr;

	int numInfMuscles = this->getInfundibulum()->getNumMuscles();

	for(int i=0;i<numInfMuscles; i++)
	{
		cylPtr = (Cylinder *)this->getInfundibulum()->getMuscle(i);
		totalHeight += cylPtr->getHeight();
	}
	
	area = this->getInfundibulum()->getVolume()/(totalHeight/numInfMuscles);

	//-----------------------Temp ----------------------

//	fprintf(fp,"AREA = %lf\n",area);
//	fclose(fp);

	//-----------------------Temp ----------------------


	return (area);
}

//============================================================
// Sucker::getSuckerAdhesionForce
//============================================================

Vector Sucker::getSuckerAdhesionForce(void)
	// Calculate the magnitude and direction of the force applied to an object
	// in contact with the sucker rim 
	// Written by FG 10/09/05
{

	Vector forceDirection, adhesionForce;
	double forceMagnitude;

	forceDirection = -1*this->getInfundibularOrientation();
	forceDirection.normalize();

	forceMagnitude =this->getSuckerInternalPressure()/this->getAreaOfRimContact();

	adhesionForce = forceMagnitude * forceDirection;

	return (adhesionForce);
}

//============================================================
// Sucker::getInfundibularOrientation
//============================================================

Vector Sucker::getInfundibularOrientation(void) const
	// Calculate the orientation of the infundibular MHUs from their average orientation
	// Written by FG 10/09/05
{
	Vector CummulativeVector(0,0,0);

	for(int i=0; i<this->getInfundibulum()->getNumMuscles(); i++)
		CummulativeVector += this->getInfundibulum()->getMuscle(i)->getOrientation();

	return (CummulativeVector/(this->getInfundibulum()->getNumMuscles()));
}

//============================================================
// Sucker::getSuckerInternalPressure
//============================================================

double Sucker::getSuckerInternalPressure(void)
	// Calculate the pressure based on change change in volume at the present time
	// from some reference volume
	// Written by FG 10/09/05
{
	double deltaPressure, currentVolume;

	currentVolume = 0;
	currentVolume = this->getInternalVolumeOf();

	deltaPressure = - g_bulkModulus * (currentVolume - d_initialSealedVolume)/d_initialSealedVolume;


	return (deltaPressure);
}


//============================================================
// Sucker::~Sucker
//============================================================

Sucker :: ~Sucker(){}
	// Default Destructor


