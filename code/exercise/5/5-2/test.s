# Add
# Format:
# ADD RD, RS1, RS2
# Description:
#   The contents if RS1 is added to the contents of RS2 and result is
#   placed in RD.

    .text
    .global _start

_start:
    li x5, 1        # b = 1
    li x6, 2        # c = 2
    li x7, 3        # e = 3
    add x9, x5, x6  # x9 = x5 + x6  # a = b + c
    sub x10, x9, x7
    
stop:
    j stop

    .end
