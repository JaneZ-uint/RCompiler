	.text
	.attribute	4, 16
	.attribute	5, "rv32i2p1_m2p0"
	.file	"stub_builtin.c"
	.globl	my_strdup                       # -- Begin function my_strdup
	.p2align	2
	.type	my_strdup,@function
my_strdup:                              # @my_strdup
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	addi	s0, sp, 32
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	call	strlen
	addi	a0, a0, 1
	sw	a0, -16(s0)
	lw	a0, -16(s0)
	call	malloc
	sw	a0, -20(s0)
	lw	a0, -20(s0)
	beqz	a0, .LBB0_2
	j	.LBB0_1
.LBB0_1:
	lw	a0, -20(s0)
	lw	a1, -12(s0)
	call	strcpy
	j	.LBB0_2
.LBB0_2:
	lw	a0, -20(s0)
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end0:
	.size	my_strdup, .Lfunc_end0-my_strdup
                                        # -- End function
	.globl	my_exit                         # -- Begin function my_exit
	.p2align	2
	.type	my_exit,@function
my_exit:                                # @my_exit
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	lw	a1, -12(s0)
	lui	a0, %hi(.L.str)
	addi	a0, a0, %lo(.L.str)
	call	printf
	j	.LBB1_1
.LBB1_1:                                # =>This Inner Loop Header: Depth=1
	j	.LBB1_1
.Lfunc_end1:
	.size	my_exit, .Lfunc_end1-my_exit
                                        # -- End function
	.globl	print                           # -- Begin function print
	.p2align	2
	.type	print,@function
print:                                  # @print
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	beqz	a0, .LBB2_2
	j	.LBB2_1
.LBB2_1:
	lw	a1, -12(s0)
	lui	a0, %hi(.L.str.1)
	addi	a0, a0, %lo(.L.str.1)
	call	printf
	j	.LBB2_2
.LBB2_2:
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end2:
	.size	print, .Lfunc_end2-print
                                        # -- End function
	.globl	println                         # -- Begin function println
	.p2align	2
	.type	println,@function
println:                                # @println
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	beqz	a0, .LBB3_2
	j	.LBB3_1
.LBB3_1:
	lw	a1, -12(s0)
	lui	a0, %hi(.L.str.2)
	addi	a0, a0, %lo(.L.str.2)
	call	printf
	j	.LBB3_3
.LBB3_2:
	lui	a0, %hi(.L.str.3)
	addi	a0, a0, %lo(.L.str.3)
	call	printf
	j	.LBB3_3
.LBB3_3:
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end3:
	.size	println, .Lfunc_end3-println
                                        # -- End function
	.globl	printInt                        # -- Begin function printInt
	.p2align	2
	.type	printInt,@function
printInt:                               # @printInt
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	lw	a1, -12(s0)
	lui	a0, %hi(.L.str.4)
	addi	a0, a0, %lo(.L.str.4)
	call	printf
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end4:
	.size	printInt, .Lfunc_end4-printInt
                                        # -- End function
	.globl	printlnInt                      # -- Begin function printlnInt
	.p2align	2
	.type	printlnInt,@function
printlnInt:                             # @printlnInt
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	lw	a1, -12(s0)
	lui	a0, %hi(.L.str.5)
	addi	a0, a0, %lo(.L.str.5)
	call	printf
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end5:
	.size	printlnInt, .Lfunc_end5-printlnInt
                                        # -- End function
	.globl	getString                       # -- Begin function getString
	.p2align	2
	.type	getString,@function
getString:                              # @getString
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	addi	s0, sp, 32
	li	a0, 0
	sw	a0, -12(s0)
	sw	a0, -16(s0)
	sw	a0, -20(s0)
	li	a0, 32
	sw	a0, -16(s0)
	lw	a0, -16(s0)
	call	malloc
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	bnez	a0, .LBB6_2
	j	.LBB6_1
.LBB6_1:
	lui	a0, %hi(.L.str.6)
	addi	a0, a0, %lo(.L.str.6)
	call	printf
	li	a0, 1
	call	my_exit
	j	.LBB6_2
.LBB6_2:
	j	.LBB6_3
.LBB6_3:                                # =>This Inner Loop Header: Depth=1
	call	getchar
	sw	a0, -24(s0)
	lw	a0, -24(s0)
	li	a1, -1
	beq	a0, a1, .LBB6_5
	j	.LBB6_4
.LBB6_4:                                #   in Loop: Header=BB6_3 Depth=1
	lw	a0, -24(s0)
	li	a1, 10
	bne	a0, a1, .LBB6_6
	j	.LBB6_5
.LBB6_5:
	j	.LBB6_11
.LBB6_6:                                #   in Loop: Header=BB6_3 Depth=1
	lw	a0, -24(s0)
	lw	a1, -12(s0)
	lw	a2, -20(s0)
	addi	a3, a2, 1
	sw	a3, -20(s0)
	add	a1, a1, a2
	sb	a0, 0(a1)
	lw	a0, -20(s0)
	addi	a0, a0, 1
	lw	a1, -16(s0)
	bltu	a0, a1, .LBB6_10
	j	.LBB6_7
.LBB6_7:                                #   in Loop: Header=BB6_3 Depth=1
	lw	a0, -16(s0)
	slli	a0, a0, 1
	sw	a0, -16(s0)
	lw	a0, -12(s0)
	lw	a1, -16(s0)
	call	realloc
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	bnez	a0, .LBB6_9
	j	.LBB6_8
.LBB6_8:                                #   in Loop: Header=BB6_3 Depth=1
	lui	a0, %hi(.L.str.6)
	addi	a0, a0, %lo(.L.str.6)
	call	printf
	li	a0, 1
	call	my_exit
	j	.LBB6_9
.LBB6_9:                                #   in Loop: Header=BB6_3 Depth=1
	j	.LBB6_10
.LBB6_10:                               #   in Loop: Header=BB6_3 Depth=1
	j	.LBB6_3
.LBB6_11:
	lw	a0, -12(s0)
	lw	a1, -20(s0)
	add	a1, a0, a1
	li	a0, 0
	sb	a0, 0(a1)
	lw	a0, -12(s0)
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end6:
	.size	getString, .Lfunc_end6-getString
                                        # -- End function
	.globl	getInt                          # -- Begin function getInt
	.p2align	2
	.type	getInt,@function
getInt:                                 # @getInt
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	addi	s0, sp, 32
	lui	a0, %hi(.L.str.4)
	addi	a0, a0, %lo(.L.str.4)
	addi	a1, s0, -16
	call	scanf
	sw	a0, -20(s0)
	lw	a0, -20(s0)
	li	a1, 1
	beq	a0, a1, .LBB7_2
	j	.LBB7_1
.LBB7_1:
	li	a0, 0
	sw	a0, -12(s0)
	j	.LBB7_3
.LBB7_2:
	lw	a0, -16(s0)
	sw	a0, -12(s0)
	j	.LBB7_3
.LBB7_3:
	lw	a0, -12(s0)
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end7:
	.size	getInt, .Lfunc_end7-getInt
                                        # -- End function
	.globl	__builtin_exit                  # -- Begin function __builtin_exit
	.p2align	2
	.type	__builtin_exit,@function
__builtin_exit:                         # @__builtin_exit
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	call	my_exit
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end8:
	.size	__builtin_exit, .Lfunc_end8-__builtin_exit
                                        # -- End function
	.globl	u32_to_string                   # -- Begin function u32_to_string
	.p2align	2
	.type	u32_to_string,@function
u32_to_string:                          # @u32_to_string
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	li	a0, 16
	call	malloc
	sw	a0, -16(s0)
	lw	a0, -16(s0)
	bnez	a0, .LBB9_2
	j	.LBB9_1
.LBB9_1:
	li	a0, 1
	call	my_exit
	j	.LBB9_2
.LBB9_2:
	lw	a0, -16(s0)
	lw	a2, -12(s0)
	lui	a1, %hi(.L.str.7)
	addi	a1, a1, %lo(.L.str.7)
	call	sprintf
	lw	a0, -16(s0)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end9:
	.size	u32_to_string, .Lfunc_end9-u32_to_string
                                        # -- End function
	.globl	usize_to_string                 # -- Begin function usize_to_string
	.p2align	2
	.type	usize_to_string,@function
usize_to_string:                        # @usize_to_string
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	li	a0, 32
	call	malloc
	sw	a0, -16(s0)
	lw	a0, -16(s0)
	bnez	a0, .LBB10_2
	j	.LBB10_1
.LBB10_1:
	li	a0, 1
	call	my_exit
	j	.LBB10_2
.LBB10_2:
	lw	a0, -16(s0)
	lw	a2, -12(s0)
	lui	a1, %hi(.L.str.8)
	addi	a1, a1, %lo(.L.str.8)
	call	sprintf
	lw	a0, -16(s0)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end10:
	.size	usize_to_string, .Lfunc_end10-usize_to_string
                                        # -- End function
	.globl	string_len                      # -- Begin function string_len
	.p2align	2
	.type	string_len,@function
string_len:                             # @string_len
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -16(s0)
	lw	a0, -16(s0)
	bnez	a0, .LBB11_2
	j	.LBB11_1
.LBB11_1:
	li	a0, 0
	sw	a0, -12(s0)
	j	.LBB11_3
.LBB11_2:
	lw	a0, -16(s0)
	call	strlen
	sw	a0, -12(s0)
	j	.LBB11_3
.LBB11_3:
	lw	a0, -12(s0)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end11:
	.size	string_len, .Lfunc_end11-string_len
                                        # -- End function
	.globl	string_as_str                   # -- Begin function string_as_str
	.p2align	2
	.type	string_as_str,@function
string_as_str:                          # @string_as_str
# %bb.0:
	addi	sp, sp, -16
	sw	ra, 12(sp)                      # 4-byte Folded Spill
	sw	s0, 8(sp)                       # 4-byte Folded Spill
	addi	s0, sp, 16
	sw	a0, -12(s0)
	lw	a0, -12(s0)
	lw	ra, 12(sp)                      # 4-byte Folded Reload
	lw	s0, 8(sp)                       # 4-byte Folded Reload
	addi	sp, sp, 16
	ret
.Lfunc_end12:
	.size	string_as_str, .Lfunc_end12-string_as_str
                                        # -- End function
	.globl	string_from                     # -- Begin function string_from
	.p2align	2
	.type	string_from,@function
string_from:                            # @string_from
# %bb.0:
	addi	sp, sp, -32
	sw	ra, 28(sp)                      # 4-byte Folded Spill
	sw	s0, 24(sp)                      # 4-byte Folded Spill
	addi	s0, sp, 32
	sw	a0, -16(s0)
	lw	a0, -16(s0)
	bnez	a0, .LBB13_4
	j	.LBB13_1
.LBB13_1:
	li	a0, 1
	call	malloc
	sw	a0, -20(s0)
	lw	a0, -20(s0)
	bnez	a0, .LBB13_3
	j	.LBB13_2
.LBB13_2:
	li	a0, 1
	call	my_exit
	j	.LBB13_3
.LBB13_3:
	lw	a1, -20(s0)
	li	a0, 0
	sb	a0, 0(a1)
	lw	a0, -20(s0)
	sw	a0, -12(s0)
	j	.LBB13_7
.LBB13_4:
	lw	a0, -16(s0)
	call	my_strdup
	sw	a0, -24(s0)
	lw	a0, -24(s0)
	bnez	a0, .LBB13_6
	j	.LBB13_5
.LBB13_5:
	li	a0, 1
	call	my_exit
	j	.LBB13_6
.LBB13_6:
	lw	a0, -24(s0)
	sw	a0, -12(s0)
	j	.LBB13_7
.LBB13_7:
	lw	a0, -12(s0)
	lw	ra, 28(sp)                      # 4-byte Folded Reload
	lw	s0, 24(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 32
	ret
.Lfunc_end13:
	.size	string_from, .Lfunc_end13-string_from
                                        # -- End function
	.globl	string_append                   # -- Begin function string_append
	.p2align	2
	.type	string_append,@function
string_append:                          # @string_append
# %bb.0:
	addi	sp, sp, -48
	sw	ra, 44(sp)                      # 4-byte Folded Spill
	sw	s0, 40(sp)                      # 4-byte Folded Spill
	addi	s0, sp, 48
	sw	a0, -12(s0)
	sw	a1, -16(s0)
	lw	a0, -12(s0)
	beqz	a0, .LBB14_2
	j	.LBB14_1
.LBB14_1:
	lw	a0, -16(s0)
	bnez	a0, .LBB14_3
	j	.LBB14_2
.LBB14_2:
	j	.LBB14_11
.LBB14_3:
	lw	a0, -12(s0)
	lw	a0, 0(a0)
	sw	a0, -20(s0)
	lw	a0, -20(s0)
	beqz	a0, .LBB14_5
	j	.LBB14_4
.LBB14_4:
	lw	a0, -20(s0)
	call	strlen
	sw	a0, -40(s0)                     # 4-byte Folded Spill
	j	.LBB14_6
.LBB14_5:
	li	a0, 0
	sw	a0, -40(s0)                     # 4-byte Folded Spill
	j	.LBB14_6
.LBB14_6:
	lw	a0, -40(s0)                     # 4-byte Folded Reload
	sw	a0, -24(s0)
	lw	a0, -16(s0)
	call	strlen
	sw	a0, -28(s0)
	lw	a0, -24(s0)
	lw	a1, -28(s0)
	add	a0, a0, a1
	sw	a0, -32(s0)
	lw	a0, -20(s0)
	lw	a1, -32(s0)
	addi	a1, a1, 1
	call	realloc
	sw	a0, -36(s0)
	lw	a0, -36(s0)
	bnez	a0, .LBB14_8
	j	.LBB14_7
.LBB14_7:
	lui	a0, %hi(.L.str.9)
	addi	a0, a0, %lo(.L.str.9)
	call	printf
	li	a0, 1
	call	my_exit
	j	.LBB14_8
.LBB14_8:
	lw	a0, -20(s0)
	bnez	a0, .LBB14_10
	j	.LBB14_9
.LBB14_9:
	lw	a1, -36(s0)
	li	a0, 0
	sb	a0, 0(a1)
	j	.LBB14_10
.LBB14_10:
	lw	a0, -36(s0)
	lw	a1, -16(s0)
	call	strcat
	lw	a0, -36(s0)
	lw	a1, -12(s0)
	sw	a0, 0(a1)
	j	.LBB14_11
.LBB14_11:
	lw	ra, 44(sp)                      # 4-byte Folded Reload
	lw	s0, 40(sp)                      # 4-byte Folded Reload
	addi	sp, sp, 48
	ret
.Lfunc_end14:
	.size	string_append, .Lfunc_end14-string_append
                                        # -- End function
	.type	.L.str,@object                  # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"Exiting with status %d\n"
	.size	.L.str, 24

	.type	.L.str.1,@object                # @.str.1
.L.str.1:
	.asciz	"%s"
	.size	.L.str.1, 3

	.type	.L.str.2,@object                # @.str.2
.L.str.2:
	.asciz	"%s\n"
	.size	.L.str.2, 4

	.type	.L.str.3,@object                # @.str.3
.L.str.3:
	.asciz	"\n"
	.size	.L.str.3, 2

	.type	.L.str.4,@object                # @.str.4
.L.str.4:
	.asciz	"%d"
	.size	.L.str.4, 3

	.type	.L.str.5,@object                # @.str.5
.L.str.5:
	.asciz	"%d\n"
	.size	.L.str.5, 4

	.type	.L.str.6,@object                # @.str.6
.L.str.6:
	.asciz	"Error: memory allocation failed in getString\n"
	.size	.L.str.6, 46

	.type	.L.str.7,@object                # @.str.7
.L.str.7:
	.asciz	"%u"
	.size	.L.str.7, 3

	.type	.L.str.8,@object                # @.str.8
.L.str.8:
	.asciz	"%lu"
	.size	.L.str.8, 4

	.type	.L.str.9,@object                # @.str.9
.L.str.9:
	.asciz	"Error: memory allocation failed in append\n"
	.size	.L.str.9, 43

	.ident	"Ubuntu clang version 18.1.3 (1ubuntu1)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym my_strdup
	.addrsig_sym strlen
	.addrsig_sym malloc
	.addrsig_sym strcpy
	.addrsig_sym my_exit
	.addrsig_sym printf
	.addrsig_sym getchar
	.addrsig_sym realloc
	.addrsig_sym scanf
	.addrsig_sym sprintf
	.addrsig_sym strcat
