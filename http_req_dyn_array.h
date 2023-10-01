#ifndef _HTTP_REQ_LINKED_LIST_H
#define _HTTP_REQ_LINKED_LIST_H


/* MAKE THIS SHIT ALLOCATOR AWARE */
/* (probably by adding two function pointers into the linked list, */
/* for allocation and deallocation) */

#include <stddef.h>
#include <stdlib.h>
struct http_header_node {
  const char *key;
  const char *value;
};

struct http_header_dyn_arr {
  struct http_header_node *array;
  size_t occupied;
  size_t capacity;
};

struct http_header_dyn_arr *http_header_dyn_arr_init();

void http_header_node_push(struct http_header_dyn_arr *array, char *header,
			   const char *value) ;
const char *http_header_get_value(struct http_header_dyn_arr *array, char *header);
#endif
