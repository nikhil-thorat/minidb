#ifndef MAP_H
#define MAP_H

#include "entry.h"
#include <stdlib.h>

/*
    Represents Map of entiries, contains capacity of the map,
    current size of the map and a pointer to an array of Entry struct
*/
typedef struct Map
{
    size_t capacity;
    size_t size;
    Entry *table;
} Map;

/*
    Initializes a Map with specified capacity
    Returns a pointer to the created Map.
*/
Map *NewMap(size_t capacity);

/*
    Find's a Slot for the given key to be inserted
    in the map.
    Returns the Slot number for the key.
*/
int FindSlot(Map *map, const char *key);

#endif
