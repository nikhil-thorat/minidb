#ifndef LIST_H
#define LIST_H

#include "../include/node.h"

/*
  Represents a Doubly linked list used for
  solving Eviction problem, contains pointers
  to head and tail Node.
*/
typedef struct List
{
    Node *head;
    Node *tail;
    int count;
} List;

/*
  Creates a new List and returns a poitner to it.
 */
List *NewList();

/*
  Adds the given Node to the front of the List.
*/
void AddToHead(List *list, Node *node);

/*
  Moves the given Node to the front of the List.
 */
void MoveToHead(List *list, Node *node);

/*
  Removes the tail Node from the List, and
  returns the deleted Node.
*/
Node *RemoveTail(List *list);

/*
  Removes the given Node from the List, and
  returns the deleted Node.
*/
Node *RemoveNode(List *list);

#endif
