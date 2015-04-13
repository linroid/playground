//
//  多线程
//  Example:
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int p_count = 0;
void *thread(void *vargp){
    pthread_t tid;
    p_count++;
    printf("Hello Pthreads: %d\n", pthread_self());

    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    pthread_detach(pthread_self());
    return NULL;
}
int main(int argc, const char * argv[]) {
    pthread_t tid;
    pthread_create(&tid, NULL, thread, NULL);
    pthread_cancel(tid);
    pause();
    pthread_join(tid, NULL);
    printf("共创建了%d个线程\n", p_count);
    return 0;
}
