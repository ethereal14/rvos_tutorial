# exercise 5-3

# register int a, b, c, d, e;
# b = 1;
# c = 2;
# d = 3;
# e = 4;
# a = (b + c) - (d + e);

    .text
    .global _start

_start:
    li x1, 1        # b = 1
    li x2, 2        # c = 2
    li x3, 3        # d = 3
    li x4, 4        # e = 4
    add x1, x1, x2
    add x3, x3, x4
    sub x5, x1, x3

stop:
    j stop

    .end

