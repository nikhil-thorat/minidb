#ifndef ENTRY_H
#define ENTRY_H

typedef struct Node Node;

/*
 * Slot encoding for the open-addressed table:
 *   NULL      -> EMPTY
 *   (Node*)1  -> DELETED (tombstone)
 *   other     -> OCCUPIED (live Node pointer)
 *
 * Pool Node pointers are at least 8-byte aligned, so they never equal 1.
 */
#define SLOT_EMPTY ((Node*)0)
#define SLOT_DELETED ((Node*)1)

#define SLOT_IS_EMPTY(s) ((s) == SLOT_EMPTY)
#define SLOT_IS_DELETED(s) ((s) == SLOT_DELETED)
#define SLOT_IS_OCCUPIED(s) (!SLOT_IS_EMPTY(s) && !SLOT_IS_DELETED(s))

#endif  // ENTRY_H
