#ifndef LIST_H
#define LIST_H

#include "node.h"

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
  Creates a new List.
  Returns a poitner to the created List.
 */
List *NewList();

/*
  Adds the given Node to the front of the List head.
*/
void AddToHead(List *list, Node *node);

/*
  Moves the given Node to the front of the List.
 */
void MoveToHead(List *list, Node *node);

/*
  Removes the tail Node from the List.
  Returns a pointer deleted Node.
*/
Node *RemoveTail(List *list);

/*
  Removes the given Node from the List.
  Returns a pointer deleted Node.
*/
Node *RemoveNode(List *list);

#endif
