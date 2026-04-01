#include "../include/shard.h"
#include "../include/node.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Shard *NewShard(size_t capacity)
{
    Shard *shard = (Shard *)malloc(sizeof(Shard));
    if (shard == NULL)
    {
        return NULL;
    }

    Map *map = NewMap(capacity * 2);
    List *list = NewList();

    Node *pool = (Node *)malloc(sizeof(Node) * capacity);

    if (map == NULL || list == NULL || pool == NULL)
    {
        if (map != NULL)
        {
            DestroyMap(shard->map);
        }
        if (list != NULL)
        {
            DestroyList(shard->list);
        }
        if (pool != NULL)
        {
            free(pool);
        }
        free(shard);
        return NULL;
    }

    shard->capacity = capacity;
    shard->size = 0;
    shard->map = map;
    shard->list = list;
    shard->node_pool = pool;

    for (size_t i = 0; i < capacity; i++)
    {
        pool[i].next_node = &pool[i + 1];
    }
    pool[capacity - 1].next_node = NULL;
    shard->free_list = &pool[0];

    return shard;
}

int ShardSet(Shard *shard, const char *key, const char *value)
{
    if (shard == NULL || key == NULL || value == NULL || key == NULL || value == NULL)
    {
        return 0;
    }

    Node *existing_node = MapGet(shard->map, key);
    if (existing_node != NULL)
    {
        UpdateNodeValue(existing_node, value);
        ListMoveToHead(shard->list, existing_node);
        return 0;
    }

    if (shard->size >= shard->capacity)
    {
        Node *deleted_node = ListRemoveTail(shard->list);
        if (deleted_node != NULL)
        {
            MapDelete(shard->map, deleted_node->key);
            deleted_node->next_node = shard->free_list;
            shard->free_list = deleted_node;
            shard->size--;
        }
    }

    if (shard->free_list == NULL)
    {
        return 0;
    }

    Node *node = shard->free_list;
    shard->free_list = node->next_node;

    InitializeNode(node, key, value);

    int result = MapSet(shard->map, key, node);
    if (result == -1)
    {
        node->next_node = shard->free_list;
        shard->free_list = node;
        return 0;
    }

    ListAddToHead(shard->list, node);
    shard->size++;
    return 1;
}

char *ShardGet(Shard *shard, const char *key)
{
    if (shard == NULL || key == NULL)
    {
        return NULL;
    }

    Node *node = MapGet(shard->map, key);
    if (node == NULL)
    {
        return NULL;
    }

    ListMoveToHead(shard->list, node);
    return node->value;
}

int ShardDelete(Shard *shard, const char *key)
{
    if (shard == NULL || key == NULL)
    {
        return 0;
    }

    Node *deleted_node = MapDelete(shard->map, key);
    if (deleted_node == NULL)
    {
        return 0;
    }

    deleted_node = ListRemoveNode(shard->list, deleted_node);
    if (deleted_node == NULL)
    {
        return 0;
    }

    deleted_node->next_node = shard->free_list;
    shard->free_list = deleted_node;
    shard->size--;
    return 1;
}

void DestroyShard(Shard *shard)
{
    if (shard == NULL)
    {
        return;
    }

    DestroyMap(shard->map);
    DestroyList(shard->list);
    free(shard->node_pool);
    free(shard);
}
