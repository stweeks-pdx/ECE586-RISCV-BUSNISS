	.section .text
	.align 2
	.global _start
	.equ all1, 0xffffffff
_start:
	mv	ra,zero
	la	s2,var
	li	t0,all1
	mv	t1,zero
	lb	t0,0(s2)
	lb	t1,1(s2)
	li	t2,all1
	lbu	t2,3(s2)
	li	t3,all1
	mv	t4,zero
	li	t5,all1
	lh	t3,1(s2)
	lh	t4,0(s2)
	lhu	t5,2(s2)
	li	t6,all1
	lw	t6,0(s2)
	jr	ra


var: .word 0x9A658A75
