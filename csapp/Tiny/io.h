//
// Created by 张林 on 3/26/15.
//

#ifndef _TINY_IO_H_
#define _TINY_IO_H_
#define RIO_BUFSIZE 8192
#define MAXLINE 1024
#define MAXBUF 8192
typedef struct {
    int rio_fd; //描述符
    ssize_t rio_cnt; //缓存中未读数
    char *rio_bufptr; //缓存中的下一个未读字节
    char rio_buf[RIO_BUFSIZE]; //缓存
    int end;
} rio_t;

ssize_t rio_readn(int fd, char *buf, size_t n);
ssize_t rio_writen(int fd, char *buf, size_t n);

//
//初始化rio
//
void rio_readinitb(rio_t *rp, int fd);

ssize_t rio_readlineb(rio_t *rp, char *buf, size_t maxlen);
ssize_t rio_readnb(rio_t *rp, char *buf, size_t n);

ssize_t rio_read(rio_t *rp, char *buf, size_t n);
void error(char *msg);

#endif //_TINY_IO_H_
