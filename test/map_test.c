#include "../include/map.h"
#include "../include/node.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void test()
{
    size_t capacity = 5;
    Map *map = NewMap(capacity);

    assert(map != NULL);
    assert(map->capacity == 5);
    assert(map->size == 0);

    Node *nodeA = NewNode("A", "ValueA");
    Node *nodeB = NewNode("B", "ValueB");
    Node *nodeC = NewNode("C", "ValueC");
    Node *nodeD = NewNode("D", "ValueD");
    Node *nodeE = NewNode("E", "ValueE");

    Node *nodeA_updated = NewNode("A", "ValueAUpdated");

    int res = Set(map, "A", nodeA);
    assert(res == 1);
    assert(map->size == 1);

    Node *found = Get(map, "A");
    assert(found == nodeA);
    assert(strcmp(found->value, "ValueA") == 0);

    res = Set(map, "A", nodeA_updated);
    assert(res == 0);
    assert(map->size == 1);

    found = Get(map, "A");
    assert(found == nodeA);
    assert(strcmp(found->value, "ValueAUpdated") == 0);

    found = Get(map, "Z");
    assert(found == NULL);

    Set(map, "B", nodeB);
    Set(map, "C", nodeC);
    Set(map, "D", nodeD);
    Set(map, "E", nodeE);
    assert(map->size == 5);

    Node *nodeF = NewNode("F", "ValueF");
    res = Set(map, "F", nodeF);
    assert(res == -1);
    assert(map->size == 5);

    Delete(map, "C");
    assert(map->size == 4);
    found = Get(map, "C");
    assert(found == NULL);

    found = Get(map, "E");
    assert(found == nodeE);

    res = Set(map, "F", nodeF);
    assert(res == 1);
    assert(map->size == 5);
    found = Get(map, "F");
    assert(found == nodeF);

    DestroyMap(map);
    FreeNode(nodeA);
    FreeNode(nodeB);
    FreeNode(nodeC);
    FreeNode(nodeD);
    FreeNode(nodeE);
    FreeNode(nodeF);

    puts("ALL TESET PASSED : OK!");
}

int main()
{
    test();
    return 0;
}
