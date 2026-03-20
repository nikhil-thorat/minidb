#include "../include/node.h"
#include <stdlib.h>
#include <string.h>

Node *NewNode(const char *key, const char *value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    if (node == NULL)
    {
        return NULL;
    }

    node->key = strdup(key);
    node->value = strdup(value);

    node->prev_node = NULL;
    node->next_node = NULL;

    return node;
}

void FreeNode(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    free(node->key);
    free(node->value);
    free(node);
}
