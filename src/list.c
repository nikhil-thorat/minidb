#include "../include/list.h"
#include <stdlib.h>

static Node *create_dummy_node()
{
    Node *dummy_node = malloc(sizeof(Node));
    if (dummy_node == NULL)
    {
        return NULL;
    }

    dummy_node->key = NULL;
    dummy_node->value = NULL;
    dummy_node->prev_node = NULL;
    dummy_node->next_node = NULL;

    return dummy_node;
};

List *NewList()
{
    List *list = malloc(sizeof(List));
    if (list == NULL)
    {
        return NULL;
    }

    list->head = create_dummy_node();
    list->tail = create_dummy_node();

    list->head->next_node = list->tail;
    list->tail->prev_node = list->head;

    list->count = 0;

    return list;
};

void AddToHead(List *list, Node *node)
{
    if (node == NULL)
    {
        return;
    }

    Node *first_node = list->head->next_node;

    list->head->next_node = node;
    node->prev_node = list->head;

    node->next_node = first_node;
    first_node->prev_node = node;

    list->count++;
}

void MoveToHead(List *list, Node *node)
{
    if (node == NULL)
    {
        return;
    }

    Node *prev_node = node->prev_node;
    Node *next_node = node->next_node;
    prev_node->next_node = next_node;
    next_node->prev_node = prev_node;

    AddToHead(list, node);
}

Node *RemoveTail(List *list)
{

    if (list->head->next_node == list->tail)
    {
        return NULL;
    }

    Node *last_node = list->tail->prev_node;
    Node *prev_to_last = last_node->prev_node;

    list->tail->prev_node = prev_to_last;
    prev_to_last->next_node = list->tail;

    last_node->prev_node = NULL;
    last_node->next_node = NULL;

    list->count--;

    return last_node;
}

Node *RemoveNode(List *list, Node *node)
{
    if (node == NULL)
    {
        return NULL;
    }

    Node *prev_node = node->prev_node;
    Node *next_node = node->next_node;
    next_node->prev_node = prev_node;
    prev_node->next_node = next_node;

    node->prev_node = NULL;
    node->next_node = NULL;

    list->count--;

    return node;
}

void DestroyList(List *list)
{
    Node *current_node = list->head;
    while (current_node != NULL)
    {
        Node *next_node = current_node->next_node;
        FreeNode(current_node);
        current_node = next_node;
    }

    free(list);
}
