#include "../include/list.h"
#include <assert.h>
#include <stdio.h>

void display_list(List *list)
{
    Node *node = list->head;
    while (node)
    {
        printf("%s = %s", node->key, node->value);
        if (node->next_node != NULL)
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

    Node *node1 = NewNode("foo", "bar");
    AddToHead(list, node1);
    assert(node1 == list->head->next_node);

    Node *node2 = NewNode("bar", "foo");
    AddToHead(list, node2);
    assert(node2 == list->head->next_node);

    display_list(list);

    MoveToHead(list, node1);
    display_list(list);
    assert(node1 == list->head->next_node);

    RemoveTail(list);
    assert(node1 == list->tail->prev_node);
    display_list(list);

    RemoveNode(list, node1);
    display_list(list);
    assert(list->head == list->tail->prev_node);

    DestroyList(list);

    printf("ALL TESET PASSED : OK!\n");
}

int main()
{
    test();
    return 0;
}
