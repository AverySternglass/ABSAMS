//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Command.cpp
// Implementation of the class Command.
//========================================================================  


#include "Command.hpp"
#include <math.h>



//============================================================
// Command::Command
//============================================================

Command::Command(){}
	// Default Constructor


//============================================================
// Command::Command
//============================================================

Command::Command(const char *commandFile)
	// Constructor
{
	
	FILE *mhaFilePtr;
	char header[10];
	int mhuID; // MHU id number
	double timeOn,timeOff,commandMagnitude;
	int commandType, numCommands;

	d_numActionItems = 0;
	d_currentActionItem = 0;
	if((mhaFilePtr = fopen(commandFile,"r")) == NULL)
		throw Status(3);
	else
	{
		// Stripping the header
		fscanf(mhaFilePtr,"%s", header);
		fscanf(mhaFilePtr,"%d", &numCommands);
	
		// Stripping the header
		for(int i = 0; i < 5; i++)
			fscanf(mhaFilePtr,"%s", header);
		//xg
		for(int i = 0; i < numCommands; i++)
		{
			fscanf(mhaFilePtr,"%d", &mhuID);
			fscanf(mhaFilePtr,"%lf", &timeOn);
			fscanf(mhaFilePtr,"%lf", &timeOff);
			fscanf(mhaFilePtr,"%d", &commandType);
			fscanf(mhaFilePtr,"%lf", &commandMagnitude);

			this->addCommand(mhuID, timeOn, timeOff, commandType, commandMagnitude);
		}
	}


}


//============================================================
// Command::addCommand
//============================================================

void Command::addCommand(int mhuID, double timeOn, double timeOff, 
						 int type, double magnitude)
{
	
	ActionItem *actionItemPtr, *tempPtr;
	
	actionItemPtr = new ActionItem(mhuID, timeOn, type, magnitude);
			
	if(d_numActionItems == 0)
		d_actionItems.addElementAt(actionItemPtr,0);
	else
	{
		tempPtr = d_actionItems.getElement(0).getData();
		if(timeOn < tempPtr->getActionTime())
			d_actionItems.addElementAt(actionItemPtr,0);
		else
		{	//xg
			int i;
			for(i = 0; i < d_numActionItems; i++)
			{
				tempPtr = d_actionItems.getElement(i).getData();
				if(timeOn > tempPtr->getActionTime())
					d_actionItems.getElement(i).getNext();
				else break;
			}	
			d_actionItems.addElementAt(actionItemPtr,i);
		}
	}
	d_numActionItems++;
	if(timeOff != -1)
	{
		actionItemPtr = new ActionItem(mhuID, timeOff, type, 0.0);
		int i; //xg
		for(i = 0; i < d_numActionItems; i++)
		{
			tempPtr = d_actionItems.getElement(i).getData();
			if(timeOff > tempPtr->getActionTime())
				d_actionItems.getElement(i).getNext();
			else break;
		}	
		d_actionItems.addElementAt(actionItemPtr,i);
		d_numActionItems++;
	}	
}


//============================================================
// Command::deleteSubsequentActions
//============================================================

void Command::deleteSubsequentActions(double deletionTime)
{
	ActionItem *tempPtr;
	
	for(int i = 0; i < d_numActionItems; i++)
	{
		tempPtr = d_actionItems.getElement(i).getData();
		if(deletionTime >= tempPtr->getActionTime())
			d_actionItems.getElement(i).getNext();
		else
		{
			d_actionItems.deleteElement(i);
			d_numActionItems--;
		}
	}
}


//============================================================
// Command::~Command
//============================================================

Command ::~Command(){}
	// Default Destructor


//============================================================
// Command::applyCommand
//============================================================

void Command::applyCommand(Assembly *assemblyPtr, double currentTime)
{
	if(d_currentActionItem < d_numActionItems)
	{
		ActionItem *actionPtr = d_actionItems.getElement(d_currentActionItem).getData();
		if(actionPtr->getActionTime() <= currentTime)
		{
			(d_actionItems.getElement(d_currentActionItem).getData())->performAction(assemblyPtr);
			d_currentActionItem++;
		}
	}
}


