//
//  用信号量来实现互斥
//  Example:
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
void *thread(void *vargp);
volatile int cnt = 0;
sem_t mutex;
int main(int argc, const char * argv[]) {
    int niters;
    pthread_t tid1,tid2;
    niters = atoi(argv[1]);
    sem_init(&mutex, 0, 1);

    pthread_create(&tid1, NULL, thread, &niters);
    pthread_create(&tid2, NULL, thread, &niters);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    if(cnt!=(2*niters)){
        printf("BOOM! cnt=%d\n", cnt);
    }else{
        printf("OK cnt=%d\n", cnt);
    }
    exit(0);
    return 0;
}
void *thread(void *vargp){
    int i, niters = *((int *) vargp);
    for(int i=0; i<niters; i++){
        sem_wait(&mutex);
        cnt++;
        sem_post(&mutex);
    }
    return NULL;
}
