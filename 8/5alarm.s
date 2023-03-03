	.file	"5alarm.c"
	.text
	.p2align 4
	.type	h1, @function
h1:
.LFB22:
	.cfi_startproc
	movl	$0, loop(%rip)
	ret
	.cfi_endproc
.LFE22:
	.size	h1, .-h1
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%lld\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movl	$5, %edi
	call	alarm@PLT
	leaq	h1(%rip), %rsi
	movl	$14, %edi
	call	signal@PLT
	movl	loop(%rip), %eax
	testl	%eax, %eax
	je	.L4
	.p2align 4,,10
	.p2align 3
.L5:
	movl	loop(%rip), %eax
	addq	$1, %rbx
	testl	%eax, %eax
	jne	.L5
.L4:
	leaq	.LC0(%rip), %rdi
	movq	%rbx, %rsi
	xorl	%eax, %eax
	call	printf@PLT
	xorl	%edi, %edi
	call	exit@PLT
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.data
	.align 4
	.type	loop, @object
	.size	loop, 4
loop:
	.long	1
	.ident	"GCC: (Debian 12.2.0-14) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
