	.text
	.global map_ptrs_to_objs
map_ptrs_to_objs:
    pushq %rbp
    movq %rsp, %rbp
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
	subq $16, %rsp          # Local variable + alignment

    movq %rdi, %r12         # current input pointer ref
    movq %rsi, %r13         # current output object ref
    movq %rcx, %r14         # size of each output object
    movq %r8,  %r15         # address of map_obj
    movq %rdx, -40(%rbp)    # remaining element count

    cmpq $0, -40(%rbp)      # initial count check
    jmp .Lcheck
.Lbody:
    movq (%r12), %rdi       # input object address
    movq %r13, %rsi         # output object address
    call *%r15              # map_obj(input, output)

	addq $8, %r12
	addq %r14, %r13
    decq -40(%rbp)          # decrement count
.Lcheck:
    jnz .Lbody              # is count == 0 ?

    addq $16, %rsp
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rbp
    ret

	.section .note.GNU-stack,"",@progbits
