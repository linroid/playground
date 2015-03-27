//
//  lib.h
//  csapp
//
//  Created by 张林 on 15/3/25.
//  Copyright (c) 2015年 linroid. All rights reserved.
//

#ifndef __SHOWBYTES__H__
#define __SHOWBYTES__H__

#include <stdio.h>

typedef unsigned char * byte_pointer;

void show_bytes(byte_pointer start, int len);

void show_int(int x);

void show_float(float x);

void show_pointer(void *x);

void test_show_bytes(int val);

#endif 
/* defined(__SHOWBYTES__H__) */
