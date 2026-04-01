#include "../include/map.h"
#include "../include/node.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * MurmurHash3 (32-bit)
 * Extremely fast, excellent collision resistance.
 * Processes 4 bytes at a time instead of 1 byte.
 */
static uint32_t HashString(const char *key)
{
    int len = strlen(key);
    const uint8_t *data = (const uint8_t *)key;

    uint32_t h1 = 0x9747b28c;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *)(data);

    for (int i = 0; i < nblocks; i++)
    {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> (32 - 13));
        h1 = h1 * 5 + 0xe6546b64;
    }

    const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3)
    {
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0];
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;
        h1 ^= k1;
    }

    h1 ^= len;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
}

/*
 * FNV-1a Hashing algorithm
 */
// static uint32_t HashString(const char *key)
// {
//     uint32_t hash = 2166136261u;
//     for (int i = 0; key[i] != '\0'; i++)
//     {
//         hash ^= (uint8_t)key[i];
//         hash *= 16777619;
//     }
//     return hash;
// }

Map *NewMap(size_t capacity)
{
    Map *new_map = (Map *)malloc(sizeof(Map));
    if (new_map == NULL)
    {
        return NULL;
    }

    new_map->capacity = capacity;
    new_map->size = 0;

    new_map->table = (Entry *)calloc(capacity, sizeof(Entry));
    if (new_map->table == NULL)
    {
        free(new_map);
        return NULL;
    }

    return new_map;
}

int MapSet(Map *map, const char *key, Node *node)
{
    if (map->size >= map->capacity)
    {
        return -1;
    }

    uint32_t index = HashString(key) % map->capacity;
    int first_deleted_index = -1;

    for (size_t i = 0; i < map->capacity; i++)
    {
        Entry *slot = &map->table[index];
        if (slot->status == EMPTY)
        {
            int target_index;
            if (first_deleted_index != -1)
            {
                target_index = first_deleted_index;
            }
            else
            {
                target_index = index;
            }

            map->table[target_index].node = node;
            map->table[target_index].status = OCCUPIED;
            map->size++;
            return 1;
        }
        else if (slot->status == DELETED)
        {
            if (first_deleted_index == -1)
            {
                first_deleted_index = index;
            }
        }
        else if (slot->status == OCCUPIED)
        {
            Node *existing_node = slot->node;
            if (strcmp(existing_node->key, key) == 0)
            {
                int result = UpdateNodeValue(existing_node, node->value);
                if (result == 1)
                {
                    FreeNode(node);
                    return 0;
                }
                else
                {
                    FreeNode(node);
                    return -1;
                }
            }
        }

        index = (index + 1) % map->capacity;
    }

    if (first_deleted_index != -1)
    {
        map->table[first_deleted_index].node = node;
        map->table[first_deleted_index].status = OCCUPIED;
        map->size++;
        return 1;
    }

    return -1;
}

Node *MapGet(Map *map, const char *key)
{

    uint32_t index = HashString(key) % map->capacity;

    for (size_t i = 0; i < map->capacity; i++)
    {
        Entry *slot = &map->table[index];

        if (slot->status == EMPTY)
        {
            return NULL;
        }
        else if (slot->status == OCCUPIED)
        {
            Node *node = slot->node;
            if (strcmp(node->key, key) == 0)
            {
                return node;
            }
        }

        index = (index + 1) % map->capacity;
    }

    return NULL;
}

Node *MapDelete(Map *map, const char *key)
{
    uint32_t index = HashString(key) % map->capacity;

    for (size_t i = 0; i < map->capacity; i++)
    {
        Entry *slot = &map->table[index];

        if (slot->status == EMPTY)
        {
            return NULL;
        }
        else if (slot->status == OCCUPIED)
        {
            Node *node = slot->node;
            if (strcmp(node->key, key) == 0)
            {
                slot->status = DELETED;
                map->size--;
                return node;
            }
        }

        index = (index + 1) % map->capacity;
    }
    return NULL;
}

void DestroyMap(Map *map)
{
    if (map == NULL)
    {
        return;
    }

    free(map->table);
    free(map);
}
