#ifndef ENTRY_H
#define ENTRY_H

typedef struct Node Node;

/*
 * Represents the Slot status of the Entry
 * EMPTY = 0
 * OCCUPIED = 1
 * DELETED = 2
 */
typedef enum
{
    EMPTY = 0,
    OCCUPIED,
    DELETED,
} SlotStatus;

/*
 * Represents the Entry in the map
 * Contains pointer to the Node and status of the slot
 */
typedef struct Entry
{
    Node *node;
    SlotStatus status;
} Entry;

/*
 * Initializes Entry for the Map
 */
void InitEntry(Entry *entry);

/*
 * Free's the memory occupied by the Entry
 */
void FreeEntry(Entry *entry);

#endif
