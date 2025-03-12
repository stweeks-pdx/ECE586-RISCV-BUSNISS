	.section .text
		.align 2
		.global _start
		.equ ssr, 0x0E
		.equ bsr, 0x77
		.equ nsr, 0xFFD
		.equ ps, 0x55555555
		.equ ns, 0x80000000

_start:
	mv 	ra, zero
	li	 t0, ps #Load positive shift subject into t0
	li	 t3, ns #Load negative shift subject into t3
	srai	 t0, t0, 0 #0 shift
	srai	 t1, t0, ssr #Shift by less than 31
#	srai	 t2, t0, bsr #Shift by more than 31, should shift by 25
	srai	 t3, t3, 0 #0 shift a negative
	srai	 t4, t3, ssr #small shift a negative number
#	srai	 t5, t3, bsr #big shift a negative number, should shift by 25
#	srai	 t6, t3, nsr #shift a number by a negative number, should shift by 30
	jr	ra
