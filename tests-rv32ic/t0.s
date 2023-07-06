    .text
    .globl	main
main:
    li x1, 1
    li x2, 2
    li x3, 3
    li x4, 4
    li x5, 5
    li x6, 6

    add x7, x1, x2
    add x8, x7, x0
    add x9, x8, x7
    sub x10, x9, x6

    li  x11, 0x7A0
    sll x11, x11, 5
    la  x12, 0x7A0
    
test_branch:
    blt x1, x2, L1
    j   FAIL
L1:
    bge x6, x5, L2
    j   FAIL
L2:
    beq x11, x12, PASS
FAIL:
    li  x31, -1
    j   finish
PASS:
    li  x31, 0
finish:
    li  a7, 10
    ecall    
    