//======================================================================== 
// Package			: The Connective Tissue
// Authors			: Pradeep Setlur
// Start Date		: Wed Feb 18 2004
// Compiler			: Microsoft Visual C++ 6.0
// Acknowledgements : Biomimetic and Cognitive Robotics Laboratory,
//                    Brooklyn College, CUNY.
//                    Defense Advanced Research Projects Agency
// ----------------------------------------------------------------------  
// File: ListElement.hpp
// Interface of the class ListElement.
//========================================================================  
 

//====================================================================
// class ListElement
// -------------------------------------------------------------------
// \brief
// The class \c ListElement describes a template class to describe each 
// element of a List.
//
// 
//
// The class \c ListElement defines the data type \c ListElement to
// that encapsulates the Object to insert into linked lists.
//
// <b>Example Program:</b>
//
// \include List.t.cpp
//========================================================================  

#ifndef INCLUDED_ListElement_hpp
#define INCLUDED_ListElement_hpp

#include <stdio.h>
//xg
#include <iostream>
#include <stdlib.h>
#include "Status.hpp"

template< class T> class List;
	// Forward Declaration

template< class T>
class ListElement
{
	friend class List<T>;
public:
	
// ---- Constructor and Destructor -----

	inline ListElement(const T newObject);
		// Copy Constructor. 

	~ListElement();
		// The default destructor.

// ---- Member Functions  -----

	inline T getData(void) const;
		// This function provides access to the Object stored in the 
		// ListElement of the list.
		//  return		Object stored in the ListElement
		
	inline ListElement< T> *getNext(void) const;
		// This function allows manipulation of the Linked 
		// List.
		//  return		Pointer to next List Element
	//xg
	inline void setNext(ListElement<T> *newPtr);
		// This function allows manipulation of the Linked 
		// List.
		//  newPtr		New pointer to next List Element

private:
	inline ListElement();
		// Default Constructor
	
	T data;
		// Number of members in the list

	ListElement< T> *nextPtr;
		// Pointer to the next Element in the List
};

// ========== END OF INTERFACE ==========



//============================================================
// ListElement::ListElement
//============================================================

template< class T>
ListElement< T> ::ListElement(){}
	// Deafult Constructor



//============================================================
// ListElement::ListElement
//============================================================

template< class T>
ListElement< T> :: ListElement(const T newObject)
	// Copy Constructor
{
	data = newObject;
	nextPtr = NULL;
}



//============================================================
// ListElement::~ListElement
//============================================================

template< class T>
ListElement< T> :: ~ListElement(){}
	// Deafult Destructor



//============================================================
// ListElement::getData
//============================================================

template< class T>
T ListElement< T> :: getData(void) const
	// Returns object stored in the List Element
{
	return data;
}



//============================================================
// ListElement::getNext
//============================================================

template< class T>
ListElement< T> *ListElement< T> :: getNext(void) const
	// Returns pointer to next List Element
{
	return nextPtr;
}



//============================================================
// ListElement::setNext
//============================================================

template< class T>
//xg
void ListElement< T> :: setNext(ListElement< T> *newPtr)
	// Sets pointer to next List Element
{
	nextPtr = newPtr;
}


#endif // INCLUDED_ListElement_hpp