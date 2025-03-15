		.section .text
		.align 2
		.global _start


_start:
	li t0, 10
	li t1, -5
	li t2, 0
	li s0, 1
	li s1, 1
	li s2, 1
	li s3, 1
	li s4, 1
	li s5, 1
	sltiu a0, t0, 11
	sltiu a1, t1, -4
	sltiu a2, t0, -4
	seqz a3, t2
	sltiu s0, t0, 9
	sltiu s1, t1, 10
	sltiu s2, t0, 10
	sltiu s3, t2, 0
	sltiu s4, t1, -6
	seqz s5, t0
	jr ra
