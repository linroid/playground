#include <stdio.h>
#include <stdlib.h>
#include "tiny.h"

int main(int argc, char **argv){
    int port, listenfd;
    if(argc != 2){
        error("请指定端口号\n\tExample: ./tiny 8000\n");
    }
    port = atoi(argv[1]);
    listenfd = startup(port);
    printf("listen on %d port ...\n", port);
    wait_client(listenfd);
    char* s1 = "Hello world";
    char s2[] = "Hello world";
    s1[2] = 'E';     // 1
    s2[2] = 'E';     // 2
    *(s1 + 2) = 'E';  // 3
    *(s2 + 2) = 'E';  // 4
    return 0;
}