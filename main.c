#include "http_parser.h"
#include "http_req_dyn_array.h"
#include <stdio.h>

const char *buffer =
    "POST /cgi-bin/process.cgi HTTP/1.1\r\n"
    "User-Agent: Mozilla/4.0 (compatible; MSIE5.01; Windows NT)\r\n"
    "Host: www.tutorialspoint.com\r\n"
    "Content-Type: text/xml; charset=utf-8\r\n"
    "Content-Length: 5\r\n"
    "Accept-Language: en-us\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Connection: Keep-Alive\r\n"
    "\r\n"
    "Hi There 1\n"
    "Hi There 2\n"
    "Hi There 3\n"
    "Hi There 4\n";

int main(void) {
  struct http_request *http = http_init(buffer, NULL);
  http_dump(http);
  http_free(http, NULL);

  /* const char *val = NULL; */

  /* val = http_header_get_value(http->headers_array, "Host"); */
  /* puts(val); */
  /* val = http_header_get_value(http->headers_array, "Hosd"); */
  /* puts(val); */

  return puts("Program Terminated Normally ^_^"), 0;
}
