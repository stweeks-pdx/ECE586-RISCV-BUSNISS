	.section .text
	.align 2
	.global _start
	.equ posNum, 0x78ABE
	.equ negNum, 0x8B23D

_start:
	mv	ra, zero
	lui	t0, posNum
	lui 	t1, negNum	
	jr	ra
