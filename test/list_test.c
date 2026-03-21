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
    assert(list->size == 0);

    Node *node1 = NewNode("foo", "bar");
    ListAddToHead(list, node1);
    assert(node1 == list->head->next_node);
    assert(list->size == 1);

    Node *node2 = NewNode("bar", "foo");
    ListAddToHead(list, node2);
    assert(node2 == list->head->next_node);
    assert(list->size == 2);

    display_list(list);

    ListMoveToHead(list, node1);
    display_list(list);
    assert(node1 == list->head->next_node);
    assert(list->size == 2);

    Node *removed_tail = ListRemoveTail(list);
    assert(removed_tail == node2);
    assert(list->size == 1);
    display_list(list);
    FreeNode(removed_tail);

    Node *removed_node = ListRemoveNode(list, node1);
    assert(removed_node == node1);
    assert(list->size == 0);
    assert(list->head->next_node == list->tail);
    FreeNode(removed_node);

    Node *empty_tail = ListRemoveTail(list);
    assert(empty_tail == NULL);
    assert(list->size == 0);

    DestroyList(list);

    puts("ALL TESET PASSED : OK!");
}

int main()
{
    test();
    return 0;
}
