//
// Created by 张林 on 3/26/15.
//

#ifndef _TINY_TINY_H_
#define _TINY_TINY_H_

#include "io.h"
#include "http.h"

struct response {
    int status;
    char * content_type;
    size_t content_length;
};
struct request {
    int connfd;
    char method[MAXLINE];
    int uri_type;
    char uri[MAXLINE];
    char cgi_args[MAXLINE];
    char headers[MAXBUF];
    char body[MAXBUF];
    char filename[MAXLINE];
    char version[MAXLINE];
};
extern char **environ;
/**
* 启动服务器
*/
int startup(int port);

/**
* 监听客户端的请求
*/
void wait_client(int fd);

/**
* 读取客户端的请求
*/
void handle_client(int connfd);

/**
* 读取http头信息
*/
int read_headers(rio_t *rp, char *headers);
/**
* 读取http内容
*/
void read_body(rio_t *rp , char *body);
void do_error(int status, struct request *req, struct response *resp);
#define URI_STATIC 0
#define URI_DYNAMIC 1
int parse_uri(char * uri, char *filename, char *cgi_args);
int build_file_headers(char * filename, struct response *resp);
void write_response(struct request *req);
void write_static(struct request *req, struct response *resp);
void write_dynamic(struct request *req, struct response *resp);
void write_headers(struct request *req, struct response *resp);
void write_file(struct request *req, struct response *resp);
void header(char *buff, char *key, char*value);
/**
* 跳转
*/
int redirect(char * url);
#endif //_TINY_TINY_H_
