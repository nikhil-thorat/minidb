#include "../src/shard/shard.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../src/hash/hash.h"

static int SSet(Shard* s, const char* k, const char* v) {
  return ShardSet(s, k, Hash(k), v);
}
static char* SGet(Shard* s, const char* k) { return ShardGet(s, k, Hash(k)); }
static int SDel(Shard* s, const char* k) { return ShardDelete(s, k, Hash(k)); }

void test_million_keys() {
  size_t capacity = 1024;
  Shard* shard = NewShard(capacity);
  assert(shard != NULL);
  assert(shard->size == 0);
  assert(shard->capacity == capacity);

  int total_operations = 1e6;
  char value[] = "million_test_value";

  for (int i = 0; i < total_operations; i++) {
    char key[20];
    snprintf(key, sizeof(key), "%d", i);

    int result = SSet(shard, key, value);
    assert(result == 1);
  }

  assert(shard->size == capacity);
  assert(shard->list->size == capacity);

  assert(SGet(shard, "0") == NULL);
  assert(SGet(shard, "500000") == NULL);
  assert(SGet(shard, "998975") == NULL);

  int remaining_keys = total_operations - capacity;
  for (int i = remaining_keys; i < total_operations; i++) {
    char key[20];
    snprintf(key, sizeof(key), "%d", i);

    char* result = SGet(shard, key);
    assert(result != NULL);
    assert(strcmp(result, value) == 0);
  }

  DestroyShard(shard);
  puts("MILLION KEY TEST PASSED : OK!");
}

void test() {
  size_t capacity = 1024;
  Shard* shard = NewShard(capacity);
  assert(shard != NULL);
  assert(shard->size == 0);
  assert(shard->capacity == capacity);

  char value[27] = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < capacity; i++) {
    char key[20];
    snprintf(key, sizeof(key), "%d", i);
    int result = SSet(shard, key, value);
    assert(result == 1);
  }

  assert(shard->size == shard->capacity);

  for (int i = 0; i < capacity; i++) {
    char key[20];
    snprintf(key, sizeof(key), "%d", i);
    char* result = SGet(shard, key);
    assert(strcmp(result, value) == 0);
  }

  for (int i = 0; i < capacity; i++) {
    char key[20];
    snprintf(key, sizeof(key), "%d", i);
    int result = SDel(shard, key);
    assert(result == 1);
  }

  assert(shard->size == 0);

  DestroyShard(shard);
  puts("BASIC SHARD TEST PASSED : OK!");
}

int main() {
  test();
  test_million_keys();
  return 0;
}
