		.section .text
			.align 2
			.global _start
			.equ nca, 0 #Add that has no change
			.equ tc3, -25 #test case 3
			.equ tc4, -20 #test case 4
			.equ tc5, 20 #test case 5

_start:
	li t0, 25 #Load A into register t0
	li a0, tc3 #Load -A into register a0
	mv a1, a0 #test case 8, a1 = a0
	addi t1, t0, nca #test case 1, a+0=a
	addi a2, a0, nca #test case 2, -a+0=-a
	addi t2, t0, tc3 #t2 = a+-a=0
	addi t3, t0, tc4 #t3 = a+-b (should be 5)
	addi t4, t0, tc5 #t4 = a+b (should be 0x2d)
	addi a3, a0, tc4 #a3 = -a+-b (should be -45, or 0xffffffd3)
	NOP
	jr ra 
