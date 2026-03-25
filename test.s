    .text
    .globl main
    .type main, @function
main:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    addi s0, sp, 80
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    li a0, 26000
    call printlnInt
    li t0, 1000
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 500
    lw t1, 12(sp)
    sw t0, 0(t1)
    li t0, 100
    lw t1, 20(sp)
    sw t0, 0(t1)
    li t0, 50
    lw t1, 28(sp)
    sw t0, 0(t1)
    li t0, 200
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw a0, 40(sp)
    call performBPlusTreeOperations
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw a0, 44(sp)
    call performQueryExecutionTest
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw a0, 48(sp)
    call performTransactionProcessingTest
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw a0, 52(sp)
    call performBufferPoolTest
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw a0, 56(sp)
    call performQueryOptimizationTest
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw a0, 60(sp)
    call performHashTableTest
    li a0, 26999
    call printlnInt
    li a0, 0
    call __builtin_exit
    li a0, 0
    j .L1
.L1:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl performBPlusTreeOperations
    .type performBPlusTreeOperations, @function
performBPlusTreeOperations:
    li t0, -21600
    add sp, sp, t0
    li t0, 21596
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 21592
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 21600
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    li t3, 4012
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4016
    add t0, sp, t1
    li t3, 4020
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4024
    add t0, sp, t1
    li t3, 4064
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4068
    add t0, sp, t1
    li t3, 8068
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8072
    add t0, sp, t1
    li t3, 8076
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8080
    add t0, sp, t1
    li t3, 12480
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 12484
    add t0, sp, t1
    li t3, 12488
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 12492
    add t0, sp, t1
    li t3, 12536
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 12540
    add t0, sp, t1
    li t3, 16940
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16944
    add t0, sp, t1
    li t3, 16948
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16952
    add t0, sp, t1
    li t3, 17352
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17356
    add t0, sp, t1
    li t3, 17360
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17364
    add t0, sp, t1
    li t3, 17764
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17768
    add t0, sp, t1
    li t3, 18168
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18172
    add t0, sp, t1
    li t3, 18176
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18180
    add t0, sp, t1
    li t3, 18580
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18584
    add t0, sp, t1
    li t3, 18984
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18988
    add t0, sp, t1
    li t3, 18992
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18996
    add t0, sp, t1
    li t3, 19396
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 19400
    add t0, sp, t1
    li t3, 19404
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 19408
    add t0, sp, t1
    li t3, 19412
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 19416
    add t0, sp, t1
    li t3, 19816
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 19820
    add t0, sp, t1
    li t3, 19824
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 19828
    add t0, sp, t1
    li t3, 20228
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20232
    add t0, sp, t1
    li t3, 20236
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20240
    add t0, sp, t1
    li t3, 20244
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20248
    add t0, sp, t1
    li t3, 20252
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20256
    add t0, sp, t1
    li t3, 20260
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20264
    add t0, sp, t1
    li t3, 20268
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20272
    add t0, sp, t1
    li t3, 20276
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20280
    add t0, sp, t1
    li t3, 20284
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20288
    add t0, sp, t1
    li t3, 20292
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20296
    add t0, sp, t1
    li t3, 20300
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20304
    add t0, sp, t1
    li t3, 20308
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20312
    add t0, sp, t1
    li t3, 20316
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20320
    add t0, sp, t1
    li t3, 20324
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20328
    add t0, sp, t1
    li t3, 20332
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20336
    add t0, sp, t1
    li t3, 20340
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20344
    add t0, sp, t1
    li t3, 20348
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20352
    add t0, sp, t1
    li t3, 20356
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20360
    add t0, sp, t1
    li t3, 20364
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20368
    add t0, sp, t1
    li t3, 20372
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20376
    add t0, sp, t1
    li t3, 20380
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20384
    add t0, sp, t1
    li t3, 20388
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20392
    add t0, sp, t1
    li t3, 20396
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li a0, 26001
    call printlnInt
    li t0, 0
    li t3, 4020
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L160
.L160:
    li t3, 4020
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20400
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10
    slt t0, t0, t1
    li t3, 20404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20404
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L164
    j .L165
.L164:
    li t3, 4020
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4064
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20408
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20412
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 20412
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 4020
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20416
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20420
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 4020
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L160
.L165:
    li t0, 0
    li t3, 8076
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L170
.L170:
    li t3, 8076
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20424
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20424
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20428
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20428
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L174
    j .L175
.L174:
    li t3, 8076
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20432
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8068
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20432
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20436
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20436
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 4064
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 40
    call memcpy
    li t3, 8076
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20440
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20440
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20444
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20444
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8076
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L170
.L175:
    li t3, 4012
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8068
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 4000
    call memcpy
    li t0, 0
    li t3, 12488
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L187
.L187:
    li t3, 12488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20448
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 11
    slt t0, t0, t1
    li t3, 20452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20452
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L191
    j .L192
.L191:
    li t3, 12488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20456
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12536
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20456
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20460
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 20460
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 12488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20464
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20464
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20468
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 12488
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L187
.L192:
    li t0, 0
    li t3, 16948
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L197
.L197:
    li t3, 16948
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20472
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20472
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20476
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L201
    j .L202
.L201:
    li t3, 16948
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20480
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16940
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20480
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 44
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20484
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 12536
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 44
    call memcpy
    li t3, 16948
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20488
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20488
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20492
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16948
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L197
.L202:
    li t3, 12480
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 16940
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 4400
    call memcpy
    li t0, 0
    li t3, 17360
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L212
.L212:
    li t3, 17360
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20496
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20500
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L216
    j .L217
.L216:
    li t3, 17360
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20504
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 17764
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20504
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20508
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 20508
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 17360
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20512
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20512
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20516
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 17360
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L212
.L217:
    li t3, 17352
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 17764
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 18176
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L226
.L226:
    li t3, 18176
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20520
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20524
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20524
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L230
    j .L231
.L230:
    li t3, 18176
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20528
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18580
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20528
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20532
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 20532
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 18176
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20536
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20540
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 18176
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L226
.L231:
    li t3, 18168
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 18580
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 18992
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L240
.L240:
    li t3, 18992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20544
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20544
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20548
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L244
    j .L245
.L244:
    li t3, 18992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20552
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 19396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20552
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20556
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 20556
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 18992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20560
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 18992
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L240
.L245:
    li t3, 18984
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 19396
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 1
    li t3, 19404
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 19412
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 18168
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 20568
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 20568
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 20572
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 20572
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 19824
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L272
.L272:
    li t3, 19824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20576
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20576
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20580
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20580
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L276
    j .L277
.L276:
    li t3, 19824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20584
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20228
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20584
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20588
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 20588
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 19824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20592
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20592
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20596
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20596
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 19824
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L272
.L277:
    li t3, 19816
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 20228
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 20236
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L285
.L285:
    j .L289
.L289:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20600
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 20604
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20600
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20604
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 20608
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 20612
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 20608
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L299
    j .L308
.L299:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20616
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20616
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20620
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20620
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 20612
    add t3, t3, sp
    sw t1, 0(t3)
    j .L308
.L308:
    li t3, 20612
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L312
    j .L355
.L312:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20624
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 19816
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20624
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20628
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20632
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20632
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 17
    mul t0, t0, t1
    li t3, 20636
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20636
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 23
    add t0, t0, t1
    li t3, 20640
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20640
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 997
    rem t0, t0, t1
    li t3, 20644
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20644
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20648
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20648
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20628
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20652
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20652
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20656
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20656
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20236
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L285
.L355:
    li t0, 0
    li t3, 20236
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L362
.L362:
    j .L366
.L366:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20660
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 20664
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20660
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20664
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 20668
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 20672
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 20668
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L376
    j .L385
.L376:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20676
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20676
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 20680
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20680
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 20672
    add t3, t3, sp
    sw t1, 0(t3)
    j .L385
.L385:
    li t3, 20672
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L389
    j .L1216
.L389:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20684
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 19816
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20684
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20688
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20688
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20692
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20692
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20244
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 19412
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20696
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20696
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L405
.L405:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20700
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18168
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20700
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20704
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20704
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20708
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20708
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 20712
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20712
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L417
    j .L507
.L417:
    li t0, 0
    li t3, 20260
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 20268
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L423
.L423:
    li t3, 20268
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20716
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20720
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20720
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20724
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20724
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20728
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20716
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20728
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 20732
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20732
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L439
    j .L487
.L439:
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20736
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20740
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20740
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20744
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20268
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20748
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20744
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20748
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20752
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20752
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20756
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20736
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20756
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t1, t0
    li t3, 20760
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20760
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L463
    j .L475
.L463:
    li t3, 20268
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20764
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20764
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20768
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20768
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20260
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L475
.L475:
    li t3, 20268
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20772
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20772
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20776
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20776
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20268
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L423
.L487:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20780
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12480
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20780
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 44
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20784
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20260
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20788
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20784
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20788
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20792
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20792
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20796
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20796
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L405
.L507:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20800
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20800
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20804
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20804
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20808
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20808
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 9
    slt t0, t0, t1
    li t3, 20812
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20812
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L523
    j .L710
.L523:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20816
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20816
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20820
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20820
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20824
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20824
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20276
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 20284
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L537
.L537:
    li t3, 20284
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20828
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20832
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20832
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20836
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20836
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20840
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20828
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20840
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 20844
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20844
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L553
    j .L598
.L553:
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20848
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20852
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20852
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20856
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20284
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20860
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20856
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20860
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20864
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20864
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20868
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20848
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20868
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 20872
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20872
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L577
    j .L586
.L577:
    li t3, 20284
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20876
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20876
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20276
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L598
.L586:
    li t3, 20284
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20880
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20880
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 20884
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20884
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20284
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L537
.L598:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20888
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20888
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20892
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20892
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20896
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20896
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20292
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L610
.L610:
    li t3, 20292
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20900
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20276
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20904
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20900
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20904
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t1, t0
    li t3, 20908
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20908
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L620
    j .L667
.L620:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20912
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20912
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20916
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20292
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20920
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20916
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20920
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20924
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20928
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20928
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20932
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20292
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20936
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20936
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 20940
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20932
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20940
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20944
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20944
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20948
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20948
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20924
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20292
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20952
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20952
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 20956
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20956
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20292
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L610
.L667:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20960
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20960
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20964
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20276
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20968
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20964
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20968
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20972
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20976
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20976
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20972
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20980
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20980
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20984
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20988
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20988
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 20992
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 20996
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20996
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21000
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21000
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20984
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1204
.L710:
    li t3, 19404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21004
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21004
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 99
    slt t0, t0, t1
    li t3, 21008
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21008
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L720
    j .L1203
.L720:
    li t3, 19404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21012
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20300
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 19404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21016
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21016
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21020
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21020
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 19404
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21024
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18168
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21024
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21028
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 21028
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21032
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21032
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21036
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 5
    li t3, 21036
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21040
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 17352
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21040
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21044
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21048
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 17352
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21048
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21052
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21052
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21056
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21056
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21044
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 20308
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L780
.L780:
    li t3, 20308
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21060
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 21064
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21064
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L788
    j .L856
.L788:
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21068
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21068
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21072
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20308
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21076
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21072
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21076
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21080
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21084
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21084
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21088
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20308
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21092
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21092
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    add t0, t0, t1
    li t3, 21096
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21088
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21096
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21100
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21100
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21104
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21104
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21080
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21108
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21108
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21112
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20308
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21116
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21116
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    add t0, t0, t1
    li t3, 21120
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21112
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21120
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21124
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 21124
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20308
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21128
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21128
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21132
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21132
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20308
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L780
.L856:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21136
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21136
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21140
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 5
    li t3, 21140
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21144
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21148
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21148
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21152
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21152
    add t3, t3, sp
    lw t0, 0(t3)
    addi t0, t0, 0
    li t3, 21156
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21156
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21160
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21144
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21160
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 21164
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21164
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L887
    j .L1039
.L887:
    li t0, 5
    li t3, 20316
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 20324
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L893
.L893:
    li t3, 20324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21168
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21168
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 21172
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21172
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L901
    j .L946
.L901:
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21176
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21180
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21180
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21184
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21188
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21184
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21188
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21192
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21196
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21176
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21196
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 21200
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21200
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L925
    j .L934
.L925:
    li t3, 20324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21204
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21204
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20316
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L946
.L934:
    li t3, 20324
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21208
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21212
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21212
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20324
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L893
.L946:
    li t0, 4
    li t3, 20332
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L950
.L950:
    li t3, 20332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21216
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20316
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21220
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21216
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21220
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 21224
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21224
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L960
    j .L1019
.L960:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21228
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21228
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21232
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21236
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21232
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21240
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21244
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21248
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21248
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21252
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21256
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21252
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21256
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21260
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21260
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21264
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21264
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21244
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21268
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21268
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 21272
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21272
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1005
    j .L1007
.L1005:
    j .L1019
.L1007:
    li t3, 20332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21276
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 21280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21280
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20332
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L950
.L1019:
    li t3, 20252
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21284
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21284
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20316
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21288
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21292
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21296
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21300
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21296
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1202
.L1039:
    li t0, 5
    li t3, 20340
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 20348
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1045
.L1045:
    li t3, 20348
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21304
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 21308
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21308
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1053
    j .L1098
.L1053:
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21316
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21320
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20348
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21320
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21324
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21328
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21328
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21312
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21332
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 21336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21336
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1077
    j .L1086
.L1077:
    li t3, 20348
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21340
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20340
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1098
.L1086:
    li t3, 20348
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21344
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21348
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20348
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1045
.L1098:
    li t0, 4
    li t3, 20356
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1102
.L1102:
    li t3, 20356
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20340
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21352
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21356
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 21360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21360
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1112
    j .L1171
.L1112:
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21364
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21368
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20356
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21372
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21372
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21368
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21376
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21384
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21388
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20356
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21392
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21388
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21392
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21400
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21380
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20356
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21404
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 21408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21408
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1157
    j .L1159
.L1157:
    j .L1171
.L1159:
    li t3, 20356
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21412
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 21416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21416
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20356
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1102
.L1171:
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21420
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21424
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20340
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21428
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21424
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21428
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21432
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20244
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21436
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21436
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21432
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20300
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21440
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21440
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 21444
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 6
    li t3, 21444
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1202
.L1202:
    j .L1203
.L1203:
    j .L1204
.L1204:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21448
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21452
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20236
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L362
.L1216:
    li t0, 0
    li t3, 20364
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 20372
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 20236
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1227
.L1227:
    j .L1231
.L1231:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21456
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21456
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 20
    slt t0, t0, t1
    li t3, 21460
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 21464
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 21460
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1239
    j .L1248
.L1239:
    li t3, 20372
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21468
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 21472
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21472
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 21464
    add t3, t3, sp
    sw t1, 0(t3)
    j .L1248
.L1248:
    li t3, 21464
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1252
    j .L1355
.L1252:
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21476
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 13
    mul t0, t0, t1
    li t3, 21480
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21480
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 7
    add t0, t0, t1
    li t3, 21484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21484
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 500
    rem t0, t0, t1
    li t3, 21488
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21488
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21492
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20380
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20380
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21500
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    mul t0, t0, t1
    li t3, 21504
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21504
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21508
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21508
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    rem t0, t0, t1
    li t3, 21512
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21496
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21512
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 21516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21516
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10
    add t0, t0, t1
    li t3, 21520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21520
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20388
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 19412
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21524
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20380
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21528
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20388
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21532
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4012
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 12480
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 18168
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 18984
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 21524
    add t3, t3, sp
    lw a4, 0(t3)
    li t3, 21528
    add t3, t3, sp
    lw a5, 0(t3)
    li t3, 21532
    add t3, t3, sp
    lw a6, 0(t3)
    call performRangeQuery
    li t3, 21536
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 21536
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20396
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20364
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20396
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21544
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21540
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21544
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 21548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21548
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20364
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20372
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21552
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21552
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21556
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21556
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20372
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 20236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21560
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 21564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20236
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1227
.L1355:
    li t3, 20364
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 21568
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21568
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 21572
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21572
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li a0, 26002
    call printlnInt
    li t3, 21576
    add t3, t3, sp
    lw a0, 0(t3)
    j .L2
.L2:
    li t0, 21596
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 21592
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 21600
    add sp, sp, t0
    jr ra
    .globl performRangeQuery
    .type performRangeQuery, @function
performRangeQuery:
    addi sp, sp, -368
    sw ra, 364(sp)
    sw s0, 360(sp)
    addi s0, sp, 368
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)
    addi t0, sp, 28
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 36(sp)
    addi t0, sp, 40
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
    addi t0, sp, 92
    sw t0, 96(sp)
    lw t0, 0(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t1, 64(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 72(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 8(sp)
    lw t1, 100(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 112(sp)
    lw t0, 112(sp)
    bnez t0, .L1387
    j .L1501
.L1387:
    li t0, 0
    lw t1, 80(sp)
    sw t0, 0(t1)
    j .L1391
.L1391:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 12(sp)
    lw t1, 120(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 116(sp)
    lw t1, 128(sp)
    slt t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    bnez t0, .L1407
    j .L1500
.L1407:
    j .L1413
.L1413:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 0(sp)
    lw t1, 136(sp)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 140(sp)
    lw t1, 144(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 152(sp)
    lw t1, 156(sp)
    slt t0, t0, t1
    xori t0, t0, 1
    sw t0, 160(sp)
    li t1, 0
    sw t1, 164(sp)
    lw t0, 160(sp)
    bnez t0, .L1435
    j .L1458
.L1435:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 0(sp)
    lw t1, 168(sp)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 172(sp)
    lw t1, 176(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 184(sp)
    lw t1, 188(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 192(sp)
    lw t1, 192(sp)
    sw t1, 164(sp)
    j .L1458
.L1458:
    lw t0, 164(sp)
    bnez t0, .L1462
    j .L1488
.L1462:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 0(sp)
    lw t1, 200(sp)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 204(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 204(sp)
    lw t1, 208(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 196(sp)
    lw t1, 216(sp)
    add t0, t0, t1
    sw t0, 220(sp)
    lw t0, 220(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L1488
.L1488:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 224(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 228(sp)
    lw t0, 228(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    j .L1391
.L1500:
    j .L1626
.L1501:
    li t0, 0
    lw t1, 88(sp)
    sw t0, 0(t1)
    j .L1505
.L1505:
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 236(sp)
    lw t0, 12(sp)
    lw t1, 236(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 240(sp)
    lw t0, 240(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 232(sp)
    lw t1, 244(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 248(sp)
    lw t0, 248(sp)
    bnez t0, .L1521
    j .L1625
.L1521:
    j .L1527
.L1527:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 252(sp)
    lw t0, 4(sp)
    lw t1, 252(sp)
    li t2, 44
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 256(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 260(sp)
    lw t0, 256(sp)
    lw t1, 260(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 264(sp)
    lw t0, 264(sp)
    lw t0, 0(t0)
    sw t0, 268(sp)
    lw t0, 268(sp)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    sw t0, 272(sp)
    li t1, 0
    sw t1, 276(sp)
    lw t0, 272(sp)
    bnez t0, .L1547
    j .L1568
.L1547:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 4(sp)
    lw t1, 280(sp)
    li t2, 44
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 284(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 288(sp)
    lw t0, 284(sp)
    lw t1, 288(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 292(sp)
    lw t0, 292(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 296(sp)
    li t1, 100
    slt t0, t0, t1
    sw t0, 300(sp)
    lw t1, 300(sp)
    sw t1, 276(sp)
    j .L1568
.L1568:
    lw t0, 276(sp)
    bnez t0, .L1572
    j .L1613
.L1572:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 304(sp)
    lw t0, 4(sp)
    lw t1, 304(sp)
    li t2, 44
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 308(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 308(sp)
    lw t1, 312(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 316(sp)
    lw t0, 0(t0)
    sw t0, 320(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 324(sp)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 328(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 12(sp)
    lw a4, 320(sp)
    lw a5, 324(sp)
    lw a6, 328(sp)
    call performRangeQuery
    sw a0, 332(sp)
    lw t0, 332(sp)
    lw t1, 96(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 336(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 340(sp)
    lw t0, 336(sp)
    lw t1, 340(sp)
    add t0, t0, t1
    sw t0, 344(sp)
    lw t0, 344(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L1613
.L1613:
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 348(sp)
    lw t0, 348(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 352(sp)
    lw t0, 352(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    j .L1505
.L1625:
    j .L1626
.L1626:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 356(sp)
    lw a0, 356(sp)
    j .L3
.L3:
    lw ra, 364(sp)
    lw s0, 360(sp)
    addi sp, sp, 368
    jr ra
    .globl performQueryExecutionTest
    .type performQueryExecutionTest, @function
performQueryExecutionTest:
    li t0, -12096
    add sp, sp, t0
    li t0, 12092
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 12088
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 12096
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 812(sp)
    addi t0, sp, 816
    sw t0, 820(sp)
    addi t0, sp, 824
    sw t0, 1624(sp)
    addi t0, sp, 1628
    li t3, 2428
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2432
    add t0, sp, t1
    li t3, 2436
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2440
    add t0, sp, t1
    li t3, 3240
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 3244
    add t0, sp, t1
    li t3, 4044
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4048
    add t0, sp, t1
    li t3, 4052
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4056
    add t0, sp, t1
    li t3, 4856
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4860
    add t0, sp, t1
    li t3, 5660
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5664
    add t0, sp, t1
    li t3, 5668
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5672
    add t0, sp, t1
    li t3, 6472
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6476
    add t0, sp, t1
    li t3, 6480
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6484
    add t0, sp, t1
    li t3, 6488
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6492
    add t0, sp, t1
    li t3, 6496
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6500
    add t0, sp, t1
    li t3, 6504
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6508
    add t0, sp, t1
    li t3, 6512
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6516
    add t0, sp, t1
    li t3, 7516
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 7520
    add t0, sp, t1
    li t3, 7524
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 7528
    add t0, sp, t1
    li t3, 7548
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 7552
    add t0, sp, t1
    li t3, 8552
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8556
    add t0, sp, t1
    li t3, 8560
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8564
    add t0, sp, t1
    li t3, 9564
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 9568
    add t0, sp, t1
    li t3, 9572
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 9576
    add t0, sp, t1
    li t3, 9596
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 9600
    add t0, sp, t1
    li t3, 10600
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10604
    add t0, sp, t1
    li t3, 10608
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10612
    add t0, sp, t1
    li t3, 10812
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10816
    add t0, sp, t1
    li t3, 10820
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10824
    add t0, sp, t1
    li t3, 11024
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11028
    add t0, sp, t1
    li t3, 11032
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11036
    add t0, sp, t1
    li t3, 11040
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11044
    add t0, sp, t1
    li t3, 11048
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11052
    add t0, sp, t1
    li t3, 11056
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11060
    add t0, sp, t1
    li t3, 11064
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11068
    add t0, sp, t1
    li t3, 11072
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11076
    add t0, sp, t1
    li t3, 11080
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11084
    add t0, sp, t1
    li t3, 11088
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li a0, 26003
    call printlnInt
    li t0, 0
    lw t1, 820(sp)
    sw t0, 0(t1)
    j .L1635
.L1635:
    lw t0, 820(sp)
    lw t0, 0(t0)
    li t3, 11092
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11092
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 11096
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11096
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1639
    j .L1640
.L1639:
    lw t0, 820(sp)
    lw t0, 0(t0)
    li t3, 11100
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1624(sp)
    li t3, 11100
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11104
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 11104
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 820(sp)
    lw t0, 0(t0)
    li t3, 11108
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11108
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11112
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11112
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 820(sp)
    sw t0, 0(t1)
    j .L1635
.L1640:
    lw a0, 812(sp)
    lw a1, 1624(sp)
    li a2, 800
    call memcpy
    li t0, 0
    li t3, 2436
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1649
.L1649:
    li t3, 2436
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11116
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11116
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 11120
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11120
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1653
    j .L1654
.L1653:
    li t3, 2436
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11124
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3240
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11124
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11128
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 11128
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 2436
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11132
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11132
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11136
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11136
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2436
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1649
.L1654:
    li t3, 2428
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 3240
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 800
    call memcpy
    li t0, 0
    li t3, 4052
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1663
.L1663:
    li t3, 4052
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11140
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11140
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 11144
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11144
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1667
    j .L1668
.L1667:
    li t3, 4052
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11148
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4856
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11148
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11152
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 11152
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 4052
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11156
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11156
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11160
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11160
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 4052
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1663
.L1668:
    li t3, 4044
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 4856
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 800
    call memcpy
    li t0, 0
    li t3, 5668
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1677
.L1677:
    li t3, 5668
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11164
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11164
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 11168
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11168
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1681
    j .L1682
.L1681:
    li t3, 5668
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11172
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6472
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11172
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11176
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 11176
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 5668
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11180
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11180
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11184
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11184
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 5668
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1677
.L1682:
    li t3, 5660
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 6472
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 800
    call memcpy
    li t0, 0
    li t3, 6480
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 6488
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1694
.L1694:
    j .L1698
.L1698:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11188
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 11192
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11188
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11192
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11196
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 11200
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 11196
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1708
    j .L1717
.L1708:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11204
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11204
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 11208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11208
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 11200
    add t3, t3, sp
    sw t1, 0(t3)
    j .L1717
.L1717:
    li t3, 11200
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1721
    j .L1804
.L1721:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11212
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 812(sp)
    li t3, 11212
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11216
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11220
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11220
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    mul t0, t0, t1
    li t3, 11224
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11224
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11228
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11228
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 150
    rem t0, t0, t1
    li t3, 11232
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11232
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11236
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11216
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2428
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11240
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11244
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11248
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11248
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 7
    mul t0, t0, t1
    li t3, 11252
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11252
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 11
    add t0, t0, t1
    li t3, 11256
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11256
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1000
    rem t0, t0, t1
    li t3, 11260
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11260
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11264
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11264
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11244
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6480
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11268
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11268
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11272
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11272
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6480
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11276
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11280
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1694
.L1804:
    li t0, 0
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1811
.L1811:
    j .L1815
.L1815:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11284
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 11288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11284
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11288
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11292
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 11296
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 11292
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1825
    j .L1834
.L1825:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11300
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 11304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11304
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 11296
    add t3, t3, sp
    sw t1, 0(t3)
    j .L1834
.L1834:
    li t3, 11296
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1838
    j .L1921
.L1838:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11308
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4044
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11308
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11316
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    mul t0, t0, t1
    li t3, 11320
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11320
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    add t0, t0, t1
    li t3, 11324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 180
    rem t0, t0, t1
    li t3, 11328
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11328
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11332
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11312
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5660
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11336
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11344
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 11
    mul t0, t0, t1
    li t3, 11348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11348
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 13
    add t0, t0, t1
    li t3, 11352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11352
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1200
    rem t0, t0, t1
    li t3, 11356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11356
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11360
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11340
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11364
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11368
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11368
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6488
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11372
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11372
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11376
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1811
.L1921:
    li t0, 0
    li t3, 6504
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1930
.L1930:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6480
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11380
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11384
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11388
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11388
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1940
    j .L2034
.L1940:
    li t0, 0
    li t3, 6512
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1944
.L1944:
    li t3, 6512
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11392
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11392
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11396
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11400
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1954
    j .L2022
.L1954:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11404
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 812(sp)
    li t3, 11404
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11408
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6512
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4044
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11416
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11420
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11424
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11412
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11424
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    seqz t0, t0
    li t3, 11428
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11428
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1978
    j .L2010
.L1978:
    li t3, 6504
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11432
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11436
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2428
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11436
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11440
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11440
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11444
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11432
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11444
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 11448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6512
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5660
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11452
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11456
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11456
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11460
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11448
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11460
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 11464
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11464
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6504
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2010
.L2010:
    li t3, 6512
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11468
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11472
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11472
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6512
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1944
.L2022:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11476
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11480
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11480
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1930
.L2034:
    li t3, 6504
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11484
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 11488
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11488
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t0, 0
    li t3, 7524
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2049
.L2049:
    li t3, 7524
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11492
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 11496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11496
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2053
    j .L2054
.L2053:
    li t3, 7524
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 7548
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11500
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11504
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 11504
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 7524
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11508
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11508
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11512
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11512
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 7524
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2049
.L2054:
    li t0, 0
    li t3, 8560
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2059
.L2059:
    li t3, 8560
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11516
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 11520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11520
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2063
    j .L2064
.L2063:
    li t3, 8560
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11524
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8552
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11524
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11528
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11528
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 7548
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 20
    call memcpy
    li t3, 8560
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11532
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11532
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11536
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8560
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2059
.L2064:
    li t3, 7516
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8552
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 1000
    call memcpy
    li t0, 0
    li t3, 9572
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2075
.L2075:
    li t3, 9572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11540
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 11544
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11544
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2079
    j .L2080
.L2079:
    li t3, 9572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 9596
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11548
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11552
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 11552
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 9572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11556
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11556
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11560
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 9572
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2075
.L2080:
    li t0, 0
    li t3, 10608
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2085
.L2085:
    li t3, 10608
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11564
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 11568
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11568
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2089
    j .L2090
.L2089:
    li t3, 10608
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11572
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10600
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11572
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11576
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11576
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 9596
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 20
    call memcpy
    li t3, 10608
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11580
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11580
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11584
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11584
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 10608
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2085
.L2090:
    li t3, 9564
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 10600
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 1000
    call memcpy
    li t0, 0
    li t3, 10820
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2099
.L2099:
    li t3, 10820
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11588
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11588
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 11592
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11592
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2103
    j .L2104
.L2103:
    li t3, 10820
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11596
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11024
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11596
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11600
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 11600
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 10820
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11604
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11604
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11608
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11608
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 10820
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2099
.L2104:
    li t3, 10812
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 11024
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 200
    call memcpy
    li t0, 0
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2115
.L2115:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11612
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6480
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11616
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11612
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11616
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11620
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11620
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2125
    j .L2251
.L2125:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11624
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 812(sp)
    li t3, 11624
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11628
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11628
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11632
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11632
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    rem t0, t0, t1
    li t3, 11636
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11636
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11032
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 11032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11640
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10812
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11640
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11644
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11644
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11648
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11648
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 11652
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11652
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2155
    j .L2239
.L2155:
    li t3, 11032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11656
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10812
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11656
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11660
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11660
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11664
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11664
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 11032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11668
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 7516
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11668
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11672
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11676
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11672
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11676
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11680
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11684
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 812(sp)
    li t3, 11684
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11688
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11688
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11692
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11692
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11680
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 11032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11696
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 9564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11696
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11700
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11704
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11700
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11704
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11708
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11712
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2428
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11712
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11716
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11716
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11720
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11720
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11708
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 11032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11724
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10812
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11724
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11728
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11732
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10812
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11732
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11736
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11736
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11740
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11740
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11744
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11744
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11728
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2239
.L2239:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11748
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11748
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11752
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11752
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2115
.L2251:
    li t0, 0
    li t3, 11048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2260
.L2260:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11756
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11760
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11756
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11760
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11764
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11764
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2270
    j .L2396
.L2270:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11768
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4044
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11768
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11772
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11772
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11776
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11776
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    rem t0, t0, t1
    li t3, 11780
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11780
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11056
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 11064
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2288
.L2288:
    li t3, 11064
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11784
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11788
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10812
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11788
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11792
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11792
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11796
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11784
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11796
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11800
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11800
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2304
    j .L2384
.L2304:
    li t3, 11056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11804
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 7516
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11804
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11808
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11064
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11812
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11808
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11812
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11816
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11816
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11820
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11824
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4044
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11824
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11828
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11828
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11832
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11820
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11832
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    seqz t0, t0
    li t3, 11836
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11836
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2334
    j .L2372
.L2334:
    li t3, 11048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11840
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11844
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 9564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11844
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11848
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11064
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11852
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11848
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11852
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11856
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11856
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11860
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11840
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11860
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 11864
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11868
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5660
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11868
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11872
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11872
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11876
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11864
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11876
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 11880
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11880
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2372
.L2372:
    li t3, 11064
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11884
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11884
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11888
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11888
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11064
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2288
.L2384:
    li t3, 6496
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11892
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11892
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 11896
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11896
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6496
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2260
.L2396:
    li t3, 11048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11900
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11900
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 11904
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11904
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 6480
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11908
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 812(sp)
    li t3, 2428
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 11908
    add t3, t3, sp
    lw a2, 0(t3)
    call performTableSort
    li t3, 6488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11912
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4044
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 5660
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 11912
    add t3, t3, sp
    lw a2, 0(t3)
    call performTableSort
    li t0, 0
    li t3, 11072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 11080
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 11088
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2427
.L2427:
    j .L2431
.L2431:
    li t3, 11080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11916
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6480
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11920
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11916
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11920
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11924
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 11928
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 11924
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2441
    j .L2452
.L2441:
    li t3, 11088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11932
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11936
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11932
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11936
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 11940
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11940
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 11928
    add t3, t3, sp
    sw t1, 0(t3)
    j .L2452
.L2452:
    li t3, 11928
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2456
    j .L2583
.L2456:
    li t3, 11080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11944
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 812(sp)
    li t3, 11944
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11948
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11948
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11952
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11956
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4044
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11956
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11960
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11960
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11964
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11952
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11964
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    seqz t0, t0
    li t3, 11968
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11968
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2480
    j .L2534
.L2480:
    li t3, 11072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11972
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11976
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2428
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11976
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11980
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11980
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11984
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11972
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11984
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 11988
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 11992
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5660
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11992
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 11996
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11996
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12000
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11988
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 12000
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 12004
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12004
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 11080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12008
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12008
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 12012
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11080
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 11088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12016
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12016
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 12020
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12020
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11088
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2582
.L2534:
    li t3, 11080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12024
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 812(sp)
    li t3, 12024
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 12028
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12028
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12032
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12036
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4044
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 12036
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 12040
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12044
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12032
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 12044
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 12048
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12048
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2557
    j .L2569
.L2557:
    li t3, 11080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12052
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12052
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 12056
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12056
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11080
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2581
.L2569:
    li t3, 11088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12060
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 12064
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12064
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11088
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2581
.L2581:
    j .L2582
.L2582:
    j .L2427
.L2583:
    li t3, 11072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 12068
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12068
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 12072
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12072
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li a0, 26004
    call printlnInt
    li t3, 12076
    add t3, t3, sp
    lw a0, 0(t3)
    j .L4
.L4:
    li t0, 12092
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 12088
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 12096
    add sp, sp, t0
    jr ra
    .globl performTableSort
    .type performTableSort, @function
performTableSort:
    addi sp, sp, -272
    sw ra, 268(sp)
    sw s0, 264(sp)
    addi s0, sp, 272
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 12(sp)
    addi t0, sp, 16
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
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L2599
.L2599:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 68(sp)
    lw t0, 60(sp)
    lw t1, 68(sp)
    slt t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    bnez t0, .L2613
    j .L2790
.L2613:
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L2617
.L2617:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 80(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 84(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 84(sp)
    lw t1, 88(sp)
    sub t0, t0, t1
    sw t0, 92(sp)
    lw t0, 76(sp)
    lw t1, 92(sp)
    slt t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    bnez t0, .L2637
    j .L2778
.L2637:
    lw t0, 40(sp)
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
    lw t0, 40(sp)
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
    lw t0, 108(sp)
    lw t1, 124(sp)
    slt t0, t1, t0
    sw t0, 128(sp)
    lw t0, 128(sp)
    bnez t0, .L2665
    j .L2766
.L2665:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 0(sp)
    lw t1, 132(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 0(sp)
    lw t1, 144(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 148(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 152(sp)
    li t1, 1
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
    lw t1, 148(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 0(sp)
    lw t1, 172(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 176(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t1, 176(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 4(sp)
    lw t1, 184(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 188(sp)
    lw t0, 188(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 192(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 4(sp)
    lw t1, 196(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 200(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 204(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 208(sp)
    lw t0, 4(sp)
    lw t1, 208(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 216(sp)
    lw t1, 200(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 220(sp)
    lw t0, 220(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 224(sp)
    lw t0, 4(sp)
    lw t1, 224(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 228(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 232(sp)
    lw t1, 228(sp)
    sw t0, 0(t1)
    j .L2766
.L2766:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 236(sp)
    lw t0, 236(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 240(sp)
    lw t0, 240(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L2617
.L2778:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 244(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 248(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L2599
.L2790:
    lw a0, 252(sp)
    j .L5
.L5:
    lw ra, 268(sp)
    lw s0, 264(sp)
    addi sp, sp, 272
    jr ra
    .globl performTransactionProcessingTest
    .type performTransactionProcessingTest, @function
performTransactionProcessingTest:
    li t0, -33104
    add sp, sp, t0
    li t0, 33100
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 33096
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 33104
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 212(sp)
    addi t0, sp, 216
    sw t0, 220(sp)
    addi t0, sp, 224
    sw t0, 424(sp)
    addi t0, sp, 428
    sw t0, 628(sp)
    addi t0, sp, 632
    sw t0, 636(sp)
    addi t0, sp, 640
    sw t0, 840(sp)
    addi t0, sp, 844
    li t3, 2844
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2848
    add t0, sp, t1
    li t3, 2852
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2856
    add t0, sp, t1
    li t3, 2896
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2900
    add t0, sp, t1
    li t3, 4900
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4904
    add t0, sp, t1
    li t3, 4908
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4912
    add t0, sp, t1
    li t3, 5112
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5116
    add t0, sp, t1
    li t3, 5120
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5124
    add t0, sp, t1
    li t3, 5324
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5328
    add t0, sp, t1
    li t3, 5728
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5732
    add t0, sp, t1
    li t3, 5736
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5740
    add t0, sp, t1
    li t3, 6140
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6144
    add t0, sp, t1
    li t3, 8144
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8148
    add t0, sp, t1
    li t3, 8152
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8156
    add t0, sp, t1
    li t3, 8176
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8180
    add t0, sp, t1
    li t3, 10180
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10184
    add t0, sp, t1
    li t3, 10188
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10192
    add t0, sp, t1
    li t3, 10592
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10596
    add t0, sp, t1
    li t3, 10600
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10604
    add t0, sp, t1
    li t3, 11004
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11008
    add t0, sp, t1
    li t3, 21008
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21012
    add t0, sp, t1
    li t3, 21016
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21020
    add t0, sp, t1
    li t3, 21220
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21224
    add t0, sp, t1
    li t3, 31224
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 31228
    add t0, sp, t1
    li t3, 31232
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 31236
    add t0, sp, t1
    li t3, 31436
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 31440
    add t0, sp, t1
    li t3, 31444
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 31448
    add t0, sp, t1
    li t3, 31648
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 31652
    add t0, sp, t1
    li t3, 31852
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 31856
    add t0, sp, t1
    li t3, 31860
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 31864
    add t0, sp, t1
    li t3, 32064
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32068
    add t0, sp, t1
    li t3, 32072
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32076
    add t0, sp, t1
    li t3, 32080
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32084
    add t0, sp, t1
    li t3, 32088
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32092
    add t0, sp, t1
    li t3, 32096
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32100
    add t0, sp, t1
    li t3, 32104
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32108
    add t0, sp, t1
    li t3, 32112
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32116
    add t0, sp, t1
    li t3, 32120
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32124
    add t0, sp, t1
    li t3, 32128
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32132
    add t0, sp, t1
    li t3, 32136
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32140
    add t0, sp, t1
    li t3, 32144
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32148
    add t0, sp, t1
    li t3, 32152
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 32156
    add t0, sp, t1
    li t3, 32160
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li a0, 26005
    call printlnInt
    li t0, 0
    lw t1, 220(sp)
    sw t0, 0(t1)
    j .L2798
.L2798:
    lw t0, 220(sp)
    lw t0, 0(t0)
    li t3, 32164
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32164
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32168
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32168
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2802
    j .L2803
.L2802:
    lw t0, 220(sp)
    lw t0, 0(t0)
    li t3, 32172
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 424(sp)
    li t3, 32172
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32176
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32176
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 220(sp)
    lw t0, 0(t0)
    li t3, 32180
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32180
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32184
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32184
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 220(sp)
    sw t0, 0(t1)
    j .L2798
.L2803:
    lw a0, 212(sp)
    lw a1, 424(sp)
    li a2, 200
    call memcpy
    li t0, 0
    lw t1, 636(sp)
    sw t0, 0(t1)
    j .L2812
.L2812:
    lw t0, 636(sp)
    lw t0, 0(t0)
    li t3, 32188
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32188
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32192
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32192
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2816
    j .L2817
.L2816:
    lw t0, 636(sp)
    lw t0, 0(t0)
    li t3, 32196
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 840(sp)
    li t3, 32196
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32200
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32200
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 636(sp)
    lw t0, 0(t0)
    li t3, 32204
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32204
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 636(sp)
    sw t0, 0(t1)
    j .L2812
.L2817:
    lw a0, 628(sp)
    lw a1, 840(sp)
    li a2, 200
    call memcpy
    li t0, 0
    li t3, 2852
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2829
.L2829:
    li t3, 2852
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32212
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32212
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10
    slt t0, t0, t1
    li t3, 32216
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32216
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2833
    j .L2834
.L2833:
    li t3, 2852
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32220
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2896
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32220
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32224
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 32224
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 2852
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32228
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32228
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32232
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32232
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2852
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2829
.L2834:
    li t0, 0
    li t3, 4908
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2839
.L2839:
    li t3, 4908
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32236
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32240
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2843
    j .L2844
.L2843:
    li t3, 4908
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32244
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4900
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32244
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32248
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32248
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 2896
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 40
    call memcpy
    li t3, 4908
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32252
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32252
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32256
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32256
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 4908
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2839
.L2844:
    li t3, 2844
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 4900
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2000
    call memcpy
    li t0, 0
    li t3, 5120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2853
.L2853:
    li t3, 5120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32260
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32260
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32264
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32264
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2857
    j .L2858
.L2857:
    li t3, 5120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32268
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5324
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32268
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32272
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32272
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 5120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32276
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32280
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 5120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2853
.L2858:
    li t3, 5112
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 5324
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 200
    call memcpy
    li t0, 0
    li t3, 5736
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2868
.L2868:
    li t3, 5736
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32284
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32284
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 32288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32288
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2872
    j .L2873
.L2872:
    li t3, 5736
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6140
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32292
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32296
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 32296
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 5736
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32300
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32304
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 5736
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2868
.L2873:
    li t3, 5728
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 6140
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 8152
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2885
.L2885:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32308
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32308
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 32312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32312
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2889
    j .L2890
.L2889:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8176
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32316
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32320
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 32320
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32328
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32328
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8152
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2885
.L2890:
    li t0, 0
    li t3, 10188
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2895
.L2895:
    li t3, 10188
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32332
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 32336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32336
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2899
    j .L2900
.L2899:
    li t3, 10188
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10180
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32340
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32344
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8176
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 20
    call memcpy
    li t3, 10188
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32348
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32352
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 10188
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2895
.L2900:
    li t3, 8144
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 10180
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2000
    call memcpy
    li t0, 0
    li t3, 10600
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2909
.L2909:
    li t3, 10600
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32356
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 32360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32360
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2913
    j .L2914
.L2913:
    li t3, 10600
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11004
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32364
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32368
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32368
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 10600
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32372
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32372
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32376
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 10600
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2909
.L2914:
    li t3, 10592
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 11004
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 21016
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2925
.L2925:
    li t3, 21016
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32380
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32384
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2929
    j .L2930
.L2929:
    li t3, 21016
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32388
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21220
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32388
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32392
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32392
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 21016
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32396
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32400
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21016
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2925
.L2930:
    li t0, 0
    li t3, 31232
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2935
.L2935:
    li t3, 31232
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32404
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32408
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2939
    j .L2940
.L2939:
    li t3, 31232
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31224
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32412
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 200
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32416
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 21220
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 200
    call memcpy
    li t3, 31232
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32420
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32424
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32424
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 31232
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2935
.L2940:
    li t3, 21008
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 31224
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 10000
    call memcpy
    li t0, 0
    li t3, 31444
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2949
.L2949:
    li t3, 31444
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32428
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32428
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32432
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32432
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2953
    j .L2954
.L2953:
    li t3, 31444
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32436
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31648
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32436
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32440
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32440
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 31444
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32444
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32444
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32448
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 31444
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2949
.L2954:
    li t3, 31436
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 31648
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 200
    call memcpy
    li t0, 0
    li t3, 31860
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2963
.L2963:
    li t3, 31860
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32452
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32456
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32456
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2967
    j .L2968
.L2967:
    li t3, 31860
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32460
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32064
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32460
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32464
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32464
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 31860
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32468
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32472
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32472
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 31860
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2963
.L2968:
    li t3, 31852
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 32064
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 200
    call memcpy
    li t0, 0
    li t3, 32072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 32080
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 32088
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 1
    li t3, 32096
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 32104
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2984
.L2984:
    j .L2988
.L2988:
    li t3, 32104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32476
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 20
    slt t0, t0, t1
    li t3, 32480
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 32484
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 32480
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2996
    j .L3007
.L2996:
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32488
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 32492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32488
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32492
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 32496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32496
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 32484
    add t3, t3, sp
    sw t1, 0(t3)
    j .L3007
.L3007:
    li t3, 32484
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3011
    j .L3685
.L3011:
    li t3, 32104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32500
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    rem t0, t0, t1
    li t3, 32504
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32504
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32508
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32508
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32112
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 32120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3028
.L3028:
    j .L3032
.L3032:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32512
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32112
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32512
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32516
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 32520
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 32524
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 32520
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3042
    j .L3053
.L3042:
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32528
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 32532
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32528
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32532
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 32536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32536
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 32524
    add t3, t3, sp
    sw t1, 0(t3)
    j .L3053
.L3053:
    li t3, 32524
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3057
    j .L3126
.L3057:
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32540
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    slt t0, t0, t1
    li t3, 32544
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32544
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3067
    j .L3114
.L3067:
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32548
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 212(sp)
    li t3, 32548
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32552
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 32552
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32556
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 628(sp)
    li t3, 32556
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32096
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32560
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32568
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5112
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32568
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32572
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 32572
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32576
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32576
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32580
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32580
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3114
.L3114:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32584
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32584
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32588
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32588
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3028
.L3126:
    li t0, 0
    li t3, 32120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3133
.L3133:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32592
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32596
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32592
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32596
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 32600
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32600
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3143
    j .L3463
.L3143:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32604
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 212(sp)
    li t3, 32604
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32608
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32608
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32612
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32612
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    li t3, 32616
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32616
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3159
    j .L3451
.L3159:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32620
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32624
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32620
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32624
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 32628
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32628
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    rem t0, t0, t1
    li t3, 32632
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32632
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32636
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32636
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32128
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 32136
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3182
.L3182:
    j .L3186
.L3186:
    li t3, 32136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32640
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32128
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32644
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32640
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32644
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 32648
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 32652
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 32648
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3196
    j .L3211
.L3196:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32656
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5112
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32656
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32660
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32660
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32664
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32664
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10
    slt t0, t0, t1
    li t3, 32668
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32668
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 32652
    add t3, t3, sp
    sw t1, 0(t3)
    j .L3211
.L3211:
    li t3, 32652
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3215
    j .L3450
.L3215:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32672
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32672
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 7
    mul t0, t0, t1
    li t3, 32676
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32680
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32680
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 11
    mul t0, t0, t1
    li t3, 32684
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32676
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32684
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 32688
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32692
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32692
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    mul t0, t0, t1
    li t3, 32696
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32688
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32696
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 32700
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32700
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    rem t0, t0, t1
    li t3, 32704
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32704
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32144
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32708
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5728
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32708
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32712
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32712
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32716
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32716
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, -1
    sub t0, t0, t1
    seqz t0, t0
    li t3, 32720
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32720
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3266
    j .L3329
.L3266:
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32724
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5728
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32724
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32728
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32732
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32732
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32728
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32736
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2844
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32736
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32740
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32744
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5112
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32744
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32748
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32748
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32752
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32740
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32752
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32756
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32760
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32760
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32756
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32764
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5112
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32764
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32768
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32772
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5112
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32772
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32776
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32776
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32780
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32780
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32784
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32784
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32768
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3438
.L3329:
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32788
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5728
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32788
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32792
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32792
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32796
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32800
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32796
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32800
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    snez t0, t0
    li t3, 32804
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32804
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3346
    j .L3437
.L3346:
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32808
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10592
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32808
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32812
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32812
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32816
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32816
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    slt t0, t0, t1
    li t3, 32820
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32820
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3362
    j .L3436
.L3362:
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32824
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8144
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32824
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32828
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32832
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10592
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32832
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32836
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32836
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32840
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32828
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32840
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32844
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32848
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32848
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32844
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32852
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10592
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32852
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32856
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32860
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10592
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32860
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32864
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32864
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32868
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32868
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32872
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32872
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32856
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32876
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21008
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32876
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 200
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32880
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32884
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5728
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32884
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32888
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32888
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32892
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32880
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32892
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32896
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 32896
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3436
.L3436:
    j .L3437
.L3437:
    j .L3438
.L3438:
    li t3, 32136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32900
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32900
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32904
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32904
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32136
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3182
.L3450:
    j .L3451
.L3451:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32908
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32908
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32912
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32912
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3133
.L3463:
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32916
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21008
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 31436
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 31852
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 32916
    add t3, t3, sp
    lw a3, 0(t3)
    call detectDeadlock
    li t3, 32920
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 32920
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32152
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32924
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32924
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    li t3, 32928
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32928
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3483
    j .L3537
.L3483:
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32932
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32096
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32936
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 628(sp)
    lw a1, 212(sp)
    li t3, 32932
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 32936
    add t3, t3, sp
    lw a3, 0(t3)
    call findVictimTransaction
    li t3, 32940
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 32940
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32160
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32944
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32944
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 32948
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32948
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3506
    j .L3536
.L3506:
    li t3, 32160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32952
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32952
    add t3, t3, sp
    lw a0, 0(t3)
    lw a1, 212(sp)
    li t3, 2844
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 5112
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 5728
    add t3, t3, sp
    lw a4, 0(t3)
    li t3, 8144
    add t3, t3, sp
    lw a5, 0(t3)
    li t3, 10592
    add t3, t3, sp
    lw a6, 0(t3)
    li t3, 21008
    add t3, t3, sp
    lw a7, 0(t3)
    call abortTransaction
    li t3, 32088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32956
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32956
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 32960
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32960
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32088
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3536
.L3536:
    j .L3537
.L3537:
    li t0, 0
    li t3, 32120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3544
.L3544:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32964
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32968
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32964
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32968
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 32972
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32972
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3554
    j .L3662
.L3554:
    j .L3560
.L3560:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32976
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 212(sp)
    li t3, 32976
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 32980
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32980
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32984
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32984
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    li t3, 32988
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 32992
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 32988
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3574
    j .L3596
.L3574:
    li t3, 32096
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 32996
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33000
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 628(sp)
    li t3, 33000
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 33004
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33004
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33008
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32996
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33008
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    li t3, 33012
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33012
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    slt t0, t1, t0
    li t3, 33016
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33016
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 32992
    add t3, t3, sp
    sw t1, 0(t3)
    j .L3596
.L3596:
    li t3, 32992
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3600
    j .L3650
.L3600:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33020
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 32104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33024
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33020
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 33024
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 33028
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33028
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 4
    rem t0, t0, t1
    li t3, 33032
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33032
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 33036
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33036
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L3621
    j .L3649
.L3621:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33040
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33040
    add t3, t3, sp
    lw a0, 0(t3)
    lw a1, 212(sp)
    li t3, 2844
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 5112
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 5728
    add t3, t3, sp
    lw a4, 0(t3)
    li t3, 8144
    add t3, t3, sp
    lw a5, 0(t3)
    li t3, 10592
    add t3, t3, sp
    lw a6, 0(t3)
    call commitTransaction
    li t3, 32080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33044
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33044
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33048
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33048
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32080
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3649
.L3649:
    j .L3650
.L3650:
    li t3, 32120
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33052
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33052
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33056
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33056
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32120
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L3544
.L3662:
    li t3, 32096
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33060
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33064
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33064
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32096
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 32104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33068
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33068
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 33072
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33072
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 32104
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2984
.L3685:
    li t3, 32080
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33076
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33076
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 32088
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 33080
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 33080
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li a0, 26006
    call printlnInt
    li t3, 33084
    add t3, t3, sp
    lw a0, 0(t3)
    j .L6
.L6:
    li t0, 33100
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 33096
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 33104
    add sp, sp, t0
    jr ra
    .globl detectDeadlock
    .type detectDeadlock, @function
detectDeadlock:
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
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 40(sp)
    lw t0, 0(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3701
.L3701:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 44(sp)
    lw t1, 48(sp)
    slt t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L3711
    j .L3745
.L3711:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 4(sp)
    lw t1, 56(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 60(sp)
    li t0, 0
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 8(sp)
    lw t1, 64(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 68(sp)
    li t0, 0
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3701
.L3745:
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3752
.L3752:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    slt t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    bnez t0, .L3762
    j .L3806
.L3762:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 4(sp)
    lw t1, 92(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 104(sp)
    lw t0, 104(sp)
    bnez t0, .L3776
    j .L3794
.L3776:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 108(sp)
    lw a4, 112(sp)
    call detectCycleDFS
    sw a0, 116(sp)
    lw t0, 116(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 120(sp)
    lw t0, 120(sp)
    bnez t0, .L3791
    j .L3793
.L3791:
    li a0, 1
    j .L7
.L3793:
    j .L3794
.L3794:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3752
.L3806:
    li a0, 0
    j .L7
.L7:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl detectCycleDFS
    .type detectCycleDFS, @function
detectCycleDFS:
    addi sp, sp, -192
    sw ra, 188(sp)
    sw s0, 184(sp)
    addi s0, sp, 192
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    lw t0, 0(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 4(sp)
    lw t1, 56(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 60(sp)
    li t0, 1
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 8(sp)
    lw t1, 64(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 68(sp)
    li t0, 1
    lw t1, 68(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L3837
.L3837:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    slt t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    bnez t0, .L3847
    j .L3926
.L3847:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 0(sp)
    lw t1, 84(sp)
    li t2, 200
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 88(sp)
    lw t1, 92(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 104(sp)
    lw t0, 104(sp)
    bnez t0, .L3866
    j .L3914
.L3866:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 4(sp)
    lw t1, 108(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 120(sp)
    lw t0, 120(sp)
    bnez t0, .L3880
    j .L3898
.L3880:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw a0, 0(sp)
    lw a1, 4(sp)
    lw a2, 8(sp)
    lw a3, 124(sp)
    lw a4, 128(sp)
    call detectCycleDFS
    sw a0, 132(sp)
    lw t0, 132(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 136(sp)
    lw t0, 136(sp)
    bnez t0, .L3895
    j .L3897
.L3895:
    li a0, 1
    j .L8
.L3897:
    j .L3913
.L3898:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 8(sp)
    lw t1, 140(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 144(sp)
    lw t0, 144(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 148(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 152(sp)
    lw t0, 152(sp)
    bnez t0, .L3910
    j .L3912
.L3910:
    li a0, 1
    j .L8
.L3912:
    j .L3913
.L3913:
    j .L3914
.L3914:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 156(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L3837
.L3926:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 8(sp)
    lw t1, 164(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 168(sp)
    li t0, 0
    lw t1, 168(sp)
    sw t0, 0(t1)
    li a0, 0
    j .L8
.L8:
    lw ra, 188(sp)
    lw s0, 184(sp)
    addi sp, sp, 192
    jr ra
    .globl findVictimTransaction
    .type findVictimTransaction, @function
findVictimTransaction:
    addi sp, sp, -160
    sw ra, 156(sp)
    sw s0, 152(sp)
    addi s0, sp, 160
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 60(sp)
    lw t0, 0(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, -1
    lw t1, 44(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 60(sp)
    sw t0, 0(t1)
    j .L3950
.L3950:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 64(sp)
    lw t1, 68(sp)
    slt t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    bnez t0, .L3960
    j .L4034
.L3960:
    j .L3966
.L3966:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 4(sp)
    lw t1, 76(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 88(sp)
    li t1, 0
    sw t1, 92(sp)
    lw t0, 88(sp)
    bnez t0, .L3980
    j .L3997
.L3980:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 0(sp)
    lw t1, 96(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 104(sp)
    lw t1, 108(sp)
    slt t0, t1, t0
    sw t0, 112(sp)
    lw t1, 112(sp)
    sw t1, 92(sp)
    j .L3997
.L3997:
    lw t0, 92(sp)
    bnez t0, .L4001
    j .L4022
.L4001:
    lw t0, 60(sp)
    lw t0, 0(t0)
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
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L4022
.L4022:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 132(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    j .L3950
.L4034:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw a0, 140(sp)
    j .L9
.L9:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl abortTransaction
    .type abortTransaction, @function
abortTransaction:
    addi sp, sp, -384
    sw ra, 380(sp)
    sw s0, 376(sp)
    addi s0, sp, 384
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)
    sw a7, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 40(sp)
    addi t0, sp, 44
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 48(sp)
    addi t0, sp, 52
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 56(sp)
    addi t0, sp, 60
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 64(sp)
    addi t0, sp, 68
    sw t0, 72(sp)
    addi t0, sp, 76
    sw t0, 80(sp)
    addi t0, sp, 84
    sw t0, 88(sp)
    addi t0, sp, 92
    sw t0, 96(sp)
    lw t0, 0(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t1, 64(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 4(sp)
    lw t1, 100(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 104(sp)
    li t0, 3
    lw t1, 104(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L4059
.L4059:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 12(sp)
    lw t1, 112(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 108(sp)
    lw t1, 120(sp)
    slt t0, t0, t1
    sw t0, 124(sp)
    lw t0, 124(sp)
    bnez t0, .L4075
    j .L4251
.L4075:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 8(sp)
    lw t1, 128(sp)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 132(sp)
    lw t1, 136(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 16(sp)
    lw t1, 148(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 152(sp)
    li t0, -1
    lw t1, 152(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 24(sp)
    lw t1, 156(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 164(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 168(sp)
    lw t0, 168(sp)
    bnez t0, .L4119
    j .L4239
.L4119:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 20(sp)
    lw t1, 172(sp)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 176(sp)
    lw t0, 176(sp)
    addi t0, t0, 0
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 184(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 16(sp)
    lw t1, 188(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 192(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 196(sp)
    lw t1, 192(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 96(sp)
    sw t0, 0(t1)
    j .L4148
.L4148:
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 24(sp)
    lw t1, 204(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 208(sp)
    lw t0, 208(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 212(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 216(sp)
    lw t0, 200(sp)
    lw t1, 216(sp)
    slt t0, t0, t1
    sw t0, 220(sp)
    lw t0, 220(sp)
    bnez t0, .L4168
    j .L4215
.L4168:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 20(sp)
    lw t1, 224(sp)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 228(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 228(sp)
    lw t1, 232(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 236(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 240(sp)
    lw t0, 20(sp)
    lw t1, 240(sp)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 244(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 248(sp)
    lw t0, 248(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 252(sp)
    lw t0, 244(sp)
    lw t1, 252(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 256(sp)
    lw t0, 256(sp)
    lw t0, 0(t0)
    sw t0, 260(sp)
    lw t0, 260(sp)
    lw t1, 236(sp)
    sw t0, 0(t1)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 264(sp)
    lw t0, 264(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 268(sp)
    lw t0, 268(sp)
    lw t1, 96(sp)
    sw t0, 0(t1)
    j .L4148
.L4215:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t0, 24(sp)
    lw t1, 272(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 276(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 24(sp)
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
    sw t0, 292(sp)
    lw t0, 292(sp)
    lw t1, 276(sp)
    sw t0, 0(t1)
    j .L4239
.L4239:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 296(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 300(sp)
    lw t0, 300(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L4059
.L4251:
    li t0, 0
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L4258
.L4258:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 304(sp)
    lw t0, 304(sp)
    li t1, 50
    slt t0, t0, t1
    sw t0, 308(sp)
    lw t0, 308(sp)
    bnez t0, .L4266
    j .L4312
.L4266:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 28(sp)
    lw t1, 312(sp)
    li t2, 200
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 320(sp)
    lw t0, 316(sp)
    lw t1, 320(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 324(sp)
    li t0, 0
    lw t1, 324(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 328(sp)
    lw t0, 28(sp)
    lw t1, 328(sp)
    li t2, 200
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 332(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 336(sp)
    lw t0, 332(sp)
    lw t1, 336(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 340(sp)
    li t0, 0
    lw t1, 340(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 344(sp)
    lw t0, 344(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 348(sp)
    lw t0, 348(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L4258
.L4312:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 352(sp)
    lw t0, 12(sp)
    lw t1, 352(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 356(sp)
    li t0, 0
    lw t1, 356(sp)
    sw t0, 0(t1)
    lw a0, 360(sp)
    j .L10
.L10:
    lw ra, 380(sp)
    lw s0, 376(sp)
    addi sp, sp, 384
    jr ra
    .globl commitTransaction
    .type commitTransaction, @function
commitTransaction:
    addi sp, sp, -320
    sw ra, 316(sp)
    sw s0, 312(sp)
    addi s0, sp, 320
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 40(sp)
    addi t0, sp, 44
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 48(sp)
    addi t0, sp, 52
    sw t0, 52(sp)
    addi t0, sp, 56
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
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 4(sp)
    lw t1, 92(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 96(sp)
    li t0, 2
    lw t1, 96(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 64(sp)
    sw t0, 0(t1)
    j .L4346
.L4346:
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 12(sp)
    lw t1, 104(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 100(sp)
    lw t1, 112(sp)
    slt t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    bnez t0, .L4362
    j .L4538
.L4362:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 8(sp)
    lw t1, 120(sp)
    li t2, 40
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 124(sp)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 124(sp)
    lw t1, 128(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 16(sp)
    lw t1, 140(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 144(sp)
    li t0, -1
    lw t1, 144(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 24(sp)
    lw t1, 148(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 156(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 160(sp)
    lw t0, 160(sp)
    bnez t0, .L4406
    j .L4526
.L4406:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 20(sp)
    lw t1, 164(sp)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 168(sp)
    lw t0, 168(sp)
    addi t0, t0, 0
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 176(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 16(sp)
    lw t1, 180(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 184(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 188(sp)
    lw t1, 184(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 88(sp)
    sw t0, 0(t1)
    j .L4435
.L4435:
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 24(sp)
    lw t1, 196(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 204(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 208(sp)
    lw t0, 192(sp)
    lw t1, 208(sp)
    slt t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    bnez t0, .L4455
    j .L4502
.L4455:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 20(sp)
    lw t1, 216(sp)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 220(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 220(sp)
    lw t1, 224(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 228(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 20(sp)
    lw t1, 232(sp)
    li t2, 20
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 236(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 240(sp)
    lw t0, 240(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 244(sp)
    lw t0, 236(sp)
    lw t1, 244(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 248(sp)
    lw t0, 0(t0)
    sw t0, 252(sp)
    lw t0, 252(sp)
    lw t1, 228(sp)
    sw t0, 0(t1)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 256(sp)
    lw t0, 256(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 260(sp)
    lw t0, 260(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    j .L4435
.L4502:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 264(sp)
    lw t0, 24(sp)
    lw t1, 264(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 268(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t0, 24(sp)
    lw t1, 272(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 276(sp)
    lw t0, 276(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 280(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 284(sp)
    lw t0, 284(sp)
    lw t1, 268(sp)
    sw t0, 0(t1)
    j .L4526
.L4526:
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 288(sp)
    lw t0, 288(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 292(sp)
    lw t0, 292(sp)
    lw t1, 64(sp)
    sw t0, 0(t1)
    j .L4346
.L4538:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 12(sp)
    lw t1, 296(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 300(sp)
    li t0, 0
    lw t1, 300(sp)
    sw t0, 0(t1)
    lw a0, 304(sp)
    j .L11
.L11:
    lw ra, 316(sp)
    lw s0, 312(sp)
    addi sp, sp, 320
    jr ra
    .globl performBufferPoolTest
    .type performBufferPoolTest, @function
performBufferPoolTest:
    li t0, -8992
    add sp, sp, t0
    li t0, 8988
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 8984
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 8992
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 412(sp)
    addi t0, sp, 416
    sw t0, 420(sp)
    addi t0, sp, 424
    sw t0, 824(sp)
    addi t0, sp, 828
    sw t0, 1228(sp)
    addi t0, sp, 1232
    sw t0, 1236(sp)
    addi t0, sp, 1240
    sw t0, 1640(sp)
    addi t0, sp, 1644
    sw t0, 2044(sp)
    li t1, 2048
    add t0, sp, t1
    li t3, 2052
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2056
    add t0, sp, t1
    li t3, 2456
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2460
    add t0, sp, t1
    li t3, 2860
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2864
    add t0, sp, t1
    li t3, 2868
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2872
    add t0, sp, t1
    li t3, 3272
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 3276
    add t0, sp, t1
    li t3, 3676
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 3680
    add t0, sp, t1
    li t3, 3684
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 3688
    add t0, sp, t1
    li t3, 4088
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4092
    add t0, sp, t1
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
    li t3, 6108
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6112
    add t0, sp, t1
    li t3, 6116
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6120
    add t0, sp, t1
    li t3, 8120
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8124
    add t0, sp, t1
    li t3, 8128
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8132
    add t0, sp, t1
    li t3, 8136
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8140
    add t0, sp, t1
    li t3, 8144
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8148
    add t0, sp, t1
    li t3, 8152
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8156
    add t0, sp, t1
    li t3, 8160
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8164
    add t0, sp, t1
    li t3, 8168
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8172
    add t0, sp, t1
    li t3, 8176
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8180
    add t0, sp, t1
    li t3, 8184
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8188
    add t0, sp, t1
    li t3, 8192
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8196
    add t0, sp, t1
    li t3, 8200
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8204
    add t0, sp, t1
    li t3, 8208
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8212
    add t0, sp, t1
    li t3, 8216
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8220
    add t0, sp, t1
    li t3, 8224
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8228
    add t0, sp, t1
    li t3, 8232
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li a0, 26007
    call printlnInt
    li t0, 0
    lw t1, 420(sp)
    sw t0, 0(t1)
    j .L4558
.L4558:
    lw t0, 420(sp)
    lw t0, 0(t0)
    li t3, 8236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8236
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 8240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8240
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4562
    j .L4563
.L4562:
    lw t0, 420(sp)
    lw t0, 0(t0)
    li t3, 8244
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 824(sp)
    li t3, 8244
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8248
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 8248
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 420(sp)
    lw t0, 0(t0)
    li t3, 8252
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8252
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8256
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8256
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 420(sp)
    sw t0, 0(t1)
    j .L4558
.L4563:
    lw a0, 412(sp)
    lw a1, 824(sp)
    li a2, 400
    call memcpy
    li t0, 0
    lw t1, 1236(sp)
    sw t0, 0(t1)
    j .L4572
.L4572:
    lw t0, 1236(sp)
    lw t0, 0(t0)
    li t3, 8260
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8260
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 8264
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8264
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4576
    j .L4577
.L4576:
    lw t0, 1236(sp)
    lw t0, 0(t0)
    li t3, 8268
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1640(sp)
    li t3, 8268
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8272
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8272
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 1236(sp)
    lw t0, 0(t0)
    li t3, 8276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8276
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8280
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 1236(sp)
    sw t0, 0(t1)
    j .L4572
.L4577:
    lw a0, 1228(sp)
    lw a1, 1640(sp)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 2052
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4586
.L4586:
    li t3, 2052
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8284
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8284
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 8288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8288
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4590
    j .L4591
.L4590:
    li t3, 2052
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2456
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8292
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8296
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8296
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 2052
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8300
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8304
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2052
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4586
.L4591:
    lw a0, 2044(sp)
    li t3, 2456
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 2868
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4600
.L4600:
    li t3, 2868
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8308
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8308
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 8312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8312
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4604
    j .L4605
.L4604:
    li t3, 2868
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3272
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8316
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8320
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8320
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 2868
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8328
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8328
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2868
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4600
.L4605:
    li t3, 2860
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 3272
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 3684
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4614
.L4614:
    li t3, 3684
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8332
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 8336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8336
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4618
    j .L4619
.L4618:
    li t3, 3684
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4088
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8340
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8344
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8344
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3684
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8348
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8352
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3684
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4614
.L4619:
    li t3, 3676
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 4088
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 4096
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 1
    li t3, 4104
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 6116
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4633
.L4633:
    li t3, 6116
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8356
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 500
    slt t0, t0, t1
    li t3, 8360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8360
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4637
    j .L4638
.L4637:
    li t3, 6116
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8120
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8364
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8368
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 8368
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6116
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8372
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8372
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8376
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6116
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4633
.L4638:
    li t3, 6108
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8120
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2000
    call memcpy
    li t0, 0
    li t3, 8128
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8136
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8144
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8152
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8160
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4654
.L4654:
    j .L4658
.L4658:
    li t3, 8160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8380
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 30
    slt t0, t0, t1
    li t3, 8384
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 8388
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 8384
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4666
    j .L4675
.L4666:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8392
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8392
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 8396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8396
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 8388
    add t3, t3, sp
    sw t1, 0(t3)
    j .L4675
.L4675:
    li t3, 8388
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4679
    j .L5320
.L4679:
    li t3, 8160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8400
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 4
    rem t0, t0, t1
    li t3, 8404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8404
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8168
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8408
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    rem t0, t0, t1
    li t3, 8412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8412
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    add t0, t0, t1
    li t3, 8416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8416
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8176
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8184
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4704
.L4704:
    j .L4708
.L4708:
    li t3, 8184
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8176
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8424
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8420
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8424
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 8428
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 8432
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 8428
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4718
    j .L4727
.L4718:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8436
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8436
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 200
    slt t0, t0, t1
    li t3, 8440
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8440
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 8432
    add t3, t3, sp
    sw t1, 0(t3)
    j .L4727
.L4727:
    li t3, 8432
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4731
    j .L5308
.L4731:
    li t3, 8168
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8444
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8444
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 8448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8448
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4745
    j .L4767
.L4745:
    li t3, 8160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8452
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10
    mul t0, t0, t1
    li t3, 8456
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8184
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8460
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8456
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8460
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 8464
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8464
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 400
    rem t0, t0, t1
    li t3, 8468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8468
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8472
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8472
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8192
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4854
.L4767:
    li t3, 8168
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8476
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    li t3, 8480
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8480
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4777
    j .L4798
.L4777:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8484
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 17
    mul t0, t0, t1
    li t3, 8488
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8488
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 23
    add t0, t0, t1
    li t3, 8492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8492
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 350
    rem t0, t0, t1
    li t3, 8496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8496
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8500
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8192
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4853
.L4798:
    li t3, 8168
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8504
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8504
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2
    sub t0, t0, t1
    seqz t0, t0
    li t3, 8508
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8508
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4808
    j .L4825
.L4808:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8512
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8512
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    mul t0, t0, t1
    li t3, 8516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8516
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 50
    rem t0, t0, t1
    li t3, 8520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8520
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8524
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8524
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8192
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4852
.L4825:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8528
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8528
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 7
    mul t0, t0, t1
    li t3, 8532
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8536
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 11
    mul t0, t0, t1
    li t3, 8540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8532
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8540
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 8544
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8544
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 300
    rem t0, t0, t1
    li t3, 8548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8548
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8552
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8552
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8192
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4852
.L4852:
    j .L4853
.L4853:
    j .L4854
.L4854:
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8556
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6108
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8556
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8560
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8200
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4870
.L4870:
    li t3, 8200
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8568
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8568
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 8572
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 8576
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 8572
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4878
    j .L4895
.L4878:
    li t3, 8200
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8580
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 412(sp)
    li t3, 8580
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8584
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8584
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8588
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8592
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8588
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8592
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    seqz t0, t0
    li t3, 8596
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8596
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 8576
    add t3, t3, sp
    sw t1, 0(t3)
    j .L4895
.L4895:
    li t3, 8576
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4899
    j .L4935
.L4899:
    li t3, 8128
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8600
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8600
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8604
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8604
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8128
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8200
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8608
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2860
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8608
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8612
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8616
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8616
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8612
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8200
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8620
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3676
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8620
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8624
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 8624
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L5217
.L4935:
    li t3, 8136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8628
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8628
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8632
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8632
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8136
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 8636
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 412(sp)
    li t3, 8636
    add t3, t3, sp
    lw a1, 0(t3)
    call findFreeBufferSlot
    li t3, 8640
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8640
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8208
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8644
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8644
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 8648
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8648
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4965
    j .L5038
.L4965:
    li t3, 8208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8652
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 412(sp)
    li t3, 8652
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8656
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8660
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8660
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8656
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8664
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1228(sp)
    li t3, 8664
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8668
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8668
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8672
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 2044(sp)
    li t3, 8672
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8676
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8676
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8680
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2860
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8680
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8684
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8688
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8688
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8684
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8692
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3676
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8692
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8696
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 8696
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8700
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6108
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8700
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8704
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8708
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8708
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8704
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L5216
.L5038:
    li t3, 4096
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8712
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 8716
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 412(sp)
    lw a1, 2044(sp)
    li t3, 3676
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 8712
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 8716
    add t3, t3, sp
    lw a4, 0(t3)
    call clockPageReplacement
    li t3, 8720
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 8720
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8216
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8724
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8724
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 8728
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8728
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L5063
    j .L5215
.L5063:
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8732
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8732
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8736
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 8740
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8736
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8740
    add t3, t3, sp
    lw t1, 0(t3)
    rem t0, t0, t1
    li t3, 8744
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8744
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 4096
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8748
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 412(sp)
    li t3, 8748
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8752
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8752
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8756
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8756
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8224
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L5097
.L5097:
    li t3, 8224
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8760
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8760
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 8764
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 8768
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 8764
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L5105
    j .L5114
.L5105:
    li t3, 8224
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8772
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8772
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 500
    slt t0, t0, t1
    li t3, 8776
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8776
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 8768
    add t3, t3, sp
    sw t1, 0(t3)
    j .L5114
.L5114:
    li t3, 8768
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L5118
    j .L5131
.L5118:
    li t3, 8224
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8780
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6108
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8780
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8784
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 8784
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L5131
.L5131:
    li t3, 8144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8788
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8788
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8792
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8792
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8144
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8796
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 412(sp)
    li t3, 8796
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8800
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8804
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8804
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8800
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8808
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1228(sp)
    li t3, 8808
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8812
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8812
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8816
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 2044(sp)
    li t3, 8816
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8820
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 8820
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8824
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2860
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8824
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8828
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8832
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8832
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8828
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8836
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3676
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8836
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8840
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 8840
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8844
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6108
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8844
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8848
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8216
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8852
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8852
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8848
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L5215
.L5215:
    j .L5216
.L5216:
    j .L5217
.L5217:
    j .L5223
.L5223:
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8856
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8856
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    rem t0, t0, t1
    li t3, 8860
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8860
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 8864
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 8868
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 8864
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L5236
    j .L5251
.L5236:
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8872
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6108
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8872
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8876
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8876
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8880
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8880
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 8884
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8884
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 8868
    add t3, t3, sp
    sw t1, 0(t3)
    j .L5251
.L5251:
    li t3, 8868
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L5255
    j .L5274
.L5255:
    li t3, 8192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8888
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6108
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8888
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8892
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8892
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8896
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1228(sp)
    li t3, 8896
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 8900
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 8900
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L5274
.L5274:
    li t3, 4104
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8904
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8904
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8908
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8908
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 4104
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8912
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8912
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8916
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8916
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8152
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8184
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8920
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8920
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8924
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8924
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8184
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4704
.L5308:
    li t3, 8160
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8928
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8928
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 8932
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8932
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8160
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4654
.L5320:
    li t3, 8128
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8936
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8936
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    mul t0, t0, t1
    li t3, 8940
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8128
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8944
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8948
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8944
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8948
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 8952
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8940
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8952
    add t3, t3, sp
    lw t1, 0(t3)
    div t0, t0, t1
    li t3, 8956
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8956
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8232
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8128
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8960
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8960
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 8136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8964
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8964
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 8232
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8968
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8968
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 8144
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 8972
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8972
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li a0, 26008
    call printlnInt
    li t3, 8976
    add t3, t3, sp
    lw a0, 0(t3)
    j .L12
.L12:
    li t0, 8988
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 8984
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 8992
    add sp, sp, t0
    jr ra
    .globl findFreeBufferSlot
    .type findFreeBufferSlot, @function
findFreeBufferSlot:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    addi s0, sp, 80
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L5362
.L5362:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 28(sp)
    lw t1, 32(sp)
    slt t0, t0, t1
    sw t0, 36(sp)
    lw t0, 36(sp)
    bnez t0, .L5372
    j .L5407
.L5372:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 0(sp)
    lw t1, 40(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, -1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L5389
    j .L5395
.L5389:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw a0, 56(sp)
    j .L13
.L5395:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 60(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L5362
.L5407:
    li a0, -1
    j .L13
.L13:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl clockPageReplacement
    .type clockPageReplacement, @function
clockPageReplacement:
    addi sp, sp, -224
    sw ra, 220(sp)
    sw s0, 216(sp)
    addi s0, sp, 224
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    lw t0, 0(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 60(sp)
    sw t0, 0(t1)
    j .L5421
.L5421:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 2
    slt t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    bnez t0, .L5429
    j .L5521
.L5429:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 4(sp)
    lw t1, 84(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 96(sp)
    lw t0, 96(sp)
    bnez t0, .L5445
    j .L5478
.L5445:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 8(sp)
    lw t1, 100(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 112(sp)
    lw t0, 112(sp)
    bnez t0, .L5459
    j .L5465
.L5459:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw a0, 116(sp)
    j .L14
.L5465:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 8(sp)
    lw t1, 120(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 124(sp)
    li t0, 0
    lw t1, 124(sp)
    sw t0, 0(t1)
    j .L5477
.L5477:
    j .L5478
.L5478:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 128(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 132(sp)
    lw t1, 136(sp)
    rem t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 144(sp)
    lw t1, 148(sp)
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 152(sp)
    lw t0, 152(sp)
    bnez t0, .L5508
    j .L5520
.L5508:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 156(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    j .L5520
.L5520:
    j .L5421
.L5521:
    li t0, 0
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L5525
.L5525:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 164(sp)
    lw t1, 168(sp)
    slt t0, t0, t1
    sw t0, 172(sp)
    lw t0, 172(sp)
    bnez t0, .L5535
    j .L5569
.L5535:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 4(sp)
    lw t1, 176(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 184(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 188(sp)
    lw t0, 188(sp)
    bnez t0, .L5551
    j .L5557
.L5551:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw a0, 192(sp)
    j .L14
.L5557:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 196(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L5525
.L5569:
    li a0, -1
    j .L14
.L14:
    lw ra, 220(sp)
    lw s0, 216(sp)
    addi sp, sp, 224
    jr ra
    .globl performQueryOptimizationTest
    .type performQueryOptimizationTest, @function
performQueryOptimizationTest:
    addi sp, sp, -1440
    sw ra, 1436(sp)
    sw s0, 1432(sp)
    addi s0, sp, 1440
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 56(sp)
    addi t0, sp, 60
    sw t0, 80(sp)
    addi t0, sp, 84
    sw t0, 104(sp)
    addi t0, sp, 108
    sw t0, 168(sp)
    addi t0, sp, 172
    sw t0, 184(sp)
    addi t0, sp, 188
    sw t0, 192(sp)
    addi t0, sp, 196
    sw t0, 256(sp)
    addi t0, sp, 260
    sw t0, 340(sp)
    addi t0, sp, 344
    sw t0, 348(sp)
    addi t0, sp, 352
    sw t0, 432(sp)
    addi t0, sp, 436
    sw t0, 516(sp)
    addi t0, sp, 520
    sw t0, 524(sp)
    addi t0, sp, 528
    sw t0, 608(sp)
    addi t0, sp, 612
    sw t0, 616(sp)
    addi t0, sp, 620
    sw t0, 624(sp)
    addi t0, sp, 628
    sw t0, 632(sp)
    addi t0, sp, 636
    sw t0, 640(sp)
    addi t0, sp, 644
    sw t0, 648(sp)
    addi t0, sp, 652
    sw t0, 656(sp)
    addi t0, sp, 660
    sw t0, 664(sp)
    addi t0, sp, 668
    sw t0, 688(sp)
    addi t0, sp, 692
    sw t0, 712(sp)
    addi t0, sp, 716
    sw t0, 736(sp)
    addi t0, sp, 740
    sw t0, 760(sp)
    addi t0, sp, 764
    sw t0, 784(sp)
    addi t0, sp, 788
    sw t0, 808(sp)
    addi t0, sp, 812
    sw t0, 816(sp)
    addi t0, sp, 820
    sw t0, 880(sp)
    addi t0, sp, 884
    sw t0, 888(sp)
    addi t0, sp, 892
    sw t0, 912(sp)
    addi t0, sp, 916
    sw t0, 920(sp)
    addi t0, sp, 924
    sw t0, 928(sp)
    addi t0, sp, 932
    sw t0, 936(sp)
    addi t0, sp, 940
    sw t0, 944(sp)
    addi t0, sp, 948
    sw t0, 952(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li a0, 26009
    call printlnInt
    lw t0, 56(sp)
    addi t0, t0, 0
    sw t0, 956(sp)
    li t0, 100
    lw t1, 956(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    addi t0, t0, 4
    sw t0, 960(sp)
    li t0, 200
    lw t1, 960(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    addi t0, t0, 8
    sw t0, 964(sp)
    li t0, 150
    lw t1, 964(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    addi t0, t0, 12
    sw t0, 968(sp)
    li t0, 300
    lw t1, 968(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    addi t0, t0, 16
    sw t0, 972(sp)
    li t0, 250
    lw t1, 972(sp)
    sw t0, 0(t1)
    lw a0, 32(sp)
    lw a1, 56(sp)
    li a2, 20
    call memcpy
    lw t0, 104(sp)
    addi t0, t0, 0
    sw t0, 976(sp)
    li t0, 10
    lw t1, 976(sp)
    sw t0, 0(t1)
    lw t0, 104(sp)
    addi t0, t0, 4
    sw t0, 980(sp)
    li t0, 20
    lw t1, 980(sp)
    sw t0, 0(t1)
    lw t0, 104(sp)
    addi t0, t0, 8
    sw t0, 984(sp)
    li t0, 15
    lw t1, 984(sp)
    sw t0, 0(t1)
    lw t0, 104(sp)
    addi t0, t0, 12
    sw t0, 988(sp)
    li t0, 30
    lw t1, 988(sp)
    sw t0, 0(t1)
    lw t0, 104(sp)
    addi t0, t0, 16
    sw t0, 992(sp)
    li t0, 25
    lw t1, 992(sp)
    sw t0, 0(t1)
    lw a0, 80(sp)
    lw a1, 104(sp)
    li a2, 20
    call memcpy
    lw t0, 184(sp)
    addi t0, t0, 0
    sw t0, 996(sp)
    li t0, 10
    lw t1, 996(sp)
    sw t0, 0(t1)
    lw t0, 184(sp)
    addi t0, t0, 4
    sw t0, 1000(sp)
    li t0, 25
    lw t1, 1000(sp)
    sw t0, 0(t1)
    lw t0, 184(sp)
    addi t0, t0, 8
    sw t0, 1004(sp)
    li t0, 50
    lw t1, 1004(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 192(sp)
    sw t0, 0(t1)
    j .L5600
.L5600:
    lw t0, 192(sp)
    lw t0, 0(t0)
    sw t0, 1008(sp)
    lw t0, 1008(sp)
    li t1, 5
    slt t0, t0, t1
    sw t0, 1012(sp)
    lw t0, 1012(sp)
    bnez t0, .L5604
    j .L5605
.L5604:
    lw t0, 192(sp)
    lw t0, 0(t0)
    sw t0, 1016(sp)
    lw t0, 256(sp)
    lw t1, 1016(sp)
    li t2, 12
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1020(sp)
    lw a0, 1020(sp)
    lw a1, 184(sp)
    li a2, 12
    call memcpy
    lw t0, 192(sp)
    lw t0, 0(t0)
    sw t0, 1024(sp)
    lw t0, 1024(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1028(sp)
    lw t0, 1028(sp)
    lw t1, 192(sp)
    sw t0, 0(t1)
    j .L5600
.L5605:
    lw a0, 168(sp)
    lw a1, 256(sp)
    li a2, 60
    call memcpy
    li t0, 0
    lw t1, 348(sp)
    sw t0, 0(t1)
    j .L5614
.L5614:
    lw t0, 348(sp)
    lw t0, 0(t0)
    sw t0, 1032(sp)
    lw t0, 1032(sp)
    li t1, 20
    slt t0, t0, t1
    sw t0, 1036(sp)
    lw t0, 1036(sp)
    bnez t0, .L5618
    j .L5619
.L5618:
    lw t0, 348(sp)
    lw t0, 0(t0)
    sw t0, 1040(sp)
    lw t0, 432(sp)
    lw t1, 1040(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1044(sp)
    li t0, 0
    lw t1, 1044(sp)
    sw t0, 0(t1)
    lw t0, 348(sp)
    lw t0, 0(t0)
    sw t0, 1048(sp)
    lw t0, 1048(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1052(sp)
    lw t0, 1052(sp)
    lw t1, 348(sp)
    sw t0, 0(t1)
    j .L5614
.L5619:
    lw a0, 340(sp)
    lw a1, 432(sp)
    li a2, 80
    call memcpy
    li t0, 0
    lw t1, 524(sp)
    sw t0, 0(t1)
    j .L5628
.L5628:
    lw t0, 524(sp)
    lw t0, 0(t0)
    sw t0, 1056(sp)
    lw t0, 1056(sp)
    li t1, 20
    slt t0, t0, t1
    sw t0, 1060(sp)
    lw t0, 1060(sp)
    bnez t0, .L5632
    j .L5633
.L5632:
    lw t0, 524(sp)
    lw t0, 0(t0)
    sw t0, 1064(sp)
    lw t0, 608(sp)
    lw t1, 1064(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1068(sp)
    li t0, 0
    lw t1, 1068(sp)
    sw t0, 0(t1)
    lw t0, 524(sp)
    lw t0, 0(t0)
    sw t0, 1072(sp)
    lw t0, 1072(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1076(sp)
    lw t0, 1076(sp)
    lw t1, 524(sp)
    sw t0, 0(t1)
    j .L5628
.L5633:
    lw a0, 516(sp)
    lw a1, 608(sp)
    li a2, 80
    call memcpy
    li t0, 0
    lw t1, 616(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 624(sp)
    sw t0, 0(t1)
    j .L5643
.L5643:
    lw t0, 624(sp)
    lw t0, 0(t0)
    sw t0, 1080(sp)
    lw t0, 1080(sp)
    li t1, 10
    slt t0, t0, t1
    sw t0, 1084(sp)
    lw t0, 1084(sp)
    bnez t0, .L5651
    j .L5957
.L5651:
    lw t0, 624(sp)
    lw t0, 0(t0)
    sw t0, 1088(sp)
    lw t0, 1088(sp)
    li t1, 3
    rem t0, t0, t1
    sw t0, 1092(sp)
    lw t0, 1092(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1096(sp)
    lw t0, 1096(sp)
    lw t1, 632(sp)
    sw t0, 0(t1)
    li t0, 999999
    lw t1, 640(sp)
    sw t0, 0(t1)
    li t0, -1
    lw t1, 648(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 656(sp)
    sw t0, 0(t1)
    j .L5673
.L5673:
    j .L5677
.L5677:
    lw t0, 656(sp)
    lw t0, 0(t0)
    sw t0, 1100(sp)
    lw t0, 1100(sp)
    li t1, 6
    slt t0, t0, t1
    sw t0, 1104(sp)
    li t1, 0
    sw t1, 1108(sp)
    lw t0, 1104(sp)
    bnez t0, .L5685
    j .L5694
.L5685:
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1112(sp)
    lw t0, 1112(sp)
    li t1, 20
    slt t0, t0, t1
    sw t0, 1116(sp)
    lw t1, 1116(sp)
    sw t1, 1108(sp)
    j .L5694
.L5694:
    lw t0, 1108(sp)
    bnez t0, .L5698
    j .L5899
.L5698:
    li t0, 0
    lw t1, 664(sp)
    sw t0, 0(t1)
    lw t0, 656(sp)
    lw t0, 0(t0)
    sw t0, 1120(sp)
    lw t0, 1120(sp)
    li t1, 3
    rem t0, t0, t1
    sw t0, 1124(sp)
    lw t0, 1124(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1128(sp)
    lw t0, 1128(sp)
    bnez t0, .L5714
    j .L5742
.L5714:
    lw a0, 688(sp)
    lw a1, 32(sp)
    li a2, 20
    call memcpy
    lw a0, 712(sp)
    lw a1, 80(sp)
    li a2, 20
    call memcpy
    lw t0, 632(sp)
    lw t0, 0(t0)
    sw t0, 1132(sp)
    lw t0, 624(sp)
    lw t0, 0(t0)
    sw t0, 1136(sp)
    lw a0, 688(sp)
    lw a1, 712(sp)
    lw a2, 1132(sp)
    lw a3, 1136(sp)
    call estimateNestedLoopCost
    sw a0, 1140(sp)
    lw t0, 1140(sp)
    lw t1, 664(sp)
    sw t0, 0(t1)
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1144(sp)
    lw t0, 516(sp)
    lw t1, 1144(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1148(sp)
    li t0, 0
    lw t1, 1148(sp)
    sw t0, 0(t1)
    j .L5812
.L5742:
    lw t0, 656(sp)
    lw t0, 0(t0)
    sw t0, 1152(sp)
    lw t0, 1152(sp)
    li t1, 3
    rem t0, t0, t1
    sw t0, 1156(sp)
    lw t0, 1156(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1160(sp)
    lw t0, 1160(sp)
    bnez t0, .L5755
    j .L5783
.L5755:
    lw a0, 736(sp)
    lw a1, 32(sp)
    li a2, 20
    call memcpy
    lw a0, 760(sp)
    lw a1, 80(sp)
    li a2, 20
    call memcpy
    lw t0, 632(sp)
    lw t0, 0(t0)
    sw t0, 1164(sp)
    lw t0, 624(sp)
    lw t0, 0(t0)
    sw t0, 1168(sp)
    lw a0, 736(sp)
    lw a1, 760(sp)
    lw a2, 1164(sp)
    lw a3, 1168(sp)
    call estimateHashJoinCost
    sw a0, 1172(sp)
    lw t0, 1172(sp)
    lw t1, 664(sp)
    sw t0, 0(t1)
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1176(sp)
    lw t0, 516(sp)
    lw t1, 1176(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1180(sp)
    li t0, 1
    lw t1, 1180(sp)
    sw t0, 0(t1)
    j .L5811
.L5783:
    lw a0, 784(sp)
    lw a1, 32(sp)
    li a2, 20
    call memcpy
    lw a0, 808(sp)
    lw a1, 80(sp)
    li a2, 20
    call memcpy
    lw t0, 632(sp)
    lw t0, 0(t0)
    sw t0, 1184(sp)
    lw t0, 624(sp)
    lw t0, 0(t0)
    sw t0, 1188(sp)
    lw a0, 784(sp)
    lw a1, 808(sp)
    lw a2, 1184(sp)
    lw a3, 1188(sp)
    call estimateSortMergeCost
    sw a0, 1192(sp)
    lw t0, 1192(sp)
    lw t1, 664(sp)
    sw t0, 0(t1)
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1196(sp)
    lw t0, 516(sp)
    lw t1, 1196(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1200(sp)
    li t0, 2
    lw t1, 1200(sp)
    sw t0, 0(t1)
    j .L5811
.L5811:
    j .L5812
.L5812:
    lw a0, 880(sp)
    lw a1, 168(sp)
    li a2, 60
    call memcpy
    lw t0, 632(sp)
    lw t0, 0(t0)
    sw t0, 1204(sp)
    lw t0, 624(sp)
    lw t0, 0(t0)
    sw t0, 1208(sp)
    lw a0, 880(sp)
    lw a1, 1204(sp)
    lw a2, 1208(sp)
    call selectOptimalIndex
    sw a0, 1212(sp)
    lw t0, 1212(sp)
    lw t1, 816(sp)
    sw t0, 0(t1)
    lw t0, 664(sp)
    lw t0, 0(t0)
    sw t0, 1216(sp)
    lw t0, 816(sp)
    lw t0, 0(t0)
    sw t0, 1220(sp)
    lw t0, 1216(sp)
    lw t1, 1220(sp)
    add t0, t0, t1
    sw t0, 1224(sp)
    lw t0, 1224(sp)
    lw t1, 664(sp)
    sw t0, 0(t1)
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1228(sp)
    lw t0, 340(sp)
    lw t1, 1228(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1232(sp)
    lw t0, 664(sp)
    lw t0, 0(t0)
    sw t0, 1236(sp)
    lw t0, 1236(sp)
    lw t1, 1232(sp)
    sw t0, 0(t1)
    lw t0, 664(sp)
    lw t0, 0(t0)
    sw t0, 1240(sp)
    lw t0, 640(sp)
    lw t0, 0(t0)
    sw t0, 1244(sp)
    lw t0, 1240(sp)
    lw t1, 1244(sp)
    slt t0, t0, t1
    sw t0, 1248(sp)
    lw t0, 1248(sp)
    bnez t0, .L5861
    j .L5876
.L5861:
    lw t0, 664(sp)
    lw t0, 0(t0)
    sw t0, 1252(sp)
    lw t0, 1252(sp)
    lw t1, 640(sp)
    sw t0, 0(t1)
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1256(sp)
    lw t0, 1256(sp)
    lw t1, 648(sp)
    sw t0, 0(t1)
    j .L5876
.L5876:
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1260(sp)
    lw t0, 1260(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1264(sp)
    lw t0, 1264(sp)
    lw t1, 616(sp)
    sw t0, 0(t1)
    lw t0, 656(sp)
    lw t0, 0(t0)
    sw t0, 1268(sp)
    lw t0, 1268(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1272(sp)
    lw t0, 1272(sp)
    lw t1, 656(sp)
    sw t0, 0(t1)
    j .L5673
.L5899:
    lw t0, 648(sp)
    lw t0, 0(t0)
    sw t0, 1276(sp)
    lw t0, 1276(sp)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    sw t0, 1280(sp)
    lw t0, 1280(sp)
    bnez t0, .L5909
    j .L5945
.L5909:
    lw t0, 648(sp)
    lw t0, 0(t0)
    sw t0, 1284(sp)
    lw t0, 516(sp)
    lw t1, 1284(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1288(sp)
    lw t0, 1288(sp)
    lw t0, 0(t0)
    sw t0, 1292(sp)
    lw a0, 912(sp)
    lw a1, 32(sp)
    li a2, 20
    call memcpy
    lw t0, 632(sp)
    lw t0, 0(t0)
    sw t0, 1296(sp)
    lw a0, 1292(sp)
    lw a1, 912(sp)
    lw a2, 1296(sp)
    call simulatePlanExecution
    sw a0, 1300(sp)
    lw t0, 1300(sp)
    lw t1, 888(sp)
    sw t0, 0(t1)
    lw t0, 648(sp)
    lw t0, 0(t0)
    sw t0, 1304(sp)
    lw t0, 340(sp)
    lw t1, 1304(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1308(sp)
    lw t0, 1308(sp)
    lw t0, 0(t0)
    sw t0, 1312(sp)
    lw t0, 888(sp)
    lw t0, 0(t0)
    sw t0, 1316(sp)
    lw a0, 1312(sp)
    lw a1, 1316(sp)
    call calculateCostAccuracy
    sw a0, 1320(sp)
    lw t0, 1320(sp)
    lw t1, 920(sp)
    sw t0, 0(t1)
    lw t0, 920(sp)
    lw t0, 0(t0)
    sw t0, 1324(sp)
    lw a0, 1324(sp)
    call printlnInt
    j .L5945
.L5945:
    lw t0, 624(sp)
    lw t0, 0(t0)
    sw t0, 1328(sp)
    lw t0, 1328(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1332(sp)
    lw t0, 1332(sp)
    lw t1, 624(sp)
    sw t0, 0(t1)
    j .L5643
.L5957:
    li t0, 0
    lw t1, 928(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 936(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 944(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 952(sp)
    sw t0, 0(t1)
    j .L5967
.L5967:
    lw t0, 952(sp)
    lw t0, 0(t0)
    sw t0, 1336(sp)
    lw t0, 616(sp)
    lw t0, 0(t0)
    sw t0, 1340(sp)
    lw t0, 1336(sp)
    lw t1, 1340(sp)
    slt t0, t0, t1
    sw t0, 1344(sp)
    lw t0, 1344(sp)
    bnez t0, .L5977
    j .L6057
.L5977:
    lw t0, 952(sp)
    lw t0, 0(t0)
    sw t0, 1348(sp)
    lw t0, 516(sp)
    lw t1, 1348(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1352(sp)
    lw t0, 1352(sp)
    lw t0, 0(t0)
    sw t0, 1356(sp)
    lw t0, 1356(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1360(sp)
    lw t0, 1360(sp)
    bnez t0, .L5993
    j .L6005
.L5993:
    lw t0, 928(sp)
    lw t0, 0(t0)
    sw t0, 1364(sp)
    lw t0, 1364(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1368(sp)
    lw t0, 1368(sp)
    lw t1, 928(sp)
    sw t0, 0(t1)
    j .L6045
.L6005:
    lw t0, 952(sp)
    lw t0, 0(t0)
    sw t0, 1372(sp)
    lw t0, 516(sp)
    lw t1, 1372(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1376(sp)
    lw t0, 1376(sp)
    lw t0, 0(t0)
    sw t0, 1380(sp)
    lw t0, 1380(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1384(sp)
    lw t0, 1384(sp)
    bnez t0, .L6020
    j .L6032
.L6020:
    lw t0, 936(sp)
    lw t0, 0(t0)
    sw t0, 1388(sp)
    lw t0, 1388(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1392(sp)
    lw t0, 1392(sp)
    lw t1, 936(sp)
    sw t0, 0(t1)
    j .L6044
.L6032:
    lw t0, 944(sp)
    lw t0, 0(t0)
    sw t0, 1396(sp)
    lw t0, 1396(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1400(sp)
    lw t0, 1400(sp)
    lw t1, 944(sp)
    sw t0, 0(t1)
    j .L6044
.L6044:
    j .L6045
.L6045:
    lw t0, 952(sp)
    lw t0, 0(t0)
    sw t0, 1404(sp)
    lw t0, 1404(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1408(sp)
    lw t0, 1408(sp)
    lw t1, 952(sp)
    sw t0, 0(t1)
    j .L5967
.L6057:
    lw t0, 928(sp)
    lw t0, 0(t0)
    sw t0, 1412(sp)
    lw a0, 1412(sp)
    call printlnInt
    lw t0, 936(sp)
    lw t0, 0(t0)
    sw t0, 1416(sp)
    lw a0, 1416(sp)
    call printlnInt
    lw t0, 944(sp)
    lw t0, 0(t0)
    sw t0, 1420(sp)
    lw a0, 1420(sp)
    call printlnInt
    li a0, 26010
    call printlnInt
    lw a0, 1424(sp)
    j .L15
.L15:
    lw ra, 1436(sp)
    lw s0, 1432(sp)
    addi sp, sp, 1440
    jr ra
    .globl estimateNestedLoopCost
    .type estimateNestedLoopCost, @function
estimateNestedLoopCost:
    addi sp, sp, -176
    sw ra, 172(sp)
    sw s0, 168(sp)
    addi s0, sp, 176
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    lw t0, 0(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L6078
.L6078:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 80(sp)
    lw t0, 72(sp)
    lw t1, 80(sp)
    slt t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    bnez t0, .L6092
    j .L6156
.L6092:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
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
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 4(sp)
    lw t1, 124(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 120(sp)
    lw t1, 132(sp)
    mul t0, t0, t1
    sw t0, 136(sp)
    lw t0, 108(sp)
    lw t1, 136(sp)
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L6078
.L6156:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 156(sp)
    li t1, 100
    mul t0, t0, t1
    sw t0, 160(sp)
    lw t0, 152(sp)
    lw t1, 160(sp)
    add t0, t0, t1
    sw t0, 164(sp)
    lw a0, 164(sp)
    j .L16
.L16:
    lw ra, 172(sp)
    lw s0, 168(sp)
    addi sp, sp, 176
    jr ra
    .globl estimateHashJoinCost
    .type estimateHashJoinCost, @function
estimateHashJoinCost:
    addi sp, sp, -208
    sw ra, 204(sp)
    sw s0, 200(sp)
    addi s0, sp, 208
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    lw t0, 0(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L6179
.L6179:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 80(sp)
    lw t0, 72(sp)
    lw t1, 80(sp)
    slt t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    bnez t0, .L6193
    j .L6281
.L6193:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 4(sp)
    lw t1, 112(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 108(sp)
    lw t1, 120(sp)
    add t0, t0, t1
    sw t0, 124(sp)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 4(sp)
    lw t1, 128(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 124(sp)
    lw t1, 136(sp)
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
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
    li t1, 10
    div t0, t0, t1
    sw t0, 160(sp)
    lw t0, 144(sp)
    lw t1, 160(sp)
    add t0, t0, t1
    sw t0, 164(sp)
    lw t0, 164(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L6179
.L6281:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 180(sp)
    li t1, 50
    mul t0, t0, t1
    sw t0, 184(sp)
    lw t0, 176(sp)
    lw t1, 184(sp)
    add t0, t0, t1
    sw t0, 188(sp)
    lw a0, 188(sp)
    j .L17
.L17:
    lw ra, 204(sp)
    lw s0, 200(sp)
    addi sp, sp, 208
    jr ra
    .globl estimateSortMergeCost
    .type estimateSortMergeCost, @function
estimateSortMergeCost:
    addi sp, sp, -288
    sw ra, 284(sp)
    sw s0, 280(sp)
    addi s0, sp, 288
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    addi t0, sp, 72
    sw t0, 76(sp)
    addi t0, sp, 80
    sw t0, 84(sp)
    lw t0, 0(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L6304
.L6304:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 96(sp)
    lw t0, 88(sp)
    lw t1, 96(sp)
    slt t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    bnez t0, .L6318
    j .L6451
.L6318:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 0(sp)
    lw t1, 124(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
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
    lw a0, 144(sp)
    call logBase2
    sw a0, 148(sp)
    lw t0, 132(sp)
    lw t1, 148(sp)
    mul t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
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
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 0(sp)
    lw t1, 168(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw a0, 176(sp)
    call logBase2
    sw a0, 180(sp)
    lw t0, 164(sp)
    lw t1, 180(sp)
    mul t0, t0, t1
    sw t0, 184(sp)
    lw t0, 184(sp)
    lw t1, 84(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 188(sp)
    lw t1, 192(sp)
    add t0, t0, t1
    sw t0, 196(sp)
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 196(sp)
    lw t1, 200(sp)
    add t0, t0, t1
    sw t0, 204(sp)
    lw t0, 204(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 4(sp)
    lw t1, 212(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 216(sp)
    lw t0, 216(sp)
    lw t0, 0(t0)
    sw t0, 220(sp)
    lw t0, 208(sp)
    lw t1, 220(sp)
    add t0, t0, t1
    sw t0, 224(sp)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 228(sp)
    lw t0, 4(sp)
    lw t1, 228(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 232(sp)
    lw t0, 232(sp)
    lw t0, 0(t0)
    sw t0, 236(sp)
    lw t0, 224(sp)
    lw t1, 236(sp)
    add t0, t0, t1
    sw t0, 240(sp)
    lw t0, 240(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 244(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 248(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L6304
.L6451:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 252(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 256(sp)
    lw t0, 256(sp)
    li t1, 75
    mul t0, t0, t1
    sw t0, 260(sp)
    lw t0, 252(sp)
    lw t1, 260(sp)
    add t0, t0, t1
    sw t0, 264(sp)
    lw a0, 264(sp)
    j .L18
.L18:
    lw ra, 284(sp)
    lw s0, 280(sp)
    addi sp, sp, 288
    jr ra
    .globl logBase2
    .type logBase2, @function
logBase2:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 12(sp)
    lw t0, 12(sp)
    li t1, 1
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 16(sp)
    lw t0, 16(sp)
    bnez t0, .L6476
    j .L6478
.L6476:
    li a0, 1
    j .L19
.L6478:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 20(sp)
    lw t0, 20(sp)
    li t1, 2
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 24(sp)
    lw t0, 24(sp)
    bnez t0, .L6489
    j .L6491
.L6489:
    li a0, 1
    j .L19
.L6491:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 28(sp)
    li t1, 4
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 32(sp)
    lw t0, 32(sp)
    bnez t0, .L6502
    j .L6504
.L6502:
    li a0, 2
    j .L19
.L6504:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 36(sp)
    li t1, 8
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 40(sp)
    lw t0, 40(sp)
    bnez t0, .L6515
    j .L6517
.L6515:
    li a0, 3
    j .L19
.L6517:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 44(sp)
    li t1, 16
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 48(sp)
    lw t0, 48(sp)
    bnez t0, .L6528
    j .L6530
.L6528:
    li a0, 4
    j .L19
.L6530:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 52(sp)
    li t1, 32
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L6541
    j .L6543
.L6541:
    li a0, 5
    j .L19
.L6543:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 60(sp)
    li t1, 64
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L6554
    j .L6556
.L6554:
    li a0, 6
    j .L19
.L6556:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 68(sp)
    li t1, 128
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 72(sp)
    lw t0, 72(sp)
    bnez t0, .L6567
    j .L6569
.L6567:
    li a0, 7
    j .L19
.L6569:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 256
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 80(sp)
    lw t0, 80(sp)
    bnez t0, .L6580
    j .L6582
.L6580:
    li a0, 8
    j .L19
.L6582:
    li a0, 9
    j .L19
.L19:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl selectOptimalIndex
    .type selectOptimalIndex, @function
selectOptimalIndex:
    addi sp, sp, -192
    sw ra, 188(sp)
    sw s0, 184(sp)
    addi s0, sp, 192
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
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
    addi t0, sp, 56
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L6592
.L6592:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    slt t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    bnez t0, .L6602
    j .L6709
.L6602:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 92(sp)
    lw t1, 96(sp)
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 3
    rem t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 0(sp)
    lw t1, 108(sp)
    li t2, 12
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 112(sp)
    lw t1, 116(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 128(sp)
    li t1, 20
    slt t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    bnez t0, .L6651
    j .L6663
.L6651:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 10
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L6697
.L6663:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    li t1, 40
    slt t0, t0, t1
    sw t0, 148(sp)
    lw t0, 148(sp)
    bnez t0, .L6672
    j .L6684
.L6672:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 152(sp)
    li t1, 25
    add t0, t0, t1
    sw t0, 156(sp)
    lw t0, 156(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L6696
.L6684:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 160(sp)
    li t1, 50
    add t0, t0, t1
    sw t0, 164(sp)
    lw t0, 164(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L6696
.L6696:
    j .L6697
.L6697:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L6592
.L6709:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw a0, 176(sp)
    j .L20
.L20:
    lw ra, 188(sp)
    lw s0, 184(sp)
    addi sp, sp, 192
    jr ra
    .globl simulatePlanExecution
    .type simulatePlanExecution, @function
simulatePlanExecution:
    addi sp, sp, -432
    sw ra, 428(sp)
    sw s0, 424(sp)
    addi s0, sp, 432
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    addi t0, sp, 56
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    addi t0, sp, 72
    sw t0, 76(sp)
    addi t0, sp, 80
    sw t0, 84(sp)
    addi t0, sp, 88
    sw t0, 92(sp)
    addi t0, sp, 96
    sw t0, 100(sp)
    addi t0, sp, 104
    sw t0, 108(sp)
    lw t0, 0(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 116(sp)
    lw t0, 116(sp)
    bnez t0, .L6727
    j .L6815
.L6727:
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L6731
.L6731:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 128(sp)
    lw t0, 120(sp)
    lw t1, 128(sp)
    slt t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    bnez t0, .L6745
    j .L6814
.L6745:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 140(sp)
    lw t0, 4(sp)
    lw t1, 140(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 144(sp)
    lw t0, 144(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 152(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 156(sp)
    lw t0, 156(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 160(sp)
    lw t0, 4(sp)
    lw t1, 160(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 164(sp)
    lw t0, 164(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 176(sp)
    lw t1, 180(sp)
    mul t0, t0, t1
    sw t0, 184(sp)
    lw t0, 184(sp)
    li t1, 100
    div t0, t0, t1
    sw t0, 188(sp)
    lw t0, 172(sp)
    lw t1, 188(sp)
    add t0, t0, t1
    sw t0, 192(sp)
    lw t0, 192(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 196(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L6731
.L6814:
    j .L7029
.L6815:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 204(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 208(sp)
    lw t0, 208(sp)
    bnez t0, .L6824
    j .L6918
.L6824:
    li t0, 0
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L6828
.L6828:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 216(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 220(sp)
    lw t0, 212(sp)
    lw t1, 220(sp)
    slt t0, t0, t1
    sw t0, 224(sp)
    lw t0, 224(sp)
    bnez t0, .L6842
    j .L6917
.L6842:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 228(sp)
    lw t0, 228(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 232(sp)
    lw t0, 4(sp)
    lw t1, 232(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 236(sp)
    lw t0, 236(sp)
    lw t0, 0(t0)
    sw t0, 240(sp)
    lw t0, 240(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 244(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 248(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 252(sp)
    lw t0, 4(sp)
    lw t1, 252(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 256(sp)
    lw t0, 256(sp)
    lw t0, 0(t0)
    sw t0, 260(sp)
    lw t0, 260(sp)
    lw t1, 84(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 264(sp)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 268(sp)
    lw t0, 264(sp)
    lw t1, 268(sp)
    add t0, t0, t1
    sw t0, 272(sp)
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 276(sp)
    lw t0, 272(sp)
    lw t1, 276(sp)
    add t0, t0, t1
    sw t0, 280(sp)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 284(sp)
    lw t0, 284(sp)
    li t1, 10
    div t0, t0, t1
    sw t0, 288(sp)
    lw t0, 280(sp)
    lw t1, 288(sp)
    add t0, t0, t1
    sw t0, 292(sp)
    lw t0, 292(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 296(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 300(sp)
    lw t0, 300(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L6828
.L6917:
    j .L7028
.L6918:
    li t0, 0
    lw t1, 92(sp)
    sw t0, 0(t1)
    j .L6922
.L6922:
    lw t0, 92(sp)
    lw t0, 0(t0)
    sw t0, 304(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 308(sp)
    lw t0, 308(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 312(sp)
    lw t0, 304(sp)
    lw t1, 312(sp)
    slt t0, t0, t1
    sw t0, 316(sp)
    lw t0, 316(sp)
    bnez t0, .L6936
    j .L7027
.L6936:
    lw t0, 92(sp)
    lw t0, 0(t0)
    sw t0, 320(sp)
    lw t0, 320(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 324(sp)
    lw t0, 4(sp)
    lw t1, 324(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 328(sp)
    lw t0, 328(sp)
    lw t0, 0(t0)
    sw t0, 332(sp)
    lw t0, 332(sp)
    lw t1, 100(sp)
    sw t0, 0(t1)
    lw t0, 92(sp)
    lw t0, 0(t0)
    sw t0, 336(sp)
    lw t0, 336(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 340(sp)
    lw t0, 340(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 344(sp)
    lw t0, 4(sp)
    lw t1, 344(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 348(sp)
    lw t0, 348(sp)
    lw t0, 0(t0)
    sw t0, 352(sp)
    lw t0, 352(sp)
    lw t1, 108(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 356(sp)
    lw t0, 100(sp)
    lw t0, 0(t0)
    sw t0, 360(sp)
    lw t0, 360(sp)
    li t1, 2
    mul t0, t0, t1
    sw t0, 364(sp)
    lw t0, 356(sp)
    lw t1, 364(sp)
    add t0, t0, t1
    sw t0, 368(sp)
    lw t0, 108(sp)
    lw t0, 0(t0)
    sw t0, 372(sp)
    lw t0, 372(sp)
    li t1, 2
    mul t0, t0, t1
    sw t0, 376(sp)
    lw t0, 368(sp)
    lw t1, 376(sp)
    add t0, t0, t1
    sw t0, 380(sp)
    lw t0, 380(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 384(sp)
    lw t0, 100(sp)
    lw t0, 0(t0)
    sw t0, 388(sp)
    lw t0, 384(sp)
    lw t1, 388(sp)
    add t0, t0, t1
    sw t0, 392(sp)
    lw t0, 108(sp)
    lw t0, 0(t0)
    sw t0, 396(sp)
    lw t0, 392(sp)
    lw t1, 396(sp)
    add t0, t0, t1
    sw t0, 400(sp)
    lw t0, 400(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 92(sp)
    lw t0, 0(t0)
    sw t0, 404(sp)
    lw t0, 404(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 408(sp)
    lw t0, 408(sp)
    lw t1, 92(sp)
    sw t0, 0(t1)
    j .L6922
.L7027:
    j .L7028
.L7028:
    j .L7029
.L7029:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 412(sp)
    lw a0, 412(sp)
    j .L21
.L21:
    lw ra, 428(sp)
    lw s0, 424(sp)
    addi sp, sp, 432
    jr ra
    .globl calculateCostAccuracy
    .type calculateCostAccuracy, @function
calculateCostAccuracy:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 36(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 40(sp)
    lw t1, 44(sp)
    slt t0, t1, t0
    sw t0, 48(sp)
    lw t0, 48(sp)
    bnez t0, .L7049
    j .L7058
.L7049:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 52(sp)
    lw t1, 56(sp)
    sub t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L7067
.L7058:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 64(sp)
    lw t1, 68(sp)
    sub t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L7067
.L7067:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 100
    mul t0, t0, t1
    sw t0, 80(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    div t0, t0, t1
    sw t0, 88(sp)
    li t0, 100
    lw t1, 88(sp)
    sub t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    bnez t0, .L7098
    j .L7099
.L7098:
    li a0, 0
    j .L22
.L7099:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw a0, 104(sp)
    j .L22
.L7102:
    li a0, 0
    j .L22
.L22:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl performHashTableTest
    .type performHashTableTest, @function
performHashTableTest:
    li t0, -31056
    add sp, sp, t0
    li t0, 31052
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 31048
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 31056
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 2012(sp)
    addi t0, sp, 2016
    sw t0, 2020(sp)
    addi t0, sp, 2024
    li t3, 4024
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 4028
    add t0, sp, t1
    li t3, 6028
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6032
    add t0, sp, t1
    li t3, 6036
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 6040
    add t0, sp, t1
    li t3, 8040
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8044
    add t0, sp, t1
    li t3, 8048
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8052
    add t0, sp, t1
    li t3, 8056
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8060
    add t0, sp, t1
    li t3, 8064
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8068
    add t0, sp, t1
    li t3, 8072
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8076
    add t0, sp, t1
    li t3, 11276
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11280
    add t0, sp, t1
    li t3, 11284
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11288
    add t0, sp, t1
    li t3, 11320
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 11324
    add t0, sp, t1
    li t3, 14524
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 14528
    add t0, sp, t1
    li t3, 14532
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 14536
    add t0, sp, t1
    li t3, 17736
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17740
    add t0, sp, t1
    li t3, 17744
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17748
    add t0, sp, t1
    li t3, 17780
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17784
    add t0, sp, t1
    li t3, 20984
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20988
    add t0, sp, t1
    li t3, 20992
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 20996
    add t0, sp, t1
    li t3, 21396
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21400
    add t0, sp, t1
    li t3, 21404
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21408
    add t0, sp, t1
    li t3, 21808
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21812
    add t0, sp, t1
    li t3, 21816
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21820
    add t0, sp, t1
    li t3, 21824
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21828
    add t0, sp, t1
    li t3, 21832
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21836
    add t0, sp, t1
    li t3, 21840
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21844
    add t0, sp, t1
    li t3, 21848
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21852
    add t0, sp, t1
    li t3, 21856
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21860
    add t0, sp, t1
    li t3, 21864
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 21868
    add t0, sp, t1
    li t3, 23868
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 23872
    add t0, sp, t1
    li t3, 23876
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 23880
    add t0, sp, t1
    li t3, 25880
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 25884
    add t0, sp, t1
    li t3, 27884
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 27888
    add t0, sp, t1
    li t3, 27892
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 27896
    add t0, sp, t1
    li t3, 29896
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29900
    add t0, sp, t1
    li t3, 29904
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29908
    add t0, sp, t1
    li t3, 29912
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29916
    add t0, sp, t1
    li t3, 29920
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29924
    add t0, sp, t1
    li t3, 29928
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29932
    add t0, sp, t1
    li t3, 29936
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29940
    add t0, sp, t1
    li t3, 29944
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29948
    add t0, sp, t1
    li t3, 29952
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29956
    add t0, sp, t1
    li t3, 29960
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29964
    add t0, sp, t1
    li t3, 29968
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29972
    add t0, sp, t1
    li t3, 29976
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29980
    add t0, sp, t1
    li t3, 29984
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29988
    add t0, sp, t1
    li t3, 29992
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 29996
    add t0, sp, t1
    li t3, 30000
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 30004
    add t0, sp, t1
    li t3, 30008
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 30012
    add t0, sp, t1
    li t3, 30016
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 30020
    add t0, sp, t1
    li t3, 30024
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 30028
    add t0, sp, t1
    li t3, 30032
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li a0, 26011
    call printlnInt
    li t0, 0
    lw t1, 2020(sp)
    sw t0, 0(t1)
    j .L7110
.L7110:
    lw t0, 2020(sp)
    lw t0, 0(t0)
    li t3, 30036
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30036
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 500
    slt t0, t0, t1
    li t3, 30040
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30040
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7114
    j .L7115
.L7114:
    lw t0, 2020(sp)
    lw t0, 0(t0)
    li t3, 30044
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 4024
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30044
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30048
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 30048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 2020(sp)
    lw t0, 0(t0)
    li t3, 30052
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30052
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30056
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 2020(sp)
    sw t0, 0(t1)
    j .L7110
.L7115:
    lw a0, 2012(sp)
    li t3, 4024
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2000
    call memcpy
    li t0, 0
    li t3, 6036
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7124
.L7124:
    li t3, 6036
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30060
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 500
    slt t0, t0, t1
    li t3, 30064
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30064
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7128
    j .L7129
.L7128:
    li t3, 6036
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30068
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8040
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30068
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30072
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 30072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 6036
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30076
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30076
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30080
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30080
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 6036
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7124
.L7129:
    li t3, 6028
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 8040
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2000
    call memcpy
    li t0, 100
    li t3, 8048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8056
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8064
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 11284
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7149
.L7149:
    li t3, 11284
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30084
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30084
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 8
    slt t0, t0, t1
    li t3, 30088
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30088
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7153
    j .L7154
.L7153:
    li t3, 11284
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30092
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11320
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30092
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30096
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 30096
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 11284
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30100
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30100
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30104
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30104
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 11284
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7149
.L7154:
    li t0, 0
    li t3, 14532
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7159
.L7159:
    li t3, 14532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30108
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30108
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 30112
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30112
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7163
    j .L7164
.L7163:
    li t3, 14532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30116
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 14524
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30116
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 32
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30120
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30120
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 11320
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 32
    call memcpy
    li t3, 14532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30124
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30124
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30128
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30128
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 14532
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7159
.L7164:
    li t3, 11276
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 14524
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 3200
    call memcpy
    li t0, 0
    li t3, 17744
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7175
.L7175:
    li t3, 17744
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30132
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30132
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 8
    slt t0, t0, t1
    li t3, 30136
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30136
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7179
    j .L7180
.L7179:
    li t3, 17744
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30140
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 17780
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30140
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30144
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 30144
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 17744
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30148
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30148
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30152
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30152
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 17744
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7175
.L7180:
    li t0, 0
    li t3, 20992
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7185
.L7185:
    li t3, 20992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30156
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30156
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 30160
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30160
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7189
    j .L7190
.L7189:
    li t3, 20992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30164
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 20984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30164
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 32
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30168
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30168
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 17780
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 32
    call memcpy
    li t3, 20992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30172
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30172
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30176
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30176
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 20992
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7185
.L7190:
    li t3, 17736
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 20984
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 3200
    call memcpy
    li t0, 0
    li t3, 21404
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7199
.L7199:
    li t3, 21404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30180
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30180
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 30184
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30184
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7203
    j .L7204
.L7203:
    li t3, 21404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30188
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21808
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30188
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30192
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 30192
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 21404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30196
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30196
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30200
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30200
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21404
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7199
.L7204:
    li t3, 21396
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 21808
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    li t0, 100
    li t3, 21816
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 21824
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 21832
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7216
.L7216:
    j .L7220
.L7220:
    li t3, 21824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30204
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 30208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30204
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30208
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 30212
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 30216
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 30212
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7230
    j .L7239
.L7230:
    li t3, 21824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30220
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30220
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 400
    slt t0, t0, t1
    li t3, 30224
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30224
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 30216
    add t3, t3, sp
    sw t1, 0(t3)
    j .L7239
.L7239:
    li t3, 30216
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7243
    j .L7659
.L7243:
    li t3, 21824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30228
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30228
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 17
    mul t0, t0, t1
    li t3, 30232
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30232
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 23
    add t0, t0, t1
    li t3, 30236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30236
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2000
    rem t0, t0, t1
    li t3, 30240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30240
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30244
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30244
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21840
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 21824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30248
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30248
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 11
    mul t0, t0, t1
    li t3, 30252
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30252
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 7
    add t0, t0, t1
    li t3, 30256
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30256
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1000
    rem t0, t0, t1
    li t3, 30260
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30260
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30264
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30264
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21848
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30268
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30268
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    mul t0, t0, t1
    li t3, 30272
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30272
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30276
    add t3, t3, sp
    lw t1, 0(t3)
    div t0, t0, t1
    li t3, 30280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30280
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21856
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7306
.L7306:
    li t3, 21856
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30284
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30284
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 70
    slt t0, t1, t0
    li t3, 30288
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 30292
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 30288
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7314
    j .L7323
.L7314:
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30296
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30296
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 250
    slt t0, t0, t1
    li t3, 30300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30300
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 30292
    add t3, t3, sp
    sw t1, 0(t3)
    j .L7323
.L7323:
    li t3, 30292
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7327
    j .L7598
.L7327:
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30304
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21864
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30308
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30308
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2
    mul t0, t0, t1
    li t3, 30312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30312
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30316
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30320
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30320
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 23876
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7359
.L7359:
    li t3, 23876
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 500
    slt t0, t0, t1
    li t3, 30328
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30328
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7363
    j .L7364
.L7363:
    li t3, 23876
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 25880
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30332
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30336
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 30336
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 23876
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30340
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30344
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 23876
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7359
.L7364:
    li t3, 23868
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 25880
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2000
    call memcpy
    li t0, 0
    li t3, 27892
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7373
.L7373:
    li t3, 27892
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30348
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 500
    slt t0, t0, t1
    li t3, 30352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30352
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7377
    j .L7378
.L7377:
    li t3, 27892
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29896
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30356
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30360
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 30360
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 27892
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30364
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30368
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30368
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 27892
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7373
.L7378:
    li t3, 27884
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 29896
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2000
    call memcpy
    li t0, 0
    li t3, 29904
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7386
.L7386:
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30372
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21864
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30372
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30376
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 30380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30380
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7396
    j .L7469
.L7396:
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 23868
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30384
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30388
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30392
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 2012(sp)
    li t3, 30392
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30396
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30400
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30388
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 27884
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30404
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6028
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30412
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30416
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30420
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30408
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30424
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 2012(sp)
    li t3, 30424
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30428
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 30428
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30432
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6028
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30432
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30436
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 30436
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30440
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30440
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30444
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30444
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29904
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7386
.L7469:
    j .L7471
.L7471:
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30448
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30452
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 30456
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30456
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7481
    j .L7516
.L7481:
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30460
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 2012(sp)
    li t3, 30460
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30464
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, -1
    li t3, 30464
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 6028
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30468
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30472
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 30472
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30476
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30480
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30480
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29904
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7471
.L7516:
    li t0, 0
    li t3, 8056
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 29904
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7528
.L7528:
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21864
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30488
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30484
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30488
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 30492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30492
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7538
    j .L7597
.L7538:
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 23868
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30496
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30500
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30504
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30504
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, -1
    sub t0, t0, t1
    snez t0, t0
    li t3, 30508
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30508
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7555
    j .L7585
.L7555:
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30512
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 23868
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30516
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30520
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30524
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30528
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 27884
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30528
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30532
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30540
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 2012(sp)
    li t3, 6028
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 30512
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 30524
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 30536
    add t3, t3, sp
    lw a4, 0(t3)
    li t3, 8064
    add t3, t3, sp
    lw a5, 0(t3)
    li t3, 30540
    add t3, t3, sp
    lw a6, 0(t3)
    call insertLinearProbing
    li t3, 30544
    add t3, t3, sp
    sw a0, 0(t3)
    j .L7585
.L7585:
    li t3, 29904
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30548
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30552
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30552
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29904
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7528
.L7597:
    j .L7598
.L7598:
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30556
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21840
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21848
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30568
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 2012(sp)
    li t3, 6028
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 30556
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 30560
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 30564
    add t3, t3, sp
    lw a4, 0(t3)
    li t3, 8064
    add t3, t3, sp
    lw a5, 0(t3)
    li t3, 30568
    add t3, t3, sp
    lw a6, 0(t3)
    call insertLinearProbing
    li t3, 30572
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 30572
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29912
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29912
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30576
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30576
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    li t3, 30580
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30580
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7624
    j .L7647
.L7624:
    li t3, 21832
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30584
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30584
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30588
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30588
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21832
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30592
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30592
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30596
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30596
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8056
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7647
.L7647:
    li t3, 21824
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30600
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30600
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30604
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30604
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 21824
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7216
.L7659:
    li t0, 0
    li t3, 29920
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 29928
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7665
.L7665:
    j .L7669
.L7669:
    li t3, 29920
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30608
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 30612
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30608
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30612
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 30616
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 30620
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 30616
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7679
    j .L7688
.L7679:
    li t3, 29920
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30624
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30624
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 300
    slt t0, t0, t1
    li t3, 30628
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30628
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 30620
    add t3, t3, sp
    sw t1, 0(t3)
    j .L7688
.L7688:
    li t3, 30620
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7692
    j .L7975
.L7692:
    li t3, 29920
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30632
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30632
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 13
    mul t0, t0, t1
    li t3, 30636
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30636
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 31
    add t0, t0, t1
    li t3, 30640
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30640
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1500
    rem t0, t0, t1
    li t3, 30644
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30644
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30648
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30648
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29936
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29920
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30652
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30652
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 19
    mul t0, t0, t1
    li t3, 30656
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30656
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 5
    add t0, t0, t1
    li t3, 30660
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30660
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 800
    rem t0, t0, t1
    li t3, 30664
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30664
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30668
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30668
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29944
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29936
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30672
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21816
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30676
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30672
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30676
    add t3, t3, sp
    lw t1, 0(t3)
    rem t0, t0, t1
    li t3, 30680
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30680
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29952
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 29960
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 29968
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7750
.L7750:
    j .L7754
.L7754:
    li t3, 29968
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30684
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30688
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30688
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30692
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30692
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30696
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30684
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30696
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 30700
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 30704
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 30700
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7770
    j .L7779
.L7770:
    li t3, 29968
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30708
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30708
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 8
    slt t0, t0, t1
    li t3, 30712
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30712
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 30704
    add t3, t3, sp
    sw t1, 0(t3)
    j .L7779
.L7779:
    li t3, 30704
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7783
    j .L7845
.L7783:
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30716
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11276
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30716
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 32
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30720
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29968
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30724
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30720
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30724
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30728
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30728
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30732
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29936
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30736
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30732
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30736
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    seqz t0, t0
    li t3, 30740
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30740
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7807
    j .L7833
.L7807:
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30744
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 17736
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30744
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 32
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30748
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29968
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30752
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30748
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30752
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30756
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29944
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30760
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30760
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30756
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 1
    li t3, 29960
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7845
.L7833:
    li t3, 29968
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30764
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30764
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30768
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30768
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29968
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7750
.L7845:
    j .L7851
.L7851:
    li t3, 29960
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30772
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30772
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 30776
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 30780
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 30776
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7857
    j .L7872
.L7857:
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30784
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30784
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30788
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30788
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30792
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30792
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 8
    slt t0, t0, t1
    li t3, 30796
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30796
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 30780
    add t3, t3, sp
    sw t1, 0(t3)
    j .L7872
.L7872:
    li t3, 30780
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7876
    j .L7963
.L7876:
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30800
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11276
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30800
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 32
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30804
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30808
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30808
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30812
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30812
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30816
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30804
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30816
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30820
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29936
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30824
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30824
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30820
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30828
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 17736
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30828
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 32
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30832
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30836
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30836
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30840
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30840
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30844
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30832
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30844
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30848
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29944
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30852
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30852
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30848
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30856
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30856
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30860
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 29952
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30864
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30864
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 30868
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30868
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30872
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30872
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30876
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30876
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30860
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 29928
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30880
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30880
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30884
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30884
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29928
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7963
.L7963:
    li t3, 29920
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30888
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30888
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30892
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30892
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29920
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7665
.L7975:
    li t0, 0
    li t3, 29976
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 29984
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 29992
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7983
.L7983:
    li t3, 29992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30896
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30896
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 30900
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30900
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L7991
    j .L8092
.L7991:
    li t3, 29992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30904
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30904
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 23
    mul t0, t0, t1
    li t3, 30908
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30908
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 17
    add t0, t0, t1
    li t3, 30912
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30912
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1000
    rem t0, t0, t1
    li t3, 30916
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30916
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30920
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30920
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30000
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30924
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30000
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30928
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 2012(sp)
    li t3, 30924
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 30928
    add t3, t3, sp
    lw a2, 0(t3)
    call lookupLinearProbing
    li t3, 30932
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 30932
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30008
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 30008
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30936
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30936
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 30940
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30940
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L8033
    j .L8045
.L8033:
    li t3, 29976
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30944
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30944
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30948
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30948
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29976
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L8045
.L8045:
    li t3, 21816
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30952
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30000
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30956
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 11276
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 30952
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 30956
    add t3, t3, sp
    lw a3, 0(t3)
    call lookupChaining
    li t3, 30960
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 30960
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30016
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 30016
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30964
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30964
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 30968
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30968
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L8068
    j .L8080
.L8068:
    li t3, 29984
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30972
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30972
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30976
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30976
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29984
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L8080
.L8080:
    li t3, 29992
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30980
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30980
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 30984
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30984
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 29992
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L7983
.L8092:
    li t3, 8056
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30988
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30988
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    mul t0, t0, t1
    li t3, 30992
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 30996
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 30992
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30996
    add t3, t3, sp
    lw t1, 0(t3)
    div t0, t0, t1
    li t3, 31000
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31000
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30024
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 21816
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31004
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 21396
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 31004
    add t3, t3, sp
    lw a1, 0(t3)
    call calculateAverageChainLength
    li t3, 31008
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 31008
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 30032
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 21832
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31012
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31012
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 29928
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31016
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31016
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 8064
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31020
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31020
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 29976
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31024
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31024
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 29984
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31028
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31028
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 30024
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31032
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31032
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 30032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31036
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31036
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li t3, 8072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 31040
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 31040
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    li a0, 26012
    call printlnInt
    li t3, 31044
    add t3, t3, sp
    lw a0, 0(t3)
    j .L23
.L23:
    li t0, 31052
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 31048
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 31056
    add sp, sp, t0
    jr ra
    .globl insertLinearProbing
    .type insertLinearProbing, @function
insertLinearProbing:
    addi sp, sp, -224
    sw ra, 220(sp)
    sw s0, 216(sp)
    addi s0, sp, 224
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)
    addi t0, sp, 28
    sw t0, 28(sp)
    addi t0, sp, 32
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 40(sp)
    addi t0, sp, 44
    sw t0, 48(sp)
    addi t0, sp, 52
    sw t0, 56(sp)
    addi t0, sp, 60
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    addi t0, sp, 72
    sw t0, 76(sp)
    addi t0, sp, 80
    sw t0, 84(sp)
    lw t0, 0(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 88(sp)
    lw t1, 92(sp)
    rem t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 84(sp)
    sw t0, 0(t1)
    j .L8163
.L8163:
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 100(sp)
    lw t1, 104(sp)
    slt t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    bnez t0, .L8173
    j .L8295
.L8173:
    lw t0, 76(sp)
    lw t0, 0(t0)
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
    lw t0, 120(sp)
    li t1, -1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 124(sp)
    lw t0, 124(sp)
    bnez t0, .L8190
    j .L8218
.L8190:
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 0(sp)
    lw t1, 128(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 132(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 4(sp)
    lw t1, 140(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 144(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t1, 144(sp)
    sw t0, 0(t1)
    li a0, 1
    j .L24
.L8218:
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 0(sp)
    lw t1, 152(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 156(sp)
    lw t0, 156(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 160(sp)
    lw t1, 164(sp)
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 168(sp)
    lw t0, 168(sp)
    bnez t0, .L8235
    j .L8250
.L8235:
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 4(sp)
    lw t1, 172(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 176(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t1, 176(sp)
    sw t0, 0(t1)
    li a0, 1
    j .L24
.L8250:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 184(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 188(sp)
    lw t0, 188(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 192(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 196(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 196(sp)
    lw t1, 200(sp)
    rem t0, t0, t1
    sw t0, 204(sp)
    lw t0, 204(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 208(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    lw t1, 84(sp)
    sw t0, 0(t1)
    j .L8293
.L8293:
    j .L8294
.L8294:
    j .L8163
.L8295:
    li a0, 0
    j .L24
.L24:
    lw ra, 220(sp)
    lw s0, 216(sp)
    addi sp, sp, 224
    jr ra
    .globl lookupLinearProbing
    .type lookupLinearProbing, @function
lookupLinearProbing:
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
    addi t0, sp, 32
    sw t0, 36(sp)
    addi t0, sp, 40
    sw t0, 44(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    rem t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L8312
.L8312:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    slt t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L8322
    j .L8398
.L8322:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 0(sp)
    lw t1, 72(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 88(sp)
    lw t0, 88(sp)
    bnez t0, .L8340
    j .L8346
.L8340:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw a0, 92(sp)
    j .L25
.L8346:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 0(sp)
    lw t1, 96(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, -1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 108(sp)
    lw t0, 108(sp)
    bnez t0, .L8362
    j .L8366
.L8362:
    li a0, -1
    j .L25
.L8366:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 116(sp)
    lw t1, 120(sp)
    rem t0, t0, t1
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 128(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L8396
.L8396:
    j .L8397
.L8397:
    j .L8312
.L8398:
    li a0, -1
    j .L25
.L25:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl lookupChaining
    .type lookupChaining, @function
lookupChaining:
    addi sp, sp, -160
    sw ra, 156(sp)
    sw s0, 152(sp)
    addi s0, sp, 160
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    addi t0, sp, 16
    sw t0, 16(sp)
    addi t0, sp, 20
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
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    rem t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L8417
.L8417:
    j .L8421
.L8421:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 4(sp)
    lw t1, 72(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 68(sp)
    lw t1, 80(sp)
    slt t0, t0, t1
    sw t0, 84(sp)
    li t1, 0
    sw t1, 88(sp)
    lw t0, 84(sp)
    bnez t0, .L8437
    j .L8446
.L8437:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 8
    slt t0, t0, t1
    sw t0, 96(sp)
    lw t1, 96(sp)
    sw t1, 88(sp)
    j .L8446
.L8446:
    lw t0, 88(sp)
    bnez t0, .L8450
    j .L8492
.L8450:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 0(sp)
    lw t1, 100(sp)
    li t2, 32
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 104(sp)
    lw t1, 108(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 116(sp)
    lw t1, 120(sp)
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 124(sp)
    lw t0, 124(sp)
    bnez t0, .L8474
    j .L8480
.L8474:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw a0, 128(sp)
    j .L26
.L8480:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 132(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L8417
.L8492:
    li a0, -1
    j .L26
.L26:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl calculateAverageChainLength
    .type calculateAverageChainLength, @function
calculateAverageChainLength:
    addi sp, sp, -144
    sw ra, 140(sp)
    sw s0, 136(sp)
    addi s0, sp, 144
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
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L8503
.L8503:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 44(sp)
    lw t1, 48(sp)
    slt t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L8513
    j .L8572
.L8513:
    lw t0, 40(sp)
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
    slt t0, t1, t0
    sw t0, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L8529
    j .L8560
.L8529:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 0(sp)
    lw t1, 76(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 72(sp)
    lw t1, 84(sp)
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L8560
.L8560:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L8503
.L8572:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 112(sp)
    lw t0, 112(sp)
    bnez t0, .L8583
    j .L8592
.L8583:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 116(sp)
    lw t1, 120(sp)
    div t0, t0, t1
    sw t0, 124(sp)
    lw a0, 124(sp)
    j .L27
.L8592:
    li a0, 0
    j .L27
.L8593:
    li a0, 0
    j .L27
.L27:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
