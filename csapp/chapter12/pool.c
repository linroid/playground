
//
//  I/O多路复用
//
#include "pool.h"
void echo (int);
void command(void);

//服务端收到的总字节数
int byte_cnt = 0;
int main(int argc, char**argv){
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    static pool pool;

    port = atoi(argv[1]);
    listenfd = Open_listenfd(port);

    init_pool(listenfd, &pool);
    while(1){
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);
        if(FD_ISSET(listenfd, &pool.ready_set)){
            connfd = Accept(listenfd, (SA *) &clientaddr, &clientlen);
            add_client(connfd, &pool);
        }
        check_clients(&pool);
    }
}

void init_pool(int listenfd, pool *pool){
    pool->maxi = -1;
    memset(pool->clientfd, -1, sizeof(pool->clientfd));
    pool->maxfd = listenfd;
    FD_ZERO(&pool->read_set);
    FD_SET(listenfd, &pool->read_set);
}
void add_client(int connfd, pool * pool){
    int i;
    pool->nready--;
    //找到未使用的
    for(i=0; i<FD_SETSIZE; i++){
        if(pool->clientfd[i] < 0){
            pool->clientfd[i] = connfd;
            Rio_readinitb(&pool->clientrio[i], connfd);
            FD_SET(connfd, &pool->read_set);
            if(connfd > pool->maxfd){
                pool->maxfd = connfd;
            }
            if(i > pool->maxi){
                pool->maxi = i;
            }
            break;
        }
    }
    if(i == FD_SETSIZE){
        app_error("add_client error: Too many clients");
    }
}
void check_clients(pool *pool){
    int i,connfd, n;
    char buf[MAXLINE];
    rio_t rio;
    for(i=0; (i<=pool->maxi) && (pool->nready>0); i++){
        connfd = pool->clientfd[i];
        rio = pool->clientrio[i];
        if((connfd>0) && (FD_ISSET(connfd, &pool->ready_set ))){
            pool->nready--;
            if((n=Rio_readlineb(&rio, buf, MAXLINE)) != 0){
                byte_cnt += n;
                printf("服务端在描述符[%d]上收到%d(总共%d)字节\n", connfd, n, byte_cnt);

                fflush(stdout);
                Rio_writen(connfd, buf, n;
            }else{
                 Close(connfd);
                 FD_CLR(connfd, &pool->read_set);
                 pool->clientfd[i] = -1;
             }
        }
    }
}
