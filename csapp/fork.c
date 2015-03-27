//
//
//  Example:
//
//  Created by 张林 on 15/2/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
int main(int argc, const char * argv[]) {
    fork();
    fork() && fork() || fork();
    fork();
    printf("+");
    return 0;
}
