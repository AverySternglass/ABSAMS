//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Mar 22 2005
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Instantiation.t.cpp
// Example program to test the instantiation of the Assembly Class.
//========================================================================

//========================================================================
// stripdata.cpp
//------------------------------------------------------------------------
// 
// Uses the .mhl file to create individual files for particular MHUs
//========================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[])
{
	if(argc < 3)
	{
		printf("Expect at least 2 arguments: One mhl file and atleast one MHU whose data needs to be stripped\n");
		exit(0);
	}
	FILE *mhlFilePtr, *newFilePtr;
	char header[10],fileName[30] = "",temp[10], data[10];
	int i, j, numUnits;
	double timeStamp;

	if((mhlFilePtr = fopen(argv[1],"r")) == NULL)
	{
		printf("Cannot open %s", argv[1]);
		exit(0);
	}
	
	fscanf(mhlFilePtr,"%s\t%d",header, &numUnits);
	for (i = 2; i < argc; i++)
		if(atoi(argv[i]) > (numUnits - 1))
		{
			printf("Error: Unit %d does not exist", atoi(argv[i]));
			exit(0);
		}

	for(i = 2; i < argc; i++)
	{
		rewind(mhlFilePtr);
		for(j = 0;j < 30;j++)
			fileName[j] = '\0';
		for(j = 0; j < (8*numUnits + 3); j++)
			fscanf(mhlFilePtr,"%s\t",header);
		strncpy(fileName, argv[1], (strlen(argv[1])-4));
		if(i < 10) sprintf(temp,"_0%d.mhl",i);
		else sprintf(temp,"_%d.mhl",i);
		strcat(fileName,temp);
		newFilePtr = fopen(fileName,"w");
		fprintf(newFilePtr,"Time\tUnit\tType\tDimension1\tDimension2\tDimension3\tLocationX\tLocationY\tLocationZ\n");
		while(fscanf(mhlFilePtr,"%lf", &timeStamp) != EOF)
		{
			fprintf(newFilePtr, "%lf\t", timeStamp);
			for(j = 0; j < i*8; j++)
				fscanf(mhlFilePtr,"%s\t",header);
			for(j = 0; j < 8; j++)
			{
				fscanf(mhlFilePtr,"%s\t",data);
				fprintf(newFilePtr, "%s\t", data);
			}
			fprintf(newFilePtr, "\n");
			for(j = 0; j < (numUnits - i - 1)*8; j++)
				fscanf(mhlFilePtr,"%s\t",header);
		}
	}
	

}


