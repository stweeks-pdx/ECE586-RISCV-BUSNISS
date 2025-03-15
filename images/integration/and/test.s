	.section .text
	.align 2
	.global _start
	
	.equ	all0, 0
	.equ	allF, 0xFFFFFFFF
	.equ	allA, 0xAAAAAAAA
	.equ	all5, 0x55555555
	.equ	A, 0x7734BCE1

_start:
	mv	ra, zero
	li	t0, all0
	li	t1, allF
	li	t2, allA
	li	t3, all5
	li	t4, A
	and	t5, t4, t0
	and	t6, t4, t1
	and	s1, t4, t2
	and	s2, t4, t3 	
	jr	ra
