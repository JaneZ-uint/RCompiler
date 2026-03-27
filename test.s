    .text
    .globl setup_scene
    .type setup_scene, @function
setup_scene:
    addi sp, sp, -608
    sw ra, 604(sp)
    sw s0, 600(sp)
    addi s0, sp, 608
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 76(sp)
    addi t0, sp, 80
    sw t0, 108(sp)
    addi t0, sp, 112
    sw t0, 124(sp)
    addi t0, sp, 128
    sw t0, 140(sp)
    addi t0, sp, 144
    sw t0, 172(sp)
    addi t0, sp, 176
    sw t0, 188(sp)
    addi t0, sp, 192
    sw t0, 204(sp)
    addi t0, sp, 208
    sw t0, 236(sp)
    addi t0, sp, 240
    sw t0, 252(sp)
    addi t0, sp, 256
    sw t0, 268(sp)
    addi t0, sp, 272
    sw t0, 288(sp)
    addi t0, sp, 292
    sw t0, 304(sp)
    addi t0, sp, 308
    sw t0, 324(sp)
    addi t0, sp, 328
    sw t0, 340(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 344(sp)
    lw a0, 44(sp)
    li a1, 0
    li a2, 28
    call memset
    lw a0, 60(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 60(sp)
    addi t0, t0, 0
    sw t0, 348(sp)
    li t0, 0
    lw t1, 348(sp)
    sw t0, 0(t1)
    lw t0, 60(sp)
    addi t0, t0, 4
    sw t0, 352(sp)
    li t0, -80
    lw t1, 352(sp)
    sw t0, 0(t1)
    li t0, 3
    li t1, 80
    mul t0, t0, t1
    sw t0, 356(sp)
    lw t0, 60(sp)
    addi t0, t0, 8
    sw t0, 360(sp)
    lw t0, 356(sp)
    lw t1, 360(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    addi t0, t0, 0
    sw t0, 364(sp)
    lw a0, 364(sp)
    lw a1, 60(sp)
    li a2, 12
    call memcpy
    li t0, 1
    li t1, 80
    mul t0, t0, t1
    sw t0, 368(sp)
    lw t0, 44(sp)
    addi t0, t0, 12
    sw t0, 372(sp)
    lw t0, 368(sp)
    lw t1, 372(sp)
    sw t0, 0(t1)
    lw a0, 76(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 76(sp)
    addi t0, t0, 0
    sw t0, 376(sp)
    li t0, 255
    lw t1, 376(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    addi t0, t0, 4
    sw t0, 380(sp)
    li t0, 0
    lw t1, 380(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    addi t0, t0, 8
    sw t0, 384(sp)
    li t0, 0
    lw t1, 384(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    addi t0, t0, 16
    sw t0, 388(sp)
    lw a0, 388(sp)
    lw a1, 76(sp)
    li a2, 12
    call memcpy
    lw a0, 344(sp)
    lw a1, 44(sp)
    li a2, 28
    call memcpy
    lw t0, 0(sp)
    addi t0, t0, 28
    sw t0, 392(sp)
    lw a0, 108(sp)
    li a1, 0
    li a2, 28
    call memset
    lw a0, 124(sp)
    li a1, 0
    li a2, 12
    call memset
    li t0, 2
    li t1, 80
    mul t0, t0, t1
    sw t0, 396(sp)
    lw t0, 124(sp)
    addi t0, t0, 0
    sw t0, 400(sp)
    lw t0, 396(sp)
    lw t1, 400(sp)
    sw t0, 0(t1)
    lw t0, 124(sp)
    addi t0, t0, 4
    sw t0, 404(sp)
    li t0, 0
    lw t1, 404(sp)
    sw t0, 0(t1)
    li t0, 4
    li t1, 80
    mul t0, t0, t1
    sw t0, 408(sp)
    lw t0, 124(sp)
    addi t0, t0, 8
    sw t0, 412(sp)
    lw t0, 408(sp)
    lw t1, 412(sp)
    sw t0, 0(t1)
    lw t0, 108(sp)
    addi t0, t0, 0
    sw t0, 416(sp)
    lw a0, 416(sp)
    lw a1, 124(sp)
    li a2, 12
    call memcpy
    li t0, 1
    li t1, 80
    mul t0, t0, t1
    sw t0, 420(sp)
    lw t0, 108(sp)
    addi t0, t0, 12
    sw t0, 424(sp)
    lw t0, 420(sp)
    lw t1, 424(sp)
    sw t0, 0(t1)
    lw a0, 140(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 140(sp)
    addi t0, t0, 0
    sw t0, 428(sp)
    li t0, 0
    lw t1, 428(sp)
    sw t0, 0(t1)
    lw t0, 140(sp)
    addi t0, t0, 4
    sw t0, 432(sp)
    li t0, 0
    lw t1, 432(sp)
    sw t0, 0(t1)
    lw t0, 140(sp)
    addi t0, t0, 8
    sw t0, 436(sp)
    li t0, 255
    lw t1, 436(sp)
    sw t0, 0(t1)
    lw t0, 108(sp)
    addi t0, t0, 16
    sw t0, 440(sp)
    lw a0, 440(sp)
    lw a1, 140(sp)
    li a2, 12
    call memcpy
    lw a0, 392(sp)
    lw a1, 108(sp)
    li a2, 28
    call memcpy
    lw t0, 0(sp)
    addi t0, t0, 56
    sw t0, 444(sp)
    lw a0, 172(sp)
    li a1, 0
    li a2, 28
    call memset
    lw a0, 188(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 188(sp)
    addi t0, t0, 0
    sw t0, 448(sp)
    li t0, -160
    lw t1, 448(sp)
    sw t0, 0(t1)
    lw t0, 188(sp)
    addi t0, t0, 4
    sw t0, 452(sp)
    li t0, 0
    lw t1, 452(sp)
    sw t0, 0(t1)
    li t0, 4
    li t1, 80
    mul t0, t0, t1
    sw t0, 456(sp)
    lw t0, 188(sp)
    addi t0, t0, 8
    sw t0, 460(sp)
    lw t0, 456(sp)
    lw t1, 460(sp)
    sw t0, 0(t1)
    lw t0, 172(sp)
    addi t0, t0, 0
    sw t0, 464(sp)
    lw a0, 464(sp)
    lw a1, 188(sp)
    li a2, 12
    call memcpy
    li t0, 1
    li t1, 80
    mul t0, t0, t1
    sw t0, 468(sp)
    lw t0, 172(sp)
    addi t0, t0, 12
    sw t0, 472(sp)
    lw t0, 468(sp)
    lw t1, 472(sp)
    sw t0, 0(t1)
    lw a0, 204(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 204(sp)
    addi t0, t0, 0
    sw t0, 476(sp)
    li t0, 0
    lw t1, 476(sp)
    sw t0, 0(t1)
    lw t0, 204(sp)
    addi t0, t0, 4
    sw t0, 480(sp)
    li t0, 255
    lw t1, 480(sp)
    sw t0, 0(t1)
    lw t0, 204(sp)
    addi t0, t0, 8
    sw t0, 484(sp)
    li t0, 0
    lw t1, 484(sp)
    sw t0, 0(t1)
    lw t0, 172(sp)
    addi t0, t0, 16
    sw t0, 488(sp)
    lw a0, 488(sp)
    lw a1, 204(sp)
    li a2, 12
    call memcpy
    lw a0, 444(sp)
    lw a1, 172(sp)
    li a2, 28
    call memcpy
    lw t0, 0(sp)
    addi t0, t0, 84
    sw t0, 492(sp)
    lw a0, 236(sp)
    li a1, 0
    li a2, 28
    call memset
    lw a0, 252(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 252(sp)
    addi t0, t0, 0
    sw t0, 496(sp)
    li t0, 0
    lw t1, 496(sp)
    sw t0, 0(t1)
    lw t0, 252(sp)
    addi t0, t0, 4
    sw t0, 500(sp)
    li t0, -16080
    lw t1, 500(sp)
    sw t0, 0(t1)
    lw t0, 252(sp)
    addi t0, t0, 8
    sw t0, 504(sp)
    li t0, 0
    lw t1, 504(sp)
    sw t0, 0(t1)
    lw t0, 236(sp)
    addi t0, t0, 0
    sw t0, 508(sp)
    lw a0, 508(sp)
    lw a1, 252(sp)
    li a2, 12
    call memcpy
    li t0, 200
    li t1, 80
    mul t0, t0, t1
    sw t0, 512(sp)
    lw t0, 236(sp)
    addi t0, t0, 12
    sw t0, 516(sp)
    lw t0, 512(sp)
    lw t1, 516(sp)
    sw t0, 0(t1)
    lw a0, 268(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 268(sp)
    addi t0, t0, 0
    sw t0, 520(sp)
    li t0, 200
    lw t1, 520(sp)
    sw t0, 0(t1)
    lw t0, 268(sp)
    addi t0, t0, 4
    sw t0, 524(sp)
    li t0, 200
    lw t1, 524(sp)
    sw t0, 0(t1)
    lw t0, 268(sp)
    addi t0, t0, 8
    sw t0, 528(sp)
    li t0, 0
    lw t1, 528(sp)
    sw t0, 0(t1)
    lw t0, 236(sp)
    addi t0, t0, 16
    sw t0, 532(sp)
    lw a0, 532(sp)
    lw a1, 268(sp)
    li a2, 12
    call memcpy
    lw a0, 492(sp)
    lw a1, 236(sp)
    li a2, 28
    call memcpy
    lw t0, 4(sp)
    addi t0, t0, 0
    sw t0, 536(sp)
    lw a0, 288(sp)
    li a1, 0
    li a2, 16
    call memset
    lw a0, 304(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 304(sp)
    addi t0, t0, 0
    sw t0, 540(sp)
    li t0, -1600
    lw t1, 540(sp)
    sw t0, 0(t1)
    li t0, 20
    li t1, 80
    mul t0, t0, t1
    sw t0, 544(sp)
    lw t0, 304(sp)
    addi t0, t0, 4
    sw t0, 548(sp)
    lw t0, 544(sp)
    lw t1, 548(sp)
    sw t0, 0(t1)
    lw t0, 304(sp)
    addi t0, t0, 8
    sw t0, 552(sp)
    li t0, -1600
    lw t1, 552(sp)
    sw t0, 0(t1)
    lw t0, 288(sp)
    addi t0, t0, 0
    sw t0, 556(sp)
    lw a0, 556(sp)
    lw a1, 304(sp)
    li a2, 12
    call memcpy
    lw t0, 288(sp)
    addi t0, t0, 12
    sw t0, 560(sp)
    li t0, 150
    lw t1, 560(sp)
    sw t0, 0(t1)
    lw a0, 536(sp)
    lw a1, 288(sp)
    li a2, 16
    call memcpy
    lw t0, 4(sp)
    addi t0, t0, 16
    sw t0, 564(sp)
    lw a0, 324(sp)
    li a1, 0
    li a2, 16
    call memset
    lw a0, 340(sp)
    li a1, 0
    li a2, 12
    call memset
    li t0, 20
    li t1, 80
    mul t0, t0, t1
    sw t0, 568(sp)
    lw t0, 340(sp)
    addi t0, t0, 0
    sw t0, 572(sp)
    lw t0, 568(sp)
    lw t1, 572(sp)
    sw t0, 0(t1)
    li t0, 30
    li t1, 80
    mul t0, t0, t1
    sw t0, 576(sp)
    lw t0, 340(sp)
    addi t0, t0, 4
    sw t0, 580(sp)
    lw t0, 576(sp)
    lw t1, 580(sp)
    sw t0, 0(t1)
    lw t0, 340(sp)
    addi t0, t0, 8
    sw t0, 584(sp)
    li t0, -800
    lw t1, 584(sp)
    sw t0, 0(t1)
    lw t0, 324(sp)
    addi t0, t0, 0
    sw t0, 588(sp)
    lw a0, 588(sp)
    lw a1, 340(sp)
    li a2, 12
    call memcpy
    lw t0, 324(sp)
    addi t0, t0, 12
    sw t0, 592(sp)
    li t0, 120
    lw t1, 592(sp)
    sw t0, 0(t1)
    lw a0, 564(sp)
    lw a1, 324(sp)
    li a2, 16
    call memcpy
    lw a0, 596(sp)
    j .L1
.L1:
    lw ra, 604(sp)
    lw s0, 600(sp)
    addi sp, sp, 608
    jr ra
    .globl vec_dot
    .type vec_dot, @function
vec_dot:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 16(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 20(sp)
    lw t0, 4(sp)
    addi t0, t0, 0
    sw t0, 24(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 20(sp)
    lw t1, 28(sp)
    mul t0, t0, t1
    sw t0, 32(sp)
    lw t0, 0(sp)
    addi t0, t0, 4
    sw t0, 36(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 4(sp)
    addi t0, t0, 4
    sw t0, 44(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 40(sp)
    lw t1, 48(sp)
    mul t0, t0, t1
    sw t0, 52(sp)
    lw t0, 32(sp)
    lw t1, 52(sp)
    add t0, t0, t1
    sw t0, 56(sp)
    lw t0, 0(sp)
    addi t0, t0, 8
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 4(sp)
    addi t0, t0, 8
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 64(sp)
    lw t1, 72(sp)
    mul t0, t0, t1
    sw t0, 76(sp)
    lw t0, 56(sp)
    lw t1, 76(sp)
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    li t1, 80
    div t0, t0, t1
    sw t0, 84(sp)
    lw a0, 84(sp)
    j .L2
.L2:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl vec_sub
    .type vec_sub, @function
vec_sub:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 36(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw a0, 36(sp)
    li a1, 0
    li a2, 12
    call memset
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 4(sp)
    addi t0, t0, 0
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 44(sp)
    lw t1, 52(sp)
    sub t0, t0, t1
    sw t0, 56(sp)
    lw t0, 36(sp)
    addi t0, t0, 0
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 4
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 4(sp)
    addi t0, t0, 4
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 68(sp)
    lw t1, 76(sp)
    sub t0, t0, t1
    sw t0, 80(sp)
    lw t0, 36(sp)
    addi t0, t0, 4
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 8
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 4(sp)
    addi t0, t0, 8
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 92(sp)
    lw t1, 100(sp)
    sub t0, t0, t1
    sw t0, 104(sp)
    lw t0, 36(sp)
    addi t0, t0, 8
    sw t0, 108(sp)
    lw t0, 104(sp)
    lw t1, 108(sp)
    sw t0, 0(t1)
    lw a0, 8(sp)
    lw a1, 36(sp)
    li a2, 12
    call memcpy
    lw a0, 112(sp)
    j .L3
.L3:
    lw t0, 8(sp)
    mv a0, t0
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl intersect
    .type intersect, @function
intersect:
    addi sp, sp, -240
    sw ra, 236(sp)
    sw s0, 232(sp)
    addi s0, sp, 240
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    addi t0, sp, 72
    sw t0, 76(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 80(sp)
    lw t0, 4(sp)
    addi t0, t0, 0
    sw t0, 84(sp)
    lw a0, 80(sp)
    lw a1, 84(sp)
    lw a2, 44(sp)
    call vec_sub
    sw a0, 44(sp)
    lw a0, 28(sp)
    lw a1, 44(sp)
    li a2, 12
    call memcpy
    lw t0, 0(sp)
    addi t0, t0, 12
    sw t0, 88(sp)
    lw t0, 0(sp)
    addi t0, t0, 12
    sw t0, 92(sp)
    lw a0, 88(sp)
    lw a1, 92(sp)
    call vec_dot
    sw a0, 96(sp)
    lw t0, 96(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 12
    sw t0, 100(sp)
    lw a0, 28(sp)
    lw a1, 100(sp)
    call vec_dot
    sw a0, 104(sp)
    li t0, 2
    lw t1, 104(sp)
    mul t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw a0, 28(sp)
    lw a1, 28(sp)
    call vec_dot
    sw a0, 112(sp)
    lw t0, 4(sp)
    addi t0, t0, 12
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 4(sp)
    addi t0, t0, 12
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 120(sp)
    lw t1, 128(sp)
    mul t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    li t1, 80
    div t0, t0, t1
    sw t0, 136(sp)
    lw t0, 112(sp)
    lw t1, 136(sp)
    sub t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 144(sp)
    lw t1, 148(sp)
    mul t0, t0, t1
    sw t0, 152(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    li t0, 4
    lw t1, 156(sp)
    mul t0, t0, t1
    sw t0, 160(sp)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 160(sp)
    lw t1, 164(sp)
    mul t0, t0, t1
    sw t0, 168(sp)
    lw t0, 168(sp)
    li t1, 80
    div t0, t0, t1
    sw t0, 172(sp)
    lw t0, 152(sp)
    lw t1, 172(sp)
    sub t0, t0, t1
    sw t0, 176(sp)
    lw t0, 176(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 180(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 184(sp)
    lw t0, 184(sp)
    bnez t0, .L600
    j .L604
.L600:
    li a0, -1
    j .L4
.L604:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    li t0, 0
    lw t1, 188(sp)
    sub t0, t0, t1
    sw t0, 192(sp)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw a0, 196(sp)
    call isqrt
    sw a0, 200(sp)
    lw t0, 192(sp)
    lw t1, 200(sp)
    sub t0, t0, t1
    sw t0, 204(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    li t0, 2
    lw t1, 208(sp)
    mul t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    li t1, 80
    div t0, t0, t1
    sw t0, 216(sp)
    lw t0, 204(sp)
    lw t1, 216(sp)
    div t0, t0, t1
    sw t0, 220(sp)
    lw a0, 220(sp)
    j .L4
.L4:
    lw ra, 236(sp)
    lw s0, 232(sp)
    addi sp, sp, 240
    jr ra
    .globl isqrt
    .type isqrt, @function
isqrt:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 28(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 32(sp)
    lw t0, 32(sp)
    bnez t0, .L677
    j .L679
.L677:
    li a0, 0
    j .L5
.L679:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 36(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 40(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    li t1, 2
    div t0, t0, t1
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L698
.L698:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 52(sp)
    lw t1, 56(sp)
    slt t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L708
    j .L740
.L708:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    div t0, t0, t1
    sw t0, 80(sp)
    lw t0, 68(sp)
    lw t1, 80(sp)
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 2
    div t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L698
.L740:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw a0, 92(sp)
    j .L5
.L5:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl main
    .type main, @function
main:
    li t0, -34320
    add sp, sp, t0
    li t0, 34316
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 34312
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 34320
    add s0, sp, t0
    addi t0, sp, 96
    li t3, 16480
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16484
    add t0, sp, t1
    li t3, 16488
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16492
    add t0, sp, t1
    li t3, 16748
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16752
    add t0, sp, t1
    li t3, 33136
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33140
    add t0, sp, t1
    li t3, 33144
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33148
    add t0, sp, t1
    li t3, 33260
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33264
    add t0, sp, t1
    li t3, 33292
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33296
    add t0, sp, t1
    li t3, 33308
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33312
    add t0, sp, t1
    li t3, 33324
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33328
    add t0, sp, t1
    li t3, 33332
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33336
    add t0, sp, t1
    li t3, 33448
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33452
    add t0, sp, t1
    li t3, 33484
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33488
    add t0, sp, t1
    li t3, 33504
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33508
    add t0, sp, t1
    li t3, 33520
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33524
    add t0, sp, t1
    li t3, 33528
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33532
    add t0, sp, t1
    li t3, 33564
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33568
    add t0, sp, t1
    li t3, 33572
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33576
    add t0, sp, t1
    li t3, 33580
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33584
    add t0, sp, t1
    li t3, 33588
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33592
    add t0, sp, t1
    li t3, 33596
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33600
    add t0, sp, t1
    li t3, 33612
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33616
    add t0, sp, t1
    li t3, 33628
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33632
    add t0, sp, t1
    li t3, 33656
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33660
    add t0, sp, t1
    li t3, 33684
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33688
    add t0, sp, t1
    li t3, 33700
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33704
    add t0, sp, t1
    li t3, 33708
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33712
    add t0, sp, t1
    li t3, 33724
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33728
    add t0, sp, t1
    li t3, 33740
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33744
    add t0, sp, t1
    li t3, 33748
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33752
    add t0, sp, t1
    li t3, 33756
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33760
    add t0, sp, t1
    li t3, 33772
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33776
    add t0, sp, t1
    li t3, 33780
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 33784
    add t0, sp, t1
    li t3, 33788
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 16488
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L22
.L22:
    li t3, 16488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33792
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33792
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 64
    slt t0, t0, t1
    li t3, 33796
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33796
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L26
    j .L27
.L26:
    li t3, 16488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33800
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16748
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33800
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 33804
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33804
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 16488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33808
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33808
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33812
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33812
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16488
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L22
.L27:
    li t0, 0
    li t3, 33144
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L32
.L32:
    li t3, 33144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33816
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33816
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 64
    slt t0, t0, t1
    li t3, 33820
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33820
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L36
    j .L37
.L36:
    li t3, 33144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33824
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33136
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33824
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 256
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 33828
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33828
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 16748
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 256
    call memcpy
    li t3, 33144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33832
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33832
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33836
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33836
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33144
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L32
.L37:
    li t3, 16480
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33136
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 16384
    call memcpy
    li t3, 33292
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 28
    call memset
    li t3, 33308
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 12
    call memset
    li t3, 33308
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 33840
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33840
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33308
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 33844
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33844
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33308
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 33848
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33848
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33292
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 33852
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33852
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33308
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t3, 33292
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 12
    li t3, 33856
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33856
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33324
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 12
    call memset
    li t3, 33324
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 33860
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33860
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33324
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 33864
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33864
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33324
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 33868
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33868
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33292
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 16
    li t3, 33872
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33872
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33324
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t0, 0
    li t3, 33332
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L64
.L64:
    li t3, 33332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33876
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33876
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 4
    slt t0, t0, t1
    li t3, 33880
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33880
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L68
    j .L69
.L68:
    li t3, 33332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33884
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33448
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33884
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 28
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 33888
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33888
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33292
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 28
    call memcpy
    li t3, 33332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33892
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33892
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33896
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33896
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33332
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L64
.L69:
    li t3, 33260
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33448
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 112
    call memcpy
    li t3, 33504
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 16
    call memset
    li t3, 33520
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 12
    call memset
    li t3, 33520
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 33900
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33900
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33520
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 33904
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33904
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33520
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 33908
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33908
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33504
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 33912
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33912
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33520
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t3, 33504
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 12
    li t3, 33916
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 33916
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 33528
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L89
.L89:
    li t3, 33528
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33920
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33920
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2
    slt t0, t0, t1
    li t3, 33924
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33924
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L93
    j .L94
.L93:
    li t3, 33528
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33928
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33928
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 16
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 33932
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33932
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33504
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 16
    call memcpy
    li t3, 33528
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33936
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33936
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33940
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33940
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33528
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L89
.L94:
    li t3, 33484
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33564
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 32
    call memcpy
    li t3, 33260
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33484
    add t3, t3, sp
    lw a1, 0(t3)
    call setup_scene
    li t0, 64
    li t3, 33572
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 64
    li t3, 33580
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 33588
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L759
.L759:
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33944
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33580
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33948
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33944
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33948
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 33952
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33952
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L769
    j .L1026
.L769:
    li t0, 0
    li t3, 33596
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L773
.L773:
    li t3, 33596
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33956
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33960
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33956
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33960
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 33964
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33964
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L783
    j .L1014
.L783:
    li t3, 33628
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 12
    call memset
    li t3, 33596
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33968
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33972
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33972
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2
    div t0, t0, t1
    li t3, 33976
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33968
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33976
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    li t3, 33980
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33980
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 80
    mul t0, t0, t1
    li t3, 33984
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33988
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33988
    add t3, t3, sp
    lw t1, 0(t3)
    div t0, t0, t1
    li t3, 33992
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33628
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 33996
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33992
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33996
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34000
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33580
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34004
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34004
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2
    div t0, t0, t1
    li t3, 34008
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34000
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34008
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    li t3, 34012
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34012
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 80
    mul t0, t0, t1
    li t3, 34016
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33580
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34020
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34016
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34020
    add t3, t3, sp
    lw t1, 0(t3)
    div t0, t0, t1
    li t3, 34024
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33628
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 34028
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34024
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34028
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33628
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 34032
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 80
    li t3, 34032
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33612
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33628
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t3, 33684
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 24
    call memset
    li t3, 33700
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 12
    call memset
    li t3, 33700
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 34036
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 34036
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33700
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 34040
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 34040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33700
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 34044
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -80
    li t3, 34044
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33684
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 34048
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34048
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33700
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t3, 33684
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 12
    li t3, 34052
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34052
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33612
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t3, 33656
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33684
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 24
    call memcpy
    li t0, 10000
    li t1, 80
    mul t0, t0, t1
    li t3, 34056
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34056
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33708
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33740
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 0
    li a2, 12
    call memset
    li t3, 33740
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 34060
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 20
    li t3, 34060
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33740
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 34064
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 20
    li t3, 34064
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33740
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 34068
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 40
    li t3, 34068
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33724
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33740
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t0, 0
    li t3, 33748
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L874
.L874:
    li t3, 33748
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34072
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34072
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 4
    slt t0, t0, t1
    li t3, 34076
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34076
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L882
    j .L960
.L882:
    li t3, 33748
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34080
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33260
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34080
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 28
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 34084
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33656
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 34084
    add t3, t3, sp
    lw a1, 0(t3)
    call intersect
    li t3, 34088
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 34088
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33756
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L903
.L903:
    li t3, 33756
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34092
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34092
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t1, t0
    li t3, 34096
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 34100
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 34096
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L911
    j .L922
.L911:
    li t3, 33756
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34104
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33708
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34108
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34104
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34108
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 34112
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34112
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 34100
    add t3, t3, sp
    sw t1, 0(t3)
    j .L922
.L922:
    li t3, 34100
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L926
    j .L948
.L926:
    li t3, 33756
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34116
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34116
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33708
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33748
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34120
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33260
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34120
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 28
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 34124
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34124
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 16
    li t3, 34128
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33772
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 34128
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    li t3, 33724
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 33772
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 12
    call memcpy
    j .L948
.L948:
    li t3, 33748
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34132
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34132
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 34136
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34136
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33748
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L874
.L960:
    li t3, 33596
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34140
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16480
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34140
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 256
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 34144
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34148
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34144
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34148
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 34152
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33724
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 34156
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34156
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34160
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33724
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 34164
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34164
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34168
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34160
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34168
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 34172
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33724
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 34176
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34176
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34180
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34172
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34180
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 34184
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34184
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    div t0, t0, t1
    li t3, 34188
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34188
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34152
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33596
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34192
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34192
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 34196
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34196
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33596
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L773
.L1014:
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34200
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34200
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 34204
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34204
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33588
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L759
.L1026:
    li t0, 0
    li t3, 33780
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 33588
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1035
.L1035:
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33580
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34212
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34208
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34212
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 34216
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34216
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1045
    j .L1127
.L1045:
    li t0, 0
    li t3, 33788
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1049
.L1049:
    li t3, 33788
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34220
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34224
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34220
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34224
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 34228
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34228
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1059
    j .L1115
.L1059:
    li t3, 33780
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34232
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33788
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16480
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34236
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 256
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 34240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34244
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34240
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34244
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 34248
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34248
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34252
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33788
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34256
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34260
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34264
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34260
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34264
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 34268
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34256
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34268
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 34272
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34252
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34272
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 34276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34232
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 34276
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 34280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34280
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33780
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 33788
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34284
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34284
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 34288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34288
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33788
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1049
.L1115:
    li t3, 33588
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34292
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 34296
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34296
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33588
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1035
.L1127:
    li t3, 33780
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 34300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 34300
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li a0, 0
    call __builtin_exit
    li a0, 0
    j .L6
.L6:
    li t0, 34316
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 34312
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 34320
    add sp, sp, t0
    jr ra
