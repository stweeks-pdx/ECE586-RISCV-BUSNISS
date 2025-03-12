		.section .text
			.align 2
			.global _start
			.equ tc1, 0x7fffffff
			.equ tc2, 0
			.equ tc4, 45

_start:
	mv ra, zero
	li t0, tc1 #load a large number for test cases 1 and 3
	li t3, tc2 #load 0 for test case 2
	li t5, tc4 #load an arbitrary positive integer for test case 4
	srli t1, t0, 31 #test case 1
	srli t2, t0, 8 #test case 3
	srli t4, t3, 0 #test case 2
	srli t6, t5, 3 #test case 4
	srli a0, t3, 29 #shift 0 by some number
	srli a1, t5, 0 #shift a number by 0
	jr ra
