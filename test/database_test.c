#include "../include/database.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void test_distribution()
{
    size_t num_shards = 4;
    size_t shard_capacity = 1024;
    Database *db = NewDatabase(num_shards, shard_capacity);
    assert(db != NULL);

    char value[] = "distributed data value";
    int total_operations = 4000;

    for (int i = 0; i < total_operations; i++)
    {
        char key[20];
        snprintf(key, sizeof(key), "%d", i);
        int result = DatabaseSet(db, key, value);
        assert(result == 1);
    }

    size_t total_size = 0;
    for (size_t i = 0; i < db->num_shards; i++)
    {
        size_t shard_size = db->shards[i]->size;
        printf("Shard %zu holds %zu keys.\n", i, shard_size);

        assert(shard_size > 0);
        assert(shard_size <= shard_capacity);
        total_size += shard_size;
    }

    printf("Database total size : %zu\n", total_size);
    DestroyDatabase(db);
    puts("DATABASE KEY DISTRIBUTION TEST PASSED : OK!");
};

void test()
{
    Database *db = NewDatabase(4, 1024);
    assert(db != NULL);

    DatabaseSet(db, "username", "butterscotch");
    DatabaseSet(db, "hostname", "archlinux");

    char *value = DatabaseGet(db, "username");
    assert(value != NULL);
    assert(strcmp(value, "butterscotch") == 0);

    value = DatabaseGet(db, "hostname");
    assert(value != NULL);
    assert(strcmp(value, "archlinux") == 0);

    int result = DatabaseSet(db, "username", "localhost42069");
    assert(result == 1);

    value = DatabaseGet(db, "username");
    assert(value != NULL);
    assert(strcmp(value, "localhost42069") == 0);

    result = DatabaseDelete(db, "username");
    assert(result == 1);

    value = DatabaseGet(db, "username");
    assert(value == NULL);

    value = DatabaseGet(db, "unknown");
    assert(value == NULL);

    DestroyDatabase(db);
    puts("DATABASE OPERATIONS TEST PASSED : OK!");
};

int main()
{
    test();
    test_distribution();
    return 0;
}
