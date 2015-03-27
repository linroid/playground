//
//  socket 服务器端实现
//  Example:
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include "../csapp.h"
void echo(int fd){
    int n;
    char buf[MAXLINE];
    rio_t rio;
    Rio_readinitb(&rio, fd);
    while((n= (int) Rio_readlineb(&rio, buf, MAXLINE)) != 0){
        printf("server received %d bytes \n", n);
        Rio_writen(fd, buf, n);
    }
}
int open_listenfd(int port){
    int fd, optval = 1;
    struct sockaddr_in sin;
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        fprintf(stderr, "创建socket失败\n");
        return -1;
    }
    //立即终止和重启,重启服务器默认会在30秒内拒绝客户端的连接请求
    if((setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int) )) < 0){
        fprintf(stderr, "端口已经占用\n");
        return -1;
    }
    bzero((char*)&sin, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons((unsigned short)port);
    if(bind(fd, (struct sockaddr *)&sin, sizeof(sin))<0){
        fprintf(stderr, "bind出错\n");
        return -1;
    }
    if(listen(fd, 1024) < 0){
        fprintf(stderr, "listen 出错");
        return -1;
    }
    return fd;
}
void read_client(int listenfd){
    rio_t rio;
    char *host, buf[1000];
    struct sockaddr_in clientaddr;
    int clientlen, clientfd;
    struct hostent *hp;
    char * haddrp;

    clientlen = sizeof(clientaddr);

    clientfd = accept(listenfd, (struct sockaddr *) &clientaddr, (socklen_t *) &clientlen);
    hp = gethostbyaddr((const char *)(clientaddr.sin_addr.s_addr), sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    haddrp = inet_ntoa(clientaddr.sin_addr);
    printf("server connected to %s (%s)\n", hp->h_name, haddrp);
    echo(clientfd);
    close(clientfd);
}

int main(int argc, const char * argv[]) {
    int fd, port;
    sscanf(argv[1], "%d", &port);
    if((fd=open_listenfd(port))>0){
        printf("监听端口: %d 成功\n", port);
        while(1){
            read_client(fd);
        }
    }
    return 0;
}
