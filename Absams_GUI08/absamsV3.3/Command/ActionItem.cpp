//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: ActionItem.cpp
// Implementation of the class ActionItem.
//========================================================================  


#include "Command.hpp"
#include <math.h>



//============================================================
// ActionItem::ActionItem
//============================================================

ActionItem::ActionItem(){}
	// Default Constructor


//============================================================
// ActionItem::ActionItem
//============================================================

ActionItem::ActionItem(int mhuID, double actionTime, int commandType, double commandMagnitude)
		// Constructor.
{
	d_mhuID = mhuID;

	d_actionTime = actionTime;

	d_commandType = commandType;

	d_commandMagnitude = commandMagnitude;
}

//============================================================
// ActionItem::~ActionItem
//============================================================

ActionItem ::~ActionItem(){}
	// Default Destructor


//============================================================
// ActionItem::getActionTime
//============================================================

double ActionItem ::getActionTime(void) const
{
	return (d_actionTime);
}

//============================================================
// ActionItem::getCommandType
//============================================================

int ActionItem ::getCommandType(void) const
{
	return (d_commandType);
}

//============================================================
// ActionItem::getCommandMagnitude
//============================================================

double ActionItem ::getCommandMagnitude(void) const
{
	return (d_commandMagnitude);
}

//============================================================
// ActionItem::performAction
//============================================================

void ActionItem ::performAction(Assembly *assemblyPtr) const
{
	if (assemblyPtr->getNumMHUnits() < this->d_mhuID)
	{
		cout << "Cannot perform action on MH Unit" << d_mhuID <<
			" - Unit does not exist" << endl;
		return;
	}
	Muscle *musclePtr = assemblyPtr->getMHUnit(d_mhuID);
	if(musclePtr->getShape() == 1)
	{
		if(d_commandType >= 3)
		{
			cout << "Cannot perform action cylindrical MH Unit" << d_mhuID <<
				" - Only command types 1 and 2 valid - Please edit command file" << endl;
			return;
		}
		Cylinder *tempCyl = (Cylinder *)musclePtr;
		if(d_commandType == 0) tempCyl->setRadialCommandForce(d_commandMagnitude);
		if(d_commandType == 1) tempCyl->setLongitudinalCommandForce(d_commandMagnitude);
	}
	else if(musclePtr->getShape() == 2)
	{
		if(d_commandType == 0 || d_commandType == 2 || d_commandType > 3)
		{
			cout << "Cannot perform action box type MH Unit" << d_mhuID <<
				" - Only command types 1 and 2 valid - Please edit command file" << endl;
			return;
		}
		Box *tempBox = (Box *)musclePtr;
		if(d_commandType == 1) tempBox->setDimension1CommandForce(d_commandMagnitude);
		if(d_commandType == 3) tempBox->setDimension3CommandForce(d_commandMagnitude);
	}
}