#include "../include/list.h"
#include "../include/node.h"
#include <stdio.h>
#include <stdlib.h>

static Node *create_dummy_node(void)
{
    Node *dummy_node = (Node *)malloc(sizeof(Node));
    if (dummy_node == NULL)
    {
        return NULL;
    };

    dummy_node->key = NULL;
    dummy_node->value = NULL;
    dummy_node->prev_node = NULL;
    dummy_node->next_node = NULL;

    return dummy_node;
}

static void unlink_node(Node *node)
{
    Node *prev = node->prev_node;
    Node *next = node->next_node;

    prev->next_node = next;
    next->prev_node = prev;

    node->next_node = NULL;
    node->prev_node = NULL;
}

List *NewList(void)
{
    List *list = (List *)malloc(sizeof(List));
    if (list == NULL)
    {
        return NULL;
    };

    list->head = create_dummy_node();
    list->tail = create_dummy_node();

    if (list->head == NULL || list->tail == NULL)
    {
        if (list->head)
            free(list->head);
        if (list->tail)
            free(list->tail);
        free(list);
        return NULL;
    }

    list->head->next_node = list->tail;
    list->tail->prev_node = list->head;
    list->size = 0;

    return list;
}

void ListAddToHead(List *list, Node *node)
{
    if (node == NULL)
    {
        return;
    };

    Node *first_node = list->head->next_node;

    node->prev_node = list->head;
    node->next_node = first_node;

    list->head->next_node = node;
    first_node->prev_node = node;

    list->size++;
}

void ListMoveToHead(List *list, Node *node)
{
    if (node == NULL)
    {
        return;
    };

    unlink_node(node);
    list->size--;

    ListAddToHead(list, node);
}

Node *ListRemoveTail(List *list)
{

    if (list->head->next_node == list->tail)
    {
        return NULL;
    };

    Node *last_node = list->tail->prev_node;

    unlink_node(last_node);
    list->size--;

    return last_node;
}

Node *ListRemoveNode(List *list, Node *node)
{
    if (node == NULL)
    {
        return NULL;
    }

    unlink_node(node);
    list->size--;

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
    };

    free(list);
}
