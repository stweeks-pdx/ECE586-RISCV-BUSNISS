		.section .text
		.align 2
		.global _start
		.equ posi, 15 #positive immediate
		.equ negi, -15 #negative immediate

_start:
	li t0, 14
	li t1, -14
	li t2, -16
	li t3, 16
	li t4, -15
	li t5, 15
	li t6, 0
	li s0, 1
	li s1, 1
	li s2, 1
	li s3, 1
	li s4, 1
	li s5, 1
	li s6, 1
	slti a0, t0, posi #test case 1
	slti a1, t2, negi #test case 2
	slti a2, t1, posi #test case 3
	slti a3, t6, posi #test case 4
	slti s0, t3, posi #test case 5
	slti s1, t1, negi #test case 6
	slti s2, t0, negi #test case 7
	slti s3, t0, 0	  #test case 8
	slti s4, t5, posi #test case 9
	slti s5, t6, 0 	  #test case 10
	slti s6, t4, negi #test case 9, but negative
	jr ra
