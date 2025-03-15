		.section .text
		.align 2
		.global _start


_start:
	li t0, 0xfffffffe
	li t1, 0x0
	li t2, -6
	li t3, 0x10
	li a0, 31
	li a1, 0
	li a2, 5
	li a3, 33
	li a4, -7
	li s0, 1
	sll s0, t0, a0
	sll s1, t1, a2
	sll s2, t2, a2
	sll s3, t3, a2
	sll s4, t0, a3
	sll s5, t0, a4
	jr ra
