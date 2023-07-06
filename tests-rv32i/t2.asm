
t2.elf:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00010117          	auipc	sp,0x10
   4:	01010113          	add	sp,sp,16 # 10010 <_stack_start>
   8:	070000ef          	jal	78 <main>

0000000c <loop>:
   c:	00a00893          	li	a7,10
  10:	00000073          	ecall
  14:	ff9ff06f          	j	c <loop>

00000018 <printInt>:
  18:	fe010113          	add	sp,sp,-32
  1c:	00812e23          	sw	s0,28(sp)
  20:	02010413          	add	s0,sp,32
  24:	fea42623          	sw	a0,-20(s0)
  28:	00100893          	li	a7,1
  2c:	00078513          	mv	a0,a5
  30:	fef42623          	sw	a5,-20(s0)
  34:	00000073          	ecall
  38:	00000013          	nop
  3c:	01c12403          	lw	s0,28(sp)
  40:	02010113          	add	sp,sp,32
  44:	00008067          	ret

00000048 <printString>:
  48:	fe010113          	add	sp,sp,-32
  4c:	00812e23          	sw	s0,28(sp)
  50:	02010413          	add	s0,sp,32
  54:	fea42623          	sw	a0,-20(s0)
  58:	00400893          	li	a7,4
  5c:	00078513          	mv	a0,a5
  60:	fef42623          	sw	a5,-20(s0)
  64:	00000073          	ecall
  68:	00000013          	nop
  6c:	01c12403          	lw	s0,28(sp)
  70:	02010113          	add	sp,sp,32
  74:	00008067          	ret

00000078 <main>:
  78:	fe010113          	add	sp,sp,-32
  7c:	00112e23          	sw	ra,28(sp)
  80:	00812c23          	sw	s0,24(sp)
  84:	02010413          	add	s0,sp,32
  88:	00a00793          	li	a5,10
  8c:	fef42623          	sw	a5,-20(s0)
  90:	01400793          	li	a5,20
  94:	fef42423          	sw	a5,-24(s0)
  98:	fe842783          	lw	a5,-24(s0)
  9c:	00179713          	sll	a4,a5,0x1
  a0:	fec42783          	lw	a5,-20(s0)
  a4:	00f707b3          	add	a5,a4,a5
  a8:	ff378793          	add	a5,a5,-13
  ac:	fef42623          	sw	a5,-20(s0)
  b0:	fec42503          	lw	a0,-20(s0)
  b4:	f65ff0ef          	jal	18 <printInt>
  b8:	00100793          	li	a5,1
  bc:	00078513          	mv	a0,a5
  c0:	01c12083          	lw	ra,28(sp)
  c4:	01812403          	lw	s0,24(sp)
  c8:	02010113          	add	sp,sp,32
  cc:	00008067          	ret

Disassembly of section .riscv.attributes:

00000000 <.riscv.attributes>:
   0:	1b41                	.2byte	0x1b41
   2:	0000                	.2byte	0x0
   4:	7200                	.2byte	0x7200
   6:	7369                	.2byte	0x7369
   8:	01007663          	bgeu	zero,a6,14 <loop+0x8>
   c:	0011                	.2byte	0x11
   e:	0000                	.2byte	0x0
  10:	1004                	.2byte	0x1004
  12:	7205                	.2byte	0x7205
  14:	3376                	.2byte	0x3376
  16:	6932                	.2byte	0x6932
  18:	7032                	.2byte	0x7032
  1a:	0031                	.2byte	0x31

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347          	.4byte	0x3a434347
   4:	2820                	.2byte	0x2820
   6:	65653267          	.4byte	0x65653267
   a:	6535                	.2byte	0x6535
   c:	3334                	.2byte	0x3334
   e:	3030                	.2byte	0x3030
  10:	3831                	.2byte	0x3831
  12:	642d                	.2byte	0x642d
  14:	7269                	.2byte	0x7269
  16:	7974                	.2byte	0x7974
  18:	2029                	.2byte	0x2029
  1a:	3231                	.2byte	0x3231
  1c:	322e                	.2byte	0x322e
  1e:	302e                	.2byte	0x302e
	...
