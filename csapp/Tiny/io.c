//
// Created by 张林 on 3/26/15.
//

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>
#include "io.h"

void error(char *msg){
    fprintf(stderr, "⚠ %s: %s\n", msg, strerror(errno));
    exit(0);
}

ssize_t rio_readn(int fd, char *buf, size_t n) {
    size_t nleft = n;
    ssize_t nread = 0;
    char *bufp = buf;
    while(nleft > 0){
        if((nread=read(fd, bufp, nleft)) < 0){
            if(errno == EINTR){
                nread = 0;
            }else{
                return -1;
            }
        } else if(nread == 0){
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return n-nleft;
}

ssize_t rio_writen(int fd, char *buf, size_t n) {
    size_t nleft = n;
    ssize_t nwrite = 0;
    char * bufp = buf;
    while (nleft > 0){
        if((nwrite=write(fd, bufp, nleft)) < 0){
            if(errno == EINTR){
                nwrite = 0;
            }else{
                return -1;
            }
        }else if(nwrite == 0){
            break;
        }
        nleft -= nwrite;
        bufp += nwrite;
    }
    return n-nleft;
}

ssize_t rio_read(rio_t *rp, char *buf, size_t n) {
    ssize_t readc; //读取的字节数
    while(rp->rio_cnt<=0 && !rp->end){
        if((rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf))) < 0){
            if(errno != EINTR){
                return -1;
            }
        }else if(rp->rio_cnt == 0){

            return 0;
        }else{
            //What's the FUCK?
            if(rp->rio_cnt < sizeof(rp->rio_buf)){
                rp->end = 1;
            }
            rp->rio_bufptr = rp->rio_buf;
        }
    }

    //取rp->rio_cnt 与 n中较小的一个.
    readc = n;
    if(rp->rio_cnt < n){
        readc = rp->rio_cnt;
    }
//    readc = rp->rio_cnt < n ? rp->rio_cnt : n;
    memcpy(buf, rp->rio_bufptr, readc);
    rp->rio_bufptr += readc;
    rp->rio_cnt -= readc;
    return readc;
}

void rio_readinitb(rio_t *rp, int fd) {
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->end = 0;
    rp->rio_bufptr = rp->rio_buf;
}

ssize_t rio_readlineb(rio_t *rp, char *buf, size_t maxlen) {
    int n, readc;
    char c, *bufp = buf;
    for(n=0; n<maxlen; n++){
        if((readc = rio_read(rp, &c, 1)) == 1){
            *bufp++ = c;
            if(c=='\n'){
                break;
            }
        }else if(readc == 0){
            if(n==1){
                return 0; //文件结束,没有读到数据
            }else{
                break; //文件结束，读了一些数据
            }
        }else {
            return -1;
        }
    }
    *bufp = 0;
    return n;
}

ssize_t rio_readnb(rio_t *rp, char *buf, size_t n) {
    size_t nleft = n;
    size_t nread;
    char *bufp = buf;
    while(nleft > 0){
        if((nread = rio_read(rp, bufp, nleft)) < 0){
            if(errno == EINTR){
                nread = n;
            }else{
                return -1;
            }
        }else if(nread == 0){
            break;
        }

        nleft -= nread;
        bufp += nread;
    }
    return n-nleft;
}
