#ifndef ENTRY_H
#define ENTRY_H

#include "node.h"

/*
  Represents the Slot status of the Entry
  EMPTY = 0
  OCCUPIED = 1
  DELETED = 2
 */
typedef enum
{
    EMPTY,
    OCCUPIED,
    DELETED,
} SlotStatus;

/*
  Represents the Entry in the map
  Contains key, pointer to the Node and status of the slot
 */
typedef struct Entry
{
    char *key;
    Node *node;
    SlotStatus status;
} Entry;

/*
  Initializes Entry for the Map
*/
void InitEntry(Entry *entry);

/*
  Free's the memory occupied by the Entry
*/
void FreeEntry(Entry *entry);

#endif
