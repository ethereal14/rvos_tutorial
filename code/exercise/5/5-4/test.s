# exercise 5-4

    .text
    .global _start

_start:
    li x1, 0x87654321
    srli x2, x1, 16
    slli x3, x1, 16
    srli x3, x3, 16
    
stop:
    j stop

    .end

