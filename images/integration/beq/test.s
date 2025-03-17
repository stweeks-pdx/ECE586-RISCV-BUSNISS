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
        j .begin

.misalign:
        beq t1, t0, mem_loc_2
        mem_loc_1: .half 0x0
        mem_loc_2: .half 0x0
        jr ra

.begin:
        beq t0, t1, .L1
        beq t1, t0, .L2
        beq t0, t4, .L3
        beq t2, t0, .L4
        beq t0, t2, .L5
        j .misalign

.L1:
        addi s0, s0, -1
        beq t1, t0, .L2
        beq t0, t4, .L3
        beq t2, t0, .L4
        beq t0, t2, .L5
        j .misalign

.L2:
        addi s0, s0, -1
        beq t0, t4, .L3
        beq t2, t0, .L4
        beq t0, t2, .L5
        j .misalign

.L3:
        addi s0, s0, 1
        beq t2, t0, .L4
        beq t0, t2, .L5
        j .misalign

.L4:
        addi s0, s0, -1
        beq t0, t2, .L5
        j .misalign

.L5:
        addi s0, s0, -1
        j .misalign

