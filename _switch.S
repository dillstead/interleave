# Switches stacks from current, which must be the running thread, to next
# which must also be running switch(), returning current's stack to
# next's context.
# void **_switch(void ***cur_esp, void ***next_esp);
.globl _switch
.func _switch
_switch:
	# Note that the SVR4 ABI requires %rbp, %rbx, and %r12 through
        # %r15 to be preserved by the callee. [SysV-ABI-AMD64 section 3.2.1]
        # The first parameter will be in %rdi. [SysV-ABI-AMD64 section 3.2.3]
        # In the case of the stack frame contrived in start, this value
        # will be on the stack as the parameter to the apply function.
        # It needs to be pushed and restored so it's set to the proper
        # value when apply is run upon return from this function.
        # Save caller's register state.
	push %rbp
	push %rbx
	push %r12
        push %r13
        push %r14
        push %r15
	push %rdi
        # Save current stack pointer.
        mov %rsp, %rax
        mov %rax, (%rdi)
        # Restore next stack pointer.
        mov (%rsi), %rsp
        # Restore caller's register state.
        pop %rdi
	pop %r15
	pop %r14
        pop %r13
        pop %r12
        pop %rbx
	pop %rbp
        ret
.endfunc
        
