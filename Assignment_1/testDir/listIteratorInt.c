/*
  listIteratorInt.c : list Iterator ADT implementation
  Written by Yuchen Yan
  Date: 03/01/2018
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "listIteratorInt.h"


//Node structure for double link list
typedef struct Node {
    int value;
    struct Node *prev;
    struct Node *next;
} Node;

//The representation of the iterator structure
typedef struct IteratorIntRep {
    Node *iterator;
    int NorP;
} IteratorIntRep;

//Create a new node for the list
Node *newNode(int v){
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new -> value = v;
    new -> next = NULL;
    new -> prev = NULL;
    return new;
}

//Create a new Iterator
IteratorInt IteratorIntNew(){
    IteratorIntRep *new = malloc(sizeof(IteratorIntRep));
    assert(new != NULL);
    new -> iterator  = newNode(100);
    new -> NorP = 0;
    return new;
}

//Reset the iterator to the font of the list
void reset(IteratorInt it){
    assert(it != NULL);
    if(it -> iterator -> prev == NULL){
        return;
    } else {
        while(it -> iterator -> prev != NULL){
            it -> iterator -> next = it -> iterator -> prev;
            it -> iterator -> prev = it -> iterator -> prev -> prev;
        }
    }
}

//Add new element into the list
int add(IteratorInt it, int v){
    //assert the itertor
    if (it == NULL){
        return 0;
    }
    
    //make a new node
    Node *new = newNode(v);
    
    //Insert node into the list
    if(it -> iterator -> prev == NULL && it -> iterator -> next == NULL){
        it -> iterator -> prev = new;
    } else if(it -> iterator -> prev == NULL){
        new -> next = it -> iterator -> next;
        it -> iterator -> next -> prev = new;
        it -> iterator -> prev = new;
    } else if(it -> iterator -> next == NULL){
        new -> prev = it -> iterator -> prev;
        it -> iterator -> prev -> next = new;
        it -> iterator -> prev = new;
    } else {
        new -> prev = it -> iterator -> prev;
        new -> next = it -> iterator -> next;
        it -> iterator -> prev -> next = new;
        it -> iterator -> next -> prev = new;
        it -> iterator -> prev = new;
    }
    return 1;
}

//Check if there is element in the next position
int hasNext(IteratorInt it){
    assert(it != NULL);
    return (it -> iterator -> next != NULL);
}

//Check if there is element in the previous position
int hasPrevious(IteratorInt it){
    assert(it != NULL);
    return (it -> iterator -> prev != NULL);
}

//Advance the iterator and return the next element's value
int *next(IteratorInt it){
    assert(it != NULL);
    if (it -> iterator -> next == NULL){
        return NULL;
    } else {
        int *v = &(it -> iterator -> next -> value);
        it -> iterator -> prev = it -> iterator -> next;
        it -> iterator -> next = it -> iterator -> next -> next;
        it -> NorP = 1;
        return v;
    }
}

//Previous the iterator and return the previous element's value
int *previous(IteratorInt it){
    assert(it != NULL);
    if (it -> iterator -> prev == NULL){
        return NULL;
    } else {
        int *v = &(it -> iterator -> prev -> value);
        it -> iterator -> next = it -> iterator -> prev;
        it -> iterator -> prev = it -> iterator -> prev -> prev;
        it -> NorP = 2;
        return v;
    }
}

//Delete the element just returned by next or previous or findNext or findPrevious
int deleteElm(IteratorInt it){
    assert(it != NULL);
    if (it -> NorP == 1){
        Node *curr = it -> iterator -> prev;
        if (curr -> next == NULL){
            curr -> prev -> next = curr -> next;
            it -> iterator -> prev = curr -> prev;
            free(curr);
        } else {
            curr -> prev -> next = curr -> next;
            curr -> next -> prev = curr -> prev;
            it -> iterator -> prev = curr -> prev;
            free(curr);
        }
        return 1;
    } else if (it -> NorP == 2){
        Node *curr = it -> iterator -> next;
        if (curr -> prev == NULL){
            curr -> next -> prev = curr -> prev;
            it -> iterator -> next = curr -> next;
            free(curr);
        } else {
            curr -> prev -> next = curr -> next;
            curr -> next -> prev = curr -> prev;
            it -> iterator -> next = curr -> next;
            free(curr);
        }
        return 1;
        
    }
    return 0;
}

//Set the value of the element which just returned by next or previous or findNext or findPrevious
int set(IteratorInt it, int v){
    assert(it != NULL);
    if (it -> NorP == 1){
        it -> iterator -> prev -> value = v;
        return 1;
    } else if (it -> NorP == 2) {
        it -> iterator -> next -> value = v;
        return 1;
    }
    return 0;
}

//Find the next element which have the input value
int *findNext(IteratorInt it, int v){
    assert(it != NULL);
    if (it -> iterator -> next == NULL){
        return NULL;
    } else {
        Node *curr;
        curr = it -> iterator -> next;
        while(curr != NULL && curr -> value != v){
            curr = curr -> next;
        }
        if (curr != NULL){
            it -> iterator -> prev = curr;
            it -> iterator -> next = curr -> next;
            it -> NorP = 1;
            return &(curr->value);
        }
    }
    return NULL;
}

//Find the previous element which have the input value
int *findPrevious(IteratorInt it, int v){
    assert(it != NULL);
    if (it -> iterator -> prev == NULL){
        return NULL;
    } else {
        Node *curr;
        curr = it -> iterator -> prev;
        while(curr != NULL && curr -> value != v){
            curr = curr -> prev;
        }
        if (curr != NULL){
            it -> iterator -> prev = curr -> prev;
            it -> iterator -> next = curr;
            it -> NorP = 2;
            return &(curr->value);
        }
    }
    return NULL;
    
    return 0;
}

//Fre the iterator and the linked list
void freeIt(IteratorInt it){
    assert(it != NULL);
    reset(it);
    if (it -> iterator -> prev == NULL && it -> iterator -> next == NULL) {
        free(it -> iterator);
        free(it);
        return;
    } else {
        while(next(it)){
            Node *p = it -> iterator -> prev;
            it -> iterator -> prev = NULL;
            free(p);
        }
        free(it -> iterator);
        free(it);
        return;
    }
}





