	.section .text
	.align 2
	.global _start
	.equ all5, 0x555
	.equ alla, 0xAA

_start:
	mv	ra, zero
	li 	t0, 133
	xori 	t1, t0, 133	#XOR t0 with itself
	xori 	t2, t0, -134	#XOR t0 with its complement
	li	t3, 100
	not	t4, t0
	xori	t5, t3, alla 
	xori	t6, t3, all5
	jr	ra

