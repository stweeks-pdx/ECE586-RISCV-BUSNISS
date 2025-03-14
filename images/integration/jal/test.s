		.section .text
		.align 2
		.global _start

_start:
	li t0, 0x5
	jal t0, .l2
	li s2, 0xfeef
	jal t1, 0x2
	jr ra

.l3:
	li s0, 0xdeadbeef
	jr t1

.l2:
	li s1, 0xbeefdead
	jal t1, .l3
	jr t0


