//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: Cement.hpp
// Interface of the classes Assembly and Surface.
//========================================================================  
 

#ifndef INCLUDED_Cement_hpp
#define INCLUDED_Cement_hpp

#include<math.h>
#include "Bricks.hpp"
#include "Spring.hpp"
#include "Cylinder.hpp"
#include "Box.hpp"
#include "MuscleGroup.hpp"
#include<string.h>



//====================================================================
// class Assembly
// -------------------------------------------------------------------
// \brief
// The class \c Assembly represents a complete working unit consisting of
// MH Units along with the connective tissue and the interaction between them
// By definition it is assumed that an assembly is defined by the connective
// tissue and hence each assembly has only one surface defining the connective
// tissue.
// 
// 
//
// The class \c Assembly defines the data type \c Assembly and provides methods 
// for operations such as Initialization, ?? and ??.
//
// <b>Example Program:</b>
//
// \include Assembly.t.cpp
//========================================================================  


class Assembly
{
	friend class Surface;
public:
	
// ---- Constructor and Destructor -----

	Assembly(int AssemblyNumber, const char *mhaFile);
		// Constructor. 

	~Assembly();
		// The default destructor.

// ---- Member Functions ----- 

	int getNumber(void) const;
		// This function provides access to the Assembly number to help identify
		// the Assembly
		//  return		Unique identifier for the Assembly (Assembly number)
	
	int getNumNodes(void) const;
		// This function provides information regarding the total number of nodes in
		// the assembly. i.e., all surfaces in the assembly.
		//  return		number of nodes in the assembly

	int getNumSprings(void) const;
		// This function provides information regarding the total number of Springs in
		// the assembly. i.e., all surfaces
		//  return		number of springs in the assembly

	int getNumMHUnits(void) const;
		// This function provides information regarding the number of MH Units
		// in the assembly
		//  return		number of MH Units in the assembly

	int getNumSurfaces(void) const;
		// This function provides information regarding the number of Surfaces
		// in the assembly
		//  return		number of Surfaces in the assembly

	void setAssemblyType(int assemblyType);
		// This function provides access to change the materials that make up an assembly

	Muscle *getMHUnit(int mhUnitID) const;
		// This function provides access to the MH Units in the assembly
		//  return		Pointer to the MH Unit with the given ID
	
	bool isMemberOf(Node *node) const;
		// This Function checks if a node is a member of the assembly
		//  return		True if the node is a part of the assembly

	bool isMemberOf(Muscle *mhUnit) const;
		// This Function checks if a MH Unit is a member of the assembly
		//  return		True if the MH Unit is a part of the assembly

	Surface *getSurface(int surfaceNumber) const;
		// This Function Provides access to the member surfaces
		//  return		Pointer to the specified surface

	void writeMHAFile(const char *mhaFile) const;
		// Writes an MHA file that represents this assembly

	void updateAssembly(void);
		// Updates the dynamics of he assembly at each time step 
		// by calculating the iterations between the MH Units and 
		// the surface that make up the assembly

	MuscleGroup *getMuscleGroup(const char *grpName) const;
		// Returns handle to the group. Returns NULL if the group does not exist

	MuscleGroup *getMuscleGroup(int grpNumber) const;
		// Returns handle to the group. Returns NULL if the group does not exist
	
	int getNumMuscleGroups(void) const;
		// Returns the number of muscle Groups.
		// Returns zero if grouping information does not exist

	void display(void) const;
		// Displays the entire assembly in OpenGL window. If OpenGL is 
		// not available, error is printed.

	friend ostream &operator<<(ostream &output, const Assembly &Assembly);
		// This function overloads the ostream \c << operator
		// to output the all the MH Units in the Assembly \a Assembly to 
		// the output stream while waiting for "ENTER" after every node.
		// Example: \code cout << Assembly; \endcode

	friend int readIfNotComment(FILE *filePtr, char *string);
		// Reading a string from the file after stripping comments from it

	friend int readIfNotComment(FILE *filePtr, int *data);
		// Reading an integer from the file after stripping comments from it

	friend int readIfNotComment(FILE *filePtr, double *data);
		// Reading an double from the file after stripping comments from it

private:
	
	Assembly();
		// The default constructor. Do not allow creation of a 
		// Assembly without initializing it.
		
	int d_assemblyNumber;
		// Uniquely identifies the Assembly
	
	int d_numSurfaces;
		// Total number of MH Units in the Assembly

	int d_assemblyType;
		// Materials that make up the Assembly
		// 0 - Cephalopod Muscle with Collagen connective tissue
		// 1 - EAP type 1 Muscle with Rubber connective tissue
		// 2 - EAP type 2 Muscle with Rubber connective tissue

	List< Surface *> d_memberSurfaces;
		// List of surfaces associated with this assembly

	int d_numMHUnits;
		// Total number of MH Units in the Assembly

	List< Muscle *> d_memberMHUnits;
		// List of MH Units present in the Assembly

	bool d_groupingExists;
		// Indicates if grouping information has been defined for the
		// assembly
	int d_numMuscleGroups;
		// Number of muscle groups

	List< MuscleGroup *> d_muscleGroups;
		// List of the Muscle Groups in the assembly.
};


//====================================================================
// class Surface
// -------------------------------------------------------------------
// \brief
// The class \c Surface represents a collection of nodes on the connective 
// tissue of the muscle.
//
// 
// 
//
// The class \c Surface defines the data type \c Surface and provides methods 
// for operations such as Initialization, ?? and ??.
//
// <b>Example Program:</b>
//
// \include Surface.t.cpp
//========================================================================  


class Surface
{
public:
	
// ---- Constructor and Destructor -----

	Surface(int surfaceNumber, Assembly *assemblyName, FILE *mhaFilePtr);
		// Copy Constructor. 

	~Surface();
		// The default destructor.

// ---- Member Functions ----- 

	int getNumber(void) const;
		// This function provides access to the Surface number to help identify
		// the surface
		//  return		Unique identifier for the Surface (surface number)
	
	int getNumNodes(void) const;
		// This function provides information regarding the number of nodes on
		// the surface
		//  return		number of nodes in the surface

	int getNumSprings(void) const;
		// This function provides information regarding the number of springs on
		// the surface
		//  return		number of springs in the surface

	void addNode(Node *node);
		// Adds the node to the list of nodes in the surface. 
		//  node		pointer of the node to be added

	bool isMemberOf(Node *node) const;
		// This Function checks if a node is a member of the surface
		//  return		True if the node is a part of the surface

	Node *getNode(int nodeNumber) const;
		// This Function Provides access to the member nodes
		//  return		Pointer to the specified node

	SpringBase *getSpring(int springNumber) const;
		// This Function Provides access to the member springs
		//  return		Pointer to the specified spring

	void setAnchor(Node *node);
		// Allows us to specify anchor nodes on the surface
		//  node		Pointer to the node to be added

	void updateSurface(void);
		// Updates all Nodes and Springs in the surface

	void writeMHAFile(FILE *mhaFilePtr) const;
		// Writes relavant surface data to the specified file

	void display(void) const;
		// Displays the surface in OpenGL window. If OpenGL is 
		// not available, error is printed.

	friend ostream &operator<<(ostream &output, const Surface &surface);
		// This function overloads the ostream \c << operator
		// to output the all the nodes of the surface \a surface to the output stream
 		// while waiting for "ENTER" after every node.
		// Example: \code cout << surface; \endcode

	friend int readIfNotComment(FILE *filePtr, char *string);
		// Reading a string from the file after stripping comments from it

	friend int readIfNotComment(FILE *filePtr, int *data);
		// Reading an integer from the file after stripping comments from it

	friend int readIfNotComment(FILE *filePtr, double *data);
		// Reading an double from the file after stripping comments from it

private:
	
	Surface();
		// The default constructor. Do not allow creation of a 
		// surface without initializing it.
		
	int d_surfaceNumber;
		// Uniquely identifies the surface

	Assembly *d_parentAssembly;
		// Identifies the assembly of which the surface is a part of
	
	int d_numNodes;
		// Total number of nodes in the surface

	int d_numSprings;
		// Total number of springs in the surface

	List< Node *> d_memberNodes;
		// List of nodes that form the surface
	
	List< SpringBase *> d_memberSprings;
		// List of springs that are in the surface

	List< Node *> d_anchorNodes;
		// List of nodes that are anchored (constrained)
};



#endif // INCLUDED_Cement_hpp