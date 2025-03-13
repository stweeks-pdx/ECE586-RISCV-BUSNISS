	.section .text
	.align 2
	.global _start
	
	.equ A, 300
	.equ notA, -301
	.equ allA, 0xAAA
	.equ all5, 0x555

_start:	
	mv	ra, zero
	li	t0, A
	li	t1, notA
	li	t2, allA
	li	t3, all5
	xor	t4, t0, t1
	xor	t5, t0, t0
	xor	t6, t0, t2
	xor	s1, t0, t3
	jr	ra
	
