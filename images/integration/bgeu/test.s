		.section .text
		.align 2
		.global _start

_start:
	li t0, 3
	li t1, 4
	li t2, -3
	li t3, -4
	li t4, 3
	li s0, 0

	bgeu t0, t1, .L1
	bgeu t1, t0, .L2
	bgeu t0, t4, .L3
	bgeu t2, t0, .L4
	bgeu t0, t2, .L5
	jr ra

.L1:
	addi s0, s0, -1
	bgeu t1, t0, .L2
	bgeu t0, t4, .L3
	bgeu t2, t0, .L4
	bgeu t0, t2, .L5
	jr ra

.L2:
	addi s0, s0, 1
	bgeu t0, t4, .L3
	bgeu t2, t0, .L4
	bgeu t0, t2, .L5
	jr ra

.L3:
	addi s0, s0, 1
	bgeu t2, t0, .L4
	bgeu t0, t2, .L5
	jr ra

.L4:
	addi s0, s0, 1
	bgeu t0, t2, .L5
	jr ra

.L5:
	addi s0, s0, -1
	jr ra
