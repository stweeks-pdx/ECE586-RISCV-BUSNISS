	.section .text
	.align 2
	.global _start

_start:
	addi	sp,sp,-7
	li	ra,0
	li	t1,0x7f
	li	t2,0x88
	li	t3,0xA5A5A5A5
	sb	t1,6(sp)
	sh	t2,4(sp)
	sw	t3,0(sp)
	addi	sp,sp,-4
	sw	t1,0(sp)
	jr	ra
