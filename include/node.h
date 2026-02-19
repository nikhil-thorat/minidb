#ifndef NODE_H
#define NODE_H

/*
  Represents a single Node, which contains
  key and value and pointers to previous and
  next node.
*/
typedef struct Node
{
    char *key;
    char *value;
    struct Node *prev_node;
    struct Node *next_node;
} Node;

/*
  Creates a new Node with given key and value
  and returns a pointer to it.
*/
Node *NewNode(const char *key, const char *value);

/*
  Free's the memory occupied by the Node
*/
void FreeNode(Node *node);

#endif
