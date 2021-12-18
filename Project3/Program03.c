#define _CRT_SECURE_NO_WARNINGS

/*
 *	File:		  Program03.c
 *	Project:	  LinkedList
 *	Assignment:	  Programming Project #3
 *	Programmer:	  Stephen Dunn
 *	Date:		  11/9/2020
 *	University:	  McMurry University
 *	Course:		  COSC–3360 Fall 2020
 *	Instructor:	  Mr. Brozovic
 *	Compiler:	  Visual Studio
 *	Description:  App using the linked list to create a list of integers
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DataItem.h"
#include "List.h"


void displayList(char *title, ListADT list);

int main(int argc, char *argv[])
{

	FILE *infptr;
	ListADT mylist1, mylist2;
	int data, inscount, delcount, nodelcount, dupcount, count;
	
	printf("\t\t     Program #3\n");
	printf("\t\t McMurry University\n");
	printf("\t\tCOSC-3360  Fall 2020\n");
	printf("\t\t  by Stephen Dunn\n\n");

	/* Check for expected command line arg */
	if (argc != 2) {
		printf("\nUsage:  program03 input-file\n");
		printf("\nPress ENTER to continue...\n");
		getchar();
		return -1;
	}

	/*  Open the input file  */
	infptr = fopen(argv[1], "r");
	if (!infptr) {
		printf("\nError opening input file: \"%s\"!\n", argv[1]);
		printf("\nProgram terminating due to errors!\n");
		printf("\nPress ENTER to continue...\n");
		getchar();
		return -1;
	}

	// create list
	mylist1 = newList(1);
	mylist2 = newList(1);
	count = 0;
	inscount = 0;
	delcount = 0;
	nodelcount = 0;
	dupcount = 0;

	// lists are unsorted with possibility of duplicates
	//    APPENDing each new data item after last item of mylist1
	//    INSERTing each new data item before first item of mylist2

	while (!feof(infptr)) {
		fscanf(infptr, "%d", &data);
		count++;
		if (data > 0) {   /* insert data into list */
			appendListItem(mylist1, data);
			insertListItem(mylist2, data);
//			printf("\t%4d Inserted\n", data);
			inscount++;
		}
		else if (data < 0) {   /* delete data from list (if found) */
			data *= -1;   
			if (isListEmpty(mylist1)) {
				printf("\t%4d NOT Deleted -- lists are empty!\n", data);
				nodelcount++;
			}
			else if (findListItem(mylist1, data) != -1) {
				deleteListItem(mylist1);
				findListItem(mylist2, data);
				deleteListItem(mylist2);
				delcount++;
				setListCursorLast(mylist1);  // so next append after last
				setListCursorFirst(mylist2);  // so next insert before first
			}
			else {
				nodelcount++;
			}
		}
		else {
			printf("\nWARNING -- unexpected data item [0] encountered!\n");
		}
	//	displayList("List 1", mylist1);
		setListCursorLast(mylist1);  
	//	displayList("List 2", mylist2);
		setListCursorFirst(mylist2);  
	}
	fclose(infptr);

	printf("\n\t%4d integers were read\n", count);
	printf("\t%4d integers were INSERTED\n", inscount);
	printf("\t%4d integers were DUPLICATES and NOT INSERTED\n", dupcount);
	printf("\t%4d integers were DELETED\n", delcount);
	printf("\t%4d integers were NOT FOUND for deletion\n", nodelcount);

	printf("\n\tFinal lists contain %d integers\n", listLength(mylist1));

	// display and destroy lists
	displayList("List 1 (FINAL)", mylist1);
	freeList(&mylist1);

	displayList("List 2 (FINAL)", mylist2);
	freeList(&mylist2);


	infptr = fopen(argv[1], "r");
	if (!infptr) {
		printf("\nError opening input file: \"%s\"!\n", argv[1]);
		printf("\nProgram terminating due to errors!\n");
		printf("\nPress ENTER to continue...\n");
		getchar();
		return -1;
	}

	mylist1 = newList(1);
	mylist2 = newList(2);
	//count = 0;
	delcount = 0;
	nodelcount = 0;
	dupcount = 0;
	int inscounterA = 0;
	int inscounterB = 0;

	for(count = 0; !feof(infptr); count++){
		fscanf(infptr, "%d", &data);
		if (isListEmpty(mylist1)){
			appendListItem(mylist1, data);
			appendListItem(mylist2, data);
			inscounterA++;
			inscounterB++;
			count++;
			count = 0;
		}
		else
		{
			if (data > 0) {   
				if (findListItemAscend(mylist1, data) != -1){
					if (getListItem(mylist1) != data){
						appendListItem(mylist1, data);
						inscounterA++;
					}
					else
						dupcount++;
				}
				else{
					insertListItem(mylist1, data);
					inscounterA++;
				}
				if (findListItemDescend(mylist2, data) != -1){
					appendListItem(mylist2, data);
					inscounterB++;
				}
				else{
					insertListItem(mylist2, data);
					inscounterB++;
				}
			}
			else if (data < 0){  
				data*=-1;    
				if (isListEmpty(mylist1)){
					nodelcount++;
				}
				else if (findListItem(mylist1, data) != -1){
					deleteListItem(mylist1);
					findListItem(mylist2, data);
					deleteListItem(mylist2);
					setListCursorLast(mylist1);  
					setListCursorFirst(mylist2); 
					delcount++;

				}
				else{
					nodelcount++;
				}
			}
			else {
				printf("\nWARNING -- unexpected data item [0] encountered!\n");
			}
		}
	}
	fclose(infptr);

	printf("\n\tBuild Ascending List with NO Duplicates Allowed\n");
	printf("\n\t%4d integers were read\n", count);
	printf("\t%4d integers were INSERTED\n", inscounterA);
	printf("\t%4d integers were DUPLICATES and NOT INSERTED\n", dupcount);
	printf("\t%4d integers were DELETED\n", delcount);
	printf("\t%4d integers were NOT FOUND for deletion\n", nodelcount);
	printf("\n\tFinal lists contain %d integers\n", listLength(mylist1));
	displayList("List 1 (ASCENDING NO DUPS)", mylist1);
	freeList(&mylist1);

	dupcount = 0;
	printf("\n\tBuild Descending List with Duplicates Allowed\n");
	printf("\n\t%4d integers were read\n", count);
	printf("\t%4d integers were INSERTED\n", inscounterB);
	printf("\t%4d integers were DUPLICATES and NOT INSERTED\n", dupcount);
	printf("\t%4d integers were DELETED\n", delcount);
	printf("\t%4d integers were NOT FOUND for deletion\n", nodelcount);
	printf("\n\tFinal lists contain %d integers\n", listLength(mylist2));
	displayList("List 2 (DESCENDING WITH DUPS)", mylist2);
	freeList(&mylist2);


	//system("pause");
	return 0;
}

void displayList(char *title, ListADT list) {
	int count = 0;
	assert(list != NULL);
	if (isListEmpty(list)) {
		printf("\n\t%s is empty!\n", title);
	}
	else {
		setListCursorFirst(list);
		printf("\n\tContents of %s\n\n", title);
		while (isListItem(list)) {
			printf("%7d", getListItem(list));
			if (++count % 10 == 0) printf("\n");
			setListCursorNext(list);
		}
		printf("\n\n");
	}
}

