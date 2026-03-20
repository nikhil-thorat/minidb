#include "../include/map.h"
#include "../include/node.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
 * FNV-1a Hashing algorithm
 */
static uint32_t HashString(const char *key)
{
    uint32_t hash = 2166136261u;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash ^= (uint8_t)key[i];
        hash *= 16777619;
    }
    return hash;
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

    new_map->table = (Entry *)calloc(capacity, sizeof(Entry));
    if (new_map->table == NULL)
    {
        free(new_map);
        return NULL;
    }

    return new_map;
}

int Set(Map *map, const char *key, Node *node)
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
                UpdateNodeValue(existing_node, node->value);
                FreeNode(node);
                return 0;
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

Node *Get(Map *map, const char *key)
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

void Delete(Map *map, const char *key)
{
    uint32_t index = HashString(key) % map->capacity;

    for (size_t i = 0; i < map->capacity; i++)
    {
        Entry *slot = &map->table[index];

        if (slot->status == EMPTY)
        {
            return;
        }
        else if (slot->status == OCCUPIED)
        {
            Node *node = slot->node;
            if (strcmp(node->key, key) == 0)
            {
                slot->status = DELETED;
                map->size--;
                return;
            }
        }

        index = (index + 1) % map->capacity;
    }
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
