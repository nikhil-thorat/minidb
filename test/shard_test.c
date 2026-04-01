#include "../include/shard.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void test_million_keys()
{
    size_t capacity = 1024;
    Shard *shard = NewShard(capacity);
    assert(shard != NULL);
    assert(shard->size == 0);
    assert(shard->capacity == capacity);

    int total_operations = 10000000;
    char value[] = "million_test_value";

    for (int i = 0; i < total_operations; i++)
    {
        char key[20];
        snprintf(key, sizeof(key), "%d", i);

        int result = ShardSet(shard, key, value);
        assert(result == 1);
    }

    assert(shard->size == capacity);
    assert(shard->list->size == capacity);

    assert(ShardGet(shard, "0") == NULL);
    assert(ShardGet(shard, "500000") == NULL);
    assert(ShardGet(shard, "998975") == NULL);

    int remaining_keys = total_operations - capacity;
    for (int i = remaining_keys; i < total_operations; i++)
    {
        char key[20];
        snprintf(key, sizeof(key), "%d", i);

        char *result = ShardGet(shard, key);
        assert(result != NULL);
        assert(strcmp(result, value) == 0);
    }

    DestroyShard(shard);
    printf("MILLION KEY TEST PASSED\n");
}

void test()
{
    size_t capacity = 1024;
    Shard *shard = NewShard(capacity);
    assert(shard != NULL);
    assert(shard->size == 0);
    assert(shard->capacity == capacity);

    char value[27] = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < capacity; i++)
    {
        char key[20];
        snprintf(key, sizeof(key), "%d", i);
        int result = ShardSet(shard, key, value);
        assert(result == 1);
    }

    assert(shard->size == shard->capacity);

    for (int i = 0; i < capacity; i++)
    {
        char key[20];
        snprintf(key, sizeof(key), "%d", i);
        char *result = ShardGet(shard, key);
        assert(strcmp(result, value) == 0);
    }

    for (int i = 0; i < capacity; i++)
    {
        char key[20];
        snprintf(key, sizeof(key), "%d", i);
        int result = ShardDelete(shard, key);
        assert(result == 1);
    }

    assert(shard->size == 0);

    DestroyShard(shard);
    printf("ALL TEST PASSED\n");
}

int main()
{
    test();
    test_million_keys();
    return 0;
}
