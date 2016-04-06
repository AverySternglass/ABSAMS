//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Command.hpp
// Interface of the class Command
//========================================================================  
 

#ifndef INCLUDED_Command_hpp
#define INCLUDED_Command_hpp

#include<math.h>
#include "..\Assembly\List.hpp"
#include<string.h>
#include "..\Assembly\Cement.hpp"

//====================================================================
// class ActionItem
// -------------------------------------------------------------------
// \brief
// The class \c ActionItem is a single action that needs to be taken on the  
// assembly. Used with the Command class to easily apply commands to the 
// assembly
// 
// 
//
// The class \c ActionItem defines the data type \c ActionItem and provides 
// access functions..
//
//
//========================================================================  


class ActionItem
{

public:
	
// ---- Constructor and Destructor -----

	ActionItem(int mhuID, double actionTime, int commandType, double commandMagnitude);
		// Constructor. 

	~ActionItem();
		// The default destructor.

// ---- Member Functions ----- 

	double getActionTime(void) const;
		// This function provides access to the time when the action 
		// is to be taken.
		//  return		Time of action of command
	
	int getCommandType(void) const;
		// Provides access to the data member 
		//  return		command type

	double getCommandMagnitude(void) const;
		// Provides access to the magnitude of the command in the  
		// action item
		//  return magnitude of command application

	void performAction(Assembly *assemblyPtr) const;
		// Performs the required change of command in the specified 
		// Assembly. If a particular action cannot be taken, an error
		// is printed on the screen. The simulation however, will 
		// be allowed to proceed.
		//  assemblyPtr		Pointer to the assembly on which the action 
		//					is to be taken

private:
	
	ActionItem();
		// The default constructor. Do not allow creation of a 
		// ActionItem class without initializing it.
		
	int d_mhuID;
		// ID of the MHU
	
	double d_actionTime;
		// Time of action of the action item

	int d_commandType;
		// Type of command of the action item
		// 0 - Along dimension 1
		// 1 - Along dimension 2
		// 2 - Along dimension 3

	double d_commandMagnitude;
		// Magnitude of the command
	
};


//====================================================================
// class Command
// -------------------------------------------------------------------
// \brief
// The class \c Command is a complete list of the commands to be applied on a 
// given assembly. Each command can be converted to two action items - one 
// that applies the command and another that stops or changes the application. 
// The purpose of this class is to do the required book keeping. 
// 
// 
//
// The class \c Command defines the data type \c Command and provides methods 
// for operations.
//
// <b>Example Program:</b>
//
// \include Command.t.cpp
//========================================================================  


class Command
{

public:
	
// ---- Constructor and Destructor -----

	Command(const char *commandFile); //, Assembly *AssemblyName);
		// Constructor. 
	

	~Command();
		// The default destructor.

// ---- Member Functions ----- 

	
	void applyCommand( Assembly *assemblyPtr, double currentTime);
		// This function checks for the next command to be applied 
		// at the correct time and does the required application
		

	void addCommand( int mhuID, double timeOn, double timeOff, int type, double magnitude);
		// adds the specified command to the list in the
		// appropriate position (in the list)

	void deleteSubsequentActions(double deletionTime);
		// Deletes all action items to be performed after the specified time
		


private:
	
	Command();
		// The default constructor. Do not allow creation of a 
		// Command class without initializing it.
		
	int d_numActionItems;
		// Total number of Action Items in the Command sequence

	int d_currentActionItem;
		// Current Action Item being processed

	List< ActionItem *> d_actionItems;
		// List of Action Items in ascending order of time

};



#endif // INCLUDED_Command_hpp