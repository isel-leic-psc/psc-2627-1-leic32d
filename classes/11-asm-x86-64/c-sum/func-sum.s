	.text
	.global fsum
fsum:
	movq %rdi, %rax
	addq %rsi, %rax
	ret

	.section .note.GNU-stack,"",@progbits

