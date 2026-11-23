#include "../src/map/map.h"

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "../src/hash/hash.h"
#include "../src/node/node.h"

static int TSet(Map* m, const char* k, Node* n) {
  return MapSet(m, k, Hash(k), n);
}

static Node* TGet(Map* m, const char* k) { return MapGet(m, k, Hash(k)); }

static Node* TDel(Map* m, const char* k) { return MapDelete(m, k, Hash(k)); }

void test() {
  size_t capacity = 8;
  Map* map = NewMap(capacity);

  assert(map != NULL);
  assert(map->capacity == 8);
  assert(map->size == 0);

  Node node_pool[10];

  Node* nodeA = &node_pool[0];
  InitializeNode(nodeA, "A", "ValueA");
  Node* nodeB = &node_pool[1];
  InitializeNode(nodeB, "B", "ValueB");
  Node* nodeC = &node_pool[2];
  InitializeNode(nodeC, "C", "ValueC");
  Node* nodeD = &node_pool[3];
  InitializeNode(nodeD, "D", "ValueD");
  Node* nodeE = &node_pool[4];
  InitializeNode(nodeE, "E", "ValueE");
  Node* nodeF = &node_pool[5];
  InitializeNode(nodeF, "F", "ValueF");
  Node* nodeG = &node_pool[6];
  InitializeNode(nodeG, "G", "ValueG");
  Node* nodeH = &node_pool[7];
  InitializeNode(nodeH, "H", "ValueH");

  Node* nodeA_updated = &node_pool[8];
  InitializeNode(nodeA_updated, "A", "ValueAUpdated");
  Node* nodeI = &node_pool[9];
  InitializeNode(nodeI, "I", "ValueI");

  int res = TSet(map, "A", nodeA);
  assert(res == 1);
  assert(map->size == 1);

  Node* found = TGet(map, "A");
  assert(found == nodeA);
  assert(strcmp(found->value, "ValueA") == 0);

  res = TSet(map, "A", nodeA_updated);
  assert(res == 1);
  assert(map->size == 1);

  found = TGet(map, "A");
  assert(found == nodeA);
  assert(strcmp(found->value, "ValueAUpdated") == 0);

  found = TGet(map, "Z");
  assert(found == NULL);

  TSet(map, "B", nodeB);
  TSet(map, "C", nodeC);
  TSet(map, "D", nodeD);
  TSet(map, "E", nodeE);
  TSet(map, "F", nodeF);
  TSet(map, "G", nodeG);
  TSet(map, "H", nodeH);
  assert(map->size == 8);

  res = TSet(map, "I", nodeI);
  assert(res == 0);
  assert(map->size == 8);

  Node* deleted = TDel(map, "C");
  assert(deleted == nodeC);
  assert(map->size == 7);

  found = TGet(map, "C");
  assert(found == NULL);

  found = TGet(map, "H");
  assert(found == nodeH);

  res = TSet(map, "I", nodeI);
  assert(res == 1);
  assert(map->size == 8);
  found = TGet(map, "I");
  assert(found == nodeI);

  DestroyMap(map);
  puts("ALL MAP TESTS PASSED : OK!");
}

int main() {
  test();
  return 0;
}
