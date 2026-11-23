#ifndef ENTRY_H
#define ENTRY_H

typedef struct Node Node;

/*
 * Slot encoding for the open-addressed table:
 *   NULL   -> EMPTY
 *   other  -> OCCUPIED (live Node pointer)
 *
 * Deletion uses backward-shift reinsertion, so there are no tombstones.
 */
#define SLOT_EMPTY ((Node*)0)

#define SLOT_IS_EMPTY(s) ((s) == SLOT_EMPTY)
#define SLOT_IS_OCCUPIED(s) (!SLOT_IS_EMPTY(s))

#endif  // ENTRY_H
