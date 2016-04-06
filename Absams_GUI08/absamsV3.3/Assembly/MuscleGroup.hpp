//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Tue Aug 2 2005
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: MuscleGroup.hpp
// Interface of the classes MuscleGroup.
//========================================================================  


#ifndef INCLUDED_MuscleGroup_hpp
#define INCLUDED_MuscleGroup_hpp

#include "Bricks.hpp"
#include "List.hpp"
#include "Cylinder.hpp"
#include "Box.hpp"
#include <string.h>

	
//====================================================================
// class MuscleGroup
// -------------------------------------------------------------------
// \brief
// The class \c MuscleGroup describes a group of muscular hydrostat unit 
// 
//
// <b>Example Program:</b>
//
// \include MuscleGroup.t.cpp
//========================================================================  


class MuscleGroup
{
public:

	MuscleGroup(const char *grpName);
		// Constructor

	const char *getGroupName(void) const;
		// Provides access to the group name
	
	bool checkMembership(Muscle *musclePtr) const;
		// Check if the MH Unit is a member of the group

	int getNumMuscles(void) const;
		// Returns the number of muscles in the group

	List<Muscle *> getMuscleList(void) const;
		// Provides access to the muscleList

	Muscle *getMuscle(int muscleNumber) const;
		// Provides access to the muscles in the MuscleGroup
	
	void addMuscle(Muscle *musclePtr);
		// Provides means to add new muscles to a muscle group.

	double getVolume(void);
		// Calculates the volume enclosed by the MHUs in the group
		// CAUTION: The method provides the volume of the convex hull
		//          user must ensure that the MHUs represent the desired
		//          calculations.

	void writeMHAFile(FILE *mhaFilePtr) const;
		// Writes the details of the MuscleGroup to the specified 
		// file.

	~MuscleGroup();
		// Default Destructor

private:
	
	char d_groupName[60];
		// Name of the muscle group

	List<Muscle *> d_muscles;
		// List of MH Units in the group

};


#endif // INCLUDED_MuscleGroup_hpp