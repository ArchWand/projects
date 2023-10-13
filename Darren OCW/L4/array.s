	.file	"array.cpp"
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
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$2, -32(%rbp)
	movl	$3, -28(%rbp)
	movl	$5, -24(%rbp)
	movl	$7, -20(%rbp)
	movl	-32(%rbp), %edx
	movl	-28(%rbp), %eax
	imull	%eax, %edx
	movl	-24(%rbp), %eax
	imull	%eax, %edx
	movl	-20(%rbp), %eax
	imull	%edx, %eax
	movl	%eax, -36(%rbp)
	movl	-36(%rbp), %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L3
	call	__stack_chk_fail@PLT
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.1.1 20230714"
	.section	.note.GNU-stack,"",@progbits
