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

    if (node->key == NULL || node->value == NULL)
    {
        free(node->key);
        free(node->value);
        free(node);
        return NULL;
    }

    node->prev_node = NULL;
    node->next_node = NULL;

    return node;
}

int UpdateNodeValue(Node *node, const char *new_value)
{
    if (node == NULL || new_value == NULL)
    {
        return 0;
    }

    char *temp_value = strdup(new_value);
    if (temp_value == NULL)
    {
        return 0;
    }

    free(node->value);
    node->value = temp_value;

    return 1;
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
