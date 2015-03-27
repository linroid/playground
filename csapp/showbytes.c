#include "showbytes.h"

void show_bytes(byte_pointer start, int len){
    for(int i=0; i<len; i++){
        printf("%.2x\t", start[i]);
    }
    printf("\n");
}
void show_int(int x){
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x){
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x){
    show_bytes((byte_pointer)&x, sizeof(void *));
}

void test_show_bytes(int val){
    int ival = val;
    float fval = (float)val;
    int *pval = &val;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
    
}