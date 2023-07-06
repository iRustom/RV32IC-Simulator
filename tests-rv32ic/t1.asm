
t1.elf:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00010117          	auipc	sp,0x10
   4:	01010113          	add	sp,sp,16 # 10010 <_stack_start>
   8:	28b9                	jal	66 <main>

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

0000004e <dble>:
  4e:	1101                	add	sp,sp,-32
  50:	ce22                	sw	s0,28(sp)
  52:	1000                	add	s0,sp,32
  54:	fea42623          	sw	a0,-20(s0)
  58:	fec42783          	lw	a5,-20(s0)
  5c:	0786                	sll	a5,a5,0x1
  5e:	853e                	mv	a0,a5
  60:	4472                	lw	s0,28(sp)
  62:	6105                	add	sp,sp,32
  64:	8082                	ret

00000066 <main>:
  66:	1101                	add	sp,sp,-32
  68:	ce06                	sw	ra,28(sp)
  6a:	cc22                	sw	s0,24(sp)
  6c:	1000                	add	s0,sp,32
  6e:	fe042423          	sw	zero,-24(s0)
  72:	fe042623          	sw	zero,-20(s0)
  76:	a839                	j	94 <main+0x2e>
  78:	fec42503          	lw	a0,-20(s0)
  7c:	3fc9                	jal	4e <dble>
  7e:	872a                	mv	a4,a0
  80:	fe842783          	lw	a5,-24(s0)
  84:	97ba                	add	a5,a5,a4
  86:	fef42423          	sw	a5,-24(s0)
  8a:	fec42783          	lw	a5,-20(s0)
  8e:	0785                	add	a5,a5,1
  90:	fef42623          	sw	a5,-20(s0)
  94:	fec42703          	lw	a4,-20(s0)
  98:	47a5                	li	a5,9
  9a:	fce7dfe3          	bge	a5,a4,78 <main+0x12>
  9e:	fe842783          	lw	a5,-24(s0)
  a2:	853e                	mv	a0,a5
  a4:	37bd                	jal	12 <printInt>
  a6:	4785                	li	a5,1
  a8:	853e                	mv	a0,a5
  aa:	40f2                	lw	ra,28(sp)
  ac:	4462                	lw	s0,24(sp)
  ae:	6105                	add	sp,sp,32
  b0:	8082                	ret

Disassembly of section .data:

00010000 <nums>:
   10000:	0001                	nop
   10002:	0000                	unimp
   10004:	0002                	c.slli64	zero
   10006:	0000                	unimp
   10008:	0004                	.2byte	0x4
   1000a:	0000                	unimp
   1000c:	0006                	c.slli	zero,0x1
	...

00010010 <_stack_start>:
   10010:	00000007          	.4byte	0x7
   10014:	0009                	c.nop	2
   10016:	0000                	unimp
   10018:	00000007          	.4byte	0x7
   1001c:	0000000b          	.4byte	0xb
   10020:	000d                	c.nop	3
   10022:	0000                	unimp
   10024:	0011                	c.nop	4
	...

Disassembly of section .riscv.attributes:

00000000 <.riscv.attributes>:
   0:	2041                	jal	80 <main+0x1a>
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
  10:	3831                	jal	fffff82c <_end+0xfffef804>
  12:	642d                	lui	s0,0xb
  14:	7269                	lui	tp,0xffffa
  16:	7974                	.2byte	0x7974
  18:	2029                	jal	22 <printInt+0x10>
  1a:	3231                	jal	fffff926 <_end+0xfffef8fe>
  1c:	322e                	.2byte	0x322e
  1e:	302e                	.2byte	0x302e
	...
