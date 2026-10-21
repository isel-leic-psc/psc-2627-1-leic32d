	.section .rodata
msg:
	.asciz "Hello, ISEL!"

	.section .text
	.global main
	.extern puts
main:
	leaq	msg, %rdi
	call	puts

	xorq    %rax, %rax
	ret

