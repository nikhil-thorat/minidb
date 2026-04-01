#include "../include/list.h"
#include "../include/node.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

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
    assert(list->size == 0);

    Node node_pool[5];

    Node *node1 = &node_pool[0];
    InitializeNode(node1, "foo", "bar");

    Node *node2 = &node_pool[1];
    InitializeNode(node2, "bar", "foo");

    ListAddToHead(list, node1);
    assert(node1 == list->head->next_node);
    assert(list->size == 1);

    ListAddToHead(list, node2);
    assert(node2 == list->head->next_node);
    assert(list->size == 2);

    printf("After Adds: ");
    display_list(list);

    ListMoveToHead(list, node1);
    printf("After MoveToHead: ");
    display_list(list);
    assert(node1 == list->head->next_node);
    assert(list->size == 2);

    Node *removed_tail = ListRemoveTail(list);
    assert(removed_tail == node2);
    assert(list->size == 1);

    printf("After RemoveTail: ");
    display_list(list);

    Node *removed_node = ListRemoveNode(list, node1);
    assert(removed_node == node1);
    assert(list->size == 0);
    assert(list->head->next_node == list->tail);

    Node *empty_tail = ListRemoveTail(list);
    assert(empty_tail == NULL);
    assert(list->size == 0);

    DestroyList(list);
    puts("ALL LIST TESTS PASSED : OK!");
}

int main()
{
    test();
    return 0;
}
