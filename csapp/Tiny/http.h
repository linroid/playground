//
// Created by 张林 on 3/26/15.
//

#ifndef _TINY_HTTP_H_
#define _TINY_HTTP_H_

#define DOCUMENT_ROOT "./www"
#define INDEX_FILE "index.html"
#define INDEX_CGI "index"

#define HTTP_VERSION "HTTP/1.0"
#define CGI_BIN "cgi-bin"
#define SERVER_NAME "Tiny Server/0.1.0"

//method
#define METHOD_GET "GET"
#define METHOD_POST "POST"
#define METHOD_PUT "PUT"

//header
#define HEADER_HOST "Host"
#define HEADER_CONTENT_TYPE "Content-type"
#define HEADER_CONTENT_LENGTH "Content-length"
#define HEADER_SERVER  "Server"

char *status_text(int status);
char *file_type(char * filename);
#endif //_TINY_HTTP_H_
