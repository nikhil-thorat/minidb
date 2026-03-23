#include "../include/shard.h"
#include "../include/node.h"

Shard *NewShard(size_t capacity)
{
    Shard *shard = (Shard *)malloc(sizeof(Shard));
    if (shard == NULL)
    {
        free(shard);
        return NULL;
    }

    Map *map = NewMap(capacity);
    List *list = NewList();

    if (map == NULL || list == NULL)
    {
        if (map != NULL)
        {
            free(map);
        }
        if (list != NULL)
        {
            free(list);
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
    if (shard == NULL || key == NULL || value == NULL)
    {
        return 0;
    }

    if (shard->map == NULL || shard->list == NULL)
    {
        return 0;
    }

    if (shard->size == shard->capacity)
    {
        Node *deleted_node = ListRemoveTail(shard->list);
        deleted_node = MapDelete(shard->map, deleted_node->key);
        if (deleted_node != NULL)
        {
            free(deleted_node);
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
    shard->size--;
    return 1;
}

void DestroyShard(Shard *shard)
{
    DestroyMap(shard->map);
    DestroyList(shard->list);
    free(shard->map);
    free(shard->list);
    free(shard);
}
