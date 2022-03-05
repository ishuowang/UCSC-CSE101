//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#include "List.h"

// structs --------------------------------------------------------------------
// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
// The struct NodeObj should contain fields for an int (the data), 
// and two Node references (the previous and next Nodes, respectively.)
typedef struct NodeObj{
   int data;
   Node previous;
   Node next;
} NodeObj;

// private QueueObj type
// ListObj should contain fields of type Node referring to the front, back and cursor elements respectively.
// ListObj should also contain int fields for the length of a List, and the index of the cursor element.
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->previous = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
      pN = NULL;
   }
}

// new()
// Returns reference to new empty List object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
// TODO : check free and clear 
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      clear(*pL);
      free(*pL);
      *pL = NULL;
      pL = NULL;
   }
}


// Access functions -----------------------------------------------------------
int length(List L){
   return(L->length);
}

int index(List L){
   return(L->index);
}

int front(List L){
   return(L->front->data);
}

int back(List L){
   return(L->back->data);
}

int get(List L){
   return(L->cursor->data);
}

bool equals(List A, List B){
   if(A->length != B->length){
      return(false);
   }
   if(A->length == 0 && B->length == 0){
      return(true);
   }
   moveFront(A);
   moveFront(B);
   while( index(A)>=0 && index(B)>=0 ){
      int a = get(A);
      int b = get(B);
      if(a != b){
         return(false);
      }
      moveNext(A);
      moveNext(B);
   }
   return(true);
}


// Manipulation procedures ----------------------------------------------------

void clear(List L){
   if(L->length == 0){
      return;
   }
   Node temp_node;
   Node node = L->front;
   while(node != L->back){
      temp_node = node->next;
      freeNode(&node);
      node = temp_node;
   }
   free(L->back);
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
}


void set(List L, int x){
   L->cursor->data = x;
}

void moveFront(List L){
   if(L->length > 0){
      L->index = 0;
      L->cursor = L->front;
   }
}

void moveBack(List L){
   if(L->length > 0){
      L->index = L->length - 1;
      L->cursor = L->back;
   }
}

void movePrev(List L){
   if(L->cursor != NULL){
      if(L->cursor != L->front){
         L->index -= 1;
         L->cursor = L->cursor->previous;
      }else{
         L->cursor = NULL;
         L->index = -1;
      }
   }
}

void moveNext(List L){
   if(L->cursor != NULL){
      if(L->cursor != L->back){
         L->index += 1;
         L->cursor = L->cursor->next;
      }else{
         L->cursor = NULL;
         L->index = -1;
      }
   }
}

void prepend(List L, int x){
   Node X = newNode(x);
   if(L->length > 0){
      X->next = L->front;
      L->front->previous = X;
      L->front = X;
      if(L->index != -1){
         L->index += 1;
      }
   }else{
      L->front = L->back = X;
   }
   L->length += 1;
}

void append(List L, int x){
   Node X = newNode(x);
   if(L->length > 0){
      X->previous = L->back;
      L->back->next = X;
      L->back = X;
   }else{
      L->front = L->back = X;
   }
   L->length += 1;
}

void insertBefore(List L, int x){
   if(L->cursor == L->front){
      prepend(L, x);
      return;
   }
   Node X = newNode(x);
   Node node_before_cursor = L->cursor->previous;
   X->next = L->cursor;
   X->previous = node_before_cursor;
   L->cursor->previous = X;
   node_before_cursor->next = X;
   L->length += 1;
   L->index += 1;
}

void insertAfter(List L, int x){
   if(L->cursor == L->back){
      append(L, x);
      return;
   }
   Node X = newNode(x);
   Node node_after_cursor = L->cursor->next;
   X->previous = L->cursor;
   X->next = node_after_cursor;
   L->cursor->next = X;
   node_after_cursor->previous = X;
   L->length += 1;
}

void deleteFront(List L){
   if(L->length == 1){
      clear(L);
      return;
   }
   if(index(L) >= 0){
      L->index -= 1;
   }
   if(L->cursor == L->front){
      L->cursor = NULL;
   }
   Node oldFront = L->front;
   L->front = oldFront->next;
   freeNode(&oldFront);
   L->length -= 1;
}

void deleteBack(List L){
   if(L->length == 1){
      clear(L);
      return;
   }
   if(L->cursor == L->back){
      L->cursor = NULL;
      L->index = -1;
   }
   Node back = L->back;
   L->back = NULL;
   L->back = back->previous;
   freeNode(&back);
   L->length -= 1;
}


void delete(List L){
   if(L->cursor == L->front){
      deleteFront(L);
      return;
   }
   if(L->cursor == L->back){
      deleteBack(L);
      return;
   }
   Node cursor = L->cursor;
   Node node_before_cursor = cursor->previous;
   Node node_after_cursor = cursor->next;
   if(node_before_cursor) node_before_cursor->next = node_after_cursor;
   if(node_after_cursor) node_after_cursor->previous = node_before_cursor;
   L->cursor = NULL;
   L->index = -1;
   freeNode(&cursor);
   L->length -= 1;
}

List copyList(List L){
   List new_L = newList();
   int index_L = index(L); // Record origin index of L
   moveFront(L);
   while(index(L) >= 0){
      int x = get(L);
      append(new_L, x);
      moveNext(L);
   }
   moveFront(L);  // Recovery the index of L to origin index
   while (index(L) != index_L)
   {
      moveNext(L);
   }
   return new_L;
}

List concatList(List A, List B){

   List L = newList();
   moveFront(A);
   while(index(A) >= 0){
      int x = get(A);
      append(L, x);
      moveNext(A);
   }
   moveFront(B);
   while(index(B) >= 0){
      int x = get(B);
      append(B, x);
      moveNext(B);
   }
   return(L);
}

void printList(FILE* output, List L){
   moveFront(L);
   while(index(L) >= 0){
      int x = get(L);
      fprintf(output, "%d ", x);
      moveNext(L);
   }
   // fprintf(output, "\n");
}
