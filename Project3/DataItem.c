#include "DataItem.h"

/*
 *	File:		  DataItem.c
 *	Project:	  LinkedList
 *	Assignment:	  Programming Project #3
 *	Programmer:	  Stephen Dunn
 *	Date:		  10/27/2020
 *	University:	  McMurry University
 *	Course:		  COSC–3360 Fall 2020
 *	Instructor:	  Mr. Brozovic
 *	Compiler:	  Visual Studio
 *	Description:  Definition of compare function for ADT data items
 */

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

int compareItem(dataitem_t item1, dataitem_t item2) {
	if (item1 == item2)
		return 0;
	else if (item1 < item2)
		return -1;
	else
		return 1;
}
