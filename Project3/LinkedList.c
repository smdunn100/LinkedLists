/*
 *	File:		  LinkedList.c
 *	Project:	  LinkedList
 *	Assignment:	  Programming Project #3
 *	Programmer:	  Stephen Dunn
 *	Date:		  11/9/2020
 *	University:	  McMurry University
 *	Course:		  COSC–3360 Fall 2020
 *	Instructor:	  Mr. Brozovic
 *	Compiler:	  Visual Studio
 *	Description:  Linked list implementation of an ADT List
 */

#include <stdlib.h>
#include <assert.h>
#include "SingleLinkNode.h"
#include "List.h"


typedef struct LinkedListCDT {
	SLnode_t* headptr;
	SLnode_t* tailptr;
	SLnode_t* cursorptr;
	int cursorindex;
	int itemcount;
} LinkedListCDT;


 /*	======================================================================	*
  *																			*
  *	ADT LIST IMPLEMENTATION with LINKED LIST								*
  *																			*
  *		The following is a general overview -- detailed descriptions are	*
  *		provided just prior to each function below.							*
  *																			*
  *		Five variables, which are not available to application programs,	*
  *		are used to maintain the list:										*
  *			1)	Head pointer always identifies first item in list.			*
  *			2)	Tail pointer always identifies last item in list.			*
  *			3)	Cursor pointer moves through the list and is used identify	*
  *				selected items.  Some operations will automatically update	*
  *				the cursor and application programs can move the cursor by	*
  *				using available functions.									*
  *			4)	Cursor index maintains ordinal position of cursor pointer	*
  *				and functions like an array index with 0 as the first item	*
  *				in list and -1 when cursor is null.							*
  *			5)	Item counter maintains current number of items in list the	*
  *				current size of the list.									*
  *																			*
  *		EMPTY LIST:  Head, tail, and cursor pointers will all be NULL.		*
  *			Cursor index will be -1 and item count will be 0.  The only		*
  *			list manipulation functions that can be invoked with an empty	*
  *			list are insert and append.										*
  *																			*
  *		NON-EMPTY LIST:  Head pointer will identify the first list item		*
  *			while tail pointer will identify the last list item.  The		*
  *			cursor pointer will identify current list item with the cursor	*
  *			index as the corresponding position.  When the cursor pointer	*
  *			is NULL the cursor index will be -1.							*
  *																			*
  *		BASIC LIST OPERATIONS:  Include functions to create, destroy, and	*
  *			erase a list.  Also, checking empty/full status, size of list,	*
  *			and whether or not cursor identifies a valid item and whether	*
  *			or not it has a next item.										*
  *																			*
  *		INSERT and APPEND OPERATIONS:  Application program must provide		*
  *			desired index location or pre-position cursor at desired		*
  *			location.  A new list item will be allocated to store the data	*
  *			provided and it will be linked into the list before (insert)	*
  *			or after (append) the specified location.						*
  *																			*
  *		DELETE OPERATIONS:  Application program must provide desired index	*
  *			location or pre-position cursor at desired location.  Item		*
  *			will be unlinked and deallocated.								*
  *																			*
  *		REPLACE OPERATIONS:  Application program must provide desired index	*
  *			location or pre-position cursor at desired location.  Data in	*
  *			item will be replaced by the new data provided.					*
  *																			*
  *		GET OPERATIONS:  Application program must provide desired index		*
  *			location or pre-position cursor at desired location.  Copy of	*
  *			data from item will be returned.								*
  *																			*
  *		SET OPERATIONS:  Application program requests relocation of cursor	*
  *			to a specific location or increments/decrements the current		*
  *			location.														*
  *																			*
  *		FIND OPERATIONS:  Application program provides data for which to	*
  *			search for and positions cursor appropriately.					*
  *																			*
  *		The above was intended to be just an overview with details			*
  *		provided in the following function descriptions.  Everything		*
  *		except the implementation notes are duplicated in the interface		*
  *		definition (List.h).
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
   *	IMPLEMENTATION NOTES:													*
   *		Capacity ignored for linked list implementation						*
   *		On successful allocation of new list,								*
   *			All linked list pointers set to null							*
   *			Cursor index set to -1											*
   *			Item count set to 0												*
   *																			*
   *	======================================================================	*/

ListADT newList(int capacity) {
	assert(capacity >= 0);
	ListADT newlist;
	newlist = malloc(sizeof(LinkedListCDT));
	if (newlist){
		newlist->headptr = NULL;
		newlist->tailptr = NULL;
		newlist->cursorptr = NULL;
		newlist->cursorindex = -1;
		newlist->itemcount = 0;
	}
	return newlist;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Free all existing items												*
 *		Free the ADT pointer												*
 *		Set app's pointer to null											*
 *																			*
 *	======================================================================	*/

void freeList(ListADT* listptr) {
	assert(listptr != NULL && *listptr != NULL);
	clearList(*listptr);
	free(*listptr);
	*listptr = NULL;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Free all items from list											*
 *		All pointers are null												*
 *		Cursor index and item count set to initial (empty) values			*
 *																			*
 *	======================================================================	*/

void clearList(ListADT listptr) {
	assert(listptr != NULL);
	SLnode_t* step;
	setListCursorFirst(listptr);
	while (isListItem(listptr)){
		step = listptr->cursorptr->link;
		free(listptr->cursorptr);
		listptr->cursorptr = step;
	}
	listptr->headptr = NULL;
	listptr->tailptr = NULL;
	listptr->cursorptr = NULL;
	listptr->cursorindex = -1;
	listptr->itemcount = 0;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Length is current item count										*
 *																			*
 *	======================================================================	*/

int listLength(ListADT listptr) {
	assert(listptr != NULL);
	return listptr->itemcount;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Cursor pointer non-null when pointing to an item					*
 *		Also, cursor index >= 0												*
 *																			*
 *	======================================================================	*/

int isListItem(ListADT listptr) {
	assert(listptr != NULL);
	if (listptr->cursorindex >= 0 && listptr->cursorptr != NULL)
		return 1;
	else
		return 0;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Cursor item's link will be non-null when next item exists			*
 *																			*
 *	======================================================================	*/

int hasNextListItem(ListADT listptr) {
	assert(listptr != NULL);
	assert(listptr->cursorindex >= 0);
	if (listptr->cursorindex < listLength(listptr) - 1 && listptr->cursorptr != NULL && listptr->cursorptr->link != NULL)
		return 1;
	else
		return 0;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Item count 0 when empty, also head and tail pointers null			*
 *																			*
 *	======================================================================	*/

int isListEmpty(ListADT listptr) {
	assert(listptr != NULL);
	if (listptr->headptr == NULL && listptr->tailptr == NULL && listptr->itemcount == 0)
		return 1;
	else
		return 0;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Always false for linked list implementation							*
 *		(ignore possibility list could grow to memory limit)				*
 *																			*
 *	======================================================================	*/

int isListFull(ListADT listptr) {
	assert(listptr != NULL);
	return 0;		/* change what is returned */
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Make sure cursor properly positioned then call either				*
 *			insertListItem() or appendListItem() -- don't duplicate			*
 *			insert/append logic												*
 *																			*
 *	======================================================================	*/

int insertListItemAt(ListADT listptr, int index, dataitem_t data) {
	assert(listptr != NULL && index >= 0 && index <= listLength(listptr));
	setListCursorAt(listptr, index);
	if (index == listLength(listptr) - 1)
		appendListItem(listptr, data);
	else
		insertListItem(listptr, data);
	listptr->itemcount++;
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Allocate a new item and if successful, store data, then link		*
 *			new item into list												*
 *		New item inserted before current item as defined by cursor			*
 *		When cursor is null, insert at start of list						*
 *		Head and tail pointers updated as needed							*
 *		Cursor pointer and index updated to new item						*
 *		Increment size														*
 *																			*
 *	======================================================================	*/

int insertListItem(ListADT listptr, dataitem_t data) {
	assert(listptr != NULL);
	SLnode_t* item = (SLnode_t*)malloc(sizeof(SLnode_t));
	if (item){
		item->data = data;

		if (listptr->itemcount == 0){
			item->link = listptr->headptr;
			listptr->headptr = item;
			listptr->tailptr = item;
			listptr->tailptr->link = NULL;
			listptr->cursorptr = item;
			listptr->cursorindex++;
			listptr->itemcount++;
		}
		else if (listptr->cursorptr == NULL || listptr->cursorptr == listptr->headptr){
			item->link = listptr->headptr;
			listptr->headptr = item;
			listptr->cursorptr = item;
			listptr->itemcount++;
		}
		else{
			setListCursorBack(listptr);
			item->link = listptr->cursorptr->link;
			listptr->cursorptr->link = item;
			listptr->cursorptr = item;
			listptr->cursorindex++;
			listptr->itemcount++;
		}
	}
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Make sure cursor properly positioned and call appendListItem()		*
 *			-- don't duplicate append logic									*
 *																			*
 *	======================================================================	*/

int appendListItemAt(ListADT listptr, int index, dataitem_t data) {
	assert(listptr != NULL && index >= 0 && index <= listLength(listptr));
	setListCursorAt(listptr, index);
	appendListItem(listptr, data);
	listptr->itemcount++;
	return listptr->cursorindex;
}


/*	======================================================================	*
 *																			*
 *	int appendListItem(ListADT listptr, dataitem_t data)					*
 *																			*
 *	DESCRIPTION: Appends a new item to an existing list at the current		*
 *				 cursor location, after any existing item.  When cursor		*
 *				 is not valid, the new item is appended to the end of the	*
 *				 list.  Returns location of new item.						*											
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
 *	IMPLEMENTATION NOTES:													*
 *		Allocate a new item and if successful, store data, then link		*
 *			new item into list												*
 *		New item inserted after current item as defined by cursor			*
 *		When cursor is null, append at end of list							*
 *		Head and tail pointers updated as needed							*
 *		Cursor pointer and index updated to new item						*
 *		Increment size														*
 *																			*
 *	======================================================================	*/

int appendListItem(ListADT listptr, dataitem_t data) {
	assert(listptr != NULL);
	SLnode_t* item = (SLnode_t*)malloc(sizeof(SLnode_t));
	if (item)
	{
		item->data = data;
		if ( listptr->itemcount == 0 && listptr->cursorptr == NULL)
		{
			item->link = listptr->tailptr;
			listptr->headptr = item;
			listptr->cursorptr = item;
			listptr->tailptr = item;
			listptr->cursorindex++;
			listptr->itemcount++;
		}
		else if (listptr->cursorptr == NULL || listptr->cursorptr == listptr->tailptr)
		{
			listptr->tailptr->link = item;
			listptr->tailptr = item;
			listptr->tailptr->link = NULL;
			listptr->cursorptr = item;
			listptr->cursorindex++;
			listptr->itemcount++;
		}
		else
		{
			item->link = listptr->cursorptr->link;
			listptr->cursorptr->link = item;
			listptr->cursorptr = item;
			listptr->cursorindex++;
			listptr->itemcount++;
		}
	}
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Make sure cursor properly positioned and call deleteListItem()		*
 *			-- don't duplicate delete logic									*
 *																			*
 *	======================================================================	*/

int deleteListItemAt(ListADT listptr, int index) {
	assert(listptr != NULL && index >= 0 && index < listLength(listptr) - 1);
	setListCursorAt(listptr, index);
	deleteListItem(listptr);
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Relink items to remove item identified by cursor					*
 *		Free item															*
 *		Adjust cursor location as needed									*
 *		Decrement size														*
 *																			*
 *	======================================================================	*/

int deleteListItem(ListADT listptr) {
	assert(listptr != NULL);
	assert(listptr->cursorindex >= 0 && listptr->cursorptr != NULL);
	SLnode_t* tempnode;
	SLnode_t* delnode;
	if (listptr->cursorptr == listptr->tailptr || listptr->cursorindex == listLength(listptr) - 1)
	{
		setListCursorBack(listptr);
		delnode = listptr->cursorptr->link;
		listptr->tailptr = listptr->cursorptr;
		free(delnode);
		listptr->cursorindex--;
		listptr->itemcount--;
	}
	else if (listptr->cursorptr == listptr->headptr || listptr->cursorindex == 0)
	{
		delnode = listptr->cursorptr;
		listptr->cursorptr = listptr->cursorptr->link;
		listptr->headptr = listptr->cursorptr;
		free(delnode);
		listptr->itemcount--;
	}
	else
	{
		setListCursorBack(listptr);
		tempnode = listptr->cursorptr;
		delnode = tempnode->link;
		tempnode->link = delnode->link;
		free(delnode);
		setListCursorNext(listptr);
		listptr->itemcount--;
	}
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Position cursor and replace data									*
 *																			*
 *	======================================================================	*/

int replacelistItemAt(ListADT listptr, int index, dataitem_t data) {
	assert(listptr != NULL && isListEmpty(listptr) == 0);
	assert(index >= 0 && index < listLength(listptr));
	setListCursorAt(listptr, index);
	replaceListItem(listptr, data);
	return listptr->cursorindex;
}


/*	======================================================================	*
 *																			*
 *	int replaceListItem(ListADT listptr, dataitem_t data)					*
 *																			*
 *	DESCRIPTION: Replaces the data in existing item at current cursor		*
 *				 location which must be valid.  Returns the same location.	*
 *																			*
 *		Preconditions: list exists (listptr is valid) and is non-empty		*
 *			Cursor position is valid										*
 *			data contains new data for item									*
 *		Input parameter listptr is app's list pointer						*
 *		Input parameter data is data to be stored in item					*
 *		Returns same cursor location (just for consistency)					*
 *		Post condition: data in specified item updated						*
 *																			*
 *	IMPLEMENTATION NOTES:													*
 *		Replace data in cursor item											*
 *																			*
 *	======================================================================	*/

int replaceListItem(ListADT listptr, dataitem_t data) {
	assert(listptr != NULL && listptr->cursorptr != NULL && isListEmpty(listptr) == 0);
	listptr->cursorptr->data = data;
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Position cursor and return data										*
 *																			*
 *	======================================================================	*/

dataitem_t getListItemAt(ListADT listptr, int index) {
	assert(listptr != NULL && isListEmpty(listptr) == 0 && index >= 0 && index < listLength(listptr));
	setListCursorAt(listptr, index);
	return listptr->cursorptr->data;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Return data from cursor item 										*
 *																			*
 *	======================================================================	*/

dataitem_t getListItem(ListADT listptr) {
	assert(listptr != NULL && listptr->cursorptr != NULL);
	assert(listptr->cursorindex < listLength(listptr) && listptr->cursorindex >= 0);
	return listptr->cursorptr->data;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Position list cursor at requested item								*
 *																			*
 *	======================================================================	*/

int setListCursorAt(ListADT listptr, int index) {
	assert(listptr != NULL && isListEmpty(listptr) == 0);
	assert(index >= 0 && index < listptr->itemcount);
	setListCursorFirst(listptr);
	while (listptr->cursorindex < index){
		listptr->cursorptr = listptr->cursorptr->link;
		listptr->cursorindex++;
	}
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Position list cursor at first item									*
 *																			*
 *	======================================================================	*/

int setListCursorFirst(ListADT listptr) {
	assert(listptr != NULL && isListEmpty(listptr) == 0);
	listptr->cursorptr = listptr->headptr;
	listptr->cursorindex = 0;
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Position list cursor at last item									*
 *																			*
 *	======================================================================	*/

int setListCursorLast(ListADT listptr) {
	assert(listptr != NULL && isListEmpty(listptr)==0);
	listptr->cursorptr = listptr->tailptr;
	listptr->cursorindex = listLength(listptr) - 1;
	return listptr->cursorindex;	
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Position list cursor at item following cursor item					*
 *																			*
 *	======================================================================	*/

int setListCursorNext(ListADT listptr) {
	assert(listptr != NULL && isListEmpty(listptr) == 0 && listptr->cursorptr != NULL);
	if (listptr->cursorindex == listLength(listptr) - 1)
		listptr->cursorindex = -1;
	else
	{
		listptr->cursorindex++;
		listptr->cursorptr = listptr->cursorptr->link;
	}
	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Position list cursor at item before cursor item						*
 *																			*
 *	======================================================================	*/

int setListCursorBack(ListADT listptr) {
	assert(listptr != NULL && isListEmpty(listptr) == 0 && listptr->cursorptr != NULL);
	if (listptr->cursorindex == 0)
		listptr->cursorindex = -1;
	else
		setListCursorAt(listptr, listptr->cursorindex - 1);

	return listptr->cursorindex;
}


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
 *	IMPLEMENTATION NOTES:													*
 *		Set list cursor at first item										*
 *		Walk list looking until matching data is found or end of list		*
 *																			*
 *	======================================================================	*/

int findListItem(ListADT listptr, dataitem_t data) {
	assert(listptr != NULL && isListEmpty(listptr)==0);
	int Cindex = listptr->cursorindex;
	setListCursorFirst(listptr);
	int LIposition = 0;
	while (listptr->cursorindex < listLength(listptr) && LIposition == 0)
	{
		if (listptr->cursorptr->data == data) {
			LIposition = listptr->cursorindex;
		}
		else{
			listptr->cursorptr = listptr->cursorptr->link;
			listptr->cursorindex++;
		}
	}
	if (LIposition)
		return LIposition;
	else
	{
		setListCursorAt(listptr, Cindex);
		return -1;
	}
}



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
 *	IMPLEMENTATION NOTES:													*
 *		Set list cursor at first element									*
 *		If data in first item is greater than target data, set cursor to	*
 *			null and cursor index to -1										*
 *		Otherwise, walk list to position cursor at last item containing		*
 *			data that is matching or less than target data, cursor index	*
 *			must also be adjusted.											*
 *																			*
 *	======================================================================	*/

int findListItemAscend(ListADT listptr, dataitem_t data) {
	assert(listptr != NULL && isListEmpty(listptr) == 0);
	setListCursorFirst(listptr);
	if (compareItem(listptr->cursorptr->data, data) == 1){
		listptr->cursorptr = NULL;
		listptr->cursorindex = -1;
	}
	else {
		while (listptr->cursorptr != listptr->tailptr && compareItem(listptr->cursorptr->data, data) == -1) {
			listptr->cursorptr = listptr->cursorptr->link;
			listptr->cursorindex++;
		}
		if (compareItem(listptr->cursorptr->data, data) == 1) 
			setListCursorBack(listptr);
		}
	return listptr->cursorindex;
}



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
 *	IMPLEMENTATION NOTES:													*
 *		Set list cursor at first element									*
 *		If data in first item is less than target data, set cursor to null	*
 *			and cursor index to -1											*
 *		Otherwise, walk list to position cursor at last item containing		*
 *			data that is matching or greater than target data, cursor		*
 *			index must also be adjusted.									*
 *																			*
 *	======================================================================	*/

int findListItemDescend(ListADT listptr, dataitem_t data) {
	assert(listptr != NULL && listptr->itemcount > 0);
	setListCursorFirst(listptr);
	if (compareItem(listptr->cursorptr->data, data) == -1) {
		listptr->cursorptr = NULL;
		listptr->cursorindex = -1;
	}
	else {
		while (compareItem(listptr->cursorptr->data, data) == 1 && listptr->cursorptr != listptr->tailptr){
			listptr->cursorptr = listptr->cursorptr->link;
			listptr->cursorindex++;
		}
		if (compareItem(listptr->cursorptr->data, data) == -1) {
			setListCursorBack(listptr);
		}
	}
	return listptr->cursorindex;
}
