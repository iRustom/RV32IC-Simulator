	.file	"t1.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	nums
	.data
	.align	2
	.type	nums, @object
	.size	nums, 40
nums:
	.word	1
	.word	2
	.word	4
	.word	6
	.word	7
	.word	9
	.word	7
	.word	11
	.word	13
	.word	17
	.text
	.align	2
	.globl	dble
	.type	dble, @function
dble:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	sw	a0,-20(s0)
	lw	a5,-20(s0)
	slli	a5,a5,1
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	dble, .-dble
	.align	2
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32
	sw	zero,-24(s0)
	sw	zero,-20(s0)
	j	.L4
.L5:
	lw	a0,-20(s0)
	call	dble
	mv	a4,a0
	lw	a5,-24(s0)
	add	a5,a4,a5
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L4:
	lw	a4,-20(s0)
	li	a5,9
	ble	a4,a5,.L5
 #APP
# 10 "t1.c" 1
	li	a7, 1
# 0 "" 2
# 11 "t1.c" 1
	mv	a0, a5
# 0 "" 2
 #NO_APP
	sw	a5,-24(s0)
 #APP
# 12 "t1.c" 1
	ecall
# 0 "" 2
 #NO_APP
	li	a5,0
	mv	a0,a5
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (g2ee5e430018-dirty) 12.2.0"
