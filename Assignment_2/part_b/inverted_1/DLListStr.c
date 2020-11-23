/*
 Implementation of doubly-linked list ADT for string values.
 Written by Ashesh Mahidadia Jan 2018, based on code writted by John Shepherd 2015.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "DLListStr.h"



// create a new DLListNode (private function)
static DLListNode *newDLListNode(char *val)
{
	DLListNode *new;
	new = malloc(sizeof(DLListNode));
	assert(new != NULL);

        strcpy(new->value, val);  // for int, new->value = it;
	
	new->prev = new->next = NULL;
	return new;
}

// create a new empty DLListStr
DLListStr newDLListStr(void)
{
	struct DLListRep *L;
	L = malloc(sizeof (struct DLListRep));
	assert (L != NULL);
	L->nitems = 0;
	L->first = NULL;
	L->last = NULL;
	L->curr = NULL;
	return L;
}


/* 
   pre-reqisite: L is ordered (increasing) with no duplicates
   post-condition: val is inserted in L, L is ordered (increasing) with no duplicates
*/
void insertSetOrd(DLListStr L, char *val){

	/* 
	   implement this function to
	   insert val in L  (in order), no duplicates (set)

	*/
    assert(L != NULL);
    DLListNode *new = newDLListNode(val);
    assert(new != NULL);
    L -> curr = L -> first;
    
    if (L->first == NULL && L->last == NULL){
        L->first = L->last = L->curr = new;
    } else if (L->first == L->last){
        if (strcmp(val,L->curr->value) < 0){
            new -> next = L->curr;
            L->curr ->prev = new;
            L->first = new;
        } else if (strcmp(val,L->curr->value) > 0){
            L->curr->next = new;
            new->prev = L->curr;
            L->last = new;
        }
    } else {
        while(L->curr != NULL){
            if (L->curr == L->first){
                if (strcmp(val,L->curr->value) < 0){
                    new->next = L->curr;
                    L->curr->prev = new;
                    L->first = new;
                    break;
                } else if (strcmp(val,L->curr->value) > 0 && strcmp(val,L->curr->next->value) < 0){
                    DLListNode *tmp = L->curr->next;
                    new ->prev = L->curr;
                    new ->next = tmp;
                    tmp ->prev = new;
                    L->curr->next = new;
                    break;
                } else if (strcmp(val, L->curr->value) == 0){
                    break;
                }
            } else if (L->curr == L->last){
                if (strcmp(val,L->curr->value)>0){
                    L->curr->next = new;
                    new -> prev = L -> curr;
                    L->last = new;
                    break;
                } else if (strcmp(val,L->curr->value) < 0 && strcmp(val,L->curr->prev->value) > 0){
                    DLListNode *tmp = L->curr->prev;
                    new ->next = L->curr;
                    new ->prev = tmp;
                    L->curr->prev = new;
                    tmp ->next = new;
                    break;
                } else if (strcmp(val,L->curr->value) == 0){
                    break;
                }
            } else {
                if (strcmp(val, L->curr->next->value) < 0 && strcmp(val,L->curr->value) > 0){
                    DLListNode *tmp = L->curr->next;
                    new->next = tmp;
                    new->prev = L->curr;
                    tmp->prev = new;
                    L->curr->next = new;
                    break;
                } else if (strcmp(val,L->curr->value) < 0 && strcmp(val,L ->curr ->prev ->value) > 0){
                    DLListNode *tmp = L->curr->prev;
                    new -> next = L->curr;
                    new -> prev = tmp;
                    tmp -> next = new;
                    L->curr->prev = new;
                    break;
                } else if(strcmp(val,L->curr->value) == 0){
                    break;
                }
            }
            L->curr = L->curr->next;
        }
    }
    
}



// display items from a DLListStr, comma separated
void showDLListStr(FILE *f, DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr;
	int count = 0;
	for (curr = L->first; curr != NULL; curr = curr->next){
		count++;
		if(count > 1) {
			fprintf(f, " ");
		}
		fprintf(f, "%s",curr->value);
	}
	fprintf(f, "\n");
}


// free up all space associated with list
void freeDLListStr(DLListStr L)
{
	assert(L != NULL);
	DLListNode *curr, *prev;
	curr = L->first;
	while (curr != NULL) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(L);
}


