
t5.elf:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00010117          	auipc	sp,0x10
   4:	01010113          	add	sp,sp,16 # 10010 <_stack_start>
   8:	2099                	jal	4e <main>

0000000a <loop>:
   a:	48a9                	li	a7,10
   c:	00000073          	ecall
  10:	bfed                	j	a <loop>

00000012 <printInt>:
  12:	1101                	add	sp,sp,-32
  14:	ce22                	sw	s0,28(sp)
  16:	1000                	add	s0,sp,32
  18:	fea42623          	sw	a0,-20(s0)
  1c:	4885                	li	a7,1
  1e:	853e                	mv	a0,a5
  20:	fef42623          	sw	a5,-20(s0)
  24:	00000073          	ecall
  28:	0001                	nop
  2a:	4472                	lw	s0,28(sp)
  2c:	6105                	add	sp,sp,32
  2e:	8082                	ret

00000030 <printString>:
  30:	1101                	add	sp,sp,-32
  32:	ce22                	sw	s0,28(sp)
  34:	1000                	add	s0,sp,32
  36:	fea42623          	sw	a0,-20(s0)
  3a:	4891                	li	a7,4
  3c:	853e                	mv	a0,a5
  3e:	fef42623          	sw	a5,-20(s0)
  42:	00000073          	ecall
  46:	0001                	nop
  48:	4472                	lw	s0,28(sp)
  4a:	6105                	add	sp,sp,32
  4c:	8082                	ret

0000004e <main>:
  4e:	7179                	add	sp,sp,-48
  50:	d606                	sw	ra,44(sp)
  52:	d422                	sw	s0,40(sp)
  54:	1800                	add	s0,sp,48
  56:	0d000793          	li	a5,208
  5a:	438c                	lw	a1,0(a5)
  5c:	43d0                	lw	a2,4(a5)
  5e:	4794                	lw	a3,8(a5)
  60:	47d8                	lw	a4,12(a5)
  62:	fcb42c23          	sw	a1,-40(s0)
  66:	fcc42e23          	sw	a2,-36(s0)
  6a:	fed42023          	sw	a3,-32(s0)
  6e:	fee42223          	sw	a4,-28(s0)
  72:	0107d703          	lhu	a4,16(a5)
  76:	fee41423          	sh	a4,-24(s0)
  7a:	0127c783          	lbu	a5,18(a5)
  7e:	fef40523          	sb	a5,-22(s0)
  82:	fe042623          	sw	zero,-20(s0)
  86:	a031                	j	92 <main+0x44>
  88:	fec42783          	lw	a5,-20(s0)
  8c:	0785                	add	a5,a5,1
  8e:	fef42623          	sw	a5,-20(s0)
  92:	fec42783          	lw	a5,-20(s0)
  96:	17c1                	add	a5,a5,-16
  98:	97a2                	add	a5,a5,s0
  9a:	fe87c783          	lbu	a5,-24(a5)
  9e:	f7ed                	bnez	a5,88 <main+0x3a>
  a0:	0b800513          	li	a0,184
  a4:	3771                	jal	30 <printString>
  a6:	fec42503          	lw	a0,-20(s0)
  aa:	37a5                	jal	12 <printInt>
  ac:	4781                	li	a5,0
  ae:	853e                	mv	a0,a5
  b0:	50b2                	lw	ra,44(sp)
  b2:	5422                	lw	s0,40(sp)
  b4:	6145                	add	sp,sp,48
  b6:	8082                	ret

Disassembly of section .rodata:

000000b8 <_end-0x2b>:
  b8:	654c                	.2byte	0x654c
  ba:	676e                	.2byte	0x676e
  bc:	6874                	.2byte	0x6874
  be:	6f20                	.2byte	0x6f20
  c0:	2066                	.2byte	0x2066
  c2:	6874                	.2byte	0x6874
  c4:	2065                	jal	16c <_end+0x89>
  c6:	69727473          	.4byte	0x69727473
  ca:	676e                	.2byte	0x676e
  cc:	203a                	.2byte	0x203a
  ce:	0000                	unimp
  d0:	7250                	.2byte	0x7250
  d2:	6172676f          	jal	a4,26ee8 <_stack_start+0x16ed8>
  d6:	6d6d                	lui	s10,0x1b
  d8:	6e69                	lui	t3,0x1a
  da:	73692067          	.4byte	0x73692067
  de:	6620                	.2byte	0x6620
  e0:	6e75                	lui	t3,0x1d
	...

Disassembly of section .riscv.attributes:

00000000 <.riscv.attributes>:
   0:	2041                	jal	80 <main+0x32>
   2:	0000                	unimp
   4:	7200                	.2byte	0x7200
   6:	7369                	lui	t1,0xffffa
   8:	01007663          	bgeu	zero,a6,14 <printInt+0x2>
   c:	0016                	c.slli	zero,0x5
   e:	0000                	unimp
  10:	1004                	add	s1,sp,32
  12:	7205                	lui	tp,0xfffe1
  14:	3376                	.2byte	0x3376
  16:	6932                	.2byte	0x6932
  18:	7032                	.2byte	0x7032
  1a:	5f31                	li	t5,-20
  1c:	30703263          	.4byte	0x30703263
	...

Disassembly of section .comment:

00000000 <.comment>:
   0:	3a434347          	.4byte	0x3a434347
   4:	2820                	.2byte	0x2820
   6:	65653267          	.4byte	0x65653267
   a:	6535                	lui	a0,0xd
   c:	3334                	.2byte	0x3334
   e:	3030                	.2byte	0x3030
  10:	3831                	jal	fffff82c <_stack_start+0xfffef81c>
  12:	642d                	lui	s0,0xb
  14:	7269                	lui	tp,0xffffa
  16:	7974                	.2byte	0x7974
  18:	2029                	jal	22 <printInt+0x10>
  1a:	3231                	jal	fffff926 <_stack_start+0xfffef916>
  1c:	322e                	.2byte	0x322e
  1e:	302e                	.2byte	0x302e
	...
