
t3.elf:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <_start>:
   0:	00010117          	auipc	sp,0x10
   4:	01010113          	add	sp,sp,16 # 10010 <_stack_start>
   8:	28ad                	jal	82 <main>

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

0000004e <sum>:
  4e:	1101                	add	sp,sp,-32
  50:	ce06                	sw	ra,28(sp)
  52:	cc22                	sw	s0,24(sp)
  54:	1000                	add	s0,sp,32
  56:	fea42623          	sw	a0,-20(s0)
  5a:	fec42783          	lw	a5,-20(s0)
  5e:	cb99                	beqz	a5,74 <sum+0x26>
  60:	fec42783          	lw	a5,-20(s0)
  64:	17fd                	add	a5,a5,-1
  66:	853e                	mv	a0,a5
  68:	37dd                	jal	4e <sum>
  6a:	872a                	mv	a4,a0
  6c:	fec42783          	lw	a5,-20(s0)
  70:	97ba                	add	a5,a5,a4
  72:	a019                	j	78 <sum+0x2a>
  74:	fec42783          	lw	a5,-20(s0)
  78:	853e                	mv	a0,a5
  7a:	40f2                	lw	ra,28(sp)
  7c:	4462                	lw	s0,24(sp)
  7e:	6105                	add	sp,sp,32
  80:	8082                	ret

00000082 <main>:
  82:	1101                	add	sp,sp,-32
  84:	ce06                	sw	ra,28(sp)
  86:	cc22                	sw	s0,24(sp)
  88:	1000                	add	s0,sp,32
  8a:	4551                	li	a0,20
  8c:	37c9                	jal	4e <sum>
  8e:	fea42623          	sw	a0,-20(s0)
  92:	fec42503          	lw	a0,-20(s0)
  96:	3fb5                	jal	12 <printInt>
  98:	4785                	li	a5,1
  9a:	853e                	mv	a0,a5
  9c:	40f2                	lw	ra,28(sp)
  9e:	4462                	lw	s0,24(sp)
  a0:	6105                	add	sp,sp,32
  a2:	8082                	ret

Disassembly of section .riscv.attributes:

00000000 <.riscv.attributes>:
   0:	2041                	jal	80 <sum+0x32>
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
