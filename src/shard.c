#include "../include/shard.h"
#include "../include/node.h"
#include <stdio.h>

Shard *NewShard(size_t capacity)
{
    Shard *shard = (Shard *)malloc(sizeof(Shard));
    if (shard == NULL)
    {
        return NULL;
    }

    Map *map = NewMap(capacity * 2);
    List *list = NewList();

    if (map == NULL || list == NULL)
    {
        if (map != NULL)
        {
            DestroyMap(shard->map);
        }
        if (list != NULL)
        {
            DestroyList(shard->list);
        }
        free(shard);
        return NULL;
    }

    shard->capacity = capacity;
    shard->size = 0;
    shard->map = map;
    shard->list = list;

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
        int result = UpdateNodeValue(existing_node, value);
        if (result == 1)
        {
            ListMoveToHead(shard->list, existing_node);
            return 0;
        }
        return 0;
    }

    if (shard->size >= shard->capacity)
    {
        Node *deleted_node = ListRemoveTail(shard->list);
        deleted_node = MapDelete(shard->map, deleted_node->key);
        if (deleted_node != NULL)
        {
            FreeNode(deleted_node);
            shard->size--;
        }
    }

    Node *node = NewNode(key, value);
    if (node == NULL)
    {
        return 0;
    }

    int result = MapSet(shard->map, key, node);
    if (result == -1)
    {
        FreeNode(node);
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

    FreeNode(deleted_node);
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
    free(shard);
}
