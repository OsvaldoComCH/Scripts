.section .text
.globl _main

_Z6sincosdP13sincos_result:
    movq    $0x401921FB54442D18, %rax
    movq    %rax, %xmm1
    comisd  %xmm1, %xmm0
    jl      .L0
    movq    $0xC01921FB54442D18, %rax
    movq    %rax, %xmm1
    comisd  %xmm1, %xmm0
    jg      .L0
    xorq    %rax, %rax
    jmp     .L1
.L0:
    movq    $1, %rax
.L1:
    ret

_main:
    movq    $0xC02921FB54442D18, %rax
    movq    %rax, %xmm0
    xorq    %rcx, %rcx
    call    _Z6sincosdP13sincos_result
    ret
