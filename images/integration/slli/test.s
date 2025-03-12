	.section .text
		.align 2
		.global _start
		.equ tc1, 0xfffffffe
		.equ tc2, 0
		.equ tc3, -21
		.equ tc4, 21
		.equ ms, 31 #maximum shift amount
		.equ ls, 14 #arbitrary shift amount

_start:
	mv ra, zero
	li t0, tc1 #load number to be shifted until it is equal to 0
	li s0, tc2 #load 0 to be shifted
	li a0, tc3 #load negative number to be shifted
	li t3, tc4 #load positive number to be shifted
	slli t1, t0, 31 #shift until 0
	slli s1, s0, 31 #shift 0 as much as possible, should still be 0
	slli a1, a0, 14 #shift a negative number
	slli t4, t3, 14 #shift a positive number
	slli t5, t3, 0 #shift a positive number by 0
	slli s2, s0, 0 #shift 0 by 0
	jr ra
