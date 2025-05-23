	.file	"sincos.cpp"
	.text
	.p2align 4
	.globl	_Z6sincosdP13sincos_result
	.def	_Z6sincosdP13sincos_result;	.scl	2;	.type	32;	.endef
	.seh_proc	_Z6sincosdP13sincos_result
_Z6sincosdP13sincos_result:
.LFB2241:
	.seh_endprologue
	movsd	.LC0(%rip), %xmm2
	movapd	%xmm0, %xmm1
	movq	%rdx, %rcx
	divsd	%xmm2, %xmm1
	cvttsd2sil	%xmm1, %eax
	pxor	%xmm1, %xmm1
	cvtsi2sdl	%eax, %xmm1
	mulsd	%xmm2, %xmm1
	subsd	%xmm1, %xmm0
	movsd	.LC1(%rip), %xmm1
	movq	%xmm0, %rax
	btrq	$63, %rax
	movq	%rax, %xmm4
	comisd	%xmm4, %xmm1
	ja	.L19
	movsd	.LC2(%rip), %xmm1
	comisd	%xmm4, %xmm1
	jbe	.L30
	movsd	.LC3(%rip), %xmm5
	movapd	%xmm4, %xmm3
	movl	$1, %eax
	subsd	%xmm5, %xmm3
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L19:
	movsd	.LC3(%rip), %xmm5
	movapd	%xmm4, %xmm3
	xorl	%eax, %eax
.L2:
	movsd	.LC8(%rip), %xmm1
	mulsd	%xmm3, %xmm1
	mulsd	%xmm3, %xmm1
	movapd	%xmm1, %xmm3
	movapd	%xmm1, %xmm2
	mulsd	%xmm1, %xmm3
	divsd	.LC9(%rip), %xmm3
	subsd	%xmm3, %xmm2
	movsd	.LC10(%rip), %xmm3
	movapd	%xmm3, %xmm1
	subsd	%xmm2, %xmm1
	movapd	%xmm1, %xmm2
	mulsd	%xmm1, %xmm2
	subsd	%xmm2, %xmm3
/APP
 # 73 "sincos.cpp" 1
	sqrtsd  %xmm3, %xmm3
 # 0 "" 2
/NO_APP
	movapd	%xmm3, %xmm2
	testb	%al, %al
	je	.L9
	movapd	%xmm1, %xmm2
	movapd	%xmm3, %xmm1
.L9:
	comisd	%xmm4, %xmm5
	movq	%xmm1, %rax
	movq	%xmm2, %rdx
	jbe	.L33
	movabsq	$9223372036854775807, %r8
	andq	%r8, %rdx
	andq	%rax, %r8
.L12:
	pxor	%xmm1, %xmm1
	movq	%rdx, (%rcx)
	comisd	%xmm0, %xmm1
	movq	%r8, 8(%rcx)
	ja	.L36
	ret
	.p2align 4,,10
	.p2align 3
.L33:
	movsd	.LC5(%rip), %xmm1
	comisd	%xmm4, %xmm1
	jbe	.L34
	btsq	$63, %rax
	btrq	$63, %rdx
	movq	%rax, %r8
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L36:
	btcq	$63, %rdx
	movq	%rdx, (%rcx)
	ret
	.p2align 4,,10
	.p2align 3
.L30:
	movsd	.LC4(%rip), %xmm1
	comisd	%xmm4, %xmm1
	ja	.L37
	movsd	.LC6(%rip), %xmm1
	movapd	%xmm4, %xmm3
	comisd	%xmm4, %xmm1
	jbe	.L32
	subsd	.LC7(%rip), %xmm3
	movsd	.LC3(%rip), %xmm5
	movl	$1, %eax
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L34:
	movabsq	$-9223372036854775808, %r9
	movsd	.LC7(%rip), %xmm1
	movq	%rax, %r8
	movq	%r9, %r10
	btrq	$63, %r8
	orq	%r9, %rdx
	orq	%rax, %r10
	comisd	%xmm4, %xmm1
	cmova	%r10, %r8
	jmp	.L12
	.p2align 4,,10
	.p2align 3
.L37:
	movapd	%xmm4, %xmm3
	movsd	.LC3(%rip), %xmm5
	xorl	%eax, %eax
	subsd	.LC5(%rip), %xmm3
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L32:
	subsd	%xmm2, %xmm3
	movsd	.LC3(%rip), %xmm5
	xorl	%eax, %eax
	jmp	.L2
	.seh_endproc
	.section .rdata,"dr"
.LC12:
	.ascii "sin: \0"
.LC13:
	.ascii "\12cos: \0"
	.section	.text.startup,"x"
	.p2align 4
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
.LFB2242:
	subq	$72, %rsp
	.seh_stackalloc	72
	.seh_endprologue
	call	__main
	movq	.refptr._ZSt3cin(%rip), %rcx
	leaq	40(%rsp), %rdx
	call	_ZNSi10_M_extractIdEERSiRT_
	movsd	40(%rsp), %xmm0
	leaq	48(%rsp), %rdx
	call	_Z6sincosdP13sincos_result
	movq	.refptr._ZSt4cout(%rip), %rcx
	leaq	.LC12(%rip), %rdx
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movsd	48(%rsp), %xmm1
	movq	%rax, %rcx
	call	_ZNSo9_M_insertIdEERSoT_
	leaq	.LC13(%rip), %rdx
	movq	%rax, %rcx
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movsd	56(%rsp), %xmm1
	movq	%rax, %rcx
	call	_ZNSo9_M_insertIdEERSoT_
	xorl	%eax, %eax
	addq	$72, %rsp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	-57999238
	.long	1075388922
	.align 8
.LC1:
	.long	-57999238
	.long	1072243194
	.align 8
.LC2:
	.long	1030242396
	.long	1073928572
	.align 8
.LC3:
	.long	-57999238
	.long	1073291770
	.align 8
.LC4:
	.long	-1146240872
	.long	1074752121
	.align 8
.LC5:
	.long	-57999238
	.long	1074340346
	.align 8
.LC6:
	.long	-1661362069
	.long	1075183035
	.align 8
.LC7:
	.long	1030242396
	.long	1074977148
	.align 8
.LC8:
	.long	0
	.long	1071644672
	.align 8
.LC9:
	.long	0
	.long	1075314688
	.align 8
.LC10:
	.long	0
	.long	1072693248
	.def	__main;	.scl	2;	.type	32;	.endef
	.ident	"GCC: (Rev2, Built by MSYS2 project) 14.2.0"
	.def	_ZNSi10_M_extractIdEERSiRT_;	.scl	2;	.type	32;	.endef
	.def	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc;	.scl	2;	.type	32;	.endef
	.def	_ZNSo9_M_insertIdEERSoT_;	.scl	2;	.type	32;	.endef
	.section .drectve
	.ascii " -export:\"_Z6sincosdP13sincos_result\""
	.section	.rdata$.refptr._ZSt4cout, "dr"
	.globl	.refptr._ZSt4cout
	.linkonce	discard
.refptr._ZSt4cout:
	.quad	_ZSt4cout
	.section	.rdata$.refptr._ZSt3cin, "dr"
	.globl	.refptr._ZSt3cin
	.linkonce	discard
.refptr._ZSt3cin:
	.quad	_ZSt3cin
