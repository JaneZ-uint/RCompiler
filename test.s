    .text
    .globl main
    .type main, @function
main:
    addi sp, sp, -560
    sw ra, 556(sp)
    sw s0, 552(sp)
    sw s1, 512(sp)
    sw s2, 516(sp)
    sw s3, 520(sp)
    sw s4, 524(sp)
    sw s5, 528(sp)
    sw s6, 532(sp)
    sw s7, 536(sp)
    sw s8, 540(sp)
    sw s9, 544(sp)
    sw s10, 548(sp)
    addi s0, sp, 560
    addi s1, sp, 0
    addi s2, sp, 4
    addi s3, sp, 8
    addi s4, sp, 12
    addi s5, sp, 16
    addi s6, sp, 256
    addi s7, sp, 260
    addi s8, sp, 500
    addi s9, sp, 504
    addi s10, sp, 508
    li t0, 0
    sw t0, 0(s1)
    li t0, 0
    sw t0, 0(s2)
    li t0, -1
    sw t0, 0(s3)
    li t0, 0
    sw t0, 0(s4)
    li t0, 0
    sw t0, 0(s6)
    j .L40
.L40:
    lw t0, 0(s6)
    li t1, 60
    slt t2, t0, t1
    bnez t2, .L44
    j .L45
.L44:
    lw t0, 0(s6)
    li t1, 4
    mul t2, t0, t1
    add t0, s7, t2
    li t1, 0
    sw t1, 0(t0)
    lw t0, 0(s6)
    li t1, 1
    add t2, t0, t1
    sw t2, 0(s6)
    j .L40
.L45:
    mv a0, s5
    mv a1, s7
    li a2, 240
    call memcpy
    li s6, 0
    sw s6, 0(s8)
    j .L53
.L53:
    lw s6, 0(s8)
    li s7, 60
    slt t0, s6, s7
    bnez t0, .L61
    j .L92
.L61:
    lw s6, 0(s8)
    li s7, 4
    mul t0, s6, s7
    add s6, s5, t0
    lw s7, 0(s8)
    li t0, 8
    rem t1, s7, t0
    sw t1, 0(s6)
    lw s6, 0(s8)
    li s7, 1
    add t0, s6, s7
    sw t0, 0(s8)
    j .L53
.L92:
    li s6, 0
    sw s6, 0(s8)
    j .L99
.L99:
    lw s6, 0(s8)
    li s7, 60
    slt t0, s6, s7
    bnez t0, .L107
    j .L303
.L107:
    lw s6, 0(s8)
    li s7, 4
    mul t0, s6, s7
    add s6, s5, t0
    lw s7, 0(s6)
    sw s7, 0(s9)
    lw s6, 0(s8)
    li s7, 10
    mul t0, s6, s7
    sw t0, 0(s10)
    lw s6, 0(s1)
    lw s7, 0(s9)
    lw t0, 0(s10)
    lw t1, 0(s2)
    lw t2, 0(s3)
    lw t3, 0(s4)
    mv a0, s6
    mv a1, s7
    mv a2, t0
    mv a3, t1
    mv a4, t2
    mv a5, t3
    call process_event
    mv s6, a0
    sw s6, 0(s1)
    lw s6, 0(s1)
    li s7, 1
    sub t0, s6, s7
    seqz t0, t0
    bnez t0, .L157
    j .L169
.L157:
    li s6, 0
    sw s6, 0(s2)
    li s6, -1
    sw s6, 0(s3)
    j .L244
.L169:
    lw s6, 0(s1)
    li s7, 2
    sub t0, s6, s7
    seqz t0, t0
    bnez t0, .L179
    j .L221
.L179:
    lw s6, 0(s9)
    li s7, 2
    sub t0, s6, s7
    seqz t0, t0
    bnez t0, .L189
    j .L201
.L189:
    lw s6, 0(s2)
    li s7, 1
    add t0, s6, s7
    sw t0, 0(s2)
    j .L220
.L201:
    lw s6, 0(s9)
    li s7, 3
    sub t0, s6, s7
    seqz t0, t0
    bnez t0, .L211
    j .L219
.L211:
    lw s6, 0(s10)
    sw s6, 0(s3)
    j .L219
.L219:
    j .L220
.L220:
    j .L243
.L221:
    lw s6, 0(s1)
    li s7, 4
    sub t0, s6, s7
    seqz t0, t0
    bnez t0, .L231
    j .L242
.L231:
    li s6, 0
    sw s6, 0(s1)
    li s6, 0
    sw s6, 0(s4)
    j .L242
.L242:
    j .L243
.L243:
    j .L244
.L244:
    lw s6, 0(s3)
    lw s7, 0(s2)
    li t0, 5
    sub t1, s7, t0
    slt s7, s6, t1
    bnez s7, .L260
    j .L288
.L260:
    lw s6, 0(s4)
    li s7, 1
    add t0, s6, s7
    sw t0, 0(s4)
    lw s6, 0(s4)
    li s7, 3
    slt t0, s7, s6
    bnez t0, .L281
    j .L287
.L281:
    li s6, 4
    sw s6, 0(s1)
    j .L287
.L287:
    j .L288
.L288:
    lw s6, 0(s1)
    mv a0, s6
    call printInt
    lw s6, 0(s8)
    li s7, 1
    add t0, s6, s7
    sw t0, 0(s8)
    j .L99
.L303:
    li a0, 0
    call __builtin_exit
    li s1, 0
    mv a0, s1
    j .L1
.L1:
    lw s1, 512(sp)
    lw s2, 516(sp)
    lw s3, 520(sp)
    lw s4, 524(sp)
    lw s5, 528(sp)
    lw s6, 532(sp)
    lw s7, 536(sp)
    lw s8, 540(sp)
    lw s9, 544(sp)
    lw s10, 548(sp)
    lw s0, 552(sp)
    lw ra, 556(sp)
    addi sp, sp, 560
    jr ra
    .globl process_event
    .type process_event, @function
process_event:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    sw s1, 36(sp)
    sw s2, 40(sp)
    sw s3, 44(sp)
    sw s4, 48(sp)
    sw s5, 52(sp)
    sw s6, 56(sp)
    sw s7, 60(sp)
    sw s8, 64(sp)
    sw s9, 68(sp)
    sw s10, 72(sp)
    addi s0, sp, 96
    mv s1, a0
    mv s2, a1
    mv s3, a2
    mv s4, a3
    mv s5, a4
    mv s6, a5
    addi s7, sp, 0
    addi t5, sp, 4
    sw t5, 32(sp)
    addi t5, sp, 8
    sw t5, 28(sp)
    addi s10, sp, 12
    addi s9, sp, 16
    addi t0, sp, 20
    addi s8, sp, 24
    sw s1, 0(s7)
    lw t5, 32(sp)
    sw s2, 0(t5)
    lw t5, 28(sp)
    sw s3, 0(t5)
    sw s4, 0(s10)
    sw s5, 0(s9)
    sw s6, 0(t0)
    lw s1, 0(s7)
    sw s1, 0(s8)
    lw s1, 0(s7)
    li s2, 0
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L325
    j .L342
.L325:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 0
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L335
    j .L341
.L335:
    li s1, 1
    sw s1, 0(s8)
    j .L341
.L341:
    j .L543
.L342:
    lw s1, 0(s7)
    li s2, 1
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L352
    j .L386
.L352:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 1
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L362
    j .L368
.L362:
    li s1, 2
    sw s1, 0(s8)
    j .L385
.L368:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 6
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L378
    j .L384
.L378:
    li s1, 0
    sw s1, 0(s8)
    j .L384
.L384:
    j .L385
.L385:
    j .L542
.L386:
    lw s1, 0(s7)
    li s2, 2
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L396
    j .L484
.L396:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 2
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L406
    j .L424
.L406:
    lw t5, 28(sp)
    lw s1, 0(t5)
    mv a0, s1
    call validate_checksum
    mv s1, a0
    li s2, 0
    sub s3, s1, s2
    snez s3, s3
    bnez s3, .L416
    j .L417
.L416:
    j .L423
.L417:
    li s1, 4
    sw s1, 0(s8)
    j .L423
.L423:
    j .L483
.L424:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 3
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L434
    j .L448
.L434:
    lw t5, 28(sp)
    lw s1, 0(t5)
    lw s2, 0(s9)
    slt s3, s2, s1
    bnez s3, .L446
    j .L447
.L446:
    j .L447
.L447:
    j .L482
.L448:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 4
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L458
    j .L464
.L458:
    li s1, 3
    sw s1, 0(s8)
    j .L481
.L464:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 7
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L474
    j .L480
.L474:
    li s1, 4
    sw s1, 0(s8)
    j .L480
.L480:
    j .L481
.L481:
    j .L482
.L482:
    j .L483
.L483:
    j .L541
.L484:
    lw s1, 0(s7)
    li s2, 3
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L494
    j .L528
.L494:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 5
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L504
    j .L510
.L504:
    li s1, 0
    sw s1, 0(s8)
    j .L527
.L510:
    lw t5, 32(sp)
    lw s1, 0(t5)
    li s2, 6
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L520
    j .L526
.L520:
    li s1, 0
    sw s1, 0(s8)
    j .L526
.L526:
    j .L527
.L527:
    j .L540
.L528:
    lw s1, 0(s7)
    li s2, 4
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L538
    j .L539
.L538:
    j .L539
.L539:
    j .L540
.L540:
    j .L541
.L541:
    j .L542
.L542:
    j .L543
.L543:
    lw s1, 0(s8)
    lw t5, 32(sp)
    lw s2, 0(t5)
    lw t5, 28(sp)
    lw s3, 0(t5)
    mv a0, s1
    mv a1, s2
    mv a2, s3
    call complex_state_logic
    mv s1, a0
    mv a0, s1
    j .L2
.L2:
    lw s1, 36(sp)
    lw s2, 40(sp)
    lw s3, 44(sp)
    lw s4, 48(sp)
    lw s5, 52(sp)
    lw s6, 56(sp)
    lw s7, 60(sp)
    lw s8, 64(sp)
    lw s9, 68(sp)
    lw s10, 72(sp)
    lw s0, 88(sp)
    lw ra, 92(sp)
    addi sp, sp, 96
    jr ra
    .globl validate_checksum
    .type validate_checksum, @function
validate_checksum:
    addi sp, sp, -48
    sw ra, 44(sp)
    sw s0, 40(sp)
    sw s1, 12(sp)
    sw s2, 16(sp)
    sw s3, 20(sp)
    sw s4, 24(sp)
    sw s5, 28(sp)
    sw s6, 32(sp)
    addi s0, sp, 48
    mv s1, a0
    addi s2, sp, 0
    addi s3, sp, 4
    addi s4, sp, 8
    sw s1, 0(s2)
    li s1, 0
    sw s1, 0(s3)
    li s1, 1
    sw s1, 0(s4)
    j .L569
.L569:
    lw s1, 0(s4)
    lw s5, 0(s2)
    slt s6, s5, s1
    xori s6, s6, 1
    bnez s6, .L579
    j .L621
.L579:
    lw s1, 0(s2)
    lw s5, 0(s4)
    rem s6, s1, s5
    li s1, 0
    sub s5, s6, s1
    seqz s5, s5
    bnez s5, .L595
    j .L609
.L595:
    lw s1, 0(s3)
    lw s5, 0(s4)
    add s6, s1, s5
    sw s6, 0(s3)
    j .L609
.L609:
    lw s1, 0(s4)
    li s5, 1
    add s6, s1, s5
    sw s6, 0(s4)
    j .L569
.L621:
    lw s1, 0(s3)
    li s2, 2
    rem s3, s1, s2
    li s1, 0
    sub s2, s3, s1
    seqz s2, s2
    mv s1, s2
    mv a0, s1
    j .L3
.L3:
    lw s1, 12(sp)
    lw s2, 16(sp)
    lw s3, 20(sp)
    lw s4, 24(sp)
    lw s5, 28(sp)
    lw s6, 32(sp)
    lw s0, 40(sp)
    lw ra, 44(sp)
    addi sp, sp, 48
    jr ra
    .globl complex_state_logic
    .type complex_state_logic, @function
complex_state_logic:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    sw s1, 24(sp)
    sw s2, 28(sp)
    sw s3, 32(sp)
    sw s4, 36(sp)
    sw s5, 40(sp)
    sw s6, 44(sp)
    sw s7, 48(sp)
    sw s8, 52(sp)
    sw s9, 56(sp)
    addi s0, sp, 80
    mv s1, a0
    mv s2, a1
    mv s3, a2
    addi s4, sp, 0
    addi s5, sp, 4
    addi s6, sp, 8
    addi s7, sp, 12
    addi s8, sp, 16
    addi s9, sp, 20
    sw s1, 0(s4)
    sw s2, 0(s5)
    sw s3, 0(s6)
    lw s1, 0(s4)
    sw s1, 0(s7)
    lw s1, 0(s5)
    li s2, 6
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L661
    j .L685
.L661:
    lw s1, 0(s4)
    li s2, 2
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L671
    j .L684
.L671:
    lw s1, 0(s4)
    lw s2, 0(s6)
    mv a0, s1
    mv a1, s2
    call perform_recovery
    mv s1, a0
    sw s1, 0(s7)
    j .L684
.L684:
    j .L685
.L685:
    li s1, 0
    sw s1, 0(s8)
    lw s1, 0(s6)
    sw s1, 0(s9)
    j .L693
.L693:
    lw s1, 0(s8)
    li s2, 5
    slt s3, s1, s2
    bnez s3, .L701
    j .L743
.L701:
    lw s1, 0(s9)
    lw s2, 0(s8)
    li s3, 2
    add s4, s2, s3
    div s2, s1, s4
    lw s1, 0(s8)
    lw s3, 0(s8)
    mul s4, s1, s3
    add s1, s2, s4
    sw s1, 0(s9)
    lw s1, 0(s8)
    li s2, 1
    add s3, s1, s2
    sw s3, 0(s8)
    j .L693
.L743:
    lw s1, 0(s9)
    li s2, 10
    rem s3, s1, s2
    li s1, 0
    sub s2, s3, s1
    seqz s2, s2
    bnez s2, .L758
    j .L775
.L758:
    lw s1, 0(s7)
    li s2, 4
    sub s3, s1, s2
    snez s3, s3
    bnez s3, .L768
    j .L774
.L768:
    li s1, 4
    sw s1, 0(s7)
    j .L774
.L774:
    j .L775
.L775:
    lw s1, 0(s7)
    mv a0, s1
    j .L4
.L4:
    lw s1, 24(sp)
    lw s2, 28(sp)
    lw s3, 32(sp)
    lw s4, 36(sp)
    lw s5, 40(sp)
    lw s6, 44(sp)
    lw s7, 48(sp)
    lw s8, 52(sp)
    lw s9, 56(sp)
    lw s0, 72(sp)
    lw ra, 76(sp)
    addi sp, sp, 80
    jr ra
    .globl perform_recovery
    .type perform_recovery, @function
perform_recovery:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)
    sw s1, 16(sp)
    sw s2, 20(sp)
    sw s3, 24(sp)
    sw s4, 28(sp)
    sw s5, 32(sp)
    sw s6, 36(sp)
    sw s7, 40(sp)
    sw s8, 44(sp)
    sw s9, 48(sp)
    addi s0, sp, 64
    mv s1, a0
    mv s2, a1
    addi s3, sp, 0
    addi s4, sp, 4
    addi s5, sp, 8
    addi s6, sp, 12
    sw s1, 0(s3)
    sw s2, 0(s4)
    li s1, 0
    sw s1, 0(s5)
    li s1, 0
    sw s1, 0(s6)
    j .L788
.L788:
    lw s1, 0(s6)
    li s2, 10
    slt s7, s1, s2
    bnez s7, .L796
    j .L833
.L796:
    lw s1, 0(s5)
    lw s2, 0(s4)
    lw s7, 0(s6)
    li s8, 1
    add s9, s7, s8
    rem s7, s2, s9
    add s2, s1, s7
    sw s2, 0(s5)
    lw s1, 0(s6)
    li s2, 1
    add s7, s1, s2
    sw s7, 0(s6)
    j .L788
.L833:
    lw s1, 0(s5)
    li s2, 20
    slt s4, s2, s1
    bnez s4, .L844
    j .L850
.L844:
    lw s1, 0(s3)
    mv a0, s1
    j .L5
.L850:
    li s1, 4
    mv a0, s1
    j .L5
.L852:
    li s1, 0
    mv a0, s1
    j .L5
.L5:
    lw s1, 16(sp)
    lw s2, 20(sp)
    lw s3, 24(sp)
    lw s4, 28(sp)
    lw s5, 32(sp)
    lw s6, 36(sp)
    lw s7, 40(sp)
    lw s8, 44(sp)
    lw s9, 48(sp)
    lw s0, 56(sp)
    lw ra, 60(sp)
    addi sp, sp, 64
    jr ra
    .globl another_layer_of_protocol
    .type another_layer_of_protocol, @function
another_layer_of_protocol:
    addi sp, sp, -48
    sw ra, 44(sp)
    sw s0, 40(sp)
    sw s1, 16(sp)
    sw s2, 20(sp)
    sw s3, 24(sp)
    sw s4, 28(sp)
    sw s5, 32(sp)
    sw s6, 36(sp)
    addi s0, sp, 48
    mv s1, a0
    mv s2, a1
    addi s3, sp, 0
    addi s4, sp, 4
    addi s5, sp, 8
    addi s6, sp, 12
    sw s1, 0(s3)
    sw s2, 0(s4)
    lw s1, 0(s4)
    sw s1, 0(s5)
    lw s1, 0(s3)
    li s2, 2
    sub s4, s1, s2
    seqz s4, s4
    bnez s4, .L869
    j .L907
.L869:
    li s1, 0
    sw s1, 0(s6)
    j .L873
.L873:
    lw s1, 0(s6)
    li s2, 5
    slt s4, s1, s2
    bnez s4, .L881
    j .L906
.L881:
    lw s1, 0(s5)
    lw s2, 0(s6)
    add s4, s1, s2
    sw s4, 0(s5)
    lw s1, 0(s6)
    li s2, 1
    add s4, s1, s2
    sw s4, 0(s6)
    j .L873
.L906:
    j .L930
.L907:
    lw s1, 0(s3)
    li s2, 3
    sub s3, s1, s2
    seqz s3, s3
    bnez s3, .L917
    j .L929
.L917:
    lw s1, 0(s5)
    li s2, 10
    sub s3, s1, s2
    sw s3, 0(s5)
    j .L929
.L929:
    j .L930
.L930:
    lw s1, 0(s5)
    mv a0, s1
    j .L6
.L6:
    lw s1, 16(sp)
    lw s2, 20(sp)
    lw s3, 24(sp)
    lw s4, 28(sp)
    lw s5, 32(sp)
    lw s6, 36(sp)
    lw s0, 40(sp)
    lw ra, 44(sp)
    addi sp, sp, 48
    jr ra
    .globl yet_another_protocol_function
    .type yet_another_protocol_function, @function
yet_another_protocol_function:
    addi sp, sp, -48
    sw ra, 44(sp)
    sw s0, 40(sp)
    sw s1, 16(sp)
    sw s2, 20(sp)
    sw s3, 24(sp)
    sw s4, 28(sp)
    sw s5, 32(sp)
    sw s6, 36(sp)
    addi s0, sp, 48
    mv s1, a0
    mv s2, a1
    addi s3, sp, 0
    addi s4, sp, 4
    addi s5, sp, 8
    addi s6, sp, 12
    sw s1, 0(s3)
    sw s2, 0(s4)
    lw s1, 0(s3)
    lw s2, 0(s4)
    add s3, s1, s2
    sw s3, 0(s5)
    li s1, 0
    sw s1, 0(s6)
    j .L951
.L951:
    lw s1, 0(s6)
    li s2, 3
    slt s3, s1, s2
    bnez s3, .L959
    j .L983
.L959:
    lw s1, 0(s6)
    lw s2, 0(s5)
    mv a0, s1
    mv a1, s2
    call another_layer_of_protocol
    mv s1, a0
    sw s1, 0(s5)
    lw s1, 0(s6)
    li s2, 1
    add s3, s1, s2
    sw s3, 0(s6)
    j .L951
.L983:
    lw s1, 0(s5)
    mv a0, s1
    j .L7
.L7:
    lw s1, 16(sp)
    lw s2, 20(sp)
    lw s3, 24(sp)
    lw s4, 28(sp)
    lw s5, 32(sp)
    lw s6, 36(sp)
    lw s0, 40(sp)
    lw ra, 44(sp)
    addi sp, sp, 48
    jr ra
    .globl process_complex_packet
    .type process_complex_packet, @function
process_complex_packet:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    sw s1, 24(sp)
    sw s2, 28(sp)
    sw s3, 32(sp)
    sw s4, 36(sp)
    sw s5, 40(sp)
    sw s6, 44(sp)
    sw s7, 48(sp)
    sw s8, 52(sp)
    sw s9, 56(sp)
    addi s0, sp, 80
    mv s1, a0
    mv s2, a1
    mv s3, a2
    addi s4, sp, 0
    addi s5, sp, 4
    addi s6, sp, 8
    addi s7, sp, 12
    addi s8, sp, 16
    addi s9, sp, 20
    sw s1, 0(s4)
    sw s2, 0(s5)
    sw s3, 0(s6)
    lw s1, 0(s4)
    lw s2, 0(s5)
    mv a0, s1
    mv a1, s2
    call yet_another_protocol_function
    mv s1, a0
    sw s1, 0(s7)
    lw s1, 0(s5)
    lw s2, 0(s6)
    mv a0, s1
    mv a1, s2
    call yet_another_protocol_function
    mv s1, a0
    sw s1, 0(s8)
    lw s1, 0(s4)
    lw s2, 0(s6)
    mv a0, s1
    mv a1, s2
    call yet_another_protocol_function
    mv s1, a0
    sw s1, 0(s9)
    lw s1, 0(s7)
    lw s2, 0(s8)
    sub s3, s1, s2
    lw s1, 0(s9)
    add s2, s3, s1
    mv a0, s2
    j .L8
.L8:
    lw s1, 24(sp)
    lw s2, 28(sp)
    lw s3, 32(sp)
    lw s4, 36(sp)
    lw s5, 40(sp)
    lw s6, 44(sp)
    lw s7, 48(sp)
    lw s8, 52(sp)
    lw s9, 56(sp)
    lw s0, 72(sp)
    lw ra, 76(sp)
    addi sp, sp, 80
    jr ra
