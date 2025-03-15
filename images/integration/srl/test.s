		.section .text
		.align 2
		.global _start

_start:
	li t0, 0x7fffffff
	li t1, 0
	li t2, -1
	li a0, 31
	li a1, 4
	li a2, 33
	li a3, -7
	li s1, 0x50
	srl s0, t0, a0
	srl s1, t1, a1
	srl s2, t2, a1
	srl s3, t0, a1
	srl s4, t0, a2
	srl s5, t0, a3
	jr ra
