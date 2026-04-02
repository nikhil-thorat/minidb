#include "../include/cli.h"
#include "../include/database.h"
#include <stdlib.h>

#define NUM_OF_SHARDS 4
#define SHARD_CAPACITY 1024

int main(void)
{
    Database *db = NewDatabase(NUM_OF_SHARDS, SHARD_CAPACITY);
    Cli *cli = NewCli(db);
    Run(cli);

    DestroyDatabase(db);
    free(cli);

    return EXIT_SUCCESS;
}
