    .attribute arch, "rv64i2p1_m2p0_f2p2_d2p2"
    .text
    .globl __rcompiler_user_Food_better
    .type __rcompiler_user_Food_better, @function
__rcompiler_user_Food_better:
    addi sp, sp, -96
    sd ra, 88(sp)
    sd s0, 80(sp)
    sd s1, 24(sp)
    sd s2, 32(sp)
    sd s3, 40(sp)
    sd s4, 48(sp)
    sd s5, 56(sp)
    sd s6, 64(sp)
    addi s0, sp, 96
    mv s1, a0
    mv s2, a1
    mv s3, a2
    addi s4, sp, 0
    addi s4, sp, 8
    addi s4, sp, 16
    mv s4, s1
    lw s5, 0(s4)
    mv s4, s2
    lw s6, 0(s4)
    sub s4, s5, s6
    seqz s4, s4
    bnez s4, .L73
    j .L96
.L73:
    addi s4, s1, 4
    lw s5, 0(s4)
    addi s4, s2, 4
    lw s6, 0(s4)
    slt s4, s5, s6
    bnez s4, .L89
    j .L92
.L89:
    mv a0, s3
    mv a1, s1
    li a2, 8
    call memcpy
    j .L1
.L92:
    mv a0, s3
    mv a1, s2
    li a2, 8
    call memcpy
    j .L1
.L95:
    j .L118
.L96:
    mv s4, s1
    lw s5, 0(s4)
    mv s4, s2
    lw s6, 0(s4)
    slt s4, s6, s5
    bnez s4, .L111
    j .L114
.L111:
    mv a0, s3
    mv a1, s1
    li a2, 8
    call memcpy
    j .L1
.L114:
    mv a0, s3
    mv a1, s2
    li a2, 8
    call memcpy
    j .L1
.L117:
    j .L118
.L118:
    j .L1
.L1:
    mv a0, s3
    ld s1, 24(sp)
    ld s2, 32(sp)
    ld s3, 40(sp)
    ld s4, 48(sp)
    ld s5, 56(sp)
    ld s6, 64(sp)
    ld s0, 80(sp)
    ld ra, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl __rcompiler_user_new_segt
    .type __rcompiler_user_new_segt, @function
__rcompiler_user_new_segt:
    addi sp, sp, -128
    sd ra, 120(sp)
    sd s0, 112(sp)
    sd s1, 32(sp)
    sd s2, 40(sp)
    sd s3, 48(sp)
    sd s4, 56(sp)
    sd s5, 64(sp)
    sd s6, 72(sp)
    sd s7, 80(sp)
    sd s8, 88(sp)
    sd s9, 96(sp)
    addi s0, sp, 128
    mv s1, a0
    mv s2, a1
    mv s3, a2
    mv s4, a3
    mv s5, a4
    addi s6, sp, 0
    ld s7, 0(s2)
    li s8, 1
    add s9, s7, s8
    sd s9, 0(s2)
    ld s7, 0(s2)
    li s8, 32
    mul s9, s7, s8
    add s7, s1, s9
    mv a0, s6
    li a1, 0
    li a2, 32
    call memset
    mv s1, s6
    sw s3, 0(s1)
    addi s1, s6, 4
    sw s4, 0(s1)
    addi s1, s6, 8
    li s3, 0
    sd s3, 0(s1)
    addi s1, s6, 16
    li s3, 0
    sd s3, 0(s1)
    addi s1, s6, 24
    mv a0, s1
    mv a1, s5
    li a2, 8
    call memcpy
    mv a0, s7
    mv a1, s6
    li a2, 32
    call memcpy
    ld s1, 0(s2)
    mv a0, s1
    j .L2
.L2:
    ld s1, 32(sp)
    ld s2, 40(sp)
    ld s3, 48(sp)
    ld s4, 56(sp)
    ld s5, 64(sp)
    ld s6, 72(sp)
    ld s7, 80(sp)
    ld s8, 88(sp)
    ld s9, 96(sp)
    ld s0, 112(sp)
    ld ra, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl __rcompiler_user_build
    .type __rcompiler_user_build, @function
__rcompiler_user_build:
    addi sp, sp, -96
    sd ra, 88(sp)
    sd s0, 80(sp)
    sd s1, 16(sp)
    sd s2, 24(sp)
    sd s3, 32(sp)
    sd s4, 40(sp)
    sd s5, 48(sp)
    sd s6, 56(sp)
    sd s7, 64(sp)
    sd s8, 72(sp)
    addi s0, sp, 96
    mv s1, a0
    mv s2, a1
    mv s3, a2
    mv s4, a3
    addi s5, sp, 0
    addi s6, sp, 8
    slt s7, s4, s3
    bnez s7, .L172
    j .L174
.L172:
    li s7, 0
    mv a0, s7
    j .L3
.L174:
    sub s7, s3, s4
    seqz s7, s7
    bnez s7, .L187
    j .L221
.L187:
    mv a0, s5
    li a1, 0
    li a2, 8
    call memset
    mv s7, s5
    li s8, 0
    sw s8, 0(s7)
    addi s7, s5, 4
    sw s3, 0(s7)
    mv a0, s1
    mv a1, s2
    mv a2, s3
    mv a3, s4
    mv a4, s5
    call __rcompiler_user_new_segt
    mv s5, a0
    mv a0, s5
    j .L3
.L221:
    mv a0, s6
    li a1, 0
    li a2, 8
    call memset
    mv s5, s6
    li s7, 0
    sw s7, 0(s5)
    addi s5, s6, 4
    li s7, 0
    sw s7, 0(s5)
    mv a0, s1
    mv a1, s2
    mv a2, s3
    mv a3, s4
    mv a4, s6
    call __rcompiler_user_new_segt
    mv s1, a0
    mv a0, s1
    j .L3
.L3:
    ld s1, 16(sp)
    ld s2, 24(sp)
    ld s3, 32(sp)
    ld s4, 40(sp)
    ld s5, 48(sp)
    ld s6, 56(sp)
    ld s7, 64(sp)
    ld s8, 72(sp)
    ld s0, 80(sp)
    ld ra, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl __rcompiler_user_update
    .type __rcompiler_user_update, @function
__rcompiler_user_update:
    addi sp, sp, -288
    sd ra, 280(sp)
    sd s0, 272(sp)
    sd s1, 184(sp)
    sd s2, 192(sp)
    sd s3, 200(sp)
    sd s4, 208(sp)
    sd s5, 216(sp)
    sd s6, 224(sp)
    sd s7, 232(sp)
    sd s8, 240(sp)
    sd s9, 248(sp)
    sd s10, 256(sp)
    addi s0, sp, 288
    mv t5, a0
    sd t5, -184(s0)
    mv s6, a1
    mv t5, a2
    sd t5, -176(s0)
    mv s8, a3
    mv s9, a4
    addi t5, sp, 0
    sd t5, -192(s0)
    addi s2, sp, 8
    addi s10, sp, 16
    addi t5, sp, 24
    sd t5, -112(s0)
    addi t5, sp, 32
    sd t5, -120(s0)
    addi t5, sp, 40
    sd t5, -168(s0)
    addi t5, sp, 48
    sd t5, -160(s0)
    addi t5, sp, 56
    sd t5, -152(s0)
    addi t5, sp, 64
    sd t5, -144(s0)
    addi t5, sp, 72
    sd t5, -136(s0)
    addi t5, sp, 80
    sd t5, -128(s0)
    li t0, 0
    ld t5, -176(s0)
    sub t1, t5, t0
    seqz t1, t1
    bnez t1, .L251
    j .L254
.L251:
    mv a0, s1
    j .L4
.L254:
    li s1, 32
    ld t5, -176(s0)
    mul t0, t5, s1
    ld t5, -184(s0)
    add s1, t5, t0
    mv t0, s1
    lw s1, 0(t0)
    li t0, 32
    ld t5, -176(s0)
    mul t1, t5, t0
    ld t5, -184(s0)
    add t0, t5, t1
    addi t1, t0, 4
    lw s7, 0(t1)
    j .L281
.L281:
    slt t0, s8, s1
    li t1, 1
    mv t2, t1
    bnez t0, .L302
    j .L291
.L291:
    slt t0, s7, s8
    mv t1, t0
    mv t2, t1
    j .L302
.L302:
    bnez t2, .L306
    j .L309
.L306:
    mv a0, s4
    j .L4
.L309:
    sub s4, s1, s7
    seqz s4, s4
    bnez s4, .L322
    j .L341
.L322:
    li s4, 32
    ld t5, -176(s0)
    mul t0, t5, s4
    ld t5, -184(s0)
    add s4, t5, t0
    addi t0, s4, 24
    mv s4, t0
    lw t0, 0(s4)
    addw t1, t0, s9
    sw t1, 0(s4)
    mv a0, s3
    j .L4
.L341:
    addw s3, s1, s7
    li s4, 2
    divw s5, s3, s4
    slt s3, s5, s8
    xori s3, s3, 1
    bnez s3, .L369
    j .L423
.L369:
    li s3, 32
    ld t5, -176(s0)
    mul s4, t5, s3
    ld t5, -184(s0)
    add s3, t5, s4
    addi s4, s3, 8
    ld s3, 0(s4)
    li s4, 0
    sub t0, s3, s4
    seqz t0, t0
    bnez t0, .L385
    j .L406
.L385:
    li s3, 32
    ld t5, -176(s0)
    mul s4, t5, s3
    ld t5, -184(s0)
    add s3, t5, s4
    addi s4, s3, 8
    ld t5, -184(s0)
    mv a0, t5
    mv a1, s6
    mv a2, s1
    mv a3, s5
    call __rcompiler_user_build
    mv s1, a0
    sd s1, 0(s4)
    j .L406
.L406:
    li s1, 32
    ld t5, -176(s0)
    mul s3, t5, s1
    ld t5, -184(s0)
    add s1, t5, s3
    addi s3, s1, 8
    ld s1, 0(s3)
    ld t5, -184(s0)
    mv a0, t5
    mv a1, s6
    mv a2, s1
    mv a3, s8
    mv a4, s9
    call __rcompiler_user_update
    j .L481
.L423:
    li s1, 32
    ld t5, -176(s0)
    mul s3, t5, s1
    ld t5, -184(s0)
    add s1, t5, s3
    addi s3, s1, 16
    ld s1, 0(s3)
    li s3, 0
    sub s4, s1, s3
    seqz s4, s4
    bnez s4, .L439
    j .L464
.L439:
    li s1, 32
    ld t5, -176(s0)
    mul s3, t5, s1
    ld t5, -184(s0)
    add s1, t5, s3
    addi s3, s1, 16
    li s1, 1
    addw s4, s5, s1
    ld t5, -184(s0)
    mv a0, t5
    mv a1, s6
    mv a2, s4
    mv a3, s7
    call __rcompiler_user_build
    mv s1, a0
    sd s1, 0(s3)
    j .L464
.L464:
    li s1, 32
    ld t5, -176(s0)
    mul s3, t5, s1
    ld t5, -184(s0)
    add s1, t5, s3
    addi s3, s1, 16
    ld s1, 0(s3)
    ld t5, -184(s0)
    mv a0, t5
    mv a1, s6
    mv a2, s1
    mv a3, s8
    mv a4, s9
    call __rcompiler_user_update
    j .L481
.L481:
    mv a0, s2
    li a1, 0
    li a2, 8
    call memset
    mv s1, s2
    li s3, 0
    sw s3, 0(s1)
    addi s1, s2, 4
    li s3, 0
    sw s3, 0(s1)
    ld t5, -192(s0)
    mv a0, t5
    mv a1, s2
    li a2, 8
    call memcpy
    li s1, 32
    ld t5, -176(s0)
    mul s2, t5, s1
    ld t5, -184(s0)
    add s1, t5, s2
    addi s2, s1, 8
    ld s1, 0(s2)
    li s2, 0
    sub s3, s1, s2
    snez s3, s3
    bnez s3, .L505
    j .L523
.L505:
    li s1, 32
    ld t5, -176(s0)
    mul s2, t5, s1
    ld t5, -184(s0)
    add s1, t5, s2
    mv a0, s1
    ld t5, -184(s0)
    mv a1, t5
    mv a2, s10
    call __rcompiler_user_SegT_lc_val
    mv s10, a0
    ld t5, -112(s0)
    mv a0, t5
    mv a1, s10
    li a2, 8
    call memcpy
    ld t5, -120(s0)
    mv a0, t5
    ld t5, -192(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    ld t5, -112(s0)
    mv a0, t5
    ld t5, -120(s0)
    mv a1, t5
    ld t5, -168(s0)
    mv a2, t5
    call __rcompiler_user_Food_better
    mv t5, a0
    sd t5, -168(s0)
    ld t5, -192(s0)
    mv a0, t5
    ld t5, -168(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    j .L523
.L523:
    li s1, 32
    ld t5, -176(s0)
    mul s2, t5, s1
    ld t5, -184(s0)
    add s1, t5, s2
    addi s2, s1, 16
    ld s1, 0(s2)
    li s2, 0
    sub s3, s1, s2
    snez s3, s3
    bnez s3, .L540
    j .L558
.L540:
    li s1, 32
    ld t5, -176(s0)
    mul s2, t5, s1
    ld t5, -184(s0)
    add s1, t5, s2
    mv a0, s1
    ld t5, -184(s0)
    mv a1, t5
    ld t5, -160(s0)
    mv a2, t5
    call __rcompiler_user_SegT_rc_val
    mv t5, a0
    sd t5, -160(s0)
    ld t5, -152(s0)
    mv a0, t5
    ld t5, -160(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    ld t5, -144(s0)
    mv a0, t5
    ld t5, -192(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    ld t5, -152(s0)
    mv a0, t5
    ld t5, -144(s0)
    mv a1, t5
    ld t5, -136(s0)
    mv a2, t5
    call __rcompiler_user_Food_better
    mv t5, a0
    sd t5, -136(s0)
    ld t5, -192(s0)
    mv a0, t5
    ld t5, -136(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    j .L558
.L558:
    li s1, 32
    ld t5, -176(s0)
    mul s2, t5, s1
    ld t5, -184(s0)
    add s1, t5, s2
    addi s2, s1, 24
    ld t5, -128(s0)
    mv a0, t5
    ld t5, -192(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    mv a0, s2
    ld t5, -128(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    ld t5, -200(s0)
    mv a0, t5
    j .L4
.L4:
    ld s1, 184(sp)
    ld s2, 192(sp)
    ld s3, 200(sp)
    ld s4, 208(sp)
    ld s5, 216(sp)
    ld s6, 224(sp)
    ld s7, 232(sp)
    ld s8, 240(sp)
    ld s9, 248(sp)
    ld s10, 256(sp)
    ld s0, 272(sp)
    ld ra, 280(sp)
    addi sp, sp, 288
    jr ra
    .globl __rcompiler_user_SegT_lc_val
    .type __rcompiler_user_SegT_lc_val, @function
__rcompiler_user_SegT_lc_val:
    addi sp, sp, -80
    sd ra, 72(sp)
    sd s0, 64(sp)
    sd s1, 24(sp)
    sd s2, 32(sp)
    sd s3, 40(sp)
    sd s4, 48(sp)
    sd s5, 56(sp)
    addi s0, sp, 80
    mv s1, a0
    mv s2, a1
    mv s3, a2
    addi s4, sp, 0
    addi s4, sp, 8
    addi s4, sp, 16
    addi s4, s1, 8
    ld s1, 0(s4)
    li s4, 32
    mul s5, s1, s4
    add s1, s2, s5
    addi s2, s1, 24
    mv a0, s3
    mv a1, s2
    li a2, 8
    call memcpy
    j .L5
.L5:
    mv a0, s3
    ld s1, 24(sp)
    ld s2, 32(sp)
    ld s3, 40(sp)
    ld s4, 48(sp)
    ld s5, 56(sp)
    ld s0, 64(sp)
    ld ra, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl __rcompiler_user_SegT_rc_val
    .type __rcompiler_user_SegT_rc_val, @function
__rcompiler_user_SegT_rc_val:
    addi sp, sp, -80
    sd ra, 72(sp)
    sd s0, 64(sp)
    sd s1, 24(sp)
    sd s2, 32(sp)
    sd s3, 40(sp)
    sd s4, 48(sp)
    sd s5, 56(sp)
    addi s0, sp, 80
    mv s1, a0
    mv s2, a1
    mv s3, a2
    addi s4, sp, 0
    addi s4, sp, 8
    addi s4, sp, 16
    addi s4, s1, 16
    ld s1, 0(s4)
    li s4, 32
    mul s5, s1, s4
    add s1, s2, s5
    addi s2, s1, 24
    mv a0, s3
    mv a1, s2
    li a2, 8
    call memcpy
    j .L6
.L6:
    mv a0, s3
    ld s1, 24(sp)
    ld s2, 32(sp)
    ld s3, 40(sp)
    ld s4, 48(sp)
    ld s5, 56(sp)
    ld s0, 64(sp)
    ld ra, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl __rcompiler_user_merge
    .type __rcompiler_user_merge, @function
__rcompiler_user_merge:
    addi sp, sp, -240
    sd ra, 232(sp)
    sd s0, 224(sp)
    sd s1, 144(sp)
    sd s2, 152(sp)
    sd s3, 160(sp)
    sd s4, 168(sp)
    sd s5, 176(sp)
    sd s6, 184(sp)
    sd s7, 192(sp)
    sd s8, 200(sp)
    sd s9, 208(sp)
    sd s10, 216(sp)
    addi s0, sp, 240
    mv t5, a0
    sd t5, -136(s0)
    mv s2, a1
    mv t5, a2
    sd t5, -152(s0)
    mv s4, a3
    addi t5, sp, 0
    sd t5, -144(s0)
    addi s6, sp, 8
    addi s7, sp, 16
    addi s8, sp, 24
    addi s9, sp, 32
    addi s10, sp, 40
    addi s3, sp, 48
    addi t5, sp, 56
    sd t5, -104(s0)
    addi t5, sp, 64
    sd t5, -112(s0)
    addi t5, sp, 72
    sd t5, -128(s0)
    addi t5, sp, 80
    sd t5, -120(s0)
    li t0, 0
    ld t5, -152(s0)
    sub t1, t5, t0
    seqz t1, t1
    bnez t1, .L612
    j .L618
.L612:
    mv a0, s4
    j .L7
.L618:
    li t0, 0
    sub t1, s4, t0
    seqz t1, t1
    bnez t1, .L629
    j .L635
.L629:
    ld t5, -152(s0)
    mv a0, t5
    j .L7
.L635:
    li t0, 32
    ld t5, -152(s0)
    mul t1, t5, t0
    ld t5, -136(s0)
    add t0, t5, t1
    mv t1, t0
    lw t0, 0(t1)
    li t1, 32
    ld t5, -152(s0)
    mul t2, t5, t1
    ld t5, -136(s0)
    add t1, t5, t2
    addi t2, t1, 4
    lw t1, 0(t2)
    sub t2, t0, t1
    seqz t2, t2
    bnez t2, .L660
    j .L690
.L660:
    li t0, 32
    ld t5, -152(s0)
    mul t1, t5, t0
    ld t5, -136(s0)
    add t0, t5, t1
    addi t1, t0, 24
    mv t0, t1
    li t1, 32
    mul t2, s4, t1
    ld t5, -136(s0)
    add t1, t5, t2
    addi t2, t1, 24
    mv t1, t2
    lw t2, 0(t1)
    lw t1, 0(t0)
    addw t3, t1, t2
    sw t3, 0(t0)
    ld t5, -152(s0)
    mv a0, t5
    j .L7
.L690:
    li t0, 32
    ld t5, -152(s0)
    mul t1, t5, t0
    ld t5, -136(s0)
    add t0, t5, t1
    addi s1, t0, 8
    li t0, 32
    ld t5, -152(s0)
    mul t1, t5, t0
    ld t5, -136(s0)
    add t0, t5, t1
    addi t1, t0, 8
    ld t0, 0(t1)
    li t1, 32
    mul t2, s4, t1
    ld t5, -136(s0)
    add t1, t5, t2
    addi t2, t1, 8
    ld t1, 0(t2)
    ld t5, -136(s0)
    mv a0, t5
    mv a1, s2
    mv a2, t0
    mv a3, t1
    call __rcompiler_user_merge
    mv t0, a0
    sd t0, 0(s1)
    li s1, 32
    ld t5, -152(s0)
    mul t0, t5, s1
    ld t5, -136(s0)
    add s1, t5, t0
    addi s5, s1, 16
    li s1, 32
    ld t5, -152(s0)
    mul t0, t5, s1
    ld t5, -136(s0)
    add s1, t5, t0
    addi t0, s1, 16
    ld s1, 0(t0)
    li t0, 32
    mul t1, s4, t0
    ld t5, -136(s0)
    add s4, t5, t1
    addi t0, s4, 16
    ld s4, 0(t0)
    ld t5, -136(s0)
    mv a0, t5
    mv a1, s2
    mv a2, s1
    mv a3, s4
    call __rcompiler_user_merge
    mv s1, a0
    sd s1, 0(s5)
    mv a0, s6
    li a1, 0
    li a2, 8
    call memset
    mv s1, s6
    li s2, 0
    sw s2, 0(s1)
    addi s1, s6, 4
    li s2, 0
    sw s2, 0(s1)
    ld t5, -144(s0)
    mv a0, t5
    mv a1, s6
    li a2, 8
    call memcpy
    li s1, 32
    ld t5, -152(s0)
    mul s2, t5, s1
    ld t5, -136(s0)
    add s1, t5, s2
    addi s2, s1, 8
    ld s1, 0(s2)
    li s2, 0
    sub s4, s1, s2
    snez s4, s4
    bnez s4, .L778
    j .L796
.L778:
    li s1, 32
    ld t5, -152(s0)
    mul s2, t5, s1
    ld t5, -136(s0)
    add s1, t5, s2
    mv a0, s1
    ld t5, -136(s0)
    mv a1, t5
    mv a2, s7
    call __rcompiler_user_SegT_lc_val
    mv s7, a0
    mv a0, s8
    mv a1, s7
    li a2, 8
    call memcpy
    mv a0, s9
    ld t5, -144(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    mv a0, s8
    mv a1, s9
    mv a2, s10
    call __rcompiler_user_Food_better
    mv s10, a0
    ld t5, -144(s0)
    mv a0, t5
    mv a1, s10
    li a2, 8
    call memcpy
    j .L796
.L796:
    li s1, 32
    ld t5, -152(s0)
    mul s2, t5, s1
    ld t5, -136(s0)
    add s1, t5, s2
    addi s2, s1, 16
    ld s1, 0(s2)
    li s2, 0
    sub s4, s1, s2
    snez s4, s4
    bnez s4, .L813
    j .L831
.L813:
    li s1, 32
    ld t5, -152(s0)
    mul s2, t5, s1
    ld t5, -136(s0)
    add s1, t5, s2
    mv a0, s1
    ld t5, -136(s0)
    mv a1, t5
    mv a2, s3
    call __rcompiler_user_SegT_rc_val
    mv s3, a0
    ld t5, -104(s0)
    mv a0, t5
    mv a1, s3
    li a2, 8
    call memcpy
    ld t5, -112(s0)
    mv a0, t5
    ld t5, -144(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    ld t5, -104(s0)
    mv a0, t5
    ld t5, -112(s0)
    mv a1, t5
    ld t5, -128(s0)
    mv a2, t5
    call __rcompiler_user_Food_better
    mv t5, a0
    sd t5, -128(s0)
    ld t5, -144(s0)
    mv a0, t5
    ld t5, -128(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    j .L831
.L831:
    li s1, 32
    ld t5, -152(s0)
    mul s2, t5, s1
    ld t5, -136(s0)
    add s1, t5, s2
    addi s2, s1, 24
    ld t5, -120(s0)
    mv a0, t5
    ld t5, -144(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    mv a0, s2
    ld t5, -120(s0)
    mv a1, t5
    li a2, 8
    call memcpy
    ld t5, -152(s0)
    mv a0, t5
    j .L7
.L7:
    ld s1, 144(sp)
    ld s2, 152(sp)
    ld s3, 160(sp)
    ld s4, 168(sp)
    ld s5, 176(sp)
    ld s6, 184(sp)
    ld s7, 192(sp)
    ld s8, 200(sp)
    ld s9, 208(sp)
    ld s10, 216(sp)
    ld s0, 224(sp)
    ld ra, 232(sp)
    addi sp, sp, 240
    jr ra
    .globl __rcompiler_user_Node_push
    .type __rcompiler_user_Node_push, @function
__rcompiler_user_Node_push:
    addi sp, sp, -96
    sd ra, 88(sp)
    sd s0, 80(sp)
    sd s1, 16(sp)
    sd s2, 24(sp)
    sd s3, 32(sp)
    sd s4, 40(sp)
    sd s5, 48(sp)
    sd s6, 56(sp)
    sd s7, 64(sp)
    addi s0, sp, 96
    mv s2, a0
    mv s3, a1
    addi s4, sp, 0
    addi s4, sp, 8
    sd s3, 0(s4)
    mv s3, s2
    addi s5, s2, 1608
    ld s6, 0(s5)
    li s5, 8
    mul s7, s6, s5
    add s5, s3, s7
    ld s3, 0(s4)
    sd s3, 0(s5)
    addi s3, s2, 1608
    ld s2, 0(s3)
    li s4, 1
    add s5, s2, s4
    sd s5, 0(s3)
    mv a0, s1
    j .L8
.L8:
    ld s1, 16(sp)
    ld s2, 24(sp)
    ld s3, 32(sp)
    ld s4, 40(sp)
    ld s5, 48(sp)
    ld s6, 56(sp)
    ld s7, 64(sp)
    ld s0, 80(sp)
    ld ra, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl __rcompiler_user_Node_clear
    .type __rcompiler_user_Node_clear, @function
__rcompiler_user_Node_clear:
    addi sp, sp, -48
    sd ra, 40(sp)
    sd s0, 32(sp)
    sd s1, 8(sp)
    sd s2, 16(sp)
    sd s3, 24(sp)
    addi s0, sp, 48
    mv s2, a0
    addi s3, sp, 0
    addi s3, s2, 1608
    li s2, 0
    sd s2, 0(s3)
    mv a0, s1
    j .L9
.L9:
    ld s1, 8(sp)
    ld s2, 16(sp)
    ld s3, 24(sp)
    ld s0, 32(sp)
    ld ra, 40(sp)
    addi sp, sp, 48
    jr ra
    .globl __rcompiler_user_prepare
    .type __rcompiler_user_prepare, @function
__rcompiler_user_prepare:
    addi sp, sp, -96
    sd ra, 88(sp)
    sd s0, 80(sp)
    sd s1, 0(sp)
    sd s2, 8(sp)
    sd s3, 16(sp)
    sd s4, 24(sp)
    sd s5, 32(sp)
    sd s6, 40(sp)
    sd s7, 48(sp)
    sd s8, 56(sp)
    sd s9, 64(sp)
    sd s10, 72(sp)
    addi s0, sp, 96
    mv s2, a0
    mv s3, a1
    mv s4, a2
    li s5, 1720
    mul s6, s3, s5
    add s5, s2, s6
    addi s6, s5, 1620
    mv s5, s6
    sd s4, 0(s5)
    li s5, 1720
    mul s6, s3, s5
    add s5, s2, s6
    addi s6, s5, 1616
    li s5, 0
    sub s7, s4, s5
    seqz s7, s7
    bnez s7, .L914
    j .L915
.L914:
    li s5, 1
    sw s5, 0(s6)
    j .L916
.L915:
    li s5, 1720
    mul s7, s4, s5
    add s5, s2, s7
    addi s7, s5, 1616
    lw s5, 0(s7)
    li s7, 1
    addw s8, s5, s7
    sw s8, 0(s6)
    j .L916
.L916:
    li s5, 1
    li s6, 0
    add s7, s5, s6
    mv s5, s7
    mv s6, s5
    j .L932
.L932:
    li s5, 10
    sltu s7, s5, s6
    xori s7, s7, 1
    bnez s7, .L941
    j .L1008
.L941:
    li s5, 1720
    mul s7, s3, s5
    add s5, s2, s7
    addi s7, s5, 1620
    li s5, 1
    sub s8, s6, s5
    li s5, 8
    mul s9, s8, s5
    add s5, s7, s9
    ld s7, 0(s5)
    li s5, 0
    sub s8, s7, s5
    snez s8, s8
    bnez s8, .L969
    j .L1001
.L969:
    li s5, 1720
    mul s8, s3, s5
    add s5, s2, s8
    addi s8, s5, 1620
    li s5, 8
    mul s9, s6, s5
    add s5, s8, s9
    li s8, 1720
    mul s9, s7, s8
    add s7, s2, s9
    addi s8, s7, 1620
    li s7, 1
    sub s9, s6, s7
    li s7, 8
    mul s10, s9, s7
    add s7, s8, s10
    ld s8, 0(s7)
    sd s8, 0(s5)
    j .L1001
.L1001:
    li s5, 1
    add s7, s6, s5
    mv s5, s7
    mv s6, s5
    j .L932
.L1008:
    li s5, 0
    li s6, 0
    add s7, s5, s6
    mv s5, s7
    mv s6, s5
    j .L1015
.L1015:
    li s5, 1720
    mul s7, s3, s5
    add s5, s2, s7
    addi s7, s5, 1608
    ld s5, 0(s7)
    sltu s7, s6, s5
    bnez s7, .L1031
    j .L1073
.L1031:
    li s5, 1720
    mul s7, s3, s5
    add s5, s2, s7
    mv s7, s5
    li s5, 8
    mul s8, s6, s5
    add s5, s7, s8
    ld s7, 0(s5)
    li s5, 1
    add s8, s6, s5
    sub s5, s7, s4
    seqz s5, s5
    bnez s5, .L1063
    j .L1065
.L1063:
    mv s5, s8
    mv s6, s5
    j .L1015
.L1065:
    mv a0, s2
    mv a1, s7
    mv a2, s3
    call __rcompiler_user_prepare
    mv s5, s8
    mv s6, s5
    j .L1015
.L1073:
    mv a0, s1
    j .L10
.L10:
    ld s1, 0(sp)
    ld s2, 8(sp)
    ld s3, 16(sp)
    ld s4, 24(sp)
    ld s5, 32(sp)
    ld s6, 40(sp)
    ld s7, 48(sp)
    ld s8, 56(sp)
    ld s9, 64(sp)
    ld s10, 72(sp)
    ld s0, 80(sp)
    ld ra, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl __rcompiler_user_lca
    .type __rcompiler_user_lca, @function
__rcompiler_user_lca:
    addi sp, sp, -96
    sd ra, 88(sp)
    sd s0, 80(sp)
    sd s1, 0(sp)
    sd s2, 8(sp)
    sd s3, 16(sp)
    sd s4, 24(sp)
    sd s5, 32(sp)
    sd s6, 40(sp)
    sd s7, 48(sp)
    sd s8, 56(sp)
    sd s9, 64(sp)
    sd s10, 72(sp)
    addi s0, sp, 96
    mv s1, a0
    mv s2, a1
    mv s3, a2
    li s4, 1720
    mul s5, s2, s4
    add s4, s1, s5
    addi s5, s4, 1616
    lw s4, 0(s5)
    li s5, 1720
    mul s6, s3, s5
    add s5, s1, s6
    addi s6, s5, 1616
    lw s5, 0(s6)
    slt s6, s4, s5
    mv s4, s3
    mv s5, s2
    mv s7, s4
    mv s4, s5
    bnez s6, .L1102
    j .L1121
.L1102:
    mv s5, s2
    mv s2, s3
    mv s7, s5
    mv s4, s2
    j .L1121
.L1121:
    li s2, 10
    li s3, 0
    addw s5, s2, s3
    mv s2, s5
    mv s3, s4
    mv s4, s2
    mv s2, s3
    j .L1128
.L1128:
    li s3, 0
    slt s5, s4, s3
    xori s5, s5, 1
    bnez s5, .L1136
    j .L1208
.L1136:
    li s3, 1720
    mul s5, s2, s3
    add s3, s1, s5
    addi s5, s3, 1620
    li s3, 8
    mul s6, s4, s3
    add s3, s5, s6
    ld s5, 0(s3)
    j .L1158
.L1158:
    li s3, 0
    sub s6, s5, s3
    snez s6, s6
    li s3, 0
    mv s8, s3
    bnez s6, .L1166
    j .L1189
.L1166:
    li s3, 1720
    mul s6, s5, s3
    add s3, s1, s6
    addi s6, s3, 1616
    lw s3, 0(s6)
    li s6, 1720
    mul s9, s7, s6
    add s6, s1, s9
    addi s9, s6, 1616
    lw s6, 0(s9)
    slt s9, s3, s6
    xori s9, s9, 1
    mv s3, s9
    mv s8, s3
    j .L1189
.L1189:
    mv s3, s2
    mv s6, s3
    bnez s8, .L1193
    j .L1201
.L1193:
    mv s3, s5
    mv s6, s3
    j .L1201
.L1201:
    li s3, 1
    subw s5, s4, s3
    mv s3, s5
    mv s5, s6
    mv s4, s3
    mv s2, s5
    j .L1128
.L1208:
    sub s3, s2, s7
    seqz s3, s3
    bnez s3, .L1221
    j .L1227
.L1221:
    mv a0, s2
    j .L11
.L1227:
    li s3, 10
    li s4, 0
    addw s5, s3, s4
    mv s3, s5
    mv s4, s7
    mv s5, s2
    mv s2, s3
    mv s3, s4
    mv s4, s5
    j .L1237
.L1237:
    li s5, 0
    slt s6, s2, s5
    xori s6, s6, 1
    bnez s6, .L1245
    j .L1327
.L1245:
    li s5, 1720
    mul s6, s4, s5
    add s5, s1, s6
    addi s6, s5, 1620
    li s5, 8
    mul s7, s2, s5
    add s5, s6, s7
    ld s6, 0(s5)
    li s5, 1720
    mul s7, s3, s5
    add s5, s1, s7
    addi s7, s5, 1620
    li s5, 8
    mul s8, s2, s5
    add s5, s7, s8
    ld s7, 0(s5)
    sub s5, s6, s7
    snez s5, s5
    mv s6, s3
    mv s7, s4
    mv s8, s6
    mv s6, s7
    bnez s5, .L1281
    j .L1320
.L1281:
    li s5, 1720
    mul s7, s4, s5
    add s5, s1, s7
    addi s7, s5, 1620
    li s5, 8
    mul s9, s2, s5
    add s5, s7, s9
    ld s7, 0(s5)
    li s5, 1720
    mul s9, s3, s5
    add s5, s1, s9
    addi s9, s5, 1620
    li s5, 8
    mul s10, s2, s5
    add s5, s9, s10
    ld s9, 0(s5)
    mv s5, s9
    mv s9, s7
    mv s8, s5
    mv s6, s9
    j .L1320
.L1320:
    li s5, 1
    subw s7, s2, s5
    mv s5, s7
    mv s7, s8
    mv s8, s6
    mv s2, s5
    mv s3, s7
    mv s4, s8
    j .L1237
.L1327:
    li s2, 1720
    mul s3, s4, s2
    add s2, s1, s3
    addi s1, s2, 1620
    mv s2, s1
    ld s1, 0(s2)
    mv a0, s1
    j .L11
.L11:
    ld s1, 0(sp)
    ld s2, 8(sp)
    ld s3, 16(sp)
    ld s4, 24(sp)
    ld s5, 32(sp)
    ld s6, 40(sp)
    ld s7, 48(sp)
    ld s8, 56(sp)
    ld s9, 64(sp)
    ld s10, 72(sp)
    ld s0, 80(sp)
    ld ra, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl __rcompiler_user_dfs
    .type __rcompiler_user_dfs, @function
__rcompiler_user_dfs:
    addi sp, sp, -96
    sd ra, 88(sp)
    sd s0, 80(sp)
    sd s1, 0(sp)
    sd s2, 8(sp)
    sd s3, 16(sp)
    sd s4, 24(sp)
    sd s5, 32(sp)
    sd s6, 40(sp)
    sd s7, 48(sp)
    sd s8, 56(sp)
    sd s9, 64(sp)
    sd s10, 72(sp)
    addi s0, sp, 96
    mv s2, a0
    mv s3, a1
    mv s4, a2
    mv s5, a3
    mv s6, a4
    li s7, 0
    li s8, 0
    add s9, s7, s8
    mv s7, s9
    mv s8, s7
    j .L1346
.L1346:
    li s7, 1720
    mul s9, s5, s7
    add s7, s2, s9
    addi s9, s7, 1608
    ld s7, 0(s9)
    sltu s9, s8, s7
    bnez s9, .L1362
    j .L1406
.L1362:
    li s7, 1720
    mul s9, s5, s7
    add s7, s2, s9
    mv s9, s7
    li s7, 8
    mul s10, s8, s7
    add s7, s9, s10
    ld s9, 0(s7)
    li s7, 1
    add s10, s8, s7
    sub s7, s9, s6
    seqz s7, s7
    bnez s7, .L1394
    j .L1396
.L1394:
    mv s7, s10
    mv s8, s7
    j .L1346
.L1396:
    mv a0, s2
    mv a1, s3
    mv a2, s4
    mv a3, s9
    mv a4, s5
    call __rcompiler_user_dfs
    mv s7, s10
    mv s8, s7
    j .L1346
.L1406:
    li s7, 1720
    mul s8, s5, s7
    add s7, s2, s8
    addi s8, s7, 1716
    li s7, 1720
    mul s9, s5, s7
    add s7, s2, s9
    addi s9, s7, 1708
    ld s7, 0(s9)
    li s9, 32
    mul s10, s7, s9
    add s7, s3, s10
    addi s9, s7, 24
    addi s7, s9, 4
    lw s9, 0(s7)
    sw s9, 0(s8)
    li s7, 0
    sub s8, s6, s7
    snez s8, s8
    bnez s8, .L1444
    j .L1477
.L1444:
    li s7, 1720
    mul s8, s6, s7
    add s7, s2, s8
    addi s8, s7, 1708
    li s7, 1720
    mul s9, s6, s7
    add s6, s2, s9
    addi s7, s6, 1708
    ld s6, 0(s7)
    li s7, 1720
    mul s9, s5, s7
    add s5, s2, s9
    addi s2, s5, 1708
    ld s5, 0(s2)
    mv a0, s3
    mv a1, s4
    mv a2, s6
    mv a3, s5
    call __rcompiler_user_merge
    mv s2, a0
    sd s2, 0(s8)
    j .L1477
.L1477:
    mv a0, s1
    j .L12
.L12:
    ld s1, 0(sp)
    ld s2, 8(sp)
    ld s3, 16(sp)
    ld s4, 24(sp)
    ld s5, 32(sp)
    ld s6, 40(sp)
    ld s7, 48(sp)
    ld s8, 56(sp)
    ld s9, 64(sp)
    ld s10, 72(sp)
    ld s0, 80(sp)
    ld ra, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl main
    .type main, @function
main:
    li t5, -822176
    add sp, sp, t5
    li t5, 822168
    add t5, t5, sp
    sd ra, 0(t5)
    li t5, 822160
    add t5, t5, sp
    sd s0, 0(t5)
    li t5, 822072
    add t5, t5, sp
    sd s1, 0(t5)
    li t5, 822080
    add t5, t5, sp
    sd s2, 0(t5)
    li t5, 822088
    add t5, t5, sp
    sd s3, 0(t5)
    li t5, 822096
    add t5, t5, sp
    sd s4, 0(t5)
    li t5, 822104
    add t5, t5, sp
    sd s5, 0(t5)
    li t5, 822112
    add t5, t5, sp
    sd s6, 0(t5)
    li t5, 822120
    add t5, t5, sp
    sd s7, 0(t5)
    li t5, 822128
    add t5, t5, sp
    sd s8, 0(t5)
    li t5, 822136
    add t5, t5, sp
    sd s9, 0(t5)
    li t5, 822144
    add t5, t5, sp
    sd s10, 0(t5)
    li t5, 822176
    add s0, sp, t5
    addi t5, sp, 0
    sd t5, -112(s0)
    li s2, 345720
    add s3, sp, s2
    li s2, 347440
    add s4, sp, s2
    li s2, 348248
    add s5, sp, s2
    li s2, 693968
    add s6, sp, s2
    li s2, 694016
    add s7, sp, s2
    li s2, 758016
    add s8, sp, s2
    li s2, 758048
    add s9, sp, s2
    li s2, 758056
    add s10, sp, s2
    li s2, 822056
    add s1, sp, s2
    mv a0, s3
    li a1, 0
    li a2, 1720
    call memset
    li s2, 0
    li t0, 0
    addw t1, s2, t0
    mv s2, t1
    mv t0, s2
    j .L1488
.L1488:
    li s2, 201
    slt t1, t0, s2
    bnez t1, .L1492
    j .L1493
.L1492:
    li s2, 4
    mul t1, t0, s2
    add s2, s4, t1
    li t1, 0
    sw t1, 0(s2)
    li s2, 1
    addw t1, t0, s2
    mv s2, t1
    mv t0, s2
    j .L1488
.L1493:
    mv s2, s3
    mv a0, s2
    mv a1, s4
    li a2, 1608
    call memcpy
    addi s2, s3, 1608
    li s4, 0
    sd s4, 0(s2)
    addi s2, s3, 1616
    li s4, 0
    sw s4, 0(s2)
    li s2, 0
    li s4, 0
    addw t0, s2, s4
    mv s2, t0
    mv s4, s2
    j .L1503
.L1503:
    li s2, 11
    slt t0, s4, s2
    bnez t0, .L1507
    j .L1508
.L1507:
    li s2, 4
    mul t0, s4, s2
    add s2, s6, t0
    li t0, 0
    sw t0, 0(s2)
    li s2, 1
    addw t0, s4, s2
    mv s2, t0
    mv s4, s2
    j .L1503
.L1508:
    addi s2, s3, 1620
    mv a0, s2
    mv a1, s6
    li a2, 88
    call memcpy
    addi s2, s3, 1708
    li s4, 0
    sd s4, 0(s2)
    addi s2, s3, 1716
    li s4, 0
    sw s4, 0(s2)
    li s2, 0
    li s4, 0
    addw s6, s2, s4
    mv s2, s6
    mv s4, s2
    j .L1516
.L1516:
    li s2, 201
    slt s6, s4, s2
    bnez s6, .L1520
    j .L1521
.L1520:
    li s2, 1720
    mul s6, s4, s2
    add s2, s5, s6
    mv a0, s2
    mv a1, s3
    li a2, 1720
    call memcpy
    li s2, 1
    addw s6, s4, s2
    mv s2, s6
    mv s4, s2
    j .L1516
.L1521:
    ld t5, -112(s0)
    mv a0, t5
    mv a1, s5
    li a2, 345720
    call memcpy
    mv a0, s8
    li a1, 0
    li a2, 32
    call memset
    mv s2, s8
    li s3, 0
    sw s3, 0(s2)
    addi s2, s8, 4
    li s3, 0
    sw s3, 0(s2)
    addi s2, s8, 8
    li s3, 0
    sd s3, 0(s2)
    addi s2, s8, 16
    li s3, 0
    sd s3, 0(s2)
    mv a0, s9
    li a1, 0
    li a2, 8
    call memset
    mv s2, s9
    li s3, 0
    sw s3, 0(s2)
    addi s2, s9, 4
    li s3, 0
    sw s3, 0(s2)
    addi s2, s8, 24
    mv a0, s2
    mv a1, s9
    li a2, 8
    call memcpy
    li s2, 0
    li s3, 0
    addw s4, s2, s3
    mv s2, s4
    mv s3, s2
    j .L1544
.L1544:
    li s2, 2000
    slt s4, s3, s2
    bnez s4, .L1548
    j .L1549
.L1548:
    li s2, 32
    mul s4, s3, s2
    add s2, s10, s4
    mv a0, s2
    mv a1, s8
    li a2, 32
    call memcpy
    li s2, 1
    addw s4, s3, s2
    mv s2, s4
    mv s3, s2
    j .L1544
.L1549:
    mv a0, s7
    mv a1, s10
    li a2, 64000
    call memcpy
    li s2, 0
    sd s2, 0(s1)
    call getInt
    mv s2, a0
    call getInt
    mv s3, a0
    li s4, 1
    li s5, 0
    add s6, s4, s5
    mv s4, s6
    mv s5, s4
    j .L1571
.L1571:
    sltu s4, s2, s5
    xori s4, s4, 1
    bnez s4, .L1581
    j .L1615
.L1581:
    li s4, 1720
    mul s6, s5, s4
    ld t5, -112(s0)
    add s4, t5, s6
    mv a0, s4
    call __rcompiler_user_Node_clear
    li s4, 1720
    mul s6, s5, s4
    ld t5, -112(s0)
    add s4, t5, s6
    addi s6, s4, 1708
    mv a0, s7
    mv a1, s1
    li s4, 1
    mv a2, s4
    li s4, 200
    mv a3, s4
    call __rcompiler_user_build
    mv s4, a0
    sd s4, 0(s6)
    li s4, 1
    add s6, s5, s4
    mv s4, s6
    mv s5, s4
    j .L1571
.L1615:
    li s4, 0
    li s5, 0
    add s6, s4, s5
    mv s4, s6
    mv s5, s4
    j .L1622
.L1622:
    li s4, 1
    sub s6, s2, s4
    sltu s4, s5, s6
    bnez s4, .L1636
    j .L1671
.L1636:
    call getInt
    mv s4, a0
    call getInt
    mv s6, a0
    li s8, 1720
    mul s9, s4, s8
    ld t5, -112(s0)
    add s8, t5, s9
    mv a0, s8
    mv a1, s6
    call __rcompiler_user_Node_push
    li s8, 1720
    mul s9, s6, s8
    ld t5, -112(s0)
    add s6, t5, s9
    mv a0, s6
    mv a1, s4
    call __rcompiler_user_Node_push
    li s4, 1
    add s6, s5, s4
    mv s4, s6
    mv s5, s4
    j .L1622
.L1671:
    ld t5, -112(s0)
    mv a0, t5
    li s4, 1
    mv a1, s4
    li s4, 0
    mv a2, s4
    call __rcompiler_user_prepare
    li s4, 0
    li s5, 0
    add s6, s4, s5
    mv s4, s6
    mv s5, s4
    j .L1682
.L1682:
    sltu s4, s5, s3
    bnez s4, .L1692
    j .L1819
.L1692:
    call getInt
    mv s4, a0
    call getInt
    mv s6, a0
    call getInt
    mv s8, a0
    ld t5, -112(s0)
    mv a0, t5
    mv a1, s4
    mv a2, s6
    call __rcompiler_user_lca
    mv s9, a0
    li s10, 1720
    mul t0, s4, s10
    ld t5, -112(s0)
    add s4, t5, t0
    addi s10, s4, 1708
    ld s4, 0(s10)
    mv a0, s7
    mv a1, s1
    mv a2, s4
    mv a3, s8
    li s4, 1
    mv a4, s4
    call __rcompiler_user_update
    li s4, 1720
    mul s10, s6, s4
    ld t5, -112(s0)
    add s4, t5, s10
    addi s6, s4, 1708
    ld s4, 0(s6)
    mv a0, s7
    mv a1, s1
    mv a2, s4
    mv a3, s8
    li s4, 1
    mv a4, s4
    call __rcompiler_user_update
    li s4, 1720
    mul s6, s9, s4
    ld t5, -112(s0)
    add s4, t5, s6
    addi s6, s4, 1708
    ld s4, 0(s6)
    mv a0, s7
    mv a1, s1
    mv a2, s4
    mv a3, s8
    li s4, -1
    mv a4, s4
    call __rcompiler_user_update
    li s4, 1720
    mul s6, s9, s4
    ld t5, -112(s0)
    add s4, t5, s6
    addi s6, s4, 1620
    mv s4, s6
    ld s6, 0(s4)
    li s4, 0
    sub s10, s6, s4
    snez s10, s10
    bnez s10, .L1786
    j .L1812
.L1786:
    li s4, 1720
    mul s6, s9, s4
    ld t5, -112(s0)
    add s4, t5, s6
    addi s6, s4, 1620
    mv s4, s6
    ld s6, 0(s4)
    li s4, 1720
    mul s9, s6, s4
    ld t5, -112(s0)
    add s4, t5, s9
    addi s6, s4, 1708
    ld s4, 0(s6)
    mv a0, s7
    mv a1, s1
    mv a2, s4
    mv a3, s8
    li s4, -1
    mv a4, s4
    call __rcompiler_user_update
    j .L1812
.L1812:
    li s4, 1
    add s6, s5, s4
    mv s4, s6
    mv s5, s4
    j .L1682
.L1819:
    ld t5, -112(s0)
    mv a0, t5
    mv a1, s7
    mv a2, s1
    li s1, 1
    mv a3, s1
    li s1, 0
    mv a4, s1
    call __rcompiler_user_dfs
    li s1, 1
    li s3, 0
    add s4, s1, s3
    mv s1, s4
    mv s3, s1
    j .L1834
.L1834:
    sltu s1, s2, s3
    xori s1, s1, 1
    bnez s1, .L1844
    j .L1860
.L1844:
    li s1, 1720
    mul s4, s3, s1
    ld t5, -112(s0)
    add s1, t5, s4
    addi s4, s1, 1716
    lw s1, 0(s4)
    mv a0, s1
    call printlnInt
    li s1, 1
    add s4, s3, s1
    mv s1, s4
    mv s3, s1
    j .L1834
.L1860:
    li a0, 0
    call __builtin_exit
    li s1, 0
    mv a0, s1
    j .L13
.L13:
    li t5, 822072
    add t5, t5, sp
    ld s1, 0(t5)
    li t5, 822080
    add t5, t5, sp
    ld s2, 0(t5)
    li t5, 822088
    add t5, t5, sp
    ld s3, 0(t5)
    li t5, 822096
    add t5, t5, sp
    ld s4, 0(t5)
    li t5, 822104
    add t5, t5, sp
    ld s5, 0(t5)
    li t5, 822112
    add t5, t5, sp
    ld s6, 0(t5)
    li t5, 822120
    add t5, t5, sp
    ld s7, 0(t5)
    li t5, 822128
    add t5, t5, sp
    ld s8, 0(t5)
    li t5, 822136
    add t5, t5, sp
    ld s9, 0(t5)
    li t5, 822144
    add t5, t5, sp
    ld s10, 0(t5)
    li t5, 822160
    add t5, t5, sp
    ld s0, 0(t5)
    li t5, 822168
    add t5, t5, sp
    ld ra, 0(t5)
    li t5, 822176
    add sp, sp, t5
    jr ra
