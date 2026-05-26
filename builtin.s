	.file	"builtin_gcc_runtime.c"
	.option nopic
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LBuiltin_C0:
	.string	"%s"
	.text
	.align	2
	.globl	print
	.type	print, @function
print:
	beq	a0,zero,.LBuiltin_7
	mv	a1,a0
	lui	a0,%hi(.LBuiltin_C0)
	addi	sp,sp,-16
	addi	a0,a0,%lo(.LBuiltin_C0)
	sd	ra,8(sp)
	call	printf
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
.LBuiltin_7:
	ret
	.size	print, .-print
	.section	.rodata.str1.8
	.align	3
.LBuiltin_C1:
	.string	"%s\n"
	.align	3
.LBuiltin_C2:
	.string	"\n"
	.text
	.align	2
	.globl	println
	.type	println, @function
println:
	addi	sp,sp,-16
	sd	ra,8(sp)
	beq	a0,zero,.LBuiltin_12
	mv	a1,a0
	lui	a0,%hi(.LBuiltin_C1)
	addi	a0,a0,%lo(.LBuiltin_C1)
	call	printf
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
.LBuiltin_12:
	lui	a0,%hi(.LBuiltin_C2)
	addi	a0,a0,%lo(.LBuiltin_C2)
	call	printf
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	println, .-println
	.section	.rodata.str1.8
	.align	3
.LBuiltin_C3:
	.string	"%d"
	.text
	.align	2
	.globl	printInt
	.type	printInt, @function
printInt:
	mv	a1,a0
	lui	a0,%hi(.LBuiltin_C3)
	addi	sp,sp,-16
	addi	a0,a0,%lo(.LBuiltin_C3)
	sd	ra,8(sp)
	call	printf
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	printInt, .-printInt
	.section	.rodata.str1.8
	.align	3
.LBuiltin_C4:
	.string	"%d\n"
	.text
	.align	2
	.globl	printlnInt
	.type	printlnInt, @function
printlnInt:
	mv	a1,a0
	lui	a0,%hi(.LBuiltin_C4)
	addi	sp,sp,-16
	addi	a0,a0,%lo(.LBuiltin_C4)
	sd	ra,8(sp)
	call	printf
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	printlnInt, .-printlnInt
	.section	.rodata.str1.8
	.align	3
.LBuiltin_C5:
	.string	"Error: memory allocation failed in getString\n"
	.text
	.align	2
	.globl	getString
	.type	getString, @function
getString:
	addi	sp,sp,-48
	li	a0,32
	sd	s1,24(sp)
	sd	ra,40(sp)
	sd	s0,32(sp)
	sd	s2,16(sp)
	sd	s3,8(sp)
	sd	s4,0(sp)
	call	malloc
	mv	s1,a0
	beq	a0,zero,.LBuiltin_27
.LBuiltin_20:
	li	s0,0
	li	s2,32
	li	s3,-1
	li	s4,10
.LBuiltin_21:
	call	getchar
	addi	a4,s0,2
	add	a5,s1,s0
	beq	a0,s3,.LBuiltin_22
.LBuiltin_28:
	beq	a0,s4,.LBuiltin_22
	sb	a0,0(a5)
	addi	s0,s0,1
	bgtu	s2,a4,.LBuiltin_21
	slli	s2,s2,1
	mv	a0,s1
	mv	a1,s2
	call	realloc
	mv	s1,a0
	bne	a0,zero,.LBuiltin_21
	lui	a5,%hi(stderr)
	ld	a0,%lo(stderr)(a5)
	lui	a1,%hi(.LBuiltin_C5)
	addi	a1,a1,%lo(.LBuiltin_C5)
	call	fprintf
	li	a0,1
	call	exit
	call	getchar
	addi	a4,s0,2
	add	a5,s1,s0
	bne	a0,s3,.LBuiltin_28
.LBuiltin_22:
	sb	zero,0(a5)
	ld	ra,40(sp)
	ld	s0,32(sp)
	ld	s2,16(sp)
	ld	s3,8(sp)
	ld	s4,0(sp)
	mv	a0,s1
	ld	s1,24(sp)
	addi	sp,sp,48
	jr	ra
.LBuiltin_27:
	lui	a5,%hi(stderr)
	ld	a0,%lo(stderr)(a5)
	lui	a1,%hi(.LBuiltin_C5)
	addi	a1,a1,%lo(.LBuiltin_C5)
	call	fprintf
	li	a0,1
	call	exit
	j	.LBuiltin_20
	.size	getString, .-getString
	.align	2
	.globl	getInt
	.type	getInt, @function
getInt:
	addi	sp,sp,-32
	lui	a0,%hi(.LBuiltin_C3)
	addi	a1,sp,12
	addi	a0,a0,%lo(.LBuiltin_C3)
	sd	ra,24(sp)
	call	scanf
	li	a4,1
	li	a5,0
	bne	a0,a4,.LBuiltin_30
	lw	a5,12(sp)
.LBuiltin_30:
	ld	ra,24(sp)
	mv	a0,a5
	addi	sp,sp,32
	jr	ra
	.size	getInt, .-getInt
	.align	2
	.globl	__builtin_exit
	.type	__builtin_exit, @function
__builtin_exit:
	addi	sp,sp,-16
	sd	ra,8(sp)
	call	exit
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	__builtin_exit, .-__builtin_exit
	.section	.rodata.str1.8
	.align	3
.LBuiltin_C6:
	.string	"%u"
	.text
	.align	2
	.globl	u32_to_string
	.type	u32_to_string, @function
u32_to_string:
	addi	sp,sp,-32
	sd	s1,8(sp)
	mv	s1,a0
	li	a0,16
	sd	s0,16(sp)
	sd	ra,24(sp)
	call	malloc
	mv	s0,a0
	beq	a0,zero,.LBuiltin_39
.LBuiltin_37:
	lui	a1,%hi(.LBuiltin_C6)
	mv	a2,s1
	mv	a0,s0
	addi	a1,a1,%lo(.LBuiltin_C6)
	call	sprintf
	ld	ra,24(sp)
	mv	a0,s0
	ld	s0,16(sp)
	ld	s1,8(sp)
	addi	sp,sp,32
	jr	ra
.LBuiltin_39:
	li	a0,1
	call	exit
	j	.LBuiltin_37
	.size	u32_to_string, .-u32_to_string
	.section	.rodata.str1.8
	.align	3
.LBuiltin_C7:
	.string	"%lu"
	.text
	.align	2
	.globl	usize_to_string
	.type	usize_to_string, @function
usize_to_string:
	addi	sp,sp,-32
	sd	s1,8(sp)
	mv	s1,a0
	li	a0,32
	sd	s0,16(sp)
	sd	ra,24(sp)
	call	malloc
	mv	s0,a0
	beq	a0,zero,.LBuiltin_43
.LBuiltin_41:
	lui	a1,%hi(.LBuiltin_C7)
	mv	a2,s1
	mv	a0,s0
	addi	a1,a1,%lo(.LBuiltin_C7)
	call	sprintf
	ld	ra,24(sp)
	mv	a0,s0
	ld	s0,16(sp)
	ld	s1,8(sp)
	addi	sp,sp,32
	jr	ra
.LBuiltin_43:
	li	a0,1
	call	exit
	j	.LBuiltin_41
	.size	usize_to_string, .-usize_to_string
	.align	2
	.globl	string_len
	.type	string_len, @function
string_len:
	beq	a0,zero,.LBuiltin_46
	addi	sp,sp,-16
	sd	ra,8(sp)
	call	strlen
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
.LBuiltin_46:
	li	a0,0
	ret
	.size	string_len, .-string_len
	.align	2
	.globl	string_as_str
	.type	string_as_str, @function
string_as_str:
	ret
	.size	string_as_str, .-string_as_str
	.align	2
	.globl	string_from
	.type	string_from, @function
string_from:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	beq	a0,zero,.LBuiltin_58
	sd	s1,8(sp)
	mv	s1,a0
	call	strlen
	addi	a0,a0,1
	call	malloc
	mv	s0,a0
	beq	a0,zero,.LBuiltin_59
	mv	a1,s1
	call	strcpy
	ld	ra,24(sp)
	mv	a0,s0
	ld	s0,16(sp)
	ld	s1,8(sp)
	addi	sp,sp,32
	jr	ra
.LBuiltin_59:
	li	a0,1
	call	exit
	ld	ra,24(sp)
	mv	a0,s0
	ld	s0,16(sp)
	ld	s1,8(sp)
	addi	sp,sp,32
	jr	ra
.LBuiltin_58:
	li	a0,1
	call	malloc
	mv	s0,a0
	beq	a0,zero,.LBuiltin_60
	sb	zero,0(s0)
.LBuiltin_61:
	ld	ra,24(sp)
	mv	a0,s0
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
.LBuiltin_60:
	li	a0,1
	call	exit
	sb	zero,0(s0)
	j	.LBuiltin_61
	.size	string_from, .-string_from
	.section	.rodata.str1.8
	.align	3
.LBuiltin_C8:
	.string	"Error: memory allocation failed in append\n"
	.text
	.align	2
	.globl	string_append
	.type	string_append, @function
string_append:
	beq	a0,zero,.LBuiltin_76
	addi	sp,sp,-48
	sd	s1,24(sp)
	sd	ra,40(sp)
	mv	s1,a1
	beq	a1,zero,.LBuiltin_62
	sd	s3,8(sp)
	ld	s3,0(a0)
	sd	s0,32(sp)
	sd	s2,16(sp)
	mv	s0,a0
	beq	s3,zero,.LBuiltin_64
	mv	a0,s3
	call	strlen
	mv	s2,a0
	mv	a0,s1
	call	strlen
	add	a1,s2,a0
	addi	a1,a1,1
	mv	a0,s3
	call	realloc
	mv	s2,a0
	beq	a0,zero,.LBuiltin_79
.LBuiltin_68:
	mv	a0,s2
	mv	a1,s1
	call	strcat
	sd	s2,0(s0)
	ld	s3,8(sp)
	ld	s0,32(sp)
	ld	s2,16(sp)
.LBuiltin_62:
	ld	ra,40(sp)
	ld	s1,24(sp)
	addi	sp,sp,48
	jr	ra
.LBuiltin_64:
	mv	a0,a1
	call	strlen
	addi	a1,a0,1
	li	a0,0
	call	realloc
	mv	s2,a0
	beq	a0,zero,.LBuiltin_80
	sb	zero,0(s2)
	j	.LBuiltin_68
.LBuiltin_76:
	ret
.LBuiltin_80:
	lui	a5,%hi(stderr)
	ld	a0,%lo(stderr)(a5)
	lui	a1,%hi(.LBuiltin_C8)
	addi	a1,a1,%lo(.LBuiltin_C8)
	call	fprintf
	li	a0,1
	call	exit
	sb	zero,0(s2)
	j	.LBuiltin_68
.LBuiltin_79:
	lui	a5,%hi(stderr)
	ld	a0,%lo(stderr)(a5)
	lui	a1,%hi(.LBuiltin_C8)
	addi	a1,a1,%lo(.LBuiltin_C8)
	call	fprintf
	li	a0,1
	call	exit
	j	.LBuiltin_68
	.size	string_append, .-string_append
