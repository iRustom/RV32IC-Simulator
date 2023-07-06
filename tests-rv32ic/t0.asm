
t0.elf:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00010117          	auipc	sp,0x10
   4:	01010113          	add	sp,sp,16 # 10010 <_stack_start>
   8:	2029                	jal	12 <main>

0000000a <loop>:
   a:	48a9                	li	a7,10
   c:	00000073          	ecall
  10:	bfed                	j	a <loop>

00000012 <main>:
  12:	4085                	li	ra,1
  14:	4109                	li	sp,2
  16:	418d                	li	gp,3
  18:	4211                	li	tp,4
  1a:	4295                	li	t0,5
  1c:	4319                	li	t1,6
  1e:	002083b3          	add	t2,ra,sp
  22:	00038433          	add	s0,t2,zero
  26:	007404b3          	add	s1,s0,t2
  2a:	40648533          	sub	a0,s1,t1
  2e:	7a000593          	li	a1,1952
  32:	0596                	sll	a1,a1,0x5
  34:	7a000613          	li	a2,1952

00000038 <test_branch>:
  38:	0020c363          	blt	ra,sp,3e <L1>
  3c:	a031                	j	48 <FAIL>

0000003e <L1>:
  3e:	00535363          	bge	t1,t0,44 <L2>
  42:	a019                	j	48 <FAIL>

00000044 <L2>:
  44:	00c58463          	beq	a1,a2,4c <PASS>

00000048 <FAIL>:
  48:	5ffd                	li	t6,-1
  4a:	a011                	j	4e <finish>

0000004c <PASS>:
  4c:	4f81                	li	t6,0

0000004e <finish>:
  4e:	48a9                	li	a7,10
  50:	00000073          	ecall

Disassembly of section .riscv.attributes:

00000000 <.riscv.attributes>:
   0:	1e41                	add	t3,t3,-16
   2:	0000                	unimp
   4:	7200                	.2byte	0x7200
   6:	7369                	lui	t1,0xffffa
   8:	01007663          	bgeu	zero,a6,14 <main+0x2>
   c:	0014                	.2byte	0x14
   e:	0000                	unimp
  10:	7205                	lui	tp,0xfffe1
  12:	3376                	.2byte	0x3376
  14:	6932                	.2byte	0x6932
  16:	7032                	.2byte	0x7032
  18:	5f31                	li	t5,-20
  1a:	30703263          	.4byte	0x30703263
	...
