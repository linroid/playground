//
//  将点分十进制的ip地址转为16进制
//  Example:
//      ./dd2dex 127.0.0.1
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, const char * argv[]) {
    struct in_addr ia;
    inet_aton(argv[1], &ia);
    printf("0x%x\n", htonl(ia.s_addr));
    return 0;
}
