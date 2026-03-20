#ifndef DATABASE_H
#define DATABASE_H

#include "list.h"
#include "map.h"
#include <stdlib.h>

/*
  Represents a Database, which uses Map and List for storing data,
  Contains Map for storing key and pointer to the Node in the List
  and max_capacity and current_size.
 */
typedef struct Database
{
    Map *map;
    List *list;
    size_t max_capacity;
    size_t current_size;
} Database;

/*
  Initializes a new Database with specified capacity.
  Returns a pointer to the created Database.
 */
Database *NewDatabase(size_t max_capacity);

/*
  Set's the given key and value in the Database.
*/
void Set(Database *db, const char *key, const char *value);

/*
  Return's the value of the given key if it exists
  in the Database.
*/
char *Get(Database *db, const char *key);

/*
  Delete's the key-value from the Database if it exits
  in the Database. Returns 1 if deleted, else 0
*/
int Del(Database *db, const char *key);

/*
  Delete's everything in the Database and free's the memory
  occupied by it.
 */
void DestroyDatabase(Database *db);

#endif
