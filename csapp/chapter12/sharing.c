//
//  12.4 多线程程序中的共享变量
//  Example:
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

#define N 2
void *thread(void *vargp);
char **ptr;
int main(int argc, const char * argv[]) {
    int i;
    pthread_t tid;
    char *msgs[N] = {"第0条消息", "第1条消息"};
    ptr = msgs;
    for (i=0; i<N; i++){
        pthread_create(&tid, NULL, thread, (void *)i);
    }
    pthread_exit(NULL);
    return 0;
}
void *thread(void *vargp){
    int i = (int)vargp;
    static int cnt=0;
    printf("[%d]: %s(cnt=%d)\n", i, ptr[i], ++cnt);
    return NULL;
}
