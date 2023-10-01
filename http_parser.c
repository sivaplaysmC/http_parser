#include "http_parser.h"
#include "http_req_dyn_array.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

enum { true = 1, false = 0 };

extern void *malloc(size_t size);

static char *get_line(char **str);

struct http_request *http_init(const char *http_str,
                               void *(*allocate)(size_t size)) {

  if (allocate == NULL)
    allocate = malloc;

  struct http_request *http = allocate(sizeof(struct http_request));
  if (http == NULL)
    goto ret;
  http->__underlying_buffer = http->__underlying_buffer_start =
      strdup(http_str);

  char *__request_line = get_line(&http->__underlying_buffer);
  char *method_str = strtok_r(__request_line, " ", &__request_line);
  http->method = method_str[0];
  if (method_str[0] == 'P')
    http->method += method_str[1];

  http->path = strtok_r(__request_line, " ", &__request_line);
  http->protocol_ver = __request_line;

  http->headers_array = http_header_dyn_arr_init();
  char *line = NULL;
  while(line = get_line(&http->__underlying_buffer), *line != '\0' ) {
    char *header = strtok_r(line, ":", &line);
    char *value = line;
    if (strcasecmp("Content-length", header) == 0 ) {
      http->content_length = atoi(value);
    };
    if (*value == ' ') {
      value++;
    }
    http_header_node_push(http->headers_array, header, value);
  }


  goto ret;

ret:
  return http;
};

void http_free(struct http_request *http, void (*dealloc)(void *)) {
  if (dealloc == NULL)
    dealloc = free;
  free(http->__underlying_buffer_start);
  dealloc(http);
};

/* TODO : use `restrict` micro optimization for (double) pointer */
/* dont touch this. DONT TOUCH THIS. IT WILL BREAK . */
/* DEBUGGING THIS HAS SUBJECT ME TO MORE PAIN THAN BEING HIT IN THE BALLS */

static char *get_line(char **str) {
  char *start = *str;
  while (**str != '\0') {
    if (str[0][0] == '\r') {
      if (str[0][1] == '\n') {
        /* str[0][0] = str[0][1] = '\0'; */ // (maybe)saved 2-3 cpu cycles by reducing
                                            // one assignment to a non restrict
                                            // pointer ^_^
        str[0][0] = '\0';                   // set the \r charecter to \0, clever trick to partition string
        *str = *str + 2;
        break;
      }
    }
    *str = *str + 1;
  }

  return start;
}
