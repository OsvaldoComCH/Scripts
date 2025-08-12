.section .text
.globl _main

_Z6sincosdP13sincos_result:
    movq    $0x401921FB54442D18, %rax
    movq    %rax, %xmm1
    comisd  %xmm1, %xmm0
    ja      .L0
    movq    $0xC01921FB54442D18, %rax
    movq    %rax, %xmm2
    comisd  %xmm2, %xmm0
    jb      .L0
    xorq    %rax, %rax
    jmp     .L1
.L0:
    movsd   %xmm0, %xmm2
    divsd   %xmm1, %xmm2
    cvttsd2si   %xmm2, %rax
    cvtsi2sd    %rax, %xmm2
    mulsd   %xmm1, %xmm2
    subsd   %xmm2, %xmm0
.L1:
    movq    %xmm0, %rax
    ret

_main:
    movq    $0x40198861baaa937e, %rax
    movq    %rax, %xmm0
    xorq    %rcx, %rcx
    call    _Z6sincosdP13sincos_result
    ret
