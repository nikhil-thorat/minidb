#include "map.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../node/node.h"

Map* NewMap(size_t capacity) {
  Map* new_map = (Map*)malloc(sizeof(Map));
  if (new_map == NULL) return NULL;

  new_map->capacity = capacity;
  new_map->size = 0;

  new_map->table = (Node**)calloc(capacity, sizeof(Node*));
  if (new_map->table == NULL) {
    free(new_map);
    return NULL;
  }

  return new_map;
}

int MapSet(Map* map, const char* key, uint32_t hash, Node* node) {
  if (map == NULL || key == NULL || node == NULL) return 0;

  if (map->size >= map->capacity) return 0;

  uint32_t mask = (uint32_t)(map->capacity - 1);
  uint32_t index = hash & mask;

  for (size_t i = 0; i < map->capacity; i++) {
    Node* slot = map->table[index];

    if (SLOT_IS_EMPTY(slot)) {
      map->table[index] = node;
      node->hash = hash;
      map->size++;

      return 1;
    }

    if (slot->hash == hash && strcmp(slot->key, key) == 0) {
      return UpdateNodeValue(slot, node->value);
    }

    index = (index + 1) & mask;
  }

  return 0;
}

Node* MapGet(Map* map, const char* key, uint32_t hash) {
  if (map == NULL || key == NULL) return NULL;

  uint32_t mask = (uint32_t)(map->capacity - 1);
  uint32_t index = hash & mask;

  for (size_t i = 0; i < map->capacity; i++) {
    Node* slot = map->table[index];

    if (SLOT_IS_EMPTY(slot)) return NULL;

    if (slot->hash == hash && strcmp(slot->key, key) == 0) return slot;

    index = (index + 1) & mask;
  }

  return NULL;
}

Node* MapDelete(Map* map, const char* key, uint32_t hash) {
  if (map == NULL || key == NULL) return NULL;

  uint32_t mask = (uint32_t)(map->capacity - 1);
  uint32_t index = hash & mask;

  for (size_t i = 0; i < map->capacity; i++) {
    Node* slot = map->table[index];

    if (SLOT_IS_EMPTY(slot)) return NULL;

    if (slot->hash == hash && strcmp(slot->key, key) == 0) {
      Node* deleted = slot;

      uint32_t hole = index;
      uint32_t j = index;

      map->table[hole] = SLOT_EMPTY;

      for (size_t n = 0; n < map->capacity; n++) {
        j = (j + 1) & mask;
        Node* entry = map->table[j];
        if (SLOT_IS_EMPTY(entry)) break;

        uint32_t home = entry->hash & mask;
        int move = (j > hole) ? (home <= hole || home > j)
                              : (home <= hole && home > j);

        if (move) {
          map->table[hole] = entry;
          hole = j;
        }
      }

      map->table[hole] = SLOT_EMPTY;
      map->size--;

      return deleted;
    }

    index = (index + 1) & mask;
  }

  return NULL;
}

void DestroyMap(Map* map) {
  if (map == NULL) return;

  free(map->table);
  free(map);
}
