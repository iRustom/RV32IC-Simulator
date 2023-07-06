
t4.elf:     file format elf32-littleriscv


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
  4e:	1101                	add	sp,sp,-32
  50:	ce06                	sw	ra,28(sp)
  52:	cc22                	sw	s0,24(sp)
  54:	1000                	add	s0,sp,32
  56:	fe042623          	sw	zero,-20(s0)
  5a:	a031                	j	66 <main+0x18>
  5c:	fec42783          	lw	a5,-20(s0)
  60:	0785                	add	a5,a5,1
  62:	fef42623          	sw	a5,-20(s0)
  66:	67c1                	lui	a5,0x10
  68:	00078713          	mv	a4,a5
  6c:	fec42783          	lw	a5,-20(s0)
  70:	97ba                	add	a5,a5,a4
  72:	0007c783          	lbu	a5,0(a5) # 10000 <s1>
  76:	f3fd                	bnez	a5,5c <main+0xe>
  78:	fe042423          	sw	zero,-24(s0)
  7c:	a81d                	j	b2 <main+0x64>
  7e:	67c1                	lui	a5,0x10
  80:	06478713          	add	a4,a5,100 # 10064 <s2>
  84:	fe842783          	lw	a5,-24(s0)
  88:	97ba                	add	a5,a5,a4
  8a:	0007c703          	lbu	a4,0(a5)
  8e:	67c1                	lui	a5,0x10
  90:	00078693          	mv	a3,a5
  94:	fec42783          	lw	a5,-20(s0)
  98:	97b6                	add	a5,a5,a3
  9a:	00e78023          	sb	a4,0(a5) # 10000 <s1>
  9e:	fe842783          	lw	a5,-24(s0)
  a2:	0785                	add	a5,a5,1
  a4:	fef42423          	sw	a5,-24(s0)
  a8:	fec42783          	lw	a5,-20(s0)
  ac:	0785                	add	a5,a5,1
  ae:	fef42623          	sw	a5,-20(s0)
  b2:	67c1                	lui	a5,0x10
  b4:	06478713          	add	a4,a5,100 # 10064 <s2>
  b8:	fe842783          	lw	a5,-24(s0)
  bc:	97ba                	add	a5,a5,a4
  be:	0007c783          	lbu	a5,0(a5)
  c2:	ffd5                	bnez	a5,7e <main+0x30>
  c4:	67c1                	lui	a5,0x10
  c6:	00078713          	mv	a4,a5
  ca:	fec42783          	lw	a5,-20(s0)
  ce:	97ba                	add	a5,a5,a4
  d0:	00078023          	sb	zero,0(a5) # 10000 <s1>
  d4:	0f000513          	li	a0,240
  d8:	3fa1                	jal	30 <printString>
  da:	67c1                	lui	a5,0x10
  dc:	00078513          	mv	a0,a5
  e0:	3f81                	jal	30 <printString>
  e2:	4785                	li	a5,1
  e4:	853e                	mv	a0,a5
  e6:	40f2                	lw	ra,28(sp)
  e8:	4462                	lw	s0,24(sp)
  ea:	6105                	add	sp,sp,32
  ec:	8082                	ret

Disassembly of section .rodata:

000000f0 <.rodata>:
  f0:	6641                	lui	a2,0x10
  f2:	6574                	.2byte	0x6574
  f4:	2072                	.2byte	0x2072
  f6:	636e6f63          	bltu	t3,s6,734 <main+0x6e6>
  fa:	7461                	lui	s0,0xffff8
  fc:	6e65                	lui	t3,0x19
  fe:	7461                	lui	s0,0xffff8
 100:	6f69                	lui	t5,0x1a
 102:	3a6e                	.2byte	0x3a6e
 104:	0020                	add	s0,sp,8

Disassembly of section .data:

00010000 <s1>:
   10000:	7270                	.2byte	0x7270
   10002:	6172676f          	jal	a4,36e18 <_end+0x26da9>
   10006:	6d6d                	lui	s10,0x1b
   10008:	6e69                	lui	t3,0x1a
   1000a:	00002067          	.4byte	0x2067
	...

00010010 <_stack_start>:
	...

00010064 <s2>:
   10064:	7369                	lui	t1,0xffffa
   10066:	6120                	.2byte	0x6120
   10068:	6f736577          	.4byte	0x6f736577
   1006c:	656d                	lui	a0,0x1b
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
  10:	3831                	jal	fffff82c <_end+0xfffef7bd>
  12:	642d                	lui	s0,0xb
  14:	7269                	lui	tp,0xffffa
  16:	7974                	.2byte	0x7974
  18:	2029                	jal	22 <printInt+0x10>
  1a:	3231                	jal	fffff926 <_end+0xfffef8b7>
  1c:	322e                	.2byte	0x322e
  1e:	302e                	.2byte	0x302e
	...
