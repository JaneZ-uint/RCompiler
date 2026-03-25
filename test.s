    .text
    .globl main
    .type main, @function
main:
    li t0, -8416
    add sp, sp, t0
    li t0, 8412
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 8408
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 8416
    add s0, sp, t0
    addi t0, sp, 0
    li t3, 4096
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4100
    add t0, sp, t1
    li t3, 4104
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4108
    add t0, sp, t1
    li t3, 8204
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8208
    add t0, sp, t1
    li t3, 8212
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8216
    add t0, sp, t1
    li t3, 8220
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8224
    add t0, sp, t1
    li t3, 8228
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8232
    add t0, sp, t1
    li t3, 8236
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8240
    add t0, sp, t1
    li t3, 8244
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8248
    add t0, sp, t1
    li t3, 8252
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8256
    add t0, sp, t1
    li t3, 8260
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8264
    add t0, sp, t1
    li t3, 8268
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 4104
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L22
.L22:
    li t3, 4104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8272
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8272
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1024
    slt t0, t0, t1
    li t3, 8276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8276
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L26
    j .L27
.L26:
    li t3, 4104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8204
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8280
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8284
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8284
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 4104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8288
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8292
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 4104
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L22
.L27:
    li t3, 4096
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8204
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4096
    call memcpy
    li t3, 4096
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 8296
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 8296
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 4096
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 4
    li t3, 8300
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1020
    li t3, 8300
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 4096
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 8
    li t3, 8304
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 8304
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 4096
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 12
    li t3, 8308
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 8308
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 256
    call allocate
    li t3, 8312
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8312
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8212
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8212
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8316
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 128
    call allocate
    li t3, 8320
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8320
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8220
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8220
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8324
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 512
    call allocate
    li t3, 8328
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8328
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8228
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8228
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8332
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 8220
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8336
    add t3, t3, sp
    lw a1, 0(t3)
    call deallocate
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 64
    call allocate
    li t3, 8340
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8340
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8236
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8344
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 8212
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8348
    add t3, t3, sp
    lw a1, 0(t3)
    call deallocate
    li t3, 8228
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8352
    add t3, t3, sp
    lw a1, 0(t3)
    call deallocate
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 768
    call allocate
    li t3, 8356
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8356
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8244
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8360
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t0, 0
    li t3, 8252
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L133
.L133:
    li t3, 8252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8364
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10
    slt t0, t0, t1
    li t3, 8368
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8368
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L141
    j .L181
.L141:
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li a1, 10
    call allocate
    li t3, 8372
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8372
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8260
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8260
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8376
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, -1
    sub t0, t0, t1
    seqz t0, t0
    li t3, 8380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8380
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L159
    j .L169
.L159:
    li t0, -1
    li t3, 8268
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8384
    add t3, t3, sp
    lw a1, 0(t3)
    call deallocate
    j .L169
.L169:
    li t3, 8252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8388
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8388
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8392
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8392
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8252
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L133
.L181:
    li t3, 4096
    add t3, t3, sp
    lw a0, 0(t3)
    call print_memory_state
    li a0, 0
    call __builtin_exit
    li a0, 0
    j .L1
.L1:
    li t0, 8412
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 8408
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 8416
    add sp, sp, t0
    jr ra
    .globl allocate
    .type allocate, @function
allocate:
    addi sp, sp, -432
    sw ra, 428(sp)
    sw s0, 424(sp)
    addi s0, sp, 432
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 40(sp)
    addi t0, sp, 44
    sw t0, 48(sp)
    addi t0, sp, 52
    sw t0, 56(sp)
    addi t0, sp, 60
    sw t0, 64(sp)
    addi t0, sp, 68
    sw t0, 72(sp)
    addi t0, sp, 76
    sw t0, 80(sp)
    addi t0, sp, 84
    sw t0, 88(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, -1
    lw t1, 32(sp)
    sw t0, 0(t1)
    li t0, 1025
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L197
.L197:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 96(sp)
    lw t0, 96(sp)
    bnez t0, .L206
    j .L299
.L206:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 0(sp)
    lw t1, 100(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 0(sp)
    lw t1, 116(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 128(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 132(sp)
    lw t0, 132(sp)
    bnez t0, .L240
    j .L281
.L240:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 136(sp)
    lw t1, 140(sp)
    slt t0, t0, t1
    xori t0, t0, 1
    sw t0, 144(sp)
    lw t0, 144(sp)
    bnez t0, .L252
    j .L280
.L252:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 148(sp)
    lw t1, 152(sp)
    slt t0, t0, t1
    sw t0, 156(sp)
    lw t0, 156(sp)
    bnez t0, .L264
    j .L279
.L264:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 164(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L279
.L279:
    j .L280
.L280:
    j .L281
.L281:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 0(sp)
    lw t1, 172(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 176(sp)
    lw t0, 176(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L197
.L299:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 184(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 188(sp)
    lw t0, 188(sp)
    bnez t0, .L311
    j .L550
.L311:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 192(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 196(sp)
    lw t0, 0(sp)
    lw t1, 196(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 204(sp)
    lw t1, 64(sp)
    sw t0, 0(t1)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 208(sp)
    lw t1, 212(sp)
    sub t0, t0, t1
    sw t0, 216(sp)
    lw t0, 216(sp)
    li t1, 4
    sub t0, t0, t1
    sw t0, 220(sp)
    lw t0, 220(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 224(sp)
    li t1, 8
    slt t0, t1, t0
    sw t0, 228(sp)
    lw t0, 228(sp)
    bnez t0, .L349
    j .L524
.L349:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 232(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 236(sp)
    lw t0, 0(sp)
    lw t1, 236(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 240(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 244(sp)
    lw t1, 240(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 248(sp)
    lw t0, 0(sp)
    lw t1, 248(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 252(sp)
    li t0, 0
    lw t1, 252(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 256(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 260(sp)
    lw t0, 256(sp)
    lw t1, 260(sp)
    add t0, t0, t1
    sw t0, 264(sp)
    lw t0, 264(sp)
    li t1, 4
    add t0, t0, t1
    sw t0, 268(sp)
    lw t0, 268(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t0, 0(sp)
    lw t1, 272(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 276(sp)
    li t0, 1
    lw t1, 276(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 280(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 284(sp)
    lw t0, 0(sp)
    lw t1, 284(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 288(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 292(sp)
    lw t0, 292(sp)
    lw t1, 288(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 296(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 300(sp)
    lw t0, 0(sp)
    lw t1, 300(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 304(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 308(sp)
    lw t0, 308(sp)
    lw t1, 304(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 312(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 0(sp)
    lw t1, 316(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 320(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 324(sp)
    lw t0, 324(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 328(sp)
    lw t0, 0(sp)
    lw t1, 328(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 332(sp)
    lw t0, 332(sp)
    lw t0, 0(t0)
    sw t0, 336(sp)
    lw t0, 336(sp)
    lw t1, 320(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 340(sp)
    lw t0, 340(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 344(sp)
    lw t0, 0(sp)
    lw t1, 344(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 348(sp)
    lw t0, 348(sp)
    lw t0, 0(t0)
    sw t0, 352(sp)
    lw t0, 352(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 356(sp)
    lw t0, 356(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 360(sp)
    lw t0, 360(sp)
    bnez t0, .L488
    j .L506
.L488:
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 364(sp)
    lw t0, 364(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 368(sp)
    lw t0, 0(sp)
    lw t1, 368(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 372(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 376(sp)
    lw t0, 376(sp)
    lw t1, 372(sp)
    sw t0, 0(t1)
    j .L506
.L506:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 380(sp)
    lw t0, 380(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 384(sp)
    lw t0, 0(sp)
    lw t1, 384(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 388(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 392(sp)
    lw t0, 392(sp)
    lw t1, 388(sp)
    sw t0, 0(t1)
    j .L536
.L524:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 396(sp)
    lw t0, 0(sp)
    lw t1, 396(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 400(sp)
    li t0, 0
    lw t1, 400(sp)
    sw t0, 0(t1)
    j .L536
.L536:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 404(sp)
    lw t0, 404(sp)
    li t1, 4
    add t0, t0, t1
    sw t0, 408(sp)
    lw a0, 408(sp)
    j .L2
.L550:
    li a0, -1
    j .L2
.L2:
    lw ra, 428(sp)
    lw s0, 424(sp)
    addi sp, sp, 432
    jr ra
    .globl deallocate
    .type deallocate, @function
deallocate:
    addi sp, sp, -432
    sw ra, 428(sp)
    sw s0, 424(sp)
    addi s0, sp, 432
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 40(sp)
    addi t0, sp, 44
    sw t0, 48(sp)
    addi t0, sp, 52
    sw t0, 56(sp)
    addi t0, sp, 60
    sw t0, 64(sp)
    addi t0, sp, 68
    sw t0, 72(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 4
    slt t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    bnez t0, .L566
    j .L569
.L566:
    lw a0, 84(sp)
    j .L3
.L569:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 4
    sub t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 0(sp)
    lw t1, 96(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 100(sp)
    li t0, 1
    lw t1, 100(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 0(sp)
    lw t1, 108(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 120(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 124(sp)
    lw t0, 124(sp)
    bnez t0, .L614
    j .L743
.L614:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 0(sp)
    lw t1, 128(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 140(sp)
    lw t0, 140(sp)
    bnez t0, .L630
    j .L742
.L630:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 148(sp)
    lw t0, 0(sp)
    lw t1, 148(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 156(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 160(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 164(sp)
    lw t0, 0(sp)
    lw t1, 164(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 168(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 172(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 176(sp)
    lw t0, 0(sp)
    lw t1, 176(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 184(sp)
    lw t1, 188(sp)
    add t0, t0, t1
    sw t0, 192(sp)
    lw t0, 192(sp)
    li t1, 4
    add t0, t0, t1
    sw t0, 196(sp)
    lw t0, 196(sp)
    lw t1, 168(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 200(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 204(sp)
    lw t0, 0(sp)
    lw t1, 204(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 208(sp)
    lw t0, 208(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 212(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 216(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 220(sp)
    lw t0, 0(sp)
    lw t1, 220(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 224(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 228(sp)
    lw t0, 228(sp)
    lw t1, 224(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 232(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 236(sp)
    lw t0, 236(sp)
    bnez t0, .L723
    j .L741
.L723:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 240(sp)
    lw t0, 240(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 244(sp)
    lw t0, 0(sp)
    lw t1, 244(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 252(sp)
    lw t0, 252(sp)
    lw t1, 248(sp)
    sw t0, 0(t1)
    j .L741
.L741:
    j .L742
.L742:
    j .L743
.L743:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 256(sp)
    lw t0, 256(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 260(sp)
    lw t0, 0(sp)
    lw t1, 260(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 264(sp)
    lw t0, 264(sp)
    lw t0, 0(t0)
    sw t0, 268(sp)
    lw t0, 268(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t0, 272(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 276(sp)
    lw t0, 276(sp)
    bnez t0, .L769
    j .L898
.L769:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 0(sp)
    lw t1, 280(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 284(sp)
    lw t0, 284(sp)
    lw t0, 0(t0)
    sw t0, 288(sp)
    lw t0, 288(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 292(sp)
    lw t0, 292(sp)
    bnez t0, .L785
    j .L897
.L785:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 296(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 300(sp)
    lw t0, 0(sp)
    lw t1, 300(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 304(sp)
    lw t0, 304(sp)
    lw t0, 0(t0)
    sw t0, 308(sp)
    lw t0, 308(sp)
    lw t1, 64(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 312(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 0(sp)
    lw t1, 316(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 320(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 324(sp)
    lw t0, 324(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 328(sp)
    lw t0, 0(sp)
    lw t1, 328(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 332(sp)
    lw t0, 332(sp)
    lw t0, 0(t0)
    sw t0, 336(sp)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 340(sp)
    lw t0, 336(sp)
    lw t1, 340(sp)
    add t0, t0, t1
    sw t0, 344(sp)
    lw t0, 344(sp)
    li t1, 4
    add t0, t0, t1
    sw t0, 348(sp)
    lw t0, 348(sp)
    lw t1, 320(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 352(sp)
    lw t0, 352(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 356(sp)
    lw t0, 0(sp)
    lw t1, 356(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 360(sp)
    lw t0, 360(sp)
    lw t0, 0(t0)
    sw t0, 364(sp)
    lw t0, 364(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 368(sp)
    lw t0, 368(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 372(sp)
    lw t0, 0(sp)
    lw t1, 372(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 376(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 380(sp)
    lw t0, 380(sp)
    lw t1, 376(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 384(sp)
    lw t0, 384(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 388(sp)
    lw t0, 388(sp)
    bnez t0, .L878
    j .L896
.L878:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 392(sp)
    lw t0, 392(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 396(sp)
    lw t0, 0(sp)
    lw t1, 396(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 400(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 404(sp)
    lw t0, 404(sp)
    lw t1, 400(sp)
    sw t0, 0(t1)
    j .L896
.L896:
    j .L897
.L897:
    j .L898
.L898:
    lw a0, 408(sp)
    j .L3
.L3:
    lw ra, 428(sp)
    lw s0, 424(sp)
    addi sp, sp, 432
    jr ra
    .globl print_memory_state
    .type print_memory_state, @function
print_memory_state:
    addi sp, sp, -176
    sw ra, 172(sp)
    sw s0, 168(sp)
    addi s0, sp, 176
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    lw t0, 0(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 12(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 20(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 28(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L910
.L910:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L919
    j .L1010
.L919:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 0(sp)
    lw t1, 64(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 0(sp)
    lw t1, 80(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 96(sp)
    lw t0, 96(sp)
    bnez t0, .L953
    j .L978
.L953:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 100(sp)
    lw t1, 104(sp)
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L992
.L978:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 120(sp)
    lw t1, 124(sp)
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L992
.L992:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 132(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 136(sp)
    lw t0, 0(sp)
    lw t1, 136(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L910
.L1010:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw a0, 148(sp)
    call printlnInt
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw a0, 152(sp)
    call printlnInt
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw a0, 156(sp)
    call printlnInt
    lw a0, 160(sp)
    j .L4
.L4:
    lw ra, 172(sp)
    lw s0, 168(sp)
    addi sp, sp, 176
    jr ra
    .globl deep_recursive_check
    .type deep_recursive_check, @function
deep_recursive_check:
    addi sp, sp, -144
    sw ra, 140(sp)
    sw s0, 136(sp)
    addi s0, sp, 144
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 32(sp)
    li t1, 0
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 36(sp)
    lw t0, 36(sp)
    bnez t0, .L1034
    j .L1036
.L1034:
    li a0, 1
    j .L5
.L1036:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 40(sp)
    li t1, -1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L1048
    j .L1050
.L1048:
    li a0, 0
    j .L5
.L1050:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 0(sp)
    lw t1, 52(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 60(sp)
    li t1, 100
    slt t0, t1, t0
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L1071
    j .L1094
.L1071:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 68(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 72(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 0(sp)
    lw t1, 80(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw a0, 0(sp)
    lw a1, 72(sp)
    lw a2, 88(sp)
    call deep_recursive_check
    sw a0, 92(sp)
    lw a0, 92(sp)
    j .L5
.L1094:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 100(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 0(sp)
    lw t1, 108(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw a0, 0(sp)
    lw a1, 100(sp)
    lw a2, 116(sp)
    call deep_recursive_check
    sw a0, 120(sp)
    lw a0, 120(sp)
    j .L5
.L1117:
    li a0, 0
    j .L5
.L5:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl another_utility_function
    .type another_utility_function, @function
another_utility_function:
    addi sp, sp, -192
    sw ra, 188(sp)
    sw s0, 184(sp)
    addi s0, sp, 192
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 40(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 44(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L1127
.L1127:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L1136
    j .L1252
.L1136:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 0(sp)
    lw t1, 56(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L1152
    j .L1234
.L1152:
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L1156
.L1156:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 0(sp)
    lw t1, 80(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 72(sp)
    lw t1, 88(sp)
    slt t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    bnez t0, .L1176
    j .L1233
.L1176:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 4
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 104(sp)
    lw t1, 108(sp)
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 0(sp)
    lw t1, 112(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 3
    rem t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 132(sp)
    lw t0, 120(sp)
    lw t1, 132(sp)
    mul t0, t0, t1
    sw t0, 136(sp)
    lw t0, 96(sp)
    lw t1, 136(sp)
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L1156
.L1233:
    j .L1234
.L1234:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 152(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 156(sp)
    lw t0, 0(sp)
    lw t1, 156(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 164(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1127
.L1252:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw a0, 168(sp)
    j .L6
.L6:
    lw ra, 188(sp)
    lw s0, 184(sp)
    addi sp, sp, 192
    jr ra
    .globl complex_memory_scan
    .type complex_memory_scan, @function
complex_memory_scan:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    addi s0, sp, 80
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    lw t0, 0(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 12(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L1261
.L1261:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 24(sp)
    lw t0, 24(sp)
    li t1, 5
    slt t0, t0, t1
    sw t0, 28(sp)
    lw t0, 28(sp)
    bnez t0, .L1269
    j .L1302
.L1269:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 36(sp)
    li t1, 10
    mul t0, t0, t1
    sw t0, 40(sp)
    lw a0, 0(sp)
    lw a1, 40(sp)
    call another_utility_function
    sw a0, 44(sp)
    lw t0, 32(sp)
    lw t1, 44(sp)
    add t0, t0, t1
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 52(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L1261
.L1302:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw a0, 60(sp)
    j .L7
.L7:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
