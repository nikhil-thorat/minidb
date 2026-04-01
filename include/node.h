#ifndef NODE_H
#define NODE_H

/*
 * Defining maximum lengths for key and value.
 */
#define MAX_KEY_LEN 32
#define MAX_VALUE_LEN 64

/*
 * Represents a single Node, which contains
 * key and value and pointers to previous and
 * next node.
 */
typedef struct Node
{
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
    struct Node *prev_node;
    struct Node *next_node;
} Node;

/*
 * Initializes the given node with the given key and value.
 */
void InitializeNode(Node *node, const char *key, const char *value);

/*
 * Updates the value of a give Node. Returns 1 if
 * updates successfully else 0.
 */
int UpdateNodeValue(Node *node, const char *new_value);

#endif
