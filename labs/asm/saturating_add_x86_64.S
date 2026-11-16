    .text
    .globl saturating_add_i64
    .type saturating_add_i64, @function
# System V AMD64 ABI: rdi + rsi -> rax, clamped to signed 64-bit limits.
saturating_add_i64:
    movq %rdi, %rax
    addq %rsi, %rax
    jno .Ldone
    testq %rdi, %rdi
    js .Lnegative
    movabsq $0x7fffffffffffffff, %rax
    ret
.Lnegative:
    movabsq $0x8000000000000000, %rax
.Ldone:
    ret
    .size saturating_add_i64, .-saturating_add_i64
    .section .note.GNU-stack,"",@progbits
