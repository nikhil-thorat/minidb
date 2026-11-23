#include "../node/node.h"

#include <string.h>

void InitializeNode(Node* node, const char* key, const char* value) {
  if (node == NULL || key == NULL || value == NULL) return;

  size_t key_len = strnlen(key, MAX_KEY_LEN - 1);
  memcpy(node->key, key, key_len);
  node->key[key_len] = '\0';

  size_t value_len = strnlen(value, MAX_VALUE_LEN - 1);
  memcpy(node->value, value, value_len);
  node->value[value_len] = '\0';

  node->prev_node = NULL;
  node->next_node = NULL;
}

int UpdateNodeValue(Node* node, const char* new_value) {
  if (node == NULL || new_value == NULL) return 0;

  size_t value_len = strnlen(new_value, MAX_VALUE_LEN - 1);
  memcpy(node->value, new_value, value_len);
  node->value[value_len] = '\0';

  return 1;
}
