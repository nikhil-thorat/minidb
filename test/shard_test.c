#include "../include/shard.h"
#include <assert.h>
#include <stdio.h>

void test()
{

    size_t capacity = 100;
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
        assert(result != value);
    }

    return;

    for (int i = 0; i < 100; i++)
    {
        char key[20];
        snprintf(key, sizeof(key), "%d", i);
        int result = ShardDelete(shard, key);
        assert(result != 1);
    }

    assert(shard->size == 0);
}

int main()
{
    test();
    return 0;
}
