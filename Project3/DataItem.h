#ifndef DATAITEM
#define DATAITEM


/*
 *	File:		  DataItem.h
 *	Project:	  LinkedList
 *	Assignment:	  Programming Project #3
 *	Programmer:	  Stephen Dunn
 *	Date:		  10/27/2020
 *	University:	  McMurry University
 *	Course:		  COSC–3360 Fall 2020
 *	Instructor:	  Mr. Brozovic
 *	Compiler:	  Visual Studio
 *	Description:  Definition of type dataitem_t for ADT data items
 */

/*	======================================================================	*
 *																			*
 *	Definition of underlying data type for use in ADTs						*
 *																			*
 *		Programmer simply replaces "int" in following typedef				*
 *		with desired type for the individual data items in the ADT.			*
 *																			*
 *		Caution must be exercised embedding pointers within the				*
 *		data description as simple copy operations will create				*
 *		alias pointers!!													*
 *																			*
 *		Programmer must also provide a comparison function as described		*
 *		below.																*
 *																			*
 *	======================================================================	*/

typedef int dataitem_t;

/*	======================================================================	*
 *																			*
 *	int compareItem(dataitem_t item1, dataitem_t item2)						*
 *																			*
 *	DESCRIPTION: Compares desired portion of two data items.				*
 *				 Returns a tri-state value (like standard strcmp function).	*
 *					 0 when the key of item1 == key of item2				*
 *					-1 when the key of item1 < key of item2					*
 *					 1 when the key of item1 > key of item2					*
 *																			*
 *	======================================================================	*/

int compareItem(dataitem_t item1, dataitem_t item2);

#endif
