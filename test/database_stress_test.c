#include "../include/database.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static inline void fast_itoa(int val, char *buf)
{
    if (val == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return;
    }
    char temp[20];
    int i = 0;
    while (val > 0)
    {
        temp[i++] = (val % 10) + '0';
        val /= 10;
    }
    int j = 0;
    while (i > 0)
    {
        buf[j++] = temp[--i];
    }
    buf[j] = '\0';
}

void stress_test()
{
    Database *db = NewDatabase(16, 65536);
    if (db == NULL)
    {
        printf("Failed to allocate Database!\n");
        return;
    }

    char key[32];
    char value[] = "Stress test database value";
    clock_t start, end;
    double time_spent;
    int ops;

    ops = 50000000;
    printf("Inserting %d keys...\n", ops);

    start = clock();
    for (int i = 0; i < ops; i++)
    {
        fast_itoa(i, key);
        DatabaseSet(db, key, value);
    }
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    puts("Insertion Completed : OK!");
    printf("Time: %.3f seconds | Speed: %.0f OPS\n\n", time_spent, ops / time_spent);

    ops = 50000000;
    printf("Querying %d keys...\n", ops);

    int cache_hits = 0;
    start = clock();
    for (int i = 49000000; i < 99000000; i++)
    {
        fast_itoa(i, key);
        char *result = DatabaseGet(db, key);
        if (result != NULL)
        {
            cache_hits++;
            assert(strcmp(result, value) == 0);
        }
    }
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    puts("Querying Completed : OK!");
    printf("Time: %.3f seconds | Speed: %.0f OPS\n", time_spent, ops / time_spent);
    printf("(Cache Hits: %d)\n\n", cache_hits);

    ops = 20000000;
    printf("Real world test : %d random operations\n", ops);

    start = clock();
    for (int i = 0; i < ops; i++)
    {
        fast_itoa(i, key);
        int action = i % 10;

        if (action < 7)
        {
            DatabaseGet(db, key);
        }
        else if (action < 9)
        {
            DatabaseSet(db, key, value);
        }
        else
        {
            DatabaseDelete(db, key);
        }
    }
    end = clock();

    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    puts("Real-world test Completed : OK!");
    printf("Done! Time: %.3f seconds | Speed: %.0f OPS\n", time_spent, ops / time_spent);

    DestroyDatabase(db);
}

int main()
{
    stress_test();
    return 0;
}
