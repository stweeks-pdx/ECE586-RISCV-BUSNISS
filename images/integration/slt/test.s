	.section .text
	.align 2
	.global _start
	
	.equ spn, 50
	.equ bpn, 100
	.equ snn, -300
	.equ bnn, -50


_start:
	mv	ra, zero
	li	t0, spn
	li	t1, bpn
	li	t2, snn
	li	t3, bnn
	li	t4, 0 
	li	t5, 0 
	li	t6, 0 
	li	s1, 0 
	li	s2, 1
	li	s3, 1
	li 	s4, 1
	li	s5, 1
	li	s6, 1
	li	s7, 1
 	slt	t4, t0, t1
	slt	t5, t2, t3
	slt	t6, t3, t0
	slt	s1, zero, t0
	slt	s2, t1, t0
	slt	s3, t3, t2
	slt	s4, t1, t1
	slt 	s5, zero, zero
	slt	s6, t0, t2
	slt	s7, t1, zero
	jr	ra
		
