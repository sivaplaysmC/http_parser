#ifndef _HTTP_PARSER_H
#define _HTTP_PARSER_H

#include "http_req_dyn_array.h"
#include <stddef.h>
#include <stdio.h>

#define INLINE __attribute__((always_inline)) inline

#define DBG(x) puts(x)

enum HTTP_METHOD : unsigned char {
  METHOD_GET = 'G',
  METHOD_PUT = 'P' + 'U',
  METHOD_POST = 'P' + 'O',
  METHOD_SET = 'S',
  METHOD_DELETE = 'D',
  METHOD_HEAD = 'H',
  METHOD_CONNECT = 'C',
  METHOD_PATCH = 'P' + 'A',
  METHOD_OPTIONS = 'O',
};

struct http_request {

  enum HTTP_METHOD method;
  const char *path;
  const char *protocol_ver;

  size_t content_length ;

  struct http_header_dyn_arr *headers_array;

  char *__underlying_buffer;
  char *__underlying_buffer_start;
};

struct http_request_options {
  void *(*allocate)(size_t);
  void *(*deallocate)(void *);
};

struct http_request *http_init(const char *http_str,
                               void *(*allocate)(size_t size));

void http_free(struct http_request *http, void (*dealloc)(void *));

INLINE void http_dump(struct http_request *http) {
  puts("--- HTTP DUMP START ---");
  puts("----- REQUEST_PATH -----");
  puts(http->path);
  puts("----- PROTOCOL_VERSION -----");
  puts(http->protocol_ver);
  puts("----- CONTENT_LENGTH -----");
  printf("%zu\n",http->content_length);

  puts("----- HTTP_HEADERS START -----");
  for (size_t i = 0 ; i < http->headers_array->occupied; i++) {
    struct http_header_node node = (http->headers_array->array)[i];
    printf("Header: %s\t\t\tValue:%s\n", node.key, node.value );
  }

  puts("----- REST OF BUFFER -----");
  puts(http->__underlying_buffer);
  puts("--- HTTP DUMP END ---");
  return;
}

#endif
