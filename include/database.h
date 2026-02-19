#ifndef DATABASE_H
#define DATABASE_H

#include "list.h"
#include "map.h"

/*
  Represents a Database, which used Map and List for storing data,
  Contains Map for sotring key and pointer to the Node in the List
  and max_capacity and current_size.
 */
typedef struct Database
{
    Map *map;
    List *list;
    int max_capacity;
    int current_size;
} Database;

/*
  Initialized a new Database with specified capacity,
  and returns a pointer to the it.
 */
Database *InitDatabase(int max_capacity);

/*
  Set's the given key and value in the Database.
*/
void Set(Database *db, const char *key, const char *value);

/*
  Return's the value of the given key if it exists
  in the database.
*/
char *Get(Database *db, const char *key);

/*
  Delete's the key-value from the Database if it exits
  in the database. Returns 1 if deleted, else 0
*/
int Del(Database *db, const char *key);

/*
  Delete's everything in the Database and free's the memory
  occupied by it.
 */
void DestroyDatabase(Database *db);


#endif
