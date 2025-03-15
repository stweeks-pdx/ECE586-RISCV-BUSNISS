		.section .text
		.align 2
		.global _start

_start:
	li t0, 0
	li t1, 0x10101010
	li t2, 0xf0707070
	li t3, 0xffffffff
	li a0, 3
	li a1, 33
	li a2, -7
	li s0, 0xffffffff
	sra s0, t0, a0
	sra s1, t1, a0
	sra s2, t2, a0
	sra s3, t1, a1
	sra s4, t3, a0
	sra s5, t1, a2
	jr ra
