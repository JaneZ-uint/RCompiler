    .text
    .globl init_vm
    .type init_vm, @function
init_vm:
    addi sp, sp, -160
    sw ra, 156(sp)
    sw s0, 152(sp)
    addi s0, sp, 160
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)
    sw a7, 28(sp)
    addi t0, sp, 32
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
    sw t0, 60(sp)
    addi t0, sp, 64
    sw t0, 68(sp)
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
    lw t0, 28(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L32
.L32:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 72(sp)
    lw t0, 72(sp)
    li t1, 16
    slt t0, t0, t1
    sw t0, 76(sp)
    lw t0, 76(sp)
    bnez t0, .L41
    j .L64
.L41:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 80(sp)
    lw t0, 0(sp)
    lw t1, 80(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 84(sp)
    li t0, 0
    lw t1, 84(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 88(sp)
    lw t0, 88(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 92(sp)
    lw t0, 92(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L32
.L64:
    li t0, 0
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L71
.L71:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 96(sp)
    lw t0, 96(sp)
    li t1, 2048
    slt t0, t0, t1
    sw t0, 100(sp)
    lw t0, 100(sp)
    bnez t0, .L80
    j .L103
.L80:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 104(sp)
    lw t0, 4(sp)
    lw t1, 104(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 108(sp)
    li t0, 0
    lw t1, 108(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 112(sp)
    lw t0, 112(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 116(sp)
    lw t0, 116(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L71
.L103:
    li t0, 0
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L110
.L110:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 120(sp)
    lw t0, 120(sp)
    li t1, 256
    slt t0, t0, t1
    sw t0, 124(sp)
    lw t0, 124(sp)
    bnez t0, .L119
    j .L142
.L119:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 128(sp)
    lw t0, 8(sp)
    lw t1, 128(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 132(sp)
    li t0, 0
    lw t1, 132(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 136(sp)
    lw t0, 136(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 140(sp)
    lw t0, 140(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    j .L110
.L142:
    li t0, 0
    lw t1, 12(sp)
    sw t0, 0(t1)
    li t0, 256
    lw t1, 16(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 20(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    li t0, 0
    lw t1, 28(sp)
    sw t0, 0(t1)
    lw a0, 144(sp)
    j .L1
.L1:
    lw ra, 156(sp)
    lw s0, 152(sp)
    addi sp, sp, 160
    jr ra
    .globl load_program
    .type load_program, @function
load_program:
    li t0, -2096
    add sp, sp, t0
    li t0, 2092
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 2088
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 2096
    add s0, sp, t0
    sw a0, 0(sp)
    addi t0, sp, 4
    sw t0, 4(sp)
    addi t0, sp, 8
    sw t0, 680(sp)
    addi t0, sp, 684
    sw t0, 1356(sp)
    addi t0, sp, 1360
    sw t0, 1364(sp)
    lw t0, 0(sp)
    lw t1, 4(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 0
    sw t0, 1368(sp)
    li t0, 2
    lw t1, 1368(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 4
    sw t0, 1372(sp)
    li t0, 0
    lw t1, 1372(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 8
    sw t0, 1376(sp)
    li t0, 15
    lw t1, 1376(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 12
    sw t0, 1380(sp)
    li t0, 2
    lw t1, 1380(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 16
    sw t0, 1384(sp)
    li t0, 1
    lw t1, 1384(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 20
    sw t0, 1388(sp)
    li t0, 0
    lw t1, 1388(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 24
    sw t0, 1392(sp)
    li t0, 2
    lw t1, 1392(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 28
    sw t0, 1396(sp)
    li t0, 2
    lw t1, 1396(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 32
    sw t0, 1400(sp)
    li t0, 1
    lw t1, 1400(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 36
    sw t0, 1404(sp)
    li t0, 1
    lw t1, 1404(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 40
    sw t0, 1408(sp)
    li t0, 4
    lw t1, 1408(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 44
    sw t0, 1412(sp)
    li t0, 0
    lw t1, 1412(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 48
    sw t0, 1416(sp)
    li t0, 25
    lw t1, 1416(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 52
    sw t0, 1420(sp)
    li t0, 4
    lw t1, 1420(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 56
    sw t0, 1424(sp)
    li t0, 1
    lw t1, 1424(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 60
    sw t0, 1428(sp)
    li t0, 18
    lw t1, 1428(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 64
    sw t0, 1432(sp)
    li t0, 36
    lw t1, 1432(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 68
    sw t0, 1436(sp)
    li t0, 0
    lw t1, 1436(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 72
    sw t0, 1440(sp)
    li t0, 1
    lw t1, 1440(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 76
    sw t0, 1444(sp)
    li t0, 3
    lw t1, 1444(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 80
    sw t0, 1448(sp)
    li t0, 1
    lw t1, 1448(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 84
    sw t0, 1452(sp)
    li t0, 1
    lw t1, 1452(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 88
    sw t0, 1456(sp)
    li t0, 1
    lw t1, 1456(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 92
    sw t0, 1460(sp)
    li t0, 2
    lw t1, 1460(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 96
    sw t0, 1464(sp)
    li t0, 3
    lw t1, 1464(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 100
    sw t0, 1468(sp)
    li t0, 2
    lw t1, 1468(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 104
    sw t0, 1472(sp)
    li t0, 3
    lw t1, 1472(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 108
    sw t0, 1476(sp)
    li t0, 0
    lw t1, 1476(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 112
    sw t0, 1480(sp)
    li t0, 4
    lw t1, 1480(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 116
    sw t0, 1484(sp)
    li t0, 4
    lw t1, 1484(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 120
    sw t0, 1488(sp)
    li t0, 1
    lw t1, 1488(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 124
    sw t0, 1492(sp)
    li t0, 0
    lw t1, 1492(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 128
    sw t0, 1496(sp)
    li t0, 25
    lw t1, 1496(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 132
    sw t0, 1500(sp)
    li t0, 4
    lw t1, 1500(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 136
    sw t0, 1504(sp)
    li t0, 1
    lw t1, 1504(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 140
    sw t0, 1508(sp)
    li t0, 19
    lw t1, 1508(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 144
    sw t0, 1512(sp)
    li t0, 21
    lw t1, 1512(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 148
    sw t0, 1516(sp)
    li t0, 0
    lw t1, 1516(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 152
    sw t0, 1520(sp)
    li t0, 26
    lw t1, 1520(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 156
    sw t0, 1524(sp)
    li t0, 1
    lw t1, 1524(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 160
    sw t0, 1528(sp)
    li t0, 0
    lw t1, 1528(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 164
    sw t0, 1532(sp)
    li t0, 2
    lw t1, 1532(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 168
    sw t0, 1536(sp)
    li t0, 0
    lw t1, 1536(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 172
    sw t0, 1540(sp)
    li t0, 10
    lw t1, 1540(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 176
    sw t0, 1544(sp)
    li t0, 13
    lw t1, 1544(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 180
    sw t0, 1548(sp)
    li t0, 0
    lw t1, 1548(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 184
    sw t0, 1552(sp)
    li t0, 0
    lw t1, 1552(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 188
    sw t0, 1556(sp)
    li t0, 22
    lw t1, 1556(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 192
    sw t0, 1560(sp)
    li t0, 81
    lw t1, 1560(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 196
    sw t0, 1564(sp)
    li t0, 0
    lw t1, 1564(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 200
    sw t0, 1568(sp)
    li t0, 14
    lw t1, 1568(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 204
    sw t0, 1572(sp)
    li t0, 1
    lw t1, 1572(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 208
    sw t0, 1576(sp)
    li t0, 0
    lw t1, 1576(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 212
    sw t0, 1580(sp)
    li t0, 26
    lw t1, 1580(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 216
    sw t0, 1584(sp)
    li t0, 1
    lw t1, 1584(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 220
    sw t0, 1588(sp)
    li t0, 0
    lw t1, 1588(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 224
    sw t0, 1592(sp)
    li t0, 2
    lw t1, 1592(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 228
    sw t0, 1596(sp)
    li t0, 5
    lw t1, 1596(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 232
    sw t0, 1600(sp)
    li t0, 12345
    lw t1, 1600(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 236
    sw t0, 1604(sp)
    li t0, 2
    lw t1, 1604(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 240
    sw t0, 1608(sp)
    li t0, 6
    lw t1, 1608(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 244
    sw t0, 1612(sp)
    li t0, 54321
    lw t1, 1612(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 248
    sw t0, 1616(sp)
    li t0, 7
    lw t1, 1616(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 252
    sw t0, 1620(sp)
    li t0, 5
    lw t1, 1620(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 256
    sw t0, 1624(sp)
    li t0, 6
    lw t1, 1624(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 260
    sw t0, 1628(sp)
    li t0, 0
    lw t1, 1628(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 264
    sw t0, 1632(sp)
    li t0, 26
    lw t1, 1632(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 268
    sw t0, 1636(sp)
    li t0, 5
    lw t1, 1636(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 272
    sw t0, 1640(sp)
    li t0, 0
    lw t1, 1640(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 276
    sw t0, 1644(sp)
    li t0, 2
    lw t1, 1644(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 280
    sw t0, 1648(sp)
    li t0, 5
    lw t1, 1648(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 284
    sw t0, 1652(sp)
    li t0, 12345
    lw t1, 1652(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 288
    sw t0, 1656(sp)
    li t0, 8
    lw t1, 1656(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 292
    sw t0, 1660(sp)
    li t0, 5
    lw t1, 1660(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 296
    sw t0, 1664(sp)
    li t0, 6
    lw t1, 1664(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 300
    sw t0, 1668(sp)
    li t0, 0
    lw t1, 1668(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 304
    sw t0, 1672(sp)
    li t0, 26
    lw t1, 1672(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 308
    sw t0, 1676(sp)
    li t0, 5
    lw t1, 1676(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 312
    sw t0, 1680(sp)
    li t0, 0
    lw t1, 1680(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 316
    sw t0, 1684(sp)
    li t0, 11
    lw t1, 1684(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 320
    sw t0, 1688(sp)
    li t0, 5
    lw t1, 1688(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 324
    sw t0, 1692(sp)
    li t0, 3
    lw t1, 1692(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 328
    sw t0, 1696(sp)
    li t0, 0
    lw t1, 1696(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 332
    sw t0, 1700(sp)
    li t0, 26
    lw t1, 1700(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 336
    sw t0, 1704(sp)
    li t0, 5
    lw t1, 1704(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 340
    sw t0, 1708(sp)
    li t0, 0
    lw t1, 1708(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 344
    sw t0, 1712(sp)
    li t0, 12
    lw t1, 1712(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 348
    sw t0, 1716(sp)
    li t0, 5
    lw t1, 1716(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 352
    sw t0, 1720(sp)
    li t0, 5
    lw t1, 1720(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 356
    sw t0, 1724(sp)
    li t0, 0
    lw t1, 1724(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 360
    sw t0, 1728(sp)
    li t0, 26
    lw t1, 1728(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 364
    sw t0, 1732(sp)
    li t0, 5
    lw t1, 1732(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 368
    sw t0, 1736(sp)
    li t0, 0
    lw t1, 1736(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 372
    sw t0, 1740(sp)
    li t0, 0
    lw t1, 1740(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 376
    sw t0, 1744(sp)
    li t0, 0
    lw t1, 1744(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 380
    sw t0, 1748(sp)
    li t0, 0
    lw t1, 1748(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 384
    sw t0, 1752(sp)
    li t0, 13
    lw t1, 1752(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 388
    sw t0, 1756(sp)
    li t0, 14
    lw t1, 1756(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 392
    sw t0, 1760(sp)
    li t0, 0
    lw t1, 1760(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 396
    sw t0, 1764(sp)
    li t0, 13
    lw t1, 1764(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 400
    sw t0, 1768(sp)
    li t0, 2
    lw t1, 1768(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 404
    sw t0, 1772(sp)
    li t0, 0
    lw t1, 1772(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 408
    sw t0, 1776(sp)
    li t0, 13
    lw t1, 1776(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 412
    sw t0, 1780(sp)
    li t0, 3
    lw t1, 1780(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 416
    sw t0, 1784(sp)
    li t0, 0
    lw t1, 1784(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 420
    sw t0, 1788(sp)
    li t0, 15
    lw t1, 1788(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 424
    sw t0, 1792(sp)
    li t0, 0
    lw t1, 1792(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 428
    sw t0, 1796(sp)
    li t0, 1
    lw t1, 1796(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 432
    sw t0, 1800(sp)
    li t0, 4
    lw t1, 1800(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 436
    sw t0, 1804(sp)
    li t0, 25
    lw t1, 1804(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 440
    sw t0, 1808(sp)
    li t0, 0
    lw t1, 1808(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 444
    sw t0, 1812(sp)
    li t0, 2
    lw t1, 1812(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 448
    sw t0, 1816(sp)
    li t0, 20
    lw t1, 1816(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 452
    sw t0, 1820(sp)
    li t0, 108
    lw t1, 1820(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 456
    sw t0, 1824(sp)
    li t0, 0
    lw t1, 1824(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 460
    sw t0, 1828(sp)
    li t0, 4
    lw t1, 1828(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 464
    sw t0, 1832(sp)
    li t0, 0
    lw t1, 1832(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 468
    sw t0, 1836(sp)
    li t0, 1
    lw t1, 1836(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 472
    sw t0, 1840(sp)
    li t0, 0
    lw t1, 1840(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 476
    sw t0, 1844(sp)
    li t0, 13
    lw t1, 1844(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 480
    sw t0, 1848(sp)
    li t0, 0
    lw t1, 1848(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 484
    sw t0, 1852(sp)
    li t0, 0
    lw t1, 1852(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 488
    sw t0, 1856(sp)
    li t0, 22
    lw t1, 1856(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 492
    sw t0, 1860(sp)
    li t0, 81
    lw t1, 1860(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 496
    sw t0, 1864(sp)
    li t0, 0
    lw t1, 1864(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 500
    sw t0, 1868(sp)
    li t0, 14
    lw t1, 1868(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 504
    sw t0, 1872(sp)
    li t0, 2
    lw t1, 1872(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 508
    sw t0, 1876(sp)
    li t0, 0
    lw t1, 1876(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 512
    sw t0, 1880(sp)
    li t0, 4
    lw t1, 1880(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 516
    sw t0, 1884(sp)
    li t0, 0
    lw t1, 1884(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 520
    sw t0, 1888(sp)
    li t0, 1
    lw t1, 1888(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 524
    sw t0, 1892(sp)
    li t0, 0
    lw t1, 1892(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 528
    sw t0, 1896(sp)
    li t0, 13
    lw t1, 1896(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 532
    sw t0, 1900(sp)
    li t0, 0
    lw t1, 1900(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 536
    sw t0, 1904(sp)
    li t0, 0
    lw t1, 1904(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 540
    sw t0, 1908(sp)
    li t0, 22
    lw t1, 1908(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 544
    sw t0, 1912(sp)
    li t0, 81
    lw t1, 1912(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 548
    sw t0, 1916(sp)
    li t0, 0
    lw t1, 1916(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 552
    sw t0, 1920(sp)
    li t0, 14
    lw t1, 1920(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 556
    sw t0, 1924(sp)
    li t0, 3
    lw t1, 1924(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 560
    sw t0, 1928(sp)
    li t0, 0
    lw t1, 1928(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 564
    sw t0, 1932(sp)
    li t0, 3
    lw t1, 1932(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 568
    sw t0, 1936(sp)
    li t0, 0
    lw t1, 1936(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 572
    sw t0, 1940(sp)
    li t0, 2
    lw t1, 1940(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 576
    sw t0, 1944(sp)
    li t0, 3
    lw t1, 1944(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 580
    sw t0, 1948(sp)
    li t0, 17
    lw t1, 1948(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 584
    sw t0, 1952(sp)
    li t0, 114
    lw t1, 1952(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 588
    sw t0, 1956(sp)
    li t0, 0
    lw t1, 1956(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 592
    sw t0, 1960(sp)
    li t0, 15
    lw t1, 1960(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 596
    sw t0, 1964(sp)
    li t0, 0
    lw t1, 1964(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 600
    sw t0, 1968(sp)
    li t0, 1
    lw t1, 1968(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 604
    sw t0, 1972(sp)
    li t0, 4
    lw t1, 1972(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 608
    sw t0, 1976(sp)
    li t0, 16
    lw t1, 1976(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 612
    sw t0, 1980(sp)
    li t0, 0
    lw t1, 1980(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 616
    sw t0, 1984(sp)
    li t0, 1
    lw t1, 1984(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 620
    sw t0, 1988(sp)
    li t0, 4
    lw t1, 1988(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 624
    sw t0, 1992(sp)
    li t0, 14
    lw t1, 1992(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 628
    sw t0, 1996(sp)
    li t0, 3
    lw t1, 1996(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 632
    sw t0, 2000(sp)
    li t0, 0
    lw t1, 2000(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 636
    sw t0, 2004(sp)
    li t0, 14
    lw t1, 2004(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 640
    sw t0, 2008(sp)
    li t0, 2
    lw t1, 2008(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 644
    sw t0, 2012(sp)
    li t0, 0
    lw t1, 2012(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 648
    sw t0, 2016(sp)
    li t0, 14
    lw t1, 2016(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 652
    sw t0, 2020(sp)
    li t0, 14
    lw t1, 2020(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 656
    sw t0, 2024(sp)
    li t0, 0
    lw t1, 2024(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 660
    sw t0, 2028(sp)
    li t0, 23
    lw t1, 2028(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 664
    sw t0, 2032(sp)
    li t0, 0
    lw t1, 2032(sp)
    sw t0, 0(t1)
    lw t0, 1356(sp)
    addi t0, t0, 668
    sw t0, 2036(sp)
    li t0, 0
    lw t1, 2036(sp)
    sw t0, 0(t1)
    lw t0, 680(sp)
    lw t1, 1356(sp)
    li t2, 672
    call memcpy
    li t0, 0
    lw t1, 1364(sp)
    sw t0, 0(t1)
    j .L353
.L353:
    lw t0, 1364(sp)
    lw t0, 0(t0)
    sw t0, 2040(sp)
    lw t0, 2040(sp)
    li t1, 168
    slt t0, t0, t1
    sw t0, 2044(sp)
    lw t0, 2044(sp)
    bnez t0, .L361
    j .L392
.L361:
    lw t0, 1364(sp)
    lw t0, 0(t0)
    li t3, 2048
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    li t3, 2048
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2052
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 1364(sp)
    lw t0, 0(t0)
    li t3, 2056
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 680(sp)
    li t3, 2056
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2060
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2064
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2064
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2052
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 1364(sp)
    lw t0, 0(t0)
    li t3, 2068
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2068
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2072
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2072
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 1364(sp)
    sw t0, 0(t1)
    j .L353
.L392:
    li t3, 2076
    add t3, t3, sp
    lw a0, 0(t3)
    j .L2
.L2:
    li t0, 2092
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 2088
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 2096
    add sp, sp, t0
    jr ra
    .globl fetch_decode_execute
    .type fetch_decode_execute, @function
fetch_decode_execute:
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
    sw a0, 0(sp)
    sw a1, 4(sp)
    sw a2, 8(sp)
    sw a3, 12(sp)
    sw a4, 16(sp)
    sw a5, 20(sp)
    sw a6, 24(sp)
    sw a7, 28(sp)
    addi t0, sp, 32
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
    sw t0, 156(sp)
    addi t0, sp, 160
    sw t0, 164(sp)
    addi t0, sp, 168
    sw t0, 172(sp)
    addi t0, sp, 176
    sw t0, 180(sp)
    addi t0, sp, 184
    sw t0, 188(sp)
    addi t0, sp, 192
    sw t0, 196(sp)
    addi t0, sp, 200
    sw t0, 204(sp)
    addi t0, sp, 208
    sw t0, 212(sp)
    addi t0, sp, 216
    sw t0, 220(sp)
    addi t0, sp, 224
    sw t0, 228(sp)
    addi t0, sp, 232
    sw t0, 236(sp)
    addi t0, sp, 240
    sw t0, 244(sp)
    addi t0, sp, 248
    sw t0, 252(sp)
    addi t0, sp, 256
    sw t0, 260(sp)
    addi t0, sp, 264
    sw t0, 268(sp)
    addi t0, sp, 272
    sw t0, 276(sp)
    addi t0, sp, 280
    sw t0, 284(sp)
    addi t0, sp, 288
    sw t0, 292(sp)
    addi t0, sp, 296
    sw t0, 300(sp)
    addi t0, sp, 304
    sw t0, 308(sp)
    addi t0, sp, 312
    sw t0, 316(sp)
    addi t0, sp, 320
    sw t0, 324(sp)
    addi t0, sp, 328
    sw t0, 332(sp)
    addi t0, sp, 336
    sw t0, 340(sp)
    addi t0, sp, 344
    sw t0, 348(sp)
    addi t0, sp, 352
    sw t0, 356(sp)
    addi t0, sp, 360
    sw t0, 364(sp)
    addi t0, sp, 368
    sw t0, 372(sp)
    addi t0, sp, 376
    sw t0, 380(sp)
    addi t0, sp, 384
    sw t0, 388(sp)
    addi t0, sp, 392
    sw t0, 396(sp)
    addi t0, sp, 400
    sw t0, 404(sp)
    addi t0, sp, 408
    sw t0, 412(sp)
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
    lw t0, 28(sp)
    lw t1, 60(sp)
    sw t0, 0(t1)
    j .L403
.L403:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 416(sp)
    lw t0, 416(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 420(sp)
    lw t0, 420(sp)
    bnez t0, .L413
    j .L2880
.L413:
    j .L419
.L419:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 424(sp)
    lw t0, 424(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 428(sp)
    li t1, 1
    sw t1, 432(sp)
    lw t0, 428(sp)
    bnez t0, .L441
    j .L429
.L429:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 436(sp)
    lw t0, 436(sp)
    li t1, 2048
    slt t0, t0, t1
    xori t0, t0, 1
    sw t0, 440(sp)
    lw t1, 440(sp)
    sw t1, 432(sp)
    j .L441
.L441:
    lw t0, 432(sp)
    bnez t0, .L445
    j .L452
.L445:
    li t0, 1
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L452
.L452:
    lw t0, 28(sp)
    lw t0, 0(t0)
    sw t0, 444(sp)
    lw t0, 444(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 448(sp)
    lw t0, 448(sp)
    bnez t0, .L464
    j .L465
.L464:
    j .L2879
.L465:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 452(sp)
    lw t0, 4(sp)
    lw t1, 452(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 456(sp)
    lw t0, 456(sp)
    lw t0, 0(t0)
    sw t0, 460(sp)
    lw t0, 460(sp)
    lw t1, 68(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 464(sp)
    lw t0, 464(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 468(sp)
    lw t0, 468(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 472(sp)
    lw t0, 472(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 476(sp)
    lw t0, 476(sp)
    bnez t0, .L500
    j .L507
.L500:
    li t0, 1
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L2878
.L507:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 480(sp)
    lw t0, 480(sp)
    li t1, 1
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 484(sp)
    lw t0, 484(sp)
    bnez t0, .L516
    j .L576
.L516:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 488(sp)
    lw t0, 4(sp)
    lw t1, 488(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 492(sp)
    lw t0, 492(sp)
    lw t0, 0(t0)
    sw t0, 496(sp)
    lw t0, 496(sp)
    lw t1, 76(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 500(sp)
    lw t0, 500(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 504(sp)
    lw t0, 4(sp)
    lw t1, 504(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 508(sp)
    lw t0, 508(sp)
    lw t0, 0(t0)
    sw t0, 512(sp)
    lw t0, 512(sp)
    lw t1, 84(sp)
    sw t0, 0(t1)
    lw t0, 76(sp)
    lw t0, 0(t0)
    sw t0, 516(sp)
    lw t0, 0(sp)
    lw t1, 516(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 520(sp)
    lw t0, 84(sp)
    lw t0, 0(t0)
    sw t0, 524(sp)
    lw t0, 0(sp)
    lw t1, 524(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 528(sp)
    lw t0, 528(sp)
    lw t0, 0(t0)
    sw t0, 532(sp)
    lw t0, 532(sp)
    lw t1, 520(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 536(sp)
    lw t0, 536(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 540(sp)
    lw t0, 540(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2877
.L576:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 544(sp)
    lw t0, 544(sp)
    li t1, 2
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 548(sp)
    lw t0, 548(sp)
    bnez t0, .L585
    j .L639
.L585:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 552(sp)
    lw t0, 4(sp)
    lw t1, 552(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 556(sp)
    lw t0, 556(sp)
    lw t0, 0(t0)
    sw t0, 560(sp)
    lw t0, 560(sp)
    lw t1, 92(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 564(sp)
    lw t0, 564(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 568(sp)
    lw t0, 4(sp)
    lw t1, 568(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 572(sp)
    lw t0, 572(sp)
    lw t0, 0(t0)
    sw t0, 576(sp)
    lw t0, 576(sp)
    lw t1, 100(sp)
    sw t0, 0(t1)
    lw t0, 92(sp)
    lw t0, 0(t0)
    sw t0, 580(sp)
    lw t0, 0(sp)
    lw t1, 580(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 584(sp)
    lw t0, 100(sp)
    lw t0, 0(t0)
    sw t0, 588(sp)
    lw t0, 588(sp)
    lw t1, 584(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 592(sp)
    lw t0, 592(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 596(sp)
    lw t0, 596(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2876
.L639:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 600(sp)
    lw t0, 600(sp)
    li t1, 3
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 604(sp)
    lw t0, 604(sp)
    bnez t0, .L648
    j .L869
.L648:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 608(sp)
    lw t0, 4(sp)
    lw t1, 608(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 612(sp)
    lw t0, 612(sp)
    lw t0, 0(t0)
    sw t0, 616(sp)
    lw t0, 616(sp)
    lw t1, 108(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 620(sp)
    lw t0, 620(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 624(sp)
    lw t0, 4(sp)
    lw t1, 624(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 628(sp)
    lw t0, 628(sp)
    lw t0, 0(t0)
    sw t0, 632(sp)
    lw t0, 632(sp)
    lw t1, 116(sp)
    sw t0, 0(t1)
    lw t0, 108(sp)
    lw t0, 0(t0)
    sw t0, 636(sp)
    lw t0, 0(sp)
    lw t1, 636(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 640(sp)
    lw t0, 640(sp)
    lw t0, 0(t0)
    sw t0, 644(sp)
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 648(sp)
    lw t0, 0(sp)
    lw t1, 648(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 652(sp)
    lw t0, 652(sp)
    lw t0, 0(t0)
    sw t0, 656(sp)
    lw t0, 644(sp)
    lw t1, 656(sp)
    add t0, t0, t1
    sw t0, 660(sp)
    lw t0, 660(sp)
    lw t1, 124(sp)
    sw t0, 0(t1)
    j .L702
.L702:
    j .L705
.L705:
    lw t0, 108(sp)
    lw t0, 0(t0)
    sw t0, 664(sp)
    lw t0, 0(sp)
    lw t1, 664(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 668(sp)
    lw t0, 668(sp)
    lw t0, 0(t0)
    sw t0, 672(sp)
    lw t0, 672(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 676(sp)
    li t1, 0
    sw t1, 680(sp)
    lw t0, 676(sp)
    bnez t0, .L719
    j .L734
.L719:
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 684(sp)
    lw t0, 0(sp)
    lw t1, 684(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 688(sp)
    lw t0, 688(sp)
    lw t0, 0(t0)
    sw t0, 692(sp)
    lw t0, 692(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 696(sp)
    lw t1, 696(sp)
    sw t1, 680(sp)
    j .L734
.L734:
    li t1, 0
    sw t1, 700(sp)
    lw t0, 680(sp)
    bnez t0, .L739
    j .L748
.L739:
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 704(sp)
    lw t0, 704(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 708(sp)
    lw t1, 708(sp)
    sw t1, 700(sp)
    j .L748
.L748:
    lw t0, 700(sp)
    bnez t0, .L752
    j .L759
.L752:
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L829
.L759:
    j .L764
.L764:
    j .L767
.L767:
    lw t0, 108(sp)
    lw t0, 0(t0)
    sw t0, 712(sp)
    lw t0, 0(sp)
    lw t1, 712(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 716(sp)
    lw t0, 716(sp)
    lw t0, 0(t0)
    sw t0, 720(sp)
    lw t0, 720(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 724(sp)
    li t1, 0
    sw t1, 728(sp)
    lw t0, 724(sp)
    bnez t0, .L781
    j .L796
.L781:
    lw t0, 116(sp)
    lw t0, 0(t0)
    sw t0, 732(sp)
    lw t0, 0(sp)
    lw t1, 732(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 736(sp)
    lw t0, 736(sp)
    lw t0, 0(t0)
    sw t0, 740(sp)
    lw t0, 740(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 744(sp)
    lw t1, 744(sp)
    sw t1, 728(sp)
    j .L796
.L796:
    li t1, 0
    sw t1, 748(sp)
    lw t0, 728(sp)
    bnez t0, .L801
    j .L810
.L801:
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 752(sp)
    lw t0, 752(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 756(sp)
    lw t1, 756(sp)
    sw t1, 748(sp)
    j .L810
.L810:
    lw t0, 748(sp)
    bnez t0, .L814
    j .L821
.L814:
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L828
.L821:
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L828
.L828:
    j .L829
.L829:
    lw t0, 108(sp)
    lw t0, 0(t0)
    sw t0, 760(sp)
    lw t0, 0(sp)
    lw t1, 760(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 764(sp)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 768(sp)
    lw t0, 768(sp)
    lw t1, 764(sp)
    sw t0, 0(t1)
    lw t0, 124(sp)
    lw t0, 0(t0)
    sw t0, 772(sp)
    lw t0, 772(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 776(sp)
    lw t0, 780(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 784(sp)
    lw t0, 784(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 788(sp)
    lw t0, 788(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2875
.L869:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 792(sp)
    lw t0, 792(sp)
    li t1, 4
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 796(sp)
    lw t0, 796(sp)
    bnez t0, .L878
    j .L1099
.L878:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 800(sp)
    lw t0, 4(sp)
    lw t1, 800(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 804(sp)
    lw t0, 804(sp)
    lw t0, 0(t0)
    sw t0, 808(sp)
    lw t0, 808(sp)
    lw t1, 132(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 812(sp)
    lw t0, 812(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 816(sp)
    lw t0, 4(sp)
    lw t1, 816(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 820(sp)
    lw t0, 820(sp)
    lw t0, 0(t0)
    sw t0, 824(sp)
    lw t0, 824(sp)
    lw t1, 140(sp)
    sw t0, 0(t1)
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 828(sp)
    lw t0, 0(sp)
    lw t1, 828(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 832(sp)
    lw t0, 832(sp)
    lw t0, 0(t0)
    sw t0, 836(sp)
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 840(sp)
    lw t0, 0(sp)
    lw t1, 840(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 844(sp)
    lw t0, 844(sp)
    lw t0, 0(t0)
    sw t0, 848(sp)
    lw t0, 836(sp)
    lw t1, 848(sp)
    sub t0, t0, t1
    sw t0, 852(sp)
    lw t0, 852(sp)
    lw t1, 148(sp)
    sw t0, 0(t1)
    j .L932
.L932:
    j .L935
.L935:
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 856(sp)
    lw t0, 0(sp)
    lw t1, 856(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 860(sp)
    lw t0, 860(sp)
    lw t0, 0(t0)
    sw t0, 864(sp)
    lw t0, 864(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 868(sp)
    li t1, 0
    sw t1, 872(sp)
    lw t0, 868(sp)
    bnez t0, .L949
    j .L964
.L949:
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 876(sp)
    lw t0, 0(sp)
    lw t1, 876(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 880(sp)
    lw t0, 880(sp)
    lw t0, 0(t0)
    sw t0, 884(sp)
    lw t0, 884(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 888(sp)
    lw t1, 888(sp)
    sw t1, 872(sp)
    j .L964
.L964:
    li t1, 0
    sw t1, 892(sp)
    lw t0, 872(sp)
    bnez t0, .L969
    j .L978
.L969:
    lw t0, 148(sp)
    lw t0, 0(t0)
    sw t0, 896(sp)
    lw t0, 896(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 900(sp)
    lw t1, 900(sp)
    sw t1, 892(sp)
    j .L978
.L978:
    lw t0, 892(sp)
    bnez t0, .L982
    j .L989
.L982:
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1059
.L989:
    j .L994
.L994:
    j .L997
.L997:
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 904(sp)
    lw t0, 0(sp)
    lw t1, 904(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 908(sp)
    lw t0, 908(sp)
    lw t0, 0(t0)
    sw t0, 912(sp)
    lw t0, 912(sp)
    li t1, 0
    slt t0, t0, t1
    sw t0, 916(sp)
    li t1, 0
    sw t1, 920(sp)
    lw t0, 916(sp)
    bnez t0, .L1011
    j .L1026
.L1011:
    lw t0, 140(sp)
    lw t0, 0(t0)
    sw t0, 924(sp)
    lw t0, 0(sp)
    lw t1, 924(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 928(sp)
    lw t0, 928(sp)
    lw t0, 0(t0)
    sw t0, 932(sp)
    lw t0, 932(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 936(sp)
    lw t1, 936(sp)
    sw t1, 920(sp)
    j .L1026
.L1026:
    li t1, 0
    sw t1, 940(sp)
    lw t0, 920(sp)
    bnez t0, .L1031
    j .L1040
.L1031:
    lw t0, 148(sp)
    lw t0, 0(t0)
    sw t0, 944(sp)
    lw t0, 944(sp)
    li t1, 0
    slt t0, t1, t0
    sw t0, 948(sp)
    lw t1, 948(sp)
    sw t1, 940(sp)
    j .L1040
.L1040:
    lw t0, 940(sp)
    bnez t0, .L1044
    j .L1051
.L1044:
    li t0, 1
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1058
.L1051:
    li t0, 0
    lw t1, 24(sp)
    sw t0, 0(t1)
    j .L1058
.L1058:
    j .L1059
.L1059:
    lw t0, 132(sp)
    lw t0, 0(t0)
    sw t0, 952(sp)
    lw t0, 0(sp)
    lw t1, 952(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 956(sp)
    lw t0, 148(sp)
    lw t0, 0(t0)
    sw t0, 960(sp)
    lw t0, 960(sp)
    lw t1, 956(sp)
    sw t0, 0(t1)
    lw t0, 148(sp)
    lw t0, 0(t0)
    sw t0, 964(sp)
    lw t0, 964(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 968(sp)
    lw t0, 972(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 976(sp)
    lw t0, 976(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 980(sp)
    lw t0, 980(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2874
.L1099:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 984(sp)
    lw t0, 984(sp)
    li t1, 5
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 988(sp)
    lw t0, 988(sp)
    bnez t0, .L1108
    j .L1198
.L1108:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 992(sp)
    lw t0, 4(sp)
    lw t1, 992(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 996(sp)
    lw t0, 996(sp)
    lw t0, 0(t0)
    sw t0, 1000(sp)
    lw t0, 1000(sp)
    lw t1, 156(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1004(sp)
    lw t0, 1004(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1008(sp)
    lw t0, 4(sp)
    lw t1, 1008(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1012(sp)
    lw t0, 1012(sp)
    lw t0, 0(t0)
    sw t0, 1016(sp)
    lw t0, 1016(sp)
    lw t1, 164(sp)
    sw t0, 0(t1)
    lw t0, 156(sp)
    lw t0, 0(t0)
    sw t0, 1020(sp)
    lw t0, 0(sp)
    lw t1, 1020(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1024(sp)
    lw t0, 156(sp)
    lw t0, 0(t0)
    sw t0, 1028(sp)
    lw t0, 0(sp)
    lw t1, 1028(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1032(sp)
    lw t0, 1032(sp)
    lw t0, 0(t0)
    sw t0, 1036(sp)
    lw t0, 164(sp)
    lw t0, 0(t0)
    sw t0, 1040(sp)
    lw t0, 0(sp)
    lw t1, 1040(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1044(sp)
    lw t0, 1044(sp)
    lw t0, 0(t0)
    sw t0, 1048(sp)
    lw t0, 1036(sp)
    lw t1, 1048(sp)
    mul t0, t0, t1
    sw t0, 1052(sp)
    lw t0, 1052(sp)
    lw t1, 1024(sp)
    sw t0, 0(t1)
    lw t0, 156(sp)
    lw t0, 0(t0)
    sw t0, 1056(sp)
    lw t0, 0(sp)
    lw t1, 1056(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1060(sp)
    lw t0, 1060(sp)
    lw t0, 0(t0)
    sw t0, 1064(sp)
    lw t0, 1064(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1068(sp)
    lw t0, 1072(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1076(sp)
    lw t0, 1076(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1080(sp)
    lw t0, 1080(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2873
.L1198:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1084(sp)
    lw t0, 1084(sp)
    li t1, 6
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1088(sp)
    lw t0, 1088(sp)
    bnez t0, .L1207
    j .L1321
.L1207:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1092(sp)
    lw t0, 4(sp)
    lw t1, 1092(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1096(sp)
    lw t0, 1096(sp)
    lw t0, 0(t0)
    sw t0, 1100(sp)
    lw t0, 1100(sp)
    lw t1, 172(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1104(sp)
    lw t0, 1104(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1108(sp)
    lw t0, 4(sp)
    lw t1, 1108(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1112(sp)
    lw t0, 1112(sp)
    lw t0, 0(t0)
    sw t0, 1116(sp)
    lw t0, 1116(sp)
    lw t1, 180(sp)
    sw t0, 0(t1)
    lw t0, 180(sp)
    lw t0, 0(t0)
    sw t0, 1120(sp)
    lw t0, 0(sp)
    lw t1, 1120(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1124(sp)
    lw t0, 1124(sp)
    lw t0, 0(t0)
    sw t0, 1128(sp)
    lw t0, 1128(sp)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    sw t0, 1132(sp)
    lw t0, 1132(sp)
    bnez t0, .L1249
    j .L1281
.L1249:
    lw t0, 172(sp)
    lw t0, 0(t0)
    sw t0, 1136(sp)
    lw t0, 0(sp)
    lw t1, 1136(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1140(sp)
    lw t0, 172(sp)
    lw t0, 0(t0)
    sw t0, 1144(sp)
    lw t0, 0(sp)
    lw t1, 1144(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1148(sp)
    lw t0, 1148(sp)
    lw t0, 0(t0)
    sw t0, 1152(sp)
    lw t0, 180(sp)
    lw t0, 0(t0)
    sw t0, 1156(sp)
    lw t0, 0(sp)
    lw t1, 1156(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1160(sp)
    lw t0, 1160(sp)
    lw t0, 0(t0)
    sw t0, 1164(sp)
    lw t0, 1152(sp)
    lw t1, 1164(sp)
    div t0, t0, t1
    sw t0, 1168(sp)
    lw t0, 1168(sp)
    lw t1, 1140(sp)
    sw t0, 0(t1)
    j .L1288
.L1281:
    li t0, 1
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L1288
.L1288:
    lw t0, 172(sp)
    lw t0, 0(t0)
    sw t0, 1172(sp)
    lw t0, 0(sp)
    lw t1, 1172(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1176(sp)
    lw t0, 1176(sp)
    lw t0, 0(t0)
    sw t0, 1180(sp)
    lw t0, 1180(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1184(sp)
    lw t0, 1188(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1192(sp)
    lw t0, 1192(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1196(sp)
    lw t0, 1196(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2872
.L1321:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1200(sp)
    lw t0, 1200(sp)
    li t1, 7
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1204(sp)
    lw t0, 1204(sp)
    bnez t0, .L1330
    j .L1420
.L1330:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1208(sp)
    lw t0, 4(sp)
    lw t1, 1208(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1212(sp)
    lw t0, 1212(sp)
    lw t0, 0(t0)
    sw t0, 1216(sp)
    lw t0, 1216(sp)
    lw t1, 188(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1220(sp)
    lw t0, 1220(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1224(sp)
    lw t0, 4(sp)
    lw t1, 1224(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1228(sp)
    lw t0, 1228(sp)
    lw t0, 0(t0)
    sw t0, 1232(sp)
    lw t0, 1232(sp)
    lw t1, 196(sp)
    sw t0, 0(t1)
    lw t0, 188(sp)
    lw t0, 0(t0)
    sw t0, 1236(sp)
    lw t0, 0(sp)
    lw t1, 1236(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1240(sp)
    lw t0, 188(sp)
    lw t0, 0(t0)
    sw t0, 1244(sp)
    lw t0, 0(sp)
    lw t1, 1244(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1248(sp)
    lw t0, 1248(sp)
    lw t0, 0(t0)
    sw t0, 1252(sp)
    lw t0, 196(sp)
    lw t0, 0(t0)
    sw t0, 1256(sp)
    lw t0, 0(sp)
    lw t1, 1256(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1260(sp)
    lw t0, 1260(sp)
    lw t0, 0(t0)
    sw t0, 1264(sp)
    lw t0, 1252(sp)
    lw t1, 1264(sp)
    and t0, t0, t1
    sw t0, 1268(sp)
    lw t0, 1268(sp)
    lw t1, 1240(sp)
    sw t0, 0(t1)
    lw t0, 188(sp)
    lw t0, 0(t0)
    sw t0, 1272(sp)
    lw t0, 0(sp)
    lw t1, 1272(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1276(sp)
    lw t0, 1276(sp)
    lw t0, 0(t0)
    sw t0, 1280(sp)
    lw t0, 1280(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1284(sp)
    lw t0, 1288(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1292(sp)
    lw t0, 1292(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1296(sp)
    lw t0, 1296(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2871
.L1420:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1300(sp)
    lw t0, 1300(sp)
    li t1, 8
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1304(sp)
    lw t0, 1304(sp)
    bnez t0, .L1429
    j .L1519
.L1429:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1308(sp)
    lw t0, 4(sp)
    lw t1, 1308(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1312(sp)
    lw t0, 1312(sp)
    lw t0, 0(t0)
    sw t0, 1316(sp)
    lw t0, 1316(sp)
    lw t1, 204(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1320(sp)
    lw t0, 1320(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1324(sp)
    lw t0, 4(sp)
    lw t1, 1324(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1328(sp)
    lw t0, 1328(sp)
    lw t0, 0(t0)
    sw t0, 1332(sp)
    lw t0, 1332(sp)
    lw t1, 212(sp)
    sw t0, 0(t1)
    lw t0, 204(sp)
    lw t0, 0(t0)
    sw t0, 1336(sp)
    lw t0, 0(sp)
    lw t1, 1336(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1340(sp)
    lw t0, 204(sp)
    lw t0, 0(t0)
    sw t0, 1344(sp)
    lw t0, 0(sp)
    lw t1, 1344(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1348(sp)
    lw t0, 1348(sp)
    lw t0, 0(t0)
    sw t0, 1352(sp)
    lw t0, 212(sp)
    lw t0, 0(t0)
    sw t0, 1356(sp)
    lw t0, 0(sp)
    lw t1, 1356(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1360(sp)
    lw t0, 1360(sp)
    lw t0, 0(t0)
    sw t0, 1364(sp)
    lw t0, 1352(sp)
    lw t1, 1364(sp)
    or t0, t0, t1
    sw t0, 1368(sp)
    lw t0, 1368(sp)
    lw t1, 1340(sp)
    sw t0, 0(t1)
    lw t0, 204(sp)
    lw t0, 0(t0)
    sw t0, 1372(sp)
    lw t0, 0(sp)
    lw t1, 1372(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1376(sp)
    lw t0, 1376(sp)
    lw t0, 0(t0)
    sw t0, 1380(sp)
    lw t0, 1380(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1384(sp)
    lw t0, 1388(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1392(sp)
    lw t0, 1392(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1396(sp)
    lw t0, 1396(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2870
.L1519:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1400(sp)
    lw t0, 1400(sp)
    li t1, 9
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1404(sp)
    lw t0, 1404(sp)
    bnez t0, .L1528
    j .L1618
.L1528:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1408(sp)
    lw t0, 4(sp)
    lw t1, 1408(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1412(sp)
    lw t0, 1412(sp)
    lw t0, 0(t0)
    sw t0, 1416(sp)
    lw t0, 1416(sp)
    lw t1, 220(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1420(sp)
    lw t0, 1420(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1424(sp)
    lw t0, 4(sp)
    lw t1, 1424(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1428(sp)
    lw t0, 1428(sp)
    lw t0, 0(t0)
    sw t0, 1432(sp)
    lw t0, 1432(sp)
    lw t1, 228(sp)
    sw t0, 0(t1)
    lw t0, 220(sp)
    lw t0, 0(t0)
    sw t0, 1436(sp)
    lw t0, 0(sp)
    lw t1, 1436(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1440(sp)
    lw t0, 220(sp)
    lw t0, 0(t0)
    sw t0, 1444(sp)
    lw t0, 0(sp)
    lw t1, 1444(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1448(sp)
    lw t0, 1448(sp)
    lw t0, 0(t0)
    sw t0, 1452(sp)
    lw t0, 228(sp)
    lw t0, 0(t0)
    sw t0, 1456(sp)
    lw t0, 0(sp)
    lw t1, 1456(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1460(sp)
    lw t0, 1460(sp)
    lw t0, 0(t0)
    sw t0, 1464(sp)
    lw t0, 1452(sp)
    lw t1, 1464(sp)
    xor t0, t0, t1
    sw t0, 1468(sp)
    lw t0, 1468(sp)
    lw t1, 1440(sp)
    sw t0, 0(t1)
    lw t0, 220(sp)
    lw t0, 0(t0)
    sw t0, 1472(sp)
    lw t0, 0(sp)
    lw t1, 1472(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1476(sp)
    lw t0, 1476(sp)
    lw t0, 0(t0)
    sw t0, 1480(sp)
    lw t0, 1480(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1484(sp)
    lw t0, 1488(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1492(sp)
    lw t0, 1492(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1496(sp)
    lw t0, 1496(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2869
.L1618:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1500(sp)
    lw t0, 1500(sp)
    li t1, 10
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1504(sp)
    lw t0, 1504(sp)
    bnez t0, .L1627
    j .L1692
.L1627:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1508(sp)
    lw t0, 4(sp)
    lw t1, 1508(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1512(sp)
    lw t0, 1512(sp)
    lw t0, 0(t0)
    sw t0, 1516(sp)
    lw t0, 1516(sp)
    lw t1, 236(sp)
    sw t0, 0(t1)
    lw t0, 236(sp)
    lw t0, 0(t0)
    sw t0, 1520(sp)
    lw t0, 0(sp)
    lw t1, 1520(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1524(sp)
    lw t0, 236(sp)
    lw t0, 0(t0)
    sw t0, 1528(sp)
    lw t0, 0(sp)
    lw t1, 1528(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1532(sp)
    lw t0, 1532(sp)
    lw t0, 0(t0)
    sw t0, 1536(sp)
    lw t0, 1536(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1540(sp)
    lw t0, 1544(sp)
    lw t1, 1524(sp)
    sw t0, 0(t1)
    lw t0, 236(sp)
    lw t0, 0(t0)
    sw t0, 1548(sp)
    lw t0, 0(sp)
    lw t1, 1548(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1552(sp)
    lw t0, 1552(sp)
    lw t0, 0(t0)
    sw t0, 1556(sp)
    lw t0, 1556(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1560(sp)
    lw t0, 1564(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1568(sp)
    lw t0, 1568(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1572(sp)
    lw t0, 1572(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2868
.L1692:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1576(sp)
    lw t0, 1576(sp)
    li t1, 11
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1580(sp)
    lw t0, 1580(sp)
    bnez t0, .L1701
    j .L1788
.L1701:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1584(sp)
    lw t0, 4(sp)
    lw t1, 1584(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1588(sp)
    lw t0, 1588(sp)
    lw t0, 0(t0)
    sw t0, 1592(sp)
    lw t0, 1592(sp)
    lw t1, 244(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1596(sp)
    lw t0, 1596(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1600(sp)
    lw t0, 4(sp)
    lw t1, 1600(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1604(sp)
    lw t0, 1604(sp)
    lw t0, 0(t0)
    sw t0, 1608(sp)
    lw t0, 1608(sp)
    lw t1, 252(sp)
    sw t0, 0(t1)
    lw t0, 244(sp)
    lw t0, 0(t0)
    sw t0, 1612(sp)
    lw t0, 0(sp)
    lw t1, 1612(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1616(sp)
    lw t0, 244(sp)
    lw t0, 0(t0)
    sw t0, 1620(sp)
    lw t0, 0(sp)
    lw t1, 1620(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1624(sp)
    lw t0, 1624(sp)
    lw t0, 0(t0)
    sw t0, 1628(sp)
    lw t0, 252(sp)
    lw t0, 0(t0)
    sw t0, 1632(sp)
    lw t0, 1628(sp)
    lw t1, 1632(sp)
    sll t0, t0, t1
    sw t0, 1636(sp)
    lw t0, 1636(sp)
    lw t1, 1616(sp)
    sw t0, 0(t1)
    lw t0, 244(sp)
    lw t0, 0(t0)
    sw t0, 1640(sp)
    lw t0, 0(sp)
    lw t1, 1640(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1644(sp)
    lw t0, 1644(sp)
    lw t0, 0(t0)
    sw t0, 1648(sp)
    lw t0, 1648(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1652(sp)
    lw t0, 1656(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1660(sp)
    lw t0, 1660(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1664(sp)
    lw t0, 1664(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2867
.L1788:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1668(sp)
    lw t0, 1668(sp)
    li t1, 12
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1672(sp)
    lw t0, 1672(sp)
    bnez t0, .L1797
    j .L1884
.L1797:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1676(sp)
    lw t0, 4(sp)
    lw t1, 1676(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1680(sp)
    lw t0, 1680(sp)
    lw t0, 0(t0)
    sw t0, 1684(sp)
    lw t0, 1684(sp)
    lw t1, 260(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1688(sp)
    lw t0, 1688(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1692(sp)
    lw t0, 4(sp)
    lw t1, 1692(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1696(sp)
    lw t0, 1696(sp)
    lw t0, 0(t0)
    sw t0, 1700(sp)
    lw t0, 1700(sp)
    lw t1, 268(sp)
    sw t0, 0(t1)
    lw t0, 260(sp)
    lw t0, 0(t0)
    sw t0, 1704(sp)
    lw t0, 0(sp)
    lw t1, 1704(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1708(sp)
    lw t0, 260(sp)
    lw t0, 0(t0)
    sw t0, 1712(sp)
    lw t0, 0(sp)
    lw t1, 1712(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1716(sp)
    lw t0, 1716(sp)
    lw t0, 0(t0)
    sw t0, 1720(sp)
    lw t0, 268(sp)
    lw t0, 0(t0)
    sw t0, 1724(sp)
    lw t0, 1720(sp)
    lw t1, 1724(sp)
    sra t0, t0, t1
    sw t0, 1728(sp)
    lw t0, 1728(sp)
    lw t1, 1708(sp)
    sw t0, 0(t1)
    lw t0, 260(sp)
    lw t0, 0(t0)
    sw t0, 1732(sp)
    lw t0, 0(sp)
    lw t1, 1732(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1736(sp)
    lw t0, 1736(sp)
    lw t0, 0(t0)
    sw t0, 1740(sp)
    lw t0, 1740(sp)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1744(sp)
    lw t0, 1748(sp)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1752(sp)
    lw t0, 1752(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1756(sp)
    lw t0, 1756(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2866
.L1884:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1760(sp)
    lw t0, 1760(sp)
    li t1, 13
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1764(sp)
    lw t0, 1764(sp)
    bnez t0, .L1893
    j .L1953
.L1893:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1768(sp)
    lw t0, 4(sp)
    lw t1, 1768(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1772(sp)
    lw t0, 1772(sp)
    lw t0, 0(t0)
    sw t0, 1776(sp)
    lw t0, 1776(sp)
    lw t1, 276(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 1780(sp)
    lw t0, 1780(sp)
    li t1, 1
    sub t0, t0, t1
    sw t0, 1784(sp)
    lw t0, 1784(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 1788(sp)
    lw t0, 8(sp)
    lw t1, 1788(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1792(sp)
    lw t0, 276(sp)
    lw t0, 0(t0)
    sw t0, 1796(sp)
    lw t0, 0(sp)
    lw t1, 1796(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1800(sp)
    lw t0, 1800(sp)
    lw t0, 0(t0)
    sw t0, 1804(sp)
    lw t0, 1804(sp)
    lw t1, 1792(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1808(sp)
    lw t0, 1808(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1812(sp)
    lw t0, 1812(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2865
.L1953:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1816(sp)
    lw t0, 1816(sp)
    li t1, 14
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1820(sp)
    lw t0, 1820(sp)
    bnez t0, .L1962
    j .L2022
.L1962:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1824(sp)
    lw t0, 4(sp)
    lw t1, 1824(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1828(sp)
    lw t0, 1828(sp)
    lw t0, 0(t0)
    sw t0, 1832(sp)
    lw t0, 1832(sp)
    lw t1, 284(sp)
    sw t0, 0(t1)
    lw t0, 284(sp)
    lw t0, 0(t0)
    sw t0, 1836(sp)
    lw t0, 0(sp)
    lw t1, 1836(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1840(sp)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 1844(sp)
    lw t0, 8(sp)
    lw t1, 1844(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1848(sp)
    lw t0, 1848(sp)
    lw t0, 0(t0)
    sw t0, 1852(sp)
    lw t0, 1852(sp)
    lw t1, 1840(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    sw t0, 1856(sp)
    lw t0, 1856(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1860(sp)
    lw t0, 1860(sp)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1864(sp)
    lw t0, 1864(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1868(sp)
    lw t0, 1868(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2864
.L2022:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1872(sp)
    lw t0, 1872(sp)
    li t1, 15
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1876(sp)
    lw t0, 1876(sp)
    bnez t0, .L2031
    j .L2158
.L2031:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1880(sp)
    lw t0, 4(sp)
    lw t1, 1880(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1884(sp)
    lw t0, 1884(sp)
    lw t0, 0(t0)
    sw t0, 1888(sp)
    lw t0, 1888(sp)
    lw t1, 292(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1892(sp)
    lw t0, 1892(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 1896(sp)
    lw t0, 4(sp)
    lw t1, 1896(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1900(sp)
    lw t0, 1900(sp)
    lw t0, 0(t0)
    sw t0, 1904(sp)
    lw t0, 1904(sp)
    lw t1, 300(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1908(sp)
    lw t0, 1908(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 1912(sp)
    lw t0, 4(sp)
    lw t1, 1912(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1916(sp)
    lw t0, 1916(sp)
    lw t0, 0(t0)
    sw t0, 1920(sp)
    lw t0, 1920(sp)
    lw t1, 308(sp)
    sw t0, 0(t1)
    lw t0, 300(sp)
    lw t0, 0(t0)
    sw t0, 1924(sp)
    lw t0, 0(sp)
    lw t1, 1924(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1928(sp)
    lw t0, 1928(sp)
    lw t0, 0(t0)
    sw t0, 1932(sp)
    lw t0, 308(sp)
    lw t0, 0(t0)
    sw t0, 1936(sp)
    lw t0, 1932(sp)
    lw t1, 1936(sp)
    add t0, t0, t1
    sw t0, 1940(sp)
    lw t0, 1940(sp)
    lw t1, 316(sp)
    sw t0, 0(t1)
    j .L2094
.L2094:
    lw t0, 316(sp)
    lw t0, 0(t0)
    sw t0, 1944(sp)
    lw t0, 1944(sp)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    sw t0, 1948(sp)
    li t1, 0
    sw t1, 1952(sp)
    lw t0, 1948(sp)
    bnez t0, .L2102
    j .L2112
.L2102:
    lw t0, 316(sp)
    lw t0, 0(t0)
    sw t0, 1956(sp)
    lw t0, 1956(sp)
    li t1, 2048
    slt t0, t0, t1
    sw t0, 1960(sp)
    lw t1, 1960(sp)
    sw t1, 1952(sp)
    j .L2112
.L2112:
    lw t0, 1952(sp)
    bnez t0, .L2116
    j .L2136
.L2116:
    lw t0, 292(sp)
    lw t0, 0(t0)
    sw t0, 1964(sp)
    lw t0, 0(sp)
    lw t1, 1964(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1968(sp)
    lw t0, 316(sp)
    lw t0, 0(t0)
    sw t0, 1972(sp)
    lw t0, 4(sp)
    lw t1, 1972(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 1976(sp)
    lw t0, 1976(sp)
    lw t0, 0(t0)
    sw t0, 1980(sp)
    lw t0, 1980(sp)
    lw t1, 1968(sp)
    sw t0, 0(t1)
    j .L2143
.L2136:
    li t0, 1
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L2143
.L2143:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 1984(sp)
    lw t0, 1984(sp)
    li t1, 3
    add t0, t0, t1
    sw t0, 1988(sp)
    lw t0, 1988(sp)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2863
.L2158:
    lw t0, 68(sp)
    lw t0, 0(t0)
    sw t0, 1992(sp)
    lw t0, 1992(sp)
    li t1, 16
    sub t0, t0, t1
    seqz t0, t0
    sw t0, 1996(sp)
    lw t0, 1996(sp)
    bnez t0, .L2167
    j .L2294
.L2167:
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 2000(sp)
    lw t0, 4(sp)
    lw t1, 2000(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 2004(sp)
    lw t0, 2004(sp)
    lw t0, 0(t0)
    sw t0, 2008(sp)
    lw t0, 2008(sp)
    lw t1, 324(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 2012(sp)
    lw t0, 2012(sp)
    li t1, 1
    add t0, t0, t1
    sw t0, 2016(sp)
    lw t0, 4(sp)
    lw t1, 2016(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 2020(sp)
    lw t0, 2020(sp)
    lw t0, 0(t0)
    sw t0, 2024(sp)
    lw t0, 2024(sp)
    lw t1, 332(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    sw t0, 2028(sp)
    lw t0, 2028(sp)
    li t1, 2
    add t0, t0, t1
    sw t0, 2032(sp)
    lw t0, 4(sp)
    lw t1, 2032(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    sw t0, 2036(sp)
    lw t0, 2036(sp)
    lw t0, 0(t0)
    sw t0, 2040(sp)
    lw t0, 2040(sp)
    lw t1, 340(sp)
    sw t0, 0(t1)
    lw t0, 332(sp)
    lw t0, 0(t0)
    sw t0, 2044(sp)
    lw t0, 0(sp)
    lw t1, 2044(sp)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2048
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2048
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2052
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 340(sp)
    lw t0, 0(t0)
    li t3, 2056
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2052
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2056
    add t3, t3, sp
    lw t1, 0(t3)
    add t0, t0, t1
    li t3, 2060
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2060
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 348(sp)
    sw t0, 0(t1)
    j .L2230
.L2230:
    lw t0, 348(sp)
    lw t0, 0(t0)
    li t3, 2064
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2064
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    slt t0, t0, t1
    xori t0, t0, 1
    li t3, 2068
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 0
    li t3, 2072
    add t3, t3, sp
    sw t1, 0(t3)
    li t3, 2068
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2238
    j .L2248
.L2238:
    lw t0, 348(sp)
    lw t0, 0(t0)
    li t3, 2076
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2076
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2048
    slt t0, t0, t1
    li t3, 2080
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2080
    add t3, t3, sp
    lw t1, 0(t3)
    li t3, 2072
    add t3, t3, sp
    sw t1, 0(t3)
    j .L2248
.L2248:
    li t3, 2072
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2252
    j .L2272
.L2252:
    lw t0, 348(sp)
    lw t0, 0(t0)
    li t3, 2084
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2084
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2088
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 324(sp)
    lw t0, 0(t0)
    li t3, 2092
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    li t3, 2092
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2096
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2096
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2100
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2100
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2088
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2279
.L2272:
    li t0, 1
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L2279
.L2279:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2104
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2104
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 3
    add t0, t0, t1
    li t3, 2108
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2108
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2862
.L2294:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2112
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2112
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 17
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2116
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2116
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2303
    j .L2319
.L2303:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2120
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2120
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2124
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2124
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2128
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2128
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2861
.L2319:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2132
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2132
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 18
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2136
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2136
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2328
    j .L2368
.L2328:
    lw t0, 20(sp)
    lw t0, 0(t0)
    li t3, 2140
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2140
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    li t3, 2144
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2144
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2336
    j .L2352
.L2336:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2148
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2148
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2152
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2152
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2156
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2156
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2367
.L2352:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2160
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2160
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2164
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2164
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2367
.L2367:
    j .L2860
.L2368:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2168
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2168
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 19
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2172
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2172
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2377
    j .L2418
.L2377:
    lw t0, 20(sp)
    lw t0, 0(t0)
    li t3, 2176
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2176
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2180
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2180
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2386
    j .L2402
.L2386:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2184
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2184
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2188
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2188
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2192
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2192
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2417
.L2402:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2196
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2196
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2200
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2200
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2417
.L2417:
    j .L2859
.L2418:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2204
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2204
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 20
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2208
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2208
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2427
    j .L2467
.L2427:
    lw t0, 24(sp)
    lw t0, 0(t0)
    li t3, 2212
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2212
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    li t3, 2216
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2216
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2435
    j .L2451
.L2435:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2220
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2220
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2224
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2224
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2228
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2228
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2466
.L2451:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2232
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2232
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2236
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2236
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2466
.L2466:
    j .L2858
.L2467:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2240
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2240
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 21
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2244
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2244
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2476
    j .L2517
.L2476:
    lw t0, 24(sp)
    lw t0, 0(t0)
    li t3, 2248
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2248
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2252
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2252
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2485
    j .L2501
.L2485:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2256
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2256
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2260
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2260
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2264
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2264
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2516
.L2501:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2268
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2268
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2272
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2272
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2516
.L2516:
    j .L2857
.L2517:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2276
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2276
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 22
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2280
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2280
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2526
    j .L2576
.L2526:
    lw t0, 16(sp)
    lw t0, 0(t0)
    li t3, 2284
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2284
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    sub t0, t0, t1
    li t3, 2288
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2288
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 16(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    li t3, 2292
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    li t3, 2292
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2296
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2300
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2300
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2304
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2304
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2296
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2308
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2308
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2312
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2312
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2316
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2316
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2856
.L2576:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2320
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2320
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 23
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2324
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2324
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2585
    j .L2615
.L2585:
    lw t0, 16(sp)
    lw t0, 0(t0)
    li t3, 2328
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 8(sp)
    li t3, 2328
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2332
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2332
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2336
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2336
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    lw t0, 16(sp)
    lw t0, 0(t0)
    li t3, 2340
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2340
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2344
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2344
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 16(sp)
    sw t0, 0(t1)
    j .L2855
.L2615:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2348
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2348
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 24
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2352
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2352
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2624
    j .L2713
.L2624:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2356
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2356
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2360
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2360
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2364
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2364
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 356(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2368
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2368
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2372
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2372
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2376
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2376
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2380
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2380
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 364(sp)
    sw t0, 0(t1)
    lw t0, 356(sp)
    lw t0, 0(t0)
    li t3, 2384
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    li t3, 2384
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2388
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2388
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2392
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2392
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 372(sp)
    sw t0, 0(t1)
    lw t0, 364(sp)
    lw t0, 0(t0)
    li t3, 2396
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    li t3, 2396
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2400
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2400
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2404
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2404
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 380(sp)
    sw t0, 0(t1)
    lw t0, 372(sp)
    lw t0, 0(t0)
    li t3, 2408
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 380(sp)
    lw t0, 0(t0)
    li t3, 2412
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2408
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2412
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2416
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2420
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 372(sp)
    lw t0, 0(t0)
    li t3, 2424
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 380(sp)
    lw t0, 0(t0)
    li t3, 2428
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2424
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2428
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 2432
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2436
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2440
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2440
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2
    add t0, t0, t1
    li t3, 2444
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2444
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2854
.L2713:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2448
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2448
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 25
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2452
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2452
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2722
    j .L2801
.L2722:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2456
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2456
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2460
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2460
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2464
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2464
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 388(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2468
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2468
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2472
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2472
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2476
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2476
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2480
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2480
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 396(sp)
    sw t0, 0(t1)
    lw t0, 388(sp)
    lw t0, 0(t0)
    li t3, 2484
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    li t3, 2484
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2488
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2488
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2492
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2492
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 404(sp)
    sw t0, 0(t1)
    lw t0, 404(sp)
    lw t0, 0(t0)
    li t3, 2496
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 396(sp)
    lw t0, 0(t0)
    li t3, 2500
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2496
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2500
    add t3, t3, sp
    lw t1, 0(t3)
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2504
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2508
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 20(sp)
    sw t0, 0(t1)
    lw t0, 404(sp)
    lw t0, 0(t0)
    li t3, 2512
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 396(sp)
    lw t0, 0(t0)
    li t3, 2516
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2512
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 2516
    add t3, t3, sp
    lw t1, 0(t3)
    slt t0, t0, t1
    li t3, 2520
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2524
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 24(sp)
    sw t0, 0(t1)
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2528
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2528
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2
    add t0, t0, t1
    li t3, 2532
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2532
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2853
.L2801:
    lw t0, 68(sp)
    lw t0, 0(t0)
    li t3, 2536
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2536
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 26
    sub t0, t0, t1
    seqz t0, t0
    li t3, 2540
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2540
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2810
    j .L2845
.L2810:
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2544
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 4(sp)
    li t3, 2544
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2548
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2548
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2552
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2552
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 412(sp)
    sw t0, 0(t1)
    lw t0, 412(sp)
    lw t0, 0(t0)
    li t3, 2556
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 0(sp)
    li t3, 2556
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 2560
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2560
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 2564
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2564
    add t3, t3, sp
    lw a0, 0(t3)
    call printlnInt
    lw t0, 12(sp)
    lw t0, 0(t0)
    li t3, 2568
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2568
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 2572
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 2572
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 12(sp)
    sw t0, 0(t1)
    j .L2852
.L2845:
    li t0, 1
    lw t1, 28(sp)
    sw t0, 0(t1)
    j .L2852
.L2852:
    j .L2853
.L2853:
    j .L2854
.L2854:
    j .L2855
.L2855:
    j .L2856
.L2856:
    j .L2857
.L2857:
    j .L2858
.L2858:
    j .L2859
.L2859:
    j .L2860
.L2860:
    j .L2861
.L2861:
    j .L2862
.L2862:
    j .L2863
.L2863:
    j .L2864
.L2864:
    j .L2865
.L2865:
    j .L2866
.L2866:
    j .L2867
.L2867:
    j .L2868
.L2868:
    j .L2869
.L2869:
    j .L2870
.L2870:
    j .L2871
.L2871:
    j .L2872
.L2872:
    j .L2873
.L2873:
    j .L2874
.L2874:
    j .L2875
.L2875:
    j .L2876
.L2876:
    j .L2877
.L2877:
    j .L2878
.L2878:
    j .L2879
.L2879:
    j .L403
.L2880:
    li t3, 2576
    add t3, t3, sp
    lw a0, 0(t3)
    j .L3
.L3:
    li t0, 2588
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 2584
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 2592
    add sp, sp, t0
    jr ra
    .globl main
    .type main, @function
main:
    li t0, -18736
    add sp, sp, t0
    li t0, 18732
    add t0, t0, sp
    sw ra, 0(t0)
    li t0, 18728
    add t0, t0, sp
    sw s0, 0(t0)
    li t0, 18736
    add s0, sp, t0
    addi t0, sp, 0
    sw t0, 64(sp)
    addi t0, sp, 68
    sw t0, 72(sp)
    addi t0, sp, 76
    sw t0, 140(sp)
    addi t0, sp, 144
    li t3, 8336
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8340
    add t0, sp, t1
    li t3, 8344
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 8348
    add t0, sp, t1
    li t3, 16540
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 16544
    add t0, sp, t1
    li t3, 17568
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17572
    add t0, sp, t1
    li t3, 17576
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 17580
    add t0, sp, t1
    li t3, 18604
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18608
    add t0, sp, t1
    li t3, 18612
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18616
    add t0, sp, t1
    li t3, 18620
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18624
    add t0, sp, t1
    li t3, 18628
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18632
    add t0, sp, t1
    li t3, 18636
    add t3, t3, sp
    sw t0, 0(t3)
    li t1, 18640
    add t0, sp, t1
    li t3, 18644
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L2886
.L2886:
    lw t0, 72(sp)
    lw t0, 0(t0)
    li t3, 18648
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18648
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 16
    slt t0, t0, t1
    li t3, 18652
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18652
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2890
    j .L2891
.L2890:
    lw t0, 72(sp)
    lw t0, 0(t0)
    li t3, 18656
    add t3, t3, sp
    sw t0, 0(t3)
    lw t0, 140(sp)
    li t3, 18656
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 18660
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 18660
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw t0, 72(sp)
    lw t0, 0(t0)
    li t3, 18664
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18664
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 18668
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18668
    add t3, t3, sp
    lw t0, 0(t3)
    lw t1, 72(sp)
    sw t0, 0(t1)
    j .L2886
.L2891:
    lw t0, 64(sp)
    lw t1, 140(sp)
    li t2, 64
    call memcpy
    li t0, 0
    li t3, 8344
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2900
.L2900:
    li t3, 8344
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 18672
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18672
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 2048
    slt t0, t0, t1
    li t3, 18676
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18676
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2904
    j .L2905
.L2904:
    li t3, 8344
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 18680
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 16540
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 18680
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 18684
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 18684
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 8344
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 18688
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18688
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 18692
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18692
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 8344
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2900
.L2905:
    li t3, 8336
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 16540
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 8192
    call memcpy
    li t0, 0
    li t3, 17576
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2914
.L2914:
    li t3, 17576
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 18696
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18696
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 256
    slt t0, t0, t1
    li t3, 18700
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18700
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2918
    j .L2919
.L2918:
    li t3, 17576
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 18704
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18604
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 18704
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 4
    mul t1, t1, t2
    add t0, t0, t1
    li t3, 18708
    add t3, t3, sp
    sw t0, 0(t3)
    li t0, 0
    li t3, 18708
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t3, 17576
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 18712
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18712
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 1
    add t0, t0, t1
    li t3, 18716
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18716
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 17576
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    j .L2914
.L2919:
    li t3, 17568
    add t3, t3, sp
    lw t0, 0(t3)
    li t3, 18604
    add t3, t3, sp
    lw t1, 0(t3)
    li t2, 1024
    call memcpy
    li t0, 0
    li t3, 18612
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 18620
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 18628
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 18636
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    li t0, 0
    li t3, 18644
    add t3, t3, sp
    lw t1, 0(t3)
    sw t0, 0(t1)
    lw a0, 64(sp)
    li t3, 8336
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 17568
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 18612
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 18620
    add t3, t3, sp
    lw a4, 0(t3)
    li t3, 18628
    add t3, t3, sp
    lw a5, 0(t3)
    li t3, 18636
    add t3, t3, sp
    lw a6, 0(t3)
    li t3, 18644
    add t3, t3, sp
    lw a7, 0(t3)
    call init_vm
    li t3, 8336
    add t3, t3, sp
    lw a0, 0(t3)
    call load_program
    lw a0, 64(sp)
    li t3, 8336
    add t3, t3, sp
    lw a1, 0(t3)
    li t3, 17568
    add t3, t3, sp
    lw a2, 0(t3)
    li t3, 18612
    add t3, t3, sp
    lw a3, 0(t3)
    li t3, 18620
    add t3, t3, sp
    lw a4, 0(t3)
    li t3, 18628
    add t3, t3, sp
    lw a5, 0(t3)
    li t3, 18636
    add t3, t3, sp
    lw a6, 0(t3)
    li t3, 18644
    add t3, t3, sp
    lw a7, 0(t3)
    call fetch_decode_execute
    li t3, 18644
    add t3, t3, sp
    lw t0, 0(t3)
    lw t0, 0(t0)
    li t3, 18720
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18720
    add t3, t3, sp
    lw t0, 0(t3)
    li t1, 0
    sub t0, t0, t1
    snez t0, t0
    li t3, 18724
    add t3, t3, sp
    sw t0, 0(t3)
    li t3, 18724
    add t3, t3, sp
    lw t0, 0(t3)
    bnez t0, .L2981
    j .L2983
.L2981:
    li a0, 1337
    call printlnInt
    j .L2985
.L2983:
    li a0, 9999
    call printlnInt
    j .L2985
.L2985:
    li a0, 0
    call __builtin_exit
    li a0, 0
    j .L4
.L4:
    li t0, 18732
    add t0, t0, sp
    lw ra, 0(t0)
    li t0, 18728
    add t0, t0, sp
    lw s0, 0(t0)
    li t0, 18736
    add sp, sp, t0
    jr ra
