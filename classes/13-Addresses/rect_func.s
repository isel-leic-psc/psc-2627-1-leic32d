	.text
	.global rects_total_area
rects_total_area:
	xorq %rax, %rax

.Lloop1:
	testq %rsi, %rsi
	jz .Lexit1

	movl   8(%rdi), %ecx
	imull 12(%rdi), %ecx

	addl %ecx, %eax

	addq $16, %rdi
	decq %rsi
	jmp .Lloop1

.Lexit1:
	ret

	.global rect_refs_total_area
rect_refs_total_area:
	xorq %rax, %rax

	jmp .Ltest2
.Lloop2:
	decq %rsi

	movq (%rdi, %rsi, 8), %rdx
	movl   8(%rdx), %ecx
	imull 12(%rdx), %ecx

	addl %ecx, %eax

.Ltest2:
	testq %rsi, %rsi
	jnz .Lloop2

.Lexit2:
	ret

	.section .note.GNU-stack,"",@progbits
