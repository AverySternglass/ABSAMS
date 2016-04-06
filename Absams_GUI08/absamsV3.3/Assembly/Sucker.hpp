//======================================================================== 
// Package			: The Sucker		
// Authors			: Pradeep Setlur
// Start Date		: Mon Aug 1, 2005
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Sucker.hpp
// Interface of the classes Sucker derived from the Assembly class
//========================================================================  
 

#ifndef INCLUDED_Sucker_hpp
#define INCLUDED_Sucker_hpp

#include "Cement.hpp"



//====================================================================
// class Sucker
// -------------------------------------------------------------------
// \brief
// The class \c Sucker represents a MHU assembly that is specifically a sucker
// It has well defined functional units which are clearly defined in the MHA file
// 
// 
//
// The class \c Sucker defines the data type \c Sucker and provides methods 
// for operations such as Initialization, adhesion and ??.
//
// <b>Example Program:</b>
//
// \include Sucker.t.cpp
//========================================================================  
class Sucker : public Assembly
{
public:
	
// ---- Constructor and Destructor -----

	Sucker(int SuckerNumber, const char *mhaFile);
		// Constructor. 

	~Sucker();
		// The default destructor.

// ---- Member Functions ----- 
	MuscleGroup *getAcetabulum(void) const;
		// Provides access to the Acetabulum MHUs

	MuscleGroup *getInfundibulum(void) const;
		// Provides access to the Infundibulum MHUs

	MuscleGroup *getSphincter(void) const;
		// Provides access to the Sphincter MHUs

	MuscleGroup *getExtrinsicMuscles(void) const;
		// Provides access to the Extrinsic MHUs
	
	MuscleGroup *getAcetabulumCap(void) const;
		// Provides access to the Acetabulum cap 

	MuscleGroup *getRimMuscles(void) const;
		// Provides access to the sucker rim musclegroup

	double getInternalVolumeOf(void);
		// Get internal volume of the muscle group Specified
		//  muscleGroup - List of muscles that form a convex shape

	bool isSealed(Muscle *objectMuscle);
		// Checks to see if the sucker rim is in contact with the 
		// external object (also a MHU).
		//  returns   true if object is in contact with all rim MHUs 

	double getAreaOfRimContact(void) const;
		// Calculates the area of rim contact with object when a seal is formed
		//  returns   area of contact 

	Vector getInfundibularOrientation(void) const;
		// Calculate the orientation of the infundibular MHUs from their average orientation

	double getSuckerInternalPressure(void);
		// Calculate the pressure based on change change in volume at the present time
		// from some reference volume

	Vector getSuckerAdhesionForce(void);
		// Calculate the magnitude and direction of the force applied to an object
		// in contact with the sucker rim 
private:
		
	double d_infundibulumVolume;
		// Internal Volume enclosed by the infundibulum MHUs

	double d_sphincterVolume;
		// Internal Volume enclosed by the sphincter MHUs

	double d_acetabulumVolume;
		// Internal Volume enclosed by the acetabulum MHUs

	double d_initialSealedVolume;
		// Internal Volume of sucker at the point when seal is formed

	bool d_sealFormed;
		// True when a seal has been made

};

#endif // INCLUDED_Sucker_hpp