#include "../include/map.h"
#include "../include/hash.h"
#include "../include/node.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

static void MapRehash(Map *map)
{
    Entry *new_table = (Entry *)calloc(map->capacity, sizeof(Entry));
    size_t size = 0;

    for (size_t i = 0; i < map->capacity; i++)
    {
        if (map->table[i].status == OCCUPIED)
        {
            Node *node = map->table[i].node;
            uint32_t hash = Hash(node->key);
            uint32_t index = hash & (map->capacity - 1);

            while (new_table[index].status == OCCUPIED)
            {
                index = (index + 1) & (map->capacity - 1);
            }

            new_table[index].node = node;
            new_table[index].status = OCCUPIED;
            size++;
        }
    }

    free(map->table);
    map->table = new_table;
    map->tombstones = 0;
    map->size = size;
}

Map *NewMap(size_t capacity)
{
    Map *new_map = (Map *)malloc(sizeof(Map));
    if (new_map == NULL)
    {
        return NULL;
    }

    new_map->capacity = capacity;
    new_map->size = 0;
    new_map->tombstones = 0;

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

    if (map == NULL || key == NULL || node == NULL)
    {
        return 0;
    }

    if (map->size >= map->capacity)
    {
        return 0;
    }

    if ((map->size + map->tombstones) > (map->capacity * MAP_MAX_LOAD_FACTOR))
    {
        MapRehash(map);
    }

    uint32_t hash = Hash(key);
    uint32_t index = hash & (map->capacity - 1);
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
                return result;
            }
        }

        index = (index + 1) & (map->capacity - 1);
    }

    if (first_deleted_index != -1)
    {
        map->table[first_deleted_index].node = node;
        map->table[first_deleted_index].status = OCCUPIED;
        map->size++;
        map->tombstones--;
        return 1;
    }

    return 0;
}

Node *MapGet(Map *map, const char *key)
{
    if (map == NULL || key == NULL)
    {
        return NULL;
    }

    uint32_t hash = Hash(key);
    uint32_t index = hash & (map->capacity - 1);

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

        index = (index + 1) & (map->capacity - 1);
    }

    return NULL;
}

Node *MapDelete(Map *map, const char *key)
{
    if (map == NULL || key == NULL)
    {
        return NULL;
    }

    uint32_t hash = Hash(key);
    uint32_t index = hash & (map->capacity - 1);

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
                map->tombstones++;
                return node;
            }
        }

        index = (index + 1) & (map->capacity - 1);
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
