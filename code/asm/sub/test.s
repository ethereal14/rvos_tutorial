# Substract
# Format:
#   SUB RD, RS1, RS2
# Description:
#   The contents if RS1 is substracted to the contents of RS2 and result is
#   placed in RD.

    .text
    .global _start

_start:
    li x6, -1 # x6 = 1
    li x7, -2 # x7 = -2
    sub x5, x6, x7 # x5 = x6 - x7

stop:
    j stop

    .end
    
