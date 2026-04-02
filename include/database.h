#ifndef DATABASE_H
#define DATABASE_H

#include "shard.h"

/*
 * Represents actual database engine, contains
 * multiple shards for maximum performance.
 */
typedef struct Database
{
    Shard **shards;
    size_t num_shards;
} Database;

/*
 * Initializes a new Database with specified no of shards.
 * Returns a pointer to the created Database.
 */
Database *NewDatabase(size_t num_shards, size_t shard_capacity);

/*
 * Set's the given key and value in the Datbase.
 * Returns 1 if successful, else 0.
 */
int DatabaseSet(Database *db, const char *key, const char *value);

/*
 * Return's the pointer to the value of the given
 * key if it exists in the Database.
 */
char *DatabaseGet(Database *db, const char *key);

/*
 * Delete's the key-value from the Database if it exits
 * in the Database. Returns 1 if deleted, else 0.
 */
int DatabaseDelete(Database *db, const char *key);

/*
 * Delete's everything in the Database and free's the memory
 * occupied by it.
 */
void DestroyDatabase(Database *db);

#endif
