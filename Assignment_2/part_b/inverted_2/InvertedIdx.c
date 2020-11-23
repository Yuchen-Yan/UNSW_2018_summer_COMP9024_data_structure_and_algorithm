/*
 Inverted Index ADT (partial) implementation, written by Ashesh Mahidadia Jan 2018.
 You may need to modify the following implementation and test it properly before using 
 in your program.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "InvertedIdx.h"
#include "DLListStr.h"

#define data(tree)  ((tree)->data)
#define left(tree)  ((tree)->left)
#define right(tree) ((tree)->right)



// make a new node containing data
Tree newNode(Item it) {
   Tree new = malloc(sizeof(Node));
   assert(new != NULL);
   strcpy(new->data, it);  // replace,   data(new) = it;
   left(new) = right(new) = NULL;
   return new;
}

// create a new empty Tree
Tree newTree() {
   return NULL;
}

// free memory associated with Tree
void freeTree(Tree t) {
   if (t != NULL) {
      freeTree(left(t));
      freeTree(right(t));
      free(t);
   }
}

// display Tree sideways
void showTreeR(FILE *f, Tree t, int depth) {
   if (t != NULL) {
      showTreeR(f, left(t), depth+1);
      int i;
      //for (i = 0; i < depth; i++){
           //putchar('\t');
      //}
      fprintf(f,"%s", data(t));
      fprintf(f," ");
      showDLListStr(f, t->list);
      showTreeR(f, right(t), depth+1);
   }
    
}

void showTree(FILE *f,Tree t) {
   showTreeR(f, t, 0);
}

// check whether a key is in a Tree
bool TreeSearch(Tree t, Item it) {
    if (t == NULL){
        return false;
    } else if (strcmp(it, data(t)) < 0){
        return TreeSearch(left(t), it);
    } else if (strcmp(it, data(t)) > 0){
        return TreeSearch(right(t), it);
    } else {
        return true;
    }
    
}

// insert a new item into a Tree
Tree TreeInsert(Tree t, Item it, Item url){
    if (t == NULL){
       t = newNode(it);
       t -> list = newDLListStr();
       insertSetOrd(t->list, url);
    } else if (strcmp(it, data(t)) < 0){
       left(t) = TreeInsert(left(t), it, url);
    } else if (strcmp(it, data(t)) > 0){
       right(t) = TreeInsert(right(t), it, url);
    } else if(strcmp(it, data(t)) == 0) {
        insertSetOrd(t ->list, url);
    }
    
   return t;
}

