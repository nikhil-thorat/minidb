#ifndef MAP_H
#define MAP_H

#include "entry.h"
#include <stdlib.h>

#define MAP_MAX_LOAD_FACTOR 0.75

typedef struct Node Node;

/*
 * Represents Map of entiries, contains capacity of the map,
 * current size of the map and a pointer to an array of Entry struct
 */
typedef struct Map
{
    size_t capacity;
    size_t size;
    size_t tombstones;
    Entry *table;
} Map;

/*
 * Initializes a Map with specified capacity
 * Returns a pointer to the created Map.
 */
Map *NewMap(size_t capacity);

/*
 * Sets the given key and value in the Map.
 * Returns 1 if successfully else 0.
 * */
int MapSet(Map *map, const char *key, Node *node);

/*
 * Returns the Node of the given
 * key from the Map, else returns
 * NULL if key is not found.
 */
Node *MapGet(Map *map, const char *key);

/*
 * Marks the slot of given key as DELETED
 */
Node *MapDelete(Map *map, const char *key);

/*
 * Frees the Maps internal table and the Map itself.
 */
void DestroyMap(Map *map);

#endif
