	.file	"a.c"
	.comm	c,200,32
	.globl	a
	.data
	.align 8
	.type	a, @object
	.size	a, 8
a:
	.string	"sdfhgfd"
	.section	.rodata
.LC0:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$2, -100(%rbp)
	movl	$0, -104(%rbp)
	jmp	.L2
.L3:
	movl	-104(%rbp), %eax
	imull	-104(%rbp), %eax
	movl	%eax, %edx
	movl	-104(%rbp), %eax
	cltq
	movl	%edx, -96(%rbp,%rax,4)
	movl	-104(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, -104(%rbp)
.L2:
	cmpl	$19, -104(%rbp)
	jle	.L3
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L5
	call	__stack_chk_fail
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
