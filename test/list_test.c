#include "../include/list.h"
#include "../include/node.h"
#include <assert.h>
#include <stdio.h>

void display_list(List *list)
{
    Node *node = list->head->next_node;
    while (node != list->tail)
    {
        printf("[%s : %s]", node->key, node->value);
        if (node->next_node != list->tail)
        {
            printf(" <=> ");
        }
        node = node->next_node;
    }
    printf("\n");
}

void test()
{
    List *list = NewList();
    assert(list != NULL);
    assert(list->count == 0);

    Node *node1 = NewNode("foo", "bar");
    AddToHead(list, node1);
    assert(node1 == list->head->next_node);
    assert(list->count == 1);

    Node *node2 = NewNode("bar", "foo");
    AddToHead(list, node2);
    assert(node2 == list->head->next_node);
    assert(list->count == 2);

    display_list(list);

    MoveToHead(list, node1);
    display_list(list);
    assert(node1 == list->head->next_node);
    assert(list->count == 2);

    Node *removed_tail = RemoveTail(list);
    assert(removed_tail == node2);
    assert(list->count == 1);
    display_list(list);
    FreeNode(removed_tail);

    Node *removed_node = RemoveNode(list, node1);
    assert(removed_node == node1);
    assert(list->count == 0);
    assert(list->head->next_node == list->tail);
    FreeNode(removed_node);

    Node *empty_tail = RemoveTail(list);
    assert(empty_tail == NULL);
    assert(list->count == 0);

    DestroyList(list);

    printf("ALL TESET PASSED : OK!\n");
}

int main()
{
    test();
    return 0;
}
