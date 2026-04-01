#include "../include/node.h"
#include <string.h>

void InitializeNode(Node *node, const char *key, const char *value)
{
    if (node == NULL)
    {
        return;
    }

    strncpy(node->key, key, MAX_KEY_LEN - 1);
    node->key[MAX_KEY_LEN - 1] = '\0';

    strncpy(node->value, value, MAX_VALUE_LEN - 1);
    node->value[MAX_VALUE_LEN - 1] = '\0';

    node->prev_node = NULL;
    node->next_node = NULL;
}

int UpdateNodeValue(Node *node, const char *new_value)
{
    if (node == NULL || new_value == NULL)
    {
        return 0;
    }

    strncpy(node->value, new_value, MAX_VALUE_LEN - 1);
    node->value[MAX_VALUE_LEN - 1] = '\0';

    return 1;
}
