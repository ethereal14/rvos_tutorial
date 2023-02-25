#include<stdio.h>

void foo()
{
    unsigned int i = 0x87654321;
    unsigned int high = i >> 16;
    unsigned int low = (i << 16)>>16;

    printf("i    = 0x%x\n"
           "high = 0x%x\n"
           "low  = 0x%x\n", i, high, low);
}

int main(void)
{
    foo();

    return 1;
}