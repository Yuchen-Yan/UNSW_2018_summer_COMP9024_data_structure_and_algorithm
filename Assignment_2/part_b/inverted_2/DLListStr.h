// DLListStr.h - Interface to doubly-linked list ADT
// Written by John Shepherd, March 2013
// Last modified, Ashesh Mahidadia, Jan 2017 

#ifndef DLListStr_H
#define DLListStr_H

#include <stdio.h>
#include "DLListStr.h"

// External view of DLListStr
// Implementation given in DLListStr.c
// Implements a DLListStr of string 

typedef struct DLListRep *DLListStr;



// data structures representing DLListStr

typedef struct DLListNode {
    char   value[100];  // value of this list item (string)
    struct DLListNode *prev;
    // pointer previous node in list
    struct DLListNode *next;
    // pointer to next node in list
} DLListNode;

typedef struct DLListRep {
    int  nitems;      // count of items in list
    DLListNode *first; // first node in list
    DLListNode *curr;  // current node in list
    DLListNode *last;  // last node in list
} DLListRep;

// create a new empty DLListStr
DLListStr newDLListStr(void);

void insertSetOrd(DLListStr, char*);

// free up all space associated with list
void freeDLListStr(DLListStr);

// display items from a DLListStr, comma separated
void showDLListStr(FILE *, DLListStr);



#endif
