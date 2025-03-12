	.section .text
		.align 2
		.global _start
		.equ nco, 0x000 #no change OR
		.equ sao, -1 #OR to set all bits
		.equ tc3, -1366 #mask for test case 3
		.equ tc4, 0x555 #mask for test case 4

_start:
	li t0, tc3
	li a0, tc4
	ori t1, t0, nco
	ori a1, a0, sao
	ori t2, t0, tc4
	ori a2, a0, tc3
	jr ra
