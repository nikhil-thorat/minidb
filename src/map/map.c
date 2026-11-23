#include "map.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../node/node.h"

static void MapRehash(Map* map) {
  Node** new_table = (Node**)calloc(map->capacity, sizeof(Node*));
  size_t size = 0;

  for (size_t i = 0; i < map->capacity; i++) {
    Node* node = map->table[i];
    if (!SLOT_IS_OCCUPIED(node)) continue;

    uint32_t hash = node->hash;
    uint32_t index = hash & (map->capacity - 1);

    while (SLOT_IS_OCCUPIED(new_table[index])) {
      index = (index + 1) & (map->capacity - 1);
    }

    new_table[index] = node;

    size++;
  }

  free(map->table);
  map->table = new_table;
  map->tombstones = 0;
  map->size = size;
}

Map* NewMap(size_t capacity) {
  Map* new_map = (Map*)malloc(sizeof(Map));
  if (new_map == NULL) return NULL;

  new_map->capacity = capacity;
  new_map->size = 0;
  new_map->tombstones = 0;

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

  if ((map->size + map->tombstones) > (map->capacity * MAP_MAX_LOAD_FACTOR)) {
    MapRehash(map);
  }

  Node** table = map->table;
  uint32_t index = hash & (map->capacity - 1);
  int first_deleted_index = -1;

  for (size_t i = 0; i < map->capacity; i++) {
    Node* slot = table[index];
    if (SLOT_IS_EMPTY(slot)) {
      int target_index;

      if (first_deleted_index != -1) {
        target_index = first_deleted_index;
      } else {
        target_index = index;
      }

      table[target_index] = node;
      node->hash = hash;
      map->size++;

      return 1;
    } else if (SLOT_IS_DELETED(slot)) {
      if (first_deleted_index == -1) first_deleted_index = index;
    } else {
      if (slot->hash == hash && strcmp(slot->key, key) == 0) {
        int result = UpdateNodeValue(slot, node->value);
        return result;
      }
    }

    index = (index + 1) & (map->capacity - 1);
  }

  if (first_deleted_index != -1) {
    table[first_deleted_index] = node;
    node->hash = hash;
    map->size++;
    map->tombstones--;

    return 1;
  }

  return 0;
}

Node* MapGet(Map* map, const char* key, uint32_t hash) {
  if (map == NULL || key == NULL) return NULL;

  uint32_t index = hash & (map->capacity - 1);

  for (size_t i = 0; i < map->capacity; i++) {
    Node* slot = map->table[index];

    if (SLOT_IS_EMPTY(slot)) {
      return NULL;
    } else if (SLOT_IS_OCCUPIED(slot)) {
      if (slot->hash == hash && strcmp(slot->key, key) == 0) return slot;
    }

    index = (index + 1) & (map->capacity - 1);
  }

  return NULL;
}

Node* MapDelete(Map* map, const char* key, uint32_t hash) {
  if (map == NULL || key == NULL) return NULL;

  uint32_t index = hash & (map->capacity - 1);

  for (size_t i = 0; i < map->capacity; i++) {
    Node* slot = map->table[index];

    if (SLOT_IS_EMPTY(slot)) {
      return NULL;
    } else if (SLOT_IS_OCCUPIED(slot)) {
      if (slot->hash == hash && strcmp(slot->key, key) == 0) {
        map->table[index] = SLOT_DELETED;
        map->size--;
        map->tombstones++;

        return slot;
      }
    }

    index = (index + 1) & (map->capacity - 1);
  }
  return NULL;
}

void DestroyMap(Map* map) {
  if (map == NULL) return;

  free(map->table);
  free(map);
}
