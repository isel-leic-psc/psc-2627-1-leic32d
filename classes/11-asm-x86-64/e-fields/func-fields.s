	.text
	.global example_sum_of_fields
example_sum_of_fields:
	movl 4(%rdi), %eax
	addl 16(%rsi), %eax
	ret

	.section .note.GNU-stack,"",@progbits

