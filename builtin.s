	.text
	.attribute	4, 16
	.attribute	5, "rv64i2p1_m2p0"
	.file	"builtin_rv64_runtime.c"
	.globl	print                           # -- Begin function print
	.p2align	2
	.type	print,@function
print:                                  # @print
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
	sd	a0, -24(s0)
	ld	a0, -24(s0)
	beqz	a0, .LBB0_2
	j	.LBB0_1
.LBB0_1:
	ld	a1, -24(s0)
	lui	a0, %hi(.L.str)
	addi	a0, a0, %lo(.L.str)
	call	printf
	j	.LBB0_2
.LBB0_2:
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end0:
	.size	print, .Lfunc_end0-print
                                        # -- End function
	.globl	println                         # -- Begin function println
	.p2align	2
	.type	println,@function
println:                                # @println
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
	sd	a0, -24(s0)
	ld	a0, -24(s0)
	beqz	a0, .LBB1_2
	j	.LBB1_1
.LBB1_1:
	ld	a1, -24(s0)
	lui	a0, %hi(.L.str.1)
	addi	a0, a0, %lo(.L.str.1)
	call	printf
	j	.LBB1_3
.LBB1_2:
	lui	a0, %hi(.L.str.2)
	addi	a0, a0, %lo(.L.str.2)
	call	printf
	j	.LBB1_3
.LBB1_3:
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end1:
	.size	println, .Lfunc_end1-println
                                        # -- End function
	.globl	printInt                        # -- Begin function printInt
	.p2align	2
	.type	printInt,@function
printInt:                               # @printInt
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
                                        # kill: def $x11 killed $x10
	sw	a0, -20(s0)
	lw	a1, -20(s0)
	lui	a0, %hi(.L.str.3)
	addi	a0, a0, %lo(.L.str.3)
	call	printf
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end2:
	.size	printInt, .Lfunc_end2-printInt
                                        # -- End function
	.globl	printlnInt                      # -- Begin function printlnInt
	.p2align	2
	.type	printlnInt,@function
printlnInt:                             # @printlnInt
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
                                        # kill: def $x11 killed $x10
	sw	a0, -20(s0)
	lw	a1, -20(s0)
	lui	a0, %hi(.L.str.4)
	addi	a0, a0, %lo(.L.str.4)
	call	printf
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end3:
	.size	printlnInt, .Lfunc_end3-printlnInt
                                        # -- End function
	.globl	getString                       # -- Begin function getString
	.p2align	2
	.type	getString,@function
getString:                              # @getString
# %bb.0:
	addi	sp, sp, -64
	sd	ra, 56(sp)                      # 8-byte Folded Spill
	sd	s0, 48(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 64
	li	a0, 32
	sd	a0, -56(s0)                     # 8-byte Folded Spill
	call	malloc
	mv	a1, a0
	ld	a0, -56(s0)                     # 8-byte Folded Reload
	sd	a1, -24(s0)
	sd	a0, -32(s0)
	li	a0, 0
	sd	a0, -40(s0)
	ld	a0, -24(s0)
	bnez	a0, .LBB4_2
	j	.LBB4_1
.LBB4_1:
	li	a0, 1
	call	exit
.LBB4_2:
	j	.LBB4_3
.LBB4_3:                                # =>This Inner Loop Header: Depth=1
	call	getchar
	sw	a0, -44(s0)
	lw	a0, -44(s0)
	li	a1, -1
	beq	a0, a1, .LBB4_5
	j	.LBB4_4
.LBB4_4:                                #   in Loop: Header=BB4_3 Depth=1
	lw	a0, -44(s0)
	li	a1, 10
	bne	a0, a1, .LBB4_6
	j	.LBB4_5
.LBB4_5:
	j	.LBB4_11
.LBB4_6:                                #   in Loop: Header=BB4_3 Depth=1
	lbu	a0, -44(s0)
	ld	a1, -24(s0)
	ld	a2, -40(s0)
	addi	a3, a2, 1
	sd	a3, -40(s0)
	add	a1, a1, a2
	sb	a0, 0(a1)
	ld	a0, -40(s0)
	addi	a0, a0, 1
	ld	a1, -32(s0)
	bltu	a0, a1, .LBB4_10
	j	.LBB4_7
.LBB4_7:                                #   in Loop: Header=BB4_3 Depth=1
	ld	a0, -32(s0)
	slli	a0, a0, 1
	sd	a0, -32(s0)
	ld	a0, -24(s0)
	ld	a1, -32(s0)
	call	realloc
	sd	a0, -24(s0)
	ld	a0, -24(s0)
	bnez	a0, .LBB4_9
	j	.LBB4_8
.LBB4_8:
	li	a0, 1
	call	exit
.LBB4_9:                                #   in Loop: Header=BB4_3 Depth=1
	j	.LBB4_10
.LBB4_10:                               #   in Loop: Header=BB4_3 Depth=1
	j	.LBB4_3
.LBB4_11:
	ld	a0, -24(s0)
	ld	a1, -40(s0)
	add	a1, a0, a1
	li	a0, 0
	sb	a0, 0(a1)
	ld	a0, -24(s0)
	ld	ra, 56(sp)                      # 8-byte Folded Reload
	ld	s0, 48(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 64
	ret
.Lfunc_end4:
	.size	getString, .Lfunc_end4-getString
                                        # -- End function
	.globl	getInt                          # -- Begin function getInt
	.p2align	2
	.type	getInt,@function
getInt:                                 # @getInt
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
	lui	a0, %hi(.L.str.3)
	addi	a0, a0, %lo(.L.str.3)
	addi	a1, s0, -24
	call	scanf
	sw	a0, -28(s0)
	lw	a0, -28(s0)
	li	a1, 1
	beq	a0, a1, .LBB5_2
	j	.LBB5_1
.LBB5_1:
	li	a0, 0
	sw	a0, -20(s0)
	j	.LBB5_3
.LBB5_2:
	lw	a0, -24(s0)
	sw	a0, -20(s0)
	j	.LBB5_3
.LBB5_3:
	lw	a0, -20(s0)
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end5:
	.size	getInt, .Lfunc_end5-getInt
                                        # -- End function
	.globl	__builtin_exit                  # -- Begin function __builtin_exit
	.p2align	2
	.type	__builtin_exit,@function
__builtin_exit:                         # @__builtin_exit
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
                                        # kill: def $x11 killed $x10
	sw	a0, -20(s0)
	lw	a0, -20(s0)
	call	exit
.Lfunc_end6:
	.size	__builtin_exit, .Lfunc_end6-__builtin_exit
                                        # -- End function
	.globl	u32_to_string                   # -- Begin function u32_to_string
	.p2align	2
	.type	u32_to_string,@function
u32_to_string:                          # @u32_to_string
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
                                        # kill: def $x11 killed $x10
	sw	a0, -20(s0)
	li	a0, 16
	call	malloc
	sd	a0, -32(s0)
	ld	a0, -32(s0)
	bnez	a0, .LBB7_2
	j	.LBB7_1
.LBB7_1:
	li	a0, 1
	call	exit
.LBB7_2:
	ld	a0, -32(s0)
	lw	a2, -20(s0)
	lui	a1, %hi(.L.str.5)
	addi	a1, a1, %lo(.L.str.5)
	call	sprintf
	ld	a0, -32(s0)
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end7:
	.size	u32_to_string, .Lfunc_end7-u32_to_string
                                        # -- End function
	.globl	usize_to_string                 # -- Begin function usize_to_string
	.p2align	2
	.type	usize_to_string,@function
usize_to_string:                        # @usize_to_string
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
	sd	a0, -24(s0)
	li	a0, 32
	call	malloc
	sd	a0, -32(s0)
	ld	a0, -32(s0)
	bnez	a0, .LBB8_2
	j	.LBB8_1
.LBB8_1:
	li	a0, 1
	call	exit
.LBB8_2:
	ld	a0, -32(s0)
	ld	a2, -24(s0)
	lui	a1, %hi(.L.str.6)
	addi	a1, a1, %lo(.L.str.6)
	call	sprintf
	ld	a0, -32(s0)
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end8:
	.size	usize_to_string, .Lfunc_end8-usize_to_string
                                        # -- End function
	.globl	string_len                      # -- Begin function string_len
	.p2align	2
	.type	string_len,@function
string_len:                             # @string_len
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
	sd	a0, -32(s0)
	ld	a0, -32(s0)
	bnez	a0, .LBB9_2
	j	.LBB9_1
.LBB9_1:
	li	a0, 0
	sd	a0, -24(s0)
	j	.LBB9_3
.LBB9_2:
	ld	a0, -32(s0)
	call	strlen
	sd	a0, -24(s0)
	j	.LBB9_3
.LBB9_3:
	ld	a0, -24(s0)
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end9:
	.size	string_len, .Lfunc_end9-string_len
                                        # -- End function
	.globl	string_as_str                   # -- Begin function string_as_str
	.p2align	2
	.type	string_as_str,@function
string_as_str:                          # @string_as_str
# %bb.0:
	addi	sp, sp, -32
	sd	ra, 24(sp)                      # 8-byte Folded Spill
	sd	s0, 16(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 32
	sd	a0, -24(s0)
	ld	a0, -24(s0)
	ld	ra, 24(sp)                      # 8-byte Folded Reload
	ld	s0, 16(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end10:
	.size	string_as_str, .Lfunc_end10-string_as_str
                                        # -- End function
	.globl	string_from                     # -- Begin function string_from
	.p2align	2
	.type	string_from,@function
string_from:                            # @string_from
# %bb.0:
	addi	sp, sp, -48
	sd	ra, 40(sp)                      # 8-byte Folded Spill
	sd	s0, 32(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 48
	sd	a0, -32(s0)
	ld	a0, -32(s0)
	bnez	a0, .LBB11_4
	j	.LBB11_1
.LBB11_1:
	li	a0, 1
	call	malloc
	sd	a0, -40(s0)
	ld	a0, -40(s0)
	bnez	a0, .LBB11_3
	j	.LBB11_2
.LBB11_2:
	li	a0, 1
	call	exit
.LBB11_3:
	ld	a1, -40(s0)
	li	a0, 0
	sb	a0, 0(a1)
	ld	a0, -40(s0)
	sd	a0, -24(s0)
	j	.LBB11_7
.LBB11_4:
	ld	a0, -32(s0)
	call	strdup
	sd	a0, -48(s0)
	ld	a0, -48(s0)
	bnez	a0, .LBB11_6
	j	.LBB11_5
.LBB11_5:
	li	a0, 1
	call	exit
.LBB11_6:
	ld	a0, -48(s0)
	sd	a0, -24(s0)
	j	.LBB11_7
.LBB11_7:
	ld	a0, -24(s0)
	ld	ra, 40(sp)                      # 8-byte Folded Reload
	ld	s0, 32(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 48
	ret
.Lfunc_end11:
	.size	string_from, .Lfunc_end11-string_from
                                        # -- End function
	.globl	string_append                   # -- Begin function string_append
	.p2align	2
	.type	string_append,@function
string_append:                          # @string_append
# %bb.0:
	addi	sp, sp, -80
	sd	ra, 72(sp)                      # 8-byte Folded Spill
	sd	s0, 64(sp)                      # 8-byte Folded Spill
	addi	s0, sp, 80
	sd	a0, -24(s0)
	sd	a1, -32(s0)
	ld	a0, -24(s0)
	beqz	a0, .LBB12_2
	j	.LBB12_1
.LBB12_1:
	ld	a0, -32(s0)
	bnez	a0, .LBB12_3
	j	.LBB12_2
.LBB12_2:
	j	.LBB12_11
.LBB12_3:
	ld	a0, -24(s0)
	ld	a0, 0(a0)
	sd	a0, -40(s0)
	ld	a0, -40(s0)
	beqz	a0, .LBB12_5
	j	.LBB12_4
.LBB12_4:
	ld	a0, -40(s0)
	call	strlen
	sd	a0, -72(s0)                     # 8-byte Folded Spill
	j	.LBB12_6
.LBB12_5:
	li	a0, 0
	sd	a0, -72(s0)                     # 8-byte Folded Spill
	j	.LBB12_6
.LBB12_6:
	ld	a0, -72(s0)                     # 8-byte Folded Reload
	sd	a0, -48(s0)
	ld	a0, -32(s0)
	call	strlen
	sd	a0, -56(s0)
	ld	a0, -40(s0)
	ld	a1, -48(s0)
	ld	a2, -56(s0)
	add	a1, a1, a2
	addi	a1, a1, 1
	call	realloc
	sd	a0, -64(s0)
	ld	a0, -64(s0)
	bnez	a0, .LBB12_8
	j	.LBB12_7
.LBB12_7:
	li	a0, 1
	call	exit
.LBB12_8:
	ld	a0, -40(s0)
	bnez	a0, .LBB12_10
	j	.LBB12_9
.LBB12_9:
	ld	a1, -64(s0)
	li	a0, 0
	sb	a0, 0(a1)
	j	.LBB12_10
.LBB12_10:
	ld	a0, -64(s0)
	ld	a1, -32(s0)
	call	strcat
	ld	a0, -64(s0)
	ld	a1, -24(s0)
	sd	a0, 0(a1)
	j	.LBB12_11
.LBB12_11:
	ld	ra, 72(sp)                      # 8-byte Folded Reload
	ld	s0, 64(sp)                      # 8-byte Folded Reload
	addi	sp, sp, 80
	ret
.Lfunc_end12:
	.size	string_append, .Lfunc_end12-string_append
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"%s"
	.size	.L.str, 3

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%s\n"
	.size	.L.str.1, 4

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"\n"
	.size	.L.str.2, 2

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"%d"
	.size	.L.str.3, 3

	.type	.L.str.4,@object                # @.str.4
.L.str.4:
	.asciz	"%d\n"
	.size	.L.str.4, 4

	.type	.L.str.5,@object                # @.str.5
.L.str.5:
	.asciz	"%u"
	.size	.L.str.5, 3

	.type	.L.str.6,@object                # @.str.6
.L.str.6:
	.asciz	"%lu"
	.size	.L.str.6, 4

	.ident	"Ubuntu clang version 18.1.3 (1ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym printf
	.addrsig_sym malloc
	.addrsig_sym exit
	.addrsig_sym getchar
	.addrsig_sym realloc
	.addrsig_sym scanf
	.addrsig_sym sprintf
	.addrsig_sym strlen
	.addrsig_sym strdup
	.addrsig_sym strcat
