		.section .text
		.align 2
		.global _start

_start:
	la a0, .l2
	addi a0, a0, -4
	la a1, .l3
	addi a1, a1, -4
	jalr t0, a0, 4
	li s2, 0xdeadbeef
	li t2, 0x2
	li t3, 0x1
	jalr zero, t2, 0
	jr ra

.l3:
	li s0, 0xdead
	jr t1

.l2:
	li s1, 0xbeef
	jalr t1, a1, 4
	jr t0
