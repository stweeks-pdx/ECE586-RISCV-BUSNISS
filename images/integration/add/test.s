	.section .text
	.align 2
	.global _start
	
	.equ posNum, 100
	.equ negNum, -225
	.equ recipNum, -100
		 

_start:
	mv	ra, zero
	li	t0, posNum
	li	t1, negNum
	li	t2, recipNum
	add	s1, t0, zero
	add	s2, t1, zero
	add	s3, t0, t2
	add	t3, t0, t1
	add	t4, t0, t0
	add	t5, t1, t1
	jr 	ra	
	
