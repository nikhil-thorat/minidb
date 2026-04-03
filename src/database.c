#include "../include/database.h"
#include "../include/hash.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

static inline Shard *DatabaseGetShard(Database *db, const char *key)
{
    return db->shards[Hash(key) & (db->num_shards - 1)];
}

Database *NewDatabase(size_t num_shards, size_t shard_capacity)
{
    Database *db = (Database *)malloc(sizeof(Database));
    if (db == NULL)
    {
        return NULL;
    }

    db->num_shards = num_shards;

    db->shards = (Shard **)malloc(sizeof(Shard *) * num_shards);
    if (db->shards == NULL)
    {
        free(db);
        return NULL;
    }

    for (size_t i = 0; i < num_shards; i++)
    {
        db->shards[i] = NewShard(shard_capacity);
        if (db->shards[i] == NULL)
        {
            for (size_t j = 0; j < i; j++)
            {
                DestroyShard(db->shards[j]);
            }
            free(db->shards);
            free(db);
            return NULL;
        }
    }

    return db;
}

int DatabaseSet(Database *db, const char *key, const char *value)
{
    if (db == NULL || key == NULL || value == NULL)
    {
        return 0;
    }

    Shard *shard = DatabaseGetShard(db, key);
    return ShardSet(shard, key, value);
}

char *DatabaseGet(Database *db, const char *key)
{

    if (db == NULL || key == NULL)
    {
        return NULL;
    }

    Shard *shard = DatabaseGetShard(db, key);
    return ShardGet(shard, key);
}

int DatabaseDelete(Database *db, const char *key)
{
    if (db == NULL || key == NULL)
    {
        return 0;
    }

    Shard *shard = DatabaseGetShard(db, key);
    return ShardDelete(shard, key);
}

void DestroyDatabase(Database *db)
{
    if (db == NULL)
    {
        return;
    }

    for (size_t i = 0; i < db->num_shards; i++)
    {
        DestroyShard(db->shards[i]);
    }

    free(db->shards);
    free(db);
}
