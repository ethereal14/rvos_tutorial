#include "platform.h"

    # size of each hart's stack is 1024 bytes
    .equ    STACK_SIZE, 1024
    .global _start

    .text

_start:
    csrr t0, mhartid    # 读Hart id
    mv tp, t0
    bnez   t0, park

    # set all bytes in the bss section to zero
    la a0, _bss_start
    la a1, _bss_end
    bgeu a0, a1, 2f
1:
    sw zero, (a0)
    addi a0, a0, 4; # a0 = a0 + 4
    bltu a0, a1, 1b
2:
    slli t0, t0, 10     #t0 向左移动10位, 1024
    la sp, stacks + STACK_SIZE

    add sp, sp, t0; #  把sp移动到Hart对应的栈的栈顶位置上

    j start_kernel
    

park:
    wfi
    j park

stacks:
    .skip STACK_SIZE * MAXNUM_CPU

    .end