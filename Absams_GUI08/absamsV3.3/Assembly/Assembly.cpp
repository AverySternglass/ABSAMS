//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Assembly.cpp
// Implementation of the class Assembly.
//========================================================================  


#include "Cement.hpp"

void output(int x, int y, int z, char *string)
{
  int len, i;
  glRasterPos3f(x, y, z);
  len = (int) strlen(string);
  for (i = 0; i < len; i++)
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}


//============================================================
// Assembly::Assembly
//============================================================

Assembly::Assembly(){}
	// Default Constructor


//============================================================
// Assembly::Assembly
//============================================================

Assembly::Assembly(int assemblyNumber, const char *mhaFile)
	// Constructor
{
	
	FILE *mhaFilePtr;
	char header[60];
	double xpos,ypos,zpos;
	double dimensionA, dimensionB, dimensionC;
	double orientationI, orientationJ, orientationK;
	double uAxisL,uAxisM,uAxisN;
	Muscle *musclePtr;
	Surface *surfacePtr;
	int i;
	int mhuNumber;
	int type;
	int anchor;
	char grpName[60];
	MuscleGroup *grpPtr;
	int tempNumMusc;
	int mhuID;

	d_assemblyNumber = assemblyNumber;
	if((mhaFilePtr = fopen(mhaFile,"r")) == NULL)
		throw Status(3);
	else
	{
		readIfNotComment(mhaFilePtr, header);
		readIfNotComment(mhaFilePtr, &d_numMHUnits);
		cout << "Number of MH Units in the Assembly: " << d_numMHUnits << endl;
		readIfNotComment(mhaFilePtr, header);
		readIfNotComment(mhaFilePtr, &d_numSurfaces);

		readIfNotComment(mhaFilePtr, header);
		readIfNotComment(mhaFilePtr, &d_assemblyType);
		
		double muscleDensity= g_cephMuscleDensity;
		if(d_assemblyType == 1) muscleDensity= g_EAP1MuscleDensity;
		if(d_assemblyType == 2) muscleDensity= g_EAP2MuscleDensity;
		

		for (i = 0; i < 15; i++)
			readIfNotComment(mhaFilePtr, header);

		for ( i=0; i < d_numMHUnits; i++)
		{
			readIfNotComment(mhaFilePtr, &mhuNumber);
			readIfNotComment(mhaFilePtr, &type);
			readIfNotComment(mhaFilePtr, &anchor);
			readIfNotComment(mhaFilePtr, &dimensionA);
			readIfNotComment(mhaFilePtr, &dimensionB);
			readIfNotComment(mhaFilePtr, &dimensionC);
			readIfNotComment(mhaFilePtr, &xpos);
			readIfNotComment(mhaFilePtr, &ypos);
			readIfNotComment(mhaFilePtr, &zpos);
			readIfNotComment(mhaFilePtr, &orientationI);
			readIfNotComment(mhaFilePtr, &orientationJ);
			readIfNotComment(mhaFilePtr, &orientationK);
			readIfNotComment(mhaFilePtr, &uAxisL);
			readIfNotComment(mhaFilePtr, &uAxisM);
			readIfNotComment(mhaFilePtr, &uAxisN);
			
			if(type == 1)
			{
				musclePtr = new Cylinder( mhuNumber, g_sizeRatio*dimensionA, g_sizeRatio*dimensionB,
									Vector(g_sizeRatio*xpos,g_sizeRatio*ypos,g_sizeRatio*zpos),
									Vector(orientationI,orientationJ,orientationK),
									Vector(uAxisL,uAxisM,uAxisN), muscleDensity);
				if(anchor == 1) musclePtr->setAnchor();
				d_memberMHUnits.addElement(musclePtr);
			}

			if(type == 2)
			{
				musclePtr = new Box(mhuNumber, g_sizeRatio*dimensionA, g_sizeRatio*dimensionB, g_sizeRatio*dimensionC,
									Vector(g_sizeRatio*xpos,g_sizeRatio*ypos,g_sizeRatio*zpos),
									Vector(orientationI,orientationJ,orientationK),
									Vector(uAxisL,uAxisM,uAxisN), muscleDensity);
				if(anchor == 1) musclePtr->setAnchor();
				d_memberMHUnits.addElement(musclePtr);
			}

		//	else
		//	{
		//		cout << "MH Unit " << mhuNumber << " cannot be created in ver 1.0" << endl;
		//		exit(0);
		//	}
		}
		for (i = 0; i < d_numSurfaces; i++)
		{
			surfacePtr = new Surface(i, this, mhaFilePtr);
			d_memberSurfaces.addElement(surfacePtr);
		}
		d_numMuscleGroups = 0;
		if(readIfNotComment(mhaFilePtr, header) != EOF)
		{
			printf("Muscle Groups Defined\n");
			d_groupingExists = true;
			for(i = 0;i < 2; i++)
				readIfNotComment(mhaFilePtr, header); // strip grouping info header(2 strings)
			while(readIfNotComment(mhaFilePtr, grpName) != EOF)
			{
				d_numMuscleGroups++;
				grpPtr = new MuscleGroup(grpName);
				d_muscleGroups.addElement(grpPtr);
				readIfNotComment(mhaFilePtr, &tempNumMusc);
				for(i = 0;i < tempNumMusc; i++)
				{
					readIfNotComment(mhaFilePtr, &mhuID);
					Muscle *tempMusclePtr = this->getMHUnit(mhuID);
					if(tempMusclePtr == NULL)
					{
						cout << "MH Unit" << mhuID << "cannot be added to the muscle groups:"
							<< "MHU does not exist" << endl;
						exit(0);
					}
					else grpPtr->addMuscle(tempMusclePtr);
				}
				
			}
		}
		else 
		{
			printf("Muscle Groups NOT defined\n");
			d_groupingExists = false;
		}

		fclose(mhaFilePtr);
	}
}

//============================================================
// Assembly::~Assembly
//============================================================

Assembly :: ~Assembly(){}
	// Default Destructor



//============================================================
// Assembly::getNumber
//============================================================

int Assembly :: getNumber(void) const
	// Access function
{
	return(d_assemblyNumber);
}

//============================================================
// Assembly::getNumNodes
//============================================================

int Assembly :: getNumNodes(void) const
	// Access function
{
	int i, total=0;
	for(i = 0; i< d_numSurfaces; i++)
		total += (this->getSurface(i))->getNumNodes();
	return total;
}


///============================================================
// Assembly::getNumMHUnits
//============================================================

int Assembly :: getNumMHUnits(void) const
	// Access function
{
	return(this->d_numMHUnits);
}


///============================================================
// Assembly::getNumSurfaces
//============================================================

int Assembly :: getNumSurfaces(void) const
	// Access function
{
	return(this->d_numSurfaces);
}


//============================================================
// Assembly::getNumSprings
//============================================================

int Assembly :: getNumSprings(void) const
	// Access function
{
	int i, total=0;
	for(i = 0; i< d_numSurfaces; i++)
		total += (this->getSurface(i))->getNumSprings();
	return total;
}


//============================================================
// Assembly::isMemberOf
//============================================================

bool Assembly :: isMemberOf(Node *node) const
	// Checks if a node is a part of a assembly
{
	cout << " Not implemented" << endl;
	return true;
}



//============================================================
// Assembly::getSurface
//============================================================

Surface * Assembly :: getSurface(int surfaceNumber) const
	// Access function to surfaces
{
	return (this->d_memberSurfaces.getElement(surfaceNumber)).getData();
}



//============================================================
// Assembly::setAssemblyType
//============================================================

void Assembly :: setAssemblyType(int assemblyType)
	// Access function to surfaces
{
	d_assemblyType = assemblyType;
}


//============================================================
// Assembly::writeMHAFile
//============================================================

void Assembly :: writeMHAFile(const char *mhaFile) const
	// Access function to surfaces
{
	FILE *mhaFilePtr;
	int i;
	if((mhaFilePtr = fopen(mhaFile,"w")) == NULL)
		throw Status(3);
	else
	{
		fprintf(mhaFilePtr,"MHUnits\t");
		fprintf(mhaFilePtr,"%d\n", d_numMHUnits);
		fprintf(mhaFilePtr,"Surfaces\t");
		fprintf(mhaFilePtr,"%d\n", d_numSurfaces);
		

		fprintf(mhaFilePtr,"Materials\t");
		fprintf(mhaFilePtr,"%d\n", d_assemblyType);
		fprintf(mhaFilePtr,"\nMHU\tType\tAnch\tA\tB\tC\tX\tY\tZ\tI\tJ\tK\tL\tM\tN\n");
		Muscle *mhuPtr;
		for ( i=0; i < d_numMHUnits; i++)
		{
			mhuPtr = d_memberMHUnits.getElement(i).getData();
			mhuPtr->writeMHAFile(mhaFilePtr);
		}

		for ( i=0; i < d_numSurfaces; i++)
			(d_memberSurfaces.getElement(i).getData())->writeMHAFile(mhaFilePtr);

		if(d_groupingExists)
		{
			fprintf(mhaFilePtr,"\nName\tnum\tList");
			for(i=0; i < d_numMuscleGroups; i++)
				(d_muscleGroups.getElement(i).getData())->writeMHAFile(mhaFilePtr);
		}		

	}
	fclose(mhaFilePtr);
}


//============================================================
// Assembly::getMHUnit
//============================================================

Muscle * Assembly :: getMHUnit(int mhUnitID) const
	// Access function to MH Units
{
	for(int i = 0; i < d_numMHUnits; i++)
	{
		Muscle *tempMusclePtr = (this->d_memberMHUnits.getElement(i)).getData();
		if(tempMusclePtr->getID() == mhUnitID)
			return (this->d_memberMHUnits.getElement(mhUnitID)).getData();
	}
	return NULL;
}



//============================================================
// Assembly::updateAssembly
//============================================================

void Assembly :: updateAssembly(void)
	// Updates the assembly in the correct order
{
	int i;
	for(i = 0; i < d_numMHUnits; i++)
	{
		this->getMHUnit(i)->shapeChange();
	}
	for(i = 0; i < d_numSurfaces; i++)
	{
		this->getSurface(i)->updateSurface();
	}
	for(i = 0; i < d_numMHUnits; i++)
	{
		if(!(this->getMHUnit(i)->isAnchor()))
			this->getMHUnit(i)->updateMuscle();
	}
}

//============================================================
// Assembly::getMuscleGroup
//============================================================

MuscleGroup * Assembly :: getMuscleGroup(const char *grpName) const
{
	for(int i = 0; i < d_muscleGroups.getNumElements(); i++)
		if(strcmp(d_muscleGroups.getElement(i).getData()->getGroupName(),grpName)==0)
			return d_muscleGroups.getElement(i).getData();
	return NULL;
}


//============================================================
// Assembly::getMuscleGroup
//============================================================

MuscleGroup * Assembly :: getMuscleGroup(int grpNumber) const
{
	if(grpNumber < d_muscleGroups.getNumElements())
		return d_muscleGroups.getElement(grpNumber).getData();
	else return NULL;
}


//============================================================
// Assembly::getNumMuscleGroups
//============================================================

int Assembly :: getNumMuscleGroups(void) const
{
	return d_numMuscleGroups;
}


#ifdef __glut_h__
//============================================================
// Assembly::display
//============================================================
void Assembly :: display(void) const
{
	// Draw the world frame

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex3f(-10,0,0);
	glVertex3f(1000,0,0);
	glColor3f(0,1,0);
	glVertex3f(0,-10,0);
	glVertex3f(0,1000,0);
	glColor3f(0,0,1);
	glVertex3f(0,0,-10);
	glVertex3f(0,0,1000);
	glEnd();
	glPopMatrix();
	
	glColor3f(1,0,0);
	output(100,-5,-5, "X");
	glColor3f(0,1,0);
	output(-5,100,-5, "Y");
	glColor3f(0,0,1);
	output(-5,-5,100, "Z");

	int i;
	for(i = 0; i < d_numMHUnits; i++)
	{
		this->getMHUnit(i)->display();
		this->getMHUnit(i)->displayAxes();
	}
	for(i = 0; i < d_numSurfaces; i++)
	{
		this->getSurface(i)->display();
	}

}

#endif

#ifndef __glut_h__
//============================================================
// Assembly::display
//============================================================
void Assembly :: display(void) const
{
	cout << " Cannot Display : GLUT libraries not installed" << endl;
	exit(1);
}

#endif
//============================================================
// operator<<
//============================================================

ostream &operator<<(ostream &output, const Assembly &assembly)
	// Overloading the << operator for easy display of Assembly information on the screen.
{
	int i;
	output << "Assembly Number: " << assembly.getNumber() << endl;
	for(i = 0; i < assembly.getNumSurfaces(); i++)
	{
		output << assembly.getSurface(i) << endl;
	}
	output << endl;
	return output;
}

//============================================================
// readIfNotComment
//============================================================

int readIfNotComment(FILE *filePtr, char *string)
{
	bool done = false;
	while(!done)
	{
		if(fscanf(filePtr,"%s", string) == EOF)
		{
			strcpy(string,"");
			return EOF;
		}
		if(strchr(string, '%') != NULL) 
		{
			fgets(string,60,filePtr);
			done = false;
		}
		else done = true;
	}
	return 0;
}

//============================================================
// readIfNotComment
//============================================================

int readIfNotComment(FILE *filePtr, int *data)
{
	char string[60];
	bool done = false;
	while(!done)
	{
		if(fscanf(filePtr,"%s", string) == EOF)
		{
			strcpy(string,"");
			return EOF;
		}
		if(strchr(string, '%') != NULL) 
		{
			fgets(string,60,filePtr);
			done = false;
		}
		else done = true;
	}
	*data = atoi(string);
	return 0;
}

//============================================================
// readIfNotComment
//============================================================

int readIfNotComment(FILE *filePtr, double *data)
{
	char string[60];
	bool done = false;
	while(!done)
	{
		if(fscanf(filePtr,"%s", string) == EOF)
		{
			strcpy(string,"");
			return EOF;
		}
		if(strchr(string, '%') != NULL) 
		{
			fgets(string,60,filePtr);
			done = false;
		}
		else done = true;
	}
	*data = atof(string);
	return 0;
}

