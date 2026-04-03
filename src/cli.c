#include "../include/cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SET "set"
#define GET "get"
#define DEL "del"
#define HELP "help"
#define CLEAR "clear"
#define CLS "cls"
#define EXIT "exit"
#define QUIT "quit"
#define STATUS "status"
#define PERFORMANCE "performance"

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

void print_banner(void)
{
    puts("███╗███╗   ███╗██╗███╗   ██╗██╗██████╗ ██████╗ ███╗");
    puts("██╔╝████╗ ████║██║████╗  ██║██║██╔══██╗██╔══██╗╚██║");
    puts("██║ ██╔████╔██║██║██╔██╗ ██║██║██║  ██║██████╔╝ ██║");
    puts("██║ ██║╚██╔╝██║██║██║╚██╗██║██║██║  ██║██╔══██╗ ██║");
    puts("███╗██║ ╚═╝ ██║██║██║ ╚████║██║██████╔╝██████╔╝███║");
    puts("╚══╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═════╝ ╚═════╝ ╚══╝");
    puts("");
    puts("Type 'help' for commands or 'exit' to quit!");
    puts("");
}

void print_help(void)
{
    puts("");
    puts("Avaliable Commands : ");
    puts("set key value          : Store a key-value pair");
    puts("get key                : Retrieve a value by key");
    puts("del value              : Delete a key-value pair");
    puts("status                 : Check the database health and capacity");
    puts("performance            : Check the database performance");
    puts("clear or cls           : Clear the terminal screen");
    puts("exit or quit           : Quit the program");
    puts("");
}

void clear_screen(void)
{
    system("clear");
    print_banner();
}

void check_db_status(Database *db)
{
    puts("");
    puts("Checking Database Status");

    printf("Shard Count : %zu\n", db->num_shards);
    printf("Shard Capacity : %zu\n", db->shards[0]->capacity);

    int total_keys = 0;
    for (size_t i = 0; i < db->num_shards; i++)
    {
        total_keys += db->shards[i]->size;
    }
    printf("Total key-value pairs : %d\n", total_keys);
    for (size_t i = 0; i < db->num_shards; i++)
    {
        printf("Shard %zu contains %zu key-value pairs\n", i + 1, db->shards[i]->size);
    }
    puts("");
}

void run_performance_test(void)
{
    puts("");
    puts("Starting Performance Test...");

    Database *test_db = NewDatabase(16, 65536);

    char key[32];
    char value[] = "performance test value";

    puts("Testing Insertion Performance");
    clock_t start = clock();
    int operations = 50000000;
    for (int i = 0; i < operations; i++)
    {
        fast_itoa(i, key);
        DatabaseSet(test_db, key, value);
    }

    clock_t insert_time = clock();
    double time_spent = (double)(insert_time - start) / CLOCKS_PER_SEC;

    puts("Insertion Test Completed : OK!");
    printf("Time Taken : %.3f seconds for %d operations\n", time_spent, operations);
    printf("Operations Speed : %.0f operations per second\n", operations / time_spent);
    puts("");

    puts("Testing Querying Performance");
    int cache_hits = 0;

    start = clock();
    for (int i = 49000000; i < 99000000; i++)
    {
        fast_itoa(i, key);
        char *result = DatabaseGet(test_db, key);
        if (result != NULL)
        {
            cache_hits++;
        }
    }

    clock_t query_time = clock();
    time_spent = (double)(query_time - start) / CLOCKS_PER_SEC;

    puts("Querying Test Completed : OK!");
    printf("Time Taken : %.3f seconds for %d operations\n", time_spent, operations);
    printf("Operations Speed : %.0f operations per second\n", operations / time_spent);
    printf("(Cache Hits: %d)\n", cache_hits);
    puts("");

    puts("Testing Real-world Performance");
    operations = 20000000;
    start = clock();
    for (int i = 0; i < operations; i++)
    {
        fast_itoa(i, key);
        int action = i % 10;

        if (action < 7)
        {
            DatabaseGet(test_db, key);
        }
        else if (action < 9)
        {
            DatabaseSet(test_db, key, value);
        }
        else
        {
            DatabaseDelete(test_db, key);
        }
    }

    clock_t end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    puts("Performance Test Completed");
    printf("Time Taken : %.3f seconds for %d operations\n", time_spent, operations);
    printf("Operations Speed : %.0f operations per second\n", operations / time_spent);
    puts("");

    DestroyDatabase(test_db);
}

void handle_command(Cli *cli, char *input)
{

    char *saved_ptr;

    char *cmd = strtok_r(input, " \n\r", &saved_ptr);
    if (cmd == NULL)
    {
        return;
    }

    if (strcmp(cmd, EXIT) == 0 || strcmp(cmd, QUIT) == 0)
    {
        puts("Shutting down Database...");
        DestroyDatabase(cli->db);
        free(cli);
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(cmd, HELP) == 0)
    {
        print_help();
    }
    else if (strcmp(cmd, CLEAR) == 0 || strcmp(cmd, CLS) == 0)
    {
        clear_screen();
    }
    else if (strcmp(cmd, PERFORMANCE) == 0)
    {
        run_performance_test();
    }
    else if (strcmp(cmd, STATUS) == 0)
    {
        check_db_status(cli->db);
    }
    else if (strcmp(cmd, SET) == 0)
    {
        char *key = strtok_r(NULL, " \n\r", &saved_ptr);
        char *value = strtok_r(NULL, " \n\r", &saved_ptr);

        if (key == NULL || value == NULL)
        {
            puts("Missing arguments. Usage set <key> <value>");
            return;
        }

        int result = DatabaseSet(cli->db, key, value);
        if (result == 1)
        {
            puts("OK!");
        }
        else
        {
            puts("Failed to set key (Out of Memory?)");
        }
    }
    else if (strcmp(cmd, GET) == 0)
    {
        char *key = strtok_r(NULL, " \n\r", &saved_ptr);
        if (key == NULL)
        {
            puts("Missing key argument. Usage get <key>");
            return;
        }

        char *value = DatabaseGet(cli->db, key);
        if (value != NULL)
        {
            puts(value);
        }
        else
        {
            puts("404!");
        }
    }
    else if (strcmp(cmd, DEL) == 0)
    {
        char *key = strtok_r(NULL, " \n\r", &saved_ptr);
        if (key == NULL)
        {
            puts("Missing key argument. Usage del <key>");
            return;
        }

        int result = DatabaseDelete(cli->db, key);
        if (result == 1)
        {
            puts("OK!");
        }
        else
        {
            puts("404!");
        }
    }
    else
    {
        puts("Unknown command. Type 'help' for options.");
    }
}

Cli *NewCli(Database *db)
{
    Cli *cli = (Cli *)malloc(sizeof(Cli));
    if (cli == NULL)
    {
        return NULL;
    }

    cli->db = db;
    return cli;
}

void Run(Cli *cli)
{
    clear_screen();
    char input_buffer[256];

    while (1)
    {
        printf("[MINIDB] ");
        if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
        {
            break;
        }
        handle_command(cli, input_buffer);
    }
}
