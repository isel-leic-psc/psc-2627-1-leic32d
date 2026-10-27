	.text
	.global stringlen
stringlen:
	xorq %rax, %rax
slen_loop:
	movb (%rdi, %rax), %cl
	test %cl, %cl
	jz slen_end
	inc %rax
	jmp slen_loop
slen_end:
	ret

	.section .note.GNU-stack,"",@progbits

