
t1.elf:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00010117          	auipc	sp,0x10
   4:	01010113          	add	sp,sp,16 # 10010 <_stack_start>
   8:	098000ef          	jal	a0 <main>

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

00000078 <dble>:
  78:	fe010113          	add	sp,sp,-32
  7c:	00812e23          	sw	s0,28(sp)
  80:	02010413          	add	s0,sp,32
  84:	fea42623          	sw	a0,-20(s0)
  88:	fec42783          	lw	a5,-20(s0)
  8c:	00179793          	sll	a5,a5,0x1
  90:	00078513          	mv	a0,a5
  94:	01c12403          	lw	s0,28(sp)
  98:	02010113          	add	sp,sp,32
  9c:	00008067          	ret

000000a0 <main>:
  a0:	fe010113          	add	sp,sp,-32
  a4:	00112e23          	sw	ra,28(sp)
  a8:	00812c23          	sw	s0,24(sp)
  ac:	02010413          	add	s0,sp,32
  b0:	fe042423          	sw	zero,-24(s0)
  b4:	fe042623          	sw	zero,-20(s0)
  b8:	0280006f          	j	e0 <main+0x40>
  bc:	fec42503          	lw	a0,-20(s0)
  c0:	fb9ff0ef          	jal	78 <dble>
  c4:	00050713          	mv	a4,a0
  c8:	fe842783          	lw	a5,-24(s0)
  cc:	00f707b3          	add	a5,a4,a5
  d0:	fef42423          	sw	a5,-24(s0)
  d4:	fec42783          	lw	a5,-20(s0)
  d8:	00178793          	add	a5,a5,1
  dc:	fef42623          	sw	a5,-20(s0)
  e0:	fec42703          	lw	a4,-20(s0)
  e4:	00900793          	li	a5,9
  e8:	fce7dae3          	bge	a5,a4,bc <main+0x1c>
  ec:	fe842783          	lw	a5,-24(s0)
  f0:	00078513          	mv	a0,a5
  f4:	f25ff0ef          	jal	18 <printInt>
  f8:	00100793          	li	a5,1
  fc:	00078513          	mv	a0,a5
 100:	01c12083          	lw	ra,28(sp)
 104:	01812403          	lw	s0,24(sp)
 108:	02010113          	add	sp,sp,32
 10c:	00008067          	ret

Disassembly of section .data:

00010000 <nums>:
   10000:	0001                	.2byte	0x1
   10002:	0000                	.2byte	0x0
   10004:	0002                	.2byte	0x2
   10006:	0000                	.2byte	0x0
   10008:	0004                	.2byte	0x4
   1000a:	0000                	.2byte	0x0
   1000c:	0006                	.2byte	0x6
	...

00010010 <_stack_start>:
   10010:	00000007          	.4byte	0x7
   10014:	0009                	.2byte	0x9
   10016:	0000                	.2byte	0x0
   10018:	00000007          	.4byte	0x7
   1001c:	0000000b          	.4byte	0xb
   10020:	000d                	.2byte	0xd
   10022:	0000                	.2byte	0x0
   10024:	0011                	.2byte	0x11
	...

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
