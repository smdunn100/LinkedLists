#ifndef SLNODE
#define SLNODE

/*
 *	File:		  SingleLinkNode.h
 *	Project:	  LinkedList
 *	Assignment:	  Programming Project #3
 *	Programmer:	  Stephen Dunn
 *	Date:		  10/27/2020
 *	University:	  McMurry University
 *	Course:		  COSC–3360 Fall 2020
 *	Instructor:	  Mr. Brozovic
 *	Compiler:	  Visual Studio
 *	Description:  Node for singly linked lists
 */

#include "DataItem.h"

typedef struct SLnode_t {
	dataitem_t data;
	struct SLnode_t *link;
} SLnode_t;

#endif
