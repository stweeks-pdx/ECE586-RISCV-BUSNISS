		.section .text
		.align 2
		.global _start

_start:
	li t0, 5
	li t1, -5
	li t2, 9
	li t3, 3
	li t4, 0
	li a0, 4
	li a1, -4
	li a2, -1
	sub s0, t0, a0
	sub s1, t1, a1
	sub s2, t2, a2
	sub s3, t1, a0
	sub s4, t0, t1
	sub s5, t0, t4
	sub s6, t1, t4
	jr ra
