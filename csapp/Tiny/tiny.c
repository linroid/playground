//
// Created by 张林 on 3/26/15.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <strings.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <stddef.h>
#include "tiny.h"



int startup(int port){
    struct sockaddr_in server_sin;
    int listenfd;
    listenfd =socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd<0){
        error("创建socket出错");
    }
    //立即终止和重启服务,默认情况下重启服务器会在30秒左右拒绝客户端的请求
    int optval = 1;
    if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int)) < 0){
        error("重启服务失败");
    }
    memset(&server_sin, 0, sizeof(server_sin));
    server_sin.sin_family = AF_INET;
    server_sin.sin_port = htons(port);
    server_sin.sin_addr.s_addr = htonl(INADDR_ANY);
    //将服务器套接字地址server_sin和套接字描述listenfd符联系起来
    if(bind(listenfd, (struct sockaddr const *) &server_sin, sizeof(server_sin)) <0){
        error("绑定出错");
    }
    if(listen(listenfd, 1024) < 0){
        error("监听出错");
    }
    return listenfd;
}

void wait_client(int listenfd) {
    struct sockaddr_in client_sin;
    int connfd;
    struct hostent *hp;
    char * clientaddr;
    int clientlen;
    while (1){
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (struct sockaddr *) &client_sin, &clientlen);
        hp = gethostbyaddr((const char *) &client_sin.sin_addr.s_addr, sizeof(client_sin.sin_addr.s_addr), AF_INET);
        clientaddr = inet_ntoa(client_sin.sin_addr);
        printf("收到客户端%s的连接(%s:%d)\n", hp->h_name, clientaddr, ntohs(client_sin.sin_addr.s_addr));
        fflush(stdout);
        handle_client(connfd);
        close(connfd);
    }
}
void handle_client(int connfd){
    char buff[MAXLINE];
    struct request req;
    rio_t rp;

    req.connfd = connfd;
    rio_readinitb(&rp, req.connfd);
    rio_readlineb(&rp, &buff, sizeof(buff));
    sscanf(buff, "%s %s %s", req.method, req.uri, req.version);

    req.uri_type = parse_uri(req.uri, req.filename, req.cgi_args);
    read_headers(&rp, req.headers);
    read_body(&rp, req.body);
    write_response(&req);
}

int read_headers(rio_t *rp, char *headers) {
    char buff[MAXLINE];
    rio_readlineb(rp, buff, sizeof(buff));
    puts("-------HEADER------\n");
    while(strcmp(buff, "\r\n")){
        rio_readlineb(rp, buff, sizeof(buff));
        sprintf(headers, "%s%s", headers, buff);
    }
    puts(headers);
}

void read_body(rio_t *rp, char *body) {
    fflush(stdout);
    rio_readnb(rp, body, sizeof(body));
    puts("-------BODY------\n");
    puts(body);
}

void write_response(struct request *req) {
    struct response resp;
    if(req->uri_type == URI_STATIC){
        write_static(req, &resp);
    }else{
        write_dynamic(req, &resp);
    }
}


void write_static(struct request *req, struct response *resp) {
    struct stat st;
    if(stat(req->filename, &st) < 0){
        printf("%s文件未f7找到\n", req->filename);
        do_error(404, req, resp);
    }else{
        build_file_headers(req->filename, resp);
        write_headers(req, resp);
        write_file(req, resp);
    }
}

void write_dynamic(struct request *req, struct response *resp) {
    char * argv[] = {NULL};
    char buf[MAXLINE];

    /* Return first part of HTTP response */
    sprintf(buf, "%s %d %s\r\n", HTTP_VERSION, 200, status_text(200));
    rio_writen(req->connfd, buf, strlen(buf));
    sprintf(buf, "%s: %s\r\n", HEADER_SERVER, SERVER_NAME);
    rio_writen(req->connfd, buf, strlen(buf));

    if (fork() == 0){
        //设置cgi变量
        setenv("QUERY_STRING", req->cgi_args, 1);
        dup2(req->connfd, STDOUT_FILENO);//重定向标准输出流描述符到套接字描述符
        execve(req->filename, argv, environ); //执行cgi程序
    }
    wait(NULL);
}
void write_file(struct request *req, struct response *resp) {
    int filefd;
    char * filep;
    filefd = open(req->filename, O_RDONLY, 0);
    filep = mmap(0, resp->content_length, PROT_READ, MAP_PRIVATE, filefd, 0);
    close(filefd);
    rio_writen(req->connfd, filep, resp->content_length);
    munmap(filep, resp->content_length);
}

void do_error(int status, struct request *req, struct response *resp) {
    resp->status = status;
    sprintf(req->filename, "./errors/%d.html", status);
    if(build_file_headers(req->filename, resp) < 0){
        sprintf(req->filename, "./errors/%d.html", 500);
        build_file_headers(req->filename, resp);
    }
    write_headers(req, resp);
    write_file(req, resp);
}

int build_file_headers(char *filename, struct response *resp) {
    struct stat st;
    if(stat(filename, &st) < 0){
        return -1;
    }
    resp->status = 200;
    resp->content_type = file_type(filename);
    resp->content_length = (size_t) st.st_size;
    return 0;
}



void write_headers(struct request *req, struct response *resp) {
    char buff[MAXBUF];
    sprintf(buff, "%s %d %s\r\n", HTTP_VERSION, resp->status, status_text(resp->status));
    sprintf(buff, "%s%s: %d\r\n", buff, HEADER_CONTENT_LENGTH, resp->content_length);
    header(buff, HEADER_SERVER, SERVER_NAME);
    header(buff, HEADER_CONTENT_TYPE, resp->content_type);
    sprintf(buff, "%s\r\n", buff);
    rio_writen(req->connfd, buff, strlen(buff));
}


void header(char *buff, char *key, char *value) {
    sprintf(buff, "%s%s: %s\r\n", buff, key, value);
}

int parse_uri(char *uri, char *filename, char *cgi_args) {
    //访问静态文件
    if(strstr(uri, CGI_BIN)==NULL){
        strcpy(filename, DOCUMENT_ROOT);
        strcat(filename, uri);
        if(uri[strlen(uri)-1] == '/'){
            strcat(filename, INDEX_FILE);
        }
        strcpy(cgi_args, "");
        return URI_STATIC;
    //动态页面
    }else{
        char *ptr = index(uri, '?');
        if(ptr){
            strcpy(cgi_args, ptr+1);
            *ptr = '\0';
        }else{
            strcpy(cgi_args, "");
        }
        strcpy(filename, ".");
        strcpy(filename, uri);
        if(uri[strlen(uri)-1] == '/'){
            strcat(filename, INDEX_CGI);
        }
        return URI_DYNAMIC;
    }
}
int redirect(char *url) {
    return 0;
}