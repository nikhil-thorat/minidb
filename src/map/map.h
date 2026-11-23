#ifndef MAP_H
#define MAP_H

#include <stdint.h>
#include <stdlib.h>

#include "entry.h"

#define MAP_MAX_LOAD_FACTOR 0.60

typedef struct Node Node;

/*
 * Represents Map of entries, contains capacity of the map,
 * current size of the map and a pointer to an array of slots.
 * Each slot is a tagged Node pointer.
 */
typedef struct Map {
  size_t capacity;
  size_t size;
  Node** table;
} Map;

/*
 * Initializes a Map with specified capacity
 * Returns a pointer to the created Map.
 */
Map* NewMap(size_t capacity);

/*
 * Sets the given key and value in the Map.
 * Returns 1 if successfully else 0.
 * */
int MapSet(Map* map, const char* key, uint32_t hash, Node* node);

/*
 * Returns the Node of the given
 * key from the Map, else returns
 * NULL if key is not found.
 */
Node* MapGet(Map* map, const char* key, uint32_t hash);

/*
 * Deletes the given key from the Map and closes the probe cluster.
 * Returns the removed Node, or NULL if the key is not found.
 */
Node* MapDelete(Map* map, const char* key, uint32_t hash);

/*
 * Frees the Maps internal table and the Map itself.
 */
void DestroyMap(Map* map);

#endif  // MAP_H
