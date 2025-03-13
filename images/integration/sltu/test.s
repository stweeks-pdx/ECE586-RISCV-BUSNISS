	.section .text
	.align 2
	.global _start
	
	.equ bpn, 200
	.equ spn, 50
	.equ snn, -50
	.equ bnn, -200

_start:
	mv	ra, zero	
	li	t0, bpn
	li	t1, spn
	li	t2, snn
	li 	t3, bnn
	li	t4, 0
	li 	t5, 0
	li	t6, 0
	li	s1, 1
	li	s2, 1
	li	s3, 1
	li	s4, 1
	li	s5, 1
	li	s6, 1
	li	s7, 0
	sltu	t4, t1, t0
	sltu	t5, t3, t2
	sltu	t6, t1, t2
	sltu	s1, t0, t1
	sltu	s2, t2, t3
	sltu	s3, t3, t1
	sltu	s4, t0, t0
	sltu	s5, zero, zero
	snez	s6, zero
	snez	s7, t1 
	jr	ra
