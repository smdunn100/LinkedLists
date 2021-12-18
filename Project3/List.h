#ifndef LISTADT
#define LISTADT

/*	======================================================================	*
 *																			*
 *		W A R N I N G  --  W A R N I N G  --  W A R N I N G					*
 *																			*
 *		DO NOT MAKE ANY CHANGES TO THIS FILE FOR THIS PROJECT!!				*
 *																			*
 *	======================================================================	*/

/*
 *	File:		  ListADT.h
 *	Project:	  LinkedList
 *	Assignment:	  Programming Project #3
 *	Programmer:	  Stephen Dunn
 *	Date:		  10/27/2020
 *	University:	  McMurry University
 *	Course:		  COSC–3360 Fall 2020
 *	Instructor:	  Mr. Brozovic
 *	Compiler:	  Visual Studio
 *	Description:  ADT interface for a list
 */

#include "DataItem.h"

/*  Abstract list to be implemented as linked list (concrete type)  */
typedef struct LinkedListCDT *ListADT;

/*	======================================================================	*
 *																			*
 *	ADT INTERFACE -- LIST													*
 *																			*
 *		OVERVIEW -- Definition of an abstract storage mechanism for a list	*
 *		of data items as defined by the application.  The application must	*
 *		provide "DataItem.h" which defines dataitem_t, the data type of		*
 *		items in the list, along with "DataItem.c" which must provide a		*
 *		compareItem(dataitem_t,dataitem_t) function that works similar to	*
 *		the standard strcmp() function.  To make use of an ADT List, the	*
 *		application must declare a ListADT variable, which will be a		*
 *		pointer to the application's list.  That pointer identifies the		*
 *		specific list that is to be created and manipulated via the			*
 *		behavior functions defined below.	Each list will maintain a		*
 *		cursor to identify its current list location to support some		*
 *		operations -- see detailed descriptions of individual functions		*
 *		below for more information.  Most operations will allow application	*
 *		to specify a desired location via an index value with 0 being the	*
 *		index of the first item in the list and size-1 being the index of	*
 *		the last item in the list, with the same basic functionality as a	*
 *		standard array.  Ideally, the application should not care about the	*
 *		underlying concrete implementation.									*
 *																			*
 *		HOUSEKEEPING BEHAVIORS:												*
 *			Create a new list												*
 *			Destroy an existing list and all of its items					*
 *			Clear or Erase all existing data items from a list				*
 *			Check length or size of a list, number of items in list			*
 *			Check whether current list location identifies an item			*
 *			Check whether current list location has a next item				*
 *			Check for empty list and full list conditions					*
 *																			*
 *		MANIPULATION BEHAVIORS:												*
 *			Insert or add new item to list, before an existing item			*
 *			Append or add new item to list, after an existing item			*
 *			Delete an existing item from list								*
 *			Replace data in an existing list item							*
 *			Get data from an existing list item								*
 *			Move current list location to first or last item in list		*
 *			Move current list location to specific position in list			*
 *			Move current list location forward or backward in list			*
 *			Find location of first list item containing requested data		*
 *			Find location of last list item whose data is less than			*
 *				or greater than requested data								*
 *																			*
 *		APPLICATION WARNINGS:												*
 *			Attempts to perform operations on non-existing list items		*
 *			will cause program to abort in most cases.  Application must	*
 *			make use of proper behaviors to check for existence of a		*
 *			current item or empty list as needed.							*
 *																			*
 *	======================================================================	*/


/*	======================================================================	*
*																			*
*	ListADT newList(int capacity)											*
*																			*
*	DESCRIPTION: Creates a brand new empty list with requested capacity.	*
*																			*
*		Precondition: capacity >= 0											*
*		Input parameter capacity is desired number of items the new list	*
*			is capable of storing but applies only for array-based			*
*			implementations (ignored for linked list implementations)		*
*		Returns a pointer to the list (null on failure)						*
*		Post condition: empty list exists unless allocation failed			*
*																			*
*	======================================================================	*/

ListADT newList(int capacity);


/*	======================================================================	*
*																			*
*	void freeList(ListADT *listptr)											*
*																			*
*	DESCRIPTION: Destroys an existing list, freeing all items in list and	*
*				 all memory used by the list.  List pointer is set to null.	*
*																			*
*		Precondition: list exists (listptr and *listptr are valid)			*
*		Input/Output parameter listptr is pointer to app's variable			*
*			containing the list's pointer									*
*		Post conditions: list destroyed and app's pointer is null			*
*																			*
*	======================================================================	*/

void freeList(ListADT *listptr);


/*	======================================================================	*
*																			*
*	void clearList(ListADT listptr)											*
*																			*
*	DESCRIPTION: Erases all items from an existing list, reseting list		*
*				 to an empty list.											*
*																			*
*		Precondition: list exists (listptr is valid)						*
*		Input parameter listptr is app's list pointer						*
*		Post condition: list exists but is empty							*
*																			*
*	======================================================================	*/

void clearList(ListADT listptr);


/*	======================================================================	*
*																			*
*	int listLength(ListADT listptr)											*
*																			*
*	DESCRIPTION: Provides current size of an existing list.					*
*																			*
*		Precondition: list exists (listptr is valid)						*
*		Input parameter listptr is app's list pointer						*
*		Returns current length of list, number of items in list				*
*		Post condition: list unchanged										*
*																			*
*	======================================================================	*/

int listLength(ListADT listptr);


/*	======================================================================	*
*																			*
*	int isListItem(ListADT listptr)											*
*																			*
*	DESCRIPTION: Determines whether or not list cursor identifies an item.	*
*																			*
*		Precondition: list exists (listptr is valid)						*
*		Input parameter listptr is app's list pointer						*
*		Returns TRUE iff current list location contains an item				*
*		Post condition: list unchanged										*
*																			*
*	======================================================================	*/

int isListItem(ListADT listptr);


/*	======================================================================	*
*																			*
*	int hasNextListItem(ListADT listptr)									*
*																			*
*	DESCRIPTION: Determines whether or not a next item exists after			*
*				 current list cursor item.  Current cursor location must	*
*				 be valid.													*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			Current cursor location is valid								*
*		Input parameter listptr is app's list pointer						*
*		Returns TRUE iff a next item follows current list cursor item		*
*		Post condition: list unchanged										*
*																			*
*	======================================================================	*/

int hasNextListItem(ListADT listptr);


/*	======================================================================	*
*																			*
*	int isListEmpty(ListADT listptr)										*
*																			*
*	DESCRIPTION: Determines whether or not an existing list is empty.		*
*																			*
*		Precondition: list exists (listptr is valid)						*
*		Input parameter listptr is app's list pointer						*
*		Returns TRUE iff list contains no data items						*
*		Post condition: list unchanged										*
*																			*
*	======================================================================	*/

int isListEmpty(ListADT listptr);


/*	======================================================================	*
*																			*
*	int isListFull(ListADT listptr)											*
*																			*
*	DESCRIPTION: Determines whether or not an existing list is full.		*
*																			*
*		Precondition: list exists (listptr is valid)						*
*		Input parameter listptr is app's list pointer						*
*		Returns TRUE iff list cannot store any additional items				*
*		Post condition: list unchanged										*
*																			*
*	======================================================================	*/

int isListFull(ListADT listptr);


/*	======================================================================	*
*																			*
*	int insertListItemAt(ListADT listptr, int index, dataitem_t data)		*
*																			*
*	DESCRIPTION: Inserts a new item into an existing list at a specified	*
*				 location, before any existing item.  Location must be in	*
*				 the range 0 ... size where size would append the new item	*
*				 at the end of the list.  Returns location of new item.		*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			index is valid and data contains new data for item				*
*		Input parameter listptr is app's list pointer						*
*		Input parameter index is list location where item is to be placed	*
*		Input parameter data is data to be stored in new item				*
*		Returns new cursor location											*
*		Post conditions: new data stored in new item which is placed		*
*				before current item at requested location					*
*			New item becomes list's current location						*
*			List's size increases by 1										*
*																			*
*	======================================================================	*/

int insertListItemAt(ListADT listptr, int index, dataitem_t data);


/*	======================================================================	*
*																			*
*	int insertListItem(ListADT listptr, dataitem_t data)					*
*																			*
*	DESCRIPTION: Inserts a new item into an existing list at the current	*
*				 cursor location, before any existing item.  When cursor	*
*				 is not valid, the new item is inserted at the front of		*
*				 the list.  Returns location of new item.					*											*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			data contains new data for item									*
*		Input parameter listptr is app's list pointer						*
*		Input parameter data is data to be stored in new item				*
*		Returns new cursor location											*
*		Post conditions: new data stored in new item which is placed		*
*				before item defined by current cursor location or at		*
*				front of list												*
*			New item becomes list's current location						*
*			List's size increases by 1										*
*																			*
*	======================================================================	*/

int insertListItem(ListADT listptr, dataitem_t data);


/*	======================================================================	*
*																			*
*	int appendListItemAt(ListADT listptr, int index, dataitem_t data)		*
*																			*
*	DESCRIPTION: Appends a new item to an existing list at a specified		*
*				 location, after any existing item.  Location must be in	*
*				 the range 0 ... size where size would append the new item	*
*				 to the end of the list.  Returns location of new item.		*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			index is valid and data contains new data for item				*
*		Input parameter listptr is app's list pointer						*
*		Input parameter index is list location, after which new item		*
*			will be placed													*
*		Input parameter data is data to be stored in new item				*
*		Returns new cursor location											*
*		Post conditions: new data stored in new item which is placed		*
*				after current item at requested location					*
*			New item becomes list's current location						*
*			List's size increases by 1										*
*																			*
*	======================================================================	*/

int appendListItemAt(ListADT listptr, int index, dataitem_t data);


/*	======================================================================	*
*																			*
*	int appendListItem(ListADT listptr, dataitem_t data)					*
*																			*
*	DESCRIPTION: Appends a new item to an existing list at the current		*
*				 cursor location, after any existing item.  When cursor		*
*				 is not valid, the new item is appended to the end of the	*
*				 list.  Returns location of new item.						*											*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			data contains new data for item									*
*		Input parameter listptr is app's list pointer						*
*		Input parameter data is data to be stored in new item				*
*		Returns new cursor location											*
*		Post conditions: new data stored in new item which is placed		*
*				after item defined by current cursor location or at			*
*				end of list													*
*			New item becomes list's current location						*
*			List's size increases by 1										*
*																			*
*	======================================================================	*/

int appendListItem(ListADT listptr, dataitem_t data);


/*	======================================================================	*
*																			*
*	int deleteListItemAt(ListADT listptr, int index)						*
*																			*
*	DESCRIPTION: Deletes existing item at a specified location which must	*
*				 be in the range 0 ... size - 1.  Returns either same		*
*				 location (now with next item) or location of new			*
*				 last item which will be -1 when last item is deleted.		*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*			index is between 0 ... size - 1									*
*		Input parameter listptr is app's list pointer						*
*		Input parameter index is list location where item will be removed	*
*		Returns new cursor location 										*
*		Post conditions: item removed from list and size reduced by 1		*
*			Current list location either same (with next item in its place)	*
*				or new last item in list or -1								*
*																			*
*	======================================================================	*/

int deleteListItemAt(ListADT listptr, int index);


/*	======================================================================	*
*																			*
*	int deleteListItem(ListADT listptr)										*
*																			*
*	DESCRIPTION: Deletes existing item at current cursor location which		*
*				 must be valid.  Returns either same location (now with		*
*				 next item) or location of new last item which will be -1	*
*				 when last item is deleted.									*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			Cursor position is valid										*
*		Input parameter listptr is app's list pointer						*
*		Returns new cursor location 										*
*		Post conditions: item removed from list and size reduced by 1		*
*			Current list location either same (with next item in its place)	*
*				or new last item in list or -1								*
*																			*
*	======================================================================	*/

int deleteListItem(ListADT listptr);


/*	======================================================================	*
*																			*
*	int replaceListItemAt(ListADT listptr, int index, dataitem_t data)		*
*																			*
*	DESCRIPTION: Replaces the data in existing item at a specified			*
*				 location which must be in the range 0 ... size - 1 and		*
*				 returns the same location.									*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*			index is between 0 ... size - 1									*
*			data contains new data for item									*
*		Input parameter listptr is app's list pointer						*
*		Input parameter index is list location of item to replace			*
*		Input parameter data is data to be stored in item					*
*		Returns same cursor location (just for consistency)					*
*		Post condition: data in specified item updated						*
*																			*
*	======================================================================	*/

int replacelistItemAt(ListADT listptr, int index, dataitem_t data);


/*	======================================================================	*
*																			*
*	int replaceListItem(ListADT listptr, dataitem_t data)					*
*																			*
*	DESCRIPTION: Replaces the data in existing item at current cursor		*
*				 location which must be valid.  Returns the same location.	*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			Cursor position is valid										*
*			data contains new data for item									*
*		Input parameter listptr is app's list pointer						*
*		Input parameter data is data to be stored in item					*
*		Returns same cursor location (just for consistency)					*
*		Post condition: data in specified item updated						*
*																			*
*	======================================================================	*/

int replaceListItem(ListADT listptr, dataitem_t data);


/*	======================================================================	*
*																			*
*	dataitem_t getListItemAt(ListADT listptr, int index)					*
*																			*
*	DESCRIPTION: Retrieves the data from existing item at a specified		*
*				 location which must be in range 0 ... size - 1.			*
*				 Item's location becomes list's current location.			*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*			index in range 0 ... size - 1									*
*		Input parameter listptr is app's list pointer						*
*		Input parameter index is list location of item						*
*		Returns copy of data from item 										*
*		Post condition: specified location becomes current list location	*
*																			*
*	======================================================================	*/

dataitem_t getListItemAt(ListADT listptr, int index);


/*	======================================================================	*
*																			*
*	dataitem_t getListItem(ListADT listptr)									*
*																			*
*	DESCRIPTION: Retrieves the data from existing item at current cursor	*
*				 location which must be valid.								*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			Cursor is valid													*
*		Input parameter listptr is app's list pointer						*
*		Returns data from item		 										*
*		Post condition: list unchanged										*
*																			*
*	======================================================================	*/

dataitem_t getListItem(ListADT listptr);


/*	======================================================================	*
*																			*
*	int setListCursorAt(ListADT listptr, int index)							*
*																			*
*	DESCRIPTION: Sets list cursor to specified item of a non-empty list		*
*				 where index must be in the range 0 ... size - 1.  Returns	*
*				 new cursor location.										*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*			index in range 0 ... size - 1									*
*		Input parameter listptr is app's list pointer						*
*		Input parameter index is list location of desired item				*
*		Returns new cursor location	 										*
*		Post condition: list cursor updated									*
*																			*
*	======================================================================	*/

int setListCursorAt(ListADT listptr, int index);


/*	======================================================================	*
*																			*
*	int setListCursorFirst(ListADT listptr)									*
*																			*
*	DESCRIPTION: Sets list cursor to first item in a non-empty list and		*
*				 returns the new cursor location.							*
*																			*
*		Precondition: list exists (listptr is valid) and is non-empty		*
*		Input parameter listptr is app's list pointer						*
*		Returns new cursor location	 										*
*		Post condition: list cursor updated to first item					*
*																			*
*	======================================================================	*/

int setListCursorFirst(ListADT listptr);


/*	======================================================================	*
*																			*
*	int setListCursorLast(ListADT listptr)									*
*																			*
*	DESCRIPTION: Sets list cursor to last item in non-empty list and		*
*				 returns the new list location.								*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*		Input parameter listptr is app's list pointer						*
*		Returns new cursor location	 										*
*		Post condition: list cursor updated to last item					*
*																			*
*	======================================================================	*/

int setListCursorLast(ListADT listptr);


/*	======================================================================	*
*																			*
*	int setListCursorNext(ListADT listptr)									*
*																			*
*	DESCRIPTION: Sets list cursor, which must be currently valid, to next	*
*				 item in list.  Returns the new cursor location which will	*
*				 be -1 if the cursor was located at last item.				*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*			Cursor position is valid										*
*		Input parameter listptr is app's list pointer						*
*		Returns new cursor location	 										*
*		Post condition: list cursor updated									*
*																			*
*	======================================================================	*/

int setListCursorNext(ListADT listptr);


/*	======================================================================	*
*																			*
*	int setListCursorBack(ListADT listptr)									*
*																			*
*	DESCRIPTION: Sets list cursor, which must be currently valid, to		*
*				 previous item in list.  Returns the new cursor location	*
*				 which will be -1 if the cursor was located at first item.	*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*			Cursor position is valid										*
*		Input parameter listptr is app's list pointer						*
*		Returns new cursor location	 										*
*		Post condition: list cursor updated									*
*																			*
*	======================================================================	*/

int setListCursorBack(ListADT listptr);


/*	======================================================================	*
*																			*
*	int findListItem(ListADT listptr, dataitem_t data)						*
*																			*
*	DESCRIPTION: Performs a first-to-last search for first item with		*
*				 matching data and returns its location or -1 if not found.	*
*				 List must not be empty.  Searches unsorted lists.			*
*																			*
*		Preconditions: list exists (listptr is valid) and is non-empty		*
*		Input parameter listptr is app's list pointer						*
*		Input parameter data is target of search							*
*		Returns list location of first item with matching data or -1		*
*		Post condition: list cursor updated to item or set invalid			*
*																			*
*	======================================================================	*/

int findListItem(ListADT listptr, dataitem_t data);


/*	======================================================================	*
*																			*
*	int findListItemAscend(ListADT listptr, dataitem_t data)				*
*																			*
*	DESCRIPTION: Performs an ascending first-to-last search for the last	*
*				 item with matching data and returns its location or -1		*
*				 if not found.  List must not be empty and is expected to	*
*				 be sorted in ascending order.  List cursor will be left	*
*				 at last matching item or at the item to which a new item	*
*				 with the data should be appended for an ascending list.	*
*				 Cursor location will be invalid when the new data item		*
*				 needs to be inserted before first item.					*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			List is not empty and must be sorted ascending					*
*		Input parameter listptr is app's list pointer						*
*		Input parameter data is target of search							*
*		Returns list location of last item with matching data or -1			*
*		Post condition: cursor location updated								*
*																			*
*	======================================================================	*/

int findListItemAscend(ListADT listptr, dataitem_t data);


/*	======================================================================	*
*																			*
*	int findListItemDescend(ListADT listptr, dataitem_t data)				*
*																			*
*	DESCRIPTION: Performs a descending first-to-last search for the last	*
*				 item with matching data and returns its location or -1		*
*				 if not found.  List must not be empty and is expected to	*
*				 be sorted in descending order.  List cursor will be left	*
*				 at last matching item or at the item to which a new item	*
*				 with the data should be appended for an descending list.	*
*				 Cursor location will be invalid when the new data item		*
*				 needs to be inserted before first item.					*
*																			*
*		Preconditions: list exists (listptr is valid)						*
*			List is not empty and must be sorted descending					*
*		Input parameter listptr is app's list pointer						*
*		Input parameter data is target of search							*
*		Returns list location of last item with matching data or -1			*
*		Post condition: cursor location updated								*
*																			*
*	======================================================================	*/

int findListItemDescend(ListADT listptr, dataitem_t data);

#endif
