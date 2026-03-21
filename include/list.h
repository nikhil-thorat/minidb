#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct Node Node;

/*
 * Represents a Doubly linked list used for
 * solving Eviction problem, contains pointers
 * to head and tail Node.
 */
typedef struct List
{
    Node *head;
    Node *tail;
    size_t count;
} List;

/*
 * Creates a new List.
 * Returns a poitner to the created List.
 */
List *NewList(void);

/*
 * Adds the given Node to the front of the List head.
 */
void ListAddToHead(List *list, Node *node);

/*
 * Moves the given Node to the front of the List.
 */
void ListMoveToHead(List *list, Node *node);

/*
 * Removes the tail Node from the List.
 * Returns a pointer deleted Node.
 */
Node *ListRemoveTail(List *list);

/*
 * Removes the given Node from the List.
 * Returns a pointer deleted Node.
 */
Node *ListRemoveNode(List *list, Node *node);

/*
 * Delete's all the Nodes in the list and
 * Free's the memory occupied by them.
 */
void DestroyList(List *list);

#endif
