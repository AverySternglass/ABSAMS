//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: List.hpp
// Interface of the class List.
//========================================================================  
 

//====================================================================
// class List
// -------------------------------------------------------------------
// \brief
// The class \c List describes a template class to describe a list of 
// objects of the same type
//
// 
//
// The class \c List defines the data type \c List and provides methods 
// for operations such as create, add and delete.
//
// <b>Example Program:</b>
//
// \include List.t.cpp
//========================================================================  

#ifndef INCLUDED_List_hpp
#define INCLUDED_List_hpp

#include <stdio.h>
//#include <iostream.h>
#include <iostream>
#include <stdlib.h>
#include "ListElement.hpp"
#include "Status.hpp"

template< class T>
class List
{
public:
	
// ---- Constructor and Destructor -----

	inline List();
		// Default Constructor. 

	~List();
		// The default destructor.

// ---- Member Functions -----

	inline ListElement< T> getElement(int position) const;
		// This function provides access to the elements of the list.
		//  return		Object at the specified position
		
	inline void addElement(const T newElement);
		// This function allows the addition of elements to the list.
		//  newElement		Element to be added to the list
	
	inline void addElementAt(const T newElement, int position);
		// This function allows the addition of elements to the list at
		// a specified position making it easy to create sorted lists
		//  newElement		Element to be added to the list
		//  position		Position to be added
	//xg
	inline void deleteElement(int position);
		// This function allows the deletion of elements from the list.
		//  position		Position of element to be deleted

	inline int getNumElements(void) const;
		// This function allows the addition of elements to the list.
		//  newElement		Element to be added to the list
	//xg
	inline void clearList(void);
		// This function allows the clearing all elements from the list,
		// without destroying the list itself
		
	
private:
	int numElements;
		// Number of members in the list

	ListElement< T> *listPtr;
		// Pointer to the list

};

// ========== END OF INTERFACE ==========

//============================================================
// List::List
//============================================================

template< class T>
List< T> :: List()
	// Default Constructor. 
{
	numElements = 0;
	listPtr = NULL;
}



//============================================================
// List::List
//============================================================

template< class T>
List< T> :: ~List()
	// Default Destructor. 
{
	ListElement< T> *pointer, *nextPtr;
	pointer = listPtr;
	for(int i=0; i<numElements; i++)
	{
		nextPtr = (*pointer).getNext();
		delete pointer;
		pointer = nextPtr;
	}
	//cout << " List Destroyed" << endl;
}




//============================================================
// List::getElement
//============================================================

template< class T>
ListElement< T> List< T> :: getElement(int position) const
	// Returns element at specified position
{
	if(numElements < position)
	{
		throw Status(2);
		return NULL;
	}
	
	else
	{
		ListElement< T> *pointer;
		pointer = listPtr;
		for(int i=0; i<position; i++)
			pointer = (*pointer).getNext();

		return (*pointer);
	}
}



//============================================================
// List::addElement
//============================================================

template< class T>
//xg
void List< T> :: addElement(const T newElement)
	// Adds the new member to the list
{
	
	ListElement< T> *tempPtr;
	ListElement< T> *pointer =  new ListElement< T> (newElement);
	tempPtr = listPtr;

	if( listPtr == NULL) listPtr = pointer;
	else
		while(true)
		{
			if((*tempPtr).getNext() == NULL) 
			{
				(*tempPtr).setNext(pointer);
				break;
			}
			else tempPtr = (*tempPtr).getNext();
		}

	numElements++;
}


//============================================================
// List::addElementAt
//============================================================

template< class T>
//xg
void List< T> :: addElementAt(const T newElement, int position)
	// Adds the new member to the list at the specified position
{
	
	ListElement< T> *previousPtr, *currentPtr;
	ListElement< T> *pointer =  new ListElement< T> (newElement);
	
	
	if(numElements < position)
	{
		throw Status(2);
//		return NULL;
	}
	else
	{	
		if( listPtr == NULL) listPtr = pointer;
		else
		{
			if(position == 0)
			{
				pointer->setNext(listPtr);
				listPtr = pointer;
			}
			else
			{
				currentPtr = listPtr;
				for(int i=0; i<position; i++)
				{
					previousPtr = currentPtr;
					currentPtr = (*currentPtr).getNext();
				}
				(*previousPtr).setNext(pointer);
				(*pointer).setNext(currentPtr);
			}
		}

		numElements++;
	}
}


//============================================================
// List::deleteElement
//============================================================

template< class T>
//xg
void List< T> :: deleteElement(int position)
	// Removes the element at a position from the list
{
	if(numElements < (position+1))
		throw Status(2);	
	else
	{
		ListElement< T> *pointer, *previousPtr;
		previousPtr = listPtr;
		pointer = listPtr;
		
		for(int i=0; i<position; i++)
		{
			previousPtr = pointer;
			pointer = (*pointer).getNext();
		}
		
		if(position==0) listPtr = (*pointer).getNext();
		else (*previousPtr).setNext((*pointer).getNext());
		delete pointer;
	}
	numElements--;
}


//============================================================
// List::clearList
//============================================================

template< class T>
//xg
void List< T> :: clearList(void)
	// Clears all elements from the list
{
	ListElement< T> *pointer, *nextPointer;
		
	pointer = listPtr;
		
	for(int i=0; i<numElements; i++)
	{
		nextPointer = (*pointer).getNext();
		delete pointer;
		pointer = nextPointer;
	}
	
	listPtr = NULL;
	numElements = 0;
}

//============================================================
// List::getNumElements
//============================================================

template< class T>
int List< T> :: getNumElements(void) const
	// Returns the number of elements in the list
{
	return numElements;
}


#endif // INCLUDED_List_hpp