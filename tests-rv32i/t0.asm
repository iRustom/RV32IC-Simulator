
t0.elf:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00010117          	auipc	sp,0x10
   4:	01010113          	add	sp,sp,16 # 10010 <_stack_start>
   8:	010000ef          	jal	18 <main>

0000000c <loop>:
   c:	00a00893          	li	a7,10
  10:	00000073          	ecall
  14:	ff9ff06f          	j	c <loop>

00000018 <main>:
  18:	00100093          	li	ra,1
  1c:	00200113          	li	sp,2
  20:	00300193          	li	gp,3
  24:	00400213          	li	tp,4
  28:	00500293          	li	t0,5
  2c:	00600313          	li	t1,6
  30:	002083b3          	add	t2,ra,sp
  34:	00038433          	add	s0,t2,zero
  38:	007404b3          	add	s1,s0,t2
  3c:	40648533          	sub	a0,s1,t1
  40:	7a000593          	li	a1,1952
  44:	00559593          	sll	a1,a1,0x5
  48:	7a000613          	li	a2,1952

0000004c <test_branch>:
  4c:	0020c463          	blt	ra,sp,54 <L1>
  50:	0100006f          	j	60 <FAIL>

00000054 <L1>:
  54:	00535463          	bge	t1,t0,5c <L2>
  58:	0080006f          	j	60 <FAIL>

0000005c <L2>:
  5c:	00c58663          	beq	a1,a2,68 <PASS>

00000060 <FAIL>:
  60:	fff00f93          	li	t6,-1
  64:	0080006f          	j	6c <finish>

00000068 <PASS>:
  68:	00000f93          	li	t6,0

0000006c <finish>:
  6c:	00a00893          	li	a7,10
  70:	00000073          	ecall

Disassembly of section .riscv.attributes:

00000000 <.riscv.attributes>:
   0:	1941                	.2byte	0x1941
   2:	0000                	.2byte	0x0
   4:	7200                	.2byte	0x7200
   6:	7369                	.2byte	0x7369
   8:	01007663          	bgeu	zero,a6,14 <loop+0x8>
   c:	0000000f          	fence	unknown,unknown
  10:	7205                	.2byte	0x7205
  12:	3376                	.2byte	0x3376
  14:	6932                	.2byte	0x6932
  16:	7032                	.2byte	0x7032
  18:	0031                	.2byte	0x31
