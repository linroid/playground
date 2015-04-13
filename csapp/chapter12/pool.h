#include "../csapp.h"
typedef struct {
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    rio_t clientrio[FD_SETSIZE];
} pool;

void init_pool(int listenfd, pool *p);
void check_clients(pool *p);
void add_client(int connfd, pool*p);

