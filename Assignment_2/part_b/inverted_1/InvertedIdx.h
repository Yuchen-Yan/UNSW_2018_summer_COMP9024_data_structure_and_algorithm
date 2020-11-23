/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdbool.h>
#include "DLListStr.h"


typedef char *Item;      // item is just a key

typedef struct Node *Tree;


typedef struct Node {
    Tree left, right;
    char  data[100];
    DLListStr  list;
} Node;

Tree newNode(Item);
Tree newTree();        // create an empty Tree
void freeTree(Tree);   // free memory associated with Tree
void showTree(FILE *, Tree);   // display a Tree (sideways)

bool TreeSearch(Tree, Item);   // check whether an item is in a Tree
Tree TreeInsert(Tree, Item, Item);   // insert a new item into a Tree



