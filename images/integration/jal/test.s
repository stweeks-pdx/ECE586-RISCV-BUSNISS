		.section .text
		.align 2
		.global _start

.l2:
	li s0, 0x7ee
	jal t0, 0x008
	jr ra
_start:
	
	jal t0, .l2
	jr ra


