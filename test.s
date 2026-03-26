    .text
    .globl main
    .type main, @function
main:
    addi sp, sp, -16
    sw ra, 12(sp)
    sw s0, 8(sp)
    addi s0, sp, 16
    li a0, 3000
    call printlnInt
    call performMathematicalSeries
    call performNumberTheoryAlgorithms
    call performLinearAlgebraOperations
    call performCombinatorialAlgorithms
    call performCryptographicOperations
    li a0, 3999
    call printlnInt
    li a0, 0
    call __builtin_exit
    li a0, 0
    j .L1
.L1:
    lw ra, 12(sp)
    lw s0, 8(sp)
    addi sp, sp, 16
    jr ra
    .globl performMathematicalSeries
    .type performMathematicalSeries, @function
performMathematicalSeries:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
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
    li a0, 3001
    call printlnInt
    li a0, 1000
    call calculatePiApproximation
    sw a0, 40(sp)
    lw t0, 40(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw a0, 44(sp)
    call printlnInt
    li a0, 50
    call calculateFibonacciSum
    sw a0, 48(sp)
    lw t0, 48(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw a0, 52(sp)
    call printlnInt
    li a0, 20
    call calculateFactorialSeries
    sw a0, 56(sp)
    lw t0, 56(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw a0, 60(sp)
    call printlnInt
    li a0, 10000
    call calculateHarmonicSeries
    sw a0, 64(sp)
    lw t0, 64(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw a0, 68(sp)
    call printlnInt
    li a0, 100
    li a1, 3
    call calculateGeometricSeries
    sw a0, 72(sp)
    lw t0, 72(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw a0, 76(sp)
    call printlnInt
    li a0, 3002
    call printlnInt
    lw a0, 80(sp)
    j .L2
.L2:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl calculatePiApproximation
    .type calculatePiApproximation, @function
calculatePiApproximation:
    addi sp, sp, -144
    sw ra, 140(sp)
    sw s0, 136(sp)
    addi s0, sp, 144
    sw a0, 0(sp)
    addi t0, sp, 4
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 32(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L211
.L211:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 52(sp)
    lw t1, 56(sp)
    slt t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L221
    j .L266
.L221:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 10000
    mul t0, t0, t1
    sw t0, 68(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 68(sp)
    lw t1, 72(sp)
    div t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 80(sp)
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    li t0, 0
    lw t1, 92(sp)
    sub t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L211
.L266:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 4
    mul t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    li t1, 100000
    rem t0, t0, t1
    sw t0, 124(sp)
    lw a0, 124(sp)
    j .L3
.L3:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl calculateFibonacciSum
    .type calculateFibonacciSum, @function
calculateFibonacciSum:
    addi sp, sp, -144
    sw ra, 140(sp)
    sw s0, 136(sp)
    addi s0, sp, 144
    sw a0, 0(sp)
    addi t0, sp, 4
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 32(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L300
.L300:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 52(sp)
    lw t1, 56(sp)
    slt t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L310
    j .L365
.L310:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t1, 64(sp)
    add t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 88(sp)
    lw t1, 92(sp)
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L300
.L365:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 120(sp)
    lw a0, 120(sp)
    j .L4
.L4:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl calculateFactorialSeries
    .type calculateFactorialSeries, @function
calculateFactorialSeries:
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
    addi t0, sp, 28
    sw t0, 32(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L387
.L387:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L397
    j .L440
.L397:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    mul t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 64(sp)
    lw t1, 68(sp)
    add t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 80(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L387
.L440:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 92(sp)
    lw a0, 92(sp)
    j .L5
.L5:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl calculateHarmonicSeries
    .type calculateHarmonicSeries, @function
calculateHarmonicSeries:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    addi s0, sp, 80
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
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L460
.L460:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 28(sp)
    lw t1, 32(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 36(sp)
    lw t0, 36(sp)
    bnez t0, .L470
    j .L489
.L470:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    li t0, 10000
    lw t1, 40(sp)
    div t0, t0, t1
    sw t0, 44(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t1, 44(sp)
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L460
.L489:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 68(sp)
    lw a0, 68(sp)
    j .L6
.L6:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl calculateGeometricSeries
    .type calculateGeometricSeries, @function
calculateGeometricSeries:
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
    addi t0, sp, 40
    sw t0, 44(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 28(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L512
.L512:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    slt t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L522
    j .L565
.L522:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    add t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 76(sp)
    lw t1, 80(sp)
    mul t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L512
.L565:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 104(sp)
    lw a0, 104(sp)
    j .L7
.L7:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl performNumberTheoryAlgorithms
    .type performNumberTheoryAlgorithms, @function
performNumberTheoryAlgorithms:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
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
    li a0, 3003
    call printlnInt
    li a0, 2000
    call sieveOfEratosthenes
    sw a0, 40(sp)
    lw t0, 40(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw a0, 44(sp)
    call printlnInt
    li a0, 100
    call performGCDOperations
    sw a0, 48(sp)
    lw t0, 48(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw a0, 52(sp)
    call printlnInt
    call performModularExponentiation
    sw a0, 56(sp)
    lw t0, 56(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw a0, 60(sp)
    call printlnInt
    li a0, 100
    call calculateTotientSum
    sw a0, 64(sp)
    lw t0, 64(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw a0, 68(sp)
    call printlnInt
    li a0, 1000
    call findPerfectNumbers
    sw a0, 72(sp)
    lw t0, 72(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw a0, 76(sp)
    call printlnInt
    li a0, 3004
    call printlnInt
    lw a0, 80(sp)
    j .L8
.L8:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl sieveOfEratosthenes
    .type sieveOfEratosthenes, @function
sieveOfEratosthenes:
    li t0, -16256
    add sp, sp, t0
    li t0, 16252
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 16248
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 16256
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    li t3, 8012
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8016
    add t0, sp, t1
    li t3, 8020
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8024
    add t0, sp, t1
    li t3, 16024
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16028
    add t0, sp, t1
    li t3, 16032
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16036
    add t0, sp, t1
    li t3, 16040
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16044
    add t0, sp, t1
    li t3, 16048
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li t0, 0
    li t3, 8020
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L627
.L627:
    li t3, 8020
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16052
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16052
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2000
    slt t0, t0, t1
    li t3, 16056
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16056
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L631
    j .L632
.L631:
    li t3, 8020
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16024
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16060
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 16064
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 16064
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8020
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16068
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16068
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 16072
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16072
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8020
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L627
.L632:
    li t3, 8012
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 16024
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 8000
    call memcpy
    li t0, 0
    li t3, 16032
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 2
    li t3, 16040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L642
.L642:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16076
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 16080
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16076
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16080
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 16084
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16084
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L652
    j .L668
.L652:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16088
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16088
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 16092
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 16092
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16096
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16096
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 16100
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16100
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L642
.L668:
    li t0, 2
    li t3, 16040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L675
.L675:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16104
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16108
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16104
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16108
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 16112
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 16116
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16112
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16116
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 16120
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16120
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L691
    j .L753
.L691:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16124
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16124
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 16128
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16128
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16132
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16132
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    li t3, 16136
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16136
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L705
    j .L746
.L705:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16140
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16144
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16140
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16144
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 16148
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16148
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L717
.L717:
    li t3, 16048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16152
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 16156
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16152
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16156
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 16160
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16160
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L727
    j .L745
.L727:
    li t3, 16048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16164
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16164
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 16168
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 16168
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16172
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16176
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16176
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16172
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 16180
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16180
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L717
.L745:
    j .L746
.L746:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16184
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16184
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 16188
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16188
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L675
.L753:
    li t0, 2
    li t3, 16040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L760
.L760:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16192
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 16196
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16192
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16196
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 16200
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16200
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L770
    j .L798
.L770:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16204
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 8012
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16204
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 16208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16208
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16212
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16212
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    li t3, 16216
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16216
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L784
    j .L791
.L784:
    li t3, 16032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16220
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16220
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 16224
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16224
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16032
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L791
.L791:
    li t3, 16040
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16228
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16228
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 16232
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16232
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16040
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L760
.L798:
    li t3, 16032
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 16236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16236
    add t3, t3, sp
    lw a0, 0(t3)
    j .L9
.L9:
    li t0, 16252
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 16248
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 16256
    add sp, sp, t0
    jr ra
    .globl performGCDOperations
    .type performGCDOperations, @function
performGCDOperations:
    addi sp, sp, -176
    sw ra, 172(sp)
    sw s0, 168(sp)
    addi s0, sp, 176
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L810
.L810:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L820
    j .L906
.L820:
    li t0, 1
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L824
.L824:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L834
    j .L899
.L834:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 60(sp)
    li t1, 13
    mul t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 7
    add t0, t0, t1
    sw t0, 68(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    li t1, 17
    mul t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 11
    add t0, t0, t1
    sw t0, 80(sp)
    lw a0, 68(sp)
    lw a1, 80(sp)
    call euclideanGCD
    sw a0, 84(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 84(sp)
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 19
    mul t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 23
    mul t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 5
    add t0, t0, t1
    sw t0, 116(sp)
    lw a0, 104(sp)
    lw a1, 116(sp)
    call binaryGCD
    sw a0, 120(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t1, 120(sp)
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 132(sp)
    li t1, 10
    add t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L824
.L899:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 140(sp)
    li t1, 10
    add t0, t0, t1
    sw t0, 144(sp)
    lw t0, 144(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L810
.L906:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 148(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 152(sp)
    lw a0, 152(sp)
    j .L10
.L10:
    lw ra, 172(sp)
    lw s0, 168(sp)
    addi sp, sp, 176
    jr ra
    .globl euclideanGCD
    .type euclideanGCD, @function
euclideanGCD:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
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
    addi t0, sp, 40
    sw t0, 44(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L931
.L931:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L939
    j .L964
.L939:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 68(sp)
    lw t1, 72(sp)
    rem t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L931
.L964:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw a0, 84(sp)
    j .L11
.L11:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl binaryGCD
    .type binaryGCD, @function
binaryGCD:
    addi sp, sp, -240
    sw ra, 236(sp)
    sw s0, 232(sp)
    addi s0, sp, 240
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
    addi t0, sp, 40
    sw t0, 44(sp)
    addi t0, sp, 48
    sw t0, 52(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L992
    j .L998
.L992:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw a0, 72(sp)
    j .L12
.L998:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 80(sp)
    lw t0, 80(sp)
    bnez t0, .L1009
    j .L1015
.L1009:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw a0, 84(sp)
    j .L12
.L1015:
    j .L1017
.L1017:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 88(sp)
    lw t1, 92(sp)
    or t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    and t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 104(sp)
    lw t0, 104(sp)
    bnez t0, .L1037
    j .L1056
.L1037:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 1
    sra t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 1
    sra t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L1017
.L1056:
    j .L1058
.L1058:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 132(sp)
    li t1, 1
    and t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 140(sp)
    lw t0, 140(sp)
    bnez t0, .L1071
    j .L1078
.L1071:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    li t1, 1
    sra t0, t0, t1
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L1058
.L1078:
    j .L1080
.L1080:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 152(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 156(sp)
    lw t0, 156(sp)
    bnez t0, .L1088
    j .L1155
.L1088:
    j .L1090
.L1090:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 160(sp)
    li t1, 1
    and t0, t0, t1
    sw t0, 164(sp)
    lw t0, 164(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 168(sp)
    lw t0, 168(sp)
    bnez t0, .L1103
    j .L1110
.L1103:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 172(sp)
    li t1, 1
    sra t0, t0, t1
    sw t0, 176(sp)
    lw t0, 176(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L1090
.L1110:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 180(sp)
    lw t1, 184(sp)
    slt t0, t1, t0
    sw t0, 188(sp)
    lw t0, 188(sp)
    bnez t0, .L1122
    j .L1141
.L1122:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 192(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 196(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L1141
.L1141:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 204(sp)
    lw t1, 208(sp)
    sub t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L1080
.L1155:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 220(sp)
    lw t0, 216(sp)
    lw t1, 220(sp)
    sll t0, t0, t1
    sw t0, 224(sp)
    lw a0, 224(sp)
    j .L12
.L12:
    lw ra, 236(sp)
    lw s0, 232(sp)
    addi sp, sp, 240
    jr ra
    .globl performModularExponentiation
    .type performModularExponentiation, @function
performModularExponentiation:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
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
    li t0, 0
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 2
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L1178
.L1178:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 40(sp)
    li t1, 10
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L1186
    j .L1243
.L1186:
    li t0, 1
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L1190
.L1190:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, 20
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L1198
    j .L1236
.L1198:
    li t0, 97
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw a0, 56(sp)
    lw a1, 60(sp)
    lw a2, 64(sp)
    call modularPower
    sw a0, 68(sp)
    lw t0, 68(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L1190
.L1236:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L1178
.L1243:
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw a0, 104(sp)
    j .L13
.L13:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl modularPower
    .type modularPower, @function
modularPower:
    addi sp, sp, -160
    sw ra, 156(sp)
    sw s0, 152(sp)
    addi s0, sp, 160
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
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
    lw t0, 0(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    rem t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    j .L1269
.L1269:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 80(sp)
    lw t0, 80(sp)
    bnez t0, .L1277
    j .L1339
.L1277:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 2
    rem t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 92(sp)
    lw t0, 92(sp)
    bnez t0, .L1291
    j .L1312
.L1291:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 96(sp)
    lw t1, 100(sp)
    mul t0, t0, t1
    sw t0, 104(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 104(sp)
    lw t1, 108(sp)
    rem t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L1312
.L1312:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 1
    sra t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 124(sp)
    lw t1, 128(sp)
    mul t0, t0, t1
    sw t0, 132(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 132(sp)
    lw t1, 136(sp)
    rem t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    j .L1269
.L1339:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw a0, 144(sp)
    j .L14
.L14:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl calculateTotientSum
    .type calculateTotientSum, @function
calculateTotientSum:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    addi s0, sp, 80
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
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1351
.L1351:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 28(sp)
    lw t1, 32(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 36(sp)
    lw t0, 36(sp)
    bnez t0, .L1361
    j .L1379
.L1361:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw a0, 40(sp)
    call eulerTotient
    sw a0, 44(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t1, 44(sp)
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1351
.L1379:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 68(sp)
    lw a0, 68(sp)
    j .L15
.L15:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl eulerTotient
    .type eulerTotient, @function
eulerTotient:
    addi sp, sp, -224
    sw ra, 220(sp)
    sw s0, 216(sp)
    addi s0, sp, 224
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 36(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 2
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 44(sp)
    li t1, 2
    rem t0, t0, t1
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L1418
    j .L1452
.L1418:
    j .L1420
.L1420:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 2
    rem t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L1432
    j .L1439
.L1432:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 68(sp)
    li t1, 2
    div t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1420
.L1439:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 2
    div t0, t0, t1
    sw t0, 80(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 80(sp)
    sub t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    j .L1452
.L1452:
    li t0, 3
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L1459
.L1459:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 92(sp)
    lw t1, 96(sp)
    mul t0, t0, t1
    sw t0, 100(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 100(sp)
    lw t1, 104(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 108(sp)
    lw t0, 108(sp)
    bnez t0, .L1475
    j .L1538
.L1475:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 112(sp)
    lw t1, 116(sp)
    rem t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 124(sp)
    lw t0, 124(sp)
    bnez t0, .L1491
    j .L1531
.L1491:
    j .L1493
.L1493:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 128(sp)
    lw t1, 132(sp)
    rem t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 140(sp)
    lw t0, 140(sp)
    bnez t0, .L1507
    j .L1516
.L1507:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t1, 144(sp)
    div t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1493
.L1516:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 156(sp)
    lw t1, 160(sp)
    div t0, t0, t1
    sw t0, 164(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    lw t1, 164(sp)
    sub t0, t0, t1
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    j .L1531
.L1531:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 176(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L1459
.L1538:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 184(sp)
    li t1, 1
    slt t0, t1, t0
    sw t0, 188(sp)
    lw t0, 188(sp)
    bnez t0, .L1549
    j .L1564
.L1549:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 192(sp)
    lw t1, 196(sp)
    div t0, t0, t1
    sw t0, 200(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 204(sp)
    lw t1, 200(sp)
    sub t0, t0, t1
    sw t0, 208(sp)
    lw t0, 208(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    j .L1564
.L1564:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw a0, 212(sp)
    j .L16
.L16:
    lw ra, 220(sp)
    lw s0, 216(sp)
    addi sp, sp, 224
    jr ra
    .globl findPerfectNumbers
    .type findPerfectNumbers, @function
findPerfectNumbers:
    addi sp, sp, -80
    sw ra, 76(sp)
    sw s0, 72(sp)
    addi s0, sp, 80
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
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 6
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1576
.L1576:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 28(sp)
    lw t1, 32(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 36(sp)
    lw t0, 36(sp)
    bnez t0, .L1586
    j .L1613
.L1586:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw a0, 40(sp)
    call isPerfectNumber
    sw a0, 44(sp)
    lw t0, 44(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 48(sp)
    lw t0, 48(sp)
    bnez t0, .L1599
    j .L1606
.L1599:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 52(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    j .L1606
.L1606:
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
    j .L1576
.L1613:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw a0, 68(sp)
    j .L17
.L17:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl isPerfectNumber
    .type isPerfectNumber, @function
isPerfectNumber:
    addi sp, sp, -160
    sw ra, 156(sp)
    sw s0, 152(sp)
    addi s0, sp, 160
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
    li t0, 1
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 2
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1625
.L1625:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 28(sp)
    lw t1, 32(sp)
    mul t0, t0, t1
    sw t0, 36(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L1641
    j .L1706
.L1641:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    rem t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L1657
    j .L1699
.L1657:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t1, 64(sp)
    add t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    div t0, t0, t1
    sw t0, 88(sp)
    lw t0, 76(sp)
    lw t1, 88(sp)
    sub t0, t0, t1
    snez t0, t0
    sw t0, 92(sp)
    lw t0, 92(sp)
    bnez t0, .L1683
    j .L1698
.L1683:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 96(sp)
    lw t1, 100(sp)
    div t0, t0, t1
    sw t0, 104(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 104(sp)
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    j .L1698
.L1698:
    j .L1699
.L1699:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 120(sp)
    lw t0, 120(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1625
.L1706:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 124(sp)
    lw t1, 128(sp)
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 132(sp)
    lw t0, 132(sp)
    sw t0, 136(sp)
    lw a0, 136(sp)
    j .L18
.L18:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl performLinearAlgebraOperations
    .type performLinearAlgebraOperations, @function
performLinearAlgebraOperations:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)
    addi s0, sp, 64
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    li a0, 3005
    call printlnInt
    call performMatrixCalculations
    sw a0, 24(sp)
    lw t0, 24(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw a0, 28(sp)
    call printlnInt
    call performVectorCalculations
    sw a0, 32(sp)
    lw t0, 32(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw a0, 36(sp)
    call printlnInt
    call solveLinearSystem
    sw a0, 40(sp)
    lw t0, 40(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw a0, 44(sp)
    call printlnInt
    li a0, 3006
    call printlnInt
    lw a0, 48(sp)
    j .L19
.L19:
    lw ra, 60(sp)
    lw s0, 56(sp)
    addi sp, sp, 64
    jr ra
    .globl performMatrixCalculations
    .type performMatrixCalculations, @function
performMatrixCalculations:
    li t0, -15440
    add sp, sp, t0
    li t0, 15436
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 15432
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 15440
    add s0, sp, t0
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    li t3, 2508
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2512
    add t0, sp, t1
    li t3, 2516
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2520
    add t0, sp, t1
    li t3, 5020
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 5024
    add t0, sp, t1
    li t3, 7524
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 7528
    add t0, sp, t1
    li t3, 7532
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 7536
    add t0, sp, t1
    li t3, 10036
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 10040
    add t0, sp, t1
    li t3, 12540
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 12544
    add t0, sp, t1
    li t3, 12548
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 12552
    add t0, sp, t1
    li t3, 15052
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 15056
    add t0, sp, t1
    li t3, 15060
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 15064
    add t0, sp, t1
    li t3, 15128
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 15132
    add t0, sp, t1
    li t3, 15136
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 15140
    add t0, sp, t1
    li t3, 15204
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 15208
    add t0, sp, t1
    li t3, 15212
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 15216
    add t0, sp, t1
    li t3, 15280
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 25
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 0
    li t3, 2516
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1765
.L1765:
    li t3, 2516
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15284
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15284
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 625
    slt t0, t0, t1
    li t3, 15288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15288
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1769
    j .L1770
.L1769:
    li t3, 2516
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 5020
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15292
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 15296
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 15296
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 2516
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15300
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 15304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15304
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2516
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1765
.L1770:
    li t3, 2508
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 5020
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2500
    call memcpy
    li t0, 0
    li t3, 7532
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1779
.L1779:
    li t3, 7532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15308
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15308
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 625
    slt t0, t0, t1
    li t3, 15312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15312
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1783
    j .L1784
.L1783:
    li t3, 7532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 10036
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15316
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 15320
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 15320
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 7532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15324
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 15328
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15328
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 7532
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1779
.L1784:
    li t3, 7524
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 10036
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2500
    call memcpy
    li t0, 0
    li t3, 12548
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1793
.L1793:
    li t3, 12548
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15332
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 625
    slt t0, t0, t1
    li t3, 15336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15336
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1797
    j .L1798
.L1797:
    li t3, 12548
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15052
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15340
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 15344
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 15344
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 12548
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15348
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 15352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15352
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 12548
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1793
.L1798:
    li t3, 12540
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 15052
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 2500
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 15356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2508
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 15356
    add t3, t3, sp
    lw a1, 0(t3)
    call initializeMatrixA
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 15360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 7524
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 15360
    add t3, t3, sp
    lw a1, 0(t3)
    call initializeMatrixB
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 15364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2508
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 7524
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 12540
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 15364
    add t3, t3, sp
    lw a3, 0(t3)
    call multiplyMatrices
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 15368
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12540
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 15368
    add t3, t3, sp
    lw a1, 0(t3)
    call calculateMatrixTrace
    li t3, 15372
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 15372
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15060
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 15136
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1838
.L1838:
    li t3, 15136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15376
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 16
    slt t0, t0, t1
    li t3, 15380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15380
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L1842
    j .L1843
.L1842:
    li t3, 15136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15204
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15384
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 15388
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 15388
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 15136
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15392
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15392
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 15396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15136
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L1838
.L1843:
    li t3, 15128
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 15204
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 64
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 15400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 12540
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 15128
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 15400
    add t3, t3, sp
    lw a2, 0(t3)
    li a3, 4
    call extractSubmatrix
    li t3, 15280
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 15128
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 64
    call memcpy
    li t3, 15280
    add t3, t3, sp
    lw a0, 0(t3)
    call calculateDeterminant4x4
    li t3, 15404
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 15404
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15212
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 15060
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15212
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 15412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15408
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 15412
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 15416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15416
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 15420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 15420
    add t3, t3, sp
    lw a0, 0(t3)
    j .L20
.L20:
    li t0, 15436
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 15432
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 15440
    add sp, sp, t0
    jr ra
    .globl initializeMatrixA
    .type initializeMatrixA, @function
initializeMatrixA:
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1895
.L1895:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L1905
    j .L1973
.L1905:
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L1909
.L1909:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    slt t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L1919
    j .L1966
.L1919:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    mul t0, t0, t1
    sw t0, 68(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 68(sp)
    lw t1, 72(sp)
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 0(sp)
    lw t1, 76(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 84(sp)
    lw t1, 88(sp)
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 10
    rem t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L1909
.L1966:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1895
.L1973:
    lw a0, 120(sp)
    j .L21
.L21:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl initializeMatrixB
    .type initializeMatrixB, @function
initializeMatrixB:
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1980
.L1980:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L1990
    j .L2058
.L1990:
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L1994
.L1994:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    slt t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L2004
    j .L2051
.L2004:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    mul t0, t0, t1
    sw t0, 68(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 68(sp)
    lw t1, 72(sp)
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 0(sp)
    lw t1, 76(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 84(sp)
    lw t1, 88(sp)
    mul t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 10
    rem t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L1994
.L2051:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1980
.L2058:
    lw a0, 120(sp)
    j .L22
.L22:
    lw ra, 140(sp)
    lw s0, 136(sp)
    addi sp, sp, 144
    jr ra
    .globl multiplyMatrices
    .type multiplyMatrices, @function
multiplyMatrices:
    addi sp, sp, -528
    sw ra, 524(sp)
    sw s0, 520(sp)
    addi s0, sp, 528
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
    addi t0, sp, 100
    sw t0, 104(sp)
    addi t0, sp, 108
    sw t0, 112(sp)
    addi t0, sp, 116
    sw t0, 120(sp)
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
    j .L2067
.L2067:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 124(sp)
    lw t1, 128(sp)
    slt t0, t0, t1
    sw t0, 132(sp)
    lw t0, 132(sp)
    bnez t0, .L2077
    j .L2126
.L2077:
    li t0, 0
    lw t1, 48(sp)
    sw t0, 0(t1)
    j .L2081
.L2081:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 136(sp)
    lw t1, 140(sp)
    slt t0, t0, t1
    sw t0, 144(sp)
    lw t0, 144(sp)
    bnez t0, .L2091
    j .L2119
.L2091:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 148(sp)
    lw t1, 152(sp)
    mul t0, t0, t1
    sw t0, 156(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 156(sp)
    lw t1, 160(sp)
    add t0, t0, t1
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
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 172(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 176(sp)
    lw t0, 176(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    j .L2081
.L2119:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 180(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 184(sp)
    lw t0, 184(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L2067
.L2126:
    li t0, 5
    lw t1, 56(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 64(sp)
    sw t0, 0(t1)
    j .L2132
.L2132:
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 188(sp)
    lw t1, 192(sp)
    slt t0, t0, t1
    sw t0, 196(sp)
    lw t0, 196(sp)
    bnez t0, .L2142
    j .L2421
.L2142:
    li t0, 0
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L2146
.L2146:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 200(sp)
    lw t1, 204(sp)
    slt t0, t0, t1
    sw t0, 208(sp)
    lw t0, 208(sp)
    bnez t0, .L2156
    j .L2412
.L2156:
    li t0, 0
    lw t1, 80(sp)
    sw t0, 0(t1)
    j .L2160
.L2160:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 212(sp)
    lw t1, 216(sp)
    slt t0, t0, t1
    sw t0, 220(sp)
    lw t0, 220(sp)
    bnez t0, .L2170
    j .L2403
.L2170:
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 224(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 228(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 228(sp)
    lw t1, 232(sp)
    add t0, t0, t1
    sw t0, 236(sp)
    lw t0, 236(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 240(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 240(sp)
    lw t1, 244(sp)
    slt t0, t1, t0
    sw t0, 248(sp)
    lw t0, 248(sp)
    bnez t0, .L2199
    j .L2207
.L2199:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 252(sp)
    lw t0, 252(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    j .L2207
.L2207:
    j .L2209
.L2209:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 256(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 260(sp)
    lw t0, 256(sp)
    lw t1, 260(sp)
    slt t0, t0, t1
    sw t0, 264(sp)
    lw t0, 264(sp)
    bnez t0, .L2219
    j .L2394
.L2219:
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 268(sp)
    lw t0, 268(sp)
    lw t1, 96(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 276(sp)
    lw t0, 272(sp)
    lw t1, 276(sp)
    add t0, t0, t1
    sw t0, 280(sp)
    lw t0, 280(sp)
    lw t1, 104(sp)
    sw t0, 0(t1)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 284(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 288(sp)
    lw t0, 284(sp)
    lw t1, 288(sp)
    slt t0, t1, t0
    sw t0, 292(sp)
    lw t0, 292(sp)
    bnez t0, .L2245
    j .L2253
.L2245:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 296(sp)
    lw t1, 104(sp)
    sw t0, 0(t1)
    j .L2253
.L2253:
    j .L2255
.L2255:
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 300(sp)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 304(sp)
    lw t0, 300(sp)
    lw t1, 304(sp)
    slt t0, t0, t1
    sw t0, 308(sp)
    lw t0, 308(sp)
    bnez t0, .L2265
    j .L2387
.L2265:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 312(sp)
    lw t1, 112(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 316(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 320(sp)
    lw t0, 316(sp)
    lw t1, 320(sp)
    add t0, t0, t1
    sw t0, 324(sp)
    lw t0, 324(sp)
    lw t1, 120(sp)
    sw t0, 0(t1)
    lw t0, 120(sp)
    lw t0, 0(t0)
    sw t0, 328(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 332(sp)
    lw t0, 328(sp)
    lw t1, 332(sp)
    slt t0, t1, t0
    sw t0, 336(sp)
    lw t0, 336(sp)
    bnez t0, .L2291
    j .L2299
.L2291:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 340(sp)
    lw t0, 340(sp)
    lw t1, 120(sp)
    sw t0, 0(t1)
    j .L2299
.L2299:
    j .L2301
.L2301:
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 344(sp)
    lw t0, 120(sp)
    lw t0, 0(t0)
    sw t0, 348(sp)
    lw t0, 344(sp)
    lw t1, 348(sp)
    slt t0, t0, t1
    sw t0, 352(sp)
    lw t0, 352(sp)
    bnez t0, .L2311
    j .L2380
.L2311:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 356(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 360(sp)
    lw t0, 356(sp)
    lw t1, 360(sp)
    mul t0, t0, t1
    sw t0, 364(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 368(sp)
    lw t0, 364(sp)
    lw t1, 368(sp)
    add t0, t0, t1
    sw t0, 372(sp)
    lw t0, 8(sp)
    lw t1, 372(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 376(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 380(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 384(sp)
    lw t0, 380(sp)
    lw t1, 384(sp)
    mul t0, t0, t1
    sw t0, 388(sp)
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 392(sp)
    lw t0, 388(sp)
    lw t1, 392(sp)
    add t0, t0, t1
    sw t0, 396(sp)
    lw t0, 0(sp)
    lw t1, 396(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 400(sp)
    lw t0, 400(sp)
    lw t0, 0(t0)
    sw t0, 404(sp)
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 408(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 412(sp)
    lw t0, 408(sp)
    lw t1, 412(sp)
    mul t0, t0, t1
    sw t0, 416(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 420(sp)
    lw t0, 416(sp)
    lw t1, 420(sp)
    add t0, t0, t1
    sw t0, 424(sp)
    lw t0, 4(sp)
    lw t1, 424(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 428(sp)
    lw t0, 428(sp)
    lw t0, 0(t0)
    sw t0, 432(sp)
    lw t0, 404(sp)
    lw t1, 432(sp)
    mul t0, t0, t1
    sw t0, 436(sp)
    lw t0, 376(sp)
    lw t0, 0(t0)
    sw t0, 440(sp)
    lw t0, 440(sp)
    lw t1, 436(sp)
    add t0, t0, t1
    sw t0, 444(sp)
    lw t0, 444(sp)
    lw t1, 376(sp)
    sw t0, 0(t1)
    lw t0, 112(sp)
    lw t0, 0(t0)
    sw t0, 448(sp)
    lw t0, 448(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 452(sp)
    lw t0, 452(sp)
    lw t1, 112(sp)
    sw t0, 0(t1)
    j .L2301
.L2380:
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 456(sp)
    lw t0, 456(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 460(sp)
    lw t0, 460(sp)
    lw t1, 96(sp)
    sw t0, 0(t1)
    j .L2255
.L2387:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 464(sp)
    lw t0, 464(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 468(sp)
    lw t0, 468(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L2209
.L2394:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 472(sp)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 476(sp)
    lw t0, 476(sp)
    lw t1, 472(sp)
    add t0, t0, t1
    sw t0, 480(sp)
    lw t0, 480(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    j .L2160
.L2403:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 484(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 488(sp)
    lw t0, 488(sp)
    lw t1, 484(sp)
    add t0, t0, t1
    sw t0, 492(sp)
    lw t0, 492(sp)
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L2146
.L2412:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 496(sp)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 500(sp)
    lw t0, 500(sp)
    lw t1, 496(sp)
    add t0, t0, t1
    sw t0, 504(sp)
    lw t0, 504(sp)
    lw t1, 64(sp)
    sw t0, 0(t1)
    j .L2132
.L2421:
    lw a0, 508(sp)
    j .L23
.L23:
    lw ra, 524(sp)
    lw s0, 520(sp)
    addi sp, sp, 528
    jr ra
    .globl calculateMatrixTrace
    .type calculateMatrixTrace, @function
calculateMatrixTrace:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
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
    j .L2430
.L2430:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L2440
    j .L2471
.L2440:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    mul t0, t0, t1
    sw t0, 56(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    add t0, t0, t1
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
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 72(sp)
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L2430
.L2471:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw a0, 92(sp)
    j .L24
.L24:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl extractSubmatrix
    .type extractSubmatrix, @function
extractSubmatrix:
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
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L2484
.L2484:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    slt t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L2494
    j .L2561
.L2494:
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L2498
.L2498:
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 68(sp)
    lw t1, 72(sp)
    slt t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    bnez t0, .L2508
    j .L2554
.L2508:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    mul t0, t0, t1
    sw t0, 88(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 88(sp)
    lw t1, 92(sp)
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 4(sp)
    lw t1, 96(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 104(sp)
    lw t1, 108(sp)
    mul t0, t0, t1
    sw t0, 112(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 112(sp)
    lw t1, 116(sp)
    add t0, t0, t1
    sw t0, 120(sp)
    lw t0, 0(sp)
    lw t1, 120(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 100(sp)
    sw t0, 0(t1)
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
    j .L2498
.L2554:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 140(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 144(sp)
    lw t0, 144(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L2484
.L2561:
    lw a0, 148(sp)
    j .L25
.L25:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl calculateDeterminant4x4
    .type calculateDeterminant4x4, @function
calculateDeterminant4x4:
    addi sp, sp, -432
    sw ra, 428(sp)
    sw s0, 424(sp)
    addi s0, sp, 432
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
    addi t0, sp, 72
    sw t0, 108(sp)
    addi t0, sp, 112
    sw t0, 116(sp)
    addi t0, sp, 120
    sw t0, 124(sp)
    addi t0, sp, 128
    sw t0, 132(sp)
    addi t0, sp, 136
    sw t0, 140(sp)
    addi t0, sp, 144
    sw t0, 148(sp)
    addi t0, sp, 152
    sw t0, 188(sp)
    lw t0, 0(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 12(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L2569
.L2569:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 192(sp)
    li t1, 4
    slt t0, t0, t1
    sw t0, 196(sp)
    lw t0, 196(sp)
    bnez t0, .L2577
    j .L2759
.L2577:
    li t0, 0
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L2582
.L2582:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 200(sp)
    li t1, 9
    slt t0, t0, t1
    sw t0, 204(sp)
    lw t0, 204(sp)
    bnez t0, .L2586
    j .L2587
.L2586:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 108(sp)
    lw t1, 208(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 212(sp)
    li t0, 0
    lw t1, 212(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 216(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 220(sp)
    lw t0, 220(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L2582
.L2587:
    lw a0, 60(sp)
    lw a1, 108(sp)
    li a2, 36
    call memcpy
    li t0, 0
    lw t1, 116(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 124(sp)
    sw t0, 0(t1)
    j .L2597
.L2597:
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 224(sp)
    li t1, 4
    slt t0, t0, t1
    sw t0, 228(sp)
    lw t0, 228(sp)
    bnez t0, .L2605
    j .L2693
.L2605:
    li t0, 0
    lw t1, 132(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 140(sp)
    sw t0, 0(t1)
    j .L2611
.L2611:
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 232(sp)
    li t1, 4
    slt t0, t0, t1
    sw t0, 236(sp)
    lw t0, 236(sp)
    bnez t0, .L2619
    j .L2680
.L2619:
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 240(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 240(sp)
    lw t1, 244(sp)
    sub t0, t0, t1
    snez t0, t0
    sw t0, 248(sp)
    lw t0, 248(sp)
    bnez t0, .L2631
    j .L2673
.L2631:
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 252(sp)
    lw t0, 252(sp)
    li t1, 3
    mul t0, t0, t1
    sw t0, 256(sp)
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 260(sp)
    lw t0, 256(sp)
    lw t1, 260(sp)
    add t0, t0, t1
    sw t0, 264(sp)
    lw t0, 60(sp)
    lw t1, 264(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 268(sp)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t0, 272(sp)
    li t1, 4
    mul t0, t0, t1
    sw t0, 276(sp)
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 276(sp)
    lw t1, 280(sp)
    add t0, t0, t1
    sw t0, 284(sp)
    lw t0, 0(sp)
    lw t1, 284(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 288(sp)
    lw t0, 288(sp)
    lw t0, 0(t0)
    sw t0, 292(sp)
    lw t0, 292(sp)
    lw t1, 268(sp)
    sw t0, 0(t1)
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 296(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 300(sp)
    lw t0, 300(sp)
    lw t1, 132(sp)
    sw t0, 0(t1)
    j .L2673
.L2673:
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 304(sp)
    lw t0, 304(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 308(sp)
    lw t0, 308(sp)
    lw t1, 140(sp)
    sw t0, 0(t1)
    j .L2611
.L2680:
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 312(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 316(sp)
    lw t1, 116(sp)
    sw t0, 0(t1)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 320(sp)
    lw t0, 320(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 324(sp)
    lw t0, 324(sp)
    lw t1, 124(sp)
    sw t0, 0(t1)
    j .L2597
.L2693:
    lw a0, 188(sp)
    lw a1, 60(sp)
    li a2, 36
    call memcpy
    lw a0, 188(sp)
    call calculateDeterminant3x3
    sw a0, 328(sp)
    lw t0, 328(sp)
    lw t1, 148(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 332(sp)
    lw t0, 332(sp)
    li t1, 2
    rem t0, t0, t1
    sw t0, 336(sp)
    lw t0, 336(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 340(sp)
    lw t0, 340(sp)
    bnez t0, .L2714
    j .L2733
.L2714:
    lw t0, 20(sp)
    lw t0, 0(t0)
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
    lw t0, 148(sp)
    lw t0, 0(t0)
    sw t0, 356(sp)
    lw t0, 352(sp)
    lw t1, 356(sp)
    mul t0, t0, t1
    sw t0, 360(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 364(sp)
    lw t0, 364(sp)
    lw t1, 360(sp)
    add t0, t0, t1
    sw t0, 368(sp)
    lw t0, 368(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2752
.L2733:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 372(sp)
    lw t0, 0(sp)
    lw t1, 372(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 376(sp)
    lw t0, 376(sp)
    lw t0, 0(t0)
    sw t0, 380(sp)
    lw t0, 148(sp)
    lw t0, 0(t0)
    sw t0, 384(sp)
    lw t0, 380(sp)
    lw t1, 384(sp)
    mul t0, t0, t1
    sw t0, 388(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 392(sp)
    lw t0, 392(sp)
    lw t1, 388(sp)
    sub t0, t0, t1
    sw t0, 396(sp)
    lw t0, 396(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2752
.L2752:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 400(sp)
    lw t0, 400(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 404(sp)
    lw t0, 404(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L2569
.L2759:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 408(sp)
    lw a0, 408(sp)
    j .L26
.L26:
    lw ra, 428(sp)
    lw s0, 424(sp)
    addi sp, sp, 432
    jr ra
    .globl calculateDeterminant3x3
    .type calculateDeterminant3x3, @function
calculateDeterminant3x3:
    addi sp, sp, -240
    sw ra, 236(sp)
    sw s0, 232(sp)
    addi s0, sp, 240
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    lw t0, 0(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 0
    sw t0, 32(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 0(sp)
    addi t0, t0, 16
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 0(sp)
    addi t0, t0, 32
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 44(sp)
    lw t1, 52(sp)
    mul t0, t0, t1
    sw t0, 56(sp)
    lw t0, 0(sp)
    addi t0, t0, 20
    sw t0, 60(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 0(sp)
    addi t0, t0, 28
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
    sub t0, t0, t1
    sw t0, 80(sp)
    lw t0, 36(sp)
    lw t1, 80(sp)
    mul t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 4
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 0(sp)
    addi t0, t0, 12
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 0(sp)
    addi t0, t0, 32
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 100(sp)
    lw t1, 108(sp)
    mul t0, t0, t1
    sw t0, 112(sp)
    lw t0, 0(sp)
    addi t0, t0, 20
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 0(sp)
    addi t0, t0, 24
    sw t0, 124(sp)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 120(sp)
    lw t1, 128(sp)
    mul t0, t0, t1
    sw t0, 132(sp)
    lw t0, 112(sp)
    lw t1, 132(sp)
    sub t0, t0, t1
    sw t0, 136(sp)
    lw t0, 92(sp)
    lw t1, 136(sp)
    mul t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 0(sp)
    addi t0, t0, 8
    sw t0, 144(sp)
    lw t0, 144(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 0(sp)
    addi t0, t0, 12
    sw t0, 152(sp)
    lw t0, 152(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 0(sp)
    addi t0, t0, 28
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 156(sp)
    lw t1, 164(sp)
    mul t0, t0, t1
    sw t0, 168(sp)
    lw t0, 0(sp)
    addi t0, t0, 16
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 0(sp)
    addi t0, t0, 24
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 176(sp)
    lw t1, 184(sp)
    mul t0, t0, t1
    sw t0, 188(sp)
    lw t0, 168(sp)
    lw t1, 188(sp)
    sub t0, t0, t1
    sw t0, 192(sp)
    lw t0, 148(sp)
    lw t1, 192(sp)
    mul t0, t0, t1
    sw t0, 196(sp)
    lw t0, 196(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 200(sp)
    lw t1, 204(sp)
    sub t0, t0, t1
    sw t0, 208(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 208(sp)
    lw t1, 212(sp)
    add t0, t0, t1
    sw t0, 216(sp)
    lw a0, 216(sp)
    j .L27
.L27:
    lw ra, 236(sp)
    lw s0, 232(sp)
    addi sp, sp, 240
    jr ra
    .globl performVectorCalculations
    .type performVectorCalculations, @function
performVectorCalculations:
    li t0, -3440
    add sp, sp, t0
    li t0, 3436
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 3432
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 3440
    add s0, sp, t0
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 408(sp)
    addi t0, sp, 412
    sw t0, 416(sp)
    addi t0, sp, 420
    sw t0, 820(sp)
    addi t0, sp, 824
    sw t0, 1224(sp)
    addi t0, sp, 1228
    sw t0, 1232(sp)
    addi t0, sp, 1236
    sw t0, 1636(sp)
    addi t0, sp, 1640
    sw t0, 2040(sp)
    addi t0, sp, 2044
    li t3, 2048
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2052
    add t0, sp, t1
    li t3, 2452
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2456
    add t0, sp, t1
    li t3, 2460
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2464
    add t0, sp, t1
    li t3, 2468
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2472
    add t0, sp, t1
    li t3, 2872
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2876
    add t0, sp, t1
    li t3, 2880
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2884
    add t0, sp, t1
    li t3, 3284
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 100
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 416(sp)
    sw t0, 0(t1)
    j .L2918
.L2918:
    lw t0, 416(sp)
    lw t0, 0(t0)
    li t3, 3288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3288
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 3292
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3292
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2922
    j .L2923
.L2922:
    lw t0, 416(sp)
    lw t0, 0(t0)
    li t3, 3296
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 820(sp)
    li t3, 3296
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3300
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 3300
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 416(sp)
    lw t0, 0(t0)
    li t3, 3304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3304
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3308
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3308
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 416(sp)
    sw t0, 0(t1)
    j .L2918
.L2923:
    lw a0, 408(sp)
    lw a1, 820(sp)
    li a2, 400
    call memcpy
    li t0, 0
    lw t1, 1232(sp)
    sw t0, 0(t1)
    j .L2932
.L2932:
    lw t0, 1232(sp)
    lw t0, 0(t0)
    li t3, 3312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3312
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 3316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3316
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2936
    j .L2937
.L2936:
    lw t0, 1232(sp)
    lw t0, 0(t0)
    li t3, 3320
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1636(sp)
    li t3, 3320
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3324
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 3324
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 1232(sp)
    lw t0, 0(t0)
    li t3, 3328
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3328
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 1232(sp)
    sw t0, 0(t1)
    j .L2932
.L2937:
    lw a0, 1224(sp)
    lw a1, 1636(sp)
    li a2, 400
    call memcpy
    li t0, 0
    li t3, 2048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2946
.L2946:
    li t3, 2048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3336
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 3340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3340
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2950
    j .L2951
.L2950:
    li t3, 2048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2452
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3344
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3348
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 3348
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 2048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3352
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3356
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3356
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2048
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2946
.L2951:
    lw a0, 2040(sp)
    li t3, 2452
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 400
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 3360
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 408(sp)
    lw a1, 1224(sp)
    li t3, 3360
    add t3, t3, sp
    lw a2, 0(t3)
    call initializeVectors
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 3364
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 408(sp)
    lw a1, 1224(sp)
    li t3, 3364
    add t3, t3, sp
    lw a2, 0(t3)
    call vectorDotProduct
    li t3, 3368
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 3368
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2460
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 3372
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 408(sp)
    lw a1, 1224(sp)
    lw a2, 2040(sp)
    li t3, 3372
    add t3, t3, sp
    lw a3, 0(t3)
    call vectorAddition
    li t3, 2872
    add t3, t3, sp
    lw a0, 0(t3)
    lw a1, 408(sp)
    li a2, 400
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 3376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2872
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 3376
    add t3, t3, sp
    lw a1, 0(t3)
    call vectorMagnitude
    li t3, 3380
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 3380
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2468
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3284
    add t3, t3, sp
    lw a0, 0(t3)
    lw a1, 1224(sp)
    li a2, 400
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 3384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3284
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 3384
    add t3, t3, sp
    lw a1, 0(t3)
    call vectorMagnitude
    li t3, 3388
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 3388
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2880
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 3392
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 2040(sp)
    li a1, 3
    li t3, 3392
    add t3, t3, sp
    lw a2, 0(t3)
    call vectorScalarMultiply
    li t3, 2460
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2468
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3396
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3400
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2880
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3404
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3408
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3412
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 3416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3416
    add t3, t3, sp
    lw a0, 0(t3)
    j .L28
.L28:
    li t0, 3436
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 3432
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 3440
    add sp, sp, t0
    jr ra
    .globl initializeVectors
    .type initializeVectors, @function
initializeVectors:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
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
    j .L3054
.L3054:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L3064
    j .L3119
.L3064:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 0(sp)
    lw t1, 48(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 60(sp)
    lw t0, 60(sp)
    li t1, 20
    rem t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 4(sp)
    lw t1, 68(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 72(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 2
    mul t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 15
    rem t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 72(sp)
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
    j .L3054
.L3119:
    lw a0, 100(sp)
    j .L29
.L29:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl vectorDotProduct
    .type vectorDotProduct, @function
vectorDotProduct:
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
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 32(sp)
    addi t0, sp, 36
    sw t0, 40(sp)
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
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3129
.L3129:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 44(sp)
    lw t1, 48(sp)
    slt t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L3139
    j .L3168
.L3139:
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
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 4(sp)
    lw t1, 68(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 64(sp)
    lw t1, 76(sp)
    mul t0, t0, t1
    sw t0, 80(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 80(sp)
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3129
.L3168:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 104(sp)
    lw a0, 104(sp)
    j .L30
.L30:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl vectorAddition
    .type vectorAddition, @function
vectorAddition:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
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
    j .L3189
.L3189:
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
    bnez t0, .L3199
    j .L3231
.L3199:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 8(sp)
    lw t1, 56(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 60(sp)
    lw t0, 40(sp)
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
    lw t0, 40(sp)
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
    lw t0, 72(sp)
    lw t1, 84(sp)
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3189
.L3231:
    lw a0, 100(sp)
    j .L31
.L31:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl vectorMagnitude
    .type vectorMagnitude, @function
vectorMagnitude:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
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
    j .L3240
.L3240:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L3250
    j .L3279
.L3250:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 0(sp)
    lw t1, 48(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 0(sp)
    lw t1, 60(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 56(sp)
    lw t1, 68(sp)
    mul t0, t0, t1
    sw t0, 72(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 72(sp)
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L3240
.L3279:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw a0, 92(sp)
    call integerSquareRoot
    sw a0, 96(sp)
    lw a0, 96(sp)
    j .L32
.L32:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl integerSquareRoot
    .type integerSquareRoot, @function
integerSquareRoot:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
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
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 32(sp)
    lw t0, 32(sp)
    bnez t0, .L3302
    j .L3304
.L3302:
    li a0, 0
    j .L33
.L3304:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 36(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L3312
.L3312:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 40(sp)
    lw t1, 44(sp)
    sub t0, t0, t1
    snez t0, t0
    sw t0, 48(sp)
    lw t0, 48(sp)
    bnez t0, .L3322
    j .L3354
.L3322:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    div t0, t0, t1
    sw t0, 68(sp)
    lw t0, 56(sp)
    lw t1, 68(sp)
    add t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    li t1, 2
    div t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    j .L3312
.L3354:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw a0, 80(sp)
    j .L33
.L33:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl vectorScalarMultiply
    .type vectorScalarMultiply, @function
vectorScalarMultiply:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
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
    j .L3366
.L3366:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 40(sp)
    lw t1, 44(sp)
    slt t0, t0, t1
    sw t0, 48(sp)
    lw t0, 48(sp)
    bnez t0, .L3376
    j .L3395
.L3376:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 0(sp)
    lw t1, 52(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 56(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    lw t1, 60(sp)
    mul t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L3366
.L3395:
    lw a0, 80(sp)
    j .L34
.L34:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl solveLinearSystem
    .type solveLinearSystem, @function
solveLinearSystem:
    addi sp, sp, -464
    sw ra, 460(sp)
    sw s0, 456(sp)
    addi s0, sp, 464
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 128(sp)
    addi t0, sp, 132
    sw t0, 136(sp)
    addi t0, sp, 140
    sw t0, 260(sp)
    addi t0, sp, 264
    sw t0, 268(sp)
    addi t0, sp, 272
    sw t0, 392(sp)
    li t0, 5
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 136(sp)
    sw t0, 0(t1)
    j .L3403
.L3403:
    lw t0, 136(sp)
    lw t0, 0(t0)
    sw t0, 396(sp)
    lw t0, 396(sp)
    li t1, 30
    slt t0, t0, t1
    sw t0, 400(sp)
    lw t0, 400(sp)
    bnez t0, .L3407
    j .L3408
.L3407:
    lw t0, 136(sp)
    lw t0, 0(t0)
    sw t0, 404(sp)
    lw t0, 260(sp)
    lw t1, 404(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 408(sp)
    li t0, 0
    lw t1, 408(sp)
    sw t0, 0(t1)
    lw t0, 136(sp)
    lw t0, 0(t0)
    sw t0, 412(sp)
    lw t0, 412(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 416(sp)
    lw t0, 416(sp)
    lw t1, 136(sp)
    sw t0, 0(t1)
    j .L3403
.L3408:
    lw a0, 128(sp)
    lw a1, 260(sp)
    li a2, 120
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 420(sp)
    lw a0, 128(sp)
    lw a1, 420(sp)
    call initializeLinearSystem
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 424(sp)
    lw a0, 128(sp)
    lw a1, 424(sp)
    call gaussianElimination
    lw a0, 392(sp)
    lw a1, 128(sp)
    li a2, 120
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 428(sp)
    lw a0, 392(sp)
    lw a1, 428(sp)
    call backSubstitution
    sw a0, 432(sp)
    lw t0, 432(sp)
    lw t1, 268(sp)
    sw t0, 0(t1)
    lw t0, 268(sp)
    lw t0, 0(t0)
    sw t0, 436(sp)
    lw t0, 436(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 440(sp)
    lw a0, 440(sp)
    j .L35
.L35:
    lw ra, 460(sp)
    lw s0, 456(sp)
    addi sp, sp, 464
    jr ra
    .globl initializeLinearSystem
    .type initializeLinearSystem, @function
initializeLinearSystem:
    addi sp, sp, -224
    sw ra, 220(sp)
    sw s0, 216(sp)
    addi s0, sp, 224
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L3452
.L3452:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L3462
    j .L3622
.L3462:
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L3466
.L3466:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw t0, 48(sp)
    lw t1, 52(sp)
    slt t0, t0, t1
    sw t0, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L3476
    j .L3576
.L3476:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L3488
    j .L3523
.L3488:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 72(sp)
    lw t1, 80(sp)
    mul t0, t0, t1
    sw t0, 84(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 84(sp)
    lw t1, 88(sp)
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 0(sp)
    lw t1, 92(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    li t0, 10
    lw t1, 100(sp)
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 96(sp)
    sw t0, 0(t1)
    j .L3569
.L3523:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 108(sp)
    lw t1, 116(sp)
    mul t0, t0, t1
    sw t0, 120(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 120(sp)
    lw t1, 124(sp)
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 0(sp)
    lw t1, 128(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 132(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 136(sp)
    lw t1, 140(sp)
    add t0, t0, t1
    sw t0, 144(sp)
    lw t0, 144(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 148(sp)
    lw t0, 148(sp)
    li t1, 5
    rem t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    lw t1, 132(sp)
    sw t0, 0(t1)
    j .L3569
.L3569:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 156(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L3466
.L3576:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 164(sp)
    lw t1, 172(sp)
    mul t0, t0, t1
    sw t0, 176(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 176(sp)
    lw t1, 180(sp)
    add t0, t0, t1
    sw t0, 184(sp)
    lw t0, 0(sp)
    lw t1, 184(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 188(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 192(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 196(sp)
    lw t0, 196(sp)
    li t1, 10
    mul t0, t0, t1
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t1, 188(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 204(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 208(sp)
    lw t0, 208(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L3452
.L3622:
    lw a0, 212(sp)
    j .L36
.L36:
    lw ra, 220(sp)
    lw s0, 216(sp)
    addi sp, sp, 224
    jr ra
    .globl gaussianElimination
    .type gaussianElimination, @function
gaussianElimination:
    addi sp, sp, -464
    sw ra, 460(sp)
    sw s0, 456(sp)
    addi s0, sp, 464
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L3629
.L3629:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    slt t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L3639
    j .L3960
.L3639:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3653
.L3653:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 84(sp)
    lw t1, 88(sp)
    slt t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    bnez t0, .L3663
    j .L3738
.L3663:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 96(sp)
    lw t1, 104(sp)
    mul t0, t0, t1
    sw t0, 108(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 108(sp)
    lw t1, 112(sp)
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
    lw a0, 124(sp)
    call abs
    sw a0, 128(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 132(sp)
    lw t1, 140(sp)
    mul t0, t0, t1
    sw t0, 144(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 144(sp)
    lw t1, 148(sp)
    add t0, t0, t1
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
    lw a0, 160(sp)
    call abs
    sw a0, 164(sp)
    lw t0, 128(sp)
    lw t1, 164(sp)
    slt t0, t1, t0
    sw t0, 168(sp)
    lw t0, 168(sp)
    bnez t0, .L3723
    j .L3731
.L3723:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 172(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L3731
.L3731:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 176(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3653
.L3738:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 184(sp)
    lw t1, 188(sp)
    sub t0, t0, t1
    snez t0, t0
    sw t0, 192(sp)
    lw t0, 192(sp)
    bnez t0, .L3750
    j .L3760
.L3750:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw a0, 0(sp)
    lw a1, 196(sp)
    lw a2, 200(sp)
    lw a3, 204(sp)
    call swapRows
    j .L3760
.L3760:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 208(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3773
.L3773:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 220(sp)
    lw t0, 216(sp)
    lw t1, 220(sp)
    slt t0, t0, t1
    sw t0, 224(sp)
    lw t0, 224(sp)
    bnez t0, .L3783
    j .L3953
.L3783:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 228(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 232(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 236(sp)
    lw t0, 228(sp)
    lw t1, 236(sp)
    mul t0, t0, t1
    sw t0, 240(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 240(sp)
    lw t1, 244(sp)
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 0(sp)
    lw t1, 248(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 252(sp)
    lw t0, 252(sp)
    lw t0, 0(t0)
    sw t0, 256(sp)
    lw t0, 256(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 260(sp)
    lw t0, 260(sp)
    bnez t0, .L3814
    j .L3946
.L3814:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 264(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 268(sp)
    lw t0, 268(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 272(sp)
    lw t0, 264(sp)
    lw t1, 272(sp)
    mul t0, t0, t1
    sw t0, 276(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 276(sp)
    lw t1, 280(sp)
    add t0, t0, t1
    sw t0, 284(sp)
    lw t0, 0(sp)
    lw t1, 284(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 288(sp)
    lw t0, 288(sp)
    lw t0, 0(t0)
    sw t0, 292(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 300(sp)
    lw t0, 300(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 304(sp)
    lw t0, 296(sp)
    lw t1, 304(sp)
    mul t0, t0, t1
    sw t0, 308(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 308(sp)
    lw t1, 312(sp)
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 0(sp)
    lw t1, 316(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 320(sp)
    lw t0, 320(sp)
    lw t0, 0(t0)
    sw t0, 324(sp)
    lw t0, 292(sp)
    lw t1, 324(sp)
    div t0, t0, t1
    sw t0, 328(sp)
    lw t0, 328(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 332(sp)
    lw t0, 332(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    j .L3872
.L3872:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 336(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 340(sp)
    lw t0, 336(sp)
    lw t1, 340(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 344(sp)
    lw t0, 344(sp)
    bnez t0, .L3882
    j .L3945
.L3882:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 348(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 352(sp)
    lw t0, 352(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 356(sp)
    lw t0, 348(sp)
    lw t1, 356(sp)
    mul t0, t0, t1
    sw t0, 360(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 364(sp)
    lw t0, 360(sp)
    lw t1, 364(sp)
    add t0, t0, t1
    sw t0, 368(sp)
    lw t0, 0(sp)
    lw t1, 368(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 372(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 376(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 380(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 384(sp)
    lw t0, 384(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 388(sp)
    lw t0, 380(sp)
    lw t1, 388(sp)
    mul t0, t0, t1
    sw t0, 392(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 396(sp)
    lw t0, 392(sp)
    lw t1, 396(sp)
    add t0, t0, t1
    sw t0, 400(sp)
    lw t0, 0(sp)
    lw t1, 400(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 404(sp)
    lw t0, 404(sp)
    lw t0, 0(t0)
    sw t0, 408(sp)
    lw t0, 376(sp)
    lw t1, 408(sp)
    mul t0, t0, t1
    sw t0, 412(sp)
    lw t0, 372(sp)
    lw t0, 0(t0)
    sw t0, 416(sp)
    lw t0, 416(sp)
    lw t1, 412(sp)
    sub t0, t0, t1
    sw t0, 420(sp)
    lw t0, 420(sp)
    lw t1, 372(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 424(sp)
    lw t0, 424(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 428(sp)
    lw t0, 428(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    j .L3872
.L3945:
    j .L3946
.L3946:
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 432(sp)
    lw t0, 432(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 436(sp)
    lw t0, 436(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L3773
.L3953:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 440(sp)
    lw t0, 440(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 444(sp)
    lw t0, 444(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L3629
.L3960:
    lw a0, 448(sp)
    j .L37
.L37:
    lw ra, 460(sp)
    lw s0, 456(sp)
    addi sp, sp, 464
    jr ra
    .globl swapRows
    .type swapRows, @function
swapRows:
    addi sp, sp, -224
    sw ra, 220(sp)
    sw s0, 216(sp)
    addi s0, sp, 224
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
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
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 8(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 48(sp)
    sw t0, 0(t1)
    j .L3969
.L3969:
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 60(sp)
    lw t1, 64(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 68(sp)
    lw t0, 68(sp)
    bnez t0, .L3979
    j .L4088
.L3979:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 72(sp)
    lw t1, 80(sp)
    mul t0, t0, t1
    sw t0, 84(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 84(sp)
    lw t1, 88(sp)
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 0(sp)
    lw t1, 92(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 112(sp)
    lw t0, 104(sp)
    lw t1, 112(sp)
    mul t0, t0, t1
    sw t0, 116(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 116(sp)
    lw t1, 120(sp)
    add t0, t0, t1
    sw t0, 124(sp)
    lw t0, 0(sp)
    lw t1, 124(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 132(sp)
    lw t1, 140(sp)
    mul t0, t0, t1
    sw t0, 144(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 144(sp)
    lw t1, 148(sp)
    add t0, t0, t1
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
    lw t0, 160(sp)
    lw t1, 128(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 168(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 172(sp)
    lw t0, 164(sp)
    lw t1, 172(sp)
    mul t0, t0, t1
    sw t0, 176(sp)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 176(sp)
    lw t1, 180(sp)
    add t0, t0, t1
    sw t0, 184(sp)
    lw t0, 0(sp)
    lw t1, 184(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 188(sp)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 192(sp)
    lw t0, 192(sp)
    lw t1, 188(sp)
    sw t0, 0(t1)
    lw t0, 48(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 196(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t1, 48(sp)
    sw t0, 0(t1)
    j .L3969
.L4088:
    lw a0, 204(sp)
    j .L38
.L38:
    lw ra, 220(sp)
    lw s0, 216(sp)
    addi sp, sp, 224
    jr ra
    .globl backSubstitution
    .type backSubstitution, @function
backSubstitution:
    addi sp, sp, -416
    sw ra, 412(sp)
    sw s0, 408(sp)
    addi s0, sp, 416
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 48(sp)
    addi t0, sp, 52
    sw t0, 56(sp)
    addi t0, sp, 60
    sw t0, 80(sp)
    addi t0, sp, 84
    sw t0, 88(sp)
    addi t0, sp, 92
    sw t0, 96(sp)
    addi t0, sp, 100
    sw t0, 104(sp)
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
    lw t1, 56(sp)
    sw t0, 0(t1)
    j .L4098
.L4098:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 5
    slt t0, t0, t1
    sw t0, 112(sp)
    lw t0, 112(sp)
    bnez t0, .L4102
    j .L4103
.L4102:
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 80(sp)
    lw t1, 116(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 120(sp)
    li t0, 0
    lw t1, 120(sp)
    sw t0, 0(t1)
    lw t0, 56(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 56(sp)
    sw t0, 0(t1)
    j .L4098
.L4103:
    lw a0, 48(sp)
    lw a1, 80(sp)
    li a2, 20
    call memcpy
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 132(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    j .L4120
.L4120:
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 140(sp)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    sw t0, 144(sp)
    lw t0, 144(sp)
    bnez t0, .L4128
    j .L4325
.L4128:
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 148(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 152(sp)
    lw t0, 152(sp)
    lw t1, 88(sp)
    sw t0, 0(t1)
    lw t0, 88(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw t0, 156(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t1, 96(sp)
    sw t0, 0(t1)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 48(sp)
    lw t1, 164(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 168(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 176(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 172(sp)
    lw t1, 180(sp)
    mul t0, t0, t1
    sw t0, 184(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 184(sp)
    lw t1, 188(sp)
    add t0, t0, t1
    sw t0, 192(sp)
    lw t0, 0(sp)
    lw t1, 192(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 196(sp)
    lw t0, 196(sp)
    lw t0, 0(t0)
    sw t0, 200(sp)
    lw t0, 200(sp)
    lw t1, 168(sp)
    sw t0, 0(t1)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 204(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 208(sp)
    lw t0, 208(sp)
    lw t1, 104(sp)
    sw t0, 0(t1)
    j .L4187
.L4187:
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 212(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 212(sp)
    lw t1, 216(sp)
    slt t0, t0, t1
    sw t0, 220(sp)
    lw t0, 220(sp)
    bnez t0, .L4197
    j .L4247
.L4197:
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 48(sp)
    lw t1, 224(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 228(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 232(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 236(sp)
    lw t0, 236(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 240(sp)
    lw t0, 232(sp)
    lw t1, 240(sp)
    mul t0, t0, t1
    sw t0, 244(sp)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 248(sp)
    lw t0, 244(sp)
    lw t1, 248(sp)
    add t0, t0, t1
    sw t0, 252(sp)
    lw t0, 0(sp)
    lw t1, 252(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 256(sp)
    lw t0, 256(sp)
    lw t0, 0(t0)
    sw t0, 260(sp)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 264(sp)
    lw t0, 48(sp)
    lw t1, 264(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 268(sp)
    lw t0, 268(sp)
    lw t0, 0(t0)
    sw t0, 272(sp)
    lw t0, 260(sp)
    lw t1, 272(sp)
    mul t0, t0, t1
    sw t0, 276(sp)
    lw t0, 228(sp)
    lw t0, 0(t0)
    sw t0, 280(sp)
    lw t0, 280(sp)
    lw t1, 276(sp)
    sub t0, t0, t1
    sw t0, 284(sp)
    lw t0, 284(sp)
    lw t1, 228(sp)
    sw t0, 0(t1)
    lw t0, 104(sp)
    lw t0, 0(t0)
    sw t0, 288(sp)
    lw t0, 288(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 292(sp)
    lw t0, 292(sp)
    lw t1, 104(sp)
    sw t0, 0(t1)
    j .L4187
.L4247:
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 296(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 300(sp)
    lw t0, 300(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 304(sp)
    lw t0, 296(sp)
    lw t1, 304(sp)
    mul t0, t0, t1
    sw t0, 308(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 308(sp)
    lw t1, 312(sp)
    add t0, t0, t1
    sw t0, 316(sp)
    lw t0, 0(sp)
    lw t1, 316(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 320(sp)
    lw t0, 320(sp)
    lw t0, 0(t0)
    sw t0, 324(sp)
    lw t0, 324(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 328(sp)
    lw t0, 328(sp)
    bnez t0, .L4278
    j .L4312
.L4278:
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 332(sp)
    lw t0, 48(sp)
    lw t1, 332(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 336(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 340(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 344(sp)
    lw t0, 344(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 348(sp)
    lw t0, 340(sp)
    lw t1, 348(sp)
    mul t0, t0, t1
    sw t0, 352(sp)
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 356(sp)
    lw t0, 352(sp)
    lw t1, 356(sp)
    add t0, t0, t1
    sw t0, 360(sp)
    lw t0, 0(sp)
    lw t1, 360(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 364(sp)
    lw t0, 364(sp)
    lw t0, 0(t0)
    sw t0, 368(sp)
    lw t0, 336(sp)
    lw t0, 0(t0)
    sw t0, 372(sp)
    lw t0, 372(sp)
    lw t1, 368(sp)
    div t0, t0, t1
    sw t0, 376(sp)
    lw t0, 376(sp)
    lw t1, 336(sp)
    sw t0, 0(t1)
    j .L4312
.L4312:
    lw t0, 96(sp)
    lw t0, 0(t0)
    sw t0, 380(sp)
    lw t0, 48(sp)
    lw t1, 380(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 384(sp)
    lw t0, 384(sp)
    lw t0, 0(t0)
    sw t0, 388(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 392(sp)
    lw t0, 392(sp)
    lw t1, 388(sp)
    add t0, t0, t1
    sw t0, 396(sp)
    lw t0, 396(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L4120
.L4325:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 400(sp)
    lw a0, 400(sp)
    j .L39
.L39:
    lw ra, 412(sp)
    lw s0, 408(sp)
    addi sp, sp, 416
    jr ra
    .globl abs
    .type abs, @function
abs:
    addi sp, sp, -48
    sw ra, 44(sp)
    sw s0, 40(sp)
    addi s0, sp, 48
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
    li t1, 0
    slt t0, t0, t1
    sw t0, 16(sp)
    lw t0, 16(sp)
    bnez t0, .L4342
    j .L4352
.L4342:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 20(sp)
    li t0, 0
    lw t1, 20(sp)
    sub t0, t0, t1
    sw t0, 24(sp)
    lw a0, 24(sp)
    j .L40
.L4352:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 28(sp)
    lw a0, 28(sp)
    j .L40
.L4358:
    li a0, 0
    j .L40
.L40:
    lw ra, 44(sp)
    lw s0, 40(sp)
    addi sp, sp, 48
    jr ra
    .globl performCombinatorialAlgorithms
    .type performCombinatorialAlgorithms, @function
performCombinatorialAlgorithms:
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
    li a0, 3007
    call printlnInt
    li a0, 20
    call calculatePascalTriangle
    sw a0, 32(sp)
    lw t0, 32(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw a0, 36(sp)
    call printlnInt
    li a0, 15
    call calculatePermutations
    sw a0, 40(sp)
    lw t0, 40(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw a0, 44(sp)
    call printlnInt
    li a0, 20
    call calculateCombinations
    sw a0, 48(sp)
    lw t0, 48(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw a0, 52(sp)
    call printlnInt
    li a0, 15
    call calculateCatalanNumbers
    sw a0, 56(sp)
    lw t0, 56(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw a0, 60(sp)
    call printlnInt
    li a0, 3008
    call printlnInt
    lw a0, 64(sp)
    j .L41
.L41:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl calculatePascalTriangle
    .type calculatePascalTriangle, @function
calculatePascalTriangle:
    li t0, -3616
    add sp, sp, t0
    li t0, 3612
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 3608
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 3616
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 1652(sp)
    addi t0, sp, 1656
    sw t0, 1660(sp)
    addi t0, sp, 1664
    li t3, 3304
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 3308
    add t0, sp, t1
    li t3, 3312
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 3316
    add t0, sp, t1
    li t3, 3320
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 3324
    add t0, sp, t1
    li t3, 3328
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 1660(sp)
    sw t0, 0(t1)
    j .L4399
.L4399:
    lw t0, 1660(sp)
    lw t0, 0(t0)
    li t3, 3332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3332
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 410
    slt t0, t0, t1
    li t3, 3336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3336
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4403
    j .L4404
.L4403:
    lw t0, 1660(sp)
    lw t0, 0(t0)
    li t3, 3340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3304
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3340
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3344
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 3344
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 1660(sp)
    lw t0, 0(t0)
    li t3, 3348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3348
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3352
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 1660(sp)
    sw t0, 0(t1)
    j .L4399
.L4404:
    lw a0, 1652(sp)
    li t3, 3304
    add t3, t3, sp
    lw a1, 0(t3)
    li a2, 1640
    call memcpy
    li t0, 0
    li t3, 3312
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 1652(sp)
    addi t0, t0, 0
    li t3, 3356
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 3356
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3312
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3360
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3364
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3312
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 1
    li t3, 3320
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4427
.L4427:
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3368
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 3372
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3368
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3372
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 3376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3376
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4437
    j .L4612
.L4437:
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3380
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 3384
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3380
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3384
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 3388
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1652(sp)
    li t3, 3388
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3392
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 3392
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3312
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3396
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3396
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3400
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3312
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 1
    li t3, 3328
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4462
.L4462:
    li t3, 3328
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3408
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3404
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3408
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 3412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3412
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L4472
    j .L4578
.L4472:
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3416
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 3420
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3416
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3420
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 3424
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3328
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3428
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3424
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3428
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3432
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1652(sp)
    li t3, 3432
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3436
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3440
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3440
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 3444
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 3448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3444
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3448
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 3452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3328
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3456
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3452
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3456
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3460
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3460
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 3464
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1652(sp)
    li t3, 3464
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3468
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3472
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3476
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 3480
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 3484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3480
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3484
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 3488
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3328
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3488
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3492
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3496
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1652(sp)
    li t3, 3496
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3500
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3504
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3472
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3504
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3508
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3508
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3436
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3512
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 3516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3512
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3516
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 3520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3328
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3524
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3520
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3524
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3528
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1652(sp)
    li t3, 3528
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3532
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3312
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3540
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3536
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3544
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3544
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3312
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3328
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3548
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3552
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3552
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3328
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4462
.L4578:
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3556
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    lw t0, 0(t0)
    li t3, 3560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3556
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3560
    add t3, t3, sp
    lw t1, 0(t3)
    mul t0, t0, t1
    li t3, 3564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3568
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3568
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 3572
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1652(sp)
    li t3, 3572
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 3576
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 1
    li t3, 3576
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3312
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3580
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3580
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3584
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3584
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3312
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 3320
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3588
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3588
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 3592
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3592
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 3320
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L4427
.L4612:
    li t3, 3312
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 3596
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3596
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 3600
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 3600
    add t3, t3, sp
    lw a0, 0(t3)
    j .L42
.L42:
    li t0, 3612
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 3608
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 3616
    add sp, sp, t0
    jr ra
    .globl calculatePermutations
    .type calculatePermutations, @function
calculatePermutations:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    sw a0, 0(sp)
    addi t0, sp, 4
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
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L4632
.L4632:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 44(sp)
    lw t1, 48(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L4642
    j .L4697
.L4642:
    li t0, 1
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L4646
.L4646:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L4656
    j .L4690
.L4656:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw a0, 68(sp)
    lw a1, 72(sp)
    call permutation
    sw a0, 76(sp)
    lw t0, 76(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L4646
.L4690:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L4632
.L4697:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 116(sp)
    lw a0, 116(sp)
    j .L43
.L43:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl permutation
    .type permutation, @function
permutation:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
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
    li t0, 1
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 40(sp)
    lw t1, 44(sp)
    sub t0, t0, t1
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L4730
.L4730:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L4740
    j .L4765
.L4740:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 68(sp)
    lw t1, 72(sp)
    mul t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L4730
.L4765:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw a0, 92(sp)
    j .L44
.L44:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl calculateCombinations
    .type calculateCombinations, @function
calculateCombinations:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
    sw a0, 0(sp)
    addi t0, sp, 4
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
    li t0, 0
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L4777
.L4777:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 44(sp)
    lw t1, 48(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L4787
    j .L4842
.L4787:
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L4791
.L4791:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L4801
    j .L4835
.L4801:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw a0, 68(sp)
    lw a1, 72(sp)
    call combination
    sw a0, 76(sp)
    lw t0, 76(sp)
    lw t1, 40(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 40(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L4791
.L4835:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L4777
.L4842:
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 116(sp)
    lw a0, 116(sp)
    j .L45
.L45:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl combination
    .type combination, @function
combination:
    addi sp, sp, -160
    sw ra, 156(sp)
    sw s0, 152(sp)
    addi s0, sp, 160
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
    addi t0, sp, 40
    sw t0, 44(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
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
    lw t0, 48(sp)
    lw t1, 60(sp)
    slt t0, t1, t0
    sw t0, 64(sp)
    lw t0, 64(sp)
    bnez t0, .L4879
    j .L4888
.L4879:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 68(sp)
    lw t1, 72(sp)
    sub t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L4891
.L4888:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L4891
.L4891:
    li t0, 1
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L4897
.L4897:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 84(sp)
    lw t1, 88(sp)
    slt t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    bnez t0, .L4907
    j .L4945
.L4907:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 100(sp)
    lw t1, 104(sp)
    sub t0, t0, t1
    sw t0, 108(sp)
    lw t0, 96(sp)
    lw t1, 108(sp)
    mul t0, t0, t1
    sw t0, 112(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 116(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 120(sp)
    lw t0, 112(sp)
    lw t1, 120(sp)
    div t0, t0, t1
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
    j .L4897
.L4945:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 140(sp)
    lw a0, 140(sp)
    j .L46
.L46:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl calculateCatalanNumbers
    .type calculateCatalanNumbers, @function
calculateCatalanNumbers:
    addi sp, sp, -368
    sw ra, 364(sp)
    sw s0, 360(sp)
    addi s0, sp, 368
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 72(sp)
    addi t0, sp, 76
    sw t0, 80(sp)
    addi t0, sp, 84
    sw t0, 144(sp)
    addi t0, sp, 148
    sw t0, 152(sp)
    addi t0, sp, 156
    sw t0, 160(sp)
    addi t0, sp, 164
    sw t0, 168(sp)
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 80(sp)
    sw t0, 0(t1)
    j .L4964
.L4964:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 172(sp)
    li t1, 15
    slt t0, t0, t1
    sw t0, 176(sp)
    lw t0, 176(sp)
    bnez t0, .L4968
    j .L4969
.L4968:
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 144(sp)
    lw t1, 180(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 184(sp)
    li t0, 0
    lw t1, 184(sp)
    sw t0, 0(t1)
    lw t0, 80(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 188(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 192(sp)
    lw t0, 192(sp)
    lw t1, 80(sp)
    sw t0, 0(t1)
    j .L4964
.L4969:
    lw a0, 72(sp)
    lw a1, 144(sp)
    li a2, 60
    call memcpy
    li t0, 0
    lw t1, 152(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    addi t0, t0, 0
    sw t0, 196(sp)
    li t0, 1
    lw t1, 196(sp)
    sw t0, 0(t1)
    lw t0, 72(sp)
    addi t0, t0, 4
    sw t0, 200(sp)
    li t0, 1
    lw t1, 200(sp)
    sw t0, 0(t1)
    li t0, 2
    lw t1, 152(sp)
    sw t0, 0(t1)
    li t0, 2
    lw t1, 160(sp)
    sw t0, 0(t1)
    j .L4998
.L4998:
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 204(sp)
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 208(sp)
    lw t0, 204(sp)
    lw t1, 208(sp)
    slt t0, t0, t1
    sw t0, 212(sp)
    lw t0, 212(sp)
    bnez t0, .L5008
    j .L5117
.L5008:
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 216(sp)
    lw t0, 72(sp)
    lw t1, 216(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 220(sp)
    li t0, 0
    lw t1, 220(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 168(sp)
    sw t0, 0(t1)
    j .L5021
.L5021:
    lw t0, 168(sp)
    lw t0, 0(t0)
    sw t0, 224(sp)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 228(sp)
    lw t0, 224(sp)
    lw t1, 228(sp)
    slt t0, t0, t1
    sw t0, 232(sp)
    lw t0, 232(sp)
    bnez t0, .L5031
    j .L5088
.L5031:
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 236(sp)
    lw t0, 72(sp)
    lw t1, 236(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 240(sp)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 244(sp)
    lw t0, 72(sp)
    lw t1, 244(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 248(sp)
    lw t0, 248(sp)
    lw t0, 0(t0)
    sw t0, 252(sp)
    lw t0, 168(sp)
    lw t0, 0(t0)
    sw t0, 256(sp)
    lw t0, 72(sp)
    lw t1, 256(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 260(sp)
    lw t0, 260(sp)
    lw t0, 0(t0)
    sw t0, 264(sp)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 268(sp)
    lw t0, 268(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 272(sp)
    lw t0, 168(sp)
    lw t0, 0(t0)
    sw t0, 276(sp)
    lw t0, 272(sp)
    lw t1, 276(sp)
    sub t0, t0, t1
    sw t0, 280(sp)
    lw t0, 72(sp)
    lw t1, 280(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 284(sp)
    lw t0, 284(sp)
    lw t0, 0(t0)
    sw t0, 288(sp)
    lw t0, 264(sp)
    lw t1, 288(sp)
    mul t0, t0, t1
    sw t0, 292(sp)
    lw t0, 252(sp)
    lw t1, 292(sp)
    add t0, t0, t1
    sw t0, 296(sp)
    lw t0, 296(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 300(sp)
    lw t0, 300(sp)
    lw t1, 240(sp)
    sw t0, 0(t1)
    lw t0, 168(sp)
    lw t0, 0(t0)
    sw t0, 304(sp)
    lw t0, 304(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 308(sp)
    lw t0, 308(sp)
    lw t1, 168(sp)
    sw t0, 0(t1)
    j .L5021
.L5088:
    lw t0, 152(sp)
    lw t0, 0(t0)
    sw t0, 312(sp)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 316(sp)
    lw t0, 72(sp)
    lw t1, 316(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 320(sp)
    lw t0, 320(sp)
    lw t0, 0(t0)
    sw t0, 324(sp)
    lw t0, 312(sp)
    lw t1, 324(sp)
    add t0, t0, t1
    sw t0, 328(sp)
    lw t0, 328(sp)
    li t1, 1000000
    rem t0, t0, t1
    sw t0, 332(sp)
    lw t0, 332(sp)
    lw t1, 152(sp)
    sw t0, 0(t1)
    lw t0, 160(sp)
    lw t0, 0(t0)
    sw t0, 336(sp)
    lw t0, 336(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 340(sp)
    lw t0, 340(sp)
    lw t1, 160(sp)
    sw t0, 0(t1)
    j .L4998
.L5117:
    lw t0, 152(sp)
    lw t0, 0(t0)
    sw t0, 344(sp)
    lw t0, 344(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 348(sp)
    lw a0, 348(sp)
    j .L47
.L47:
    lw ra, 364(sp)
    lw s0, 360(sp)
    addi sp, sp, 368
    jr ra
    .globl performCryptographicOperations
    .type performCryptographicOperations, @function
performCryptographicOperations:
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
    li a0, 3009
    call printlnInt
    call performRSAOperations
    sw a0, 32(sp)
    lw t0, 32(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw a0, 36(sp)
    call printlnInt
    call performModularInverse
    sw a0, 40(sp)
    lw t0, 40(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw a0, 44(sp)
    call printlnInt
    call performPrimalityTesting
    sw a0, 48(sp)
    lw t0, 48(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw a0, 52(sp)
    call printlnInt
    call performHashOperations
    sw a0, 56(sp)
    lw t0, 56(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw a0, 60(sp)
    call printlnInt
    li a0, 3010
    call printlnInt
    lw a0, 64(sp)
    j .L48
.L48:
    lw ra, 76(sp)
    lw s0, 72(sp)
    addi sp, sp, 80
    jr ra
    .globl performRSAOperations
    .type performRSAOperations, @function
performRSAOperations:
    addi sp, sp, -224
    sw ra, 220(sp)
    sw s0, 216(sp)
    addi s0, sp, 224
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
    li t0, 0
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 61
    lw t1, 12(sp)
    sw t0, 0(t1)
    li t0, 53
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    mul t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 96(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 104(sp)
    lw t0, 96(sp)
    lw t1, 104(sp)
    mul t0, t0, t1
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 17
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw a0, 112(sp)
    lw a1, 116(sp)
    call modularInverse
    sw a0, 120(sp)
    lw t0, 120(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    li t0, 2
    lw t1, 60(sp)
    sw t0, 0(t1)
    j .L5216
.L5216:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 100
    slt t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    bnez t0, .L5224
    j .L5274
.L5224:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw a0, 132(sp)
    lw a1, 136(sp)
    lw a2, 140(sp)
    call modularPower
    sw a0, 144(sp)
    lw t0, 144(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 152(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 156(sp)
    lw a0, 148(sp)
    lw a1, 152(sp)
    lw a2, 156(sp)
    call modularPower
    sw a0, 160(sp)
    lw t0, 160(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 168(sp)
    lw t0, 164(sp)
    lw t1, 168(sp)
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 172(sp)
    lw t0, 172(sp)
    bnez t0, .L5258
    j .L5267
.L5258:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t1, 176(sp)
    add t0, t0, t1
    sw t0, 184(sp)
    lw t0, 184(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    j .L5267
.L5267:
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 188(sp)
    lw t0, 188(sp)
    li t1, 7
    add t0, t0, t1
    sw t0, 192(sp)
    lw t0, 192(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    j .L5216
.L5274:
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 196(sp)
    lw t0, 196(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 200(sp)
    lw a0, 200(sp)
    j .L49
.L49:
    lw ra, 220(sp)
    lw s0, 216(sp)
    addi sp, sp, 224
    jr ra
    .globl modularInverse
    .type modularInverse, @function
modularInverse:
    addi sp, sp, -208
    sw ra, 204(sp)
    sw s0, 200(sp)
    addi s0, sp, 208
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
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 80(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    li t0, 1
    lw t1, 44(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 52(sp)
    sw t0, 0(t1)
    j .L5303
.L5303:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 92(sp)
    lw t0, 92(sp)
    bnez t0, .L5311
    j .L5382
.L5311:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 96(sp)
    lw t1, 100(sp)
    div t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 116(sp)
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 116(sp)
    lw t1, 120(sp)
    mul t0, t0, t1
    sw t0, 124(sp)
    lw t0, 112(sp)
    lw t1, 124(sp)
    sub t0, t0, t1
    sw t0, 128(sp)
    lw t0, 128(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw t0, 132(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 140(sp)
    lw t0, 60(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 148(sp)
    lw t0, 144(sp)
    lw t1, 148(sp)
    mul t0, t0, t1
    sw t0, 152(sp)
    lw t0, 140(sp)
    lw t1, 152(sp)
    sub t0, t0, t1
    sw t0, 156(sp)
    lw t0, 156(sp)
    lw t1, 52(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 160(sp)
    lw t0, 160(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L5303
.L5382:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 164(sp)
    lw t0, 164(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 168(sp)
    lw t0, 168(sp)
    bnez t0, .L5393
    j .L5402
.L5393:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 172(sp)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 176(sp)
    lw t0, 176(sp)
    lw t1, 172(sp)
    add t0, t0, t1
    sw t0, 180(sp)
    lw t0, 180(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    j .L5402
.L5402:
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 184(sp)
    lw a0, 184(sp)
    j .L50
.L50:
    lw ra, 204(sp)
    lw s0, 200(sp)
    addi sp, sp, 208
    jr ra
    .globl performModularInverse
    .type performModularInverse, @function
performModularInverse:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    addi t0, sp, 16
    sw t0, 20(sp)
    addi t0, sp, 24
    sw t0, 28(sp)
    li t0, 0
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 97
    lw t1, 12(sp)
    sw t0, 0(t1)
    li t0, 2
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L5415
.L5415:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 32(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 32(sp)
    lw t1, 36(sp)
    slt t0, t0, t1
    sw t0, 40(sp)
    lw t0, 40(sp)
    bnez t0, .L5425
    j .L5475
.L5425:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw a0, 44(sp)
    lw a1, 48(sp)
    call euclideanGCD
    sw a0, 52(sp)
    lw t0, 52(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 56(sp)
    lw t0, 56(sp)
    bnez t0, .L5440
    j .L5468
.L5440:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw a0, 60(sp)
    lw a1, 64(sp)
    call modularInverse
    sw a0, 68(sp)
    lw t0, 68(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 72(sp)
    lw t1, 76(sp)
    add t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    j .L5468
.L5468:
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    j .L5415
.L5475:
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw a0, 96(sp)
    j .L51
.L51:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl performPrimalityTesting
    .type performPrimalityTesting, @function
performPrimalityTesting:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)
    addi s0, sp, 64
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 12(sp)
    li t0, 0
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 3
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L5486
.L5486:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 16(sp)
    lw t0, 16(sp)
    li t1, 500
    slt t0, t0, t1
    sw t0, 20(sp)
    lw t0, 20(sp)
    bnez t0, .L5494
    j .L5521
.L5494:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 24(sp)
    lw a0, 24(sp)
    li a1, 5
    call fermatPrimalityTest
    sw a0, 28(sp)
    lw t0, 28(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 32(sp)
    lw t0, 32(sp)
    bnez t0, .L5507
    j .L5514
.L5507:
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 36(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    j .L5514
.L5514:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw t0, 44(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 48(sp)
    lw t0, 48(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L5486
.L5521:
    lw t0, 4(sp)
    lw t0, 0(t0)
    sw t0, 52(sp)
    lw a0, 52(sp)
    j .L52
.L52:
    lw ra, 60(sp)
    lw s0, 56(sp)
    addi sp, sp, 64
    jr ra
    .globl fermatPrimalityTest
    .type fermatPrimalityTest, @function
fermatPrimalityTest:
    addi sp, sp, -160
    sw ra, 156(sp)
    sw s0, 152(sp)
    addi s0, sp, 160
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
    addi t0, sp, 40
    sw t0, 44(sp)
    lw t0, 0(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, 1
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 52(sp)
    lw t0, 52(sp)
    bnez t0, .L5539
    j .L5541
.L5539:
    li a0, 0
    j .L53
.L5541:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 56(sp)
    li t1, 3
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 60(sp)
    lw t0, 60(sp)
    bnez t0, .L5552
    j .L5554
.L5552:
    li a0, 1
    j .L53
.L5554:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 2
    rem t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 72(sp)
    lw t0, 72(sp)
    bnez t0, .L5569
    j .L5571
.L5569:
    li a0, 0
    j .L53
.L5571:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L5579
.L5579:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 20(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 80(sp)
    lw t1, 84(sp)
    slt t0, t0, t1
    sw t0, 88(sp)
    lw t0, 88(sp)
    bnez t0, .L5589
    j .L5649
.L5589:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw a0, 92(sp)
    call updateSeed
    sw a0, 96(sp)
    lw t0, 96(sp)
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 104(sp)
    li t1, 3
    sub t0, t0, t1
    sw t0, 108(sp)
    lw t0, 100(sp)
    lw t1, 108(sp)
    rem t0, t0, t1
    sw t0, 112(sp)
    li t0, 2
    lw t1, 112(sp)
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t1, 44(sp)
    sw t0, 0(t1)
    lw t0, 44(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 124(sp)
    lw t0, 124(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 128(sp)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 132(sp)
    lw a0, 120(sp)
    lw a1, 128(sp)
    lw a2, 132(sp)
    call modularPower
    sw a0, 136(sp)
    lw t0, 136(sp)
    li t1, 1
    sub t0, t0, t1
    snez t0, t0
    sw t0, 140(sp)
    lw t0, 140(sp)
    bnez t0, .L5640
    j .L5642
.L5640:
    li a0, 0
    j .L53
.L5642:
    lw t0, 36(sp)
    lw t0, 0(t0)
    sw t0, 144(sp)
    lw t0, 144(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 148(sp)
    lw t0, 148(sp)
    lw t1, 36(sp)
    sw t0, 0(t1)
    j .L5579
.L5649:
    li a0, 1
    j .L53
.L53:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl performHashOperations
    .type performHashOperations, @function
performHashOperations:
    li t0, -2592
    add sp, sp, t0
    li t0, 2588
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 2584
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 2592
    add s0, sp, t0
    addi t0, sp, 0
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 408(sp)
    addi t0, sp, 412
    sw t0, 416(sp)
    addi t0, sp, 420
    sw t0, 820(sp)
    addi t0, sp, 824
    sw t0, 828(sp)
    addi t0, sp, 832
    sw t0, 836(sp)
    addi t0, sp, 840
    sw t0, 1240(sp)
    addi t0, sp, 1244
    sw t0, 1248(sp)
    addi t0, sp, 1252
    sw t0, 1652(sp)
    addi t0, sp, 1656
    sw t0, 1660(sp)
    addi t0, sp, 1664
    li t3, 2064
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2068
    add t0, sp, t1
    li t3, 2072
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 2076
    add t0, sp, t1
    li t3, 2476
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 100
    lw t1, 4(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 416(sp)
    sw t0, 0(t1)
    j .L5657
.L5657:
    lw t0, 416(sp)
    lw t0, 0(t0)
    li t3, 2480
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2480
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 100
    slt t0, t0, t1
    li t3, 2484
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2484
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L5661
    j .L5662
.L5661:
    lw t0, 416(sp)
    lw t0, 0(t0)
    li t3, 2488
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 820(sp)
    li t3, 2488
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2492
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 2492
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 416(sp)
    lw t0, 0(t0)
    li t3, 2496
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2496
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2500
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 416(sp)
    sw t0, 0(t1)
    j .L5657
.L5662:
    lw a0, 408(sp)
    lw a1, 820(sp)
    li a2, 400
    call memcpy
    li t0, 0
    lw t1, 828(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 2504
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 408(sp)
    li t3, 2504
    add t3, t3, sp
    lw a1, 0(t3)
    call initializeHashInput
    lw a0, 1240(sp)
    lw a1, 408(sp)
    li a2, 400
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 2508
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 1240(sp)
    li t3, 2508
    add t3, t3, sp
    lw a1, 0(t3)
    call djb2Hash
    li t3, 2512
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 2512
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 836(sp)
    sw t0, 0(t1)
    lw a0, 1652(sp)
    lw a1, 408(sp)
    li a2, 400
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 2516
    add t3, t3, sp
    sw t0, 0(t3)
    lw a0, 1652(sp)
    li t3, 2516
    add t3, t3, sp
    lw a1, 0(t3)
    call sdbmHash
    li t3, 2520
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 2520
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 1248(sp)
    sw t0, 0(t1)
    li t3, 2064
    add t3, t3, sp
    lw a0, 0(t3)
    lw a1, 408(sp)
    li a2, 400
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 2524
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2064
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 2524
    add t3, t3, sp
    lw a1, 0(t3)
    call fnvHash
    li t3, 2528
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 2528
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 1660(sp)
    sw t0, 0(t1)
    lw t0, 836(sp)
    lw t0, 0(t0)
    li t3, 2532
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1248(sp)
    lw t0, 0(t0)
    li t3, 2536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2532
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2536
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 2540
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1660(sp)
    lw t0, 0(t0)
    li t3, 2544
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2540
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2544
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 2548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2548
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 2552
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2552
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 828(sp)
    sw t0, 0(t1)
    li t3, 2476
    add t3, t3, sp
    lw a0, 0(t3)
    lw a1, 408(sp)
    li a2, 400
    call memcpy
    lw t0, 4(sp)
    lw t0, 0(t0)
    li t3, 2556
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2476
    add t3, t3, sp
    lw a0, 0(t3)
    li t3, 2556
    add t3, t3, sp
    lw a1, 0(t3)
    call testHashDistribution
    li t3, 2560
    add t3, t3, sp
    sw a0, 0(t3)
    li t3, 2560
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2072
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 828(sp)
    lw t0, 0(t0)
    li t3, 2564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2568
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2564
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2568
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 2572
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2572
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 10000
    rem t0, t0, t1
    li t3, 2576
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2576
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 828(sp)
    sw t0, 0(t1)
    lw t0, 828(sp)
    lw t0, 0(t0)
    li t3, 2580
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2580
    add t3, t3, sp
    lw a0, 0(t3)
    j .L54
.L54:
    li t0, 2588
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 2584
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 2592
    add sp, sp, t0
    jr ra
    .globl updateSeed
    .type updateSeed, @function
updateSeed:
    addi sp, sp, -64
    sw ra, 60(sp)
    sw s0, 56(sp)
    addi s0, sp, 64
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
    li t1, 1103
    mul t0, t0, t1
    sw t0, 16(sp)
    lw t0, 16(sp)
    li t1, 4721
    add t0, t0, t1
    sw t0, 20(sp)
    lw t0, 20(sp)
    li t1, 1048583
    rem t0, t0, t1
    sw t0, 24(sp)
    lw t0, 24(sp)
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
    bnez t0, .L5789
    j .L5799
.L5789:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    li t0, 0
    lw t1, 36(sp)
    sub t0, t0, t1
    sw t0, 40(sp)
    lw t0, 40(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    j .L5799
.L5799:
    lw t0, 8(sp)
    lw t0, 0(t0)
    sw t0, 44(sp)
    lw a0, 44(sp)
    j .L55
.L55:
    lw ra, 60(sp)
    lw s0, 56(sp)
    addi sp, sp, 64
    jr ra
    .globl initializeHashInput
    .type initializeHashInput, @function
initializeHashInput:
    addi sp, sp, -96
    sw ra, 92(sp)
    sw s0, 88(sp)
    addi s0, sp, 96
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 42
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L5809
.L5809:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L5819
    j .L5851
.L5819:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw a0, 48(sp)
    call updateSeed
    sw a0, 52(sp)
    lw t0, 52(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 0(sp)
    lw t1, 56(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 60(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 256
    rem t0, t0, t1
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L5809
.L5851:
    lw a0, 80(sp)
    j .L56
.L56:
    lw ra, 92(sp)
    lw s0, 88(sp)
    addi sp, sp, 96
    jr ra
    .globl djb2Hash
    .type djb2Hash, @function
djb2Hash:
    addi sp, sp, -112
    sw ra, 108(sp)
    sw s0, 104(sp)
    addi s0, sp, 112
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
    lw t0, 0(sp)
    lw t1, 8(sp)
    sw t0, 0(t1)
    lw t0, 4(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 5381
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L5860
.L5860:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L5870
    j .L5914
.L5870:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 48(sp)
    li t1, 5
    sll t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 56(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 56(sp)
    lw t1, 60(sp)
    add t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 68(sp)
    lw t0, 32(sp)
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
    lw t0, 68(sp)
    lw t1, 80(sp)
    add t0, t0, t1
    sw t0, 84(sp)
    lw t0, 84(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L5860
.L5914:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 100(sp)
    lw a0, 100(sp)
    j .L57
.L57:
    lw ra, 108(sp)
    lw s0, 104(sp)
    addi sp, sp, 112
    jr ra
    .globl sdbmHash
    .type sdbmHash, @function
sdbmHash:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
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
    j .L5935
.L5935:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 36(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 40(sp)
    lw t0, 36(sp)
    lw t1, 40(sp)
    slt t0, t0, t1
    sw t0, 44(sp)
    lw t0, 44(sp)
    bnez t0, .L5945
    j .L5999
.L5945:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 48(sp)
    lw t0, 0(sp)
    lw t1, 48(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 52(sp)
    lw t0, 52(sp)
    lw t0, 0(t0)
    sw t0, 56(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 60(sp)
    lw t0, 60(sp)
    li t1, 6
    sll t0, t0, t1
    sw t0, 64(sp)
    lw t0, 64(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 68(sp)
    lw t0, 56(sp)
    lw t1, 68(sp)
    add t0, t0, t1
    sw t0, 72(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 16
    sll t0, t0, t1
    sw t0, 80(sp)
    lw t0, 80(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 84(sp)
    lw t0, 72(sp)
    lw t1, 84(sp)
    add t0, t0, t1
    sw t0, 88(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 92(sp)
    lw t0, 88(sp)
    lw t1, 92(sp)
    sub t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 100(sp)
    lw t0, 100(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 104(sp)
    lw t0, 104(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    j .L5935
.L5999:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 112(sp)
    lw a0, 112(sp)
    j .L58
.L58:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl fnvHash
    .type fnvHash, @function
fnvHash:
    addi sp, sp, -128
    sw ra, 124(sp)
    sw s0, 120(sp)
    addi s0, sp, 128
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
    li t0, 16777619
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, -2128831035
    lw t1, 32(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 40(sp)
    sw t0, 0(t1)
    j .L6022
.L6022:
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
    bnez t0, .L6032
    j .L6080
.L6032:
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
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 68(sp)
    lw t0, 68(sp)
    lw t1, 64(sp)
    xor t0, t0, t1
    sw t0, 72(sp)
    lw t0, 72(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 76(sp)
    lw t0, 76(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 80(sp)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 84(sp)
    lw t0, 84(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 88(sp)
    lw t0, 80(sp)
    lw t1, 88(sp)
    mul t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 96(sp)
    lw t0, 96(sp)
    lw t1, 32(sp)
    sw t0, 0(t1)
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
    j .L6022
.L6080:
    lw t0, 32(sp)
    lw t0, 0(t0)
    sw t0, 108(sp)
    lw t0, 108(sp)
    li t1, 65536
    rem t0, t0, t1
    sw t0, 112(sp)
    lw a0, 112(sp)
    j .L59
.L59:
    lw ra, 124(sp)
    lw s0, 120(sp)
    addi sp, sp, 128
    jr ra
    .globl testHashDistribution
    .type testHashDistribution, @function
testHashDistribution:
    addi sp, sp, -1424
    sw ra, 1420(sp)
    sw s0, 1416(sp)
    addi s0, sp, 1424
    sw a0, 0(sp)
    sw a1, 4(sp)
    addi t0, sp, 8
    sw t0, 8(sp)
    addi t0, sp, 12
    sw t0, 16(sp)
    addi t0, sp, 20
    sw t0, 24(sp)
    addi t0, sp, 28
    sw t0, 428(sp)
    addi t0, sp, 432
    sw t0, 436(sp)
    addi t0, sp, 440
    sw t0, 840(sp)
    addi t0, sp, 844
    sw t0, 848(sp)
    addi t0, sp, 852
    sw t0, 856(sp)
    addi t0, sp, 860
    sw t0, 864(sp)
    addi t0, sp, 868
    sw t0, 1268(sp)
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
    lw t1, 436(sp)
    sw t0, 0(t1)
    j .L6106
.L6106:
    lw t0, 436(sp)
    lw t0, 0(t0)
    sw t0, 1272(sp)
    lw t0, 1272(sp)
    li t1, 100
    slt t0, t0, t1
    sw t0, 1276(sp)
    lw t0, 1276(sp)
    bnez t0, .L6110
    j .L6111
.L6110:
    lw t0, 436(sp)
    lw t0, 0(t0)
    sw t0, 1280(sp)
    lw t0, 840(sp)
    lw t1, 1280(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1284(sp)
    li t0, 0
    lw t1, 1284(sp)
    sw t0, 0(t1)
    lw t0, 436(sp)
    lw t0, 0(t0)
    sw t0, 1288(sp)
    lw t0, 1288(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1292(sp)
    lw t0, 1292(sp)
    lw t1, 436(sp)
    sw t0, 0(t1)
    j .L6106
.L6111:
    lw a0, 428(sp)
    lw a1, 840(sp)
    li a2, 400
    call memcpy
    li t0, 1
    lw t1, 848(sp)
    sw t0, 0(t1)
    j .L6119
.L6119:
    lw t0, 848(sp)
    lw t0, 0(t0)
    sw t0, 1296(sp)
    lw t0, 1296(sp)
    li t1, 10
    slt t0, t1, t0
    xori t0, t0, 1
    sw t0, 1300(sp)
    lw t0, 1300(sp)
    bnez t0, .L6127
    j .L6221
.L6127:
    li t0, 0
    lw t1, 856(sp)
    sw t0, 0(t1)
    j .L6131
.L6131:
    lw t0, 856(sp)
    lw t0, 0(t0)
    sw t0, 1304(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 1308(sp)
    lw t0, 1304(sp)
    lw t1, 1308(sp)
    slt t0, t0, t1
    sw t0, 1312(sp)
    lw t0, 1312(sp)
    bnez t0, .L6141
    j .L6163
.L6141:
    lw t0, 856(sp)
    lw t0, 0(t0)
    sw t0, 1316(sp)
    lw t0, 428(sp)
    lw t1, 1316(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1320(sp)
    lw t0, 856(sp)
    lw t0, 0(t0)
    sw t0, 1324(sp)
    lw t0, 0(sp)
    lw t1, 1324(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1328(sp)
    lw t0, 1328(sp)
    lw t0, 0(t0)
    sw t0, 1332(sp)
    lw t0, 1332(sp)
    lw t1, 1320(sp)
    sw t0, 0(t1)
    lw t0, 856(sp)
    lw t0, 0(t0)
    sw t0, 1336(sp)
    lw t0, 1336(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1340(sp)
    lw t0, 1340(sp)
    lw t1, 856(sp)
    sw t0, 0(t1)
    j .L6131
.L6163:
    lw t0, 848(sp)
    lw t0, 0(t0)
    sw t0, 1344(sp)
    lw t0, 1344(sp)
    li t1, 7
    mul t0, t0, t1
    sw t0, 1348(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 1352(sp)
    lw t0, 1348(sp)
    lw t1, 1352(sp)
    rem t0, t0, t1
    sw t0, 1356(sp)
    lw t0, 428(sp)
    lw t1, 1356(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1360(sp)
    lw t0, 848(sp)
    lw t0, 0(t0)
    sw t0, 1364(sp)
    lw t0, 1360(sp)
    lw t0, 0(t0)
    sw t0, 1368(sp)
    lw t0, 1368(sp)
    lw t1, 1364(sp)
    add t0, t0, t1
    sw t0, 1372(sp)
    lw t0, 1372(sp)
    lw t1, 1360(sp)
    sw t0, 0(t1)
    lw a0, 1268(sp)
    lw a1, 428(sp)
    li a2, 400
    call memcpy
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 1376(sp)
    lw a0, 1268(sp)
    lw a1, 1376(sp)
    call djb2Hash
    sw a0, 1380(sp)
    lw t0, 1380(sp)
    lw t1, 864(sp)
    sw t0, 0(t1)
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 1384(sp)
    lw t0, 864(sp)
    lw t0, 0(t0)
    sw t0, 1388(sp)
    lw t0, 1384(sp)
    lw t1, 1388(sp)
    add t0, t0, t1
    sw t0, 1392(sp)
    lw t0, 1392(sp)
    li t1, 10000
    rem t0, t0, t1
    sw t0, 1396(sp)
    lw t0, 1396(sp)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 848(sp)
    lw t0, 0(t0)
    sw t0, 1400(sp)
    lw t0, 1400(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1404(sp)
    lw t0, 1404(sp)
    lw t1, 848(sp)
    sw t0, 0(t1)
    j .L6119
.L6221:
    lw t0, 24(sp)
    lw t0, 0(t0)
    sw t0, 1408(sp)
    lw a0, 1408(sp)
    j .L60
.L60:
    lw ra, 1420(sp)
    lw s0, 1416(sp)
    addi sp, sp, 1424
    jr ra
