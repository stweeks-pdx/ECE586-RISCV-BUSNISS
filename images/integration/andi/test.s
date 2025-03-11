	.section .text
		.align 2
		.global _start
		.equ caa, 0x000 #clear all AND
		.equ nca, -1 #no change AND
		.equ tc3, -1366 #mask for test case 3
		.equ tc4, 0x555 #mask for test case 4

_start:
	li t0, 0x7BB
	andi t1, t0, caa
	andi t2, t0, nca
	andi s0, t0, tc3
	andi s1, t0, tc4
	jr ra
