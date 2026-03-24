    .text
    .globl Food_better
    .type Food_better, @function
Food_better:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    lw t0, 12(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 16
    sw t0, 16(sp)
    lw t0, 16(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t1, 0(t0)
    sw t1, 28(sp)
    lw t0, 4(sp)
    addi t0, t0, 0
    sw t0, 32(sp)
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 36(sp)
    lw t0, 28(sp)
    lw t1, 36(sp)
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 40(sp)
    lw t0, 40(sp)
    bnez t0, .L73
    j .L96
.L73:
    lw t0, 0(sp)
    addi t0, t0, 4
    sw t0, 44(sp)
    lw t0, 44(sp)
    lw t1, 0(t0)
    sw t1, 48(sp)
    lw t0, 4(sp)
    addi t0, t0, 4
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t1, 0(t0)
    sw t1, 56(sp)
    lw t0, 48(sp)
    lw t1, 56(sp)
    slt t2, t0, t1
    sw t2, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L89
    j .L92
.L89:
    lw a0, 64(sp)
    j .L1
.L92:
    lw a0, 68(sp)
    j .L1
.L95:
    j .L118
.L96:
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 0(t0)
    sw t1, 76(sp)
    lw t0, 4(sp)
    addi t0, t0, 0
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 0(t0)
    sw t1, 84(sp)
    lw t0, 76(sp)
    lw t1, 84(sp)
    slt t2, t1, t0
    sw t2, 88(sp)
    lw t0, 88(sp)
    bnez t0, .L111
    j .L114
.L111:
    lw a0, 92(sp)
    j .L1
.L114:
    lw a0, 96(sp)
    j .L1
.L117:
    j .L118
.L118:
    li a0, 0
    j .L1
.L1:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl new_segt
    .type new_segt, @function
new_segt:
    addi sp, sp, -144
    sw ra, 140(sp)
    sw s0, 136(sp)
    addi s0, sp, 144
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 24
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 28
    sw t0, 32(sp)
    lw t0, 32(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    addi t0, sp, 36
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t1, 12(sp)
    sw t1, 0(t0)
    addi t0, sp, 44
    sw t0, 44(sp)
    lw t0, 44(sp)
    lw t1, 16(sp)
    sw t1, 0(t0)
    lw t0, 4(sp)
    lw t1, 0(t0)
    sw t1, 48(sp)
    lw t0, 48(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 52(sp)
    lw t0, 4(sp)
    lw t1, 52(sp)
    sw t1, 0(t0)
    lw t0, 4(sp)
    lw t1, 0(t0)
    sw t1, 56(sp)
    lw t0, 0(sp)
    lw t1, 56(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 88(sp)
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 92(sp)
    lw t0, 88(sp)
    addi t0, t0, 0
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 92(sp)
    sw t1, 0(t0)
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 100(sp)
    lw t0, 88(sp)
    addi t0, t0, 4
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 100(sp)
    sw t1, 0(t0)
    lw t0, 88(sp)
    addi t0, t0, 8
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 88(sp)
    addi t0, t0, 12
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 88(sp)
    addi t0, t0, 16
    sw t0, 116(sp)
    lw t0, 4(sp)
    lw t1, 0(t0)
    sw t1, 120(sp)
    lw a0, 120(sp)
    j .L2
.L2:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl build
    .type build, @function
build:
    addi sp, sp, -144
    sw ra, 140(sp)
    sw s0, 136(sp)
    addi s0, sp, 144
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    lw t0, 16(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 24
    sw t0, 28(sp)
    lw t0, 28(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    addi t0, sp, 32
    sw t0, 36(sp)
    lw t0, 36(sp)
    lw t1, 12(sp)
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 40(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 44(sp)
    lw t0, 40(sp)
    lw t1, 44(sp)
    slt t2, t1, t0
    sw t2, 48(sp)
    lw t0, 48(sp)
    bnez t0, .L172
    j .L174
.L172:
    li a0, 0
    j .L3
.L174:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 52(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 56(sp)
    lw t0, 52(sp)
    lw t1, 56(sp)
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L187
    j .L221
.L187:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 64(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 68(sp)
    addi t0, sp, 72
    sw t0, 80(sp)
    lw t0, 80(sp)
    addi t0, t0, 0
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 88(sp)
    lw t0, 80(sp)
    addi t0, t0, 4
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 88(sp)
    sw t1, 0(t0)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 64(sp)
    lw a3, 68(sp)
    lw a4, 80(sp)
    call new_segt
    sw a0, 96(sp)
    lw a0, 96(sp)
    j .L3
.L221:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 100(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 104(sp)
    addi t0, sp, 108
    sw t0, 116(sp)
    lw t0, 116(sp)
    addi t0, t0, 0
    sw t0, 120(sp)
    lw t0, 120(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 116(sp)
    addi t0, t0, 4
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 0
    sw t1, 0(t0)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 100(sp)
    lw a3, 104(sp)
    lw a4, 116(sp)
    call new_segt
    sw a0, 128(sp)
    lw a0, 128(sp)
    j .L3
.L3:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl update
    .type update, @function
update:
    addi sp, sp, -592
    sw ra, 588(sp)
    sw s0, 584(sp)
    addi s0, sp, 592
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 24
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 28
    sw t0, 32(sp)
    lw t0, 32(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    addi t0, sp, 36
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t1, 12(sp)
    sw t1, 0(t0)
    addi t0, sp, 44
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t1, 16(sp)
    sw t1, 0(t0)
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 52(sp)
    lw t0, 52(sp)
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L251
    j .L254
.L251:
    lw a0, 60(sp)
    j .L4
.L254:
    addi t0, sp, 64
    sw t0, 68(sp)
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 72(sp)
    lw t0, 0(sp)
    lw t1, 72(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    addi t0, t0, 0
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 0(t0)
    sw t1, 84(sp)
    lw t0, 68(sp)
    lw t1, 84(sp)
    sw t1, 0(t0)
    addi t0, sp, 88
    sw t0, 92(sp)
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 96(sp)
    lw t0, 0(sp)
    lw t1, 96(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    addi t0, t0, 4
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 0(t0)
    sw t1, 108(sp)
    lw t0, 92(sp)
    lw t1, 108(sp)
    sw t1, 0(t0)
    j .L281
.L281:
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 112(sp)
    lw t0, 68(sp)
    lw t1, 0(t0)
    sw t1, 116(sp)
    lw t0, 112(sp)
    lw t1, 116(sp)
    slt t2, t0, t1
    sw t2, 120(sp)
    li t1, 1
    sw t1, 124(sp)
    lw t0, 120(sp)
    bnez t0, .L302
    j .L291
.L291:
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 128(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 132(sp)
    lw t0, 128(sp)
    lw t1, 132(sp)
    slt t2, t1, t0
    sw t2, 136(sp)
    lw t1, 136(sp)
    sw t1, 124(sp)
    j .L302
.L302:
    lw t0, 124(sp)
    bnez t0, .L306
    j .L309
.L306:
    lw a0, 140(sp)
    j .L4
.L309:
    lw t0, 68(sp)
    lw t1, 0(t0)
    sw t1, 144(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 148(sp)
    lw t0, 144(sp)
    lw t1, 148(sp)
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 152(sp)
    lw t0, 152(sp)
    bnez t0, .L322
    j .L341
.L322:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 156(sp)
    lw t0, 0(sp)
    lw t1, 156(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 160(sp)
    lw t0, 160(sp)
    addi t0, t0, 16
    sw t0, 164(sp)
    lw t0, 164(sp)
    addi t0, t0, 0
    sw t0, 168(sp)
    lw t0, 48(sp)
    lw t1, 0(t0)
    sw t1, 172(sp)
    lw t0, 168(sp)
    lw t1, 0(t0)
    sw t1, 176(sp)
    lw t0, 176(sp)
    lw t1, 172(sp)
    add t2, t0, t1
    sw t2, 180(sp)
    lw t0, 168(sp)
    lw t1, 180(sp)
    sw t1, 0(t0)
    lw a0, 184(sp)
    j .L4
.L341:
    addi t0, sp, 188
    sw t0, 192(sp)
    lw t0, 68(sp)
    lw t1, 0(t0)
    sw t1, 196(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 200(sp)
    lw t0, 196(sp)
    lw t1, 200(sp)
    add t2, t0, t1
    sw t2, 204(sp)
    lw t0, 204(sp)
    li t1, 2
    div t2, t0, t1
    sw t2, 208(sp)
    lw t0, 192(sp)
    lw t1, 208(sp)
    sw t1, 0(t0)
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 212(sp)
    lw t0, 192(sp)
    lw t1, 0(t0)
    sw t1, 216(sp)
    lw t0, 212(sp)
    lw t1, 216(sp)
    slt t2, t1, t0
    xori t2, t2, 1
    sw t2, 220(sp)
    lw t0, 220(sp)
    bnez t0, .L369
    j .L423
.L369:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 224(sp)
    lw t0, 0(sp)
    lw t1, 224(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 228(sp)
    lw t0, 228(sp)
    addi t0, t0, 8
    sw t0, 232(sp)
    lw t0, 232(sp)
    lw t1, 0(t0)
    sw t1, 236(sp)
    lw t0, 236(sp)
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 240(sp)
    lw t0, 240(sp)
    bnez t0, .L385
    j .L406
.L385:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 244(sp)
    lw t0, 0(sp)
    lw t1, 244(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 248(sp)
    addi t0, t0, 8
    sw t0, 252(sp)
    lw t0, 68(sp)
    lw t1, 0(t0)
    sw t1, 256(sp)
    lw t0, 192(sp)
    lw t1, 0(t0)
    sw t1, 260(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 256(sp)
    lw a3, 260(sp)
    call build
    sw a0, 264(sp)
    lw t0, 252(sp)
    lw t1, 264(sp)
    sw t1, 0(t0)
    j .L406
.L406:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 268(sp)
    lw t0, 0(sp)
    lw t1, 268(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 272(sp)
    lw t0, 272(sp)
    addi t0, t0, 8
    sw t0, 276(sp)
    lw t0, 276(sp)
    lw t1, 0(t0)
    sw t1, 280(sp)
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 284(sp)
    lw t0, 48(sp)
    lw t1, 0(t0)
    sw t1, 288(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 280(sp)
    lw a3, 284(sp)
    lw a4, 288(sp)
    call update
    j .L481
.L423:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 292(sp)
    lw t0, 0(sp)
    lw t1, 292(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 296(sp)
    lw t0, 296(sp)
    addi t0, t0, 12
    sw t0, 300(sp)
    lw t0, 300(sp)
    lw t1, 0(t0)
    sw t1, 304(sp)
    lw t0, 304(sp)
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 308(sp)
    lw t0, 308(sp)
    bnez t0, .L439
    j .L464
.L439:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 312(sp)
    lw t0, 0(sp)
    lw t1, 312(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 316(sp)
    addi t0, t0, 12
    sw t0, 320(sp)
    lw t0, 192(sp)
    lw t1, 0(t0)
    sw t1, 324(sp)
    lw t0, 324(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 328(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 332(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 328(sp)
    lw a3, 332(sp)
    call build
    sw a0, 336(sp)
    lw t0, 320(sp)
    lw t1, 336(sp)
    sw t1, 0(t0)
    j .L464
.L464:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 340(sp)
    lw t0, 0(sp)
    lw t1, 340(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 344(sp)
    lw t0, 344(sp)
    addi t0, t0, 12
    sw t0, 348(sp)
    lw t0, 348(sp)
    lw t1, 0(t0)
    sw t1, 352(sp)
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 356(sp)
    lw t0, 48(sp)
    lw t1, 0(t0)
    sw t1, 360(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 352(sp)
    lw a3, 356(sp)
    lw a4, 360(sp)
    call update
    j .L481
.L481:
    addi t0, sp, 364
    sw t0, 372(sp)
    addi t0, sp, 376
    sw t0, 384(sp)
    lw t0, 384(sp)
    addi t0, t0, 0
    sw t0, 388(sp)
    lw t0, 388(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 384(sp)
    addi t0, t0, 4
    sw t0, 392(sp)
    lw t0, 392(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 396(sp)
    lw t0, 0(sp)
    lw t1, 396(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 400(sp)
    lw t0, 400(sp)
    addi t0, t0, 8
    sw t0, 404(sp)
    lw t0, 404(sp)
    lw t1, 0(t0)
    sw t1, 408(sp)
    lw t0, 408(sp)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    sw t2, 412(sp)
    lw t0, 412(sp)
    bnez t0, .L505
    j .L523
.L505:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 416(sp)
    lw t0, 0(sp)
    lw t1, 416(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 420(sp)
    addi t0, sp, 424
    sw t0, 432(sp)
    lw a0, 420(sp)
    lw a1, 0(sp)
    lw a2, 432(sp)
    call SegT_lc_val
    sw a0, 432(sp)
    addi t0, sp, 436
    sw t0, 444(sp)
    addi t0, sp, 448
    sw t0, 456(sp)
    addi t0, sp, 460
    sw t0, 468(sp)
    lw a0, 444(sp)
    lw a1, 456(sp)
    lw a2, 468(sp)
    call Food_better
    sw a0, 468(sp)
    j .L523
.L523:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 472(sp)
    lw t0, 0(sp)
    lw t1, 472(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 476(sp)
    lw t0, 476(sp)
    addi t0, t0, 12
    sw t0, 480(sp)
    lw t0, 480(sp)
    lw t1, 0(t0)
    sw t1, 484(sp)
    lw t0, 484(sp)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    sw t2, 488(sp)
    lw t0, 488(sp)
    bnez t0, .L540
    j .L558
.L540:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 492(sp)
    lw t0, 0(sp)
    lw t1, 492(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 496(sp)
    addi t0, sp, 500
    sw t0, 508(sp)
    lw a0, 496(sp)
    lw a1, 0(sp)
    lw a2, 508(sp)
    call SegT_rc_val
    sw a0, 508(sp)
    addi t0, sp, 512
    sw t0, 520(sp)
    addi t0, sp, 524
    sw t0, 532(sp)
    addi t0, sp, 536
    sw t0, 544(sp)
    lw a0, 520(sp)
    lw a1, 532(sp)
    lw a2, 544(sp)
    call Food_better
    sw a0, 544(sp)
    j .L558
.L558:
    lw t0, 32(sp)
    lw t1, 0(t0)
    sw t1, 548(sp)
    lw t0, 0(sp)
    lw t1, 548(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 552(sp)
    lw t0, 552(sp)
    addi t0, t0, 16
    sw t0, 556(sp)
    addi t0, sp, 560
    sw t0, 568(sp)
    lw a0, 572(sp)
    j .L4
.L4:
    lw ra, 588(sp)
    lw s0, 584(sp)
    addi sp, sp, 592
    jr ra
    .globl SegT_lc_val
    .type SegT_lc_val, @function
SegT_lc_val:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)
    addi s0, sp, 64
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    lw t0, 12(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 16
    sw t0, 16(sp)
    lw t0, 16(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    lw t0, 0(sp)
    addi t0, t0, 8
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t1, 0(t0)
    sw t1, 28(sp)
    lw t0, 4(sp)
    lw t1, 28(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 32(sp)
    lw t0, 32(sp)
    addi t0, t0, 16
    sw t0, 36(sp)
    lw a0, 40(sp)
    j .L5
.L5:
    lw ra, 60(sp)
    lw s0, 56(sp)
    addi sp, sp, 64
    jr ra
    .globl SegT_rc_val
    .type SegT_rc_val, @function
SegT_rc_val:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)
    addi s0, sp, 64
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    lw t0, 12(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 16
    sw t0, 16(sp)
    lw t0, 16(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    lw t0, 0(sp)
    addi t0, t0, 12
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t1, 0(t0)
    sw t1, 28(sp)
    lw t0, 4(sp)
    lw t1, 28(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 32(sp)
    lw t0, 32(sp)
    addi t0, t0, 16
    sw t0, 36(sp)
    lw a0, 40(sp)
    j .L6
.L6:
    lw ra, 60(sp)
    lw s0, 56(sp)
    addi sp, sp, 64
    jr ra
    .globl merge
    .type merge, @function
merge:
    addi sp, sp, -464
    sw ra, 460(sp)
    sw s0, 456(sp)
    addi s0, sp, 464
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    lw t0, 16(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 24
    sw t0, 28(sp)
    lw t0, 28(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    addi t0, sp, 32
    sw t0, 36(sp)
    lw t0, 36(sp)
    lw t1, 12(sp)
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 40(sp)
    lw t0, 40(sp)
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L612
    j .L618
.L612:
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 48(sp)
    lw a0, 48(sp)
    j .L7
.L618:
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 52(sp)
    lw t0, 52(sp)
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L629
    j .L635
.L629:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 60(sp)
    lw a0, 60(sp)
    j .L7
.L635:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 64(sp)
    lw t0, 0(sp)
    lw t1, 64(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    addi t0, t0, 0
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 0(t0)
    sw t1, 76(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 80(sp)
    lw t0, 0(sp)
    lw t1, 80(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    addi t0, t0, 4
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 0(t0)
    sw t1, 92(sp)
    lw t0, 76(sp)
    lw t1, 92(sp)
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 96(sp)
    lw t0, 96(sp)
    bnez t0, .L660
    j .L690
.L660:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 100(sp)
    lw t0, 0(sp)
    lw t1, 100(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    addi t0, t0, 16
    sw t0, 108(sp)
    lw t0, 108(sp)
    addi t0, t0, 0
    sw t0, 112(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 116(sp)
    lw t0, 0(sp)
    lw t1, 116(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    addi t0, t0, 16
    sw t0, 124(sp)
    lw t0, 124(sp)
    addi t0, t0, 0
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 0(t0)
    sw t1, 132(sp)
    lw t0, 112(sp)
    lw t1, 0(t0)
    sw t1, 136(sp)
    lw t0, 136(sp)
    lw t1, 132(sp)
    add t2, t0, t1
    sw t2, 140(sp)
    lw t0, 112(sp)
    lw t1, 140(sp)
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 144(sp)
    lw a0, 144(sp)
    j .L7
.L690:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 148(sp)
    lw t0, 0(sp)
    lw t1, 148(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    addi t0, t0, 8
    sw t0, 156(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 160(sp)
    lw t0, 0(sp)
    lw t1, 160(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 164(sp)
    lw t0, 164(sp)
    addi t0, t0, 8
    sw t0, 168(sp)
    lw t0, 168(sp)
    lw t1, 0(t0)
    sw t1, 172(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 176(sp)
    lw t0, 0(sp)
    lw t1, 176(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 180(sp)
    addi t0, t0, 8
    sw t0, 184(sp)
    lw t0, 184(sp)
    lw t1, 0(t0)
    sw t1, 188(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 172(sp)
    lw a3, 188(sp)
    call merge
    sw a0, 192(sp)
    lw t0, 156(sp)
    lw t1, 192(sp)
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 196(sp)
    lw t0, 0(sp)
    lw t1, 196(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 200(sp)
    lw t0, 200(sp)
    addi t0, t0, 12
    sw t0, 204(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 208(sp)
    lw t0, 0(sp)
    lw t1, 208(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    addi t0, t0, 12
    sw t0, 216(sp)
    lw t0, 216(sp)
    lw t1, 0(t0)
    sw t1, 220(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 224(sp)
    lw t0, 0(sp)
    lw t1, 224(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 228(sp)
    lw t0, 228(sp)
    addi t0, t0, 12
    sw t0, 232(sp)
    lw t0, 232(sp)
    lw t1, 0(t0)
    sw t1, 236(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 220(sp)
    lw a3, 236(sp)
    call merge
    sw a0, 240(sp)
    lw t0, 204(sp)
    lw t1, 240(sp)
    sw t1, 0(t0)
    addi t0, sp, 244
    sw t0, 252(sp)
    addi t0, sp, 256
    sw t0, 264(sp)
    lw t0, 264(sp)
    addi t0, t0, 0
    sw t0, 268(sp)
    lw t0, 268(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 264(sp)
    addi t0, t0, 4
    sw t0, 272(sp)
    lw t0, 272(sp)
    li t1, 0
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 276(sp)
    lw t0, 0(sp)
    lw t1, 276(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 280(sp)
    lw t0, 280(sp)
    addi t0, t0, 8
    sw t0, 284(sp)
    lw t0, 284(sp)
    lw t1, 0(t0)
    sw t1, 288(sp)
    lw t0, 288(sp)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    sw t2, 292(sp)
    lw t0, 292(sp)
    bnez t0, .L778
    j .L796
.L778:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 296(sp)
    lw t0, 0(sp)
    lw t1, 296(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 300(sp)
    addi t0, sp, 304
    sw t0, 312(sp)
    lw a0, 300(sp)
    lw a1, 0(sp)
    lw a2, 312(sp)
    call SegT_lc_val
    sw a0, 312(sp)
    addi t0, sp, 316
    sw t0, 324(sp)
    addi t0, sp, 328
    sw t0, 336(sp)
    addi t0, sp, 340
    sw t0, 348(sp)
    lw a0, 324(sp)
    lw a1, 336(sp)
    lw a2, 348(sp)
    call Food_better
    sw a0, 348(sp)
    j .L796
.L796:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 352(sp)
    lw t0, 0(sp)
    lw t1, 352(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 356(sp)
    lw t0, 356(sp)
    addi t0, t0, 12
    sw t0, 360(sp)
    lw t0, 360(sp)
    lw t1, 0(t0)
    sw t1, 364(sp)
    lw t0, 364(sp)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    sw t2, 368(sp)
    lw t0, 368(sp)
    bnez t0, .L813
    j .L831
.L813:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 372(sp)
    lw t0, 0(sp)
    lw t1, 372(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 376(sp)
    addi t0, sp, 380
    sw t0, 388(sp)
    lw a0, 376(sp)
    lw a1, 0(sp)
    lw a2, 388(sp)
    call SegT_rc_val
    sw a0, 388(sp)
    addi t0, sp, 392
    sw t0, 400(sp)
    addi t0, sp, 404
    sw t0, 412(sp)
    addi t0, sp, 416
    sw t0, 424(sp)
    lw a0, 400(sp)
    lw a1, 412(sp)
    lw a2, 424(sp)
    call Food_better
    sw a0, 424(sp)
    j .L831
.L831:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 428(sp)
    lw t0, 0(sp)
    lw t1, 428(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 432(sp)
    lw t0, 432(sp)
    addi t0, t0, 16
    sw t0, 436(sp)
    addi t0, sp, 440
    sw t0, 448(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 452(sp)
    lw a0, 452(sp)
    j .L7
.L7:
    lw ra, 460(sp)
    lw s0, 456(sp)
    addi sp, sp, 464
    jr ra
    .globl Node_push
    .type Node_push, @function
Node_push:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)
    addi s0, sp, 64
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    lw t0, 8(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 12
    sw t0, 16(sp)
    lw t0, 16(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 20(sp)
    lw t0, 0(sp)
    addi t0, t0, 804
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t1, 0(t0)
    sw t1, 28(sp)
    lw t0, 20(sp)
    lw t1, 28(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 32(sp)
    lw t0, 16(sp)
    lw t1, 0(t0)
    sw t1, 36(sp)
    lw t0, 32(sp)
    lw t1, 36(sp)
    sw t1, 0(t0)
    lw t0, 0(sp)
    addi t0, t0, 804
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 44(sp)
    lw t0, 44(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 48(sp)
    lw t0, 40(sp)
    lw t1, 48(sp)
    sw t1, 0(t0)
    lw a0, 52(sp)
    j .L8
.L8:
    lw ra, 60(sp)
    lw s0, 56(sp)
    addi sp, sp, 64
    jr ra
    .globl Node_clear
    .type Node_clear, @function
Node_clear:
    addi sp, sp, -32
    sw ra, 28(sp)
    sw s0, 24(sp)
    addi s0, sp, 32
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 4(sp)
    lw t0, 4(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    lw t0, 0(sp)
    addi t0, t0, 804
    sw t0, 8(sp)
    lw t0, 8(sp)
    li t1, 0
    sw t1, 0(t0)
    lw a0, 12(sp)
    j .L9
.L9:
    lw ra, 28(sp)
    lw s0, 24(sp)
    addi sp, sp, 32
    jr ra
    .globl prepare
    .type prepare, @function
prepare:
    addi sp, sp, -304
    sw ra, 300(sp)
    sw s0, 296(sp)
    addi s0, sp, 304
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    lw t0, 12(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 16
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 24
    sw t0, 28(sp)
    lw t0, 28(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 32(sp)
    lw t0, 0(sp)
    lw t1, 32(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 36(sp)
    lw t0, 36(sp)
    addi t0, t0, 812
    sw t0, 40(sp)
    lw t0, 40(sp)
    addi t0, t0, 0
    sw t0, 44(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 48(sp)
    lw t0, 44(sp)
    lw t1, 48(sp)
    sw t1, 0(t0)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 52(sp)
    lw t0, 0(sp)
    lw t1, 52(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    addi t0, t0, 808
    sw t0, 60(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 64(sp)
    lw t0, 64(sp)
    li t1, 0
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L914
    j .L915
.L914:
    lw t0, 60(sp)
    li t1, 1
    sw t1, 0(t0)
    j .L916
.L915:
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 72(sp)
    lw t0, 0(sp)
    lw t1, 72(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    addi t0, t0, 808
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 0(t0)
    sw t1, 84(sp)
    lw t0, 84(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 88(sp)
    lw t0, 60(sp)
    lw t1, 88(sp)
    sw t1, 0(t0)
    j .L916
.L916:
    addi t0, sp, 92
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    sw t1, 0(t0)
    j .L932
.L932:
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 100(sp)
    lw t0, 100(sp)
    li t1, 10
    slt t2, t1, t0
    xori t2, t2, 1
    sw t2, 104(sp)
    lw t0, 104(sp)
    bnez t0, .L941
    j .L1008
.L941:
    addi t0, sp, 108
    sw t0, 112(sp)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 116(sp)
    lw t0, 0(sp)
    lw t1, 116(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    addi t0, t0, 812
    sw t0, 124(sp)
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 128(sp)
    lw t0, 128(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 132(sp)
    lw t0, 124(sp)
    lw t1, 132(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 0(t0)
    sw t1, 140(sp)
    lw t0, 112(sp)
    lw t1, 140(sp)
    sw t1, 0(t0)
    lw t0, 112(sp)
    lw t1, 0(t0)
    sw t1, 144(sp)
    lw t0, 144(sp)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    sw t2, 148(sp)
    lw t0, 148(sp)
    bnez t0, .L969
    j .L1001
.L969:
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 152(sp)
    lw t0, 0(sp)
    lw t1, 152(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 156(sp)
    lw t0, 156(sp)
    addi t0, t0, 812
    sw t0, 160(sp)
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 164(sp)
    lw t0, 160(sp)
    lw t1, 164(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 168(sp)
    lw t0, 112(sp)
    lw t1, 0(t0)
    sw t1, 172(sp)
    lw t0, 0(sp)
    lw t1, 172(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 176(sp)
    lw t0, 176(sp)
    addi t0, t0, 812
    sw t0, 180(sp)
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 184(sp)
    lw t0, 184(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 188(sp)
    lw t0, 180(sp)
    lw t1, 188(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 192(sp)
    lw t0, 192(sp)
    lw t1, 0(t0)
    sw t1, 196(sp)
    lw t0, 168(sp)
    lw t1, 196(sp)
    sw t1, 0(t0)
    j .L1001
.L1001:
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 200(sp)
    lw t0, 200(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 204(sp)
    lw t0, 96(sp)
    lw t1, 204(sp)
    sw t1, 0(t0)
    j .L932
.L1008:
    lw t0, 96(sp)
    li t1, 0
    sw t1, 0(t0)
    j .L1015
.L1015:
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 208(sp)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 212(sp)
    lw t0, 0(sp)
    lw t1, 212(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 216(sp)
    lw t0, 216(sp)
    addi t0, t0, 804
    sw t0, 220(sp)
    lw t0, 220(sp)
    lw t1, 0(t0)
    sw t1, 224(sp)
    lw t0, 208(sp)
    lw t1, 224(sp)
    slt t2, t0, t1
    sw t2, 228(sp)
    lw t0, 228(sp)
    bnez t0, .L1031
    j .L1073
.L1031:
    addi t0, sp, 232
    sw t0, 236(sp)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 240(sp)
    lw t0, 0(sp)
    lw t1, 240(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 244(sp)
    lw t0, 244(sp)
    addi t0, t0, 0
    sw t0, 248(sp)
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 252(sp)
    lw t0, 248(sp)
    lw t1, 252(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 256(sp)
    lw t0, 256(sp)
    lw t1, 0(t0)
    sw t1, 260(sp)
    lw t0, 236(sp)
    lw t1, 260(sp)
    sw t1, 0(t0)
    lw t0, 96(sp)
    lw t1, 0(t0)
    sw t1, 264(sp)
    lw t0, 264(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 268(sp)
    lw t0, 96(sp)
    lw t1, 268(sp)
    sw t1, 0(t0)
    lw t0, 236(sp)
    lw t1, 0(t0)
    sw t1, 272(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 276(sp)
    lw t0, 272(sp)
    lw t1, 276(sp)
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 280(sp)
    lw t0, 280(sp)
    bnez t0, .L1063
    j .L1065
.L1063:
    j .L1015
.L1065:
    lw t0, 236(sp)
    lw t1, 0(t0)
    sw t1, 284(sp)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 288(sp)
    lw a0, 0(sp)
    lw a1, 284(sp)
    lw a2, 288(sp)
    call prepare
    j .L1015
.L1073:
    lw a0, 292(sp)
    j .L10
.L10:
    lw ra, 300(sp)
    lw s0, 296(sp)
    addi sp, sp, 304
    jr ra
    .globl lca
    .type lca, @function
lca:
    addi sp, sp, -368
    sw ra, 364(sp)
    sw s0, 360(sp)
    addi s0, sp, 368
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    lw t0, 12(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 16
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 24
    sw t0, 28(sp)
    lw t0, 28(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 32(sp)
    lw t0, 0(sp)
    lw t1, 32(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 36(sp)
    lw t0, 36(sp)
    addi t0, t0, 808
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t1, 0(t0)
    sw t1, 44(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 48(sp)
    lw t0, 0(sp)
    lw t1, 48(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    addi t0, t0, 808
    sw t0, 56(sp)
    lw t0, 56(sp)
    lw t1, 0(t0)
    sw t1, 60(sp)
    lw t0, 44(sp)
    lw t1, 60(sp)
    slt t2, t0, t1
    sw t2, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L1102
    j .L1121
.L1102:
    addi t0, sp, 68
    sw t0, 72(sp)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 80(sp)
    lw t0, 20(sp)
    lw t1, 80(sp)
    sw t1, 0(t0)
    lw t0, 72(sp)
    lw t1, 0(t0)
    sw t1, 84(sp)
    lw t0, 28(sp)
    lw t1, 84(sp)
    sw t1, 0(t0)
    j .L1121
.L1121:
    addi t0, sp, 88
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 10
    sw t1, 0(t0)
    j .L1128
.L1128:
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 96(sp)
    lw t0, 96(sp)
    li t1, 0
    slt t2, t0, t1
    xori t2, t2, 1
    sw t2, 100(sp)
    lw t0, 100(sp)
    bnez t0, .L1136
    j .L1208
.L1136:
    addi t0, sp, 104
    sw t0, 108(sp)
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 112(sp)
    lw t0, 0(sp)
    lw t1, 112(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    addi t0, t0, 812
    sw t0, 120(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 124(sp)
    lw t0, 120(sp)
    lw t1, 124(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 0(t0)
    sw t1, 132(sp)
    lw t0, 108(sp)
    lw t1, 132(sp)
    sw t1, 0(t0)
    j .L1158
.L1158:
    lw t0, 108(sp)
    lw t1, 0(t0)
    sw t1, 136(sp)
    lw t0, 136(sp)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    sw t2, 140(sp)
    lw t0, 140(sp)
    bnez t0, .L1166
    li t1, 0
    sw t1, 144(sp)
    j .L1189
.L1166:
    lw t0, 108(sp)
    lw t1, 0(t0)
    sw t1, 148(sp)
    lw t0, 0(sp)
    lw t1, 148(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    addi t0, t0, 808
    sw t0, 156(sp)
    lw t0, 156(sp)
    lw t1, 0(t0)
    sw t1, 160(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 164(sp)
    lw t0, 0(sp)
    lw t1, 164(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 168(sp)
    lw t0, 168(sp)
    addi t0, t0, 808
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t1, 0(t0)
    sw t1, 176(sp)
    lw t0, 160(sp)
    lw t1, 176(sp)
    slt t2, t0, t1
    xori t2, t2, 1
    sw t2, 180(sp)
    lw t1, 180(sp)
    sw t1, 144(sp)
    j .L1189
.L1189:
    lw t0, 144(sp)
    bnez t0, .L1193
    j .L1201
.L1193:
    lw t0, 108(sp)
    lw t1, 0(t0)
    sw t1, 184(sp)
    lw t0, 20(sp)
    lw t1, 184(sp)
    sw t1, 0(t0)
    j .L1201
.L1201:
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 188(sp)
    lw t0, 188(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 192(sp)
    lw t0, 92(sp)
    lw t1, 192(sp)
    sw t1, 0(t0)
    j .L1128
.L1208:
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 196(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 200(sp)
    lw t0, 196(sp)
    lw t1, 200(sp)
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 204(sp)
    lw t0, 204(sp)
    bnez t0, .L1221
    j .L1227
.L1221:
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 208(sp)
    lw a0, 208(sp)
    j .L11
.L1227:
    lw t0, 92(sp)
    li t1, 10
    sw t1, 0(t0)
    j .L1237
.L1237:
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 212(sp)
    lw t0, 212(sp)
    li t1, 0
    slt t2, t0, t1
    xori t2, t2, 1
    sw t2, 216(sp)
    lw t0, 216(sp)
    bnez t0, .L1245
    j .L1327
.L1245:
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 220(sp)
    lw t0, 0(sp)
    lw t1, 220(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 224(sp)
    lw t0, 224(sp)
    addi t0, t0, 812
    sw t0, 228(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 232(sp)
    lw t0, 228(sp)
    lw t1, 232(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 236(sp)
    lw t0, 236(sp)
    lw t1, 0(t0)
    sw t1, 240(sp)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 244(sp)
    lw t0, 0(sp)
    lw t1, 244(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 248(sp)
    addi t0, t0, 812
    sw t0, 252(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 256(sp)
    lw t0, 252(sp)
    lw t1, 256(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 260(sp)
    lw t0, 260(sp)
    lw t1, 0(t0)
    sw t1, 264(sp)
    lw t0, 240(sp)
    lw t1, 264(sp)
    sub t2, t0, t1
    snez t2, t2
    sw t2, 268(sp)
    lw t0, 268(sp)
    bnez t0, .L1281
    j .L1320
.L1281:
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 272(sp)
    lw t0, 0(sp)
    lw t1, 272(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 276(sp)
    lw t0, 276(sp)
    addi t0, t0, 812
    sw t0, 280(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 284(sp)
    lw t0, 280(sp)
    lw t1, 284(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 288(sp)
    lw t0, 288(sp)
    lw t1, 0(t0)
    sw t1, 292(sp)
    lw t0, 20(sp)
    lw t1, 292(sp)
    sw t1, 0(t0)
    lw t0, 28(sp)
    lw t1, 0(t0)
    sw t1, 296(sp)
    lw t0, 0(sp)
    lw t1, 296(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 300(sp)
    lw t0, 300(sp)
    addi t0, t0, 812
    sw t0, 304(sp)
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 308(sp)
    lw t0, 304(sp)
    lw t1, 308(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 312(sp)
    lw t0, 312(sp)
    lw t1, 0(t0)
    sw t1, 316(sp)
    lw t0, 28(sp)
    lw t1, 316(sp)
    sw t1, 0(t0)
    j .L1320
.L1320:
    lw t0, 92(sp)
    lw t1, 0(t0)
    sw t1, 320(sp)
    lw t0, 320(sp)
    li t1, 1
    sub t2, t0, t1
    sw t2, 324(sp)
    lw t0, 92(sp)
    lw t1, 324(sp)
    sw t1, 0(t0)
    j .L1237
.L1327:
    lw t0, 20(sp)
    lw t1, 0(t0)
    sw t1, 328(sp)
    lw t0, 0(sp)
    lw t1, 328(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 332(sp)
    lw t0, 332(sp)
    addi t0, t0, 812
    sw t0, 336(sp)
    lw t0, 336(sp)
    addi t0, t0, 0
    sw t0, 340(sp)
    lw t0, 340(sp)
    lw t1, 0(t0)
    sw t1, 344(sp)
    lw a0, 344(sp)
    j .L11
.L11:
    lw ra, 364(sp)
    lw s0, 360(sp)
    addi sp, sp, 368
    jr ra
    .globl dfs
    .type dfs, @function
dfs:
    addi sp, sp, -256
    sw ra, 252(sp)
    sw s0, 248(sp)
    addi s0, sp, 256
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    lw t0, 20(sp)
    lw t1, 0(sp)
    sw t1, 0(t0)
    addi t0, sp, 24
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t1, 4(sp)
    sw t1, 0(t0)
    addi t0, sp, 28
    sw t0, 28(sp)
    lw t0, 28(sp)
    lw t1, 8(sp)
    sw t1, 0(t0)
    addi t0, sp, 32
    sw t0, 36(sp)
    lw t0, 36(sp)
    lw t1, 12(sp)
    sw t1, 0(t0)
    addi t0, sp, 40
    sw t0, 44(sp)
    lw t0, 44(sp)
    lw t1, 16(sp)
    sw t1, 0(t0)
    addi t0, sp, 48
    sw t0, 52(sp)
    lw t0, 52(sp)
    li t1, 0
    sw t1, 0(t0)
    j .L1346
.L1346:
    lw t0, 52(sp)
    lw t1, 0(t0)
    sw t1, 56(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 60(sp)
    lw t0, 0(sp)
    lw t1, 60(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    addi t0, t0, 804
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t1, 0(t0)
    sw t1, 72(sp)
    lw t0, 56(sp)
    lw t1, 72(sp)
    slt t2, t0, t1
    sw t2, 76(sp)
    lw t0, 76(sp)
    bnez t0, .L1362
    j .L1406
.L1362:
    addi t0, sp, 80
    sw t0, 84(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 88(sp)
    lw t0, 0(sp)
    lw t1, 88(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    addi t0, t0, 0
    sw t0, 96(sp)
    lw t0, 52(sp)
    lw t1, 0(t0)
    sw t1, 100(sp)
    lw t0, 96(sp)
    lw t1, 100(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 0(t0)
    sw t1, 108(sp)
    lw t0, 84(sp)
    lw t1, 108(sp)
    sw t1, 0(t0)
    lw t0, 52(sp)
    lw t1, 0(t0)
    sw t1, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t2, t0, t1
    sw t2, 116(sp)
    lw t0, 52(sp)
    lw t1, 116(sp)
    sw t1, 0(t0)
    lw t0, 84(sp)
    lw t1, 0(t0)
    sw t1, 120(sp)
    lw t0, 44(sp)
    lw t1, 0(t0)
    sw t1, 124(sp)
    lw t0, 120(sp)
    lw t1, 124(sp)
    sub t2, t0, t1
    seqz t2, t2
    sw t2, 128(sp)
    lw t0, 128(sp)
    bnez t0, .L1394
    j .L1396
.L1394:
    j .L1346
.L1396:
    lw t0, 84(sp)
    lw t1, 0(t0)
    sw t1, 132(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 136(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 132(sp)
    lw a4, 136(sp)
    call dfs
    j .L1346
.L1406:
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 140(sp)
    lw t0, 0(sp)
    lw t1, 140(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 144(sp)
    lw t0, 144(sp)
    addi t0, t0, 860
    sw t0, 148(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 152(sp)
    lw t0, 0(sp)
    lw t1, 152(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 156(sp)
    lw t0, 156(sp)
    addi t0, t0, 856
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t1, 0(t0)
    sw t1, 164(sp)
    lw t0, 4(sp)
    lw t1, 164(sp)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 168(sp)
    lw t0, 168(sp)
    addi t0, t0, 16
    sw t0, 172(sp)
    lw t0, 172(sp)
    addi t0, t0, 4
    sw t0, 176(sp)
    lw t0, 176(sp)
    lw t1, 0(t0)
    sw t1, 180(sp)
    lw t0, 148(sp)
    lw t1, 180(sp)
    sw t1, 0(t0)
    lw t0, 44(sp)
    lw t1, 0(t0)
    sw t1, 184(sp)
    lw t0, 184(sp)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    sw t2, 188(sp)
    lw t0, 188(sp)
    bnez t0, .L1444
    j .L1477
.L1444:
    lw t0, 44(sp)
    lw t1, 0(t0)
    sw t1, 192(sp)
    lw t0, 0(sp)
    lw t1, 192(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 196(sp)
    lw t0, 196(sp)
    addi t0, t0, 856
    sw t0, 200(sp)
    lw t0, 44(sp)
    lw t1, 0(t0)
    sw t1, 204(sp)
    lw t0, 0(sp)
    lw t1, 204(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 208(sp)
    lw t0, 208(sp)
    addi t0, t0, 856
    sw t0, 212(sp)
    lw t0, 212(sp)
    lw t1, 0(t0)
    sw t1, 216(sp)
    lw t0, 36(sp)
    lw t1, 0(t0)
    sw t1, 220(sp)
    lw t0, 0(sp)
    lw t1, 220(sp)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 224(sp)
    lw t0, 224(sp)
    addi t0, t0, 856
    sw t0, 228(sp)
    lw t0, 228(sp)
    lw t1, 0(t0)
    sw t1, 232(sp)
    lw a0, 4(sp)
    lw a1, 8(sp)
    lw a2, 216(sp)
    lw a3, 232(sp)
    call merge
    sw a0, 236(sp)
    lw t0, 200(sp)
    lw t1, 236(sp)
    sw t1, 0(t0)
    j .L1477
.L1477:
    lw a0, 240(sp)
    j .L12
.L12:
    lw ra, 252(sp)
    lw s0, 248(sp)
    addi sp, sp, 256
    jr ra
    .globl main
    .type main, @function
main:
    li t0, -445696
    add sp, sp, t0
    li t0, 445692
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 445688
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 445696
    add s0, sp, t0
    addi t0, sp, 0
    li t3, 173664
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 173668
    add t0, sp, t1
    li t3, 174532
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 174536
    add t0, sp, t1
    li t3, 174540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 174540
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    j .L1488
    li t1, 174544
    add t0, sp, t1
    li t3, 175348
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 175352
    add t0, sp, t1
    li t3, 349016
    add t3, t3, sp
    sw t0, 0(t3)
.L1488:
    li t3, 174540
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349020
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349020
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 201
    slt t2, t0, t1
    li t3, 349024
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 349024
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1492
    j .L1493
.L1492:
    li t3, 174540
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349028
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 175348
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 349028
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 349032
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349032
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 174540
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349036
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349036
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 349040
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 174540
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 349040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1488
.L1493:
    li t3, 174532
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 349044
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 174532
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 804
    li t3, 349048
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349048
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 174532
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 808
    li t3, 349052
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349052
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t1, 349056
    add t0, sp, t1
    li t3, 349060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349060
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    j .L1503
    li t1, 349064
    add t0, sp, t1
    li t3, 349108
    add t3, t3, sp
    sw t0, 0(t3)
.L1503:
    li t3, 349060
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349112
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349112
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 11
    slt t2, t0, t1
    li t3, 349116
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 349116
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1507
    j .L1508
.L1507:
    li t3, 349060
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349120
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349108
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 349120
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 349124
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349124
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 349060
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349128
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349128
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 349132
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 349060
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 349132
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1503
.L1508:
    li t3, 174532
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 812
    li t3, 349136
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 174532
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 856
    li t3, 349140
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349140
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 174532
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 860
    li t3, 349144
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349144
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t1, 349148
    add t0, sp, t1
    li t3, 349152
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349152
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    j .L1516
.L1516:
    li t3, 349152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349156
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349156
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 201
    slt t2, t0, t1
    li t3, 349160
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 349160
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1520
    j .L1521
.L1520:
    li t3, 349152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349164
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349016
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 349164
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 349168
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 349152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 349172
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 349172
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 349176
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 349152
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 349176
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1516
.L1521:
    li t1, 349180
    add t0, sp, t1
    li t3, 397180
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 397184
    add t0, sp, t1
    li t3, 397208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397208
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 397212
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397212
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 397208
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 397216
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397216
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 397208
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 397220
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397220
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 397208
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 12
    li t3, 397224
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397224
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t1, 397228
    add t0, sp, t1
    li t3, 397236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397236
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 397240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397240
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 397236
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 397244
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397244
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t3, 397208
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 16
    li t3, 397248
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 397252
    add t0, sp, t1
    li t3, 397256
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397256
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    j .L1544
    li t1, 397260
    add t0, sp, t1
    li t3, 445260
    add t3, t3, sp
    sw t0, 0(t3)
.L1544:
    li t3, 397256
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445264
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445264
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2000
    slt t2, t0, t1
    li t3, 445268
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445268
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1548
    j .L1549
.L1548:
    li t3, 397256
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445272
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445260
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445272
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 24
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397256
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445280
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445280
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 445284
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 397256
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445284
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1544
.L1549:
    li t1, 445288
    add t0, sp, t1
    li t3, 445292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445292
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    li t1, 445296
    add t0, sp, t1
    li t3, 445300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445300
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445304
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t1, 445308
    add t0, sp, t1
    li t3, 445312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445312
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445316
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t1, 445320
    add t0, sp, t1
    li t3, 445324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sw t1, 0(t0)
    j .L1571
.L1571:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445328
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445332
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445328
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445332
    add t3, t3, sp
    lw t1, 0(t3)
    slt t2, t1, t0
    xori t2, t2, 1
    li t3, 445336
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445336
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1581
    j .L1615
.L1581:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445340
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445340
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445344
    add t3, t3, sp
    lw a0, 0(t3)
    call Node_clear
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445348
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445348
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445352
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 856
    li t3, 445356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 397180
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445292
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 1
    li a3, 200
    call build
    li t3, 445360
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 445356
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445360
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445364
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445364
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 445368
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445368
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1571
.L1615:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    j .L1622
.L1622:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445372
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445376
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445376
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t2, t0, t1
    li t3, 445380
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445372
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445380
    add t3, t3, sp
    lw t1, 0(t3)
    slt t2, t0, t1
    li t3, 445384
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445384
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1636
    j .L1671
.L1636:
    li t1, 445388
    add t0, sp, t1
    li t3, 445392
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445392
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445396
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t1, 445400
    add t0, sp, t1
    li t3, 445404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445404
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445408
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t3, 445392
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445412
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445412
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445420
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445416
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445420
    add t3, t3, sp
    lw a1, 0(t3)
    call Node_push
    li t3, 445404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445424
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445424
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445428
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445392
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445432
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445428
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445432
    add t3, t3, sp
    lw a1, 0(t3)
    call Node_push
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445436
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445436
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 445440
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445440
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1622
.L1671:
    li t3, 173664
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 1
    li a2, 0
    call prepare
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sw t1, 0(t0)
    j .L1682
.L1682:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445444
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445312
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445448
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445444
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445448
    add t3, t3, sp
    lw t1, 0(t3)
    slt t2, t0, t1
    li t3, 445452
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445452
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1692
    j .L1819
.L1692:
    li t1, 445456
    add t0, sp, t1
    li t3, 445460
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445460
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445464
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t1, 445468
    add t0, sp, t1
    li t3, 445472
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445472
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445476
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t1, 445480
    add t0, sp, t1
    li t3, 445484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445484
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445488
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t1, 445492
    add t0, sp, t1
    li t3, 445496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445460
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445500
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445472
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445504
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445500
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 445504
    add t3, t3, sp
    lw a2, 0(t3)
    call lca
    li t3, 445508
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 445496
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445508
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    li t3, 445460
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445512
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445512
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445516
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 856
    li t3, 445520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445520
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445524
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445484
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445528
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 397180
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445292
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 445524
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 445528
    add t3, t3, sp
    lw a3, 0(t3)
    li a4, 1
    call update
    li t3, 445472
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445532
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445532
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445536
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 856
    li t3, 445540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445540
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445544
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445484
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445548
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 397180
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445292
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 445544
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 445548
    add t3, t3, sp
    lw a3, 0(t3)
    li a4, 1
    call update
    li t3, 445496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445552
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445552
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445556
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445556
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 856
    li t3, 445560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445560
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445564
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445484
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445568
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 397180
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445292
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 445564
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 445568
    add t3, t3, sp
    lw a3, 0(t3)
    li a4, -1
    call update
    li t3, 445496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445572
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445572
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445576
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445576
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 812
    li t3, 445580
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445580
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 445584
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445584
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445588
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445588
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t2, t0, t1
    snez t2, t2
    li t3, 445592
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445592
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1786
    j .L1812
.L1786:
    li t3, 445496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445596
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445596
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445600
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445600
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 812
    li t3, 445604
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445604
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 445608
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445608
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445612
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445612
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445616
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445616
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 856
    li t3, 445620
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445620
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445624
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445484
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445628
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 397180
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 445292
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 445624
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 445628
    add t3, t3, sp
    lw a3, 0(t3)
    li a4, -1
    call update
    j .L1812
.L1812:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445632
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445632
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 445636
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445636
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1682
.L1819:
    li t3, 173664
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 397180
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 445292
    add t3, t3, sp
    lw a2, 0(t3)
    li a3, 1
    li a4, 0
    call dfs
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sw t1, 0(t0)
    j .L1834
.L1834:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445640
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445644
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445640
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445644
    add t3, t3, sp
    lw t1, 0(t3)
    slt t2, t1, t0
    xori t2, t2, 1
    li t3, 445648
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445648
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1844
    j .L1860
.L1844:
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445652
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 173664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445652
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 864
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 445656
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445656
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 860
    li t3, 445660
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 445660
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445664
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445664
    add t3, t3, sp
    lw a0, 0(t3)
    call print
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 0(t0)
    li t3, 445668
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 445668
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t2, t0, t1
    li t3, 445672
    add t3, t3, sp
    sw t2, 0(t3)
    li t3, 445324
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 445672
    add t3, t3, sp
    lw t1, 0(t3)
    sw t1, 0(t0)
    j .L1834
.L1860:
    li a0, 0
    call __builtin_exit
    li a0, 0
    j .L13
.L13:
    li t0, 445692
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 445688
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 445696
    add sp, sp, t0
    jr ra
