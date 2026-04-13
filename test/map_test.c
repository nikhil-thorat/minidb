#include "../include/map.h"
#include "../include/node.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void test()
{
    size_t capacity = 8;
    Map *map = NewMap(capacity);

    assert(map != NULL);
    assert(map->capacity == 8);
    assert(map->size == 0);

    Node node_pool[10];

    Node *nodeA = &node_pool[0];
    InitializeNode(nodeA, "A", "ValueA");
    Node *nodeB = &node_pool[1];
    InitializeNode(nodeB, "B", "ValueB");
    Node *nodeC = &node_pool[2];
    InitializeNode(nodeC, "C", "ValueC");
    Node *nodeD = &node_pool[3];
    InitializeNode(nodeD, "D", "ValueD");
    Node *nodeE = &node_pool[4];
    InitializeNode(nodeE, "E", "ValueE");
    Node *nodeF = &node_pool[5];
    InitializeNode(nodeF, "F", "ValueF");
    Node *nodeG = &node_pool[6];
    InitializeNode(nodeG, "G", "ValueG");
    Node *nodeH = &node_pool[7];
    InitializeNode(nodeH, "H", "ValueH");

    Node *nodeA_updated = &node_pool[8];
    InitializeNode(nodeA_updated, "A", "ValueAUpdated");
    Node *nodeI = &node_pool[9];
    InitializeNode(nodeI, "I", "ValueI");

    int res = MapSet(map, "A", nodeA);
    assert(res == 1);
    assert(map->size == 1);

    Node *found = MapGet(map, "A");
    assert(found == nodeA);
    assert(strcmp(found->value, "ValueA") == 0);

    res = MapSet(map, "A", nodeA_updated);
    assert(res == 1);
    assert(map->size == 1);

    found = MapGet(map, "A");
    assert(found == nodeA);
    assert(strcmp(found->value, "ValueAUpdated") == 0);

    found = MapGet(map, "Z");
    assert(found == NULL);

    MapSet(map, "B", nodeB);
    MapSet(map, "C", nodeC);
    MapSet(map, "D", nodeD);
    MapSet(map, "E", nodeE);
    MapSet(map, "F", nodeF);
    MapSet(map, "G", nodeG);
    MapSet(map, "H", nodeH);
    assert(map->size == 8);

    res = MapSet(map, "I", nodeI);
    assert(res == 0);
    assert(map->size == 8);

    Node *deleted = MapDelete(map, "C");
    assert(deleted == nodeC);
    assert(map->size == 7);

    found = MapGet(map, "C");
    assert(found == NULL);

    found = MapGet(map, "H");
    assert(found == nodeH);

    res = MapSet(map, "I", nodeI);
    assert(res == 1);
    assert(map->size == 8);
    found = MapGet(map, "I");
    assert(found == nodeI);

    DestroyMap(map);
    puts("ALL MAP TESTS PASSED : OK!");
}

int main()
{
    test();
    return 0;
}
