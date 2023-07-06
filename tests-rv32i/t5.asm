
t5.elf:     file format elf32-littleriscv


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
  78:	fd010113          	add	sp,sp,-48
  7c:	02112623          	sw	ra,44(sp)
  80:	02812423          	sw	s0,40(sp)
  84:	03010413          	add	s0,sp,48
  88:	12400793          	li	a5,292
  8c:	0007a583          	lw	a1,0(a5)
  90:	0047a603          	lw	a2,4(a5)
  94:	0087a683          	lw	a3,8(a5)
  98:	00c7a703          	lw	a4,12(a5)
  9c:	fcb42c23          	sw	a1,-40(s0)
  a0:	fcc42e23          	sw	a2,-36(s0)
  a4:	fed42023          	sw	a3,-32(s0)
  a8:	fee42223          	sw	a4,-28(s0)
  ac:	0107d703          	lhu	a4,16(a5)
  b0:	fee41423          	sh	a4,-24(s0)
  b4:	0127c783          	lbu	a5,18(a5)
  b8:	fef40523          	sb	a5,-22(s0)
  bc:	fe042623          	sw	zero,-20(s0)
  c0:	0100006f          	j	d0 <main+0x58>
  c4:	fec42783          	lw	a5,-20(s0)
  c8:	00178793          	add	a5,a5,1
  cc:	fef42623          	sw	a5,-20(s0)
  d0:	fec42783          	lw	a5,-20(s0)
  d4:	ff078793          	add	a5,a5,-16
  d8:	008787b3          	add	a5,a5,s0
  dc:	fe87c783          	lbu	a5,-24(a5)
  e0:	fe0792e3          	bnez	a5,c4 <main+0x4c>
  e4:	10c00513          	li	a0,268
  e8:	f61ff0ef          	jal	48 <printString>
  ec:	fec42503          	lw	a0,-20(s0)
  f0:	f29ff0ef          	jal	18 <printInt>
  f4:	00000793          	li	a5,0
  f8:	00078513          	mv	a0,a5
  fc:	02c12083          	lw	ra,44(sp)
 100:	02812403          	lw	s0,40(sp)
 104:	03010113          	add	sp,sp,48
 108:	00008067          	ret

Disassembly of section .rodata:

0000010c <_end-0x2b>:
 10c:	654c                	.2byte	0x654c
 10e:	676e                	.2byte	0x676e
 110:	6874                	.2byte	0x6874
 112:	6f20                	.2byte	0x6f20
 114:	2066                	.2byte	0x2066
 116:	6874                	.2byte	0x6874
 118:	2065                	.2byte	0x2065
 11a:	69727473          	.4byte	0x69727473
 11e:	676e                	.2byte	0x676e
 120:	203a                	.2byte	0x203a
 122:	0000                	.2byte	0x0
 124:	7250                	.2byte	0x7250
 126:	6172676f          	jal	a4,26f3c <_stack_start+0x16f2c>
 12a:	6d6d                	.2byte	0x6d6d
 12c:	6e69                	.2byte	0x6e69
 12e:	73692067          	.4byte	0x73692067
 132:	6620                	.2byte	0x6620
 134:	6e75                	.2byte	0x6e75
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
