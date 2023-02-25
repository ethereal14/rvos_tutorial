# Not
# Format:
# NOT RD, RS
# The contents of RS is fetched and each of the bits is flipped. The resulting
# value is copied into RD.
# NEG is a pseudoinstruction, and is assembled indentically to:
# XORI RD, RS, -1 // NOTE that -1 is 0xFFFFFFFF
    .text               # Define beginning of text section
    .global _start      # Define enty _start

_start:
    li x6, 0xffff0000 # x6 = 0xffff0000

    not x5, x6
    xori x5, x6, -1; # x5 = x6 ^ -1
    
stop:
    j stop          # Infinite loop to stop execution

    .end
