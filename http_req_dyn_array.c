#include "http_req_dyn_array.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

static struct http_header_node *
http_header_node_reallocate(struct http_header_node *oldPtr, size_t size);

void http_header_node_push(struct http_header_dyn_arr *array, char *header,
                          const char *value);

struct http_header_dyn_arr *http_header_dyn_arr_init() {
  struct http_header_dyn_arr *array =
      malloc(sizeof(struct http_header_dyn_arr));
  array->occupied = 0;
  array->capacity = 10;
  array->array = http_header_node_reallocate(NULL, 10);
  return array;
}

static struct http_header_node *
http_header_node_reallocate(struct http_header_node *oldPtr, size_t count) {
  if (oldPtr == NULL) {
    return malloc(sizeof(struct http_header_node[count]));
  }
  return realloc(oldPtr, sizeof(struct http_header_node[count]));
}

void http_header_node_push(struct http_header_dyn_arr *array, char *header,
                          const char *value) {
  // greater than equal to not used here, positive micro optimisation as some
  // computers implement jge as a combination of jg and je (maybe a myth, FIXME)
  if (array->occupied + 1 == array->capacity) {
    array->array =
      http_header_node_reallocate(array->array, 2 * array->capacity);
  }
  struct http_header_node *new_node = &(array->array[array->occupied]);
  new_node->key = header;
  new_node->value = value;

  array->occupied += 1;
  return ;
};


const char *http_header_get_value(struct http_header_dyn_arr *array, char *header) {
  for (size_t i = 0; i < array->occupied; i++) {
    if (strcmp((array->array)[i].key, header) == 0) // we have a match
      return (array->array)[i].value;
  }
  return NULL;
};
