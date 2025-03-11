	.section .text
	.align 2
	.global _start
	.equ posNum, 0x77777
	.equ negNum, 0x80000

_start:
	mv 	ra, zero
	auipc	t0, posNum
	auipc	t1, negNum
	jr 	ra	
