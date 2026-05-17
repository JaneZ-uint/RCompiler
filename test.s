    .text
    .globl main
    .type main, @function
main:
    addi sp, sp, -544
    sw ra, 540(sp)
    sw s0, 536(sp)
    sw s1, 488(sp)
    sw s2, 492(sp)
    sw s3, 496(sp)
    sw s4, 500(sp)
    sw s5, 504(sp)
    sw s6, 508(sp)
    sw s7, 512(sp)
    sw s8, 516(sp)
    sw s9, 520(sp)
    sw s10, 524(sp)
    addi s0, sp, 544
    addi s1, sp, 0
    addi s2, sp, 240
    li s3, 0
    li s4, 0
    add s5, s3, s4
    li s3, 0
    li s4, 0
    add s6, s3, s4
    li s3, -1
    li s4, 0
    add s7, s3, s4
    li s3, 0
    li s4, 0
    add s8, s3, s4
    li s3, 0
    li s4, 0
    add s9, s3, s4
    mv s3, s9
    mv s4, s3
    j .L40
.L40:
    li s3, 60
    slt s9, s4, s3
    bnez s9, .L44
    j .L45
.L44:
    li s3, 4
    mul s9, s4, s3
    add s3, s2, s9
    li s9, 0
    sw s9, 0(s3)
    li s3, 1
    add s9, s4, s3
    mv s3, s9
    mv s4, s3
    j .L40
.L45:
    mv a0, s1
    mv a1, s2
    li a2, 240
    call memcpy
    li s2, 0
    li s3, 0
    add s4, s2, s3
    mv s2, s4
    mv s3, s2
    j .L53
.L53:
    li s2, 60
    slt s4, s3, s2
    bnez s4, .L61
    j .L92
.L61:
    li s2, 4
    mul s4, s3, s2
    add s2, s1, s4
    li s4, 8
    rem s9, s3, s4
    sw s9, 0(s2)
    li s2, 1
    add s4, s3, s2
    mv s2, s4
    mv s3, s2
    j .L53
.L92:
    li s2, 0
    li s3, 0
    add s4, s2, s3
    mv s2, s4
    mv s3, s8
    mv s4, s7
    mv s7, s6
    mv s6, s5
    mv s5, s2
    mv s2, s3
    mv s3, s4
    mv t5, s7
    sw t5, 484(sp)
    mv t5, s6
    sw t5, 480(sp)
    j .L99
.L99:
    li s6, 60
    slt s8, s5, s6
    bnez s8, .L107
    j .L303
.L107:
    li s6, 4
    mul s8, s5, s6
    add s6, s1, s8
    lw s8, 0(s6)
    li s6, 10
    mul s9, s5, s6
    lw t5, 480(sp)
    mv a0, t5
    mv a1, s8
    mv a2, s9
    lw t5, 484(sp)
    mv a3, t5
    mv a4, s3
    mv a5, s2
    call process_event
    mv s6, a0
    li s10, 1
    sub t0, s6, s10
    seqz t0, t0
    bnez t0, .L157
    j .L169
.L157:
    li s10, 0
    li t0, 0
    add t1, s10, t0
    li s10, -1
    li t0, 0
    add t2, s10, t0
    mv s10, s2
    mv t0, t2
    mv t2, t1
    mv t1, s6
    mv t3, s10
    mv s10, t0
    mv s7, t2
    mv t0, t1
    j .L244
.L169:
    li t1, 2
    sub t2, s6, t1
    seqz t2, t2
    bnez t2, .L179
    j .L221
.L179:
    li t1, 2
    sub t2, s8, t1
    seqz t2, t2
    bnez t2, .L189
    j .L201
.L189:
    li t1, 1
    lw t5, 484(sp)
    add t2, t5, t1
    mv t1, s3
    mv t4, t2
    mv t2, t1
    mv t1, t4
    j .L220
.L201:
    li t4, 3
    sub a0, s8, t4
    seqz a0, a0
    mv s8, s3
    mv t4, s8
    bnez a0, .L211
    j .L219
.L211:
    mv s8, s9
    mv t4, s8
    j .L219
.L219:
    mv s8, t4
    lw t5, 484(sp)
    mv s9, t5
    mv t2, s8
    mv t1, s9
    j .L220
.L220:
    mv s8, s2
    mv s9, t2
    mv t2, t1
    mv t1, s6
    mv t4, s8
    mv s8, s9
    mv s9, t2
    mv t2, t1
    j .L243
.L221:
    li t1, 4
    sub a0, s6, t1
    seqz a0, a0
    mv t1, s2
    mv a1, s6
    mv s6, t1
    mv t1, a1
    bnez a0, .L231
    j .L242
.L231:
    li a0, 0
    li a1, 0
    add a2, a0, a1
    li a0, 0
    li a1, 0
    add a3, a0, a1
    mv a0, a3
    mv a1, a2
    mv s6, a0
    mv t1, a1
    j .L242
.L242:
    mv a0, s6
    mv s6, s3
    lw t5, 484(sp)
    mv a1, t5
    mv a2, t1
    mv t4, a0
    mv s8, s6
    mv s9, a1
    mv t2, a2
    j .L243
.L243:
    mv s6, t4
    mv t1, s8
    mv s8, s9
    mv s9, t2
    mv t3, s6
    mv s10, t1
    mv s7, s8
    mv t0, s9
    j .L244
.L244:
    li s6, 5
    sub s8, s7, s6
    slt s6, s10, s8
    mv s8, t3
    mv s9, t0
    mv s4, s8
    mv s8, s9
    bnez s6, .L260
    j .L288
.L260:
    li s6, 1
    add s9, t3, s6
    li s6, 3
    slt t1, s6, s9
    mv s6, t0
    mv t0, s6
    bnez t1, .L281
    j .L287
.L281:
    li s6, 4
    li t1, 0
    add t2, s6, t1
    mv s6, t2
    mv t0, s6
    j .L287
.L287:
    mv s6, s9
    mv s9, t0
    mv s4, s6
    mv s8, s9
    j .L288
.L288:
    mv a0, s8
    call printInt
    li s6, 1
    add s9, s5, s6
    mv s6, s9
    mv s9, s4
    mv s4, s10
    mv s10, s7
    mv s7, s8
    mv s5, s6
    mv s2, s9
    mv s3, s4
    mv t5, s10
    sw t5, 484(sp)
    mv t5, s7
    sw t5, 480(sp)
    j .L99
.L303:
    li a0, 0
    call __builtin_exit
    li s1, 0
    mv a0, s1
    j .L1
.L1:
    lw s1, 488(sp)
    lw s2, 492(sp)
    lw s3, 496(sp)
    lw s4, 500(sp)
    lw s5, 504(sp)
    lw s6, 508(sp)
    lw s7, 512(sp)
    lw s8, 516(sp)
    lw s9, 520(sp)
    lw s10, 524(sp)
    lw s0, 536(sp)
    lw ra, 540(sp)
    addi sp, sp, 544
    jr ra
    .globl process_event
    .type process_event, @function
process_event:
    addi sp, sp, -48
    sw ra, 44(sp)
    sw s0, 40(sp)
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    sw s5, 16(sp)
    sw s6, 20(sp)
    sw s7, 24(sp)
    sw s8, 28(sp)
    sw s9, 32(sp)
    sw s10, 36(sp)
    addi s0, sp, 48
    mv s1, a0
    mv s2, a1
    mv s3, a2
    mv s4, a4
    li s5, 0
    sub s6, s1, s5
    seqz s6, s6
    bnez s6, .L325
    j .L342
.L325:
    li s5, 0
    sub s6, s2, s5
    seqz s6, s6
    mv s5, s1
    mv s7, s5
    bnez s6, .L335
    j .L341
.L335:
    li s5, 1
    li s6, 0
    add s8, s5, s6
    mv s5, s8
    mv s7, s5
    j .L341
.L341:
    mv s5, s7
    mv s6, s5
    j .L543
.L342:
    li s5, 1
    sub s7, s1, s5
    seqz s7, s7
    bnez s7, .L352
    j .L386
.L352:
    li s5, 1
    sub s7, s2, s5
    seqz s7, s7
    bnez s7, .L362
    j .L368
.L362:
    li s5, 2
    li s7, 0
    add s8, s5, s7
    mv s5, s8
    mv s7, s5
    j .L385
.L368:
    li s5, 6
    sub s8, s2, s5
    seqz s8, s8
    mv s5, s1
    mv s9, s5
    bnez s8, .L378
    j .L384
.L378:
    li s5, 0
    li s8, 0
    add s10, s5, s8
    mv s5, s10
    mv s9, s5
    j .L384
.L384:
    mv s5, s9
    mv s7, s5
    j .L385
.L385:
    mv s5, s7
    mv s7, s5
    j .L542
.L386:
    li s5, 2
    sub s8, s1, s5
    seqz s8, s8
    bnez s8, .L396
    j .L484
.L396:
    li s5, 2
    sub s8, s2, s5
    seqz s8, s8
    bnez s8, .L406
    j .L424
.L406:
    mv a0, s3
    call validate_checksum
    mv s5, a0
    li s8, 0
    sub s9, s5, s8
    snez s9, s9
    bnez s9, .L416
    j .L417
.L416:
    mv s5, s1
    mv s8, s5
    j .L423
.L417:
    li s5, 4
    li s9, 0
    add s10, s5, s9
    mv s5, s10
    mv s8, s5
    j .L423
.L423:
    mv s5, s8
    mv s8, s5
    j .L483
.L424:
    li s5, 3
    sub s9, s2, s5
    seqz s9, s9
    bnez s9, .L434
    j .L448
.L434:
    slt s5, s4, s3
    bnez s5, .L446
    j .L447
.L446:
    j .L447
.L447:
    mv s4, s1
    mv s5, s4
    j .L482
.L448:
    li s4, 4
    sub s9, s2, s4
    seqz s9, s9
    bnez s9, .L458
    j .L464
.L458:
    li s4, 3
    li s9, 0
    add s10, s4, s9
    mv s4, s10
    mv s9, s4
    j .L481
.L464:
    li s4, 7
    sub s10, s2, s4
    seqz s10, s10
    mv s4, s1
    mv t0, s4
    bnez s10, .L474
    j .L480
.L474:
    li s4, 4
    li s10, 0
    add t1, s4, s10
    mv s4, t1
    mv t0, s4
    j .L480
.L480:
    mv s4, t0
    mv s9, s4
    j .L481
.L481:
    mv s4, s9
    mv s5, s4
    j .L482
.L482:
    mv s4, s5
    mv s8, s4
    j .L483
.L483:
    mv s4, s8
    mv s5, s4
    j .L541
.L484:
    li s4, 3
    sub s8, s1, s4
    seqz s8, s8
    bnez s8, .L494
    j .L528
.L494:
    li s4, 5
    sub s8, s2, s4
    seqz s8, s8
    bnez s8, .L504
    j .L510
.L504:
    li s4, 0
    li s8, 0
    add s9, s4, s8
    mv s4, s9
    mv s8, s4
    j .L527
.L510:
    li s4, 6
    sub s9, s2, s4
    seqz s9, s9
    mv s4, s1
    mv s10, s4
    bnez s9, .L520
    j .L526
.L520:
    li s4, 0
    li s9, 0
    add t0, s4, s9
    mv s4, t0
    mv s10, s4
    j .L526
.L526:
    mv s4, s10
    mv s8, s4
    j .L527
.L527:
    mv s4, s8
    mv s8, s4
    j .L540
.L528:
    li s4, 4
    sub s9, s1, s4
    seqz s9, s9
    bnez s9, .L538
    j .L539
.L538:
    j .L539
.L539:
    mv s4, s1
    mv s8, s4
    j .L540
.L540:
    mv s1, s8
    mv s5, s1
    j .L541
.L541:
    mv s1, s5
    mv s7, s1
    j .L542
.L542:
    mv s1, s7
    mv s6, s1
    j .L543
.L543:
    mv a0, s6
    mv a1, s2
    mv a2, s3
    call complex_state_logic
    mv s1, a0
    mv a0, s1
    j .L2
.L2:
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw s4, 12(sp)
    lw s5, 16(sp)
    lw s6, 20(sp)
    lw s7, 24(sp)
    lw s8, 28(sp)
    lw s9, 32(sp)
    lw s10, 36(sp)
    lw s0, 40(sp)
    lw ra, 44(sp)
    addi sp, sp, 48
    jr ra
    .globl validate_checksum
    .type validate_checksum, @function
validate_checksum:
    addi sp, sp, -32
    sw ra, 28(sp)
    sw s0, 24(sp)
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    sw s5, 16(sp)
    sw s6, 20(sp)
    addi s0, sp, 32
    mv s1, a0
    li s2, 0
    li s3, 0
    add s4, s2, s3
    li s2, 1
    li s3, 0
    add s5, s2, s3
    mv s2, s4
    mv s3, s5
    mv s4, s2
    mv s2, s3
    j .L569
.L569:
    slt s3, s1, s2
    xori s3, s3, 1
    bnez s3, .L579
    j .L621
.L579:
    rem s3, s1, s2
    li s5, 0
    sub s6, s3, s5
    seqz s6, s6
    mv s3, s4
    mv s5, s3
    bnez s6, .L595
    j .L609
.L595:
    add s3, s4, s2
    mv s6, s3
    mv s5, s6
    j .L609
.L609:
    li s3, 1
    add s6, s2, s3
    mv s3, s5
    mv s5, s6
    mv s4, s3
    mv s2, s5
    j .L569
.L621:
    li s1, 2
    rem s2, s4, s1
    li s1, 0
    sub s3, s2, s1
    seqz s3, s3
    mv s1, s3
    mv a0, s1
    j .L3
.L3:
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw s4, 12(sp)
    lw s5, 16(sp)
    lw s6, 20(sp)
    lw s0, 24(sp)
    lw ra, 28(sp)
    addi sp, sp, 32
    jr ra
    .globl complex_state_logic
    .type complex_state_logic, @function
complex_state_logic:
    addi sp, sp, -32
    sw ra, 28(sp)
    sw s0, 24(sp)
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    sw s5, 16(sp)
    sw s6, 20(sp)
    addi s0, sp, 32
    mv s1, a0
    mv s2, a1
    mv s3, a2
    li s4, 6
    sub s5, s2, s4
    seqz s5, s5
    mv s2, s1
    mv s4, s2
    bnez s5, .L661
    j .L685
.L661:
    li s2, 2
    sub s5, s1, s2
    seqz s5, s5
    mv s2, s1
    mv s6, s2
    bnez s5, .L671
    j .L684
.L671:
    mv a0, s1
    mv a1, s3
    call perform_recovery
    mv s1, a0
    mv s2, s1
    mv s6, s2
    j .L684
.L684:
    mv s1, s6
    mv s4, s1
    j .L685
.L685:
    li s1, 0
    li s2, 0
    add s5, s1, s2
    mv s1, s3
    mv s2, s5
    mv s3, s1
    mv s1, s2
    j .L693
.L693:
    li s2, 5
    slt s5, s1, s2
    bnez s5, .L701
    j .L743
.L701:
    li s2, 2
    add s5, s1, s2
    div s2, s3, s5
    mul s5, s1, s1
    add s6, s2, s5
    li s2, 1
    add s5, s1, s2
    mv s2, s6
    mv s6, s5
    mv s3, s2
    mv s1, s6
    j .L693
.L743:
    li s1, 10
    rem s2, s3, s1
    li s1, 0
    sub s3, s2, s1
    seqz s3, s3
    mv s1, s4
    mv s2, s1
    bnez s3, .L758
    j .L775
.L758:
    li s1, 4
    sub s3, s4, s1
    snez s3, s3
    mv s1, s4
    mv s4, s1
    bnez s3, .L768
    j .L774
.L768:
    li s1, 4
    li s3, 0
    add s5, s1, s3
    mv s1, s5
    mv s4, s1
    j .L774
.L774:
    mv s1, s4
    mv s2, s1
    j .L775
.L775:
    mv a0, s2
    j .L4
.L4:
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw s4, 12(sp)
    lw s5, 16(sp)
    lw s6, 20(sp)
    lw s0, 24(sp)
    lw ra, 28(sp)
    addi sp, sp, 32
    jr ra
    .globl perform_recovery
    .type perform_recovery, @function
perform_recovery:
    addi sp, sp, -48
    sw ra, 44(sp)
    sw s0, 40(sp)
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    sw s5, 16(sp)
    sw s6, 20(sp)
    sw s7, 24(sp)
    addi s0, sp, 48
    mv s1, a0
    mv s2, a1
    li s3, 0
    li s4, 0
    add s5, s3, s4
    li s3, 0
    li s4, 0
    add s6, s3, s4
    mv s3, s6
    mv s4, s5
    mv s5, s3
    mv s3, s4
    j .L788
.L788:
    li s4, 10
    slt s6, s5, s4
    bnez s6, .L796
    j .L833
.L796:
    li s4, 1
    add s6, s5, s4
    rem s4, s2, s6
    add s6, s3, s4
    li s4, 1
    add s7, s5, s4
    mv s4, s7
    mv s7, s6
    mv s5, s4
    mv s3, s7
    j .L788
.L833:
    li s2, 20
    slt s4, s2, s3
    bnez s4, .L844
    j .L850
.L844:
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
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw s4, 12(sp)
    lw s5, 16(sp)
    lw s6, 20(sp)
    lw s7, 24(sp)
    lw s0, 40(sp)
    lw ra, 44(sp)
    addi sp, sp, 48
    jr ra
    .globl another_layer_of_protocol
    .type another_layer_of_protocol, @function
another_layer_of_protocol:
    addi sp, sp, -48
    sw ra, 44(sp)
    sw s0, 40(sp)
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    sw s5, 16(sp)
    sw s6, 20(sp)
    sw s7, 24(sp)
    addi s0, sp, 48
    mv s1, a0
    mv s2, a1
    li s3, 2
    sub s4, s1, s3
    seqz s4, s4
    bnez s4, .L869
    j .L907
.L869:
    li s3, 0
    li s4, 0
    add s5, s3, s4
    mv s3, s5
    mv s4, s2
    mv s5, s3
    mv s3, s4
    j .L873
.L873:
    li s4, 5
    slt s6, s5, s4
    bnez s6, .L881
    j .L906
.L881:
    add s4, s3, s5
    li s6, 1
    add s7, s5, s6
    mv s6, s7
    mv s7, s4
    mv s5, s6
    mv s3, s7
    j .L873
.L906:
    mv s4, s3
    mv s3, s4
    j .L930
.L907:
    li s4, 3
    sub s5, s1, s4
    seqz s5, s5
    mv s1, s2
    mv s4, s1
    bnez s5, .L917
    j .L929
.L917:
    li s1, 10
    sub s5, s2, s1
    mv s1, s5
    mv s4, s1
    j .L929
.L929:
    mv s1, s4
    mv s3, s1
    j .L930
.L930:
    mv a0, s3
    j .L6
.L6:
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw s4, 12(sp)
    lw s5, 16(sp)
    lw s6, 20(sp)
    lw s7, 24(sp)
    lw s0, 40(sp)
    lw ra, 44(sp)
    addi sp, sp, 48
    jr ra
    .globl yet_another_protocol_function
    .type yet_another_protocol_function, @function
yet_another_protocol_function:
    addi sp, sp, -32
    sw ra, 28(sp)
    sw s0, 24(sp)
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    sw s5, 16(sp)
    addi s0, sp, 32
    mv s1, a0
    mv s2, a1
    add s3, s1, s2
    li s1, 0
    li s2, 0
    add s4, s1, s2
    mv s1, s4
    mv s2, s3
    mv s3, s1
    mv s1, s2
    j .L951
.L951:
    li s2, 3
    slt s4, s3, s2
    bnez s4, .L959
    j .L983
.L959:
    mv a0, s3
    mv a1, s1
    call another_layer_of_protocol
    mv s2, a0
    li s4, 1
    add s5, s3, s4
    mv s4, s5
    mv s5, s2
    mv s3, s4
    mv s1, s5
    j .L951
.L983:
    mv a0, s1
    j .L7
.L7:
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw s4, 12(sp)
    lw s5, 16(sp)
    lw s0, 24(sp)
    lw ra, 28(sp)
    addi sp, sp, 32
    jr ra
    .globl process_complex_packet
    .type process_complex_packet, @function
process_complex_packet:
    addi sp, sp, -32
    sw ra, 28(sp)
    sw s0, 24(sp)
    sw s1, 0(sp)
    sw s2, 4(sp)
    sw s3, 8(sp)
    sw s4, 12(sp)
    addi s0, sp, 32
    mv s1, a0
    mv s2, a1
    mv s3, a2
    mv a0, s1
    mv a1, s2
    call yet_another_protocol_function
    mv s4, a0
    mv a0, s2
    mv a1, s3
    call yet_another_protocol_function
    mv s2, a0
    mv a0, s1
    mv a1, s3
    call yet_another_protocol_function
    mv s1, a0
    sub s3, s4, s2
    add s2, s3, s1
    mv a0, s2
    j .L8
.L8:
    lw s1, 0(sp)
    lw s2, 4(sp)
    lw s3, 8(sp)
    lw s4, 12(sp)
    lw s0, 24(sp)
    lw ra, 28(sp)
    addi sp, sp, 32
    jr ra
