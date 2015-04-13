#include "../csapp.h"
void echo (int);
void command(void);
int main(int argc, char**argv){
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    fd_set read_set, ready_set;

    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);
    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);
    while(1){
        ready_set = read_set;
        Select(listenfd+1, &ready_set, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &ready_set)){
            command();
        }else{
            connfd = Accept(listenfd, (SA *)&clientaddr, &clientaddr);
            echo(connfd);
            Close(connfd);
        }
    }
}
void command(void){
    char buf[MAXLINE];
    if(!Fgets(buf, MAXLINE, stdin)){
        exit(0);
    }
    printf("%s", buf);
}
void echo(int connfd){
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
        printf("server received %d bytes\n", n);
        Rio_writen(connfd, buf, n);
    }
}
