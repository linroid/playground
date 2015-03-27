//
//  将十六进制的IP地址转为点分十进制表示
//  Example:
//      ./hex2dd 0x7f000001
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <arpa/inet.h>

int main(int argc, const char * argv[]) {
    struct in_addr ia;
    int hex;
    sscanf( argv[1], "0x%x", &hex);
    ia.s_addr = ntohl(hex);
    puts(inet_ntoa(ia));
    return 0;
}
