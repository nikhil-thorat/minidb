#ifndef SHARD_H
#define SHARD_H

#include "list.h"
#include "map.h"
#include <stdlib.h>

/*
 * Represents a Shard, which uses Map and List for storing data,
 * Contains Map for storing key and pointer to the Node in the List
 * and max_capacity and current_size.
 */
typedef struct Shard
{
    Map *map;
    List *list;
    size_t max_capacity;
    size_t current_size;
} Shard;

/*
 * Initializes a new Shard with specified capacity.
 * Returns a pointer to the created Shard.
 */
Shard *NewShard(size_t max_capacity);

/*
 * Set's the given key and value in the Shard.
 */
void Set(Shard *db, const char *key, const char *value);

/*
 * Return's the value of the given key if it exists
 * in the Shard.
 */
char *Get(Shard *db, const char *key);

/*
 * Delete's the key-value from the Shard if it exits
 * in the Shard. Returns 1 if deleted, else 0
 */
int Del(Shard *db, const char *key);

/*
 * Delete's everything in the Shard and free's the memory
 * occupied by it.
 */
void DestroyShard(Shard *db);

#endif
