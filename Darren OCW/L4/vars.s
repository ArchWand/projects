	.file	"vars.cpp"
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
	movl	$2, -20(%rbp)
	movl	$3, -16(%rbp)
	movl	$5, -12(%rbp)
	movl	$7, -8(%rbp)
	movl	-20(%rbp), %eax
	imull	-16(%rbp), %eax
	imull	-12(%rbp), %eax
	movl	-8(%rbp), %edx
	imull	%edx, %eax
	movl	%eax, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.1.1 20230714"
	.section	.note.GNU-stack,"",@progbits
