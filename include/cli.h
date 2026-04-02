#ifndef CLI_H
#define CLI_H

#include "database.h"

typedef struct
{
    Database *db;
} Cli;

void print_banner(void);
void print_help(void);
void clear_screen(void);

void check_db_status(Database *db);
void run_performance_test(void);

void handle_command(Cli *cli, char *input);

Cli *NewCli(Database *db);
void Run(Cli *cli);

#endif
