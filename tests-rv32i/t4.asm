
t4.elf:     file format elf32-littleriscv


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
  88:	fe042623          	sw	zero,-20(s0)
  8c:	0100006f          	j	9c <main+0x24>
  90:	fec42783          	lw	a5,-20(s0)
  94:	00178793          	add	a5,a5,1
  98:	fef42623          	sw	a5,-20(s0)
  9c:	000107b7          	lui	a5,0x10
  a0:	00078713          	mv	a4,a5
  a4:	fec42783          	lw	a5,-20(s0)
  a8:	00f707b3          	add	a5,a4,a5
  ac:	0007c783          	lbu	a5,0(a5) # 10000 <s1>
  b0:	fe0790e3          	bnez	a5,90 <main+0x18>
  b4:	fe042423          	sw	zero,-24(s0)
  b8:	0440006f          	j	fc <main+0x84>
  bc:	000107b7          	lui	a5,0x10
  c0:	06478713          	add	a4,a5,100 # 10064 <s2>
  c4:	fe842783          	lw	a5,-24(s0)
  c8:	00f707b3          	add	a5,a4,a5
  cc:	0007c703          	lbu	a4,0(a5)
  d0:	000107b7          	lui	a5,0x10
  d4:	00078693          	mv	a3,a5
  d8:	fec42783          	lw	a5,-20(s0)
  dc:	00f687b3          	add	a5,a3,a5
  e0:	00e78023          	sb	a4,0(a5) # 10000 <s1>
  e4:	fe842783          	lw	a5,-24(s0)
  e8:	00178793          	add	a5,a5,1
  ec:	fef42423          	sw	a5,-24(s0)
  f0:	fec42783          	lw	a5,-20(s0)
  f4:	00178793          	add	a5,a5,1
  f8:	fef42623          	sw	a5,-20(s0)
  fc:	000107b7          	lui	a5,0x10
 100:	06478713          	add	a4,a5,100 # 10064 <s2>
 104:	fe842783          	lw	a5,-24(s0)
 108:	00f707b3          	add	a5,a4,a5
 10c:	0007c783          	lbu	a5,0(a5)
 110:	fa0796e3          	bnez	a5,bc <main+0x44>
 114:	000107b7          	lui	a5,0x10
 118:	00078713          	mv	a4,a5
 11c:	fec42783          	lw	a5,-20(s0)
 120:	00f707b3          	add	a5,a4,a5
 124:	00078023          	sb	zero,0(a5) # 10000 <s1>
 128:	15400513          	li	a0,340
 12c:	f1dff0ef          	jal	48 <printString>
 130:	000107b7          	lui	a5,0x10
 134:	00078513          	mv	a0,a5
 138:	f11ff0ef          	jal	48 <printString>
 13c:	00100793          	li	a5,1
 140:	00078513          	mv	a0,a5
 144:	01c12083          	lw	ra,28(sp)
 148:	01812403          	lw	s0,24(sp)
 14c:	02010113          	add	sp,sp,32
 150:	00008067          	ret

Disassembly of section .rodata:

00000154 <.rodata>:
 154:	6641                	.2byte	0x6641
 156:	6574                	.2byte	0x6574
 158:	2072                	.2byte	0x2072
 15a:	636e6f63          	bltu	t3,s6,798 <main+0x720>
 15e:	7461                	.2byte	0x7461
 160:	6e65                	.2byte	0x6e65
 162:	7461                	.2byte	0x7461
 164:	6f69                	.2byte	0x6f69
 166:	3a6e                	.2byte	0x3a6e
 168:	0020                	.2byte	0x20

Disassembly of section .data:

00010000 <s1>:
   10000:	7270                	.2byte	0x7270
   10002:	6172676f          	jal	a4,36e18 <_end+0x26da9>
   10006:	6d6d                	.2byte	0x6d6d
   10008:	6e69                	.2byte	0x6e69
   1000a:	00002067          	.4byte	0x2067
	...

00010010 <_stack_start>:
	...

00010064 <s2>:
   10064:	7369                	.2byte	0x7369
   10066:	6120                	.2byte	0x6120
   10068:	6f736577          	.4byte	0x6f736577
   1006c:	656d                	.2byte	0x656d
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
