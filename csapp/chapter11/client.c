//
//  向目标主机建立连接，返回打开的套接字描述符
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
int open_clientfd(char *hostname, int port){
    int clientfd;
    struct hostent *hp;
    struct sockaddr_in serveraddr;
    if((clientfd=socket(AF_INET, SOCK_STREAM, 0) ) < 0){
        printf("建立socket出错\n");
        return -1;
    }
    if((hp=gethostbyname(hostname)) == NULL){
        printf("获取主机(%s)信息出错", hostname);
        return -2;
    }
    bzero((char*)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char*) hp->h_addr_list[0], (char*)&serveraddr.sin_addr, hp->h_length);
    serveraddr.sin_port = htons(port);
    if(connect(clientfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0){
        printf("连接失败\n");
        return -1;
    }
    printf("连接 %s 成功, 描述符:%d\n", hostname, clientfd);
    return clientfd;
}
int main(int argc, const char * argv[]) {
    int fd = open_clientfd("baidu.com", 80);

    return 0;
}
