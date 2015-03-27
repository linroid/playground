//
//  获取目标主机的状态信息
//  Example:
//      ./hostinfo localhost
//      ./hostinfo 127.0.0.1
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, const char * argv[]) {
    struct hostent * hostent;
    char ** pp;
    struct in_addr addr;

    if(argc != 2){
        fprintf(stderr, "usage: %s <domain name or dotted-decimal>\n", argv[0]);
        exit(0);
    }
    if(inet_aton(argv[1], &addr)){
        hostent = gethostbyaddr((const char *)&addr, sizeof(addr), AF_INET);
    }else{
        hostent = gethostbyname(argv[1]);
    }
    printf("official hostname: %s\n", hostent->h_name);
    for(pp=hostent->h_aliases; *pp!=NULL; pp++){
        printf("alias: %s\n", *pp);
    }
    for(pp=hostent->h_addr_list; *pp!=NULL; pp++){
        addr.s_addr = ((struct in_addr *) *pp)->s_addr;
        printf("address: %s\n", inet_ntoa(addr));
    }
    return 0;
}
